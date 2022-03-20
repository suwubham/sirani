#include "homescreen.h"
#include "ui_homescreen.h"

homescreen::homescreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::homescreen)
{
    ui->setupUi(this);
}

homescreen::~homescreen()
{
    delete ui;
}

void homescreen::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void homescreen::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void homescreen::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}



void homescreen::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

