#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    QFontDatabase::addApplicationFont(":/RobotoCondensed.ttf");

    w.setFont(QFont("RobotoCondensed"));
    w.setMinimumSize(QSize(400, 500));

    w.setStyleSheet("background-color: black;");

    w.show();

    return a.exec();
}
