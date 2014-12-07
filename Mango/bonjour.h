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
#ifndef BONJOURBACKEND_h
#define BONJOURBACKEND_h
#include <QString>
#include <QTcpSocket>
#include "bonjourrecord.h"
#include "bonjourrecord.h"

class BonjourServiceBrowser;
class BonjourServiceResolver;
class QHostInfo;

class BonjourBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString serviceName READ serviceName  WRITE setServiceName NOTIFY serviceNameChanged )
    Q_PROPERTY(QString registeredType READ registeredType)
    Q_PROPERTY(QString replyDomain READ replyDomain )

public:
    explicit BonjourBackend(QObject *parent = 0);

    QString registeredType()const;
    void setRegisteredType(const QString &registeredType);

    QString serviceName()const;
    void setServiceName(const QString &serviceName);

    QString replyDomain()const;
    void setReplyDomain(const QString &replyDomain);

    Q_INVOKABLE void runBackend();
//    Q_INVOKABLE QString getReplyDomain()const;

signals:
    void serviceNameChanged();
    void replyDomainChanged();
    void registeredTypeChanged();

public slots:
   void updateString(const QList<BonjourRecord> &list);

private:
    quint16 blockSize;
    BonjourServiceBrowser *bonjourBrowser;
    BonjourServiceResolver *bonjourResolver;
    QString m_replyDomain;
    QString m_ServiceName;
    QString m_registeredType;
    QString m_serviceName ;
};
#endif
