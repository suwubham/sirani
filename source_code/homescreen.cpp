#include "homescreen.h"
#include "ui_homescreen.h"
#include<QTimer>
#include<QDateTime>
#include <QDebug>
#include<QMessageBox>

homescreen::homescreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::homescreen)
{
    connOpen();
    ui->setupUi(this);
    ui -> stackedWidget -> setCurrentIndex(0);
    QTimer *datetime = new QTimer(this);
    connect(datetime,SIGNAL(timeout()),this,SLOT(Date_Time()));
    datetime -> start();

    QSqlQuery qry;
    qry.prepare("select username from current_user");
    qry.exec();
    qry.next();
    current_user = qry.value(0).toString();
    QString wooo = "Welcome, " + current_user;
    ui -> label_6 -> setText(wooo);

    showsleep_dashboard();
    showmood_dashboard();
    ui -> comboBox -> addItem("Yearly");
    ui -> comboBox -> addItem("Monthly");
    ui -> comboBox -> addItem("Weekly");
    ui -> comboBox -> addItem("Daily");
}

void homescreen :: Date_Time()
{
    QDateTime clock = QDateTime::currentDateTime();
    QString clock_text=clock.toString("ddd - dd / MM / yyyy  \n\nh : m : ss ap");
    ui -> Clock -> setText(clock_text);
}

homescreen::~homescreen()
{
    QSqlQuery final;
    final.prepare("delete from current_user");
    final.exec();
    delete ui;
}

void homescreen :: showsleep_dashboard(){
    QSqlQuery qry1, qry2,qry3;
    QString sleep_table = current_user + "_sleep";

    qry2.prepare("select count(*) from '"+sleep_table+"'");
    qry2.exec();
    qry2.first();
    int noofrows = qry2.value(0).toInt();

    int offset = noofrows - 7;

    QLineSeries *series = new QLineSeries();
    int i;
    qry3.prepare("select * from '"+sleep_table+"' limit 7 offset :offsetvalue");
    qry3.bindValue(":offsetvalue",offset);
    int count = 0;
    if (qry3.exec()){
        while (qry3.next()){
            count = count + 1;
        }
    }

    qry1.prepare("select * from '"+sleep_table+"' limit 7 offset :offsetvalue");
    qry1.bindValue(":offsetvalue",offset);
    qry1.exec();

    for (i=0; i<count; i++){
        qry1.next();
        QStringList dates = qry1.value(0).toString().split(" ").mid(1,3);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(dates[2].toInt(), dates[1].toInt() , dates[0].toInt()));
        series -> append(momentInTime.toMSecsSinceEpoch(), qry1.value(1).toDouble());
    }

    QChart *chart = new QChart();
    chart -> addSeries(series);
    chart -> legend() -> hide();
    chart -> setTitle("Sleep record");
    chart -> setTheme(QChart::ChartThemeHighContrast);

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("dd MMM");
    axisX->setTitleText("Date");
    axisX->setTickCount(count);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setRange(1,10);
    axisY->setTickCount(10);
    axisY->setTitleText("Hours");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart -> setAnimationOptions(QChart::GridAxisAnimations);
    chart -> setAnimationOptions(QChart::SeriesAnimations);
    chart -> setAnimationEasingCurve(QEasingCurve::OutCubic);

    QChartView *chartView = new QChartView(chart);
    chartView -> setRenderHint(QPainter::Antialiasing);
    chartView -> setParent(ui->horizontalFrame);
}

void homescreen :: showsleep_sleeptracker(){
    QSqlQuery qry1, qry2,qry3;
    QString sleep_table = current_user + "_sleep";

    qry2.prepare("select count(*) from '"+sleep_table+"'");
    qry2.exec();
    qry2.first();
    int noofrows = qry2.value(0).toInt();

    int offset = noofrows - 7;

    QLineSeries *series = new QLineSeries();
    int i;
    qry3.prepare("select * from '"+sleep_table+"' limit 7 offset :offsetvalue");
    qry3.bindValue(":offsetvalue",offset);
    int count = 0;
    if (qry3.exec()){
        while (qry3.next()){
            count = count + 1;
        }
    }

    qry1.prepare("select * from '"+sleep_table+"' limit 7 offset :offsetvalue");
    qry1.bindValue(":offsetvalue",offset);
    qry1.exec();

    for (i=0; i<count; i++){
        qry1.next();
        QStringList dates = qry1.value(0).toString().split(" ").mid(1,3);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(dates[2].toInt(), dates[1].toInt() , dates[0].toInt()));
        series -> append(momentInTime.toMSecsSinceEpoch(), qry1.value(1).toDouble());
    }

    QChart *chart = new QChart();
    chart -> addSeries(series);
    chart -> legend() -> hide();
    chart -> setTitle("Sleep record");
    chart -> setTheme(QChart::ChartThemeHighContrast);

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("dd MMM");
    axisX->setTitleText("Date");
    axisX->setTickCount(count);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setRange(1,10);
    axisY->setTickCount(10);
    axisY->setTitleText("Hours");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart -> setAnimationOptions(QChart::GridAxisAnimations);
    chart -> setAnimationOptions(QChart::SeriesAnimations);
    chart -> setAnimationEasingCurve(QEasingCurve::OutCubic);

    QChartView *chartView = new QChartView(chart);
    chartView -> setRenderHint(QPainter::Antialiasing);
    chartView -> setParent(ui->horizontalFrame_1);
}

