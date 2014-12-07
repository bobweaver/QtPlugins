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


#ifndef BONJOURSERVICERESOLVER_H
#define BONJOURSERVICERESOLVER_H

#include <QtCore/QObject>


#include <dns_sd.h>

class QSocketNotifier;
class QHostInfo;
class BonjourRecord;

class BonjourServiceResolver : public QObject
{
    Q_OBJECT
public:
    BonjourServiceResolver(QObject *parent);
    ~BonjourServiceResolver();

    void resolveBonjourRecord(const BonjourRecord &record);
//    int bonjourPort;

signals:
    void bonjourRecordResolved(const QHostInfo &hostInfo, int port);
    void error(DNSServiceErrorType error);

private slots:
    void bonjourSocketReadyRead();
    void cleanupResolve();
    void finishConnect(const QHostInfo &hostInfo);

private:
    static void DNSSD_API bonjourResolveReply(DNSServiceRef sdRef, DNSServiceFlags flags,
                                    quint32 interfaceIndex, DNSServiceErrorType errorCode,
                                    const char *fullName, const char *hosttarget, quint16 port,
                                    quint16 txtLen, const char *txtRecord, void *context);
    DNSServiceRef dnssref;
    QSocketNotifier *bonjourSocket;
    int bonjourPort;
};

#endif // BONJOURSERVICERESOLVER_H
