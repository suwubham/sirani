#include "signup_page.h"
#include "ui_signup_page.h"

signup_page::signup_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup_page)
{
    ui->setupUi(this);
}

signup_page::~signup_page()
{
    delete ui;
}
