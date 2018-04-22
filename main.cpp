#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // display GUI to user and accept inputs
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
