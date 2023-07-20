#include "IceBomba.h"

ObjectIceBomba* IceBomba;
void (*IceBomba_State_Flying)();
void (*IceBomba_State_Turning)();
void (*IceBomba_State_FlyAway)();

bool32 IceBomba_CheckVulnerable(Entity* self) {
	return (
	    ((EntityIceBomba*)self)->state == IceBomba_State_Flying
	 || ((EntityIceBomba*)self)->state == IceBomba_State_Turning
	 || ((EntityIceBomba*)self)->state == IceBomba_State_FlyAway
	);
}

Hitbox* IceBomba_GetHitbox(Entity* self) { return &(IceBomba->hitboxBadnik); }

void IceBomba_OnHit(EntityPlayer* player, Entity* self) {
	if (((EntityIceBomba*)self)->state != IceBomba_State_FlyAway) {
		EntityIceBomba* bomb = CREATE_ENTITY(IceBomba, INT_TO_VOID(true), self->position.x, self->position.y);
		if (self->direction) {
			bomb->position.x -= 0x40000;
		} else {
			bomb->position.x += 0x40000;
		}
		bomb->position.y += 0x1A0000;
		bomb->direction = self->direction;
	}
	Generic_BadnikBreak(player, self, true);
}

void IceBomba_EnemyInfoHook() {
	Mod.Super(IceBomba->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(IceBomba->classID, IceBomba_CheckVulnerable, IceBomba_GetHitbox, IceBomba_OnHit, NULL, ATKFLAG_NONE);
}