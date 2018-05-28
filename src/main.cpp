#include "ui/mainwindow.h"
#include <QApplication>
#include <QTextStream>
#include <QFile>
#include "data/saveddataworker.h"
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
    SavedDataWorker database_worker(&task_queue);
    WidgetForStack::setTaskQueue(&task_queue);
    w.show();
    database_worker.start();
    return a.exec();
}
