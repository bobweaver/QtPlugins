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
#ifndef SQLQUERY_H
#define SQLQUERY_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QVariant>

class SqlQuery : public QObject
       {
     Q_OBJECT
public:
    explicit SqlQuery(QObject *parent = 0);
    Q_PROPERTY(QString source READ source WRITE setSource )
    Q_PROPERTY(QString databaseName READ databaseName WRITE setdatabaseName)
    Q_PROPERTY(QString user READ user WRITE setUser)
    Q_PROPERTY(QString password READ password WRITE setPassword)
    Q_PROPERTY(QString  databaseType READ databaseType WRITE setdatabaseType)
    Q_PROPERTY(int port READ port WRITE setPort )
    Q_PROPERTY(bool connectAuto READ connectAuto WRITE setConnectionAuto)
    Q_PROPERTY( QString queryString READ queryString WRITE setQueryString)
    Q_PROPERTY(QString connectionName READ connectionName WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(QString currentConnection READ currentConnection)
    Q_PROPERTY(bool running READ running)


    QString source() const;
    void setSource(const QString &source);
    QString databaseName() const;
    void setdatabaseName(const QString &databaseName);
    QString user() const;
    void setUser(const QString &user);
    QString password() const;
    void setPassword(const QString &password);
    QString databaseType() const;
    void setdatabaseType(const QString &databaseType);
    int port() const;
    void setPort(int port);
    bool connectAuto()const;
    void  setConnectionAuto(bool &connectAuto);
    QString queryString() const;
    void setQueryString(const QString &queryString);
    QString connectionName() const;
    void setConnectionName(const QString &connectionName);

    QString currentConnection()const;


     bool running();

    Q_INVOKABLE void close(const QString &name);
    Q_INVOKABLE void connect();
    Q_INVOKABLE void createConnection();
    Q_INVOKABLE void runQuery(const QString &cmd);
    Q_INVOKABLE void getText(const QString &cmd);
    Q_INVOKABLE QString lastString();


signals:
    void connectionNameChanged();
    void running(bool);
private:
    QSqlDatabase db;
    QString getBack;
    QString m_Source;
    QString m_DbName;
    QString m_User;
    QString m_Password;
    QString m_databaseType;
    int m_Port;
    bool m_ConnectAuto;
    QString m_QueryString;
    QString m_ConnectionName;
    bool m_running;
    QString m_stringResults;
};
#endif //  // SQLQUERY_H
