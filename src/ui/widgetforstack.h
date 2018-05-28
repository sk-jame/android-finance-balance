#ifndef WIDGETFORSTACK_H
#define WIDGETFORSTACK_H

#include "data/operations.h"
#include <QWidget>
#include "data/task.h"

class WidgetForStack : public QWidget
{
    Q_OBJECT
protected:
    static TaskQueue* task_queue;
    static Operation m_operation;
public:
    explicit WidgetForStack(QWidget *parent = nullptr);
    static void setTaskQueue(TaskQueue* dbw);
signals:
    void goNext();
    void goHome();
    void goBack();
    void goWait(QString wait_for    = "Working...",
                QString success_msg = "Success",
                QString fail_msg    = "Failure");

    void notify(QString notification_message);
public slots:

    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event);
};



#endif // WIDGETFORSTACK_H
