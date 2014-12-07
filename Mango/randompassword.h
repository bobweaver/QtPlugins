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
#ifndef RANDOMPASSWORD_H
#define RANDOMPASSWORD_H
#include <QString>
#include <QDebug>
#include <QObject>

class RandomPassword : public QObject
{
    Q_OBJECT
public:
    explicit RandomPassword(QObject *parent = 0);
    Q_PROPERTY(int numberOfCharecters READ numberOfCharecters WRITE setNumberOfCharecters)

    Q_INVOKABLE QString getRandomPassword();

    int numberOfCharecters();

    void setNumberOfCharecters(const int &numberOfCharecters);

    Q_INVOKABLE QString generateRandomPassword() ;

private:
    QString m_pass;
    int i_number;

};

#endif // RANDOMPASSWORD_H
