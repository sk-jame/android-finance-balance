#include <QKeyEvent>
#include "widgetforstack.h"

Operation WidgetForStack::m_operation = Operation();
SavedDataWorker* WidgetForStack::db_worker = nullptr;

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

void WidgetForStack::setDBWorker(SavedDataWorker *dbw){
    db_worker = dbw;
}
