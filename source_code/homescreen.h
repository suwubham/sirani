#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QMainWindow>
#include<QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include "connection.h"

namespace Ui {
class homescreen;
}

class homescreen : public QMainWindow
{
    Q_OBJECT

public:

    explicit homescreen(QWidget *parent = nullptr);
    QString current_user;
    ~homescreen();

private slots:
    void showsleep_dashboard();

    void showsleep_sleeptracker();

    void Date_Time();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::homescreen *ui;
};

#endif // HOMESCREEN_H
