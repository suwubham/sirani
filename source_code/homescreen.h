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

    void showmood_moodtracker();

    void showmood_dashboard();

    void Date_Time();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();


    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_tableView_3_doubleClicked(const QModelIndex &index);

    void on_tableView_4_doubleClicked(const QModelIndex &index);

    void on_tableView_5_doubleClicked(const QModelIndex &index);

private:
    Ui::homescreen *ui;
};

#endif // HOMESCREEN_H
