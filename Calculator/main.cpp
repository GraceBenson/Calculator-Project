#include "mainwindow.h"
#include <QApplication>
//#include "sourcecode.cpp"

int main(int argc, char *argv[])
{
    //Stack stackList;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
