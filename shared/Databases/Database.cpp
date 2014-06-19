#include "Database.h"
#include "Configuration/ConfigMgr.h"

template<> Database*  Singleton<Database>::m_instance = 0;

Database::Database()
{
    m_authDatabase = NULL;
    m_coachDatabase = NULL;
    m_worldDatabase = NULL;
}

Database::~Database()
{
    if (m_authDatabase)
        m_authDatabase->Close();

    if (m_coachDatabase)
        m_coachDatabase->Close();

    if (m_worldDatabase)
        m_worldDatabase->Close();

    delete m_authDatabase;
    delete m_coachDatabase;
    delete m_worldDatabase;
}

bool Database::OpenAuthDatabase()
{
    ConnectionInfo cinfos = ConnectionInfo(ConfigMgr::World()->GetQString("AuthDatabase"));
    m_authDatabase = new AuthDatabase(cinfos);

    if(!m_authDatabase->Open())
        return false;

    return true;
}

bool Database::OpenCoachDatabase()
{
    ConnectionInfo cinfos = ConnectionInfo(ConfigMgr::World()->GetQString("CoachDatabase"));
    m_coachDatabase = new CoachDatabase(cinfos);

    if(!m_coachDatabase->Open())
        return false;

    return true;
}

bool Database::OpenWorldDatabase()
{
    ConnectionInfo cinfos = ConnectionInfo(ConfigMgr::World()->GetQString("WorldDatabase"));
    m_worldDatabase = new WorldDatabase(cinfos);

    if(!m_worldDatabase->Open())
        return false;

    return true;
}
