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
#ifndef FILEWRITER_H
#define FILEWRITER_H
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QObject>

class FileWriter : public QObject
{
    Q_OBJECT
public:
    explicit FileWriter(QObject *parent = 0);

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString output READ output WRITE setOutput NOTIFY outputChanged)
    Q_PROPERTY(QString makeDir READ makeDir WRITE setMakeDir)
    Q_PROPERTY(QString  removeDir READ removeDir WRITE setRemoveDir)
    Q_INVOKABLE void writeFile();
    Q_INVOKABLE void createPath();
    Q_INVOKABLE void removePath();
    Q_INVOKABLE void changePermissions(const QString &filename , const QString &permissions);
    QString fileName() const;
    void setFileName(const QString &fileName);
    QString makeDir();
    void setMakeDir(const QString &dirPath);
    QString removeDir();
    void setRemoveDir(const QString &removeDir);


    QString output() const;
    void setOutput(const QString &output);

signals:
      void fileNameChanged();
      void outputChanged();
private:
    QString m_FileName;
    QString m_Output;
    QString m_MakeDir;
    QString m_RemoveDir;
};
#endif // FILEWRITER_H
