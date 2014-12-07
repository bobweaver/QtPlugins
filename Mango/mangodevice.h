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

#ifndef MANGODEVICE_H
#define MANGODEVICE_H

#include <QObject>
#include <QtQml>
class MangoDevice : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString deviceModelIdentifier READ deviceModelIdentifier NOTIFY dataChanged)

public:
    static QObject *singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static MangoDevice* instance(QQmlEngine *engine);

    Q_INVOKABLE static QString deviceModelIdentifier() { return m_deviceModelIdentifier; }

signals:
    void dataChanged();

protected:
    explicit MangoDevice(QObject *parent = 0);

    static QString m_deviceModelIdentifier;
    static MangoDevice* m_pInstance;
};

#endif // MANGODEVICE_H
