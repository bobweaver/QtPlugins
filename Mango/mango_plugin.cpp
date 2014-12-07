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
#include "mango_plugin.h"
#include "mango.h"
#include <qqml.h>
#include "applicationlauncher.h"
#include "bonjour.h"
#include "bonjourrecord.h"
#include "bonjourregister.h"
#include "bonjourservicebrowser.h"
#include "bonjourserviceresolver.h"
#include "dirmodel.h"
#include "dirreader.h"
#include "dnslookup.h"
#include "filemove.h"
#include "filereader.h"
#include "filewriter.h"
#include "iorequest.h"
#include "iorequestworker.h"
#include "sqlquery.h"
#include "sqlquerymodel.h"
#include "menumodels.h"
#include "mangodownloader.h"
#include "mangofile.h"
#include "mangodir.h"
#include "mangofilesystemwatcher.h"
#include "mangosavefile.h"
#include "mangotemporaryfile.h"
#include "mangofileinfo.h"
#include "mangomimetype.h"
#include "mangomime.h"
#include "mangounits.h"
#include "mangodevice.h"
#include "mangoclipboard.h"
#include "mangosharedmemory.h"
#include "mangosslsocket.h"
#include "mdesktopentry.h"
#include "oauth2.h"
#include "placesmodel.h"
#include "hostinfo.h"
#include "soundrecorder.h"
#include "speechrecognition.h"
#include "texttospeech.h"
#include "randompassword.h"




void MangoPlugin::registerTypes(const char *uri)
{
    // @uri Mango
    qmlRegisterType<Mango>(uri, 0, 1, "Mango");
    qmlRegisterType<RandomPassword>(uri,0,1 ,"RandomPassword");
    // networking stuff
    qmlRegisterType<BonjourBackend>(uri, 0, 1, "Bonjour");
    qmlRegisterType<DnsLookUp>(uri, 0, 1, "DNSLookup");
    qmlRegisterType<OAuth2>(uri, 0, 1, "OAuth2");
    qmlRegisterType<MangoDownloader>(uri, 0, 1, "MangoDownloader");
    qmlRegisterType<HostInfo>(uri, 0, 1, "HostInfo");
    qmlRegisterType<MangoSslSocket>(uri, 0, 1, "MangoSslSocket");

    // Filesystem stuff
    qmlRegisterType<DirModel>(uri, 0, 1, "DirModel");
    qmlRegisterType<DirReader>(uri, 0, 1, "DirReader");
    qmlRegisterType<FileMove>(uri, 0, 1, "FileMove");
    qmlRegisterType<FileReader>(uri, 0, 1, "FileReader");
    qmlRegisterType<FileWriter>(uri, 0, 1, "FileWriter");
    qmlRegisterType<MangoFile>(uri, 0, 1, "MangoFile");
    qmlRegisterType<MangoDir>(uri, 0, 1, "MangoDir");
    qmlRegisterType<MangoSaveFile>(uri, 0, 1, "MangoSaveFile");
    qmlRegisterType<MangoTemporaryFile>(uri, 0, 1, "MangoTemporaryFile");
    qmlRegisterType<MangoFileInfo>(uri, 0, 1,"MangoFileInfo");
    qmlRegisterType<MangoFileSystemWatcher>(uri, 0, 1, "MangoFileSystemWatcher");
    qmlRegisterType<MangoMimeType>();
    qmlRegisterType<MangoClipboard>(uri, 0, 1, "MangoClipboard");

    //sql stuff
    qmlRegisterType<SqlQuery>(uri, 0, 1, "SqlQuery");
    qmlRegisterType<SqlQueryModel>(uri, 0, 1, "SqlQueryModel");

    //Linux stuff
    qmlRegisterType<MenuModel>(uri, 0, 1, "Menu");
    qmlRegisterType<PlacesModel>(uri, 0, 1, "PlacesModel");
    qmlRegisterType<Application>(uri, 0, 1, "Application");

    // Utils
    qmlRegisterType<SpeechRecognition>(uri, 0, 1, "SpeechRecognition");
    qmlRegisterType<SoundRecorder>(uri, 0, 1, "SoundRecorder");
    qmlRegisterType<TextToSpeech>(uri, 0, 1, "TextToSpeech");

    // mem mapping
    qmlRegisterType<MangoSharedMemory>(uri, 0, 1, "MangoSharedMemory");

}

// singleton instance tyes
void MangoPlugin::initializeEngine(QQmlEngine* engine, const char* uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
    qmlRegisterSingletonType<MangoMime>(uri, 0, 1, "MangoMime", MangoMime::singletontype_provider);
    qmlRegisterSingletonType<MangoUnits>(uri, 0, 1, "MangoUnits", MangoUnits::singletontype_provider);
    qmlRegisterSingletonType<MangoDevice>(uri, 0, 1, "MangoDevice", MangoDevice::singletontype_provider);
}
