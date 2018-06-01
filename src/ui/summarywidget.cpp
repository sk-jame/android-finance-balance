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
    ui->deFrom->setDate(QDate::currentDate().addMonths(-1));
    ui->deFrom->setTime(QTime(0,0));
    ui->deTo->setDate(QDate::currentDate());
    ui->deTo->setTime(QTime(0,0));
    ui->tableWidget->show();
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
    ui->tableWidget->filter.dateFilter.first = ui->deFrom->dateTime();
    ui->tableWidget->filter.dateFilter.second = ui->deTo->dateTime();
    ui->tableWidget->filter.filterType = DataFilter::filtered_by_date;
//    ui->tableWidget->filter.table = Operation::outcome;
    ReadDataTask *task = new ReadDataTask(this);
    task->filter = ui->tableWidget->filter;
    int uid = task_queue->addNewTask(task);
    if (uid < 0){
        qDebug()<<__FUNCTION__<<uid;
        return;
    }
    emit goWaitTask(uid, "Loading...");
}

void SummaryWidget::on_TableWidget_updateData()
{
    ReadDataTask *task = new ReadDataTask(this);
    task->filter = ui->tableWidget->filter;
    int uid = task_queue->addNewTask(task);
    if (uid < 0){
        qDebug() << __FUNCTION__ << uid;
        return;
    }
    emit goWaitTask(uid, "Loading...");
}

void SummaryWidget::operation_finished(Task* ftask)
{
    if (ftask->status() == Task::status_failure){
        return;
    }

    if (ftask->taskType() == Task::task_read){
        ReadDataTask* task = static_cast<ReadDataTask*>(ftask);
        DataContainer dc(this);
        dc.setOperations(task->read_data());
        ui->labelInData->setText(QString::number(dc.totalIncome()));
        ui->labelOutData->setText(QString::number(dc.totalOutcome()));
        ui->labelSavedData->setText(QString::number(dc.totalSaved()));
        ui->tableWidget->operationFinished(dc.getTable(ui->tableWidget->tableType_request));
        task_queue->removeTask(task);
        delete task;
    }
    else if (ftask->taskType() == Task::task_exec){

    }
}
