#include "HotaruMKII.h"

ObjectHotaruMKII *HotaruMKII;
void (*HotaruMKII_State_Charging)(void);
void (*HotaruMKII_State_LaserAttack)(void);

void HotaruMKII_EnemyInfoHook(void) {
	Mod.Super(HotaruMKII->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = HotaruMKII->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = HotaruMKII_State_Charging;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &HotaruMKII->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = HotaruMKII_State_LaserAttack;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &HotaruMKII->hitboxBadnik;
	++EnemyInfoSlot;
}
