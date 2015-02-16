TEMPLATE = lib
TARGET = Mango.Terminal
QT +=  core-private gui-private qml-private quick quick-private
CONFIG += qt plugin

CONFIG_VARS = $${OUT_PWD}$${QMAKE_DIR_SEP}.config.vars
QMAKE_CACHE = $${OUT_PWD}$${QMAKE_DIR_SEP}.qmake.cache

TARGET = $$qtLibraryTarget($$TARGET)
uri = Mango.Terminal

include(backend/backend.pri)
SOURCES += \
          plugin/terminal_screen.cpp \
          plugin/object_destruct_item.cpp \
          plugin/mono_text.cpp \
          plugin/mangoterminal_extension_plugin.cpp \

HEADERS += \
          plugin/terminal_screen.h \
          plugin/object_destruct_item.h \
          plugin/mono_text.h \
          plugin/mangoterminal_extension_plugin.h \

OTHER_FILES = \
              qmldir \
              Cursor.qml \
              Text.qml \
              Screen.qml \
              Selection.qml

other_files.files = $$OTHER_FILES
other_files.path = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
INSTALLS += other_files

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

