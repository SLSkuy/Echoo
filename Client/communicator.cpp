// Communicator类实现
// 该类用于实现局域网网络通信
// 使用UDP广播发现消息
// TCP连接进行消息传输

#include <QHostAddress>

#include "communicator.h"

Communicator::Communicator()
{
    m_udpPort = 1145;
    m_tcpPort = 1145;

    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(QHostAddress::AnyIPv4,m_udpPort
                      ,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &Communicator::OnUdpReadyRead);
}

void Communicator::OnUdpReadyRead()
{

}
