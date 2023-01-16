#include "DERobot.h"

ObjectDERobot *DERobot;
void (*DERobot_State_FallLand)(void);
void (*DERobot_State_Walk)(void);
void (*DERobot_State_ArmAttack)(void);
void (*DERobot_State_Explode)(void);
void (*DERobot_State_ArmDestroyed)(void);

void DERobot_EnemyInfoHook(void) {
	Mod.Super(DERobot->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = DERobot->classID;
	EnemyDefs[EnemyInfoSlot].animal = false;
	EnemyDefs[EnemyInfoSlot].boss = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = DERobot_State_FallLand;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &DERobot->hitboxBody;
	EnemyDefs[EnemyInfoSlot].states[1].func = DERobot_State_Walk;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &DERobot->hitboxBody;
	EnemyDefs[EnemyInfoSlot].states[2].func = DERobot_State_ArmAttack;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &DERobot->hitboxBody;
	EnemyDefs[EnemyInfoSlot].destroy_func = DERobot_TakeHit;
	++EnemyInfoSlot;
}

void DERobot_TakeHit(EntityPlayer* player, Entity* e) {
	EntityDERobot* self = (EntityDERobot*)e;
	if (!self->invincibilityTimer) {
		if (--self->health <= 0) {
			self->timer            = 0;
			self->state            = DERobot_State_Explode;
			SceneInfo->timeEnabled = false;
			Player_GiveScore(RSDK_GET_ENTITY(SLOT_PLAYER1, Player), 1000);
			((EntityDERobot*)self->arms[1])->state = DERobot_State_ArmDestroyed;
			((EntityDERobot*)self->arms[3])->state = DERobot_State_ArmDestroyed;
		} else {
			self->invincibilityTimer = 48;
			RSDK.PlaySfx(DERobot->sfxHit, false, 255);
			if (self->health == 2) {
				self->kneeAngleVel  = 16;
				self->angleVelStart = 0x20000;
				self->angleMaxInc   = -0x4000;
				((EntityDERobot*)self->legs[0])->angleVel *= 2;
				((EntityDERobot*)self->legs[0])->angleInc *= 4;
				((EntityDERobot*)self->legs[3])->angleVel *= 2;
				((EntityDERobot*)self->legs[3])->angleInc *= 4;
			}
		}
	}
}