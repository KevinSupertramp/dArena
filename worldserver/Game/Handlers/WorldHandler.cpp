#include "Server/WorldSession.h"

void WorldSession::SendEnterInstance()
{
    WorldPacket data(SMSG_ENTER_INSTANCE);
    data << float(131072); // worldX
    data << float(0); // worldY
    data << short(0); // altitude
    data << short(0); // instanceId
    data << quint8(0); // isDynamic
    SendPacket(data);

    GetCoach()->InWorld(true);
}
