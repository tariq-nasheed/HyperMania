#include "HotaruMKII.h"

ObjectHotaruMKII* HotaruMKII;
void (*HotaruMKII_State_Charging)();
void (*HotaruMKII_State_LaserAttack)();

bool32 HotaruMKII_CheckVulnerable(Entity* self) {
	return (
	    ((EntityHotaruMKII*)self)->state == HotaruMKII_State_Charging
	 || ((EntityHotaruMKII*)self)->state == HotaruMKII_State_LaserAttack
	);
}

Hitbox* HotaruMKII_GetHitbox(Entity* self) { return &(HotaruMKII->hitboxBadnik); }

void HotaruMKII_EnemyInfoHook() {
	Mod.Super(HotaruMKII->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(HotaruMKII->classID, HotaruMKII_CheckVulnerable, HotaruMKII_GetHitbox, Generic_OnHit, NULL, ATKFLAG_NONE);
}