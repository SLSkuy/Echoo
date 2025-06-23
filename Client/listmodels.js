

// var friendlistModel;
var messagelistModel;

var friendlistModel = Qt.createQmlObject(`
    import QtQuick 2.15
    ListModel {}
`, Qt.application);


function friendlistModelinit(listmodel){
    friendlistModel = listmodel
}

function messagelistModelinit(listmodel){
    messagelistModel = listmodel
}

// 2. 添加好友到不同 Model 的方法
function addFriend(user) {
    // 添加到好友列表
    friendlistModel.append({
        headPortrait: user.avatar,
        name: user.nickname,
        account: user.account,
        // s1: 0
    });
}

function addMessagelist(user, message) {
    // 添加到好友列表
    messagelistModel.append({
         picture: user.avatar,
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




// 4. 暴露接口给 QML
Qt.include({
    // models: models,
    addFriend: addFriend,
    addMessagelist: addMessagelist,
    clearfriendModel: clearfriendModel,
    clearmessageModel: clearmessageModel,
    friendlistModelinit: friendlistModelinit,
    messagelistModelinit: messagelistModelinit,
    friendlistModel: friendlistModel,
               // models: models,
    messagelistModel, messagelistModel
});


