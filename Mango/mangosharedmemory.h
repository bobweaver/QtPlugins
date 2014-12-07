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
#ifndef MANGOSHAREDMEMORY_H
#define MANGOSHAREDMEMORY_H

#include <QtCore>
#include <QSharedMemory>

class MangoSharedMemory : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)

public:

    Q_INVOKABLE bool write(QVariant data);
    Q_INVOKABLE QVariant read();

signals:
    void keyChanged();

protected:
    void setKey(const QString& key) { m_sharedMemory.setKey(key); emit keyChanged(); }
    QString key() { return m_sharedMemory.key(); }

    QSharedMemory m_sharedMemory;
};

#endif // MANGOSHAREDMEMORY_H
