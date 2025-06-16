// MessageManager类实现
// 该类作为一个服务类来使用
// 处理客户端传入的各类数据并根据规定的传输文件格式进行相应的转发等操作
// 处理私聊与群聊信息

#include <QJsonDocument>

#include "messagemanager.h"
#include "logger.h"

MessageManager::MessageManager(AccountManager *am, GroupManager *gm) : _accounts(am), _groups(gm) {}

void MessageManager::ProcessMessage(QTcpSocket *socket, const QByteArray &data)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err); // 捕获JSON字节流并反序列化
    if (err.error != QJsonParseError::NoError) {
        Logger::Error("Invalid JSON received");
        return;
    }

    QJsonObject obj = doc.object(); // 转换为JSON结构对象
    QString type = obj["type"].toString();

    if (type == "text") {
        // 测试收取信息
        qDebug() << obj["content"].toString();
    } else if (type == "register") {
        // 用户注册
        _accounts->RegisterUser(socket, obj);
    } else if (type == "login") {
        // 登录检测
        _accounts->LoginDetection(socket, obj);
    } else if (type == "privateMsg") {
        // 消息转发
        PrivateMessageForwarding(socket, obj);
    } else if (type == "accountInfo") {
        // 请求回应用户账号数据
        _accounts->ResponseInfo(socket, obj);
    } else if (type == "createGroup") {
        // 创建新的群聊
        _groups->CreateGroup(socket, obj);
    } else if (type == "groupMsg") {
        // 群聊消息转发
        GroupMessageForwarding(socket, obj);
    }
}

void MessageManager::SendResponse(QTcpSocket *socket, bool result, QString &content)
{
    QJsonObject obj;
    obj["success"] = result;
    obj["content"] = content;

    QJsonDocument doc(obj);      // 构建JSON内容的文档容器，容纳具体的JSON内容
    socket->write(doc.toJson()); // 序列化JSON数据进行传输
}

void MessageManager::PrivateMessageForwarding(QTcpSocket *socket, const QJsonObject &content)
{
    // 获取信息发送对象
    QString account = content["to"].toString();

    QJsonDocument doc(content);
    QTcpSocket *receiver = _accounts->GetSocket(account);

    if(receiver != nullptr)
    {
        receiver->write(doc.toJson());
        return;
    }

    QString response = "The user does not exist or is not online.";
    SendResponse(socket,false,response);
}

void MessageManager::GroupMessageForwarding(QTcpSocket *socket, const QJsonObject &content)
{
    QString groupAccount = content["to"].toString();

    QJsonDocument doc(content);
    QList<QString> groupMembers = _groups->GetGroupMember(groupAccount);
    if (groupMembers.isEmpty()) {
        Logger::Warning("Group has no members or doesn't exist: " + groupAccount);
        return;
    }

    for (QString &memberAccount : groupMembers) {
        QTcpSocket *user = _accounts->GetSocket(memberAccount);
        if (user == nullptr) {
            // 用户不存在或未登录
            // TODO
        } else {
            user->write(doc.toJson());
        }
    }
}
