// Communicator类实现
// 该类用于实现局域网网络通信
// 使用UDP广播发现消息
// TCP连接进行消息传输

#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>

#include "communicator.h"
#include "databasemanager.h"

Communicator::Communicator(Netizen *netizen) : _netizen(netizen), QObject(netizen)
{
    m_udpPort = 1145;
    m_tcpPort = 1145;

    _udpSocket = new QUdpSocket(this);
    _udpSocket->bind(QHostAddress::AnyIPv4, m_udpPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(_udpSocket, &QUdpSocket::readyRead, this, &Communicator::OnUdpReadyRead);

    _tcpServer = new QTcpServer(this);
    _tcpServer->listen(QHostAddress::AnyIPv4, m_tcpPort);
    connect(_tcpServer, &QTcpServer::newConnection, this, &Communicator::OnNewTcpConnection);
}

Communicator::~Communicator()
{
    QJsonObject response;
    response["nickName"] = _netizen->GetNickname();
    response["account"] = _netizen->GetAccount();
    response["online"] = true;
    BroadcastPresence(response);

    _udpSocket->close();
    _tcpServer->close();
}

void Communicator::BroadcastPresence(QJsonObject &obj)
{
    // 广播消息
    QJsonDocument doc(obj);
    _udpSocket->writeDatagram(doc.toJson(), QHostAddress::Broadcast, m_udpPort);
}

void Communicator::OnUdpReadyRead()
{
    // 处理收到的广播消息
    while (_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(_udpSocket->pendingDatagramSize()));
        QHostAddress senderAddr;
        quint16 senderPort;
        _udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddr, &senderPort);

        // 转换为Json文档便于后续处理
        QJsonDocument doc = QJsonDocument::fromJson(datagram);
        if(!doc.isNull() && doc.isObject())
        {
            // 读取json内容
            QJsonObject obj = doc.object();
            bool online = obj["online"].toBool();

            // 检测为离线操作还是在线操作
            if (online) {
                OnlineProcess(obj);
            } else {
                OfflineProcess(obj);
            }
        }
    }
}

void Communicator::OnlineProcess(QJsonObject &obj)
{
    QString nickName = obj["nickName"].toString();
    QString account = obj["account"].toString();
    // 检测当前设备本地数据库是否存在广播者信息
    DatabaseManager *db = DatabaseManager::instance();
    if (db->Contains(account)) {
        // 存在该用户
        if (!db->GetNetizen(account)->IsOnline()) {
            // 检测用户是否在线，若为否则标志为在线，并告诉对方自己也在线
            db->GetNetizen(account)->SetOnline(true);

            // 回应广播自己在线
            QJsonObject response;
            response["nickName"] = _netizen->GetNickname();
            response["account"] = _netizen->GetAccount();
            BroadcastPresence(response);
        }
    } else {
        // 不存在该用户，则添加
        Netizen *newUser = new Netizen(nickName, account, NULL, nullptr);
        newUser->SetOnline(true);
        db->AddNetizen(newUser);

        // 广播回应自己也在线，以此确保双方都确定对方在线
        QJsonObject response;
        response["nickName"] = _netizen->GetNickname();
        response["account"] = _netizen->GetAccount();
        BroadcastPresence(response);
    }
}

void Communicator::OfflineProcess(QJsonObject &obj)
{
    QString account = obj["account"].toString();
    if (DatabaseManager::instance()->Contains(account)) {
        auto netizen = DatabaseManager::instance()->GetNetizen(account);
        if (netizen->IsOnline()) {
            netizen->SetOnline(false);
            qDebug() << account << " went offline";
        }
    }
}

void Communicator::OnNewTcpConnection()
{

}
