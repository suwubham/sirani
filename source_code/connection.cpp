#include "connection.h"
#include<QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QRegularExpression>
#include <stdio.h>
QSqlDatabase auth;

bool connOpen(){
    QSqlDatabase auth=QSqlDatabase::addDatabase("QSQLITE");
    auth.setDatabaseName("D:/Bachelors/1st Year/Y1S2/semester project/sirani/sirani.db");
    if(!auth.open()){
        qDebug()<<("Failed");
        return false;
    }
    else{
        qDebug()<<("Connected");
        return true;
    }
}

void connClose(){
    auth.close();
    auth.removeDatabase(QSqlDatabase::defaultConnection);
}

bool Email_check(QString email)
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

bool pw_check(QString pw)
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



