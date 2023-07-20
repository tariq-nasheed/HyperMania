#include "Fireworm.h"

ObjectFireworm* Fireworm;
void (*Fireworm_State_FlyAround)();

bool32 Fireworm_CheckVulnerable(Entity* self) {
	return (((EntityFireworm*)self)->state == Fireworm_State_FlyAround);
}

Hitbox* Fireworm_GetHitbox(Entity* self) { return &(Fireworm->hitboxBadnik); }

void Fireworm_OnHit(EntityPlayer* player, Entity* self) {
	for (int32 i = 1; i < FIREWORM_SEGMENT_COUNT; ++i) {
		EntityDebris *debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, ((EntityFireworm*)self)->bodyPositions[i].x, ((EntityFireworm*)self)->bodyPositions[i].y);
		RSDK.SetSpriteAnimation(Fireworm->aniFrames, 3, &debris->animator, true, 0);
		debris->velocity.x      = RSDK.Rand(-0x40000, 0x40000);
		debris->velocity.y      = RSDK.Rand(-0x40000, 0x40000);
		debris->gravityStrength = 0x3800;
		debris->drawGroup       = Zone->objectDrawGroup[0];
		debris->updateRange.x   = 0x400000;
		debris->updateRange.y   = 0x400000;
	}
	Generic_BadnikBreak(player, self, true);
}

void Fireworm_AdjustPos(Entity* self) { self->position = ((EntityFireworm*)self)->bodyPositions[0]; }

void Fireworm_EnemyInfoHook() {
	Mod.Super(Fireworm->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Fireworm->classID, Fireworm_CheckVulnerable, Fireworm_GetHitbox, Fireworm_OnHit, Fireworm_AdjustPos, ATKFLAG_NONE);
}