#ifndef AUTHDATABASE_H
#define AUTHDATABASE_H

#include <QtCore>
#include "MysqlConnection.h"

class AuthDatabase : public MysqlConnection
{
public:
    AuthDatabase(ConnectionInfo& connectionInfo) : MysqlConnection(connectionInfo) {}

    virtual void LoadQueries();
};

enum AuthDatabaseQueries
{
    /**
     * DATABASE_STATEMENT_SUMMARY
     */
    SELECT_ACCOUNT_BY_LOGIN_DETAILS,
    UPDATE_ACCOUNT_COACH_GUID
};

#endif
