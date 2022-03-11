#include "signup_page.h"
#include "ui_signup_page.h"
#include <QMessageBox>
signup_page::signup_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup_page)
{
    ui->setupUi(this);
    if(!connOpen())
        ui->label_3->setText("Failed");
    else
        ui->label_3->setText("Connected");
}

signup_page::~signup_page()
{
    delete ui;
}

void signup_page::on_button_signup_clicked()
{
    User u1;
    u1.first_name = ui -> lineEdit_firstname -> text();
    u1.last_name = ui -> lineEdit_lastname -> text();
    u1.username = ui -> lineEdit_username -> text();
    u1.email = ui -> lineEdit_email -> text();
    u1.password = ui -> lineEdit_password -> text();
    connOpen();
    QSqlQuery qry,qry1;
    qry1.prepare("select * from userdetails where username='"+u1.username+"'");
    if (qry1.exec()){
        int count = 0;
        while (qry.next()){
            count = count + 1;
        }

        if (count == 0){
            qry.prepare("INSERT INTO userdetails (first_name, last_name, user_name,"
                        " email, password) VALUES (:fname, :lname, :username, :email, :password)");
            qry.bindValue(":fname", u1.first_name);
            qry.bindValue(":lname", u1.last_name);
            qry.bindValue(":username", u1.username);
            qry.bindValue(":email", u1.email);
            qry.bindValue(":password", u1.password);

            if (qry.exec()){
                QMessageBox::information(this,"Message","Signed Up Successfully",QMessageBox::Ok);
                connClose();
            }
        }
            else{
                QMessageBox::critical(this,"Message",tr("error::"),qry.lastError().text());
            }
    }
        else{
            connClose();
            QMessageBox::information(this,"Message","Username already taken",QMessageBox::Ok);
        }
}


