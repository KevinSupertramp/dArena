#include "Server/WorldSession.h"
#include "Configuration/ConfigMgr.h"
#include "Utils/Util.h"

void WorldSession::HandleClientVersion(WorldPacket& packet)
{
    quint8 version;
    quint16 revision;
    QString build;

    packet >> version;
    packet >> revision;
    build = packet.ReadString();

    QString clientVersion = QString(QString::number(version) + "." + QString::number(revision));

    if (clientVersion != ConfigMgr::Instance()->GetWorldConfig()->GetQString("AcceptClientVersion"))
    {
        QStringList version = ConfigMgr::Instance()->GetWorldConfig()->GetQString("AcceptClientVersion").split(".");
        WorldPacket data(SMSG_INVALID_CLIENT_VERSION);
        data << (quint8)version.at(0).toUShort();
        data << (quint16)version.at(1).toUShort();
        SendPacket(data);

        // To be checked
        OnClose();
    }
}

void WorldSession::HandleClientAuthentication(WorldPacket& packet)
{
    QString login, password;

    login = packet.ReadString();
    password = packet.ReadString();

    QSqlQuery result = Database::Auth()->Query(SELECT_ACCOUNT_BY_LOGIN_DETAILS, QVariantList() << login << password);

    if (!result.first())
    {
        SendLoginResult(LOGIN_RESULT_INVALID_LOGIN);
        return;
    }

    QSqlRecord fields = result.record();
    m_accountInfos.id = result.value(fields.indexOf("account_id")).toULongLong();
    m_accountInfos.login = result.value(fields.indexOf("login")).toString();
    m_accountInfos.coachGuid = result.value(fields.indexOf("coach_guid")).toBool();

    SendReconnectionTicket();
    SendLoginResult(LOGIN_RESULT_SUCCESS);

    if (!m_accountInfos.coachGuid)
    {
        WorldPacket data(SMSG_COACH_CREATION_REQUEST);
        SendPacket(data);
        return;
    }

    SendCoachInformation();
}

void WorldSession::HandleClientDisconnect(WorldPacket& /*packet*/)
{
    OnClose();
}

void WorldSession::HandleReconnectionTicket(WorldPacket& packet)
{
    qDebug() << "Reconnection ticket : " << packet.ReadString();
}

void WorldSession::SendLoginResult(LoginResult result)
{
    WorldPacket data(SMSG_CLIENT_AUTHENTICATION_RESULTS);
    data << quint8(result);
    SendPacket(data);
}

void WorldSession::SendReconnectionTicket()
{
    // Disabled feature for now.
    /*WorldPacket data(SMSG_RECONNECTION_TICKET);
    data << quint8(25);
    data << "1234567890123456789012345";
    SendPacket(data);*/
}
