#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tb_main->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tb_main->verticalHeader()->setVisible(false);
    ui->groupBox->setEnabled(false);
    
    ui->lb_status->setText("Отключено от БД");
    ui->lb_status->setStyleSheet("color:red");
    
    ui->statusbar->addWidget(ui->lb_status);
    ui->rb_arrival->setChecked(true);
    ui->centralwidget->setWindowTitle("Расписание");

    dataBase = new DataBase(this);
    msgBox = new QMessageBox(this);
    statistic = nullptr;
    connectOnce = false;

    tmr = new QTimer();
    tmr->setInterval(100);
    connect(tmr, &QTimer::timeout, this, &MainWindow::RunConnectionToDB);
    time_start = QDateTime::currentDateTime();
    tmr->start();

    connect(dataBase, &DataBase::sig_SendStatusConnection, this, &MainWindow::RcvSignalSendStatusConnectionToDB);
    connect(dataBase, &DataBase::sig_SendListAirports, this, &MainWindow::RcvSignalSendListAirports);
    connect(dataBase, &DataBase::sig_SendQueryFromDB, this, &MainWindow::RcvSignalSendQueryFromDB);

    connect(dataBase, &DataBase::sig_SendDataPerYear, this, &MainWindow::RcvSignalSendDataPerYear);
    connect(dataBase, &DataBase::sig_SendDataPerMonth, this, &MainWindow::RcvSignalSendDataPerMonth);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tmr;
    delete dataBase;
    delete msgBox;
}

void MainWindow::RunConnectionToDB()
{
    if (!dataBase->getStatusConnection())
    {
        auto t = time_start.secsTo(QDateTime::currentDateTime());
        if (t > 5)
        {
            msgBox->setIcon(QMessageBox::Critical);
            msgBox->setText(dataBase->getLastError().text());
            msgBox->exec();
            time_start = QDateTime::currentDateTime();
        }
        dataBase->connectToDB();
    }
    if (dataBase->getStatusConnection() & !connectOnce)
    {
        dataBase->getAirportList();
        connectOnce = true;
    }
}

void MainWindow::RcvSignalSendStatusConnectionToDB()
{
    if (dataBase->getStatusConnection())
    {
        ui->lb_status->setText("Подключено к БД");
        ui->lb_status->setStyleSheet("color:green");
        ui->statusbar->addWidget(ui->lb_status);
        ui->groupBox->setEnabled(true);
    }
    else
    {
        ui->lb_status->setText("Отключено от БД");
        ui->lb_status->setStyleSheet("color:red");
        ui->statusbar->addWidget(ui->lb_status);
        ui->groupBox->setEnabled(false);
    }
}

void MainWindow::RcvSignalSendListAirports(QSqlQueryModel *model)
{
    for(int i = 0; i < model->rowCount(); ++i)
    {
        ui->cb_airports->addItem(model->data(model->index(i,0)).toString());
        airports[model->data(model->index(i,0)).toString()] = model->data(model->index(i,1)).toString();
    }
}

void MainWindow::on_pb_getList_clicked()
{
    QString airportCode = airports[ui->cb_airports->currentText()];
    QString date = ui->de_date->text();
    if(ui->rb_arrival->isChecked())
        dataBase->getDataArrivals(airportCode, date);
    else if(ui->rb_departure->isChecked())
        dataBase->getDataDepartures(airportCode, date);
}

void MainWindow::RcvSignalSendQueryFromDB(QSqlQueryModel *model)
{
    ui->tb_main->setModel(model);
}

void MainWindow::on_pb_showLoad_clicked()
{
    statistic = new Statistic();
    //создал указатель -> должен удалить
    //удаляю при закрытии(149), возникает ошибка (деструктор 2 раза вызывается как в интернете написано)
    //
    connect(statistic, &Statistic::sig_CloseStatistic, this,  &MainWindow::RcvSignalCloseStatistic);

    QString airportCode = ui->cb_airports->currentText() +
            " (" + airports[ui->cb_airports->currentText()] + ")";
    statistic->setAirport(airportCode);

    if(dataBase->getDataPerYear(airports[ui->cb_airports->currentText()]) &
    dataBase->getDataPerMonth(airports[ui->cb_airports->currentText()]))
    {
        ui->centralwidget->setEnabled(false);
        statistic->show();
    }
}

void MainWindow::RcvSignalSendDataPerYear(QSqlQueryModel *model)
{
    QVector<double> data;
    for(int i = 0; i < model->rowCount(); ++i)
        data.append(model->data(model->index(i,0)).toDouble());
    statistic->setDataPerYear(data);
}

void MainWindow::RcvSignalSendDataPerMonth(QSqlQueryModel *model)
{
    QMultiMap<int, double> data;
    for(int i = 0; i < model->rowCount(); ++i)
        data.insert(model->data(model->index(i,1)).toInt(), model->data(model->index(i,0)).toDouble());
    statistic->setDataPerMonth(data);
}

void MainWindow::RcvSignalCloseStatistic()
{
    statistic->close();
    ui->centralwidget->setEnabled(true);
    //delete statistic;
}



