#include <QDebug>
#include <QDate>
#include "summarywidget.h"
#include "ui_summarywidget.h"
#include "data/datacontainer.h"
#include "dbtableview.h"

SummaryWidget::SummaryWidget(QWidget *parent) :
    WidgetForStack(parent),
    ui(new Ui::SummaryWidget)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    ui->rbAllTime->setChecked(false);
    ui->deFrom->setDate(QDate::currentDate().addMonths(-1));
    ui->deFrom->setTime(QTime(0,0));
    ui->deTo->setDate(QDate::currentDate());
    ui->deTo->setTime(QTime(0,0));
}

SummaryWidget::~SummaryWidget()
{
    delete ui;
}

void SummaryWidget::on_rbPeriod_toggled(bool checked)
{
    ui->deFrom->setEnabled(checked);
    ui->deTo->setEnabled(checked);
}

void SummaryWidget::on_pushButton_clicked()
{
    //db_worker->saveNewOperation(this->m_operation.comment);
    // load operations
    ReadDataTask *task = new ReadDataTask(this);
    task->setDt_from(ui->deFrom->dateTime());
    if (!ui->deTo->dateTime().isValid()){
        ui->deTo->setDateTime(QDateTime::currentDateTime());
    }
    task->setDt_to(ui->deTo->dateTime());
    int uid = task_queue->addNewTask(task);
    if (uid < 0){
        qDebug()<<__FUNCTION__<<uid;
        exit(1);
    }
    emit goWaitTask(uid, "Loading...");
}

void SummaryWidget::operation_finished(Task* ftask)
{
    ReadDataTask* task = static_cast<ReadDataTask*>(ftask);
    DataContainer dc(this);
    dc.setOperations(task->read_data());
    ui->labelInData->setText(QString::number(dc.totalIncome()));
    ui->labelOutData->setText(QString::number(dc.totalOutcome()));
    ui->labelSavedData->setText(QString::number(dc.totalSaved()));
    task_queue->removeTask(task);
    delete task;
}
