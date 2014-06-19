#ifndef COACHDATABASE_H
#define COACHDATABASE_H

#include <QtCore>
#include "MysqlConnection.h"

class CoachDatabase : public MysqlConnection
{
public:
    CoachDatabase(ConnectionInfo& connectionInfo) : MysqlConnection(connectionInfo) {}

    virtual void LoadQueries();
};

enum CharDatabaseQueries
{    
    /**
     * DATABASE_STATEMENT_SUMMARY
     */
    SELECT_COACH_MAX_GUID,
    SELECT_COACH_BY_GUID,
    SELECT_COACH_BY_NAME,
    INSERT_COACH,
    UPDATE_COACH
};

#endif
