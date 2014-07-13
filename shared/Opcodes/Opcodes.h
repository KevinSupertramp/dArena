#ifndef OPCODES_H
#define OPCODES_H

#include <QtCore>

class WorldPacket;
class WorldSession;

enum Opcodes
{
    // Client messages (CMSG)
    CMSG_DISCONNECTION                          = 1,
    CMSG_CLIENT_VERSION                         = 7,
    CMSG_RECONNECTION_TICKET                    = 33,
    CMSG_AUTHENTICATION                         = 1025,
    CMSG_COACH_CREATION                         = 2049,
    CMSG_COACH_MOVEMENT                         = 4501,

    // Server messages (SMSG)
    SMSG_RECONNECTION_TICKET                    = 2,
    SMSG_CLIENT_INVALID_VERSION                 = 8,
    SMSG_AUTHENTICATION_RESULT                  = 1024,
    SMSG_COACH_CREATION_REQUEST                 = 2048,
    SMSG_COACH_CREATION_RESULT                  = 2050,
    SMSG_COACH_INFORMATION                      = 2052,
    SMSG_ACTOR_MOVEMENT                         = 4500,
    SMSG_ENTER_INSTANCE                         = 4600
};

struct OpcodeHandler
{
    QString name;
    void (WorldSession::*handler)(WorldPacket& packet);
};

typedef void(WorldSession::*opcodeHandler)(WorldPacket& packet);
typedef QMap<Opcodes, OpcodeHandler> OpcodesList;

class OpcodeTable
{
public:
    static void Load();

    static void Add(quint16 opcode, char const* name, opcodeHandler handler)
    {
        OpcodeHandler opcodeHandler;
        opcodeHandler.name = QString(name);
        opcodeHandler.handler = handler;

        opcodesList.insert(Opcodes(opcode), opcodeHandler);
    }

    static bool Exists(quint16 id)
    {
        return opcodesList.contains((Opcodes)id);
    }

    static OpcodeHandler Get(quint16 id)
    {
        return opcodesList.value((Opcodes)id);
    }

private:
    static OpcodesList opcodesList;
};

inline QString GetOpcodeName(quint16 id)
{
    if (!OpcodeTable::Exists(id))
        return "Unknown opcode";

    return OpcodeTable::Get(id).name;
}

#endif
