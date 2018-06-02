#ifndef AMOUNTWIDGET_H
#define AMOUNTWIDGET_H

#include "widgetforstack.h"

namespace Ui {
class AmountWidget;
}

class AmountWidget : public WidgetForStack
{
    Q_OBJECT
public:
    explicit AmountWidget(QWidget *parent = 0);
    ~AmountWidget();
signals:
    void notify(QString str);
protected slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
private:
    Ui::AmountWidget *ui;
};

#endif // AMOUNTWIDGET_H
