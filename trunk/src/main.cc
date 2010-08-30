#include <QtGui/QApplication>
#include <QtDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Starting " << APPLICATION_NAME << "...";
    MainWindow w;
    w.show();
    return a.exec();
}
