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
    ADD_OPCODE_HANDLER(SMSG_CLIENT_INVALID_VERSION,        STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_AUTHENTICATION_RESULT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_COACH_CREATION_REQUEST,        STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_COACH_CREATION_RESULT,         STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_COACH_INFORMATION,             STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ACTOR_MOVEMENT,                STATUS_NEVER,      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ENTER_INSTANCE,                STATUS_NEVER,      &WorldSession::HandleServerSide);

#undef ADD_OPCODE_HANDLER
}
