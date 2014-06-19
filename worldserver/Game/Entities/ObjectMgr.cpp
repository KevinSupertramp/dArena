#include "ObjectMgr.h"
#include "Configuration/ConfigMgr.h"

template<> ObjectMgr*  Singleton<ObjectMgr>::m_instance = 0;

ObjectMgr::ObjectMgr()
{
    m_highCoachGuid = 0;
}

ObjectMgr::~ObjectMgr() {}

void ObjectMgr::SetHighestGuids()
{
    QSqlQuery result = Database::Coach()->Query(SELECT_COACH_MAX_GUID);
    if (result.first())
        m_highCoachGuid = result.value(0).toUInt();
}

quint32 ObjectMgr::GenerateGuid(GuidType type)
{
    switch (type)
    {
        case GUIDTYPE_COACH:
        {
            Q_ASSERT(m_highCoachGuid < 0xFFFFFFFE && "ObjectMgr::GenerateGuid : coach guid overflow !");
            return ++m_highCoachGuid;
        }
        default:
            Q_ASSERT(false && "ObjectMgr::GenerateGuid : unknown guid type.");
            return 0;
    }
}
