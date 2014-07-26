#include "WorldSession.h"
#include "Opcodes/Opcodes.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"
#include "World/World.h"

WorldSession::WorldSession(QTcpSocket *socket) : SocketHandler(socket)
{
    m_accountInfos.id           = 0;
    m_accountInfos.login        = QString();
    m_accountInfos.coachGuid    = 0;

    SetCoach(NULL);

    m_logout = false;

    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));
    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toLatin1().data());
}

WorldSession::~WorldSession()
{
    LogoutPlayer();
}

void WorldSession::ProcessPacket()
{
    if (m_logout)
        return;

    QDataStream in(m_socket);

    while (m_socket->bytesAvailable())
    {
        if (m_packetSize == 0)
        {
            if (m_socket->bytesAvailable() < (qint64)sizeof(quint16))
                return;

            in >> m_packetSize;
        }

        if ((m_socket->bytesAvailable()) < (m_packetSize - 2))
            return;

        qint8 unk;
        quint16 opcode;
        QByteArray data;

        in >> unk;
        in >> opcode;
        data = in.device()->read((qint64)(m_packetSize - 5));

        if (OpcodeTable::Exists(opcode))
        {
            OpcodeHandler opcodeHandler = OpcodeTable::Get(opcode);
            WorldPacket packet(opcode, data);

            switch (opcodeHandler.status)
            {
            case STATUS_UNHANDLED:
                Log::Write(LOG_TYPE_DEBUG, "Received unhandled packet <%u> (size : %u).", opcode, data.size());
                break;
            case STATUS_NEVER:
                Log::Write(LOG_TYPE_DEBUG, "Received not allowed packet <%u> (size : %u).", opcode, data.size());
                break;
            default:
                if (opcodeHandler.status == STATUS_ALWAYS ||
                   (opcodeHandler.status == STATUS_AUTHED && GetAccountInfos().id != 0) ||
                   (opcodeHandler.status == STATUS_IN_WORLD && (GetCoach() && GetCoach()->IsInWorld())))
                {
                    (this->*opcodeHandler.handler)(packet);
                    Log::Write(LOG_TYPE_DEBUG, "Received packet opcode %s <%u> (size : %u).", opcodeHandler.name.toLatin1().data(), opcode, data.size());
                }
                else
                {
                    // Todo
                }
                break;
            }
        }
        else
            Log::Write(LOG_TYPE_DEBUG, "Received unhandled packet <%u> (size : %u).", opcode, data.size());

        m_packetSize = 0;
    }
}

void WorldSession::OnClose()
{
    LogoutPlayer();
}

void WorldSession::LogoutPlayer(bool save)
{
    m_logout = true;

    if (m_coach)
    {
        if (save)
            m_coach->SaveToDB();

        delete m_coach;
        SetCoach(NULL);
    }

    World::Instance()->RemoveSession(this);
    SocketHandler::OnClose();
}
