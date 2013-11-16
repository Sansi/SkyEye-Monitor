#include "sqlexample.h"
#include "ui_sqlexample.h"

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
