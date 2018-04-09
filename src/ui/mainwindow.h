#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum EWidgetStack{
        eWidget_main
    };
    int outcomeWidgetIndex;
    int amountWidgetIndex;
    int incomeWidgetIndex;
    int summaryWidgetIndex;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onGoBack();
    void onGoNext();
    void restoreMain();
    void on_pbAddOut_4_clicked();
    void on_pbAddIn_4_clicked();

    void on_pbSummary_4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
