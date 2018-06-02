#ifndef INCOMESTACKWIDGET_H
#define INCOMESTACKWIDGET_H

#include "incomepage.h"
#include "stackwidget.h"
#include "base/amountwidget.h"
#include "base/reasonwidget.h"


class IncomeStackWidget : public StackWidget
{
    Q_OBJECT
    ReasonWidget* main_page;
    AmountWidget* saved_page;
    AmountWidget* salary_page;
    int index_main_page;
public:
    IncomeStackWidget(QWidget* parent = Q_NULLPTR);
    ~IncomeStackWidget();
    // StackWidget interface
private:

public slots:
    void operation_finished(Task *);

private slots:
    void onGoBack();
    void onGoNext();
    void restoreMain();
    void onWaitTask(int uid, QString str_wait_for, QString str_success, QString str_error);
};

#endif // INCOMESTACKWIDGET_H