void homescreen :: showmood_moodtracker(){
    QSqlQuery qry;
    QString mood_table = current_user + "_mood";
    int happy,sad,calm,angry;
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Happy'");
    qry.exec();
    qry.next();
    happy = qry.value(0).toInt();
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Sad'");
    qry.exec();
    qry.next();
    sad = qry.value(0).toInt();
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Calm'");
    qry.exec();
    qry.next();
    calm = qry.value(0).toInt();
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Angry'");
    qry.exec();
    qry.next();
    angry = qry.value(0).toInt();

    QBarSet *set0 = new QBarSet("Happy");
    QBarSet *set1 = new QBarSet("Sad");
    QBarSet *set2 = new QBarSet("Calm");
    QBarSet *set3 = new QBarSet("Angry");

    *set0 << happy << 0 << 0 << 0;
    *set1 << 0 << sad << 0 << 0;
    *set2 << 0 << 0 << calm << 0;
    *set3 << 0 << 0 << 0 << angry ;

    QStackedBarSeries *series = new QStackedBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();
    chart -> addSeries(series);
    chart-> setTitle("Mood frequency");
    chart -> setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Happy" << "Sad" << "Calm" << "Angry";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    QChartView *chartView = new QChartView(chart);
    chartView -> setParent(ui->horizontalFrame_2);
}

void homescreen::on_pushButton_clicked()
{
    showmood_moodtracker();
    QSqlQuery qry;
    QString mood_table = current_user + "_mood";
    int happy,sad,calm,angry;
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Happy'");
    qry.exec();
    qry.next();
    happy = qry.value(0).toInt();
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Sad'");
    qry.exec();
    qry.next();
    sad = qry.value(0).toInt();
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Calm'");
    qry.exec();
    qry.next();
    calm = qry.value(0).toInt();
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Angry'");
    qry.exec();
    qry.next();
    angry = qry.value(0).toInt();
    ui -> stackedWidget -> setCurrentIndex(2);

    if(happy>sad && happy>calm && happy>angry){
        current_mood = "Happy";
    }

    else if(sad>happy && sad>calm && sad>angry){
        current_mood = "Sad";
    }

    else if(calm>sad && happy<calm && calm>angry){
        current_mood = "Calm";
    }

    else if(angry>sad && angry>calm && happy<angry){
        current_mood = "Angry";
    }

    else{
        current_mood = "Mixed Feelings";
    }

    ui -> label_9 -> setText(current_mood);


}

void homescreen::on_pushButton_2_clicked()
{
    showsleep_dashboard();
    showmood_dashboard();
    ui -> stackedWidget -> setCurrentIndex(0);
}

void homescreen::on_pushButton_4_clicked()
{
    //here
    QString goal_table = current_user + "_goal";

    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();
    qry -> prepare("select date,goal from '"+goal_table+"' where type = 'Yearly';");
    qry -> exec();
    modal -> setQuery(*qry);
    ui -> tableView_2 -> setModel(modal);
    ui -> tableView_2 -> resizeColumnsToContents();
    ui -> tableView_2 -> resizeRowsToContents();

    QSqlQueryModel *modal1 = new QSqlQueryModel();
    QSqlQuery *qry1 = new QSqlQuery();
    qry1 -> prepare("select date,goal from '"+goal_table+"' where type = 'Weekly';");
    qry1 -> exec();
    modal1 -> setQuery(*qry1);
    ui -> tableView_4 -> setModel(modal1);
    ui -> tableView_4 -> resizeColumnsToContents();
    ui -> tableView_4 -> resizeRowsToContents();

    QSqlQueryModel *modal2 = new QSqlQueryModel();
    QSqlQuery *qry2 = new QSqlQuery();
    qry2 -> prepare("select date,goal from '"+goal_table+"' where type = 'Monthly';");
    qry2 -> exec();
    modal2 -> setQuery(*qry2);
    ui -> tableView_3 -> setModel(modal2);
    ui -> tableView_3 -> resizeColumnsToContents();
    ui -> tableView_3 -> resizeRowsToContents();

    QSqlQueryModel *modal3 = new QSqlQueryModel();
    QSqlQuery *qry3 = new QSqlQuery();
    qry3 -> prepare("select date,goal from '"+goal_table+"' where type = 'Daily';");
    qry3 -> exec();
    modal3 -> setQuery(*qry3);
    ui -> tableView_5 -> setModel(modal3);
    ui -> tableView_5 -> resizeColumnsToContents();
    ui -> tableView_5 -> resizeRowsToContents();

    ui -> stackedWidget -> setCurrentIndex(1);
}

