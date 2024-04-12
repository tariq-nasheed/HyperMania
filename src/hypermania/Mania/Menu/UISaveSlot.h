#pragma once

typedef enum {
	UISAVESLOT_REGULAR,
	UISAVESLOT_NOSAVE,
} UISaveSlotTypes;

struct ObjectUISaveSlot {
	RSDK_OBJECT
	uint16 aniFrames;
};

struct EntityUISaveSlot {
	MANIA_UI_ITEM_BASE
	bool32 isNewSave;
#if MANIA_USE_PLUS
	StateMachine(stateInput);
#endif
	int32 listID;
	int32 frameID;
	int32 saveZoneID;
	int32 saveLives;
#if MANIA_USE_PLUS
	int32 saveContinues;
#endif
	int32 saveEmeralds;
#if MANIA_USE_PLUS
	uint8 saveEncorePlayer;
	uint8 saveEncoreBuddy;
	uint8 saveEncoreFriends[3];
#endif
	UISaveSlotTypes type;
	int32 slotID;
#if MANIA_USE_PLUS
	bool32 encoreMode;
#endif
	bool32 currentlySelected;
	int32 zoneIconSprX;
	int32 textBounceOffset;
	int32 buttonBounceOffset;
	int32 textBouncePos;
	int32 buttonBouncePos;
	int32 fxRadius;
#if MANIA_USE_PLUS
	void *fxRuby;
	bool32 debugEncoreDraw;
	uint8 dCharPoint;
	uint8 dCharPartner;
	uint8 dCharStock1;
	uint8 dCharStock2;
	uint8 dCharStock3;
#endif
	Animator uiAnimator;
	Animator playersAnimator;
	Animator shadowsAnimator;
	Animator livesAnimator;
#if MANIA_USE_PLUS
	Animator continuesAnimator;
#endif
	Animator emeraldsAnimator;
	Animator zoneIconAnimator;
	Animator zoneNameAnimator;
	Animator fuzzAnimator;
	Animator iconBGAnimator;
	Animator saveStatusAnimator;
	Animator numbersAnimator;
	uint16 textFrames;
};
