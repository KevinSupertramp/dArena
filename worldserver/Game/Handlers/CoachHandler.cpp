#include "Server/WorldSession.h"
#include "Entities/ObjectMgr.h"

void WorldSession::HandleCoachCreation(WorldPacket& packet)
{
    QString name;
    quint8 skinColorIndex, hairColorIndex, gender;

    name = packet.ReadString();
    packet >> skinColorIndex >> hairColorIndex >> gender;

    WorldPacket data(SMSG_COACH_CREATION_RESULT);
    QSqlQuery result = Database::Coach()->Query(SELECT_COACH_BY_NAME, QVariantList() << name);

    if (!result.first())
    {
        // TODO
        // Check max char by account

        sCoachCreateInfos createInfos(name, gender, skinColorIndex, hairColorIndex);
        QScopedPointer<Coach> newChar(new Coach(this));

        if(newChar->Create(ObjectMgr::Instance()->GenerateGuid(GUIDTYPE_COACH), createInfos))
        {
            newChar->SaveToDB(true);

            data << quint8(0); // Success
            SendPacket(data);

            SendCoachInformation();
            return;
        }
    }

    data << quint8(11); // Invalid name
    SendPacket(data);
}

void WorldSession::SendCoachInformation()
{
    Coach* coach = new Coach(this);
    if (!coach->LoadFromDB())
    {
        delete coach;
        OnClose();
        return;
    }

    WorldPacket data(SMSG_COACH_INFORMATIONS);

    // unserializeIdAndName
    data << coach->GetGuid();
    data.WriteString(coach->GetName());

    // unserializeLook
    data << coach->GetSkinColorIndex();
    data << coach->GetHairColorIndex();
    data << coach->GetGender();

    // unserializeEquipment
    data << quint16(0); // length
    // todo

    // unserializeCardInventory
    data << quint16(0); // length
    // todo

    // unserializeLockedSet
    data << quint16(0); // length

    // unserializeLaddersStrength
    data << quint8(0); // count
    // todo

    SendPacket(data);

    // World login
    SendEnterInstance();
}

void WorldSession::HandleCoachMovement(WorldPacket& packet)
{
    QByteArray path = packet.GetPacket();
    qDebug() << path.size();

    WorldPacket data(SMSG_ACTOR_MOVEMENT);

    data << GetCoach()->GetGuid();
    data.WriteRawBytes(path.data(), path.length());

    SendPacket(data);
}
