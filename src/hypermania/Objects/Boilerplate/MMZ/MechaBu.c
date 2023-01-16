#include "MechaBu.h"

ObjectMechaBu *MechaBu;
void (*MechaBu_State_Moving)(void);
void (*MechaBu_State_Stopped)(void);
void (*MechaBu_State_Falling)(void);

void MechaBu_EnemyInfoHook(void) {
	Mod.Super(MechaBu->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = MechaBu->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = MechaBu_State_Moving;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &MechaBu->hitboxSaw;
	EnemyDefs[EnemyInfoSlot].states[1].func = MechaBu_State_Stopped;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &MechaBu->hitboxSaw;
	EnemyDefs[EnemyInfoSlot].states[2].func = MechaBu_State_Falling;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &MechaBu->hitboxSaw;
	EnemyDefs[EnemyInfoSlot].destroy_func = MechaBu_DropSaw;
	++EnemyInfoSlot;
}

void MechaBu_DropSaw(EntityPlayer* player, Entity* e) {
	EntityMechaBu* self = (EntityMechaBu*)e;
	EntityDebris *debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, self->sawPos.x, self->sawPos.y);
	RSDK.SetSpriteAnimation(MechaBu->aniFrames, 7, &debris->animator, false, 0);
	debris->velocity.x      = RSDK.Rand(-2, 3) << 16;
	debris->velocity.y      = RSDK.Rand(-4, -1) << 16;
	debris->gravityStrength = 0x3800;
	debris->drawGroup       = self->drawGroup;
	debris->updateRange.x   = 0x200000;
	debris->updateRange.y   = 0x200000;
	BreakBadnik(player, e);
}