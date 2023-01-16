#include "Bubbler.h"

ObjectBubbler *Bubbler;
void (*Bubbler_State_MotherPatrol)(void);
void (*Bubbler_State_FoundPlayer)(void);
void (*Bubbler_State_AttackPlayer)(void);
void (*Bubbler_StateProjectile_Seed)(void);
void (*Bubbler_StateProjectile_Bubbler)(void);

void Bubbler_EnemyInfoHook(void) {
	Mod.Super(Bubbler->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Bubbler->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Bubbler_State_MotherPatrol;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Bubbler->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Bubbler_State_FoundPlayer;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Bubbler->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Bubbler_State_AttackPlayer;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Bubbler->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = Bubbler_StateProjectile_Seed;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Bubbler->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[4].func = Bubbler_StateProjectile_Bubbler;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &Bubbler->hitboxBadnik;
	++EnemyInfoSlot;
}
