#ifndef STATISTIC_H
#define STATISTIC_H

#include <QDialog>
#include <QWidget>
#include <QCloseEvent>
#include "qcustomplot.h"
#include <QCloseEvent>
#include "qcustomplot.h"

namespace Ui {
class Statistic;
}

class Statistic : public QDialog
{
    Q_OBJECT

public:
    explicit Statistic(QWidget *parent = nullptr);
    virtual ~Statistic();
    void closeEvent(QCloseEvent* event) override;

    void setAirport(const QString &airport);
    void setDataPerYear(const QVector<double> data);
    void setDataPerMonth(const QMultiMap<int, double> data);
signals:
    void sig_CloseStatistic();
private:
    Ui::Statistic *ui;
    QMap<int, QString> months;
    QCPBars *bars;
    QMultiMap<int, double> dataMonth;
    void setStatisticsPerMonth(const int month = 1);

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);
};

#endif // STATISTIC_H
