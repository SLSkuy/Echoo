#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "echooclient.h"
#include "message.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // 先注册上下文再加载QML界面
    // 避免出现QML已经加载但client对象还未初始化
    EchooClient client;
    engine.rootContext()->setContextProperty("EchooClient", &client);

    // 注册Message对象用于在qml中传输消息
    qmlRegisterType<Message>("P2PModule", 1, 0, "Message");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Echoo-Client", "StartWindow");

    return app.exec();
}
