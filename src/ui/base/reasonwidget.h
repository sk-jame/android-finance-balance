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
    Q_PROPERTY(QStringList names READ names)
    Q_PROPERTY(int checkedIndex READ checkedIndex WRITE setCheckedIndex NOTIFY checkedIndexChanged)
public:
    explicit ReasonWidget(QStringList _names, QWidget *parent = 0);
    ~ReasonWidget();
    QStringList names() const;
    int checkedIndex() const;
public slots:
    void setCheckedIndex(int checkedIndex);
signals:
    void checkedIndexChanged(int checkedIndex);
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
private:
    Ui::ReasonWidget *ui;
    QStringList m_names;
    int m_checkedIndex;
};

#endif // REASONWIDGET_H
