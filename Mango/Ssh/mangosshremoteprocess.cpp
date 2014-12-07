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
#include "mangosshremoteprocess.h"

/*!
  \qmltype MangoSshRemoteProcess
  \inqmlmodule Mango.Ssh 0.1
  \ingroup Mango.Ssh
  \inherits Item
  \since 5.3
  This qml plugin implements an SSH channel for running a remote process.
    The process is started via the runCommand()
    member function. If the process needs a pseudo terminal, you can setone one via needsTerminal: true
    Note that this class does not support QIODevice's waitFor*() functions,

    \b{i.e. it has no synchronous mode}

    Example:

    \code
         MangoSshRemoteProcess{
            id: sshRemoteProcess
            // Set the ssh property's
            username: "user"
            hostName: "aFQDN"
            passwd: "a pass"
            timeout: 20

            //set up application that will run on the remote machine.
            needsTerminal: true
            command: "uname -a"

            // Check to see if the process is running on the Remote machine and get back the shells output
            onRunning:{
                // get the stdout back
                console.log(getStdout)

                // get the stderr back
                console.log(getStderr)
            }
        }
        Compoonent.onCompleded:{
            sshRemoteProcess.runCommand()
    }
    \endcode
 */

MangoSshRemoteProcess::MangoSshRemoteProcess(QObject *parent) :
    QObject(parent),
    m_needsTerminal(false),
    m_timeout(20),
    m_sshPort(22),
    m_authenticationType("password"),
    m_proxyType("none")
{

}

/*!
  \qmlproperty bool MangoSshRemoteProcess::needsTerminal
    bool property that is used to launch things with a terminal emulator,
*/
bool MangoSshRemoteProcess::needsTerminal()
{
    return m_needsTerminal;
}

void MangoSshRemoteProcess::setNeedsTerminal(bool &needsTerminal)
{
    m_needsTerminal = needsTerminal;
}
/*!
 \qmlproperty int MangoSshRemoteProcess::timeout
 sets the timeout for connection this is in seconds.
*/
int MangoSshRemoteProcess::timeout()
{
    return m_timeout;
}

void MangoSshRemoteProcess::setTimeout(int &timeout)
{
    m_timeout = timeout;
}

/*!
  \qmlproperty strinn MangoSshRemoteProcess::username
  This is the Username of the remote machine that you would like to upload to.
 */

QString MangoSshRemoteProcess::username()
{
    return m_username;
}

void MangoSshRemoteProcess::setUsername(const QString &username)
{
    m_username = username;
}

/*!
 \qmlproperty string MangoSshRemoteProcess::hostName
 This is the hostname of the remote machine that you would like to upload your files too.Used with the ssh connection to upload the file.
 */
QString MangoSshRemoteProcess::hostName()
{
    return m_hostName;
}

void MangoSshRemoteProcess::setHostName(const QString &hostName)
{
    m_hostName = hostName;

}
/*!
 \qmlproperty string MangoSshRemoteProcess::passwd
 The Password for the remote machine that you would like to upload the file to.
 */
QString MangoSshRemoteProcess::passwd()
{
    return m_passwd;
}

void MangoSshRemoteProcess::setPasswd(const QString &passwd)
{
    m_passwd = passwd;
}
/*!
  \qmlproperty int MangoSshRemoteProcess::sshPort
 This is used to set the port that ssh is listening on,  By default this is set to port 22
 */
int MangoSshRemoteProcess::sshPort()
{
    return m_sshPort;
}

void MangoSshRemoteProcess::setSshPort(int &sshPort)
{
    m_sshPort = sshPort;
}
/*!
 \qmlproperty string MangoSshRemoteProcess::command
  This is the command that you want to run after you are connected via ssh
 */
QString MangoSshRemoteProcess::command()
{
    return m_command;
}

void MangoSshRemoteProcess::setCommand(const QString &command)
{
    m_command = command;
}
/*!
  \qmlsignal MangoSshRemoteProcess::runCommand()
   sets up the connection and runs the command .
*/
void MangoSshRemoteProcess::runCommand()
{
    QSsh::SshConnectionParameters params;

    if (m_proxyType == "none")
    {
//        params.proxyType = QSsh::SshConnectionParameters::NoProxy;
        params.host = m_hostName;
        params.userName = m_username;
        params.password = m_passwd;
        params.timeout = m_timeout;
        if (m_authenticationType == "password")
        {
            params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
        }else if (m_authenticationType == "key")
        {
            params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePublicKey;
            params.privateKeyFile = m_privateKey;
        }
        params.port = m_sshPort;
    }
    else if (m_proxyType == "default ")
    {
//    params.proxyType = QSsh::SshConnectionParameters::DefaultProxy;
    params.host = m_hostName;
    params.userName = m_username;
    params.password = m_passwd;
    params.timeout = m_timeout;
    if (m_authenticationType == "password")
    {
        params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
    }
    else if (m_authenticationType == "key")
    {
        params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePublicKey;
        params.privateKeyFile = m_privateKey;
    }
    params.port = m_sshPort;

    }

    // TODO free this pointer!
    m_connection = new QSsh::SshConnection(params, this);

    connect(m_connection, SIGNAL(connected()), SLOT(onConnected()));
    connect(m_connection, SIGNAL(error(QSsh::SshError)), SLOT(onConnectionError(QSsh::SshError)));

    m_connection->connectToHost();
}

