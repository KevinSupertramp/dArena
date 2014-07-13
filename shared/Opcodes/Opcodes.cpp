#include "Opcodes.h"
#include "Server/WorldSession.h"

OpcodesList OpcodeTable::opcodesList;

void OpcodeTable::Load()
{
#define ADD_OPCODE_HANDLER(opcode, handler) \
    Add(opcode, #opcode, handler);

    // Client messages (CMSG)
    ADD_OPCODE_HANDLER(CMSG_DISCONNECTION,                          &WorldSession::HandleClientDisconnect);
    ADD_OPCODE_HANDLER(CMSG_CLIENT_VERSION,                         &WorldSession::HandleClientVersion);
    ADD_OPCODE_HANDLER(CMSG_RECONNECTION_TICKET,                    &WorldSession::HandleReconnectionTicket);
    ADD_OPCODE_HANDLER(CMSG_AUTHENTICATION,                         &WorldSession::HandleClientAuthentication);
    ADD_OPCODE_HANDLER(CMSG_COACH_CREATION,                         &WorldSession::HandleCoachCreation);
    ADD_OPCODE_HANDLER(CMSG_COACH_MOVEMENT,                         &WorldSession::HandleCoachMovement);

    // Server messages (SMSG)
    ADD_OPCODE_HANDLER(SMSG_RECONNECTION_TICKET,                    &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_INVALID_VERSION,                 &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_AUTHENTICATION_RESULT,                  &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_COACH_CREATION_REQUEST,                 &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_COACH_CREATION_RESULT,                  &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_COACH_INFORMATION,                      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ACTOR_MOVEMENT,                         &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ENTER_INSTANCE,                         &WorldSession::HandleServerSide);

#undef ADD_OPCODE_HANDLER
}
