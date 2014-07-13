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

    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));
    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toLatin1().data());
}

WorldSession::~WorldSession()
{
    qDebug() << "delete m_character";
    delete m_coach;
}

void WorldSession::ProcessPacket()
{
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
            Log::Write(LOG_TYPE_DEBUG, "Received packet opcode %s <%u> (size : %u).", opcodeHandler.name.toLatin1().data(), opcode, data.size());

            WorldPacket packet(opcode, data);
            (this->*opcodeHandler.handler)(packet);
        }
        else
            Log::Write(LOG_TYPE_DEBUG, "Received unhandled packet <%u> (size : %u).", opcode, data.size());

        m_packetSize = 0;
    }
}

void WorldSession::OnClose()
{
    Coach* coach = GetCoach();
    if (coach)
    {
        coach->SaveToDB();
        qDebug() << "Character " << coach->GetName() << " saved to DB.";
    }

    World::Instance()->RemoveSession(this);
    SocketHandler::OnClose();
}
