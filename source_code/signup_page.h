#ifndef SIGNUP_PAGE_H
#define SIGNUP_PAGE_H

#include <QDialog>

#include<QtSql>
#include <QDebug>
#include <QFileInfo>
#include "connection.h"

namespace Ui {
class signup_page;
}

class signup_page : public QDialog
{
    Q_OBJECT

public:
    explicit signup_page(QWidget *parent = nullptr);
    ~signup_page();

private slots:
    void on_button_signup_clicked();



private:
    Ui::signup_page *ui;
};

#endif // SIGNUP_PAGE_H
