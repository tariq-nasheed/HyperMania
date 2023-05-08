#include "PhantomShinobi.h"

ObjectPhantomShinobi* PhantomShinobi;
void (*PhantomShinobi_State_SetupAttack)();
void (*PhantomShinobi_State_Moving)();
void (*PhantomShinobi_State_PrepareFinAttack)();
void (*PhantomShinobi_State_ExtendFins)();
void (*PhantomShinobi_State_RetractFins)();
void (*PhantomShinobi_Hit)();

bool32 PhantomShinobi_CheckVulnerable(Entity* self) {
	if (((EntityPhantomShinobi*)self)->invincibilityTimer) return false;
	return (
	    ((EntityPhantomShinobi*)self)->state == PhantomShinobi_State_SetupAttack
	 || ((EntityPhantomShinobi*)self)->state == PhantomShinobi_State_Moving
	 || ((EntityPhantomShinobi*)self)->state == PhantomShinobi_State_PrepareFinAttack
	 || ((EntityPhantomShinobi*)self)->state == PhantomShinobi_State_ExtendFins
	 || ((EntityPhantomShinobi*)self)->state == PhantomShinobi_State_RetractFins
	);
}

Hitbox* PhantomShinobi_GetHitbox(Entity* self) { return &(PhantomShinobi->hitbox); }

void PhantomShinobi_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	SceneInfo->entitySlot = RSDK.GetEntitySlot(self);
	PhantomShinobi_Hit();
	SceneInfo->entity = old_entity;
	SceneInfo->entitySlot = RSDK.GetEntitySlot(old_entity);
}

void PhantomShinobi_EnemyInfoHook() {
	Mod.Super(PhantomShinobi->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(PhantomShinobi->classID, PhantomShinobi_CheckVulnerable, PhantomShinobi_GetHitbox, PhantomShinobi_OnHit, NULL, ATKFLAG_ISBOSS);
}