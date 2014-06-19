#include "Server/WorldSession.h"

void WorldSession::SendEnterInstance()
{
    WorldPacket data(SMSG_ENTER_INSTANCE);
    data << float(131072);
    data << float(0);
    data << float(0);
    data << short(0);
    data << short(0);
    data << quint8(0);
    SendPacket(data);
}
