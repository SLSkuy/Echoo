#include <QNetworkInterface>
#include <QJsonDocument>

#include "databasemanager.h"
#include "udpbroadcaster.h"
#include "netizen.h"
#include "logger.h"

UdpBroadcaster::UdpBroadcaster(Netizen *netizen): _netizen(netizen),QObject(netizen)
{
    _udpSocket = new QUdpSocket(this);
    _udpSocket->bind(QHostAddress::AnyIPv4,m_udpPort);
    connect(_udpSocket,&QUdpSocket::readyRead,this,&UdpBroadcaster::onUdpReadyRead);

    _timer = new QTimer(this);
    connect(_timer,&QTimer::timeout,this,&UdpBroadcaster::startBroadcast);
    connect(_timer,&QTimer::timeout,this,&UdpBroadcaster::checkTimeout);
    _timer->start(5000);    // 每5s广播一次在线消息
}

UdpBroadcaster::~UdpBroadcaster()
{
    _udpSocket->deleteLater();
    _timer->deleteLater();
}

QString UdpBroadcaster::getLocalIP()
{
    // 获取本机IP
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
            return address.toString();
        }
    }
    return QHostAddress(QHostAddress::LocalHost).toString();
}

void UdpBroadcaster::startBroadcast()
{
    // 定时发送在线消息
    QJsonObject response;
    response["nickName"] = _netizen->GetNickname();
    response["account"] = _netizen->GetAccount();
    response["online"] = true;
    response["ip"] = _netizen->GetIpAddress();
    response["avatar"] = _netizen->getAvatar();
    response["sign"] = _netizen->GetSign();
    QJsonDocument doc(response);
    _udpSocket->writeDatagram(doc.toJson(), QHostAddress::Broadcast, m_udpPort);
}

void UdpBroadcaster::checkTimeout()
{
    // 超过15秒未收到广播视为离线
    const int timeout = 15;

    QDateTime now = QDateTime::currentDateTime();
    QList<QString> toOffline;

    // 检测已超时未获取到在线广播的账号信息
    for (auto it = m_lastInfo.begin(); it != m_lastInfo.end(); ++it) {
        if (it.value().secsTo(now) > timeout) {
            toOffline.append(it.key());
        }
    }

    // 遍历获取需要删除的账号对象
    for (const QString &account : toOffline) {
        if (DatabaseManager::instance()->Contains(account)) {
            Netizen *netizen = DatabaseManager::instance()->GetNetizen(account);
            if (netizen->IsOnline()) {
                netizen->SetOnline(false);
                Logger::Log(account + " timeout offline.");

                // 发送用户离线信号
                QJsonObject obj;
                obj["account"] = account;
                obj["online"] = false;
                emit userOffline(obj);
            }
        }

        // 移除在线定时记录
        m_lastInfo.remove(account);
    }
}

void UdpBroadcaster::onUdpReadyRead()
{
    // 处理收到的广播消息
    // 读取连接队列中所有的Socket
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
                emit userOnline(obj);

                // 更新在线时间
                QString account = obj["account"].toString();
                m_lastInfo[account] = QDateTime::currentDateTime();
            } else {
                emit userOffline(obj);
            }
        }
    }
}
