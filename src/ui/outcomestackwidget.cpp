#include "data/task.h"
#include "outcomestackwidget.h"
#include "common/operations.h"

OutcomeStackWidget::OutcomeStackWidget(QWidget *parent) :
    StackWidget(parent)
{
    OutcomeOperation op;
    reasonPage = new ReasonWidget(op.getReasonsNames(), this);
    amountPage = new AmountWidget("Потрачено ;)");
    addWidget(reasonPage);
    addWidget(amountPage);
    // todo debs outcome widget
}


void OutcomeStackWidget::operation_finished(Task *)
{

}

void OutcomeStackWidget::onGoBack()
{
    if (currentWidget() == reasonPage){
        emit goHome();
    }
    else if (currentWidget() == amountPage){
        this->setCurrentWidget(reasonPage);
    }
}

void OutcomeStackWidget::onGoNext()
{
    if (currentWidget() == reasonPage){
        this->setCurrentWidget(amountPage);
    }
    else if (currentWidget() == amountPage){
        OutcomeOperation* op = new OutcomeOperation();
        op->reason = reasonPage->checkedIndex();
        op->amount = amountPage->amount();
        op->comment = amountPage->comment();
        SaveDataTask* task = new SaveDataTask(this, op);
        emit addTask(task);
        emit goHome();
    }
}

void OutcomeStackWidget::restoreMain()
{
    setCurrentWidget(reasonPage);
    emit goHome();
}

void OutcomeStackWidget::onWaitTask(int uid, QString wait_reason, QString success_msg, QString failure_msg)
{

}
