#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore>
#include "AuthDatabase.h"
#include "CoachDatabase.h"
#include "WorldDatabase.h"
#include "Utils/Singleton.h"

class Database : public Singleton<Database>
{
public:
    Database();
    ~Database();

    static AuthDatabase* Auth()
    {
        return Database::Instance()->GetAuthDatabase();
    }

    static CoachDatabase* Coach()
    {
        return Database::Instance()->GetCoachDatabase();
    }

    static WorldDatabase* World()
    {
        return Database::Instance()->GetWorldDatabase();
    }

    bool OpenAuthDatabase();
    bool OpenCoachDatabase();
    bool OpenWorldDatabase();

private:
    AuthDatabase* GetAuthDatabase()
    {
        return m_authDatabase;
    }

    CoachDatabase* GetCoachDatabase()
    {
        return m_coachDatabase;
    }

    WorldDatabase* GetWorldDatabase()
    {
        return m_worldDatabase;
    }

    AuthDatabase* m_authDatabase;
    CoachDatabase* m_coachDatabase;
    WorldDatabase* m_worldDatabase;
};

#endif
