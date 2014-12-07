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
#include "dnslookup.h"
#include <QDebug>

/*!
 * \qmltype DnsLookUp
 * \inqmlmodule Mango 0.1
 * \ingroup Mango
 * \inherits Item
 * \since 5.3
 *  a Simple Qml plugin that is used to look up dns information about computers and other things that are on the network
 */
DnsLookUp::DnsLookUp(QObject *parent) :
    QObject(parent)
{
    connect(&m_dns,SIGNAL(finished()),this,SLOT(handleServers()));
}


/*!
 * \qmlsignal DnsLookUp::start()
 * 
 * used in QML to start to look up the domain and or tcp file.
 * FIXME add in Q_PROPERTY to set the tcp file 
 */
void DnsLookUp::start(){
      m_dns.setType(QDnsLookup::SRV);
      m_dns.setName("_workstation._tcp.localhost");
      m_dns.lookup();

}

/*!
 * \qmlsignal DnsLookUp::handleServers()
 * used for error checking and looking for ports
 */
void DnsLookUp::handleServers()
{
      if (m_dns.error() != QDnsLookup::NoError) {
            qWarning("DNS lookup failed");
            m_dns.deleteLater();
            return;
        }
        // Handle the results.
        foreach (const QDnsServiceRecord &record, m_dns.serviceRecords()) {
          qDebug() << record.port();
        }
//        m_dns.deleteLater()
}
