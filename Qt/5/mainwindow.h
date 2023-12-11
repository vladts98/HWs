#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

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
    void on_pushButton_StartStop_clicked();
    void on_pushButton_ClearLap_clicked();

    void RcvSignalTime();
    void RcvSignalClear();
    void RcvSignalLap();
private:
    Ui::MainWindow *ui;
    StopWatch* sw;
};
#endif // MAINWINDOW_H
