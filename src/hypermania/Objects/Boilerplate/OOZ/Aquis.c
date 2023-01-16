#include "Aquis.h"

ObjectAquis *Aquis;
void (*Aquis_State_Idle)(void);
void (*Aquis_State_Moving)(void);
void (*Aquis_State_Shoot)(void);
void (*Aquis_State_Turning)(void);
void (*Aquis_State_Flee)(void);

void Aquis_EnemyInfoHook(void) {
	Mod.Super(Aquis->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Aquis->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Aquis_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Aquis->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Aquis_State_Moving;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Aquis->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Aquis_State_Shoot;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Aquis->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = Aquis_State_Turning;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Aquis->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[4].func = Aquis_State_Flee;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &Aquis->hitboxBadnik;
	++EnemyInfoSlot;
}
