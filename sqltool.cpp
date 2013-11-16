#include "sqltool.h"
#include <QtSql>
#include <QDebug>

SQLTool::SQLTool()
{
}

void SQLTool::connectDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("202.11.20.186");
    db.setDatabaseName("skyeye_db");
    db.setUserName("skyeye_admin");
    db.setPassword("skyeye@sansi.com");

    if (!db.open())
          qDebug() << "Failed to connect to database";
       else
        qDebug() << "Database connection OK";
}

void SQLTool::test()
{
    QStringList connectionNames = QSqlDatabase::connectionNames();

    for (int i = 0; i < connectionNames.count(); ++i) {
        QSqlDatabase db = QSqlDatabase::database(connectionNames.at(i), false);
        qDebug() << db.databaseName();
        qDebug() << db.tables();
    }
}
