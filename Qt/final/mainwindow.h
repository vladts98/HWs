#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtConcurrent>
#include <QMap>
#include <QTimer>
#include <QTime>
#include <QDateTime>

#include "database.h"
#include "statistic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    void RunConnectionToDB();
    void RcvSignalSendStatusConnectionToDB();
    void RcvSignalSendListAirports(QSqlQueryModel *model);
    void on_pb_getList_clicked();
    void RcvSignalSendQueryFromDB(QSqlQueryModel *model);
    void on_pb_showLoad_clicked();
    void RcvSignalSendDataPerYear(QSqlQueryModel *model);
    void RcvSignalSendDataPerMonth(QSqlQueryModel *model);
    void RcvSignalCloseStatistic();

private:
    Ui::MainWindow *ui;
    DataBase* dataBase;
    Statistic *statistic;
    QMessageBox *msgBox;
    QMap<QString, QString> airports;
    QTimer *tmr;
    QDateTime time_start;
    bool connectOnce;
};
#endif // MAINWINDOW_H
