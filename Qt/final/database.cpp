#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    dataBase = new QSqlDatabase();
    *dataBase = QSqlDatabase::addDatabase("QPSQL", "MyDB");
    queryModel = new QSqlQueryModel(this);
    connectingToDB = false;
}

DataBase::~DataBase()
{
    delete dataBase;
    delete queryModel;
}

void DataBase::connectToDB()
{
    if (!connectingToDB & !dataBase->isOpen())
    {
        connectingToDB = true;

        dataBase->setHostName("981757-ca08998.tmweb.ru");
        dataBase->setPort(5432);
        dataBase->setDatabaseName("demo");
        dataBase->setUserName("netology_usr_cpp");
        dataBase->setPassword("CppNeto3");
        dataBase->open();
        error = dataBase->lastError();

        connectingToDB = false;
    }
    emit sig_SendStatusConnection();
}

void DataBase::disconnectFromDB(QString nameDb)
{
    *dataBase = QSqlDatabase::database("MyDB");
    dataBase->close();
}

QString DataBase::convertDate(const QString &date)
{
    QString day, month, year;
    for(int i = 0; i < date.size(); ++i)
    {
        if(i < 2)
        {
            day+=date[i];
        }
        if(i > 2 && i < 5)
        {
            month+=date[i];
        }
        if(i > 5)
        {
            year+=date[i];
        }
    }
    QString resultStr = year + "-" + month + "-" + day;
    return resultStr;
}



void DataBase::getAirportList()
{
    QString request = "SELECT airport_name->>'ru' AS name, airport_code "
                      "FROM bookings.airports_data ORDER BY name";
    queryModel->setQuery(request, *dataBase);
    if(!queryModel->lastError().isValid())
    {
        emit sig_SendQueryFromDB(queryModel);
        emit sig_SendListAirports(queryModel);
    }
    else
        error = queryModel->lastError();
}

void DataBase::getDataArrivals(const QString& airportCode, const QString& date)
{
    QString parsedDate = convertDate(date);
    QString request = "SELECT flight_no, scheduled_arrival, ad.airport_name->>'ru' AS name "
                      "FROM bookings.flights f "
                      "JOIN bookings.airports_data ad on ad.airport_code = f.departure_airport "
                      "WHERE (f.arrival_airport  = '" + airportCode + "' AND f.scheduled_arrival::date = date('" + parsedDate + "')) "
                      "ORDER BY name";
    queryModel->setQuery(request, *dataBase);
    if(!queryModel->lastError().isValid())
        emit sig_SendQueryFromDB(queryModel);
    else
        error = queryModel->lastError();
}

void DataBase::getDataDepartures(const QString &airportCode, const QString& date)
{
    QString parsedDate = convertDate(date);
    QString request = "SELECT flight_no, scheduled_departure, ad.airport_name->>'ru' AS name "
                      "FROM bookings.flights f "
                      "JOIN bookings.airports_data ad on ad.airport_code = f.arrival_airport "
                      "WHERE (f.departure_airport  = '" + airportCode + "' AND f.scheduled_departure::date = date('" + parsedDate + "')) "
                      "ORDER BY name";
    queryModel->setQuery(request, *dataBase);
    if(!queryModel->lastError().isValid())
        emit sig_SendQueryFromDB(queryModel);
    else
        error = queryModel->lastError();
}


bool DataBase::getDataPerYear(const QString &airportCode)
{
    QString request = "SELECT count(flight_no), date_trunc('month', scheduled_departure) AS Month "
                      "FROM bookings.flights f "
                      "WHERE (scheduled_departure::date > date('2016-08-31') "
                      "AND scheduled_departure::date <= date('2017-08-31')) AND "
                      "(departure_airport = '" + airportCode + "' or arrival_airport = '" + airportCode + "') "
                      "GROUP BY Month";

    queryModel->setQuery(request, *dataBase);
    if(!queryModel->lastError().isValid())
    {
        emit sig_SendDataPerYear(queryModel);
        return true;
    }
    error = queryModel->lastError();
    return false;
}

bool DataBase::getDataPerMonth(const QString &airportCode)
{
    QString request = "SELECT count(flight_no), date_part('month', date_trunc('day', scheduled_departure)), date_trunc('day', scheduled_departure) AS Day "
                      "FROM bookings.flights f "
                      "WHERE (scheduled_departure::date > date('2016-08-31') "
                      "AND scheduled_departure::date <= date('2017-08-31')) AND "
                      "(departure_airport = '" + airportCode + "' or arrival_airport = '" + airportCode + "') "
                      "GROUP BY Day";

    queryModel->setQuery(request, *dataBase);
    if(!queryModel->lastError().isValid())
    {
        emit sig_SendDataPerMonth(queryModel);
        return true;
    }
    error = queryModel->lastError();
    return false;
}
