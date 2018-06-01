#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "summarywidget.h"
#include "incomewidget.h"
#include "amountwidget.h"
#include "outcomewidget.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    wait_dialog(this)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->stackedWidget);
    ui->stackedWidget->widget(eWidget_main)->setLayout(ui->verticalLayout_4);

    outcomeWidgetIndex = ui->stackedWidget->addWidget(new OutcomeWidget(this));
    amountWidgetIndex = ui->stackedWidget->addWidget(new AmountWidget(this));
    incomeWidgetIndex = ui->stackedWidget->addWidget(new IncomeWidget(this));
    summaryWidgetIndex = ui->stackedWidget->addWidget(new SummaryWidget(this));

    for(int i = 0; i < ui->stackedWidget->count(); i++){
        WidgetForStack* w = qobject_cast<WidgetForStack*>(ui->stackedWidget->widget(i));
        if (!w) continue;
        connect(w, &WidgetForStack::goNext, this, &MainWindow::onGoNext);
        connect(w, &WidgetForStack::goBack, this, &MainWindow::onGoBack);
        connect(w, &WidgetForStack::goHome, this, &MainWindow::restoreMain);
        connect(w, &WidgetForStack::goWaitTask, this, &MainWindow::onWaitTask);
        connect(this, &MainWindow::error, w, &WidgetForStack::operation_error);
    }
    wait_dialog.close();
}

MainWindow::~MainWindow()
{
    delete ui;
    emit finished();
}

void MainWindow::init_labels()
{
    ReadDataTask *task = new ReadDataTask(nullptr);
    task->filter.filterType = DataFilter::filter_all_tables;
    int uid = WidgetForStack::getTask_queue()->addNewTask(task);
    if (uid < 0){
        qDebug() << __FUNCTION__ << uid;
        return;
    }
    wait_task_uid = uid;
}

void MainWindow::onGoBack()
{
    int i = ui->stackedWidget->currentIndex();
    if (i == amountWidgetIndex){
        ui->stackedWidget->setCurrentIndex(outcomeWidgetIndex);
    }
    else{
        restoreMain();
    }
}

void MainWindow::onGoNext()
{
    if (ui->stackedWidget->currentIndex() == outcomeWidgetIndex){
        ui->stackedWidget->setCurrentIndex(amountWidgetIndex);
    }
    else if (ui->stackedWidget->currentIndex() == incomeWidgetIndex){
        restoreMain();
    }
    else if (ui->stackedWidget->currentIndex() == amountWidgetIndex){
        restoreMain();
    }
}

void MainWindow::restoreMain()
{
    init_labels();
    ui->stackedWidget->setCurrentIndex(eWidget_main);
}

void MainWindow::on_pbAddOut_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(outcomeWidgetIndex);
}

void MainWindow::on_pbAddIn_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(incomeWidgetIndex);
}

void MainWindow::on_pbSummary_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(summaryWidgetIndex);
}

void MainWindow::onWaitTask(int uid, QString str_wait_for, QString str_success, QString str_error)
{
    wait_dialog.setWindowTitle(str_wait_for + QString::asprintf(" .Task #%i", uid));
    wait_dialog.setMinimum(0);
    wait_dialog.setMaximum(1);
    wait_dialog.setModal(true);

    wait_task_uid = uid;
//    wait_dialog.show();
}

void MainWindow::onFinishedTask(Task* ftask)
{
    if (wait_task_uid == ftask->uid()){
        wait_dialog.close();
        if (ftask->status() == Task::status_failure){
            qDebug()<<"Task failed. UID:" << ftask->uid();
            return;
        }

        if (ftask->taskType() == Task::task_read){
            ReadDataTask* task = static_cast<ReadDataTask*>(ftask);
            DataContainer dc(this);
            dc.setOperations(task->read_data());
            ui->labelInData->setText(QString::number(dc.totalIncome()));
            ui->labelOutData->setText(QString::number(dc.totalOutcome()));
            ui->labelSavedData->setText(QString::number(dc.totalSaved()));
            ui->labelBalanceData->setText(QString::number(dc.totalDifference()));
        }

        if (ftask->lastWidget() == nullptr){
            WidgetForStack::getTask_queue()->removeTask(ftask);
            delete ftask;
            return;
        }

        for(int i = 0; i < ui->stackedWidget->count(); i++){
            if (ui->stackedWidget->widget(i) == ftask->lastWidget()){
                ftask->lastWidget()->operation_finished(ftask);
                ui->stackedWidget->setCurrentIndex(i);
                break;
            }
        }
    }
}
