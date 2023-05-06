#include "EggPistonsMKII.h"

ObjectEggPistonsMKII* EggPistonsMKII;
void (*EggPistonsMKII_State_ClassicMode)();
void (*EggPistonsMKII_State_PinchMode)();
void (*EggPistonsMKII_State_Destroyed)();
void (*EggPistonsMKII_Hit)();

bool32 EggPistonsMKII_CheckVulnerable(Entity* self) {
	if (EggPistonsMKII->invincibilityTimer || !self->visible) return false;
	return (
	    ((EntityEggPistonsMKII*)self)->state == EggPistonsMKII_State_ClassicMode
	 || ((EntityEggPistonsMKII*)self)->state == EggPistonsMKII_State_PinchMode
	);
}

Hitbox* EggPistonsMKII_GetHitbox(Entity* self) { return &(((EntityEggPistonsMKII*)self)->hitbox); }

void EggPistonsMKII_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	EggPistonsMKII_Hit();
	SceneInfo->entity = old_entity;
	// softlock without this because the check only happens in EggPistonsMKII_State_PinchMode (why????)
	if (!EggPistonsMKII->health) ((EntityEggPistonsMKII*)self)->state = EggPistonsMKII_State_Destroyed;
}

void EggPistonsMKII_EnemyInfoHook() {
	Mod.Super(EggPistonsMKII->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(EggPistonsMKII->classID, EggPistonsMKII_CheckVulnerable, EggPistonsMKII_GetHitbox, EggPistonsMKII_OnHit, NULL, ATKFLAG_ISBOSS);
}