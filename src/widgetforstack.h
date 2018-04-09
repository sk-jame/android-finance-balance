#ifndef WIDGETFORSTACK_H
#define WIDGETFORSTACK_H

#include "operations.h"
#include <QWidget>

class WidgetForStack : public QWidget
{
    Q_OBJECT
protected:

    static Operation m_operation;
public:
    explicit WidgetForStack(QWidget *parent = nullptr);

signals:
    void goNext();
    void goHome();
    void goBack();
public slots:

    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // WIDGETFORSTACK_H
