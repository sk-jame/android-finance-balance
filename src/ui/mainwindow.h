#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QProgressDialog>
#include <QMainWindow>
#include <data/task.h>

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

    int wait_task_uid;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void init_labels();
    void onFinishedTask(Task *task);
private slots:
    void onGoBack();
    void onGoNext();
    void restoreMain();
    void on_pbAddOut_4_clicked();
    void on_pbAddIn_4_clicked();
    void on_pbSummary_4_clicked();

    void onWaitTask(int uid, QString str_wait_for, QString str_success, QString str_error);
signals:
    void finished(bool value = true);
    void error(QString error, int code);
private:
    Ui::MainWindow *ui;
    QProgressDialog wait_dialog;
};

#endif // MAINWINDOW_H
