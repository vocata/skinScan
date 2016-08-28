#ifndef CUSTOMNETWORK_H
#define CUSTOMNETWORK_H

#include <QMultiMap>
#include <QNetworkCookie>
#include <QVariant>

#include <QDebug>

class QNetworkAccessManager;
class QNetworkReply;


class LoginInfo
{
    friend class CustomNetwork;
public:
    LoginInfo();
    ~LoginInfo();
private:
    QString m_account;
    QString m_password;
    QVariant m_cookie;
};

class CustomNetwork : public QObject
{
    Q_OBJECT
public:
    enum Status{ Failure, Success, Timeout };

    explicit CustomNetwork(QObject *parent = 0);
    QVariantMap userInfo();
    QVariantMap userData();
    QString account() const
    {
        return m_loginInfo.m_account;
    }

    bool hasMember() const
    {
        return !m_loginInfo.m_account.isEmpty();
    }

signals:
    void memberLoginStatus(Status status);
    void memberRegisterStatus(Status status);
    void getUserInfoStatus(Status status);
    void updateUserInfoStatus(Status status);
    void uploadUserDataStatus(Status status);
    void downloadUserDataStatus(Status status);

public slots:
    void memberLogin(const QString &account, const QString &password);
    void memberRegister(const QString &account, const QString &password, const QString &user);
    void getUserInfo();
    void updateUserInfo(const QVariantMap &userInfo);
    void uploadUserData(const QJsonDocument &userData);
    void downloadUserData();
    void clear();


private:
    QNetworkAccessManager *m_manager = nullptr;
    QNetworkReply *m_loginReply = nullptr;
    QNetworkReply *m_registerReply = nullptr;
    QNetworkReply *m_getUserInfoReply = nullptr;
    QNetworkReply *m_updateUserInfoReply = nullptr;
    QNetworkReply *m_uploadUserDataReply = nullptr;
    QNetworkReply *m_downloadUserDataReply = nullptr;

    QString m_userInfo;
    QString m_userData;
    QString m_accountTemp;
    QString m_passwordTemp;

    static LoginInfo m_loginInfo;

private slots:
    void m_loginStatus();
    void m_registorStatus();
    void m_getUserInfoStatus();
    void m_updateUserInfoStatus();
    void m_uploadUserInfoStatus();
    void m_downloadUserDataStatus();
};

QJsonObject formatUploadDataFromSQl(const QString &type, const QList<QVariantList> &rawData);
#endif // CUSTOMNETWORK_H
