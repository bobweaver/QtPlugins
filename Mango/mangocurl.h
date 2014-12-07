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
#ifndef MANGOCURL_H
#define MANGOCURL_H

#include <curl/curl.h>

#include <QHash>
#include <QVariant>
#include <QLinkedList>
class QTextCodec;

class MangoCUrl {
public:
    typedef QHash<CURLoption, QVariant> Options;
    typedef QHashIterator<CURLoption, QVariant> OptionsIterator;
    typedef int (*WriterPtr)(char*, size_t, size_t, std::string*);

    class Code {
    public:
        Code(CURLcode code = CURLE_OK): _code(code) {}
        QString text() { return curl_easy_strerror(_code); }
        inline CURLcode code() { return _code; }
        inline bool isOk() { return _code == CURLE_OK; }

    private:
        CURLcode _code;
    };

    MangoCUrl();
    virtual ~MangoCUrl();

    QString exec(Options& opt);
    QByteArray buffer() const {
        return QByteArray(_buffer.c_str(), _buffer.length());
    }
    inline Code lastError() { return _lastCode; }
    QString errorBuffer() { return _errorBuffer; }
    void setTextCodec(const char* codecName);
    void setTextCodec(QTextCodec* codec);



protected:
    void setOptions(Options& opt);

private:
    CURL* _curl;
    char* _errorBuffer;
    std::string _buffer;
    Code _lastCode;
    QTextCodec* _textCodec;
    QLinkedList<curl_slist*> _slist;
};

Q_DECLARE_METATYPE(MangoCUrl::WriterPtr)
Q_DECLARE_METATYPE(std::string*)
Q_DECLARE_METATYPE(char*)

#endif // MANGOCURL_H
