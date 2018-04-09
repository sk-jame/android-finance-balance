#ifndef SUMMARYWIDGET_H
#define SUMMARYWIDGET_H

#include <QWidget>

namespace Ui {
class SummaryWidget;
}

class SummaryWidget : public QWidget
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
};

#endif // SUMMARYWIDGET_H
