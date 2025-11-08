#include "Databse.h"

XamppDatabase::XamppDatabase(QObject *parent)
    : QObject{parent}
{
    // Initialize database connection using QMYSQL driver
    db = QSqlDatabase::addDatabase("QMYSQL");
}

XamppDatabase::~XamppDatabase()
{
    disconnectFromDatabase();
}

bool XamppDatabase::connectToDatabase(const QString &host,
                                      const QString &dbName,
                                      const QString &userName,
                                      const QString &password,
                                      int port)
{
    db.setHostName(host);
    db.setDatabaseName(dbName);
    db.setUserName(userName);
    db.setPassword(password);
    db.setPort(port);

    if (db.open()) {
        qDebug() << "✓ Database connection successful!";
        qDebug() << "  Database:" << dbName;
        qDebug() << "  Host:" << host << ":" << port;
        m_lastError.clear();
        emit connectionStatusChanged(true);
        return true;
    } else {
        m_lastError = db.lastError().text();
        qDebug() << "✗ Database connection failed:" << m_lastError;
        emit connectionStatusChanged(false);
        emit errorOccurred(m_lastError);
        return false;
    }
}

void XamppDatabase::disconnectFromDatabase()
{
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database disconnected";
        emit connectionStatusChanged(false);
    }
}

bool XamppDatabase::isConnected() const
{
    return db.isOpen();
}

QSqlQuery XamppDatabase::executeQuery(const QString &queryStr)
{
    QSqlQuery query(db);

    if (!query.exec(queryStr)) {
        m_lastError = query.lastError().text();
        qDebug() << "✗ Query execution failed:" << m_lastError;
        qDebug() << "  Query was:" << queryStr;
        emit errorOccurred(m_lastError);
    } else {
        qDebug() << "✓ Query executed successfully:" << queryStr;
        m_lastError.clear();
    }

    return query;
}

QString XamppDatabase::lastError() const
{
    return m_lastError;
}
