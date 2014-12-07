/*
 * Copyright 2014 Joseph Mills.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Joseph Mills  <josephjamesmills@gmail.com>
 */
#ifndef MANGOSQLDATABASE_H
#define MANGOSQLDATABASE_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlIndex>
#include <QSqlRecord>

class MangoSqlDatabase : public QObject
{
    Q_OBJECT
public:
    MangoSqlDatabase();


//    //functions
//    void close();
//    bool commit();
//    QString	connectOptions(); const
//    QString	connectionName(); const
//    QString	databaseName(); const
//    QSqlDriver *	driver(); const
//    QString	driverName(); const
//    QSqlQuery	exec(const QString & query = QString()); const
//    QString	hostName(); const
//    bool isOpen(); const
//    bool isOpenError(); const
//    bool isValid(); const
//    QSqlError lastError(); const
//    QSql::NumericalPrecisionPolicy	numericalPrecisionPolicy() ;const
//    bool open();
//    bool open(const QString & user, const QString & password);
//    QString	password(); const
//    int	port(); const
//    QSqlIndex	primaryIndex(const QString & tablename); const
//    QSqlRecord	record(const QString & tablename); const
//    bool rollback();
//    void setConnectOptions(const QString & options = QString());
//    void setDatabaseName(const QString &name);
//    void setHostName(const QString &host);
//    void setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy precisionPolicy);
//    void setPassword(const QString &password);
//    void setPort(int port);
//    void setUserName(const QString &name);
//    QStringList	tables(QSql::TableType type = QSql::Tables); const
//    bool transaction();
//    QString	userName();const
//    QSqlDatabase &operator=(const QSqlDatabase &other);



//    // static public members


//    QSqlDatabase addDatabase(const QString &type, const QString &connectionName = QLatin1String(defaultConnection));
//    QSqlDatabase addDatabase(QSqlDriver *driver, const QString &connectionName = QLatin1String(defaultConnection));
//    QSqlDatabase cloneDatabase(const QSqlDatabase &other, const QString &connectionName);
//    QStringList	connectionNames();
//    bool contains(const QString &connectionName = QLatin1String(defaultConnection));
//    QSqlDatabase database(const QString &connectionName = QLatin1String(defaultConnection), bool open = true);
//    QStringList	drivers();
//    bool isDriverAvailable(const QString &name);
//    void registerSqlDriver(const QString &name, QSqlDriverCreatorBase *creator);
//    void removeDatabase(const QString &connectionName);


};

#endif // MANGOSQLDATABASE_H
