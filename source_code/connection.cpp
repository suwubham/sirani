#include "connection.h"
#include<QtSql>
#include <QDebug>
#include <QFileInfo>

QSqlDatabase auth;
bool connOpen(){
    QSqlDatabase auth=QSqlDatabase::addDatabase("QSQLITE");
    auth.setDatabaseName("C:/Users/shubh/Desktop/sirani/sirani.db");
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






