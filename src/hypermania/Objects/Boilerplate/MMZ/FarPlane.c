#include "FarPlane.h"
#include "HyperStars.h"
#include "SuperFlicky.h"
#include "ImageTrail.h"
#include "Global/InvincibleStars.h"

ObjectFarPlane* FarPlane;
void (*FarPlane_SetupEntities)();
void (*FarPlane_SetEntityActivities)(uint8 active);

void FarPlane_LateUpdate_OVERLOAD() {
	RSDK_THIS(FarPlane);

	if (self->active == ACTIVE_ALWAYS) {
		FarPlane_SetupEntities();
	} else if (self->active == ACTIVE_BOUNDS) {
		self->active                                       = ACTIVE_NORMAL;
		RSDK.GetTileLayer(FarPlane->layerID)->drawGroup[0] = 0;

		FarPlane->originPos.x = self->origin.x;
		FarPlane->originPos.y = self->origin.y;

		FarPlane->position.x = self->position.x;
		FarPlane->position.y = self->position.y;

		RSDK.SetDrawGroupProperties(1, false, FarPlane_DrawHook_ApplyFarPlane);
		RSDK.SetDrawGroupProperties(3, false, FarPlane_DrawHook_RemoveFarPlane);

		FarPlane_SetEntityActivities(ACTIVE_NORMAL);
	} else if (!RSDK.CheckOnScreen(self, NULL)) {
		self->active                                       = ACTIVE_BOUNDS;
		RSDK.GetTileLayer(FarPlane->layerID)->drawGroup[0] = DRAWGROUP_COUNT;

		RSDK.SetDrawGroupProperties(1, false, StateMachine_None);
		RSDK.SetDrawGroupProperties(3, false, StateMachine_None);

		FarPlane_SetEntityActivities(ACTIVE_NEVER);
	}
}


void FarPlane_DrawHook_ApplyFarPlane() {
	int32 id = 0;
	for (int32 i = 0; i < 0x200 && id < 0x200; ++i) {
		Entity *entity = RSDK.GetDrawListRef(1, i);
		if (!entity)
			break;

		FarPlane->positionList[id].x = entity->position.x;
		FarPlane->positionList[id].y = entity->position.y;

		entity->position.x = FarPlane->worldPos.x + ((entity->position.x - FarPlane->originPos.x) >> 1);
		entity->position.y = FarPlane->worldPos.y + ((entity->position.y - FarPlane->originPos.y) >> 1);
		entity->drawFX |= FX_SCALE;
		entity->scale.x = 0x100;
		entity->scale.y = 0x100;
		id++;
	}

	for (int32 i = 0; i < 0x200 && id < 0x200; ++i) {
		Entity *entity = RSDK.GetDrawListRef(2, i);
		if (!entity)
			break;

		FarPlane->positionList[id].x = entity->position.x;
		FarPlane->positionList[id].y = entity->position.y;
		entity->position.x           = FarPlane->worldPos.x + ((entity->position.x - FarPlane->originPos.x) >> 1);
		entity->position.y           = FarPlane->worldPos.y + ((entity->position.y - FarPlane->originPos.y) >> 1);
		entity->drawFX |= FX_SCALE;
		entity->scale.x = 0x100;
		entity->scale.y = 0x100;
		id++;
	}

	foreach_active(InvincibleStars, invincibleStars) {
		if (invincibleStars->drawGroup < 3 && id < 0x200) {
			invincibleStars->starOffset = 10;
			invincibleStars->drawFX     = FX_SCALE;
			invincibleStars->scale.x    = 0x100;
			invincibleStars->scale.y    = 0x100;

			for (int32 s = 0; s < 8; ++s) {
				FarPlane->positionList[id].x = invincibleStars->starPos[s].x;
				FarPlane->positionList[id].y = invincibleStars->starPos[s].y;

				invincibleStars->starPos[s].x = FarPlane->worldPos.x + ((invincibleStars->starPos[s].x - FarPlane->originPos.x) >> 1);
				invincibleStars->starPos[s].y = FarPlane->worldPos.y + ((invincibleStars->starPos[s].y - FarPlane->originPos.y) >> 1);

				id++;
			}
		}
	}

	foreach_active(ImageTrail, imageTrail) {
		if (imageTrail->drawGroup < 3 && id < 0x200) {
			imageTrail->scale.x = 0x100;
			imageTrail->scale.y = 0x100;

			FarPlane->positionList[id].x = imageTrail->currentPos.x;
			FarPlane->positionList[id].y = imageTrail->currentPos.y;

			imageTrail->currentPos.x = FarPlane->worldPos.x + ((imageTrail->currentPos.x - FarPlane->originPos.x) >> 1);
			imageTrail->currentPos.y = FarPlane->worldPos.y + ((imageTrail->currentPos.y - FarPlane->originPos.y) >> 1);

			id++;

			for (int32 s = 0; s < 7; ++s) {
				FarPlane->positionList[id].x = imageTrail->statePos[s].x;
				FarPlane->positionList[id].y = imageTrail->statePos[s].y;

				imageTrail->statePos[s].x = FarPlane->worldPos.x + ((imageTrail->statePos[s].x - FarPlane->originPos.x) >> 1);
				imageTrail->statePos[s].y = FarPlane->worldPos.y + ((imageTrail->statePos[s].y - FarPlane->originPos.y) >> 1);

				id++;
			}

			ImageTrailExt* ext = (ImageTrailExt*)GetExtMem(RSDK.GetEntitySlot(imageTrail));
			if (ext && id < 0x200) {
				FarPlane->positionList[id].x = ext->statePos[0].x;
				FarPlane->positionList[id].y = ext->statePos[0].y;
				ext->statePos[0].x = FarPlane->worldPos.x + ((ext->statePos[0].x - FarPlane->originPos.x) >> 1);
				ext->statePos[0].y = FarPlane->worldPos.y + ((ext->statePos[0].y - FarPlane->originPos.y) >> 1);
				id++;
			}
		}
	}

	foreach_active (SuperFlicky, superFlicky) {
		if (superFlicky->drawGroup < 3 && id < 0x200) {
			for (int32 s = 0; s < SUPERFLICKY_COUNT; ++s) {
				FarPlane->positionList[id].x = superFlicky->instancePos[s].x;
				FarPlane->positionList[id].y = superFlicky->instancePos[s].y;

				superFlicky->instancePos[s].x = FarPlane->worldPos.x + ((superFlicky->instancePos[s].x - FarPlane->originPos.x) >> 1);
				superFlicky->instancePos[s].y = FarPlane->worldPos.y + ((superFlicky->instancePos[s].y - FarPlane->originPos.y) >> 1);

				id++;
			}
		}
	}

	foreach_active(HyperStars, hyperStars) {
		if (hyperStars->drawGroup < 3 && id < 0x200) {
			hyperStars->drawFX  = FX_SCALE;
			hyperStars->scale.x = 0x100;
			hyperStars->scale.y = 0x100;
			for (int32 s = 0; s < HYPERSTARS_COUNT; ++s) {
				FarPlane->positionList[id].x = hyperStars->instancePos[s].x;
				FarPlane->positionList[id].y = hyperStars->instancePos[s].y;

				hyperStars->instancePos[s].x = FarPlane->worldPos.x + ((hyperStars->instancePos[s].x - FarPlane->originPos.x) >> 1);
				hyperStars->instancePos[s].y = FarPlane->worldPos.y + ((hyperStars->instancePos[s].y - FarPlane->originPos.y) >> 1);

				id++;
			}
		}
	}
}

