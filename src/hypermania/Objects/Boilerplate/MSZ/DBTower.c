#include "DBTower.h"

ObjectDBTower* DBTower;
void (*DBTower_State_HandleBoss)();
void (*DBTower_State_Destroyed)();

bool32 DBTower_CheckVulnerable(Entity* self) {
	if (((EntityDBTower*)self)->invincibilityTimer) return false;
	return (((EntityDBTower*)self)->state == DBTower_State_HandleBoss);
}

Hitbox* DBTower_GetHitbox(Entity* self) { return &(DBTower->hitboxSegment); }

void DBTower_OnHit(EntityPlayer* player, Entity* self) {
	((EntityDBTower*)self)->wobbleAngleVel = 2048;
	if (--((EntityDBTower*)self)->health <= 0) {
		SceneInfo->timeEnabled = false;
		Player_GiveScore(RSDK_GET_ENTITY(SLOT_PLAYER1, Player), 1000);
		RSDK.PlaySfx(DBTower->sfxExplosion2, false, 255);

		((EntityDBTower*)self)->timer = 120;
		((EntityDBTower*)self)->state = DBTower_State_Destroyed;
	} else {
		((EntityDBTower*)self)->invincibilityTimer = 48;
		RSDK.PlaySfx(DBTower->sfxHit, false, 255);
	}
}

void DBTower_EnemyInfoHook(void) {
	Mod.Super(DBTower->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(DBTower->classID, DBTower_CheckVulnerable, DBTower_GetHitbox, DBTower_OnHit, NULL, ATKFLAG_ISBOSS);
}