#pragma once

struct ObjectPhantomMystic {
	RSDK_OBJECT
	uint16 aniFrames;
	uint16 sfxCupSwap;
	uint16 sfxBigLaser;
	uint16 sfxImpact;
};

struct EntityPhantomMystic {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	Vector2 originPos;
	Vector2 mysticPos;
	int32 mysticVelY;
	int32 middleCupY;
	int32 timer;
	int32 invincibilityTimer;
	int32 correctCup;
	int32 cupPos[3];
	int32 unused1[3];
	int32 unused2[3];
	int32 cupAlpha[3];
	int32 swapCup1;
	int32 swapCup2;
	int32 swapCup1Pos;
	int32 swapCup2Pos;
	int32 swapCup1Alpha;
	int32 swapCup2Alpha;
	int32 cupSwapCount;
	Animator mysticAnimator;
	Animator cupAnimator;
	Animator cupSilhouetteAnimator;
	Animator cupSpikeAnimator; // Not actually ever drawn...
	Animator cupBlastAnimator;
	Hitbox hitbox;
};
