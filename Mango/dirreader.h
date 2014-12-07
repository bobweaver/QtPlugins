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
#ifndef DIRREADER_H
#define DIRREADER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QDebug>
class DirReader : public QObject
{
    Q_OBJECT
public:
    explicit DirReader(QObject *parent = 0);
    Q_PROPERTY(QString dirPath READ dirPath WRITE setDirPath NOTIFY dirPathChanged)
    Q_PROPERTY(QString files READ files NOTIFY filesChanged)
    QString dirPath()const;
    void setDirPath(const QString &path);
    Q_INVOKABLE void readFiles();
    QString files()const;
    void setFiles(const QStringList &someList);

signals:
    void dirPathChanged();
    void filesChanged();
private:
    QString m_dirPath;
    QStringList list;
    QString mFiles;


};

#endif // DIRREADER_H
