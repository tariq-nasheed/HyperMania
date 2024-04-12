#include "SentryBug.h"

ObjectSentryBug* SentryBug;
void (*SentryBug_State_AwaitPlayer)();
void (*SentryBug_State_DropOrbs)();
void (*SentryBug_State_NetAppear)();
void (*SentryBug_State_NetShrink)();
void (*SentryBug_State_NetFlash)();
void (*SentryBug_State_ReturnToSlots)();

bool32 SentryBug_CheckVulnerable(Entity* self) {
	return (
	    ((EntitySentryBug*)self)->state == SentryBug_State_AwaitPlayer
	 || ((EntitySentryBug*)self)->state == SentryBug_State_DropOrbs
	 || ((EntitySentryBug*)self)->state == SentryBug_State_NetAppear
	 || ((EntitySentryBug*)self)->state == SentryBug_State_NetShrink
	 || ((EntitySentryBug*)self)->state == SentryBug_State_NetFlash
	 || ((EntitySentryBug*)self)->state == SentryBug_State_ReturnToSlots
	);
}

Hitbox* SentryBug_GetHitbox(Entity* self) { return &(SentryBug->hitbox); }

void SentryBug_OnHit(EntityPlayer* player, Entity* self) {
	RSDK.StopSfx(SentryBug->sfxSwarm);
	Generic_BadnikBreak(player, self, true);
}

void SentryBug_EnemyInfoHook() {
	Mod.Super(SentryBug->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(SentryBug->classID, SentryBug_CheckVulnerable, SentryBug_GetHitbox, SentryBug_OnHit, NULL, ATKFLAG_NONE);
}