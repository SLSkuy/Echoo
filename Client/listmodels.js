

var friendlistModel;
var messagelistModel;


function friendlistModelinit(listmodel){
    friendlistModel = listmodel
}

function messagelistModelinit(listmodel){
    messagelistModel = listmodel
}

function addFriend(user) {
    // 添加到好友列表
    friendlistModel.append({
        headPortrait: "data:image/png;base64," + user.avatar,
        name: user.nickname,
        account: user.account,
        // s1: 0
    });
}

function addMessagelist(user, message) {
    // 添加到好友列表
    messagelistModel.append({
         picture: "data:image/png;base64," + user.avatar,
        name: user.nickname,
         lastMessage: message[message.length-1].content,
        time: message[message.length-1].timestamp,
                                                                                                      unreadCount: 0,_isGroup: 0, account: user.account
    });
}

function clearfriendModel(modelName) {
    modelName.clear();

}

function clearmessageModel(modelName) {
    modelName.clear();

}


