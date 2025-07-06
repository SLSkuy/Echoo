#include <QFile>
#include <QStandardPaths>
#include <QUrl>

#include "userprofilemanager.h"
#include "netizen.h"
#include "logger.h"

UserProfileManager::UserProfileManager(QString nickname,Netizen *parent)
    :QObject(parent)
    ,_owner(parent)
    ,m_nickname(nickname)
{}

UserProfileManager::~UserProfileManager()
{
    // 析构时清楚头像缓存文件
    cleanupAvatarTempFile();
}

void UserProfileManager::setNickname(const QString &nickname)
{
    if(nickname != m_nickname)
    {
        m_nickname = nickname;
        emit nicknameChanged();
    }
}

void UserProfileManager::setSign(const QString &sign)
{
    if(sign != m_sign)
    {
        m_sign = sign;
        emit signChanged();
    }
}

void UserProfileManager::updateAvatar(const QString &base64)
{
    if(m_avatar != base64)
    {
        m_avatar = base64;
        emit avatarChanged();
    }
}

void UserProfileManager::setAvatarFromFile(const QString &filePath)
{
    QString path = QUrl(filePath).toLocalFile();    // 转换为本地路径

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        Logger::error() << "Can't open image: "  << filePath;
        return;
    }

    QByteArray imageData = file.readAll();
    file.close();

    if (imageData.isEmpty()) {
        Logger::error() << "Image file is empty: " << filePath;
        return;
    }

    // 读取魔数判断图片格式
    QString imageType;
    if (imageData.startsWith("\x89PNG")) {
        imageType = "png";
    } else if (imageData.startsWith("\xFF\xD8\xFF")) {
        imageType = "jpeg";
    } else {
        Logger::error() << "Unsupported image format: " + filePath;
        return;
    }

    // 自动设置图片解析前缀
    QString base64 = QString::fromLatin1(imageData.toBase64());
    m_avatar = QString("data:image/%1;base64,%2").arg(imageType, base64);
}

QString UserProfileManager::generateAvatarTmpFile()
{
    // 检测是否已经存在了缓存头像
    if (!m_cachedAvatarFilePath.isEmpty() && QFile::exists(m_cachedAvatarFilePath)) {
        Logger::log() << "Using cached avatar: " << m_cachedAvatarFilePath;
        return "file:///" + m_cachedAvatarFilePath;
    }

    // 检测是否为base64格式
    if (!m_avatar.startsWith("data:image/"))
    {
        Logger::warning() << "Failed to read base64.";
        return NULL;
    }

    // 检测base64编码索引
    int base64Index = m_avatar.indexOf("base64,");
    if (base64Index < 0)
        return NULL;

    // 检测图片格式
    QString type = m_avatar.mid(11, m_avatar.indexOf(";") - 11);
    QString ext = type == "jpeg" ? "jpg" : type;

    QByteArray base64Data = m_avatar.mid(base64Index + 7).toUtf8();
    QByteArray imageData = QByteArray::fromBase64(base64Data);

    // 临时存储在系统默认TMP文件夹中
    QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/avatar_temp" + _owner->getAccount() + "." + ext;

    QFile file(tempPath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(imageData);
        file.close();

        // 保存路径以供清理
        m_cachedAvatarFilePath = tempPath;
        return "file:///" + tempPath;
    }

    Logger::warning() << "Failed to write avatar image to temp file.";
    return NULL;
}

void UserProfileManager::cleanupAvatarTempFile()
{
    if (m_cachedAvatarFilePath.isEmpty()) {
        Logger::log() << "No cached avatar path set.";
        return;
    }

    QFile file(m_cachedAvatarFilePath);
    if (file.exists()) {
        bool success = file.remove();
        if (success)
            Logger::log() << "Avatar file deleted: " << m_cachedAvatarFilePath;
        else
            Logger::warning() << "Failed to delete avatar file.";
    } else {
        Logger::log() << "Temp file does not exist: " << m_cachedAvatarFilePath;
    }
}
