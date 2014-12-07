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
#ifndef MDESKTOPENTRY_P_H
#define MDESKTOPENTRY_P_H

#include <QSharedPointer>

class MDesktopEntry;
class QTranslator;

/*!
 * MDesktopEntryPrivate is the private class for MDesktopEntry.
 */
class MDesktopEntryPrivate
{
    Q_DECLARE_PUBLIC(MDesktopEntry)

public:
    /*!
     * Constructs a new MDesktopEntryPrivate class.
     *
     * \param fileName the name of the file to read the desktop entry from
     */
    MDesktopEntryPrivate(const QString &fileName);

    /*!
     * Destroys the MDesktopEntryPrivate.
     */
    virtual ~MDesktopEntryPrivate();

    /*!
     * Parses a desktop entry file.
     *
     * \param device the QIODevice to read the desktop file from
     * \param map the QMap to store key-value pairs to
     * \return true if desktop file can be parsed
     */
    bool readDesktopFile(QIODevice &device, QMap<QString, QString> &map);

    //! The name of the file where the information for this desktop entry was read from.
    QString sourceFileName;

    //! A map for storing the desktop entries keys and their corresponding values
    QMap<QString, QString> desktopEntriesMap;

    //! A map for storing translators for translation catalogs
    static QMap<QString, QSharedPointer<QTranslator> > translators;

    /*!
     * Returns the boolean value of a key.
     *
     * \param key the key to return the boolean value for
     * \return true if the value of specified key is set to "true" and false otherwise.
     */
    bool boolValue(const QString &key) const;

    /*!
     * Returns the string list value of a key. The list will be populated
     * with semicolon separated parts of the key value.
     *
     * \param key the key to return the string list value for
     * \return a string list containing the semicolon separated parts of the key value
     */
    QStringList stringListValue(const QString &key) const;

    //! Flag to indicate whether the desktop entry is valid during parsing
    bool valid;

protected:
    /*
     * \brief this q_ptr starts the inheritance hierarchy
     */
    MDesktopEntry *q_ptr;
};

#endif
