#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QMainWindow>
#include<QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QBarSet>
#include <QBarSeries>
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
    QString current_mood;
    QString mood_resource;
    ~homescreen();

private slots:
    void showsleep_dashboard();

    void showsleep_sleeptracker();

    void showmood_moodtracker();

    void showmood_dashboard();

    void Date_Time();

    void on_MoodTrackerButton_clicked();

    void on_DashBoardButton_clicked();

    void on_ResourcesButton_clicked();

    void on_GoalsButton_clicked();

    void on_SleepTrackerButton_clicked();

    void on_SleepTrackerSubmitButton_clicked();

    void on_SleepTrackerRemoveAllDataButton_clicked();

    void on_HappyButton_clicked();

    void on_CalmButton_clicked();

    void on_GoalsSubmitButton_clicked();

    void on_SadButton_clicked();

    void on_AngryButton_clicked();

    void on_YearlyGoalsTable_doubleClicked(const QModelIndex &index);

    void on_MonthlyGoalsTable_doubleClicked(const QModelIndex &index);

    void on_WeeklyGoalsTable_doubleClicked(const QModelIndex &index);

    void on_DailyGoalsTable_doubleClicked(const QModelIndex &index);



    void on_LogoutButton_clicked();

    void on_testbutton_clicked();

private:
    Ui::homescreen *ui;
};

#endif // HOMESCREEN_H
