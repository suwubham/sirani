#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase auth=QSqlDatabase::addDatabase("QSQLITE");
    auth.setDatabaseName("C:/Users/shubh/Desktop/logindetails.db");
    if(!auth.open())
        ui->label_3->setText("Failed");
    else
        ui->label_3->setText("Connected");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    signup = new signup_page(this);
    signup -> show();
}

