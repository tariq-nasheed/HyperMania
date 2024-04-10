#include "MegaOctus.h"

ObjectMegaOctus* MegaOctus;
void (*MegaOctus_State_EnterMegaOctus)();
void (*MegaOctus_State_OpenHatchAndLaugh)();
void (*MegaOctus_State_CloseHatch)();
void (*MegaOctus_State_DiveIntoOil)();
void (*MegaOctus_State_SpawnWeapons)();
void (*MegaOctus_State_CannonThenSpawnOrbs)();
void (*MegaOctus_StateOrb_Wait)();
void (*MegaOctus_StateOrb_FireShot)();
void (*MegaOctus_StateOrb_Idle)();
void (*MegaOctus_StateOrb_Destroyed)();
void (*MegaOctus_Hit)();
Hitbox hitbox;

bool32 MegaOctus_CheckVulnerable(Entity* self) {
	if (((EntityMegaOctus*)self)->invincibilityTimer || self->position.y >= ((EntityMegaOctus*)self)->origin.y + 0xC00000) return false;
	return (
	    ((EntityMegaOctus*)self)->state == MegaOctus_State_EnterMegaOctus
	 || ((EntityMegaOctus*)self)->state == MegaOctus_State_OpenHatchAndLaugh
	 || ((EntityMegaOctus*)self)->state == MegaOctus_State_CloseHatch
	 || ((EntityMegaOctus*)self)->state == MegaOctus_State_DiveIntoOil
	 || ((EntityMegaOctus*)self)->state == MegaOctus_State_SpawnWeapons
	 || ((EntityMegaOctus*)self)->state == MegaOctus_State_CannonThenSpawnOrbs
	 || ((EntityMegaOctus*)self)->state == MegaOctus_StateOrb_Wait
	 || ((EntityMegaOctus*)self)->state == MegaOctus_StateOrb_FireShot
	 || ((EntityMegaOctus*)self)->state == MegaOctus_StateOrb_Idle
	 || ((EntityMegaOctus*)self)->state == MegaOctus_StateOrb_Destroyed
	);
}

Hitbox* MegaOctus_GetHitbox(Entity* self) {
	if (((EntityMegaOctus*)self)->type == MEGAOCTUS_ORB) return &(((EntityMegaOctus*)self)->hitbox);
	return &hitbox;
}

void MegaOctus_OnHit(EntityPlayer* player, Entity* self) {
	if (((EntityMegaOctus*)self)->type == MEGAOCTUS_ORB) {
		--((EntityMegaOctus*)self)->health;
		--MegaOctus->orbHealth[((EntityMegaOctus*)self)->orbID];

		if (((EntityMegaOctus*)self)->health) {
			RSDK.PlaySfx(MegaOctus->sfxBossHit, false, 255);
			((EntityMegaOctus*)self)->invincibilityTimer = 30;
		} else {
			RSDK.PlaySfx(MegaOctus->sfxExplosion, false, 255);
			((EntityMegaOctus*)self)->invincibilityTimer = 60;
			((EntityMegaOctus*)self)->state              = MegaOctus_StateOrb_Destroyed;
		}
	} else {
		Entity* old_entity = SceneInfo->entity;
		SceneInfo->entity = self;
		MegaOctus_Hit();
		SceneInfo->entity = old_entity;
	}
}

void MegaOctus_AdjustPos(Entity* self) {
	if (((EntityMegaOctus*)self)->type == MEGAOCTUS_ORB) {
		self->position.x += (RSDK.Cos512(self->angle) << 10);
		self->position.y += (RSDK.Sin512(self->angle) << 8);
	}
}

void MegaOctus_EnemyInfoHook() {
	// mega octus doesn't actually use his hitbox so we have to make a more "accurate" one ourselves
	hitbox.left   = -48;
	hitbox.top    = -48;
	hitbox.right  = 48;
	hitbox.bottom = 48;
	Mod.Super(MegaOctus->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(MegaOctus->classID, MegaOctus_CheckVulnerable, MegaOctus_GetHitbox, MegaOctus_OnHit, MegaOctus_AdjustPos, ATKFLAG_ISBOSS);
}