void homescreen::on_pushButton_3_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
}

void homescreen::on_pushButton_5_clicked()
{
    showsleep_sleeptracker();
    QString sleep_table = current_user + "_sleep";
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();
    qry -> prepare("select * from '"+sleep_table+"' ");
    qry -> exec();
    modal -> setQuery(*qry);
    ui -> tableView -> setModel(modal);
    ui -> tableView -> resizeColumnsToContents();
    ui -> tableView -> resizeRowsToContents();
    ui -> stackedWidget -> setCurrentIndex(3);
}

void homescreen::on_pushButton_6_clicked()
{
    QString sleep_table = current_user + "_sleep";
    QSqlQuery qry1,qry2;
    int hours = ui -> lineEdit -> text().toInt();
    QDateTime clock = QDateTime::currentDateTime();
    clock = clock.addDays(-1);
    QString clock_text=clock.toString("ddd dd MM yyyy h m ss ap");
    qry1.prepare("INSERT INTO '"+sleep_table+"' (date, hours) "
                 "VALUES (:dates, :hour)");
    qry1.bindValue(":dates", clock_text);
    qry1.bindValue(":hour", hours);
    qry1.exec();
    on_pushButton_5_clicked();
}

void homescreen::on_pushButton_7_clicked()
{
    QSqlQuery qry5;
    QString sleep_table = current_user + "_sleep";
    qry5.prepare("delete from '"+sleep_table+"'");
    qry5.exec();
    on_pushButton_5_clicked();
    on_pushButton_5_clicked();
}

void homescreen::on_pushButton_8_clicked()
{
    showmood_moodtracker();
    QString mood_table = current_user + "_mood";
    QString current_date, last_date;
    QStringList lastdatelist;
    QSqlQuery qry1,qry2;
    QDateTime clock = QDateTime::currentDateTime();
    QString clock_text=clock.toString("ddd dd MM yyyy h m ss ap");
    current_date = clock.toString("ddMMyyyy");


    qry2.prepare("SELECT * FROM '"+mood_table+"' ORDER BY date DESC LIMIT 1");
    qry2.exec();
    qry2.next();

    lastdatelist =  qry2.value(0).toString().split(" ").mid(1,3);
    last_date = lastdatelist[0] + lastdatelist[1] + lastdatelist[2];

    qDebug() << lastdatelist << last_date << current_date;

    if (current_date != last_date){
    qry1.prepare("INSERT INTO '"+mood_table+"' (date, mood) "
                 "VALUES (:dates, :mood)");
    qry1.bindValue(":dates", clock_text);
    qry1.bindValue(":mood", "Happy");
    qry1.next();
    qry1.exec();
    }
    else{
        QMessageBox::information(this,"Message","fk u",QMessageBox::Ok);
    }
    on_pushButton_clicked();
    showmood_moodtracker();
}

void homescreen::on_pushButton_9_clicked()
{
    QString mood_table = current_user + "_mood";
    QSqlQuery qry1;
    QDateTime clock = QDateTime::currentDateTime();
    QString clock_text=clock.toString("ddd dd MM yyyy h m ss ap");
    qry1.prepare("INSERT INTO '"+mood_table+"' (date, mood) "
                 "VALUES (:dates, :mood)");
    qry1.bindValue(":dates", clock_text);
    qry1.bindValue(":mood", "Calm");
    qry1.exec();
    on_pushButton_clicked();
}

