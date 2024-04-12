#pragma once

struct ObjectUFO_Setup {
	RSDK_OBJECT
	StateMachine(deformCB);
	int32 timedOut;
#if MANIA_USE_PLUS
	bool32 encoreStage;
#endif
	int32 machLevel;
	int32 scoreBonus;
	int32 machPoints;
	int32 rings;
	int32 timer;
	int32 ringFrame;
	int32 ringPan;
	int32 spherePan;
	int32 specialStageID;
	int32 machQuotas[3];
	uint8 playFieldLayer;
	uint16 sfxBlueSphere;
	uint16 sfxSSExit;
	uint16 sfxEmerald;
	uint16 sfxEvent;
	bool32 resetToTitle;
};

struct EntityUFO_Setup {
	RSDK_ENTITY
	StateMachine(state);
	int32 timer;
	color fadeColor;
};
