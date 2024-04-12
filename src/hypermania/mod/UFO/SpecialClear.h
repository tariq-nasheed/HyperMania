#pragma once

// =============================================================================

// Definitions -----------------------------------------------------------------

// =============================================================================
extern ObjectSpecialClear *SpecialClear;

typedef struct {
	int32 SEAniFrames;
	Animator SEAnimator;
	bool32 startFadingBackground;
	int32 backgroundFade;
	bool32 drawContinue;
	int32 sparkleAniFrames;
	int32 sparkleType; // 0 - none, 1 - normal, 2 - inverted
	Vector2 sparkleTarget;
	int32 sparkleAngle;
	int32 sparkleDistance;
	Vector2 sparklePos[16];
	Animator sparkleAnimator[16];
} SpecialClearStaticExt_t;

extern SpecialClearStaticExt_t SpecialClearStaticExt;


// =============================================================================

// Functions -------------------------------------------------------------------

// =============================================================================
bool32 SpecialClear_State_TallyScore_HOOK(bool32);
bool32 SpecialClear_State_ShowTotalScore_Continues_HOOK(bool32);
bool32 SpecialClear_State_ShowTotalScore_NoContinues_HOOK(bool32);

extern void (*SpecialClear_State_EnterText)();
extern void (*SpecialClear_State_TallyScore)();
extern void (*SpecialClear_State_ExitFinishMessage)();
extern void (*SpecialClear_State_ExitResults)();
extern void (*SpecialClear_DrawNumbers)(Vector2 *pos, int32 value);

void SpecialClear_Update_OVERLOAD();
void SpecialClear_Draw_OVERLOAD();
void SpecialClear_Create_OVERLOAD(void* data);
void SpecialClear_StageLoad_OVERLOAD();

void SpecialClear_State_WaitToRevealSuperEmerald();
void SpecialClear_State_SetupDelay();
void SpecialClear_State_RevealSuperEmerald();
void SpecialClear_State_ActivateSuperEmerald();
void SpecialClear_State_RevealMasterEmerald();
void SpecialClear_State_ActivateMasterEmerald();
void SpecialClear_State_EnterHyperMessage();
void SpecialClear_State_ShowHyperMessage();

#define OBJ_SPECIALCLEAR_SETUP \
  IMPORT_PUBLIC_FUNC(SpecialClear_State_EnterText); \
  IMPORT_PUBLIC_FUNC(SpecialClear_State_TallyScore); \
  IMPORT_PUBLIC_FUNC(SpecialClear_State_ExitFinishMessage); \
  IMPORT_PUBLIC_FUNC(SpecialClear_State_ExitResults); \
  IMPORT_PUBLIC_FUNC(SpecialClear_DrawNumbers); \
  HOOK_IMPORTED_STATE(SpecialClear_State_TallyScore, 0); \
  HOOK_STATE(SpecialClear_State_ShowTotalScore_Continues, 1); \
  HOOK_STATE(SpecialClear_State_ShowTotalScore_NoContinues, 1); \
  MOD_REGISTER_OBJ_OVERLOAD(SpecialClear, SpecialClear_Update_OVERLOAD, NULL, NULL, SpecialClear_Draw_OVERLOAD, SpecialClear_Create_OVERLOAD, SpecialClear_StageLoad_OVERLOAD, NULL, NULL, NULL)
