#pragma once

typedef enum {
	SC_MSG_SPECIALCLEAR,
	SC_MSG_GOTEMERALD,
	SC_MSG_ALLEMERALDS,
	SC_MSG_SUPER,
} SpecialClearTypes;

typedef enum {
	SC_ANI_SONIC,
	SC_ANI_TAILS,
	SC_ANI_KNUX,
#if MANIA_USE_PLUS
	SC_ANI_MIGHTY,
	SC_ANI_RAY,
#endif
	SC_ANI_BONUS,
	SC_ANI_NUMBERS,
	SC_ANI_EMERALDS,
#if MANIA_USE_PLUS
	SC_ANI_CONTINUE,
#endif
} SpecialClearAniIDs;

struct ObjectSpecialClear {
	RSDK_OBJECT
	uint16 aniFrames;
#if !MANIA_USE_PLUS
	uint16 continueFrames;
#endif
	uint16 sfxScoreAdd;
	uint16 sfxScoreTotal;
	uint16 sfxEvent;
	uint16 sfxSpecialWarp;
	uint16 sfxContinue;
	uint16 sfxEmerald;
};

struct EntitySpecialClear {
	RSDK_ENTITY
	StateMachine(state);
	bool32 isBSS;
	int32 messageType;
	int32 timer;
	bool32 showFade;
	bool32 continueIconVisible;
	bool32 hasContinues;
	int32 fillColor;
	int32 score;
	int32 score1UP;
	int32 lives;
	int32 ringBonus;
	int32 perfectBonus;
	int32 machBonus;
	Vector2 messagePos1;
	Vector2 messagePos2;
	Vector2 scoreBonusPos;
	Vector2 ringBonusPos;
	Vector2 perfectBonusPos;
	Vector2 machBonusPos;
	Vector2 continuePos;
	int32 emeraldPositions[7];
	int32 emeraldSpeeds[7];
	int32 unused1;
	int32 unused2;
	int32 unused3;
	int32 unused4;
	int32 unused5;
	int32 unused6;
	int32 unused7;
	int32 unused8;
	bool32 saveInProgress;
	Animator playerNameAnimator;
	Animator bonusAnimator;
	Animator numbersAnimator;
	Animator emeraldsAnimator;
	Animator continueAnimator;
};