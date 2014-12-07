TEMPLATE = lib
TARGET = Mango
QT += qml quick network sql multimedia core widgets serialport
CONFIG += qt plugin
#link_pkgconfig

# get the Libs for avahi/bonjour/zeroconf
unix:!android: LIBS += -ldns_sd
!contains(CONFIG,NO_AVAHI): unix:!macx:LIBS +=  -lavahi-client -lavahi-common
win32:LIBS += -L"c:\\PROGRA~1\\BONJOU~1\\lib\\win32" -ldnssd
win32:INCLUDEPATH += "c:\\program files\\bonjour sdk\\include"


#PKGCONFIG += botan-1.10

TARGET = $$qtLibraryTarget($$TARGET)
uri = Mango

# Input
SOURCES += \
    applicationlauncher.cpp \
    bonjour.cpp \
    bonjourregister.cpp \
    bonjourservicebrowser.cpp \
    bonjourserviceresolver.cpp \
    desktopfileModel.cpp \
    dirmodel.cpp \
    dirreader.cpp \
    dnslookup.cpp \
    filemove.cpp \
    filereader.cpp \
    filewriter.cpp \
    iorequest.cpp \
    iorequestworker.cpp \
    ioworkerthread.cpp \
    mango_plugin.cpp \
    mango.cpp \
    sqlquery.cpp \
    sqlquerymodel.cpp\
    iconprovider.cpp \
    mdesktopentry.cpp \
    menumodels.cpp \
    placesmodel.cpp \
    qmlnetworkinfo.cpp \
    window.cpp \
    mangodownloader.cpp \
    soundrecorder.cpp \
    speechrecognition.cpp \
    texttospeech.cpp \
    oauth2.cpp \
    mangosharedmemory.cpp \
    mangounits.cpp \
    mangodevice.cpp \
    mangoclipboard.cpp \
    mangossl.cpp \
    mangosslsocket.cpp \
    mangofilesystemwatcher.cpp \
    mangotemporaryfile.cpp \
    mangofile.cpp \
    mangodir.cpp \
    mangofileinfo.cpp \
    mangomime.cpp \
    mangomimetype.cpp \
    mangosavefile.cpp \
    mangoiodevice.cpp \
    mangomodbusregistermodel.cpp \
    mangoserialport.cpp \
    mangocurl.cpp \
    randompassword.cpp \
    hostinfo.cpp \
    mangosqldatabase.cpp


HEADERS += \
    applicationlauncher.h \
    bonjour.h \
    bonjourrecord.h \
    bonjourregister.h \
    bonjourservicebrowser.h \
    bonjourserviceresolver.h \
    dirmodel.h \
    dirreader.h \
    dnslookup.h \
    desktopfileModel.h \
    filemove.h \
    filereader.h \
    filewriter.h \
    iorequest.h \
    iorequestworker.h \
    ioworkerthread.h \
    mango_plugin.h \
    mango.h \
    sqlquery.h \
    sqlquerymodel.h \
    iconprovider.h \
    mdesktopentry.h \
    mlite-global.h \
    menumodels.h \
    placesmodel.h \
    qmlnetworkinfo.h \
    window.h \
    qsysteminfocommon_p.h \
    mdesktopentry_p.h \
    mangodownloader.h \
    soundrecorder.h \
    speechrecognition.h \
    texttospeech.h \
    oauth2.h \
    mangosharedmemory.h \
    mangounits.h \
    mangodevice.h \
    mangoclipboard.h \
    mangossl.h \
    mangosslsocket.h \
    mangofilesystemwatcher.h \
    mangotemporaryfile.h \
    mangofile.h \
    mangodir.h \
    mangofileinfo.h \
    mangomime.h \
    mangomimetype.h \
    mangosavefile.h \
    mangoiodevice.h \
    mangomodbusregistermodel.h \
    mangoserialport.h \
    mangocurl.h \
    randompassword.h \
    hostinfo.h \
    mangosqldatabase.h

	
	
!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir

unix:*-g++* {
    QMAKE_CFLAGS += -fPIC -fpermissive -finline-functions -Wno-long-long
    ## adding c++ 11
    QMAKE_CXXFLAGS += -fPIC -fpermissive -finline-functions -Wno-long-long -std=c++0x -Wall -Wextra -pedantic
    QMAKE_CXXFLAGS_HIDESYMS -= -fvisibility-inlines-hidden # for ubuntu 7.04
}



unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

