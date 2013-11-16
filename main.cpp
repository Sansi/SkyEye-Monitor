#include "sqlexample.h"
#include "sqltool.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SQLExample w;
    w.show();

    SQLTool st;
    st.connectDatabase();

    qDebug() << st.db->tables();

    return a.exec();
}
