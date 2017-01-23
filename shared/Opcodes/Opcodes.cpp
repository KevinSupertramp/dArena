#include "Opcodes.h"
#include "Server/WorldSession.h"

OpcodesList OpcodeTable::opcodesList;

void OpcodeTable::Load()
{
#define ADD_OPCODE_HANDLER(opcode, status, handler) \
    Add(opcode, #opcode, status, handler);

    // Client messages (CMSG)
    ADD_OPCODE_HANDLER(CMSG_DISCONNECTION,                 STATUS_AUTHED,      &WorldSession::HandleClientDisconnect);
    ADD_OPCODE_HANDLER(CMSG_CLIENT_VERSION,                STATUS_ALWAYS,      &WorldSession::HandleClientVersion);
    ADD_OPCODE_HANDLER(CMSG_RECONNECTION_TICKET,           STATUS_ALWAYS,      &WorldSession::HandleReconnectionTicket);
    ADD_OPCODE_HANDLER(CMSG_AUTHENTICATION,                STATUS_ALWAYS,      &WorldSession::HandleClientAuthentication);
    ADD_OPCODE_HANDLER(CMSG_COACH_CREATION,                STATUS_AUTHED,      &WorldSession::HandleCoachCreation);
    ADD_OPCODE_HANDLER(CMSG_COACH_MOVEMENT,                STATUS_IN_WORLD,    &WorldSession::HandleCoachMovement);

    // Server messages (SMSG)
    ADD_OPCODE_HANDLER(SMSG_RECONNECTION_TICKET,           STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_RECONNECTION_TICKET_REQUEST_RESULT,           STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_INVALID_CLIENT_VERSION,        STATUS_NEVER,      &WorldSession::HandleServerSide);

    ADD_OPCODE_HANDLER(SMSG_CLIENT_AUTHENTICATION_RESULTS,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_WORLD_SERVER_UNAVAILABLE,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_COACH_CREATION_REQUEST,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_COACH_CREATION_RESULT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_COACH_INFORMATIONS,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_OPPONENT_SEARCH_ERROR,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_OPPONENT_FOUND,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_OPPONENT_SEARCH_IN_PROGRESS,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_OPPONENT_SEARCH_CANCEL_RESULT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHT_INVITATION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHT_INVITATION_ACCEPTED,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHT_INVITATION_REJECTED,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHT_INVITATION_ERROR,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHT_CREATION_CANCELED,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_PLAYER_STATISTICS_REPORT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_READY_FOR_FIGHT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_NO_INSTANCE_SERVER_AVAILABLE,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ENTER_INSTANCE,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_COACH_INVENTORY_UPDATE,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_COACH_EQUIPMENT_UPDATE,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ACTOR_SPAWN,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ACTOR_DESPAWN,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ACTOR_APPEAR,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ACTOR_DISAPEAR,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ACTOR_REPOSITION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ACTOR_MOVEMENT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ACTOR_TELEPORTS,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_SAVE_TEAM_PRESET,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_DELETION_TEAM_PRESET,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_TEAM_PRESET_LIST,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHTER_INFORMATION_LIST,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CREATION_FIGHTER_INFORMATION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_DELETION_FIGHTER_INFORMATION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_UPDATED_FIGHTER_INFORMATION_INVENTORY,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHT_CREATION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_MOVE_TO_FREE_PLACEMENT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_START_PRESENTATION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_END_PRESENTATION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_TEAM_MATE_SET_READY_FOR_PLACEMENT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_START_PLACEMENT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_END_PLACEMENT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_TEAM_MATE_SET_READY_FOR_OBSERVATION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_START_OBSERVATION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_END_OBSERVATION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_TEAM_MATE_SET_READY_FOR_ACTION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_EFFECT_AREA_ACTION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_START_ACTION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHTER_TURN_BEGIN,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHTER_TURN_END,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHTER_DIES,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHTER_MOVE,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_NEW_TABLE_TURN_BEGIN,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHTER_CHANGE_DIRECTION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_END_FIGHT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ITEM_EXCHANGE_INVITATION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ITEM_EXCHANGE_INVITATION_CONFIRMATION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ITEM_EXCHANGE_CARD_ADDED,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ITEM_EXCHANGE_CARD_REMOVED,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ITEM_EXCHANGE_END,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ITEM_EXCHANGE_USER_READY,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHT_ACTION_SEQUENCE_EXECUTE,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_RUNNING_EFFECT_ACTION,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_SPELL_CAST,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHTER_TACKLED,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FIGHTER_CARD_USE,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLOSE_COMBAT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHANNEL_FLAGS,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHANNEL_JOIN,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHANNEL_LEAVE,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHANNEL_MEMBER_FLAGS,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHANNEL_MEMBER_KICK,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHANNEL_MEMBERS,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHANNEL_CONTENT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHAT_USER_FLAGS,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FRIEND_LIST,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_IGNORE_LIST,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_NOTIFICATION_FRIEND_ONLINE,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_NOTIFICATION_FRIEND_OFFLINE,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_VICINITY_CONTENT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_PRIVATE_CONTENT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FRIEND_ADDED,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FRIEND_REMOVED,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_IGNORE_ADDED,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_IGNORE_REMOVED,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHANNEL_NOT_FOUND,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_USER_NOT_FOUND,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_MALFORMED_COMMAND,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_MEMBER_NOT_FOUND,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_NOT_ENOUGH_PRIVILEGES,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_NOT_YET_IMPLEMENTED,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_TARGET_IS_YOURSELF,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_OPERATION_NOT_PERMITED,         STATUS_NEVER,      &WorldSession::HandleServerSide);

#undef ADD_OPCODE_HANDLER
}
