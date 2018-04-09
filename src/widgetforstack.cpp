#include <QKeyEvent>
#include "widgetforstack.h"

Operation WidgetForStack::m_operation = Operation();


WidgetForStack::WidgetForStack(QWidget *parent) : QWidget(parent)
{

}

void WidgetForStack::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Back){
        emit goBack();
    }
}
