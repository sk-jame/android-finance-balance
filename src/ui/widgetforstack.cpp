#include <QKeyEvent>
#include "widgetforstack.h"

Operation WidgetForStack::m_operation = Operation();
TaskQueue* WidgetForStack::task_queue = nullptr;

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
