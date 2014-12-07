#include "licencegenerator.h"
#include <QTextStream>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QDirIterator>
#include <QtXml/QDomElement>

/*!
    \qmltype LicenceGenerator
    \inqmlmodule Mango 0.1
    \ingroup Mango
    \since 5.3
    \inherits Item
    \title Qml Plugin to generate licence and add them to mango.

    \b{WARNING this is under heavey development}

    This is used to make licence files for the mango system it takes in some parameters that must be set these include

    mangoApiKey

    mangoHomeDir

    mangoStore

    mangoRootDir

    dgluxApiKey

    licenceType

    */
const char* LicenceGenerator::mangoContentType = "audio/x-flac; rate=8000";
const char* LicenceGenerator::dgluxContentType = "";


//const char* LicenceGenerator::kUrl = m_ap;
LicenceGenerator::LicenceGenerator(QObject *parent) :
    QObject(parent),
    m_licKey("b8axVx0MR5TBGa2MF9Nu5dBYlNgyzcIp"),
    m_maStore("http://store.infiniteautomation.com/"),
    m_mangoHomeDir("/home/joseph/Mango/"),
    m_dgAppiKey("infinite_7f109e"),
    m_licenceType("All"),
    m_localMachine(false),
    m_distributor("IA"),
    m_description("mangoES")
{
    network_ = new QNetworkAccessManager(this);
    connect(network_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}


/*!
 \qmlproperty string LicenceGenerator::mangoApiKey
 This is the mango Api key that one must use inorder to get a licence key.
 */
QString LicenceGenerator::mangoApiKey()
{
    return m_licKey;
}
void LicenceGenerator::setMangoApiKey(const QString &mangoApiKey)
{
    if (m_licKey == mangoApiKey)
        return;
    m_licKey = mangoApiKey;
    emit mangoApiKeyChanged();
}

/*!
 \qmlproperty string LicenceGenerator::mangoStore
 This is the URL of the mango store.

 example:

 http://someurl.com

 */
QUrl LicenceGenerator::mangoStore()
{
    return m_maStore;
}
void LicenceGenerator::setMangoStore(const QUrl &mangoStore)
{
    if( m_maStore == mangoStore)
        return ;
    m_maStore = mangoStore;
    emit mangoStoreChanged();
}


/*!
 \qmlproperty string LicenceGenerator::mangoRootDir
   This must be set.  It tells the Licence Generator where the mango root directory is installed.
 */
QString LicenceGenerator::mangoRootDir()
{
    return m_mangoHomeDir;
}

void LicenceGenerator::setMangoRootDir(const QString &mangoRootDir)
{
    if (m_mangoHomeDir == mangoRootDir)
        return;
    m_mangoHomeDir = mangoRootDir;
    emit mangoRootDirChanged();
}
/*!
  \qmlproperty string LicenceGenerator::dgluxApiKey
  This is the ai key that is used for dglux

\b{important} licenceType must be set to All or DgLux in order to use this.
 */
QString LicenceGenerator::dgluxApiKey()
{
    return m_dgAppiKey;
}

void LicenceGenerator::setDgluxApiKey(const QString &dgluxApiKey)
{
    if (m_dgAppiKey == dgluxApiKey)
        return;
    m_dgAppiKey = dgluxApiKey;
    emit dgluxApiKeyChanged();
}

/*!
\qmlproperty string LicenceGenerator::licenceType
This is used to set the licence type there are three options

All

Mango

DgLux

It is important that these are spelled right. It might be best to display these options in a drop down box or a listview or something like that so that the names match
 */

QString LicenceGenerator::licenceType()
{
    return m_licenceType;
}

void LicenceGenerator::setLicenceType(const QString &licenceType)
{
    if(m_licenceType == licenceType)
        return ;
    m_licenceType = licenceType;
    emit licenceTypeChanged();
}

/*!
 \qmlproperty bool LicenceGenerator::localMachine
 This is used to tell the licence generator if the mango system is on a localmachine or on the network
 */
bool LicenceGenerator::localMachine()
{
    return m_localMachine;
}

void LicenceGenerator::setLocalMachine(const bool &localMachine)
{
    if (m_localMachine == localMachine)
        return;
    m_localMachine = localMachine;
    emit localMachineChanged();
}

/*!
 \qmlproperty string LicenceGenerator::distributor
  This is used to set the distributor of the mango system.

  by default this is set to \b{IA}
 */

QString LicenceGenerator::distributor()
{
    return m_distributor;
}
void LicenceGenerator::setDistributor(const QString &distributor)
{
    if (m_distributor == distributor)
        return;
    m_distributor = distributor;
    emit distributorChanged();
}


/*!
 \qmlproperty string LicenceGenerator::description
 the description that will show up on the licence ?

\b{This is under heavy development}

by default this is set to mangoES
*/
QString LicenceGenerator::description()
{
    return m_description;
}

void LicenceGenerator::setDescription(const QString &description)
{
    if (m_description == description)
        return;
    m_description = description;
    emit descriptionChanged();

}

void LicenceGenerator::getInterfaceStrings()
{
    QStringList list;
    QString allInterfaces;
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        list.append(interface.hardwareAddress());
    }
    foreach(QString sd, list){
        allInterfaces.append(sd);
        qDebug() << allInterfaces;
    }
    makeMD5SUM(allInterfaces);
}


