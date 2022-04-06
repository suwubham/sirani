#include "homescreen.h"
#include "ui_homescreen.h"
#include<QTimer>
#include<QDateTime>
#include<QMessageBox>

homescreen::homescreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::homescreen)
{
    ui->setupUi(this);
    QTimer *datetime = new QTimer(this);
    connect(datetime,SIGNAL(timeout()),this,SLOT(Date_Time()));
    datetime -> start();
}

void homescreen :: Date_Time()
{

    QDateTime clock = QDateTime::currentDateTime();
    QString clock_text=clock.toString("ddd MMMM yyyy \n\nh : m : ss ap");
    ui -> Clock -> setText(clock_text);
}

homescreen::~homescreen()
{
    delete ui;
}


void homescreen::on_pushButton_2_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(0);
}

void homescreen::on_pushButton_4_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(1);
}


void homescreen::on_pushButton_3_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(2);
}


void homescreen::on_pushButton_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(3);
}


void homescreen::on_pushButton_5_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
}
