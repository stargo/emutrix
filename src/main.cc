#include <QtGui/QApplication>
#include <QtDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(APPLICATION_NAME);
    qDebug() << "Starting " << APPLICATION_NAME << "...";
    MainWindow w;
    w.show();
    return a.exec();
}
