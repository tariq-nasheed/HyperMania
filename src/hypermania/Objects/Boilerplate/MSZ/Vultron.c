#include "Vultron.h"

ObjectVultron *Vultron;
void (*Vultron_State_CheckPlayerInRange)(void);
void (*Vultron_State_Hop)(void);
void (*Vultron_State_Dive)(void);
void (*Vultron_State_Flying)(void);
void (*Vultron_State_Rise)(void);
void (*Vultron_State_PrepareDive)(void);
void (*Vultron_State_Targeting)(void);

// Vultron's hitbox changes dynamically based on its current animation frames dimensions
// i dont feel like rejiggering the enemy detection/collision system to support that so for now it just has a static 32x32 box
Hitbox hitbox;

void Vultron_EnemyInfoHook(void) {
	hitbox.left   = -16;
	hitbox.top    = -16;
	hitbox.right  = 16;
	hitbox.bottom = -16;
	Mod.Super(Vultron->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Vultron->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Vultron_State_CheckPlayerInRange;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].states[1].func = Vultron_State_Hop;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].states[2].func = Vultron_State_Dive;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].states[3].func = Vultron_State_Flying;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].states[4].func = Vultron_State_Rise;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].states[5].func = Vultron_State_PrepareDive;
	EnemyDefs[EnemyInfoSlot].states[5].hitbox = &hitbox;
	EnemyDefs[EnemyInfoSlot].states[6].func = Vultron_State_Targeting;
	EnemyDefs[EnemyInfoSlot].states[6].hitbox = &hitbox;
	++EnemyInfoSlot;
}
