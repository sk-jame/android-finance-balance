#ifndef AMOUNTWIDGET_H
#define AMOUNTWIDGET_H

#include "widgetforstack.h"
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QDialogButtonBox>

class AmountWidget : public WidgetForStack
{
    Q_OBJECT
    QLabel *labelAmount;
    QLabel *labelComment;
    QLineEdit *leAmount;
    QLineEdit *leComment;
    QDialogButtonBox *btnBox;
    QSpacerItem *spacer;
    QVBoxLayout *lay;
public:
    AmountWidget(QWidget *parent);
    ~AmountWidget();
protected slots:
    void onOk();
    void onCancel();
};

#endif // AMOUNTWIDGET_H
