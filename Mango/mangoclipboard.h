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
#ifndef MANGOCLIPBOARD_H
#define MANGOCLIPBOARD_H

#include <QApplication>
#include <QClipboard>



class MangoClipboard : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY dataChanged)

public:
    MangoClipboard() {
        m_clipboard = QApplication::clipboard();
        connect(m_clipboard,SIGNAL(dataChanged()),this,SIGNAL(dataChanged()));
    }

signals:
    void dataChanged();

protected:
    void setText(QString text) {
        m_clipboard->setText(text);
    }

    QString text() { return m_clipboard->text(); }
    QClipboard* m_clipboard;
};

#endif // MANGOCLIPBOARD_H
