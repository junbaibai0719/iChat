#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QLocale>
#include <QTranslator>
#include <QWindow>
#include <QIcon>


#include "message_handler.h"

void add_env_path(const QString &path){
    qputenv("PATH", QString("%1;%2").arg(path, qgetenv("PATH")).toStdString().c_str());
}

int main(int argc, char *argv[])
{
    add_env_path("./qml/componentLib");

    qInstallMessageHandler(messageHandler);
    QGuiApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "iChat_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    qDebug() << engine.pluginPathList();
    const QUrl url("qrc:///main.qml");
    engine.addImportPath("./qml");

    QObject::connect(&app, &QGuiApplication::lastWindowClosed, &app,[]() {
        qDebug()<<"dasdasdad";
    }, Qt::AutoConnection);

//    QQuickStyle::setStyle("Material");
//    qDebug()<< QQuickStyle::name();
    qDebug() << "sadaasd撒大大";

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        };
        QWindow *window = (QWindow *)obj;
        if(window) {
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
