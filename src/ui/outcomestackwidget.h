#ifndef OUTCOMESTACKWIDGET_H
#define OUTCOMESTACKWIDGET_H

#include "stackwidget.h"
#include "base/amountwidget.h"
#include "base/reasonwidget.h"

class OutcomeStackWidget : public StackWidget
{
    ReasonWidget* reasonPage;    // Reason page
    AmountWidget* amountPage;   // Amount page

    // TODO Credit/Debs page
public:
    OutcomeStackWidget(QWidget* parent = Q_NULLPTR);

    // StackWidget interface
public slots:
    virtual void operation_finished(Task *);

protected slots:
    virtual void onGoBack();
    virtual void onGoNext();
    virtual void restoreMain();
    virtual void onWaitTask(int uid, QString wait_reason, QString success_msg, QString failure_msg);
};

#endif // OUTCOMESTACKWIDGET_H
