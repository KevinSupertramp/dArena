#include "Server/WorldSession.h"

void WorldSession::SendEnterInstance()
{
    WorldPacket data(SMSG_ENTER_INSTANCE);
    data << float(GetCoach()->GetPositionX());
    data << float(GetCoach()->GetPositionY());
    data << short(GetCoach()->GetPositionZ());
    data << short(GetCoach()->GetInstanceId());
    data << quint8(0); // isDynamic
    SendPacket(data);

    GetCoach()->InWorld(true);
    SendActorSpawn();

    // Disconnect
}

void WorldSession::SendActorSpawn()
{
    SessionList& sessions = World::Instance()->GetSessions();
    QList<Coach*> coachs;

    for (SessionList::ConstIterator itr = sessions.begin(); itr != sessions.end(); ++itr)
    {
        if (!(*itr)->HasCoach())
            continue;

        coachs.push_back((*itr)->GetCoach());
    }

    WorldPacket data(SMSG_ACTOR_SPAWN);
    data << quint32(coachs.size());

    for (QList<Coach*>::ConstIterator itr = coachs.begin(); itr != coachs.end(); ++itr)
    {
        data << quint8(TYPEID_COACH);

        data << (*itr)->GetGuid();
        data.WriteString((*itr)->GetName());

        data << (*itr)->GetPositionX();
        data << (*itr)->GetPositionY();
        data << (*itr)->GetPositionZ();
        data << (*itr)->GetDirection();

        data << (*itr)->GetSkinColorIndex();
        data << (*itr)->GetHairColorIndex();
        data << (*itr)->GetGender();

        data << quint16(0);
        data << quint8(0);
    }

    World::Instance()->SendPacketToAll(data);
}
