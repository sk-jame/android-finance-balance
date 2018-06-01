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
    void on_pushButton_clicked();
    void on_TableWidget_updateData();
    void on_pushButton_2_clicked();
private:
    Ui::SummaryWidget *ui;

    // WidgetForStack interface
    void callTableUpdate();
public slots:
    void operation_finished(Task *ftask);
};

#endif // SUMMARYWIDGET_H
