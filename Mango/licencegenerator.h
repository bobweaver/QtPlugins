#ifndef LICENCEGENERATOR_H
#define LICENCEGENERATOR_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkInterface>
//#include <QSslSocket>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QCryptographicHash>
#include <QList>
//ALL
//step 1) create md5sum from network interface cards
//step 2) Turn the md5sum into a MA instance id
//step 3) Get all the moduels
//step 4) Create the JSON file to upload to the server.
//step 5) Download and install $MA_HOME/m2m2.license.xml --data "$JSON" $MA_STORE/servlet/api
//step 6) create the md5sum from the guid and the dglux apikey
//step 7)make sure that there is a folder/path with the mango stuff installed if not create one;
//step 8) send reuest to dglux url and get back the licence for it.
//step 9) move the licence file to the correct place


//Mango
//step 1) create md5sum from network interface cards
//step 2) Turn the md5sum into a MA instance id
//step 3) Get all the moduels
//step 4) Create the JSON file to upload to the server.
//step 5) Download and install $MA_HOME/m2m2.license.xml --data "$JSON" $MA_STORE/servlet/api


//DGLuX
//step 1) create the md5sum from the guid and the dglux apikey
//step 2)make sure that there is a folder/path with the mango stuff installed if not create one;
//step 3) send reuest to dglux url and get back the licence for it.
//step 4) move the licence file to the correct place




class QIODevice;
class QNetworkAccessManager;
class QNetworkReply;
class LicenceGenerator : public QObject
{
    Q_OBJECT
public:
    explicit LicenceGenerator(QObject *parent = 0);
    static const char* dgluxContentType;
    static const char* mangoContentType;

    struct Hypothesis {
        QString utterance;
        qreal confidence;
    };
    typedef QList<Hypothesis> Hypotheses;

    //FIXME lets get some real error checking going.
    enum Result {
      Result_Success = 0,
      Result_ErrorAborted,
      Result_ErrorAudio,
      Result_ErrorNetwork,
      Result_NoSpeech,
      Result_NoMatch,
      Result_BadGrammar
    };

    Q_PROPERTY(QString mangoApiKey READ mangoApiKey WRITE setMangoApiKey NOTIFY mangoApiKeyChanged)
    Q_PROPERTY(QUrl mangoStore  READ mangoStore WRITE setMangoStore NOTIFY mangoStoreChanged )
    Q_PROPERTY(QString mangoRootDir READ mangoRootDir WRITE setMangoRootDir NOTIFY  mangoRootDirChanged )
    Q_PROPERTY(QString dgluxApiKey READ dgluxApiKey WRITE setDgluxApiKey NOTIFY dgluxApiKeyChanged)
    Q_PROPERTY(QString licenceType READ licenceType WRITE setLicenceType NOTIFY licenceTypeChanged)
    Q_PROPERTY(bool localMachine READ localMachine WRITE setLocalMachine NOTIFY localMachineChanged)

    Q_INVOKABLE void makeGuid();
    Q_INVOKABLE void setJSON();
    Q_INVOKABLE void getModuels();
    Q_INVOKABLE void makeMD5SUM(const QString &s);
    Q_INVOKABLE void getInterfaceStrings();


    QString mangoApiKey();
    void setMangoApiKey(const QString &mangoApiKey);

    QUrl mangoStore();
    void setMangoStore(const QUrl &mangoStore);

    QString mangoRootDir();
    void setMangoRootDir(const QString &mangoRootDir);

    QString  dgluxApiKey();
    void setDgluxApiKey(const QString &dgluxApiKey);

    QString licenceType();
    void setLicenceType(const QString &licenceType);

    bool localMachine();
    void setLocalMachine(const bool &localMachine );

    QString distributor();
    void setDistributor(const QString &distributor);

    QString description();
    void setDescription(const QString &description);





signals:
    void Finished(Result result, const Hypotheses& hypotheses);
    void resultsChanged();
    void mangoApiKeyChanged();
    void mangoStoreChanged();
    void mangoRootDirChanged();
    void dgluxApiKeyChanged();
    void licenceTypeChanged();
    void localMachineChanged();
    void distributorChanged();
    void descriptionChanged();

private slots:
    void replyFinished(QNetworkReply* reply);

private:
    void ParseResponse(QIODevice* reply, Result* result, Hypotheses* hypotheses);


private:

    QString m_licKey;

    QUrl m_maStore;

    QString m_mangoHomeDir;

    QString m_dgAppiKey;

    QString m_licenceType;

    bool m_localMachine;

    QString m_distributor;

    QString m_description;

    QString m_mangoMd5sum;

    QString m_dgluxMd5sum;

    QString m_guid;

    QString m_modules;

    QNetworkAccessManager* network_;

    QNetworkReply* reply_;

    QByteArray buffered_raw_data_;
};

#endif // LICENCEGENERATOR_H
