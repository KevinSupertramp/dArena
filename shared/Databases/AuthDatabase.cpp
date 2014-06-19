#include "AuthDatabase.h"

void AuthDatabase::LoadQueries()
{
    LoadQuery(SELECT_ACCOUNT_BY_LOGIN_DETAILS, "SELECT * FROM account WHERE login = ? AND password = ?");
    LoadQuery(UPDATE_ACCOUNT_COACH_GUID, "UPDATE account SET coach_guid = ? WHERE account_id = ?");
}
