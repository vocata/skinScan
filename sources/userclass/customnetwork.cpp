#include "customnetwork.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSettings>

CustomNetwork::CustomNetwork(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

QVariantMap CustomNetwork::userInfo()
{
    QVariantMap result;

    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(m_userInfo.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (!(jsonDocument.isNull() || jsonDocument.isEmpty())) {
            if (jsonDocument.isObject()) {
                result = jsonDocument.toVariant().toMap();
            }
        }
    }
    return result;
}

QVariantMap CustomNetwork::userData()
{
    QVariantMap result;

    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(m_userData.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (!(jsonDocument.isNull() || jsonDocument.isEmpty())) {
            if (jsonDocument.isObject()) {
                result = jsonDocument.toVariant().toMap();
            }
        }
    }

    return result;
}

void CustomNetwork::memberLogin(const QString &account, const QString &password)
{
    m_accountTemp = account;
    m_passwordTemp = password;
    QByteArray content = QString("phone=%1&password=%2").arg(m_accountTemp, m_passwordTemp).toUtf8();
    int contentLength = content.length();

    /* request */
    QNetworkRequest loginRequest(QUrl("http://123.207.109.164/account/login"));
    loginRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    loginRequest.setHeader(QNetworkRequest::ContentLengthHeader, contentLength);

    m_loginReply = m_manager->post(loginRequest, content);
    connect(m_loginReply, &QNetworkReply::finished, this, &CustomNetwork::m_loginStatus);
}

void CustomNetwork::memberRegister(const QString &account, const QString &password, const QString &user)
{
    QByteArray content(QString("phone=%1&password=%2&name=%3").arg(account, password, user).toUtf8());
    int contentLength = content.length();

    /* request */
    QNetworkRequest registerRequest(QUrl("http://123.207.109.164/account/register"));
    registerRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    registerRequest.setHeader(QNetworkRequest::ContentLengthHeader, contentLength);

    m_registerReply = m_manager->post(registerRequest, content);
    connect(m_registerReply, &QNetworkReply::finished, this, &CustomNetwork::m_registorStatus);
}

void CustomNetwork::getUserInfo()
{
    /* request */
    QNetworkRequest getUserInfoRequest(QUrl(QString("http://123.207.109.164/users/%1").arg(m_loginInfo.m_account)));
    getUserInfoRequest.setHeader(QNetworkRequest::CookieHeader, m_loginInfo.m_cookie);

    m_getUserInfoReply = m_manager->get(getUserInfoRequest);
    connect(m_getUserInfoReply, &QNetworkReply::finished, this, &CustomNetwork::m_getUserInfoStatus);
}

void CustomNetwork::updateUserInfo(const QVariantMap &userInfo, const QString &account)
{
    QString info = QString("phone=%1&qq=%2&email=%3&sex=%4&birthday=%5&age=%6&name=%7")
                    .arg(account,
                         userInfo.value("qq").toString(), userInfo.value("email").toString(),
                         userInfo.value("sex").toString(), userInfo.value("birthday").toString(),
                         userInfo.value("age").toString(), userInfo.value("name").toString());
    QByteArray content(info.toUtf8());
    int contentLength = content.length();

    /* request */
    QNetworkRequest updateUserInfoRequest(QUrl(QString("http://123.207.109.164/users/%1").arg(m_loginInfo.m_account)));
    updateUserInfoRequest.setHeader(QNetworkRequest::CookieHeader, m_loginInfo.m_cookie);
    updateUserInfoRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    updateUserInfoRequest.setHeader(QNetworkRequest::ContentLengthHeader, contentLength);

    m_updateUserInfoReply = m_manager->put(updateUserInfoRequest, content);
    connect(m_updateUserInfoReply, &QNetworkReply::finished, this, &CustomNetwork::m_updateUserInfoStatus);
}

void CustomNetwork::uploadSingleUserData(const QString &item, const QJsonDocument &userData)
{
    QByteArray content(userData.toJson());
    int contentLength = content.length();

    /* request */
    QNetworkRequest uploadUserDataRequest(QUrl(QString("http://123.207.109.164/skindata/%1/%2").arg(item, m_loginInfo.m_account)));
    uploadUserDataRequest.setHeader(QNetworkRequest::CookieHeader, m_loginInfo.m_cookie);
    uploadUserDataRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    uploadUserDataRequest.setHeader(QNetworkRequest::ContentLengthHeader, contentLength);

    m_uploadUserDataReply = m_manager->post(uploadUserDataRequest, content);
    connect(m_uploadUserDataReply, &QNetworkReply::finished, this, &CustomNetwork::m_uploadUserInfoStatus);
}

void CustomNetwork::uploadUserData(const QJsonDocument &userData)
{
    QByteArray content(userData.toJson());
    int contentLength = content.length();

    /* request */
    QNetworkRequest uploadUserDataRequest(QUrl(QString("http://123.207.109.164/skindata/%1").arg(m_loginInfo.m_account)));
    uploadUserDataRequest.setHeader(QNetworkRequest::CookieHeader, m_loginInfo.m_cookie);
    uploadUserDataRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    uploadUserDataRequest.setHeader(QNetworkRequest::ContentLengthHeader, contentLength);

    m_uploadUserDataReply = m_manager->post(uploadUserDataRequest, content);
    connect(m_uploadUserDataReply, &QNetworkReply::finished, this, &CustomNetwork::m_uploadUserInfoStatus);
}

void CustomNetwork::downloadUserData()
{
    /* request */
    QNetworkRequest downloadUserDataRequest(QUrl(QString("http://123.207.109.164/skindata/%1").arg(m_loginInfo.m_account)));
    downloadUserDataRequest.setHeader(QNetworkRequest::CookieHeader, m_loginInfo.m_cookie);

    m_downloadUserDataReply = m_manager->get(downloadUserDataRequest);
    connect(m_downloadUserDataReply, &QNetworkReply::finished, this, &CustomNetwork::m_downloadUserDataStatus);
}

void CustomNetwork::clear()
{
    m_loginInfo.m_account.clear();
    m_loginInfo.m_password.clear();
    m_loginInfo.m_cookie.clear();
    m_loginInfo.saveInfo();
}

void CustomNetwork::m_loginStatus()
{
    /* request timeout */
    if(m_loginReply->error() == QNetworkReply::UnknownNetworkError) {
        emit memberLoginStatus(Timeout);
    } else {
        /* judge status */
        bool isVaild = false;
        int statusCode = m_loginReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(&isVaild);
        if(!isVaild) {
            emit memberLoginStatus(Timeout);
        } else {
            switch(statusCode) {
            case 200:
                m_loginInfo.m_cookie = m_loginReply->header(QNetworkRequest::SetCookieHeader);
                m_loginInfo.m_account = m_accountTemp;
                m_loginInfo.m_password = m_passwordTemp;
                m_loginInfo.saveInfo();
                emit memberLoginStatus(Success);
                break;
            default: emit memberLoginStatus(Failure); break;
            }
        }
    }
    disconnect(m_loginReply, &QNetworkReply::finished, this, &CustomNetwork::m_loginStatus);
}

void CustomNetwork::m_registorStatus()
{
    if(m_registerReply->error() == QNetworkReply::UnknownNetworkError) {
        emit memberRegisterStatus(Timeout);
    } else {
        bool isVaild = false;
        int statusCode = m_registerReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(&isVaild);
        if(!isVaild) {
            emit memberRegisterStatus(Timeout);
        } else {
            switch(statusCode) {
            case 200: emit memberRegisterStatus(Success); break;
            default: emit memberRegisterStatus(Failure); break;
            }
        }
    }
    disconnect(m_registerReply, &QNetworkReply::finished, this, &CustomNetwork::m_registorStatus);
}

void CustomNetwork::m_getUserInfoStatus()
{
    if(m_getUserInfoReply->error() == QNetworkReply::UnknownNetworkError) {
        emit getUserInfoStatus(Timeout);
    } else {
        bool isVaild = false;
        int statusCode = m_getUserInfoReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(&isVaild);
        if(!isVaild) {
            emit getUserInfoStatus(Timeout);
        } else {
            switch(statusCode) {
            case 200: {
                m_userInfo = m_getUserInfoReply->readAll();
                QVariantMap userInfo = QJsonDocument::fromJson(m_userInfo.toUtf8()).toVariant().toMap();
                /* save user information */
                QSettings settings("conf.ini", QSettings::IniFormat);
                settings.beginGroup("normal");
                settings.setValue("account", userInfo.value("phone"));
                settings.setValue("user", userInfo.value("name"));
                settings.setValue("sex", userInfo.value("sex"));
                settings.endGroup();

                emit getUserInfoStatus(Success);
            }
                break;
            default: emit getUserInfoStatus(Failure); break;
            }
        }
    }
    disconnect(m_getUserInfoReply, &QNetworkReply::finished, this, &CustomNetwork::m_getUserInfoStatus);
}

void CustomNetwork::m_updateUserInfoStatus()
{
    if(m_updateUserInfoReply->error() == QNetworkReply::UnknownNetworkError) {
        emit updateUserInfoStatus(Timeout);
    } else {
        bool isVaild = false;
        int statusCode = m_updateUserInfoReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(&isVaild);
        if(!isVaild) {
            emit updateUserInfoStatus(Timeout);
        } else {
            switch(statusCode) {
            case 200: emit updateUserInfoStatus(Success); break;
            default: emit updateUserInfoStatus(Failure); break;
            }
        }
    }
    disconnect(m_updateUserInfoReply, &QNetworkReply::finished, this, &CustomNetwork::m_updateUserInfoStatus);
}

void CustomNetwork::m_uploadUserInfoStatus()
{
    if(m_uploadUserDataReply->error() == QNetworkReply::UnknownNetworkError) {
        emit uploadUserDataStatus(Timeout);
    } else {
        bool isVaild = false;
        int statusCode = m_uploadUserDataReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(&isVaild);
        qDebug() << statusCode;
        if(!isVaild) {
            emit uploadUserDataStatus(Timeout);
        } else {
            switch(statusCode) {
            case 200: emit uploadUserDataStatus(Success); break;
            default: emit uploadUserDataStatus(Failure); break;
            }
        }
    }
    disconnect(m_uploadUserDataReply, &QNetworkReply::finished, this, &CustomNetwork::m_uploadUserInfoStatus);
}

void CustomNetwork::m_downloadUserDataStatus()
{
    if(m_downloadUserDataReply->error() == QNetworkReply::UnknownNetworkError) {
        emit downloadUserDataStatus(Timeout);
    } else {
        bool isVaild = false;
        int statusCode = m_downloadUserDataReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(&isVaild);
        if(!isVaild) {
            emit downloadUserDataStatus(Timeout);
        } else {
        switch(statusCode) {
            case 200:
                m_userData = m_downloadUserDataReply->readAll();
                emit downloadUserDataStatus(Success);
                break;
            default: emit downloadUserDataStatus(Failure); break;
            }
        }
    }
    disconnect(m_downloadUserDataReply, &QNetworkReply::finished, this, &CustomNetwork::m_getUserInfoStatus);
}

LoginInfo CustomNetwork::m_loginInfo;

/* friend class function */

LoginInfo::LoginInfo()
{
    QSettings settings("conf.ini", QSettings::IniFormat);
    settings.beginGroup("special");
    m_account = settings.value("account").toString();
    QString cryptPassword = settings.value("password").toString();
    m_password = QByteArray::fromBase64(cryptPassword.toLatin1());      //解密
    settings.endGroup();

    /* read cookie */
    settings.beginGroup("special/cookie");
    QString cookieName = settings.value("name").toString();
    QString cookieValue = settings.value("value").toString();
    settings.endGroup();
    QList<QNetworkCookie> rawCookie;
    rawCookie << QNetworkCookie(cookieName.toUtf8(), cookieValue.toUtf8());
    m_cookie.setValue(rawCookie);
}

LoginInfo::~LoginInfo()
{
    this->saveInfo();
}

void LoginInfo::saveInfo()
{
    QSettings settings("conf.ini", QSettings::IniFormat);
    settings.beginGroup("special");
    settings.setValue("account", m_account);
    QByteArray cryptPassword = m_password.toLatin1().toBase64();     //加密
    settings.setValue("password", QString(cryptPassword));
    settings.endGroup();

    /* save cookie */
    QList<QNetworkCookie> rawCookie = m_cookie.value<QList<QNetworkCookie>>();
    QString cookieName;
    QString cookieValue;
    if(!rawCookie.isEmpty()) {
        cookieName= rawCookie.at(0).name();
        cookieValue = rawCookie.at(0).value();
    }
    settings.beginGroup("special/cookie");
    settings.setValue("name", cookieName);
    settings.setValue("value", cookieValue);
    settings.endGroup();
}
