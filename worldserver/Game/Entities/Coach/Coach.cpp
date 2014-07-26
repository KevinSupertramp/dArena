#include "Coach.h"
#include "Utils/Util.h"

Coach::Coach(WorldSession* session) : Unit()
{
    m_session = session;
    m_typeId = TYPEID_COACH;

    m_name = QString();

    m_level = 1;
    m_xp = 0;

    m_gender = 0;
    m_skinColorIndex = 0;
    m_hairColorIndex = 0;

    m_positionX = 0;
    m_positionY = 0;
    m_positionZ = 0;
    m_direction = 0;
    m_instanceId = 0;

    m_inWorld = false;
}

Coach::~Coach()
{
}

bool Coach::Create(quint64 guid, sCoachCreateInfos createInfos)
{
    SetGuid(guid);

    m_name              = createInfos.name;

    m_gender            = createInfos.gender;
    m_skinColorIndex    = createInfos.skinColorIndex;
    m_hairColorIndex    = createInfos.hairColorIndex;

    return true;
}

bool Coach::LoadFromDB()
{
    QSqlQuery result = Database::Coach()->Query(SELECT_COACH_BY_GUID, QVariantList() << GetSession()->GetAccountInfos().coachGuid);

    if (!result.first())
    {
        qDebug() << "Character::LoadFromDB no coach found for account id " << GetSession()->GetAccountInfos().id << " (Coach GUID : " << GetSession()->GetAccountInfos().coachGuid << ") !";
        return false;
    }

    QSqlRecord fields = result.record();

    m_guid              = (quint64)result.value(fields.indexOf("guid")).toULongLong();
    m_name              = result.value(fields.indexOf("name")).toString();

    m_level             = (quint16)result.value(fields.indexOf("level")).toUInt();
    m_xp                = (quint64)result.value(fields.indexOf("xp")).toULongLong();

    m_gender            = (quint8)result.value(fields.indexOf("gender")).toUInt();
    m_skinColorIndex    = (quint8)result.value(fields.indexOf("skin_color")).toUInt();
    m_hairColorIndex    = (quint8)result.value(fields.indexOf("hair_color")).toUInt();

    m_positionX         = (qint32)result.value((fields.indexOf("position_x"))).toInt();
    m_positionY         = (qint32)result.value((fields.indexOf("position_y"))).toInt();
    m_positionZ         = (qint16)result.value((fields.indexOf("position_z"))).toInt();
    m_direction         = (quint8)result.value((fields.indexOf("direction"))).toInt();
    m_instanceId        = (quint16)result.value((fields.indexOf("instance_id"))).toInt();

    GetSession()->SetCoach(this);
    return true;
}

void Coach::SaveToDB(bool create)
{
    if (create)
    {
        Database::Coach()->Query(INSERT_COACH, QVariantList()
                                << GetGuid() << GetName() << GetGender() << m_level << m_xp
                                << GetSkinColorIndex() << GetHairColorIndex() << GetPositionX() << GetPositionY() << GetPositionZ() << GetDirection() << GetInstanceId());

        Database::Auth()->Query(UPDATE_ACCOUNT_COACH_GUID, QVariantList() << GetGuid() << GetSession()->GetAccountInfos().id);
    }
    else
    {
        Database::Coach()->Query(UPDATE_COACH, QVariantList()
                                << GetPositionX() << GetPositionY() << GetPositionZ() << GetDirection() << GetInstanceId() << GetGuid());
    }
}
