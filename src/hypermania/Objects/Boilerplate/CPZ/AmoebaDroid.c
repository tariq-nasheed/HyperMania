#include "AmoebaDroid.h"

ObjectAmoebaDroid *AmoebaDroid;
void (*AmoebaDroid_State_DropIn)(void);
void (*AmoebaDroid_State_DropIntoPool)(void);
void (*AmoebaDroid_State_SurfaceFromPool)(void);
void (*AmoebaDroid_State_ChooseAttack)(void);
void (*AmoebaDroid_State_ExitPool)(void);
void (*AmoebaDroid_State_BounceAttack)(void);
void (*AmoebaDroid_State_GatherBlobs)(void);
void (*AmoebaDroid_State_SpinBlobs)(void);
void (*AmoebaDroid_State_Destroyed)(void);

void AmoebaDroid_EnemyInfoHook(void) {
	Mod.Super(AmoebaDroid->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = AmoebaDroid->classID;
	EnemyDefs[EnemyInfoSlot].animal = false;
	EnemyDefs[EnemyInfoSlot].boss = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = AmoebaDroid_State_DropIn;
	EnemyDefs[EnemyInfoSlot].states[1].func = AmoebaDroid_State_DropIntoPool;
	EnemyDefs[EnemyInfoSlot].states[2].func = AmoebaDroid_State_SurfaceFromPool;
	EnemyDefs[EnemyInfoSlot].states[3].func = AmoebaDroid_State_ChooseAttack;
	EnemyDefs[EnemyInfoSlot].states[4].func = AmoebaDroid_State_ExitPool;
	EnemyDefs[EnemyInfoSlot].states[5].func = AmoebaDroid_State_BounceAttack;
	EnemyDefs[EnemyInfoSlot].states[6].func = AmoebaDroid_State_GatherBlobs;
	EnemyDefs[EnemyInfoSlot].states[7].func = AmoebaDroid_State_SpinBlobs;
	EnemyDefs[EnemyInfoSlot].hitbox_func = AmoebaDroid_GetHitbox;
	EnemyDefs[EnemyInfoSlot].destroy_func = AmoebaDroid_TakeHit;
	++EnemyInfoSlot;
}

Hitbox* AmoebaDroid_GetHitbox(Entity* e) {
	EntityAmoebaDroid* self = (EntityAmoebaDroid*)e;
	return &self->hitbox;
}

void AmoebaDroid_TakeHit(EntityPlayer* player, Entity* e) {
	EntityAmoebaDroid* self = (EntityAmoebaDroid*)e;
	if (!self->invincibleTimer) {
		if (--self->health <= 0) {
			for (int32 i = 0; i < AMOEBADROID_BLOB_COUNT; ++i) {
				EntityAmoebaDroid *smallBlob = (EntityAmoebaDroid*)self->blobs[i];
				if (smallBlob) {
					smallBlob->velocity.y -= 0x20000;
					smallBlob->onGround    = true;
					smallBlob->interaction = true;
					self->blobs[i]         = NULL;
				}
			}
			self->state            = AmoebaDroid_State_Destroyed;
			self->timer            = 0;
			SceneInfo->timeEnabled = false;
			Player_GiveScore(RSDK_GET_ENTITY(SLOT_PLAYER1, Player), 1000);
		} else {
			self->invincibleTimer = 48;
			RSDK.PlaySfx(AmoebaDroid->sfxHit, false, 0xFF);
		}
	}
}