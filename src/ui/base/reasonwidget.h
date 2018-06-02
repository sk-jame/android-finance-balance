#ifndef REASONWIDGET_H
#define REASONWIDGET_H

#include "widgetforstack.h"
#include <QRadioButton>

namespace Ui {
class ReasonWidget;
}

class ReasonWidget : public WidgetForStack
{
    Q_OBJECT
    QList<QRadioButton*> radioList;
public:
    explicit ReasonWidget(QWidget *parent = 0);
    ~ReasonWidget();

private:
    Ui::ReasonWidget *ui;
};

#endif // REASONWIDGET_H
