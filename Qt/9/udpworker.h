#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>


#define BIND_PORT 12345

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket( void );
    void ReadDatagram(QNetworkDatagram datagram);
    void SendDatagram(QByteArray data, const QString type); //можно ли как то внести в данные что за тип данных передается?


private slots:
    void readPendingDatagrams(void);

private:
    QUdpSocket* serviceUdpSocket;
    QString flag;

signals:
    void sig_sendTimeToGUI(QDateTime data);
    void sig_sendInfoToGUI(QString data, QString address);

};

#endif // UDPWORKER_H
