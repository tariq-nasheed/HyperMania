#ifndef OBJ_UISAVESLOT_H
#define OBJ_UISAVESLOT_H

#include "GameAPI/Game.h"

typedef enum {
    UISAVESLOT_REGULAR,
    UISAVESLOT_NOSAVE,
} UISaveSlotTypes;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectUISaveSlot;

typedef struct {
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
} EntityUISaveSlot;

extern ObjectUISaveSlot *UISaveSlot;

typedef struct {
	int32 SEAniFrames;
	Animator SEAnimator;
} UISaveSlotStaticExt_t;

typedef struct {
	HM_SaveRAM* save;
} UISaveSlotExt;

extern UISaveSlotStaticExt_t UISaveSlotStaticExt;


// =============================================================================

// Functions -------------------------------------------------------------------

// =============================================================================
void UISaveSlot_StaticUpdate_OVERLOAD();
void UISaveSlot_Draw_OVERLOAD();
void UISaveSlot_Create_OVERLOAD(void* data);
void UISaveSlot_StageLoad_OVERLOAD();

#define OBJ_UISAVESLOT_SETUP \
  MOD_REGISTER_OBJ_OVERLOAD(UISaveSlot, NULL, NULL, UISaveSlot_StaticUpdate_OVERLOAD, UISaveSlot_Draw_OVERLOAD, UISaveSlot_Create_OVERLOAD, UISaveSlot_StageLoad_OVERLOAD, NULL, NULL, NULL)

#endif //! OBJ_UISAVESLOT_H
