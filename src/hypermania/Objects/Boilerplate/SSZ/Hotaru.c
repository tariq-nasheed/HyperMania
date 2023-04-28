#include "Hotaru.h"

ObjectHotaru* Hotaru;

Hitbox* Hotaru_GetHitbox(Entity* self) { return &(Hotaru->hitboxBadnik); }

void Hotaru_OnHit(EntityPlayer* player, Entity* self) {
	Vector2 position = self->position;
	if (!(((EntityHotaru*)self)->destroyedHotarus & 1)) {
		position.x += ((EntityHotaru*)self)->offset1.x;
		position.y += ((EntityHotaru*)self)->offset1.y;
		Generic_BadnikBreak_NoEntity(player, position, true);
		((EntityHotaru*)self)->destroyedHotarus |= 1;
		if (SceneInfo->entity->classID == SuperFlicky->classID) return;
	}
	if (!(((EntityHotaru*)self)->destroyedHotarus & 2)) {
		position.x += ((EntityHotaru*)self)->offset2.x;
		position.y += ((EntityHotaru*)self)->offset2.y;
		Generic_BadnikBreak_NoEntity(player, position, true);
		((EntityHotaru*)self)->destroyedHotarus |= 2;
	}
}

void Hotaru_AdjustPos(Entity* self) {
	if (!(((EntityHotaru*)self)->destroyedHotarus & 1)) {
		self->position.x += ((EntityHotaru*)self)->offset1.x;
		self->position.y += ((EntityHotaru*)self)->offset1.y;
	} else if (!(((EntityHotaru*)self)->destroyedHotarus & 2)) {
		self->position.x += ((EntityHotaru*)self)->offset2.x;
		self->position.y += ((EntityHotaru*)self)->offset2.y;
	}
}

void Hotaru_EnemyInfoHook() {
	Mod.Super(Hotaru->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(Hotaru->classID, Generic_CheckVulnerable, Hotaru_GetHitbox, Hotaru_OnHit, Hotaru_AdjustPos, ATKFLAG_NONE);
}