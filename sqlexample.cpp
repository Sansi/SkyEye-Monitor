#include "sqlexample.h"
#include "ui_sqlexample.h"
#include <QSqlDatabase>
#include <QDebug>

SQLExample::SQLExample(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SQLExample)
{
    ui->setupUi(this);
}

SQLExample::~SQLExample()
{
    delete ui;
}

void SQLExample::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SQLExample::connectDatabase()
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    db->setHostName("202.11.20.186");
    db->setDatabaseName("skyeye_db");
    db->setUserName("skyeye_admin");
    db->setPassword("skyeye@sansi.com");

    if (!db->open())
        qDebug() << "Failed to connect to database";
    else {
        qDebug() << "Database connection OK";
        qDebug() << db->databaseName();
        qDebug() << db->tables();
    }

    refresh();
}

static QString qDBCaption(const QSqlDatabase &db)
{
    QString dbCaption = db.driverName();
    dbCaption.append(QLatin1Char(':'));
    if (!db.userName().isEmpty())
        dbCaption.append(db.userName().append(QLatin1Char('@')));
    dbCaption.append(db.databaseName());
    return dbCaption;
}

void SQLExample::refresh()
{
    ui->dbTree->clear();
    QTreeWidgetItem *root = new QTreeWidgetItem(ui->dbTree);
    root->setText(0,qDBCaption(*db));
    if (db->isOpen()) {
        QStringList tables = db->tables();
        for (int t = 0; t < tables.count(); ++t) {
            QTreeWidgetItem *table = new QTreeWidgetItem(root);
            table->setText(0, tables.at(t));
        }
    }
    ui->dbTree->doItemsLayout();
}

