#include "DDWrecker.h"

ObjectDDWrecker *DDWrecker;
void (*DDWrecker_StateBall_Vulnerable)(void);
void (*DDWrecker_StateBall_Partnerless)(void);
void (*DDWrecker_StateBall_Spiked)(void);
void (*DDWrecker_State_Die)(void);
void (*DDWrecker_State_EndBounceAttack)(void);
void (*DDWrecker_State_Debris)(void);

void DDWrecker_EnemyInfoHook(void) {
	Mod.Super(DDWrecker->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = DDWrecker->classID;
	EnemyDefs[EnemyInfoSlot].animal = false;
	EnemyDefs[EnemyInfoSlot].boss = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = DDWrecker_StateBall_Vulnerable;
	EnemyDefs[EnemyInfoSlot].states[1].func = DDWrecker_StateBall_Partnerless;
	EnemyDefs[EnemyInfoSlot].states[2].func = DDWrecker_StateBall_Spiked;
	EnemyDefs[EnemyInfoSlot].check_func = DDWrecker_CheckVulnerable;
	EnemyDefs[EnemyInfoSlot].hitbox_func = DDWrecker_GetHitbox;
	EnemyDefs[EnemyInfoSlot].destroy_func = DDWrecker_TakeHit;
	++EnemyInfoSlot;
}

bool32 DDWrecker_CheckVulnerable(Entity* e) {
	//ja aopsdfiasghdofas dcjoisapdfuasdfasdf
	EntityDDWrecker* self = (EntityDDWrecker*)e;
	for (int32 i = 0; i != EnemyInfoSlot; ++i) {
		if (EnemyDefs[i].classID != self->classID) continue;
		for (int32 l = 0; l != 8; ++l) {
			if (!EnemyDefs[i].states[l].func) break;
			if (EnemyDefs[i].states[l].func == self->stateBall) {
				return true;
			}
		}
	}
	return false;
}

Hitbox* DDWrecker_GetHitbox(Entity* e) {
	EntityDDWrecker* self = (EntityDDWrecker*)e;
	return &self->hitbox;
}

void DDWrecker_TakeHit(EntityPlayer* player, Entity* e) {
	EntityDDWrecker* self = (EntityDDWrecker*)e;
	if (!self->invincibilityTimer) {
		if (--self->health <= 0) {
			self->state     = DDWrecker_State_Die;
			self->stateBall = StateMachine_None;
			self->timer     = 0;
			foreach_active(DDWrecker, child) {
				if (self != child) {
					switch (child->type) {
						case DDWRECKER_BALL1:
						case DDWRECKER_BALL2:
							if (child->stateBall) {
								child->state       = DDWrecker_State_EndBounceAttack;
								child->originPos.y = child->position.y;
								child->velocity.x  = -DDWrecker->attackVelocities[2];
								child->stateBall   = DDWrecker_StateBall_Partnerless;
							}
							break;

						case DDWRECKER_CHAIN:
						case DDWRECKER_CORE:
							if (child->state != DDWrecker_State_Debris) {
								child->state      = DDWrecker_State_Debris;
								child->velocity.x = RSDK.Rand(-0x20000, 0x20000);
								child->velocity.y = RSDK.Rand(-0x20000, 0x20000);
							}
							break;

						default: break;
					}
				}
			}
		}
		else {
			self->invincibilityTimer = 48;
			RSDK.PlaySfx(DDWrecker->sfxBossHit, false, 255);
		}
	}
}