// Create the md5sumes that are going to beused to get the GUID
void LicenceGenerator::makeMD5SUM(const QString &s)
{
    QString dgluxString;
    dgluxString = "ThisisaStringtomakeintomd5sum";
    if (m_licenceType == "All"){
        m_mangoMd5sum = QString(QCryptographicHash::hash((s.toUtf8()),QCryptographicHash::Md5).toHex());
        m_dgluxMd5sum = QString(QCryptographicHash::hash((dgluxString.toUtf8()),QCryptographicHash::Md5).toHex());
    }else if(m_licenceType == "Mango"){
        m_mangoMd5sum = QString(QCryptographicHash::hash((s.toUtf8()),QCryptographicHash::Md5).toHex());

    }else if (m_licenceType == "DGLux"){
        m_dgluxMd5sum = QString(QCryptographicHash::hash((dgluxString.toUtf8()),QCryptographicHash::Md5).toHex());
    }
qDebug() << m_mangoMd5sum;
}
// Create the json file
void LicenceGenerator::setJSON()
{
    QString json;
    json .append( "{\"apiKey\":");
    json.append("\"");
    json.append(m_licKey); // $MA_API_KEY
    json.append("\"");
    json.append(",\n\"guid\":\"");
    json.append(m_guid); // $GUID
    json.append("\"");
    json.append(",\n\"distributor\":");
    json.append( "\"");
    json.append(m_distributor);
    json.append( "\"");
    json.append(",\n\"description\":\"");
    json.append(m_description);
    json.append("\"");
    json.append(",\n\"modules\":{");
    json.append(m_modules);
    json.append( "}\n}") ;
    // there is no reason to create this but could be useful for details pages after licence is generated
    QString location = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString fileName = "/temp.json";
    QString append;
    append = location.append(fileName);
    qDebug() <<"This is append  "<< append;
    QFile mFile(append);
    if(!mFile.open(QFile::ReadWrite  | QFile::Text )){
        qDebug() << "Could not open the File for writing  " << append ;
        return ;
    }
    QTextStream out(&mFile);
    out << json;
    mFile.flush();
    mFile.close();
    qDebug() << json;
}

void LicenceGenerator::getModuels()
{
    QStringList endList;
    QString licenceType;
    QString version;
    QString name;
    QString location = m_mangoHomeDir ;
    QDirIterator scan(location,QDirIterator::Subdirectories);

    while(scan.hasNext()){
        scan.next();
        if (!scan.fileInfo().isDir()) {
            QString filename = scan.filePath();


            if (filename.endsWith("module.properties")){
                // go throwugh the files that match
                QFile mFile(filename);
                if(!mFile.open(QFile::ReadOnly | QFile::Text )){
                    qDebug() << "Could not open the File " << filename ;
                    return ;
                }
                QTextStream in(&mFile);
                QString line;
                while ( !in.atEnd() ){
                    line = in.readLine();
                    if(line.startsWith("version")){
                        QRegExp reg("=");
                        reg.setPatternSyntax(QRegExp::WildcardUnix);
                        line.replace(reg, "\" : \"");
                        line.append("\", \"licenceType\" : \"paid\"}, \n");
                        line.insert(0," { \"");
//                        version = line;
                        endList.append(line);
                    }else if (line.startsWith("name")){
                        QRegExp reg("*=");
                        reg.setPatternSyntax(QRegExp::WildcardUnix);
                        line.replace(reg,"");
                        line.append("\":");
                        line.insert(0, "\"");
//                        name = line;
                        endList.append(line);

                    }
                }
                mFile.close();


                //FIXME lets make this work for real.  right now it thinks that all modules are free
            }//name and file done
//            else if (filename.endsWith("licenseTypes.xml")){
//                QFile mFile(filename);
//                if(!mFile.open(QFile::ReadOnly | QFile::Text )){
//                    qDebug() << "Could not open the File " << filename ;
//                    return ;
//                }
//                QTextStream in(&mFile);
//                QString line;
//                while ( !in.atEnd() ){
//                    line = in.readAll();

//                    if(line.contains("id=")){
//                        //find anything with id= in it
//                        QRegExp rex("*id=*");
//                        rex.setPatternSyntax(QRegExp::WildcardUnix);
//                        line.replace(rex,"licenceType : \"paid\" }," );

//                        // remove the trailing end
////                        QRegExp re(">*");
////                        re.setPatternSyntax(QRegExp::WildcardUnix);
////                        line.replace(re,"},");
////                        licenceType = line;
//                        endList.append(line);
//                    }
//                }
//                mFile.close();
//                endList.join("\n");

//            }
        }
                        endList.join("\n");

    }
foreach(QString foo, endList){
   m_modules.append(foo);
}

//    QString fooBar = fooBar.append(endList);
//    qDebug() << m_modules;
}

void LicenceGenerator::replyFinished(QNetworkReply* reply) {

    Result result = Result_ErrorNetwork;
    Hypotheses hypotheses;

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "ERROR \n" << reply->errorString();
    } else {
        qDebug() << "Running ParserResponse for \n" << reply << result;
        ParseResponse(reply, &result, &hypotheses);
    }
    emit Finished(result, hypotheses);
    reply_->deleteLater();
    reply_ = NULL;
}

void LicenceGenerator::makeGuid(){

    // FIXME add if statements for all mango or dglux

    if(m_licenceType == "ALL")
    {

        // ad curl stuff here
    }else if (m_licenceType == "Mango")
    {

        // ad curl stuff here

    }
    else if (m_licenceType == "DGLux")
    {

        // ad curl stuff here

    }
    else
    {
        qDebug() << "that is not the lcorrect option for licence type.  You must either enter in \n " << "Mango\n" << "DGLUX\n" << "Or All\n " << "In order for this to work !";
    }
}
