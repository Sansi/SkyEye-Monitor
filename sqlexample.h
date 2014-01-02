#ifndef SQLEXAMPLE_H
#define SQLEXAMPLE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QtSql>

QT_FORWARD_DECLARE_CLASS(QTreeWidget)
QT_FORWARD_DECLARE_CLASS(QTreeWidgetItem)
QT_FORWARD_DECLARE_CLASS(QSqlDatabase)
QT_FORWARD_DECLARE_CLASS(QMenu)

namespace Ui {
class SQLExample;
}

class SQLExample : public QWidget {
    Q_OBJECT

  public:
    explicit SQLExample(QWidget* parent = 0);
    ~SQLExample();

  public slots:
    void connectDatabase();
    void currentChanged() {}
    void refresh();
    void showInfo();
    void showStatus();
    void showEvent();

  protected:
    void changeEvent(QEvent* e);

  signals:
    void statusMessage(const QString& message);

  private slots:
    void on_deviceList_itemSelectionChanged();
    void readConfig();

  private:
    Ui::SQLExample* ui;
    QSqlDatabase* db;
    QString dbmstype;
    QString hostname;
    QString database;
    QString username;
    QString password;
    QSqlQueryModel* statusModel;
    QSqlQueryModel* eventModel;
    QString listQuery;
    QString infoQuery;
    QStringList headers;
    QString playlistQuery;
    QString statusQuery;
    QString eventQuery;
};

#endif // SQLEXAMPLE_H
