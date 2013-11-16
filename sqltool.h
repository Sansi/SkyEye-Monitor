#ifndef SQLTOOL_H
#define SQLTOOL_H

#include <QSqlDatabase>

class SQLTool
{
public:
    SQLTool();
    void connectDatabase();
    QSqlDatabase *db;
private:
};

#endif // SQLTOOL_H
