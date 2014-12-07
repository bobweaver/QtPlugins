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
#ifndef DNSLOOKUP_H
#define DNSLOOKUP_H
#include <QDnsLookup>
#include <QObject>

class DnsLookUp : public QObject
{
    Q_OBJECT
public:
    explicit DnsLookUp(QObject *parent = 0);

    Q_INVOKABLE void start();
signals:
   void finished();

protected slots:
      void handleServers();

private:
    QDnsLookup m_dns;
};

#endif // DNSLOOKUP_H
