#ifndef INCOMEWIDGET_H
#define INCOMEWIDGET_H

#include "widgetforstack.h"
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QDialogButtonBox>
#include <QCheckBox>

class IncomeWidget : public WidgetForStack
{
    Q_OBJECT
    QLabel *labelAmount;
    QLabel *labelComment;
    QLineEdit *leAmount;
    QLineEdit *leComment;
    QCheckBox *cbFromSaved;
    QDialogButtonBox *btnBox;
    QVBoxLayout *lay;
public:
    IncomeWidget(QWidget *parent);
    ~IncomeWidget();
protected slots:
    void onOk();
    void onCancel();
};

#endif // INCOMEWIDGET_H
