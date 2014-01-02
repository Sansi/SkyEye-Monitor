#include "sqlexample.h"
#include "ui_sqlexample.h"
#include <QtSql>
#include <QDebug>
#include <QtWidgets>
#include <QJsonDocument>

SQLExample::SQLExample(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SQLExample)
{
    ui->setupUi(this);
    statusModel = new QSqlQueryModel;
    eventModel = new QSqlQueryModel;
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
  QFile jsonFile("config.json");

  if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    ui->statusLabel->setText("Unable to open config file!");
    return;
  }

  QByteArray jsonData = jsonFile.readAll();
  jsonFile.close();
  QJsonParseError *err = new QJsonParseError();
  QJsonDocument doc = QJsonDocument::fromJson(jsonData, err);

  if (err->error != 0)
    qDebug() << err->errorString();

  if (doc.isNull())
  {
    ui->statusLabel->setText("Invalid config file format!");
    return;
  }
  else if (doc.isObject())
  {
    QJsonObject jObject = doc.object();
    QVariantMap config = jObject.toVariantMap();
    QString dbmstype = config["dbmstype"].toString();
    QString hostname = config["hostname"].toString();
    QString database = config["database"].toString();
    QString username = config["username"].toString();
    QString password = config["password"].toString();
    db = new QSqlDatabase(QSqlDatabase::addDatabase(dbmstype));
    db->setHostName(hostname);
    db->setDatabaseName(database);
    db->setUserName(username);
    db->setPassword(password);
  }
    if (!db->open())
        ui->statusLabel->setText("Failed to connect to database");
    else {
        ui->statusLabel->setText("Database connection OK");
    }

    refresh();
}

void SQLExample::refresh()
{
    ui->deviceList->clear();
    QSqlQuery query(*db);
    // If you iterate through the result set only using next() and seek() with positive values, the following call before exec() will speed up the query significantly when operating on large result sets.
    query.setForwardOnly(true);
    query.exec("SELECT id, last_connected  FROM device ORDER BY last_connected DESC");
    while (query.next()) {
      QString id = query.value(0).toString();
      QListWidgetItem *item = new QListWidgetItem(ui->deviceList);
      item->setText(id);
    }
    ui->deviceList->doItemsLayout();
}

void SQLExample::showInfo() {
  ui->deviceInfo->clear();
  QSqlQuery query(*db);
  query.exec("SELECT cell, name, latitude, longitude, width, height, device_state_id, last_connected, last_status, last_event, last_playlist FROM device WHERE id="+ui->deviceList->currentItem()->text());
  if (query.first()) {
    ui->deviceInfo->insertPlainText("Cellnumber:\t"+query.value(0).toString()+"\n");
    ui->deviceInfo->insertPlainText("Device name:\t"+query.value(1).toString()+"\n");
    ui->deviceInfo->insertPlainText("Device latitude:\t"+query.value(2).toString()+"\n");
    ui->deviceInfo->insertPlainText("Device longitude:\t"+query.value(3).toString()+"\n");
    ui->deviceInfo->insertPlainText("Width (in mm):\t"+query.value(4).toString()+"\n");
    ui->deviceInfo->insertPlainText("Height (in mm):\t"+query.value(5).toString()+"\n");
    ui->deviceInfo->insertPlainText("Device state:\t"+query.value(6).toString()+"\n");
    ui->deviceInfo->insertPlainText("Last connected at:\t"+query.value(7).toString()+"\n");
    ui->deviceInfo->insertPlainText("Last status at:\t"+query.value(8).toString()+"\n");
    ui->deviceInfo->insertPlainText("Last event at:\t"+query.value(9).toString()+"\n");
    ui->deviceInfo->insertPlainText("Last playlist at:\t"+query.value(10).toString()+"\n");
  }
}

void SQLExample::showStatus() {
  statusModel->setQuery("SELECT type, attr, value, error FROM status WHERE device_id="+ui->deviceList->currentItem()->text());
  if (statusModel->lastError().isValid())
    ui->statusLabel->setText(statusModel->lastError().text());
  statusModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Type"));
  statusModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Attribute"));
  statusModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Value"));
  statusModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Error"));
  ui->deviceStatus->setModel(statusModel);
}

void SQLExample::showEvent() {
  eventModel->setQuery("SELECT time, type, attr, value FROM event WHERE device_id="+ui->deviceList->currentItem()->text());
  if (eventModel->lastError().isValid())
    ui->statusLabel->setText(eventModel->lastError().text());
  eventModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Timestamp"));
  eventModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
  eventModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Attribute"));
  eventModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Value"));
  ui->deviceEvent->setModel(eventModel);
}

void SQLExample::on_deviceList_itemSelectionChanged()
{
  showInfo();
  showStatus();
  showEvent();
}
