#include "signup_page.h"
#include "ui_signup_page.h"
#include <QMessageBox>
#include "connection.h"

signup_page::signup_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup_page)
{
    ui->setupUi(this);
    if(!connOpen())
        ui->DBConnStatus->setText("Failed");
    else
        ui->DBConnStatus->setText("Connected");
}

signup_page::~signup_page()
{
    delete ui;
}

bool User::Email_check(QString email)
{
    QRegularExpression regex ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if(!regex.match(email).hasMatch())
    {
        return true;
    }
    else{
        return false;
    }
}

bool User::pw_check(QString pw)
{
    QRegularExpression regex ("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$");
    if(!regex.match(pw).hasMatch())
    {
        return true;
    }
    else{
        return false;
    }
}


void signup_page::on_button_signup_clicked()
{
    User u1,u;
    u1.first_name = ui -> lineEdit_firstname -> text();
    u1.last_name = ui -> lineEdit_lastname -> text();
    u1.username = ui -> lineEdit_username -> text();
    u1.email = ui -> lineEdit_email -> text();
    u1.password = ui -> lineEdit_password -> text();
    connOpen();
    if (u.Email_check(u1.email))
    {
        QMessageBox::information(this,"Message","Invalid email",QMessageBox::Ok);
    }

    else if (u.pw_check(u1.password))
    {
        QMessageBox::information(this,"Message","Password must contain at least eight characters, at least one uppercase letter, "
                                                "one lowercase letter, one number and one special character",QMessageBox::Ok);
    }
    else
    {
    QSqlQuery qry,qry1,qry2;
    int count = 0;
    qry1.prepare("select * from userdetails where user_name='"+u1.username+"'");
    qry1.exec();
        while (qry1.next()){
            count = count + 1;
        }
        if (count != 0){
            connClose();
            QMessageBox::information(this,"Message","Username already taken",QMessageBox::Ok);
        }
        if (count == 0){
            qry.prepare("INSERT INTO userdetails (first_name, last_name, user_name,"
                        "email, password) VALUES (:fname, :lname, :username, :email, :password)");
            qry.bindValue(":fname", u1.first_name);
            qry.bindValue(":lname", u1.last_name);
            qry.bindValue(":username", u1.username);
            qry.bindValue(":email", u1.email);
            qry.bindValue(":password", u1.password);
            qry.exec();
            QMessageBox::information(this,"Message","Signed Up Successfully",QMessageBox::Ok);

            QString mood_tablename = u1.username + "_mood";
            QString sleep_tablename = u1.username + "_sleep";
            QString goal_tablename = u1.username + "_goal";
            qry2.prepare("CREATE TABLE '"+mood_tablename+"' (date INTEGER, mood text)");
            qry2.exec();
            qry2.prepare("CREATE TABLE '"+sleep_tablename+"' (date INTEGER, hours INTEGER)");
            qry2.exec();
            qry2.prepare("CREATE TABLE '"+goal_tablename+"' (date INTEGER, type text, goal text)");
            qry2.exec();
            connClose();
        }
    }
}

