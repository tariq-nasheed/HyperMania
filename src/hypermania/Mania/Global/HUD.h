#pragma once

struct ObjectHUD {
	RSDK_OBJECT
	uint16 aniFrames;
#if GAME_VERSION != VER_100
	uint16 superButtonFrames;
#endif
#if MANIA_USE_PLUS
	uint16 sfxClick;
	uint16 sfxStarpost;
	bool32 showTAPrompt;
	bool32 replaySaveEnabled;
	int32 screenBorderType[PLAYER_COUNT];
	int32 swapCooldown;
	int32 stockFlashTimers[PLAYER_COUNT];
#endif
};

struct EntityHUD {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 scorePos;
	Vector2 timePos;
	Vector2 ringsPos;
	Vector2 lifePos;
#if MANIA_USE_PLUS
	int32 lifeFrameIDs[PLAYER_COUNT];
	int32 lives[PLAYER_COUNT];
#endif
	int32 targetPos;
#if GAME_VERSION != VER_100
	int32 actionPromptPos;
#endif
#if MANIA_USE_PLUS
	StateMachine(vsStates[PLAYER_COUNT]);
	Vector2 vsScorePos[PLAYER_COUNT];
	Vector2 vsTimePos[PLAYER_COUNT];
	Vector2 vsRingsPos[PLAYER_COUNT];
	Vector2 vsLifePos[PLAYER_COUNT];
	int32 vsTargetPos[PLAYER_COUNT];
	int32 screenID;
#endif
#if GAME_VERSION != VER_100
	int32 timeFlashFrame;
#endif
	int32 ringFlashFrame;
	bool32 enableTimeFlash;
	bool32 enableRingFlash;
	Animator hudElementsAnimator;
	Animator numbersAnimator;
	Animator hyperNumbersAnimator;
	Animator lifeIconAnimator;
	Animator playerIDAnimator;
#if GAME_VERSION != VER_100
	Animator superIconAnimator;
	Animator superButtonAnimator;
#endif
#if MANIA_USE_PLUS
	Animator thumbsUpIconAnimator;
	Animator thumbsUpButtonAnimator;
	Animator replayClapAnimator;
	Animator saveReplayButtonAnimator;
#endif
};