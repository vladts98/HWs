#include <QCoreApplication>
#include <QSqlDatabase>
#include <QTcpSocket>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QTcpSocket* s;

    return a.exec();
}
