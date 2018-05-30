#include "ui/mainwindow.h"
#include <QApplication>
#include <QTextStream>
#include <QFile>
#include "data/databaseworker.h"
#include "ui/widgetforstack.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef NOT_DEFAULT_STYLE_ALLOWED
    QFile file(":/ui/style.qss");
    if (!file.open(QIODevice::ReadOnly))
        exit(0);

    QTextStream in(&file);
    QString css = in.readAll();
    a.setStyleSheet(css);

    file.close();
#endif

    TaskQueue task_queue;
    MainWindow w;
    DataBaseWorker database_worker(&task_queue);
    if (database_worker.isGood() == false){
        qDebug()<<"Something realy bad happens with database(QSql) or mb with db file (QFile)";
        return -1;
    }
    WidgetForStack::setTaskQueue(&task_queue);
    QObject::connect(&w, &MainWindow::finished, &database_worker, &DataBaseWorker::setDone);
    QObject::connect(&w, &MainWindow::error, &database_worker, &DataBaseWorker::error, Qt::QueuedConnection);
    QObject::connect(&task_queue, &TaskQueue::finished_task, &w, &MainWindow::onFinishedTask, Qt::QueuedConnection);

    w.show();
    database_worker.start();
    int ret_code = a.exec();

    database_worker.setDone(true);
    if (database_worker.stop(false))
        database_worker.stop(true);

    return ret_code;
}
