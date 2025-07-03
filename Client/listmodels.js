

var friendlistModel;
var messagelistModel;


function friendlistModelinit(listmodel){
    friendlistModel = listmodel
}

function messagelistModelinit(listmodel){
    messagelistModel = listmodel
}

function addFriend(user) {
    console.log("avatar prefix:", user.avatar?.slice(0, 50));
    // 添加到好友列表
    let avatar = user.avatar;

    friendlistModel.append({
        headPortrait: avatar,
        name: user.nickname,
        account: user.account,
        // sign: user.sign,
        // s1: 0
    });
}

function addMessagelist(user, message) {
    // console.log("avatar prefix:", user.avatar?.slice(0, 50));
    // 添加到消息列表
    let avatar = user.avatar;
    let lastMsg = message.length > 0 ? message[message.length-1] : {content: "", timestamp: ""};

    messagelistModel.append({
        picture: avatar,
        name: user.nickname,
        lastMessage: lastMsg.content,
        time: lastMsg.timestamp,
        unreadCount: 0,
        _isGroup: 0,
        account: user.account
    });
}

function clearfriendModel(modelName) {
    modelName.clear();

}

function clearmessageModel(modelName) {
    modelName.clear();

}


