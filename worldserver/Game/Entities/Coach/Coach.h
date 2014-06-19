#ifndef COACH_H
#define COACH_H

#include "Databases/Database.h"
#include "Define.h"
#include "Server/WorldSession.h"
#include "Entities/Unit/Unit.h"

struct sCoachCreateInfos
{
    sCoachCreateInfos(QString name, quint8 gender, quint8 skinColorIndex, quint8 hairColorIndex) :
        name(name), gender(gender), skinColorIndex(skinColorIndex), hairColorIndex(hairColorIndex) {}

    QString name;

    quint8 gender, skinColorIndex, hairColorIndex;
};

class Coach : public Unit
{
public:
    Coach(WorldSession* session);
    ~Coach();

    WorldSession* GetSession() { return m_session; }
    QString GetName() { return m_name; }
    quint8 GetGender() { return m_gender; }

    quint8 GetSkinColorIndex() { return m_skinColorIndex; }
    quint8 GetHairColorIndex() { return m_hairColorIndex; }

    void SetPosition(qint32 positionX, qint32 positionY, qint16 positionZ)
    {
        m_positionX = positionX;
        m_positionY = positionY;
        m_positionZ = positionZ;
    }

    qint32 GetPositionX() { return m_positionX; }
    qint32 GetPositionY() { return m_positionY; }
    qint16 GetPositionZ() { return m_positionZ; }

    void SetDirection(quint8 direction) { m_direction = direction; }
    quint8 GetDirection() { return m_direction; }

    void SetInstanceId(quint16 instanceId) { m_instanceId = instanceId; }
    quint16 GetInstanceId() { return m_instanceId; }

    bool Create(quint64 guid, sCoachCreateInfos createInfos);
    bool LoadFromDB();
    void SaveToDB(bool create = false);

private:
    WorldSession* m_session;

    QString m_name;

    quint16 m_level;
    quint64 m_xp;

    quint8 m_gender;
    quint8 m_skinColorIndex;
    quint8 m_hairColorIndex;

    qint32 m_positionX;
    qint32 m_positionY;
    qint16 m_positionZ;
    quint8 m_direction;
    quint16 m_instanceId;
};

#endif // COACH_H
