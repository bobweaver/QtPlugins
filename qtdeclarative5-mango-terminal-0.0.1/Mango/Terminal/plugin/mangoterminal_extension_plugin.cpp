/*
* Joseph Mills Fork of YAT
*/

#include "mangoterminal_extension_plugin.h"

#include <QtCore/QByteArray>

#include <QQmlEngine>

#include "terminal_screen.h"
#include "object_destruct_item.h"
#include "screen.h"
#include "text.h"
#include "cursor.h"
#include "mono_text.h"
#include "selection.h"

static const struct {
    const char *type;
    int major, minor;
} qmldir [] = {
    { "Screen", 0, 1},
    { "Text", 0, 1},
    { "Cursor", 0, 1},
    { "Selection", 0, 1},
};

void MangoTerminalExtensionPlugin::registerTypes(const char *uri)
{
    // @uri Mango.Terminal
    qmlRegisterType<TerminalScreen>(uri, 0, 1, "TerminalScreen");
    qmlRegisterType<ObjectDestructItem>(uri, 0, 1, "ObjectDestructItem");
    qmlRegisterType<MonoText>(uri, 0, 1, "MonoText");
    qmlRegisterType<Screen>();
    qmlRegisterType<Text>();
    qmlRegisterType<Cursor>();
    qmlRegisterType<Selection>();

    const QString filesLocation = baseUrl().toString();
    for (int i = 0; i < int(sizeof(qmldir)/sizeof(qmldir[0])); i++)
        qmlRegisterType(QUrl(filesLocation + "/" + qmldir[i].type + ".qml"), uri, qmldir[i].major, qmldir[i].minor, qmldir[i].type);
}

void MangoTerminalExtensionPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
    Q_UNUSED(engine);
}
