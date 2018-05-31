#include "loggerdialog.h"
#include "ui_loggerdialog.h"
#include "logger.h"

LoggerDialog::LoggerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoggerDialog)
{
    ui->setupUi(this);

    connect(ui->pbClose, &QPushButton::clicked,
            this,        &QDialog::close);

    connect(&timer,      &QTimer::timeout,
            this,        &LoggerDialog::onTimerTo);

    timer.start(1000);
    this->setLayout(ui->verticalLayout);
    setFollow(true);
    setShowed(false);

    connect(this, &QDialog::accepted, [this](){this->setShowed(false);});
    connect(this, &QDialog::rejected, [this](){this->setShowed(false);});

    this->setWindowTitle("Текущие события/обмен");
    m_showEvents = true;

}

LoggerDialog::~LoggerDialog(){
    delete ui;
}

bool LoggerDialog::follow() const{
    return m_follow;
}

bool LoggerDialog::isShowed() const {
    return m_showed;
}

void LoggerDialog::open(){
    setShowed(true);
    QDialog::open();
}

void LoggerDialog::addText(QString str){
    queue.append(str);
}

void LoggerDialog::setFollow(bool follow){
    if (m_follow == follow)
        return;

    m_follow = follow;
    emit followChanged(follow);
}

void LoggerDialog::setShowed(bool showed){
    if (m_showed == showed)
        return;

    m_showed = showed;
    emit showedChanged(showed);
}

void LoggerDialog::onTimerTo(){
    if (!isShowed()) return;
    if (queue.isEmpty()) return;
    colorAppend(queue);
    if (follow()){
        ui->teEvents->ensureCursorVisible();
    }
    mutex.lock();
    queue.clear();
    mutex.unlock();
}

void LoggerDialog::on_cbFollow_toggled(bool checked){
    setFollow(checked);
}

void LoggerDialog::on_pbShowType_clicked(){
    timer.stop();
    queue.clear();
    ui->teEvents->clear();
    if (m_showEvents){
        ui->pbShowType->setText("Отображать события");
    }
    else{
        ui->pbShowType->setText("Отображать обмен");
    }
    m_showEvents = !m_showEvents;
    Logger::setCallbackEvents(m_showEvents);
    timer.start();
}

void LoggerDialog::colorAppend(QString str){
    if (m_showEvents){
        ui->teEvents->appendPlainText(str);
        // show events. return
        return;
    }
    // show sleep. continue
    QStringList list = str.split("\n");
    foreach (QString line, list) {
        line.remove("\n");
        QTextCharFormat tf;
        tf = ui->teEvents->currentCharFormat();
        if (line.contains("r:")){
            // receive
            tf.setForeground(QBrush(Qt::darkRed));
        }
        else if (line.contains("s:")){
            // send
            tf.setForeground(QBrush(Qt::darkBlue));
        }
        ui->teEvents->setCurrentCharFormat(tf);
        ui->teEvents->appendPlainText(line);
    }
}
