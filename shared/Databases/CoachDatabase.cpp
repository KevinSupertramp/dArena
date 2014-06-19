#include "CoachDatabase.h"

void CoachDatabase::LoadQueries()
{
    LoadQuery(SELECT_COACH_MAX_GUID, "SELECT MAX(guid) FROM coaches");
    LoadQuery(SELECT_COACH_BY_GUID, "SELECT * FROM coaches WHERE guid = ?");
    LoadQuery(SELECT_COACH_BY_NAME, "SELECT guid FROM coaches WHERE name = ?");
    LoadQuery(INSERT_COACH, "INSERT INTO coaches (guid, name, gender, level, xp, skin_color, hair_color, position_x, position_y, position_z, direction, instance_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    LoadQuery(UPDATE_COACH, "UPDATE coaches SET position_x = ?, position_y = ?, position_z = ?, direction = ?, instance_id = ? WHERE guid = ?");
}
