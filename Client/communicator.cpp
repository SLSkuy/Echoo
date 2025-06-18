// Communicator类实现
// 该类用于实现局域网网络通信
// 使用UDP广播发现消息
// TCP连接进行消息传输

#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>

#include "communicator.h"
#include "databasemanager.h"
#include "logger.h"

Communicator::Communicator()
{
    m_udpPort = 1145;
    m_tcpPort = 1145;

    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(QHostAddress::AnyIPv4,m_udpPort
                      ,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &Communicator::OnUdpReadyRead);

    m_tcpServer = new QTcpServer(this);
    m_tcpServer->listen(QHostAddress::AnyIPv4, m_tcpPort);
    connect(m_tcpServer, &QTcpServer::newConnection, this, &Communicator::OnNewTcpConnection);
}

void Communicator::BroadcastPresence(QJsonObject &obj)
{
    // 客户端登录后，广播在线消息
    QJsonDocument doc(obj);
    m_udpSocket->writeDatagram(doc.toJson(),QHostAddress::Broadcast,m_udpPort);
}

void Communicator::OnUdpReadyRead()
{
    // 处理收到的广播消息
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(m_udpSocket->pendingDatagramSize()));
        QHostAddress senderAddr;
        quint16 senderPort;
        m_udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddr, &senderPort);

        // 转换为Json文档便于后续处理
        QJsonDocument doc = QJsonDocument::fromJson(datagram);
        if(!doc.isNull() && doc.isObject())
        {
            // 读取json内容
            QJsonObject obj = doc.object();
            QString nickName = obj["nickName"].toString();
            QString account = obj["account"].toString();

            Logger::Log("Account " + account + " online.");

            // 检测当前设备本地数据库是否存在广播者信息
            DatabaseManager *db = DatabaseManager::instance();
            if (db->Contains(account)) {
                // 存在该用户
                // 检测用户是否在线，若为否则标志为在线
                if (!db->GetNetizen(account)->IsOnline()) db->GetNetizen(account)->SetOnline();
            } else {
                // 不存在该用户，则添加
                Netizen *newUser = new Netizen(nickName, account, NULL, nullptr);
                newUser->SetOnline();
                db->AddNetizen(newUser);
            }
        }
    }
}

void Communicator::OnNewTcpConnection()
{

}
