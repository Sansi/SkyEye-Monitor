#ifndef SQLEXAMPLE_H
#define SQLEXAMPLE_H

#include <QWidget>
#include <QSqlDatabase>

QT_FORWARD_DECLARE_CLASS(QTreeWidget)
QT_FORWARD_DECLARE_CLASS(QTreeWidgetItem)
QT_FORWARD_DECLARE_CLASS(QSqlDatabase)
QT_FORWARD_DECLARE_CLASS(QMenu)

namespace Ui {
class SQLExample;
}

class SQLExample : public QWidget
{
    Q_OBJECT

public:
    explicit SQLExample(QWidget *parent = 0);
    ~SQLExample();

public slots:
    void connectDatabase();
    void currentChanged() {}
    void refresh();
    void showTable(const QString &t);

protected:
    void changeEvent(QEvent *e);

signals:
    void statusMessage(const QString &message);

private slots:
    void on_dbTree_itemActivated(QTreeWidgetItem *item, int column);

private:
    Ui::SQLExample *ui;
    QSqlDatabase *db;
};

#endif // SQLEXAMPLE_H
