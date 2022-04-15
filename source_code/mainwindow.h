#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql>
#include <QDebug>
#include <QFileInfo>
#include "signup_page.h"
#include "homescreen.h"
#include "connection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SignUpButton_clicked();
    void on_button_login_clicked();

private:
    Ui::MainWindow *ui;
    signup_page *signup;
    homescreen *home;

};
#endif // MAINWINDOW_H
