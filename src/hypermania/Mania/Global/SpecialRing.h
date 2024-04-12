#pragma once

struct ObjectSpecialRing {
	RSDK_OBJECT
	uint16 aniFrames;
	Hitbox hitbox;
	uint16 sfxSpecialRing;
	uint16 sfxSpecialWarp;
	uint16 modelIndex;
	uint16 sceneIndex;
};

struct EntitySpecialRing {
	RSDK_ENTITY
	StateMachine(state);
	int32 id;
	int32 planeFilter;
	int32 warpTimer;
	int32 sparkleRadius;
	Animator warpAnimator;
	int32 angleZ;
	int32 angleY;
	bool32 enabled;
	Matrix matTempRot;
	Matrix matTransform;
	Matrix matWorld;
	Matrix matNormal;
};