#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sw = new StopWatch(this);
    ui->pushButton_ClearLap->setText("Clear");
    ui->pushButton_StartStop->setText("Start");
    ui->label_Time->setText("0");

    connect(sw, &StopWatch::sig_Clear, this, &MainWindow::RcvSignalClear);
    connect(sw, &StopWatch::sig_Lap, this, &MainWindow::RcvSignalLap);
    connect(sw->getQTimer(), &QTimer::timeout, this, &MainWindow::RcvSignalTime);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sw;
}


void MainWindow::on_pushButton_StartStop_clicked()
{
   if(sw->isStart())
   {
       sw->Stop();
       ui->pushButton_StartStop->setText("Start");
       ui->pushButton_ClearLap->setText("Clear");
   }
   else
   {
       sw->Start();
       ui->pushButton_StartStop->setText("Stop");
       ui->pushButton_ClearLap->setText("Lap");
   }
}


void MainWindow::on_pushButton_ClearLap_clicked()
{
    if(sw->isStart())
        sw->Lap();
    else
        sw->Clear();
}

void MainWindow::RcvSignalClear()
{
    ui->label_Time->setText(QString::number(sw->getTime()) + " сек");
    ui->textBrowser_Lap->clear();
}

void MainWindow::RcvSignalLap()
{
    ui->textBrowser_Lap->append("Lap " + QString::number(sw->getNumLap())
                                + ", время: " + QString::number(sw->getLapTime()) + " сек");
}

void MainWindow::RcvSignalTime()
{
    if(sw->isStart())
        ui->label_Time->setText(QString::number(sw->getTime()) + " сек");

}
