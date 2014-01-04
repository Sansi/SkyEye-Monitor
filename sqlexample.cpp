#include "sqlexample.h"
#include "ui_sqlexample.h"
#include <QtSql>
#include <QDebug>
#include <QtWidgets>
#include <QJsonDocument>

SQLExample::SQLExample(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SQLExample) {
    ui->setupUi(this);
    statusModel = new QSqlQueryModel;
    eventModel = new QSqlQueryModel;
    readConfig();
}

SQLExample::~SQLExample() {
    delete ui;
}

void SQLExample::changeEvent(QEvent* e) {
    QWidget::changeEvent(e);

    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;

    default:
        break;
    }
}

void SQLExample::readConfig() {
    QFile jsonFile("config.json");

    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->statusLabel->setText("Unable to open config file!");
        return;
    }

    QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();
    QJsonParseError* err = new QJsonParseError();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, err);

    if (err->error != 0) {
        qDebug() << err->errorString();
    }

    if (doc.isNull()) {
        ui->statusLabel->setText("Invalid config file format!");
        return;
    }
    else if (doc.isObject()) {
        QJsonObject jObject = doc.object();
        QVariantMap config = jObject.toVariantMap();
        dbmstype = config["dbmstype"].toString();
        hostname = config["hostname"].toString();
        database = config["database"].toString();
        username = config["username"].toString();
        password = config["password"].toString();
        listQuery = config["list_query"].toString();
        infoQuery = config["info_query"].toString();
        headers = config["info_headers"].toStringList();
        playlistQuery = config["playlist_query"].toString();
        statusQuery = config["status_query"].toString();
        eventQuery = config["event_query"].toString();
    }
}

void SQLExample::connectDatabase() {
    db = new QSqlDatabase(QSqlDatabase::addDatabase(dbmstype));
    db->setHostName(hostname);
    db->setDatabaseName(database);
    db->setUserName(username);
    db->setPassword(password);

    if (!db->open()) {
        ui->statusLabel->setText("Failed to connect to database");
    }
    else {
        ui->statusLabel->setText("Database connection OK");
    }

    refresh();
}

void SQLExample::refresh() {
    ui->deviceList->clear();
    QSqlQuery query(*db);
    // If you iterate through the result set only using next() and seek() with
    // positive values, the following call before exec() will speed up the query
    // significantly when operating on large result sets.
    query.setForwardOnly(true);
    query.exec(listQuery);

    while (query.next()) {
        QString id = query.value(0).toString();
        QString state = query.value(1).toString();
        QListWidgetItem* item = new QListWidgetItem(ui->deviceList);
        item->setText(id + ", " + state);
    }

    ui->deviceList->doItemsLayout();
}

void SQLExample::showInfo() {
    ui->deviceInfo->clear();
    QSqlQuery query(*db);
    QString query_stmt;
    QTextStream(&query_stmt) << infoQuery << "'" <<
                               ui->deviceList->currentItem()->text() <<
                               "'";
    query.exec(query_stmt);

    if (query.lastError().isValid()) {
        ui->statusLabel->setText(query.lastError().text());
    }

    if (query.first()) {
        for (int i = 0; i < headers.size(); i++) {
            ui->deviceInfo->insertPlainText(
                headers.at(i) +
                ":\t" +
                query.value(i).toString() +
                "\n");
        }
    }

    query_stmt.clear();
    QTextStream(&query_stmt) << playlistQuery << "'" <<
                               ui->deviceList->currentItem()->text() <<
                               "'";

    query.exec(query_stmt);

    if (query.lastError().isValid()) {
        ui->statusLabel->setText(query.lastError().text());
    }

    if (query.first()) {
        ui->devicePlaylist->setText(query.value(0).toString());
    }
}

void SQLExample::showStatus() {
    QString query_stmt;
    QTextStream(&query_stmt) << statusQuery << "'" <<
                               ui->deviceList->currentItem()->text() <<
                               "'";
    statusModel->setQuery(query_stmt);

    if (statusModel->lastError().isValid()) {
        ui->statusLabel->setText(statusModel->lastError().text());
    }

    statusModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Type"));
    statusModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Attribute"));
    statusModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Value"));
    statusModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Error"));
    ui->deviceStatus->setModel(statusModel);
    ui->deviceStatus->resizeColumnsToContents();
}

void SQLExample::showEvent() {
    QString query_stmt;
    QTextStream(&query_stmt) << eventQuery << "'" <<
                               ui->deviceList->currentItem()->text() <<
                               "'";
    eventModel->setQuery(query_stmt);

    if (eventModel->lastError().isValid()) {
        ui->statusLabel->setText(eventModel->lastError().text());
    }

    eventModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Timestamp"));
    eventModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    eventModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Attribute"));
    eventModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Value"));
    ui->deviceEvent->setModel(eventModel);
    ui->deviceEvent->resizeColumnsToContents();
}

void SQLExample::on_deviceList_itemSelectionChanged() {
    showInfo();
    showStatus();
    showEvent();
}

void SQLExample::on_refreshButton_clicked()
{
    refresh();
}
