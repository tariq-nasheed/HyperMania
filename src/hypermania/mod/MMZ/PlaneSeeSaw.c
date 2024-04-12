#include "PlaneSeeSaw.h"

ObjectPlaneSeeSaw* PlaneSeeSaw;

bool32 PlaneSeeSaw_State_Launch_HOOK(bool32 skippedState) {
	if (skippedState) return true;
	RSDK_THIS(PlaneSeeSaw);

	if (self->platformAnimator.frameID <= 4 && self->scale.x == 0x100) {
		foreach_active(SuperFlicky, superFlicky) {
			if (Player_CheckCollisionPlatform(superFlicky->player, self, RSDK.GetHitbox(&self->platformAnimator, 0))) {
				for (int32 s = 0; s < SUPERFLICKY_COUNT; ++s) {
					superFlicky->instanceTarget[s] = NULL;
					superFlicky->instancePos[s].x -= FarPlane->originPos.x;
					superFlicky->instancePos[s].y -= FarPlane->originPos.y;
					superFlicky->instancePos[s].x += FarPlane->position.x;
					superFlicky->instancePos[s].y += FarPlane->position.y;
				}
			}
		}
	}

	return false;
}

bool32 PlaneSeeSaw_PlayerState_ToBG_HOOK(bool32 skippedState) {
	if (skippedState) return true;
	EntityPlayer* self = RSDK_GET_ENTITY(SceneInfo->entitySlot, Player);

	if (self->scale.x <= 0x100 && self->state == Player_State_Air) {
		foreach_active(SuperFlicky, superFlicky) {
			for (int32 s = 0; s < SUPERFLICKY_COUNT; ++s) {
				superFlicky->instanceTarget[s] = NULL;
				superFlicky->instancePos[s].x -= FarPlane->position.x;
				superFlicky->instancePos[s].y -= FarPlane->position.y;
				superFlicky->instancePos[s].x += FarPlane->originPos.x;
				superFlicky->instancePos[s].y += FarPlane->originPos.y;
			}
		}
	}

	return false;
}