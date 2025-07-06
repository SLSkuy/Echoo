#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "databasemanager.h"
#include "echooclient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // 先注册上下文再加载QML界面
    // 避免出现QML已经加载但client对象还未初始化
    EchooClient client;
    engine.rootContext()->setContextProperty("EchooClient", &client);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Echoo-Client", "StartWindow");


    int ret = app.exec();
    // 如果存在则销毁，防止未登陆时程序关闭而数据库单例并未创建导致虚空指针销毁
    if(DatabaseManager::instance())
        DatabaseManager::instance()->destroy();
    return ret;
}
