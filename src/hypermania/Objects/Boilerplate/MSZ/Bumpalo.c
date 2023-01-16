#include "Bumpalo.h"

ObjectBumpalo *Bumpalo;
void (*Bumpalo_State_Moving)(void);
void (*Bumpalo_State_Idle)(void);
void (*Bumpalo_State_Charging)(void);
void (*Bumpalo_State_Turning)(void);
void (*Bumpalo_State_Bumped)(void);
void (*Bumpalo_State_Falling)(void);

void Bumpalo_EnemyInfoHook(void) {
	Mod.Super(Bumpalo->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Bumpalo->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Bumpalo_State_Moving;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Bumpalo->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Bumpalo_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Bumpalo->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Bumpalo_State_Charging;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Bumpalo->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = Bumpalo_State_Turning;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Bumpalo->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[4].func = Bumpalo_State_Bumped;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &Bumpalo->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[5].func = Bumpalo_State_Falling;
	EnemyDefs[EnemyInfoSlot].states[5].hitbox = &Bumpalo->hitboxBadnik;
	++EnemyInfoSlot;
}
