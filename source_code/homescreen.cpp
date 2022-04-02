#include "homescreen.h"
#include "ui_homescreen.h"
#include<QTimer>
#include<QDateTime>

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

    QTime clock = QTime::currentTime();
    QString clock_text=clock.toString("hh : mm : ss");
    ui -> Clock -> setText(clock_text);

    QDate date = QDate::currentDate();
    QString date_text=date.toString();
    ui -> Date -> setText(date_text);
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




