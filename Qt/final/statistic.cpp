#include "statistic.h"
#include "ui_statistic.h"

Statistic::Statistic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistic)
{
    ui->setupUi(this);
    months =
    {
        {1, "Январь"},
        {2, "Февраль"},
        {3, "Март"},
        {4, "Апрель"},
        {5, "Май"},
        {6, "Июнь"},
        {7, "Июль"},
        {8, "Август"},
        {9, "Сентябрь"},
        {10, "Октябрь"},
        {11, "Ноябрь"},
        {12, "Декабрь"}
    };
    for(const auto& [key, value] : months.asKeyValueRange())
        ui->comboBox->addItem(value);

    ui->tabWidget->setCurrentWidget(ui->tab);

    bars = new QCPBars(ui->widget->xAxis,
                       ui->widget->yAxis);

    this->setWindowTitle("Статистика");
}

Statistic::~Statistic()
{
    delete ui;
    delete bars;
}

void Statistic::setAirport(const QString &airport)
{
    ui->label->setText("Загруженность аэропорта " + airport);
}

void Statistic::setDataPerYear(const QVector<double> data)
{
    ui->widget->clearGraphs();

    QVector<double> ticks;
    QVector<QString> labels;
    for(const auto& [key, value] : months.asKeyValueRange())
    {
        ticks << key;
        labels << value;
    }
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->widget->xAxis->setTicker(textTicker);
    ui->widget->xAxis->setTickLabelRotation(60);
    ui->widget->xAxis->setSubTicks(false);
    ui->widget->xAxis->setTickLength(0, 4);
    ui->widget->xAxis->setLabel("Месяцы");
    ui->widget->xAxis->setRange(0, months.size() + 1);
    ui->widget->xAxis->grid()->setVisible(true);

    ui->widget->yAxis->setRange(0, *std::max_element(data.begin(), data.end()) + 1);
    ui->widget->yAxis->setPadding(5);
    ui->widget->yAxis->setLabel("Загруженность аэропорта за год");
    ui->widget->yAxis->grid()->setSubGridVisible(true);
    ui->widget->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->widget->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    bars->setData(ticks, data);
    ui->widget->replot();
}


void Statistic::setDataPerMonth(const QMultiMap<int, double> data)
{
    dataMonth = data;
    setStatisticsPerMonth();
}
void Statistic::setStatisticsPerMonth(const int month)
{
    ui->widget_2->clearGraphs();
    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setPen(QPen(Qt::blue));
    QVector<double> x, y;
    int it = 0;
    for (const auto& [key, value] : dataMonth.asKeyValueRange())
    {
        if (key == month)
        {
            ++it;
            y.append(value);
            x.append(it);
        }
    }
    ui->widget_2->graph(0)->setData(x, y);
    ui->widget_2->graph(0)->rescaleAxes();

    ui->widget_2->replot();
}

void Statistic::closeEvent(QCloseEvent *event)
{
    emit sig_CloseStatistic();
}

void Statistic::on_comboBox_currentTextChanged(const QString &arg1)
{
    for (const auto& [key, value] : months.asKeyValueRange())
    {
        if (arg1 == value)
            setStatisticsPerMonth(key);
    }
}

