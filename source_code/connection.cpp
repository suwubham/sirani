#include "connection.h"
#include<QtSql>
#include <QDebug>
#include <QFileInfo>

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