QString MangoSshRemoteProcess::getStderr()
{
    return m_stderr;
}

QString MangoSshRemoteProcess::getStdout()
{
    return m_stdout;
}

/*!
  \qmlproperty string MangoSshRemoteProcess::authenticationType
  \b{under heavey development}

    This is used to change the authenticationType from password (default) or key these are the only 2 options.
    if you change from password to keys you must set the publicKey,

    see also publicKey

 */
QString MangoSshRemoteProcess::authenticationType()
{
    return m_authenticationType;
}

void MangoSshRemoteProcess::setAuthenticationType(const QString &authenticationType)
{
    m_authenticationType = authenticationType;
}

QString MangoSshRemoteProcess::proxyType()
{
    return m_proxyType;
}

/*!
  \qmlproperty string MangoSshRemoteProcess::privateKey
  This is used to set the private key that one would like to use if there going to set the authenticationType to \b{key}
  by default authenticationType is set to \b{password} so this does not need to be set.  But if you are to use keys to login
  then one must set the private key that there going to useconds_t

  \b{see also} authenticationType

 */
QString MangoSshRemoteProcess::privateKey()
{
    return m_privateKey;

}

void MangoSshRemoteProcess::setPrivateKey(const QString &privateKey)
{
    m_privateKey = privateKey;
}

/*!
 \qmlproperty readonly MangoSshRemoteProcess::exit
 returns true if the ssh connection is over, else returns false

 see also kill() close()
 */
bool MangoSshRemoteProcess::exit()
{
    return m_exit;
}




void MangoSshRemoteProcess::onConnected()
{
    qDebug() << "Connected";
    emit running(true);
    emit closed(false);
//    qDebug() << "Running Commands...";

    QByteArray ba =  m_command.toLatin1();
      const QByteArray comman(ba);
      remoteProc = m_connection->createRemoteProcess(comman);

      if(remoteProc){
          connect(remoteProc.data(), SIGNAL(started()), SLOT(onChannelStarted()) );
          connect(remoteProc.data(), SIGNAL(readyReadStandardOutput()), SLOT(readyReadStandardOutput()));
          remoteProc->start();
      }
}

void MangoSshRemoteProcess::onConnectionError(QSsh::SshError)
{
    m_errorString =  m_connection->errorString();
    emit error(m_errorString);
    emit running(false);
//    qDebug() << " Connection error" << m_connection->errorString();
}

void MangoSshRemoteProcess::onChannelStarted(){
//    qDebug() << " Channel Started";
    emit running(true);
}


// get the standered output
void MangoSshRemoteProcess::readyReadStandardOutput()
{
    QString stderr = QString::fromLatin1(remoteProc->readAllStandardOutput());
    QString stdout = QString::fromLatin1(remoteProc->readAll());

    if (!stderr.isEmpty())
    {
        m_stderr = stderr;
        emit running(false);
    }
    if (!stdout.isEmpty())
    {
        m_stdout = "";
        m_stdout = stdout;
        emit running(false);
    }
    // I SHould kill the pointer here and not real on QML programer to kill



}

/*!
  \qmlsignal MangoSshRemoteProcess::close()
  This closes the process that is running but not the ssh connection

  see also kill() exit
 */
void MangoSshRemoteProcess::close()
{
    remoteProc->close();
    emit running(false);
    emit closed(true);
    m_exit = true;
}

/*!
 \qmlsignal MangoSshRemoteProcess::kill()
 This kills the process that is running then stops the ssh connection.

see also close() exit
*/
void MangoSshRemoteProcess::kill()
{
    remoteProc->close() ;
    m_connection->disconnectFromHost();
    emit running(false);
    emit closed(true);
    m_exit = true ;
}

MangoSshRemoteProcess::State MangoSshRemoteProcess::state() const
{


    switch (m_connection->state()) {
    case QSsh::Internal::SocketUnconnected:
        return Unconnected;
    case QSsh::Internal::UserAuthServiceRequested:
        return UserAuthServiceRequested;
    case QSsh::Internal::UserAuthRequested :
        return UserAuthRequested;
    case QSsh::Internal::ConnectionEstablished:
        return Connected;
    default:
        return Connecting;
    }
}
