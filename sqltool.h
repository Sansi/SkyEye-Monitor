#ifndef SQLTOOL_H
#define SQLTOOL_H

#include <QSqlDatabase>

class SQLTool
{
public:
    SQLTool();
    void connectDatabase();
    void test();
//    QSqlDatabase *db;
private:
};

#endif // SQLTOOL_H
