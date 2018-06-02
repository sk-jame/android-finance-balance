#include <QKeyEvent>
#include "widgetforstack.h"

#ifndef TEST
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
#endif // TEST
