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
    connect(ui->tableWidget, &DatabaseTableWidget::updateDataRequest, this, &SummaryWidget::on_TableWidget_updateData);


}

SummaryWidget::~SummaryWidget()
{
    delete ui;
}

void SummaryWidget::on_pushButton_clicked()
{
    if (ui->rbTableSelect_All->isChecked()){
        ui->tableWidget->filter.filterType |= DataFilter::filter_all_tables;
    }
    else if (ui->rbTableSelect_Income->isChecked()){
        ui->tableWidget->filter.filterType &= ~DataFilter::filter_all_tables;
        ui->tableWidget->filter.table = Operation::income;
    }
    else if (ui->rbTableSelect_outcome->isChecked()){
        ui->tableWidget->filter.filterType &= ~DataFilter::filter_all_tables;
        ui->tableWidget->filter.table = Operation::outcome;
    }

    if (ui->rbShowOperations->isChecked()){
        ui->tableWidget->tableType_request = DataContainer::filtering_only;
    }
    else if (ui->rbShowBalanceDaily->isChecked()){
        ui->tableWidget->tableType_request = DataContainer::balance_by_dates;
    }
    else if (ui->rbShowBalanceMonthly->isChecked()){
        ui->tableWidget->tableType_request = DataContainer::balance_by_monthes;
    }
    else if (ui->rbShowDailySum->isChecked()){
        ui->tableWidget->tableType_request = DataContainer::summary_by_dates;
    }
    else if (ui->rbShowMonthlySum->isChecked()){
        ui->tableWidget->tableType_request = DataContainer::summary_by_monthes;
    }
    else if (ui->rbShowReasonSum->isChecked()){
        ui->tableWidget->tableType_request = DataContainer::summary_by_reason;
        ui->tableWidget->filter.filterType &= ~DataFilter::filter_all_tables;
        ui->tableWidget->filter.table = Operation::income;
    }

    callTableUpdate();
}

void SummaryWidget::on_TableWidget_updateData()
{
    callTableUpdate();
}

void SummaryWidget::callTableUpdate()
{
    ui->tableWidget->filter.dateFilter.first = ui->deFrom->dateTime();
    ui->tableWidget->filter.dateFilter.second = ui->deTo->dateTime();
    ui->tableWidget->filter.filterType |= DataFilter::filtered_by_date;

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
        ui->tableWidget->operationFinished(dc.getTable(ui->tableWidget->tableType_request));
        task_queue->removeTask(task);
        delete task;
    }
    else if (ftask->taskType() == Task::task_exec){

    }
}

void SummaryWidget::on_pushButton_2_clicked()
{
    emit goBack();
}
