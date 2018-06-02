#include "incomestackwidget.h"
#include <QDebug>
#include "data/task.h"

IncomeStackWidget::IncomeStackWidget(QWidget* parent)
    : StackWidget(parent),
      saved_page(new AmountWidget("Взять деньги из сохранённых на будущее")),
      salary_page(new AmountWidget("Получены средства (зарплата/подарок)"))
{
    IncomeOperation op;
    main_page = new ReasonWidget(op.getReasonsNames(), this);
    index_main_page = addWidget(main_page);
    addWidget(salary_page);
    addWidget(saved_page);

    for(int i = 0; i < count(); i++){
        WidgetForStack* w = qobject_cast<WidgetForStack*>(widget(i));
        if (!w) continue;
        connect(w, &WidgetForStack::goNext, this, &IncomeStackWidget::onGoNext);
        connect(w, &WidgetForStack::goBack, this, &IncomeStackWidget::onGoBack);
        connect(w, &WidgetForStack::goHome, this, &IncomeStackWidget::restoreMain);
    }
}

IncomeStackWidget::~IncomeStackWidget()
{

}

void IncomeStackWidget::operation_finished(Task *)
{

}

void IncomeStackWidget::onGoBack()
{

}

void IncomeStackWidget::onGoNext()
{
    if (currentWidget() == main_page){
        switch(main_page->checkedIndex()){
        case IncomePage::select_credit:
            break;
        case IncomePage::select_salary:
            setCurrentWidget(salary_page);
            break;
        case IncomePage::select_saved:
            setCurrentWidget(saved_page);
            break;
        }
        return;
    }

    IncomeOperation* op = new IncomeOperation;
    SaveDataTask* task = new SaveDataTask(this, static_cast<Operation*>(op));
    task->setRemove_on_finish(true);
    if (currentWidget() == salary_page){
        op->amount = salary_page->amount();
        op->comment = salary_page->comment();
    }
    else if (currentWidget() == saved_page){
        op->amount = saved_page->amount();
        op->comment = saved_page->comment();
    }

    emit addTask(task);
    emit goHome();
}

void IncomeStackWidget::restoreMain()
{
    setCurrentWidget(main_page);
    emit goHome();
}

void IncomeStackWidget::onWaitTask(int uid, QString str_wait_for, QString str_success, QString str_error)
{

}
