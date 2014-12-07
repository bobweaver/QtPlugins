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
#ifndef WINDOW_H
#define WINDOW_H

#include <QtCore/QObject>
#include <QtQuick/QQuickWindow>

class Window : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int surfaceRole READ surfaceRole WRITE setSurfaceRole NOTIFY surfaceRoleChanged)

public:
    explicit Window(QObject *parent = 0);
    int surfaceRole() const;
    void setSurfaceRole(int surfaceRole);

Q_SIGNALS:
    void surfaceRoleChanged(int);

private:
    QQuickWindow* m_window;
};

#endif // WINDOW_H
