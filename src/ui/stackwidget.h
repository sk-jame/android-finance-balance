#ifndef STACKWIDGET_H
#define STACKWIDGET_H

#include <QStackedWidget>
#include "data/task.h"
#include "base/widgetforstack.h"

class StackWidget : public QStackedWidget
{
    Q_OBJECT
    bool m_canContinue;
public:
    StackWidget(QWidget* parent = Q_NULLPTR);
    virtual ~StackWidget() {}
protected:
    bool canContinue() const;
    void setCanContinue(bool canContinue);
signals:
    void goHome();
    void addTask(Task* task);
    void removeTask(Task* task);
public slots:
    void operation_error(QString error, int code);

    virtual void operation_finished(Task*) = 0;
protected slots:
    virtual void onGoBack() = 0;
    virtual void onGoNext() = 0;
    virtual void restoreMain() = 0;
    virtual void onWaitTask(int uid, QString wait_reason, QString success_msg, QString failure_msg) = 0;

};

#endif // STACKWIDGET_H
