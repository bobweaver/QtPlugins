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
#include "mangomime.h"

MangoMime* MangoMime::m_pInstance = NULL;

MangoMime::MangoMime(QObject *parent) :
    QObject(parent)
{
}

QObject* MangoMime::singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine)
    return MangoMime::instance(engine);
}

MangoMimeType* MangoMime::get_mime_type(QString fileName) {
    QMimeDatabase db;
    return new MangoMimeType(db.mimeTypeForFile(fileName));
}

MangoMime* MangoMime::instance(QQmlEngine *engine) {
    if (!m_pInstance) {
        m_pInstance = new MangoMime(engine);
    }
    return m_pInstance;
}
