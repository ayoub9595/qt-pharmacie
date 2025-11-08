#ifndef XAMPPDATABASE_H
#define XAMPPDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class XamppDatabase : public QObject
{
    Q_OBJECT
public:
    explicit XamppDatabase(QObject *parent = nullptr);
    ~XamppDatabase();

    // Connection management
    bool connectToDatabase(const QString &host = "localhost",
                           const QString &dbName = "your_database_name",
                           const QString &userName = "root",
                           const QString &password = "",
                           int port = 3306);

    void disconnectFromDatabase();
    bool isConnected() const;

    // Query execution
    QSqlQuery executeQuery(const QString &queryStr);
    QString lastError() const;

signals:
    void connectionStatusChanged(bool connected);
    void errorOccurred(const QString &error);

private:
    QSqlDatabase db;
    QString m_lastError;
};

#endif