void FarPlane_DrawHook_RemoveFarPlane() {
	int32 id = 0;
	for (int32 i = 0; i < 0x200 && id < 0x200; ++i) {
		Entity *entity = RSDK.GetDrawListRef(1, i);
		if (!entity)
			break;

		entity->position.x = FarPlane->positionList[id].x;
		entity->position.y = FarPlane->positionList[id].y;
		id++;
	}

	for (int32 i = 0; i < 0x200 && id < 0x200; ++i) {
		Entity *entity = RSDK.GetDrawListRef(2, i);
		if (!entity)
			break;

		entity->position.x = FarPlane->positionList[id].x;
		entity->position.y = FarPlane->positionList[id].y;
		id++;
	}

	/*foreach_active(InvincibleStars, invincibleStars) {
		if (invincibleStars->drawGroup == 1 && id < 0x200) {
			for (int32 s = 0; s < 8; ++s) {
				invincibleStars->starPos[s].x = FarPlane->positionList[id].x;
				invincibleStars->starPos[s].y = FarPlane->positionList[id].y;
				id++;
			}
		}
	}*/

	foreach_active(ImageTrail, imageTrail) {
		if (imageTrail->drawGroup == 1 && id < 0x200) {
			imageTrail->currentPos.x = FarPlane->positionList[id].x;
			imageTrail->currentPos.y = FarPlane->positionList[id].y;
			id++;

			for (int32 s = 0; s < 7; ++s) {
				imageTrail->statePos[s].x = FarPlane->positionList[id].x;
				imageTrail->statePos[s].y = FarPlane->positionList[id].y;
				id++;
			}

			ImageTrailExt* ext = (ImageTrailExt*)GetExtMem(RSDK.GetEntitySlot(imageTrail));
			if (ext && id < 0x200) {
				ext->statePos[0].x = FarPlane->positionList[id].x;
				ext->statePos[0].y = FarPlane->positionList[id].y;
				id++;
			}
		}
	}

	foreach_active (SuperFlicky, superFlicky) {
		if (superFlicky->drawGroup == 2 && id < 0x200) {
			for (int32 s = 0; s < SUPERFLICKY_COUNT; ++s) {
				superFlicky->instancePos[s].x = FarPlane->positionList[id].x;
				superFlicky->instancePos[s].y = FarPlane->positionList[id].y;
				id++;
			}
		}
	}

	foreach_active(HyperStars, hyperStars) {
		if (hyperStars->drawGroup == 2 && id < 0x200) {
			for (int32 s = 0; s < HYPERSTARS_COUNT; ++s) {
				hyperStars->instancePos[s].x = FarPlane->positionList[id].x;
				hyperStars->instancePos[s].y = FarPlane->positionList[id].y;
				id++;
			}
		}
	}
}