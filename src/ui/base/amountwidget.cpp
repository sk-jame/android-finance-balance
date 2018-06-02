#include "amountwidget.h"
#include "data/task.h"
#include "ui_amountwidget.h"
#include <QMessageBox>
#include <QDebug>

AmountWidget::AmountWidget(QWidget *parent) :
    WidgetForStack(parent),
    ui(new Ui::AmountWidget)
{
    ui->setupUi(this);
}

AmountWidget::~AmountWidget()
{
    delete ui;
}

void AmountWidget::on_buttonBox_accepted()
{
    bool ok;
    this->m_operation.amount = ui->leAmount->text().toFloat(&ok);
    if (!ok){
        QMessageBox::critical(this, "Херь в сумме", "Сумму в число не получается перевести");
        return;
    }
    this->m_operation.comment = ui->leComment->text();
    SaveDataTask* task = new SaveDataTask(this, this->m_operation);
    task->setRemove_on_finish(true);
    int uid = task_queue->addNewTask(task);
    if (uid < 0){
        qDebug()<<__FUNCTION__<<"Task creation failed"<<uid;
        return;
    }
    emit notify("Операция добавлена в очередь на запись в базу");
    emit goHome();
}

void AmountWidget::on_buttonBox_rejected()
{
    emit goBack();
}
