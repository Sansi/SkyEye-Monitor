#include "sqltool.h"
#include <QSqlDatabase>
#include <QDebug>

SQLTool::SQLTool()
{
}

void SQLTool::connectDatabase()
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    db->setHostName("202.11.20.186");
    db->setDatabaseName("skyeye_db");
    db->setUserName("skyeye_admin");
    db->setPassword("skyeye@sansi.com");

    if (!db->open())
          qDebug() << "Failed to connect to database";
       else
        qDebug() << "Database connection OK";
}
