

// var friendlistModel;
var messagelistModel;

var friendlistModel;


function friendlistModelinit(listmodel){
    friendlistModel = listmodel
}

function messagelistModelinit(listmodel){
    messagelistModel = listmodel
}

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
    // 添加到消息列表
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


// Qt.include({
//     // models: models,
//     addFriend: addFriend,
//     addMessagelist: addMessagelist,
//     clearfriendModel: clearfriendModel,
//     clearmessageModel: clearmessageModel,
//     friendlistModelinit: friendlistModelinit,
//     messagelistModelinit: messagelistModelinit,
//     friendlistModel: friendlistModel,
//     messagelistModel: messagelistModel
// });


