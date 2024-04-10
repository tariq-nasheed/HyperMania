#include "DERobot.h"

ObjectDERobot* DERobot;
void (*DERobot_State_FallLand)();
void (*DERobot_State_Walk)();
void (*DERobot_State_ArmAttack)();
void (*DERobot_Hit)();

bool32 DERobot_CheckVulnerable(Entity* self) {
	if (((EntityDERobot*)self)->invincibilityTimer) return false;
	return (
	    ((EntityDERobot*)self)->state == DERobot_State_FallLand
	 || ((EntityDERobot*)self)->state == DERobot_State_Walk
	 || ((EntityDERobot*)self)->state == DERobot_State_ArmAttack
	);
}

Hitbox* DERobot_GetHitbox(Entity* self) { return &(DERobot->hitboxBody); }

void DERobot_OnHit(EntityPlayer* player, Entity* self) {
	Entity* old_entity = SceneInfo->entity;
	SceneInfo->entity = self;
	DERobot_Hit();
	SceneInfo->entity = old_entity;
}

void DERobot_EnemyInfoHook() {
	Mod.Super(DERobot->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(DERobot->classID, DERobot_CheckVulnerable, DERobot_GetHitbox, DERobot_OnHit, NULL, ATKFLAG_ISBOSS);
}