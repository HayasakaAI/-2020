#include "mainwindow.h"
#include <QApplication>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("格式转换小助手");
    w.setFixedSize(1024,760);
    w.show();
    return a.exec();
}
