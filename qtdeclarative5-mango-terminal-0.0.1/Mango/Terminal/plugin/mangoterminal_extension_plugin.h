/*
* Joseph Mills Fork of YAT
*/
#ifndef MANGO_TERMINAL_EXTENSION_PLUGIN
#define MANGOTERMINAL_EXTENSION_PLUGIN

#include <QtQml/qqmlextensionplugin.h>

class MangoTerminalExtensionPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")
public:
    void registerTypes(const char *uri);
    void initializeEngine(QQmlEngine *engine, const char *uri);
};

#endif // MANGO_TERMINAL_EXTENSTION_PLUGIN
