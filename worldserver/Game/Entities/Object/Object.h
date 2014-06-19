#ifndef OBJECT_H
#define OBJECT_H

#include <QtCore>
#include "Packets/WorldPacket.h"

enum TypeId
{
    TYPEID_OBJECT              = 0,
    TYPEID_COACH               = 1,
    TYPEID_UNIT                = 2
};

class Unit;
class Coach;

class Object
{
public:
    Object();
    ~Object();

    TypeId GetTypeId() { return m_typeId; }

    void SetGuid(quint64 guid) { m_guid = guid; }
    quint64 GetGuid() const { return m_guid; }

    Coach* ToCoach() { if (GetTypeId() == TYPEID_COACH) return reinterpret_cast<Coach*>(this); else return NULL; }

protected:
    quint64 m_guid;
    TypeId m_typeId;
};

#endif // OBJECT_H
