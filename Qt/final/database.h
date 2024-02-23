#ifndef DB_H
#define DB_H

#include <QObject>
#include <QSqlDataBase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlQuery>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    virtual ~DataBase();

    bool getStatusConnection() {return dataBase->isOpen();};
    void connectToDB();
    void disconnectFromDB(QString nameDb);
    QSqlError getLastError(){return error;};

    void getAirportList();
    void getDataArrivals(const QString& airportCode, const QString& date);
    void getDataDepartures(const QString& airportCode, const QString& date);
    bool getDataPerYear(const QString &airportCode);
    bool getDataPerMonth(const QString &airportCode);
signals:
    void sig_SendStatusConnection();
    void sig_SendListAirports(QSqlQueryModel* model);
    void sig_SendQueryFromDB(QSqlQueryModel* model);
    void sig_SendDataPerYear(QSqlQueryModel* model);
    void sig_SendDataPerMonth(QSqlQueryModel* model);

private:
    QSqlDatabase* dataBase;
    bool connectingToDB;
    QSqlQueryModel* queryModel;
    QSqlError error;
    QString convertDate(const QString& date);
};

#endif // DB_H
