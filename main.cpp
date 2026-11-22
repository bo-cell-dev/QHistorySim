#include <QApplication>
#include "mainpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainPage w;
    w.showMaximized();
    return a.exec();
}