void homescreen :: showmood_dashboard(){
    showmood_moodtracker();
    QSqlQuery qry;
    QString mood_table = current_user + "_mood";
    int happy,sad,calm,angry;
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Happy'");
    qry.exec();
    qry.next();
    happy = qry.value(0).toInt();
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Sad'");
    qry.exec();
    qry.next();
    sad = qry.value(0).toInt();
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Calm'");
    qry.exec();
    qry.next();
    calm = qry.value(0).toInt();
    qry.prepare("select count(*) from '"+mood_table+"' where mood = 'Angry'");
    qry.exec();
    qry.next();
    angry = qry.value(0).toInt();

    QBarSet *set0 = new QBarSet("Happy");
    QBarSet *set1 = new QBarSet("Sad");
    QBarSet *set2 = new QBarSet("Calm");
    QBarSet *set3 = new QBarSet("Angry");

    *set0 << happy << 0 << 0 << 0;
    *set1 << 0 << sad << 0 << 0;
    *set2 << 0 << 0 << calm << 0;
    *set3 << 0 << 0 << 0 << angry ;

    QStackedBarSeries *series = new QStackedBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();
    chart -> addSeries(series);
    chart-> setTitle("Mood frequency");
    chart -> setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Happy" << "Sad" << "Calm" << "Angry";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    QChartView *chartView = new QChartView(chart);
    chartView -> setParent(ui->horizontalFrame_4);
}

void homescreen::on_pushButton_10_clicked()
{
    QString goal_table = current_user + "_goal";
    QSqlQuery qry1;

    QString type = ui -> comboBox -> currentText();
    QString goal = ui -> lineEdit_2 -> text();
    QDateTime clock = QDateTime::currentDateTime();
    QString clock_text=clock.toString("ddd dd MM yyyy h m ss ap");
    qry1.prepare("INSERT INTO '"+goal_table+"' (date, type, goal) "
                 "VALUES (:dates, :types, :goals)");
    qry1.bindValue(":dates", clock_text);
    qry1.bindValue(":types", type);
    qry1.bindValue(":goals", goal);
    qry1.exec();
    on_pushButton_4_clicked();
}

void homescreen::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    QString goal_table = current_user + "_goal";
    QString val = ui -> tableView_2 -> model() -> data(index).toString();
    QSqlQuery qry;
    qry.prepare("delete from '"+goal_table+"' where goal = :value or date = :value or type = :value");
    qry.bindValue(":value",val);
    qry.exec();
    on_pushButton_4_clicked();
}


void homescreen::on_tableView_3_doubleClicked(const QModelIndex &index)
{
    QString goal_table = current_user + "_goal";
    QString val = ui -> tableView_3 -> model() -> data(index).toString();
    QSqlQuery qry;
    qry.prepare("delete from '"+goal_table+"' where goal = :value or date = :value or type = :value");
    qry.bindValue(":value",val);
    qry.exec();
    on_pushButton_4_clicked();
}



void homescreen::on_tableView_4_doubleClicked(const QModelIndex &index)
{
    QString goal_table = current_user + "_goal";
    QString val = ui -> tableView_4 -> model() -> data(index).toString();
    QSqlQuery qry;
    qry.prepare("delete from '"+goal_table+"' where goal = :value or date = :value or type = :value");
    qry.bindValue(":value",val);
    qry.exec();
    on_pushButton_4_clicked();
}


void homescreen::on_tableView_5_doubleClicked(const QModelIndex &index)
{
    QString goal_table = current_user + "_goal";
    QString val = ui -> tableView_5 -> model() -> data(index).toString();
    QSqlQuery qry;
    qry.prepare("delete from '"+goal_table+"' where goal = :value or date = :value or type = :value");
    qry.bindValue(":value",val);
    qry.exec();
    on_pushButton_4_clicked();
}


void homescreen::on_pushButton_11_clicked()
{
    QString mood_table = current_user + "_mood";
    QSqlQuery qry1;
    QDateTime clock = QDateTime::currentDateTime();
    QString clock_text=clock.toString("ddd dd MM yyyy h m ss ap");
    qry1.prepare("INSERT INTO '"+mood_table+"' (date, mood) "
                 "VALUES (:dates, :mood)");
    qry1.bindValue(":dates", clock_text);
    qry1.bindValue(":mood", "Sad");
    qry1.exec();
    on_pushButton_clicked();
}


void homescreen::on_pushButton_12_clicked()
{
    QString mood_table = current_user + "_mood";
    QSqlQuery qry1;
    QDateTime clock = QDateTime::currentDateTime();
    QString clock_text=clock.toString("ddd dd MM yyyy h m ss ap");
    qry1.prepare("INSERT INTO '"+mood_table+"' (date, mood) "
                 "VALUES (:dates, :mood)");
    qry1.bindValue(":dates", clock_text);
    qry1.bindValue(":mood", "Angry");
    qry1.exec();
    on_pushButton_clicked();
}

