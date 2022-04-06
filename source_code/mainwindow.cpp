#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!connOpen())
        ui->label_3->setText("Failed");
    else
        ui->label_3->setText("Connected");
}

MainWindow::~MainWindow()
{
    QSqlQuery final;
    final.prepare("delete from current_user");
    final.exec();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    signup = new signup_page(this);
    signup -> show();
}

void MainWindow::on_button_login_clicked()
{
    User u1;
    u1.username = ui -> lineEdit -> text();
    u1.password = ui -> lineEdit_2 -> text();
    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from userdetails where user_name='"+u1.username+"' and password='"+u1.password+"'");
    if (qry.exec()){
        int count = 0;
        while (qry.next()){
            count = count + 1;
        }
        if (count == 1){
            QSqlQuery qry3;
            qry3.prepare("INSERT INTO current_user (username) VALUES ('"+u1.username+"')");
            qry3.exec();
            connClose();
            home = new homescreen();
            home -> show();
            this -> hide();
        }
        else{
            connClose();
            QMessageBox::information(this,"Message","Invalid email or password",QMessageBox::Ok);
        }
    }
}
