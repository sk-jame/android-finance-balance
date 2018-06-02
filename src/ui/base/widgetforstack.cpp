#include <QKeyEvent>
#include "widgetforstack.h"
#include <QDebug>

#ifndef TEST

Operation WidgetForStack::m_operation = Operation();
TaskQueue* WidgetForStack::task_queue = nullptr;
bool WidgetForStack::m_canContinue = false;

TaskQueue *WidgetForStack::getTask_queue()
{
    return task_queue;
}

WidgetForStack::WidgetForStack(QWidget *parent)
    : QWidget(parent)
{
}

void WidgetForStack::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Back){
        emit goBack();
    }
}

void WidgetForStack::setTaskQueue(TaskQueue *dbw){
    task_queue = dbw;
}

void WidgetForStack::operation_error(QString error, int code)
{
    m_canContinue = false;
    qDebug()<<error<<"Code:"<<code;
}

#endif // TEST
