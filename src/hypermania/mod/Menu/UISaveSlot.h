#pragma once

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
extern void (*UIWidgets_DrawRectOutline_Black)(int32 x, int32 y, int32 width, int32 height);
extern void (*UIWidgets_DrawRectOutline_Blended)(int32 x, int32 y, int32 width, int32 height);
extern void (*UIWidgets_DrawRectOutline_Flash)(int32 x, int32 y, int32 width, int32 height);
extern void (*UIWidgets_DrawRightTriangle)(int32 x, int32 y, int32 size, int32 red, int32 green, int32 blue);
extern void (*UIWidgets_DrawUpDownArrows)(int32 x, int32 y, int32 arrowDist);
extern void (*UISaveSlot_DrawPlayerIcons)(int32 drawX, int32 drawY);
extern void (*UISaveSlot_DrawPlayerInfo)(int32 drawX, int32 drawY);
extern void (*UISaveSlot_State_Selected)();

void UISaveSlot_StaticUpdate_OVERLOAD();
void UISaveSlot_Draw_OVERLOAD();
void UISaveSlot_Create_OVERLOAD(void* data);
void UISaveSlot_StageLoad_OVERLOAD();

#define OBJ_UISAVESLOT_SETUP \
  IMPORT_PUBLIC_FUNC(UIWidgets_DrawRightTriangle); \
  IMPORT_PUBLIC_FUNC(UIWidgets_DrawRectOutline_Flash); \
  IMPORT_PUBLIC_FUNC(UIWidgets_DrawRectOutline_Black); \
  IMPORT_PUBLIC_FUNC(UIWidgets_DrawRectOutline_Blended); \
  IMPORT_PUBLIC_FUNC(UIWidgets_DrawUpDownArrows); \
  IMPORT_PUBLIC_FUNC(UISaveSlot_DrawPlayerIcons); \
  IMPORT_PUBLIC_FUNC(UISaveSlot_DrawPlayerInfo); \
  IMPORT_PUBLIC_FUNC(UISaveSlot_State_Selected); \
  MOD_REGISTER_OBJ_OVERLOAD(UISaveSlot, NULL, NULL, UISaveSlot_StaticUpdate_OVERLOAD, UISaveSlot_Draw_OVERLOAD, UISaveSlot_Create_OVERLOAD, UISaveSlot_StageLoad_OVERLOAD, NULL, NULL, NULL)
