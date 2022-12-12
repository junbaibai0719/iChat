#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include <QLocale>
#include <QTranslator>
#include <QWindow>
#include <QIcon>


#include "message_handler.h"

int main(int argc, char *argv[])
{
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
    const QUrl url(u"qrc:/iChat/main.qml"_qs);
//    const QIcon icon(":/icons/logo.png");
//    app.setWindowIcon(icon);
    QObject::connect(&app, &QGuiApplication::lastWindowClosed, &app,[]() {
        qDebug()<<"dasdasdad";
    }, Qt::AutoConnection);
    qDebug()<< QQuickStyle::name();
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        };
        QWindow *window = (QWindow *)obj;
        if(window) {

//            window->setFlags(window->flags()| Qt::FramelessWindowHint);
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
