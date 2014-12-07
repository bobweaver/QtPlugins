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
#ifndef FILEREADER_H
#define FILEREADER_H
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
class FileReader : public QObject
{
public:
    explicit FileReader(QObject *parent = 0);
    Q_OBJECT
    Q_PROPERTY(QString fileName  READ fileName  WRITE setFileName  NOTIFY fileNameChanged)
    Q_PROPERTY(QString output READ output NOTIFY outputChanged)
    Q_INVOKABLE void readFile(QString filename);

    QString fileName() const;
    void setFileName(const QString &fileName);



    QString output() const;
    void setOutPut(const QString &output);


signals:
    void fileNameChanged();
    void outputChanged();
private:
    QString m_FileName;
    bool mReading;
    QString mOutput;


};

#endif // FILEREADER_H
