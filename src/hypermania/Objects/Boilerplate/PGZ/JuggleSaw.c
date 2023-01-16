#include "JuggleSaw.h"

ObjectJuggleSaw *JuggleSaw;
void (*JuggleSaw_StateCrab_Handle)(void);
void (*JuggleSaw_StateCrab_ThrowSaw)(void);

void JuggleSaw_EnemyInfoHook(void) {
	Mod.Super(JuggleSaw->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = JuggleSaw->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = JuggleSaw_StateCrab_Handle;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &JuggleSaw->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = JuggleSaw_StateCrab_ThrowSaw;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &JuggleSaw->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].destroy_func = JuggleSaw_DropSaw;
	++EnemyInfoSlot;
}

void JuggleSaw_DropSaw(EntityPlayer* player, Entity* e) {
	EntityJuggleSaw* self = (EntityJuggleSaw*)e;
	if (self->hasSaw == JUGGLESAW_HAS_SAW) {
		int32 debrisX = self->position.x;
		int32 debrisY = self->position.y;
		if (self->startDir >= FLIP_Y) {
			debrisX += 0x200000 * ((self->direction & FLIP_X) ? -1 : 1);
		} else {
			debrisY += 0x200000 * ((self->direction & FLIP_Y) ? 1 : -1);
		}
		EntityDebris *debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, debrisX, debrisY);

		RSDK.SetSpriteAnimation(JuggleSaw->aniFrames, 6, &debris->animator, true, 0);

		int32 minVelX = -4, maxVelX = 5, minVelY = -4, maxVelY = 5;
		if (self->startDir >= FLIP_Y) {
			minVelY = (self->direction & FLIP_X) ? -1 : -4;
		} else {
			minVelY = (self->direction & FLIP_Y) ? -4 : -1;
		}

		debris->velocity.x      = RSDK.Rand(minVelX, maxVelX) << 16;
		debris->velocity.y      = RSDK.Rand(minVelY, maxVelY) << 16;
		debris->gravityStrength = 0x3800;
		debris->drawGroup       = self->drawGroup;
		debris->updateRange.x   = 0x400000;
		debris->updateRange.y   = 0x400000;
	}
	BreakBadnik(player, e);
}