#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "backend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<BackEnd>("qrapp.backend", 1, 0, "BackEnd");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
