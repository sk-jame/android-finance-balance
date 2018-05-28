#include <QDate>
#include "summarywidget.h"
#include "ui_summarywidget.h"

SummaryWidget::SummaryWidget(QWidget *parent) :
    WidgetForStack(parent),
    ui(new Ui::SummaryWidget)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    ui->rbAllTime->setChecked(true);
    ui->deFrom->setDate(QDate::currentDate().addMonths(-1));
    ui->deTo->setDate(QDate::currentDate());
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
    emit goWait("Saving...");
}
