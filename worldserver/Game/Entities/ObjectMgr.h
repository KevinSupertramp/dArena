#ifndef OBJECTMGR_H
#define OBJECTMGR_H

#include <QtCore>
#include "Databases/Database.h"
#include "Utils/Singleton.h"

enum GuidType
{
    GUIDTYPE_NONE      = 0,
    GUIDTYPE_COACH     = 1
};

class Character;

class ObjectMgr : public Singleton<ObjectMgr>
{
public:
    ObjectMgr();
    ~ObjectMgr();

    void SetHighestGuids();
    quint32 GenerateGuid(GuidType type);

private:
    quint32 m_highCoachGuid;
};

#endif // OBJECTMGR_H
