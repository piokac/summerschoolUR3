#include "ur3mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UR3MainWindow w;
    w.show();

    return a.exec();
}
