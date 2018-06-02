#include <QApplication>
#include "ui/base/reasonwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReasonWidget w;
    w.show();
    return a.exec();
}
