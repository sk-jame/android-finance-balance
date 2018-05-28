#ifndef OUTCOMEWIDGET_H
#define OUTCOMEWIDGET_H

#include <QRadioButton>
#include <QDialogButtonBox>
#include <QLayout>
#include <QSpacerItem>
#include "widgetforstack.h"

class OutcomeWidget : public WidgetForStack
{
    Q_OBJECT

    QList<QRadioButton*> radioList;
    QDialogButtonBox* btnBox;
    QVBoxLayout* lay;
public:
    explicit OutcomeWidget(QWidget* parent);
    ~OutcomeWidget();
protected slots:
    void onOk();
    void onCancel();
};

#endif // OUTCOMEWIDGET_H
