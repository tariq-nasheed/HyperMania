#include "Shutterbug.h"

ObjectShutterbug *Shutterbug;
void (*Shutterbug_State_FlyAround)(void);
void (*Shutterbug_State_ShakeFly)(void);
void (*Shutterbug_State_FlyAway)(void);

void Shutterbug_EnemyInfoHook(void) {
	Mod.Super(Shutterbug->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Shutterbug->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Shutterbug_State_FlyAround;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Shutterbug->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Shutterbug_State_ShakeFly;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Shutterbug->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Shutterbug_State_FlyAway;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Shutterbug->hitboxBadnik;
	++EnemyInfoSlot;
}
