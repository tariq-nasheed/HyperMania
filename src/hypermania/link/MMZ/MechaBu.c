#include "MechaBu.h"

ObjectMechaBu* MechaBu;
void (*MechaBu_State_Moving)();
void (*MechaBu_State_Stopped)();
void (*MechaBu_State_Falling)();

bool32 MechaBu_CheckVulnerable(Entity* self) {
	return (
	    ((EntityMechaBu*)self)->state == MechaBu_State_Moving
	 || ((EntityMechaBu*)self)->state == MechaBu_State_Stopped
	 || ((EntityMechaBu*)self)->state == MechaBu_State_Falling
	);
}

Hitbox* MechaBu_GetHitbox(Entity* self) { return &(MechaBu->hitboxSaw); }

void MechaBu_OnHit(EntityPlayer* player, Entity* self) {
	EntityDebris* debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, ((EntityMechaBu*)self)->sawPos.x, ((EntityMechaBu*)self)->sawPos.y);
	RSDK.SetSpriteAnimation(MechaBu->aniFrames, 7, &debris->animator, false, 0);
	debris->velocity.x      = RSDK.Rand(-2, 3) << 16;
	debris->velocity.y      = RSDK.Rand(-4, -1) << 16;
	debris->gravityStrength = 0x3800;
	debris->drawGroup       = self->drawGroup;
	debris->updateRange.x   = 0x200000;
	debris->updateRange.y   = 0x200000;
	Generic_BadnikBreak(player, self, true);
}

void MechaBu_EnemyInfoHook() {
	Mod.Super(MechaBu->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(MechaBu->classID, MechaBu_CheckVulnerable, MechaBu_GetHitbox, MechaBu_OnHit, NULL, ATKFLAG_NONE);
}