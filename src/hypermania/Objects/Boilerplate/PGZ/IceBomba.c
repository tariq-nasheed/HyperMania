#include "IceBomba.h"

ObjectIceBomba *IceBomba;
void (*IceBomba_State_Flying)(void);
void (*IceBomba_State_Turning)(void);
void (*IceBomba_State_FlyAway)(void);

void IceBomba_EnemyInfoHook(void) {
	Mod.Super(IceBomba->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = IceBomba->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = IceBomba_State_Flying;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &IceBomba->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = IceBomba_State_Turning;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &IceBomba->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = IceBomba_State_FlyAway;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &IceBomba->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].destroy_func = IceBomba_DropBomb;
	++EnemyInfoSlot;
}

void IceBomba_DropBomb(EntityPlayer* player, Entity* e) {
	EntityIceBomba* self = (EntityIceBomba*)e;
	if (self->state != IceBomba_State_FlyAway) {
		EntityIceBomba* bomb = CREATE_ENTITY(IceBomba, INT_TO_VOID(true), self->position.x, self->position.y);
		if (self->direction) {
			bomb->position.x -= 0x40000;
		} else {
			bomb->position.x += 0x40000;
		}
		bomb->position.y += 0x1A0000;
		bomb->direction = self->direction;
	}
	BreakBadnik(player, e);
}