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
    SMSG_RECONNECTION_TICKET_REQUEST_RESULT     = 4,
    SMSG_INVALID_CLIENT_VERSION                 = 8,

    SMSG_CLIENT_AUTHENTICATION_RESULTS = 1024,
    SMSG_WORLD_SERVER_UNAVAILABLE = 1026,
    SMSG_COACH_CREATION_REQUEST = 2048,
    SMSG_COACH_CREATION_RESULT = 2050,
    SMSG_COACH_INFORMATIONS = 2052,
    SMSG_OPPONENT_SEARCH_ERROR = 2302,
    SMSG_OPPONENT_FOUND = 2300,
    SMSG_OPPONENT_SEARCH_IN_PROGRESS = 2304,
    SMSG_OPPONENT_SEARCH_CANCEL_RESULT = 2306,
    SMSG_FIGHT_INVITATION = 4300,
    SMSG_FIGHT_INVITATION_ACCEPTED = 4302,
    SMSG_FIGHT_INVITATION_REJECTED = 4304,
    SMSG_FIGHT_INVITATION_ERROR = 4309,
    SMSG_FIGHT_CREATION_CANCELED = 4310,
    SMSG_PLAYER_STATISTICS_REPORT = 2400,
    SMSG_READY_FOR_FIGHT = 4306,
    SMSG_NO_INSTANCE_SERVER_AVAILABLE = 5000,
    SMSG_ENTER_INSTANCE = 4600,
    SMSG_COACH_INVENTORY_UPDATE = 5200,
    SMSG_COACH_EQUIPMENT_UPDATE = 5202,
    SMSG_ACTOR_SPAWN = 4096,
    SMSG_ACTOR_DESPAWN = 4098,
    SMSG_ACTOR_APPEAR = 4102,
    SMSG_ACTOR_DISAPEAR = 4104,
    SMSG_ACTOR_REPOSITION = 4106,
    SMSG_ACTOR_MOVEMENT = 4500,
    SMSG_ACTOR_TELEPORTS = 4510,
    SMSG_SAVE_TEAM_PRESET = 6020,
    SMSG_DELETION_TEAM_PRESET = 6022,
    SMSG_TEAM_PRESET_LIST = 6030,
    SMSG_FIGHTER_INFORMATION_LIST = 6006,
    SMSG_CREATION_FIGHTER_INFORMATION = 6000,
    SMSG_DELETION_FIGHTER_INFORMATION = 6002,
    SMSG_UPDATED_FIGHTER_INFORMATION_INVENTORY = 6010,
    SMSG_FIGHT_CREATION = 8000,
    SMSG_MOVE_TO_FREE_PLACEMENT = 8022,
    SMSG_START_PRESENTATION = 8010,
    SMSG_END_PRESENTATION = 8018,
    SMSG_TEAM_MATE_SET_READY_FOR_PLACEMENT = 8012,
    SMSG_START_PLACEMENT = 8020,
    SMSG_END_PLACEMENT = 8028,
    SMSG_TEAM_MATE_SET_READY_FOR_OBSERVATION = 8024,
    SMSG_START_OBSERVATION = 8030,
    SMSG_END_OBSERVATION = 8038,
    SMSG_TEAM_MATE_SET_READY_FOR_ACTION = 8032,
    SMSG_EFFECT_AREA_ACTION = 6200,
    SMSG_START_ACTION = 8040,
    SMSG_FIGHTER_TURN_BEGIN = 8104,
    SMSG_FIGHTER_TURN_END = 8106,
    SMSG_FIGHTER_DIES = 4520,
    SMSG_FIGHTER_MOVE = 4524,
    SMSG_NEW_TABLE_TURN_BEGIN = 8100,
    SMSG_FIGHTER_CHANGE_DIRECTION = 4522,
    SMSG_END_FIGHT = 8300,
    SMSG_ITEM_EXCHANGE_INVITATION = 5102,
    SMSG_ITEM_EXCHANGE_INVITATION_CONFIRMATION = 5104,
    SMSG_ITEM_EXCHANGE_CARD_ADDED = 5110,
    SMSG_ITEM_EXCHANGE_CARD_REMOVED = 5112,
    SMSG_ITEM_EXCHANGE_END = 5114,
    SMSG_ITEM_EXCHANGE_USER_READY = 5116,
    SMSG_FIGHT_ACTION_SEQUENCE_EXECUTE = 8200,
    SMSG_RUNNING_EFFECT_ACTION = 8120,
    SMSG_SPELL_CAST = 8110,
    SMSG_FIGHTER_TACKLED = 4506,
    SMSG_FIGHTER_CARD_USE = 8108,
    SMSG_CLOSE_COMBAT = 8112,
    SMSG_CHANNEL_FLAGS = 3128,
    SMSG_CHANNEL_JOIN = 3130,
    SMSG_CHANNEL_LEAVE = 3132,
    SMSG_CHANNEL_MEMBER_FLAGS = 3134,
    SMSG_CHANNEL_MEMBER_KICK = 3136,
    SMSG_CHANNEL_MEMBERS = 3138,
    SMSG_CHANNEL_CONTENT = 3140,
    SMSG_CHAT_USER_FLAGS = 3142,
    SMSG_FRIEND_LIST = 3144,
    SMSG_IGNORE_LIST = 3146,
    SMSG_NOTIFICATION_FRIEND_ONLINE = 3148,
    SMSG_NOTIFICATION_FRIEND_OFFLINE = 3150,
    SMSG_VICINITY_CONTENT = 3152,
    SMSG_PRIVATE_CONTENT = 3154,
    SMSG_FRIEND_ADDED = 3156,
    SMSG_FRIEND_REMOVED = 3160,
    SMSG_IGNORE_ADDED = 3158,
    SMSG_IGNORE_REMOVED = 3162,
    SMSG_CHANNEL_NOT_FOUND = 3202,
    SMSG_USER_NOT_FOUND = 3204,
    SMSG_MALFORMED_COMMAND = 3206,
    SMSG_MEMBER_NOT_FOUND = 3208,
    SMSG_NOT_ENOUGH_PRIVILEGES = 3210,
    SMSG_NOT_YET_IMPLEMENTED = 3212,
    SMSG_TARGET_IS_YOURSELF = 3214,
    SMSG_OPERATION_NOT_PERMITED = 3216,

    /*
     *         8192: new QueueNotificationMessage();
            8193 new ConsoleAdminCommandMessage();

           8194 new ConsoleAdminCommandResultMessage();
            8195 DefaultResultsMessage();
     */
};

enum OpcodeStatus
{
    STATUS_UNHANDLED = 0,
    STATUS_ALWAYS,
    STATUS_NEVER,
    STATUS_AUTHED,
    STATUS_IN_WORLD
};

struct OpcodeHandler
{
    QString name;
    OpcodeStatus status;
    void (WorldSession::*handler)(WorldPacket& packet);
};

typedef void(WorldSession::*opcodeHandler)(WorldPacket& packet);
typedef QMap<Opcodes, OpcodeHandler> OpcodesList;

class OpcodeTable
{
public:
    static void Load();

    static void Add(quint16 opcode, char const* name, OpcodeStatus status, opcodeHandler handler)
    {
        OpcodeHandler opcodeHandler;
        opcodeHandler.name = QString(name);
        opcodeHandler.status = status;
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
