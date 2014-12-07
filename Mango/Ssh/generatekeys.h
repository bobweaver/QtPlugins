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
#ifndef GENERATEKEYS_H
#define GENERATEKEYS_H

#include <QObject>
#include <QSharedPointer>
#include <QByteArray>
#include <QDateTime>
#include "QSsh/src/libs/ssh/sshkeygenerator.h"
#include "QSsh/src/libs/ssh/ssh_global.h"
#include "QSsh/src/libs/ssh/sshcapabilities_p.h"
#include "QSsh/src/libs/ssh/sshpacket_p.h"
#include "QSsh/src/libs/ssh/sshbotanconversions_p.h"


#include "QSsh/src/libs/3rdparty/botan/botan.h"
class GenerateKeys : public QObject
{
    Q_OBJECT

public:

    explicit GenerateKeys(QObject *parent = 0);
    Q_PROPERTY(QString getPassword READ getPassword WRITE setPassword)
    Q_PROPERTY(KeyType keyType READ keyType WRITE setKeyType)
    Q_PROPERTY(PrivateKeyFormat format READ format WRITE setFormat)
    Q_PROPERTY(int keySize READ keySize WRITE setKeySize)
    Q_PROPERTY(EncryptionMode encryptionMode READ encryptionMode WRITE setEncryptionMode)
    Q_ENUMS(KeyType)
    Q_ENUMS(PrivateKeyFormat)
    Q_ENUMS(EncryptionMode)


    enum KeyType{
        Rsa,
        Dsa
    };
    enum PrivateKeyFormat {
        Pkcs8,
        OpenSsl,
        Mixed
    };
    enum EncryptionMode {
        DoOfferEncryption,
        DoNotOfferEncryption
    };

    QString error() const { return m_error; }


    KeyType keyType() const{return m_keyType;}
    void setKeyType(const KeyType &keyType);


    PrivateKeyFormat format()const {return m_format;}
    void setFormat(const PrivateKeyFormat &format);

    int keySize() const;
    void setKeySize(int &keySize);

    EncryptionMode encryptionMode() const{return m_encryptionMode;}
    void setEncryptionMode(const EncryptionMode &encryptionMode);

    QString getPassword() const;
    void setPassword(const QString &password);

    Q_INVOKABLE bool generateKeys();


    QByteArray privateKey() const { return m_privateKey; }
    QByteArray publicKey() const { return m_publicKey; }

signals:

public slots:

private:

    QString m_error;
    KeyType m_keyType;
    PrivateKeyFormat m_format;
    int m_keySize;
    EncryptionMode m_encryptionMode;
    QByteArray m_privateKey;
    QByteArray m_publicKey;
    QString m_password;

    typedef QSharedPointer<Botan::Private_Key> KeyPtr;
    void generatePkcs8KeyStrings(const KeyPtr &key, Botan::RandomNumberGenerator &rng);
    void generatePkcs8KeyString(const KeyPtr &key, bool privateKey, Botan::RandomNumberGenerator &rng);
    void generateOpenSslKeyStrings(const KeyPtr &key);
    void generateOpenSslPrivateKeyString(const KeyPtr &key);
    void generateOpenSslPublicKeyString(const KeyPtr &key);
};

#endif // GENERATEKEYS_H
