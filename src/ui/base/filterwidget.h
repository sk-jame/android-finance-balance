#ifndef SUMMARYWIDGET_H
#define SUMMARYWIDGET_H

#include "widgetforstack.h"

namespace Ui {
class FilterWidget;
}

class FilterWidget : public WidgetForStack
{
    Q_OBJECT

public:
    explicit FilterWidget(QWidget *parent = 0);
    ~FilterWidget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_cbShowFilteres_toggled(bool checked);
    void callTableUpdate();
private:
    Ui::FilterWidget *ui;
};

#endif // SUMMARYWIDGET_H
