#include <iostream>
#include <QApplication>
#include "gui/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    std::cout << "Hello back end!" << std::endl;
    w.show();
    return a.exec();
}

