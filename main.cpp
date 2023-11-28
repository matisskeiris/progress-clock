#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    QFontDatabase::addApplicationFont(":/Lato-Bold.ttf");
    QFontDatabase::addApplicationFont(":/Lato-Regular.ttf");

    a.setFont(QFont("Lato"));
    w.setMinimumSize(QSize(400, 500));

    w.setStyleSheet("background-color: black; color: white;");

    w.show();

    return a.exec();
}
