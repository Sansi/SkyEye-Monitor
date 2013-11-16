#include "sqlexample.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SQLExample w;
    w.show();

    return a.exec();
}
