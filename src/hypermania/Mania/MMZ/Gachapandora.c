#include "Gachapandora.h"

ObjectGachapandora* Gachapandora;
void (*Gachapandora_StatePrize_DrillerMove)();
void (*Gachapandora_StatePrize_FireDropperMove)();
void (*Gachapandora_StatePrize_AmyWalk)();
void (*Gachapandora_StatePrize_AmyIdle)();
void (*Gachapandora_StatePrize_Destroyed)();

bool32 Gachapandora_CheckVulnerable(Entity* self) {
	if (((EntityGachapandora*)self)->invincibilityTimer) return false;
	return (
	    ((EntityGachapandora*)self)->state == Gachapandora_StatePrize_DrillerMove
	 || ((EntityGachapandora*)self)->state == Gachapandora_StatePrize_FireDropperMove
	 || ((EntityGachapandora*)self)->state == Gachapandora_StatePrize_AmyWalk
	 || ((EntityGachapandora*)self)->state == Gachapandora_StatePrize_AmyIdle
	);
}

Hitbox* Gachapandora_GetHitbox(Entity* self) { return &(((EntityGachapandora*)self)->hitbox); }

void Gachapandora_OnHit(EntityPlayer* player, Entity* self) {
	if (--((EntityGachapandora*)self)->health) {
		RSDK.PlaySfx(Gachapandora->sfxHit, false, 255);
	} else {
		EntityGachapandora* eggman = (EntityGachapandora*)(Gachapandora->eggman);
		RSDK.SetSpriteAnimation(Gachapandora->eggmanFrames, 1, &eggman->eggmanAnimator, true, 0);
		RSDK.PlaySfx(Gachapandora->sfxExplosion, false, 255);
		((EntityGachapandora*)self)->state = Gachapandora_StatePrize_Destroyed;
	}
	((EntityGachapandora*)self)->invincibilityTimer = 30;
}

void Gachapandora_EnemyInfoHook() {
	Mod.Super(Gachapandora->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Gachapandora->classID, Gachapandora_CheckVulnerable, Gachapandora_GetHitbox, Gachapandora_OnHit, NULL, ATKFLAG_ISBOSS);
}