#ifndef SQLEXAMPLE_H
#define SQLEXAMPLE_H

#include <QWidget>

namespace Ui {
class SQLExample;
}

class SQLExample : public QWidget
{
    Q_OBJECT

public:
    explicit SQLExample(QWidget *parent = 0);
    ~SQLExample();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SQLExample *ui;
};

#endif // SQLEXAMPLE_H
