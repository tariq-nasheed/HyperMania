#include "Debris.h"

ObjectDebris* Debris;
void (*Debris_State_Move)();
void (*Debris_State_FallAndFlicker)();

void Debris_Draw_OVERLOAD() {
	RSDK_THIS(Debris);
	if (HPZSetup && self->gravityStrength == 0x4800) { // TODO write a better check for this
		RSDK.SetActivePalette(6, 0, ScreenInfo->size.y);
		Mod.Super(Debris->classID, SUPER_DRAW, NULL);
		RSDK.SetActivePalette(0, 0, ScreenInfo->size.y);
	} else {
		Mod.Super(Debris->classID, SUPER_DRAW, NULL);
	}
}