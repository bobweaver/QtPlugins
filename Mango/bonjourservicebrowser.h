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

#ifndef BONJOURSERVICEBROWSER_H
#define BONJOURSERVICEBROWSER_H

#include <QObject>
#include <dns_sd.h>
#include "bonjourrecord.h"

class QSocketNotifier;
class BonjourServiceBrowser : public QObject
{
    Q_OBJECT
public:
    BonjourServiceBrowser(QObject *parent = 0);
    ~BonjourServiceBrowser();
    void browseForServiceType(const QString &serviceType);

    inline QList<BonjourRecord> currentRecords() const { return bonjourRecords; }
    inline QString serviceType() const { return browsingType; }

signals:
    void currentBonjourRecordsChanged(const QList<BonjourRecord> &list);
    void error(DNSServiceErrorType err);

private slots:
    void bonjourSocketReadyRead();

private:
    static void DNSSD_API bonjourBrowseReply(DNSServiceRef , DNSServiceFlags flags, quint32,
                                   DNSServiceErrorType errorCode, const char *serviceName,
                                   const char *regType, const char *replyDomain, void *context);
    DNSServiceRef dnssref;
    QSocketNotifier *bonjourSocket;
    QList<BonjourRecord> bonjourRecords;
    QString browsingType;
};

#endif // BONJOURSERVICEBROWSER_H
