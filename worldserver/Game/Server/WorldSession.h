#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include "Databases/Database.h"
#include "Define.h"
#include "Network/SocketHandler.h"
#include "Entities/Coach/Coach.h"
#include "World/World.h"

enum LoginResult
{
    LOGIN_RESULT_SUCCESS                    = 0,
    LOGIN_RESULT_INVALID_LOGIN              = 2,
    LOGIN_RESULT_ALREADY_CONNECTED          = 3,
    LOGIN_RESULT_SAVE_IN_PROGRESSS          = 4,
    LOGIN_RESULT_CLOSED_BETA                = 127
};

struct sAccountInfos
{
    quint64 id;
    QString login;
    quint64 coachGuid;
};

class Coach;

class WorldSession : public SocketHandler
{
    Q_OBJECT
public:
    WorldSession(QTcpSocket* socket);
    ~WorldSession();

    sAccountInfos GetAccountInfos() { return m_accountInfos; }

    void SetCoach(Coach* coach) { m_coach = coach; }
    Coach* GetCoach() const { return m_coach; }

    virtual void ProcessPacket();

    // Default handlers
    void HandleNULL(WorldPacket& /*packet*/) {}
    void HandleServerSide(WorldPacket& /*packet*/) {}

    // CMSG Handlers
    void HandleClientDisconnect(WorldPacket& /*packet*/);
    void HandleClientVersion(WorldPacket& packet);
    void HandleReconnectionTicket(WorldPacket& packet);
    void HandleClientAuthentication(WorldPacket& packet);
    void HandleCoachCreation(WorldPacket& packet);

    void HandleChatMessage(WorldPacket& packet);
    void HandlePrivateMessage(WorldPacket& packet);
    void HandleCharMovement(WorldPacket& packet);

    // SMSG Handlers
    void SendLoginResult(LoginResult result);
    void SendReconnectionTicket();
    void SendCoachInformation();
    void SendEnterInstance();

public slots:
    void OnClose();

private:
    sAccountInfos m_accountInfos;
    Coach* m_coach;
};

#endif // WORLDSESSION_H