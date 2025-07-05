// Communicator类实现
// 该类用于实现局域网网络通信
// 使用UDP广播发现消息
// TCP连接进行消息传输

#include "messageprocessor.h"
#include "udpbroadcaster.h"
#include "messagesender.h"
#include "communicator.h"
#include "tcpmanager.h"
#include "netizen.h"
#include "message.h"
#include "group.h"

Communicator::Communicator(Netizen *user) : _user(user),QObject(user)
{
    // 初始化各子模块
    _tm = new TcpManager(this);
    _ub = new UdpBroadcaster(user);
    _msgProcessor = new MessageProcessor(this);
    _msgSender = new MessageSender(_tm);
}

Communicator::~Communicator()
{
    _msgSender->deleteLater();
    _msgProcessor->deleteLater();
    _tm->deleteLater();
    _ub->deleteLater();
}

void Communicator::signalsConnect()
{
    // 消息接收信号
    connect(_msgProcessor,&MessageProcessor::messageReceived,this,&Communicator::messageReceived);
    connect(_msgProcessor,&MessageProcessor::groupMessageReceived,this,&Communicator::groupMessageReceived);
    connect(_msgProcessor,&MessageProcessor::commandReceived,this,&Communicator::commandReceived);
    connect(_msgProcessor,&MessageProcessor::imageReceived,this,&Communicator::imageReceived);

    // 消息处理信号
    connect(_tm,&TcpManager::messageReceived,_msgProcessor,&MessageProcessor::messageProcess);
    connect(_tm,&TcpManager::offlineMessageProcess,_msgSender,&MessageSender::sendOfflineMessage);

    // 账号在线处理
    connect(_ub,&UdpBroadcaster::userOnline,_tm,&TcpManager::onlineProcess);
    connect(_ub,&UdpBroadcaster::userOffline,_tm,&TcpManager::offlineProcess);
}

void Communicator::sendMessage(Message *message)
{
    _msgSender->sendMessage(message);
}

void Communicator::sendGroupMessage(Message *message)
{
    _msgSender->sendGroupMessage(message);
}

QString Communicator::getLocalIP()
{
    return _ub->getLocalIP();
}
