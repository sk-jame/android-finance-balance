#include <QDebug>
#include <QDate>
#include "filterwidget.h"
#include "ui_filterwidget.h"
#include "data/datacontainer.h"

FilterWidget::FilterWidget(QWidget *parent) :
    WidgetForStack(parent),
    ui(new Ui::FilterWidget)
{
    ui->setupUi(this);
    on_cbShowFilteres_toggled(false);
    this->setLayout(ui->gridLayout);
    ui->deFrom->setDate(QDate::currentDate().addMonths(-1));
    ui->deFrom->setTime(QTime(0,0));
    ui->deTo->setDate(QDate::currentDate());
    ui->deTo->setTime(QTime(0,0));
//    ui->tableWidget->show();
    connect(ui->tableWidget, &DatabaseTableWidget::updateDataRequest, this, &FilterWidget::callTableUpdate);
    connect(ui->lineEdit, &QLineEdit::textChanged, ui->tableWidget, &DatabaseTableWidget::find);
}

FilterWidget::~FilterWidget()
{
    delete ui;
}

void FilterWidget::on_pushButton_clicked()
{
    if (ui->rbTableSelect_All->isChecked()){
        ui->tableWidget->filter.filterFlags |= DataFilter::filter_show_all_tbl;
    }
    else if (ui->rbTableSelect_Income->isChecked()){
        ui->tableWidget->filter.filterFlags &= ~DataFilter::filter_show_all_tbl;
        ui->tableWidget->filter.table = Operation::type_income;
    }
    else if (ui->rbTableSelect_outcome->isChecked()){
        ui->tableWidget->filter.filterFlags &= ~DataFilter::filter_show_all_tbl;
        ui->tableWidget->filter.table = Operation::type_outcome;
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
        ui->tableWidget->filter.filterFlags &= ~DataFilter::filter_show_all_tbl;
        ui->tableWidget->filter.table = Operation::type_outcome;
    }

    callTableUpdate();
}

void FilterWidget::callTableUpdate()
{
//    ui->tableWidget->filter.dateFilter.first = ui->deFrom->dateTime();
//    ui->tableWidget->filter.dateFilter.second = ui->deTo->dateTime();
//    ui->tableWidget->filter.filterFlags |= DataFilter::filtered_by_date;

//    ReadDataTask *task = new ReadDataTask(this);
//    task->filter = ui->tableWidget->filter;

//    int uid = task_queue->addNewTask(task);
//    if (uid < 0){
//        qDebug() << __FUNCTION__ << uid;
//        return;
//    }
//    emit goWaitTask(uid, "Loading...");
}

//void FilterWidget::operation_finished(Task* ftask)
//{
//    if (ftask->status() == Task::status_failure){
//        return;
//    }

//    if (ftask->taskType() == Task::task_read){
//        ReadDataTask* task = static_cast<ReadDataTask*>(ftask);
//        DataContainer dc(this);
//        dc.setOperations(task->read_data());
//        ui->tableWidget->operationFinished(dc.getTable(ui->tableWidget->tableType_request));
//        task_queue->removeTask(task);
//        delete task;
//        qDebug()<<geometry();
//    }
//    else if (ftask->taskType() == Task::task_exec){

//    }
//}

void FilterWidget::on_pushButton_2_clicked()
{
    emit goBack();
}

void FilterWidget::on_cbShowFilteres_toggled(bool checked)
{
    if (checked){
        ui->deFrom->show();
        ui->deTo->show();
        ui->rbShowBalanceDaily->show();
        ui->rbShowBalanceMonthly->show();
        ui->rbShowDailySum->show();
        ui->rbShowMonthlySum->show();
        ui->rbShowOperations->show();
        ui->rbShowReasonSum->show();
        ui->rbTableSelect_All->show();
        ui->rbTableSelect_Income->show();
        ui->rbTableSelect_outcome->show();
        ui->label->show();
        ui->lineEdit->show();
        ui->gridLayout->addItem(ui->verticalLayout, 2, 0, 1);
        ui->gridLayout->addItem(ui->verticalLayout_2, 2, 1, 4);
    }
    else{
        ui->lineEdit->clear();
        ui->deFrom->hide();
        ui->deTo->hide();
        ui->rbShowBalanceDaily->hide();
        ui->rbShowBalanceMonthly->hide();
        ui->rbShowDailySum->hide();
        ui->rbShowMonthlySum->hide();
        ui->rbShowOperations->hide();
        ui->rbShowReasonSum->hide();
        ui->rbTableSelect_All->hide();
        ui->rbTableSelect_Income->hide();
        ui->rbTableSelect_outcome->hide();
        ui->label->hide();
        ui->lineEdit->hide();
        ui->gridLayout->removeItem(ui->verticalLayout);
        ui->gridLayout->removeItem(ui->verticalLayout_2);
    }
}
