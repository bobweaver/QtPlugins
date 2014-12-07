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
#include "filereader.h"
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
/*!
 * \qmltype FileReader
 * \inqmlmodule Mango 0.1
 * \ingroup Mango
 * \inherits Item
 * \since 5.3
 * A simple qml plugin that is used to read files that are on the local machine.
 */

FileReader::FileReader(QObject *parent) : QObject(parent)
{
}

/*!
 * \qmlproperty string FileReader::output
 * 
 * the output of the file and it content
 */
QString FileReader::output() const
{
    return mOutput;
}

void FileReader::setOutPut(const QString &output)
{
    if (mOutput == output)
        return;
    mOutput = output;
    emit outputChanged();
}

/*!
 * \qmlproperty string  FileReader::fileName
 *
 * used in Qml to set the name of the file that one would like to read
 */

QString FileReader::fileName() const
{
    return m_FileName;
}

void FileReader::setFileName(const QString &fileName)
{
    if (m_FileName == fileName)
        return;
    m_FileName = fileName;
    emit fileNameChanged();
}

/*!
 * \qmlsignal FileReader::readFile()
 * 
 * Used in QML to get read the file that one has selected. 
 *
 */
void FileReader::readFile(QString filename){
    QFile mFile(filename);
    if(!mFile.open(QFile::ReadOnly | QFile::Text )){
        qDebug() << "Could not open the File " << filename ;
        return ;
    }
    QTextStream in(&mFile);
    QString line ;
    while ( !in.atEnd() )
             line = in.readAll();
    setOutPut(line);
    mFile.close();
}


