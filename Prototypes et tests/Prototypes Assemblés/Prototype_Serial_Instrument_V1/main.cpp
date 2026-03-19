#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    MainWindow W1;

    W1.show();

    return App.exec();
}
