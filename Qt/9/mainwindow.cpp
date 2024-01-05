#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();
    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendInfoToGUI, this, &MainWindow::DisplayInfo);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend, "time");
        timer->start(TIMER_DELAY);

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}


void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));
}

void MainWindow::DisplayInfo(QString data, QString address)
{
    ui->te_result->append("Принято сообщение от " + address + ": " +
                          QString::number(data.size()) + " байт");
}


void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}

void MainWindow::on_pushButton_clicked()
{
    QString inText = ui->textEdit->toPlainText();
    QByteArray data;
    QDataStream outStr(&data, QIODevice::WriteOnly);
    outStr << inText;
    udpWorker->SendDatagram(data, "data");
}

