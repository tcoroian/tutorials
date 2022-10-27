//#include "mainwindow.h"
#include "alternativewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlternativeWindow w;
    w.show();
    return a.exec();
}
