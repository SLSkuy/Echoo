// 用户资料类
// 用于记录用户昵称、签名、头像等信息

#pragma once

#include <QObject>
#include <QString>

class UserProfileManager : public QObject {
    Q_OBJECT
public:
    UserProfileManager(QString nickname,QObject *parent = nullptr);
    ~UserProfileManager();

    // 基础资料获取操作
    QString nickname() { return m_nickname; }
    QString sign() { return m_sign; }
    QString avatar() { return m_avatar; }
    QString avatarTmpFilePath() { return generateAvatarTmpFile(); }
    void setNickname(const QString &nickname);
    void setSign(const QString &sign);
    void updateAvatar(const QString &base64);

    // 更新与管理
    void setAvatarFromFile(const QString &filePath);    // 本地选择图片进行更新
    QString generateAvatarTmpFile();
    void cleanupAvatarTempFile();

signals:
    void nicknameChanged();
    void signChanged();
    void avatarChanged();

private:
    QString m_nickname;
    QString m_sign;
    QString m_avatar;
    QString m_cachedAvatarFilePath;
};
