#include "JuggleSaw.h"

ObjectJuggleSaw *JuggleSaw;
void (*JuggleSaw_StateCrab_Handle)();
void (*JuggleSaw_StateCrab_ThrowSaw)();

bool32 JuggleSaw_CheckVulnerable(Entity* self) {
	return (
	    ((EntityJuggleSaw*)self)->state == JuggleSaw_StateCrab_Handle
	 || ((EntityJuggleSaw*)self)->state == JuggleSaw_StateCrab_ThrowSaw
	);
}

Hitbox* JuggleSaw_GetHitbox(Entity* self) { return &(JuggleSaw->hitboxBadnik); }

void JuggleSaw_OnHit(EntityPlayer* player, Entity* self) {
	if (((EntityJuggleSaw*)self)->hasSaw == JUGGLESAW_HAS_SAW) {
		int32 debrisX = self->position.x;
		int32 debrisY = self->position.y;
		if (((EntityJuggleSaw*)self)->startDir >= FLIP_Y) {
			debrisX += 0x200000 * ((self->direction & FLIP_X) ? -1 : 1);
		} else {
			debrisY += 0x200000 * ((self->direction & FLIP_Y) ? 1 : -1);
		}
		EntityDebris *debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, debrisX, debrisY);

		RSDK.SetSpriteAnimation(JuggleSaw->aniFrames, 6, &debris->animator, true, 0);

		int32 minVelX = -4, maxVelX = 5, minVelY = -4, maxVelY = 5;
		if (((EntityJuggleSaw*)self)->startDir >= FLIP_Y) {
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
	Generic_BadnikBreak(player, self, true);
}

void JuggleSaw_EnemyInfoHook() {
	Mod.Super(JuggleSaw->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(JuggleSaw->classID, JuggleSaw_CheckVulnerable, JuggleSaw_GetHitbox, JuggleSaw_OnHit, NULL, ATKFLAG_NONE);
}