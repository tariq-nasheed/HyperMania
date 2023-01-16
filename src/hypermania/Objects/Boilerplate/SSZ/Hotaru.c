#include "Hotaru.h"

ObjectHotaru *Hotaru;
void (*Hotaru_State_CheckPlayerInRange)(void);
void (*Hotaru_State_FlyOnScreen)(void);
void (*Hotaru_State_AttachedToScreen)(void);
void (*Hotaru_State_Charging)(void);
void (*Hotaru_State_Attacking)(void);
void (*Hotaru_State_FinishedAttacking)(void);

void Hotaru_EnemyInfoHook(void) {
	Mod.Super(Hotaru->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Hotaru->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Hotaru_State_CheckPlayerInRange;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Hotaru->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Hotaru_State_FlyOnScreen;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Hotaru->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Hotaru_State_AttachedToScreen;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Hotaru->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = Hotaru_State_Charging;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Hotaru->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[4].func = Hotaru_State_Attacking;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &Hotaru->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[5].func = Hotaru_State_FinishedAttacking;
	EnemyDefs[EnemyInfoSlot].states[5].hitbox = &Hotaru->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].destroy_func = Hotaru_Destroy;
	++EnemyInfoSlot;
}

void Hotaru_Destroy(EntityPlayer* player, Entity* e) {
	EntityHotaru* self = (EntityHotaru*)e;

	int32 storeX = self->position.x;
	int32 storeY = self->position.y;
	self->position.x += self->offset1.x;
	self->position.y += self->offset1.y;
	if (!(self->destroyedHotarus & 1)) self->destroyedHotarus |= 1;
	if (!(self->destroyedHotarus & 2)) self->destroyedHotarus |= 2;
	BreakBadnik(player, e);
	self->position.x = storeX;
	self->position.y = storeY;
}