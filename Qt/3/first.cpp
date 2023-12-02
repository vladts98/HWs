#include "first.h"
#include "ui_first.h"

First::First(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::First)
{
    ui->setupUi(this);
    mainwindow = new MainWindow(this);
}

First::~First()
{
    delete ui;
}

void First::on_pushButton_clicked()
{
    mainwindow->show();
}

