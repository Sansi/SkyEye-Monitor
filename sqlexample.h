#ifndef SQLEXAMPLE_H
#define SQLEXAMPLE_H

#include <QWidget>
#include <QSqlDatabase>

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
    void refresh();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SQLExample *ui;
    QSqlDatabase *db;
};

#endif // SQLEXAMPLE_H
