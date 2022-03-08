#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase auth=QSqlDatabase::addDatabase("QSQLITE");
    auth.setDatabaseName("D:/Bachelors/1st Year/Y1S2/semester project/logindetails.db");
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


void MainWindow::on_button_login_clicked()
{
    QString email, password;
    email = ui -> lineEdit -> text();
    password = ui -> lineEdit_2 -> text();

    QSqlQuery qry;
    if (qry.exec("select * from login where email='"+email+"' and password='"+password+"'")){
        int count = 0;
        while (qry.next()){
            count = count + 1;
        }
        if (count == 1){
            ui -> label_3 -> setText("wow");
            home = new homescreen(this);
            home -> show();
        }
        else{
            QMessageBox::information(this,"Message","Invalid email or password",QMessageBox::Ok);
        }
    }


}

