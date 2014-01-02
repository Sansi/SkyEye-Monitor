#include "sqlexample.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    SQLExample w;
    w.show();

    if (QSqlDatabase::connectionNames().isEmpty()) {
        QMetaObject::invokeMethod(&w, "connectDatabase", Qt::QueuedConnection);
    }

    return a.exec();
}
