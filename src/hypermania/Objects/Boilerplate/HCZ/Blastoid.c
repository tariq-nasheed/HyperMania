#include "Blastoid.h"

ObjectBlastoid *Blastoid;
void (*Blastoid_State_Body)(void);

void Blastoid_EnemyInfoHook(void) {
	Mod.Super(Blastoid->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Blastoid->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Blastoid_State_Body;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Blastoid->hitboxBody;
	EnemyDefs[EnemyInfoSlot].destroy_func = Blastoid_Destroy;
	++EnemyInfoSlot;
}

void Blastoid_Destroy(EntityPlayer* player, Entity* e) {
	EntityBlastoid* self = (EntityBlastoid*)e;
	EntityCollapsingPlatform *platform = RSDK_GET_ENTITY(RSDK.GetEntitySlot(self) - 1, CollapsingPlatform);
	if (platform->classID == CollapsingPlatform->classID) {
		platform->active        = ACTIVE_NORMAL;
		platform->collapseDelay = 30;
		platform->stoodPos.x    = self->position.x;
	}
	BreakBadnik(player, e);
}
