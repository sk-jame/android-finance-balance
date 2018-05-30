#ifndef SUMMARYWIDGET_H
#define SUMMARYWIDGET_H

#include "widgetforstack.h"

namespace Ui {
class SummaryWidget;
}

class SummaryWidget : public WidgetForStack
{
    Q_OBJECT

public:
    explicit SummaryWidget(QWidget *parent = 0);
    ~SummaryWidget();

private slots:
    void on_rbPeriod_toggled(bool checked);

    void on_pushButton_clicked();

private:
    Ui::SummaryWidget *ui;

    // WidgetForStack interface
public slots:
    void operation_finished(Task *ftask);
};

#endif // SUMMARYWIDGET_H
