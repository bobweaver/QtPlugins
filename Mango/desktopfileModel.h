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
#include <QAbstractListModel>
#include <QStringList>

class DesktopFile
{
public:
    DesktopFile(const QString &name, const QString &comment, const QString &exec,const QString &type, bool &terminal,const QString &icon);
    QString name() const;
    QString comment() const;
    QString exec() const;
    QString type() const;
    bool terminal() const;
    QString icon() const;

private:
    QString m_name;
    QString m_comment;
    QString m_exec;
    QString m_type;
    bool m_terminal;
    QString m_icon;
};

class DesktopFileModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DesktopFileRoles {
        NameRole = Qt::UserRole + 1,
        CommentRole,
        ExecRole,
        TypeRole,
        TerminalRole,
        IconRole
    };

    DesktopFileModel(QObject *parent = 0);
    void addDesktopFile(const DesktopFile &desktopFile);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QHash<int,QByteArray> roleNames() const;

private:
    QList<DesktopFile> m_desktopFiles;
};


