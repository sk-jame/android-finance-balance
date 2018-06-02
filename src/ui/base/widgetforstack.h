#ifndef WIDGETFORSTACK_H
#define WIDGETFORSTACK_H

#ifndef TEST
#include <QWidget>

class WidgetForStack : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetForStack(QWidget *parent = nullptr);
signals:
    void goNext();
    void goHome();
    void goBack();
protected:
    void keyReleaseEvent(QKeyEvent *event);
};

#else
#include <QWidget>
typedef QWidget WidgetForStack;
#endif // TEST

#endif // WIDGETFORSTACK_H
