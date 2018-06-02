#ifndef WIDGETFORSTACK_H
#define WIDGETFORSTACK_H

#ifndef TEST

#include "common/operations.h"
#include <QWidget>
#include "data/task.h"

class WidgetForStack : public QWidget
{
    Q_OBJECT
protected:
    static TaskQueue* task_queue;
    static Operation m_operation;
    static bool m_canContinue;
public:
    explicit WidgetForStack(QWidget *parent = nullptr);
    static void setTaskQueue(TaskQueue* dbw);
    static TaskQueue *getTask_queue();

signals:
    void goNext();
    void goHome();
    void goBack();
    void goWaitTask(int uid,
                    QString wait_for    = "Working...",
                    QString success_msg = "Success",
                    QString fail_msg    = "Failure");

    void notify(QString notification_message);
public slots:
    void operation_error(QString error, int code);
    virtual void operation_finished(Task*) {}
    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event);
};

#else
#include <QWidget>
typedef QWidget WidgetForStack;
#endif // TEST

#endif // WIDGETFORSTACK_H
