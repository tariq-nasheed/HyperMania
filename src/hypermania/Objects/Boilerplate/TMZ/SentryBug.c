#include "SentryBug.h"

ObjectSentryBug *SentryBug;
void (*SentryBug_State_AwaitPlayer)(void);
void (*SentryBug_State_DropOrbs)(void);
void (*SentryBug_State_NetAppear)(void);
void (*SentryBug_State_NetShrink)(void);
void (*SentryBug_State_NetFlash)(void);
void (*SentryBug_State_ReturnToSlots)(void);

void SentryBug_EnemyInfoHook(void) {
	Mod.Super(SentryBug->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = SentryBug->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = SentryBug_State_AwaitPlayer;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &SentryBug->hitbox;
	EnemyDefs[EnemyInfoSlot].states[1].func = SentryBug_State_DropOrbs;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &SentryBug->hitbox;
	EnemyDefs[EnemyInfoSlot].states[2].func = SentryBug_State_NetAppear;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &SentryBug->hitbox;
	EnemyDefs[EnemyInfoSlot].states[3].func = SentryBug_State_NetShrink;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &SentryBug->hitbox;
	EnemyDefs[EnemyInfoSlot].states[4].func = SentryBug_State_NetFlash;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &SentryBug->hitbox;
	EnemyDefs[EnemyInfoSlot].states[5].func = SentryBug_State_ReturnToSlots;
	EnemyDefs[EnemyInfoSlot].states[5].hitbox = &SentryBug->hitbox;
	EnemyDefs[EnemyInfoSlot].destroy_func = SentryBug_StopSound;
	++EnemyInfoSlot;
}

void SentryBug_StopSound(EntityPlayer* player, Entity* e) {
	EntitySentryBug* self = (EntitySentryBug*)e;
	RSDK.StopSfx(SentryBug->sfxSwarm);
	BreakBadnik(player, e);
}