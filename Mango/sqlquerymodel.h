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
#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H
#include <QVariant>
#include <QSqlQueryModel>
#include <QSqlDatabase>
class SqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:

    explicit SqlQueryModel(QObject *parent = 0);
    Q_INVOKABLE  void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());
    Q_INVOKABLE  void setQuery(const QSqlQuery &query);
    QVariant  data(const QModelIndex &index, int role)const;
     QHash<int, QByteArray>roleNames() const;
signals:
     void compleated();

public slots:
private:
};
#endif // QSQLQUERYMODEL_H
