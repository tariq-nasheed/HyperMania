#include "Blaster.h"

ObjectBlaster *Blaster;
void (*Blaster_State_Move)(void);
void (*Blaster_State_HandleTurn)(void);
void (*Blaster_State_AttackPlayer)(void);
void (*Blaster_State_MagnetAttract)(void);
void (*Blaster_State_MagnetReleased)(void);
void (*Blaster_State_Fall)(void);

void Blaster_EnemyInfoHook(void) {
	Mod.Super(Blaster->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Blaster->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Blaster_State_Move;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Blaster->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Blaster_State_HandleTurn;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Blaster->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Blaster_State_AttackPlayer;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Blaster->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = Blaster_State_MagnetAttract;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Blaster->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[4].func = Blaster_State_MagnetReleased;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &Blaster->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[5].func = Blaster_State_Fall;
	EnemyDefs[EnemyInfoSlot].states[5].hitbox = &Blaster->hitboxBadnik;
	++EnemyInfoSlot;
}
