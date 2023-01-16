#include "MicDrop.h"

ObjectMicDrop *MicDrop;
void (*MicDrop_State_CheckForPlayer)(void);
void (*MicDrop_State_DropDown)(void);
void (*MicDrop_State_DropRecoil)(void);
void (*MicDrop_State_Idle)(void);
void (*MicDrop_State_Swinging)(void);
void (*MicDrop_State_Electrify)(void);

void MicDrop_EnemyInfoHook(void) {
	Mod.Super(MicDrop->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = MicDrop->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = MicDrop_State_CheckForPlayer;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &MicDrop->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = MicDrop_State_DropDown;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &MicDrop->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = MicDrop_State_DropRecoil;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &MicDrop->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = MicDrop_State_Idle;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &MicDrop->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[4].func = MicDrop_State_Swinging;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &MicDrop->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[5].func = MicDrop_State_Electrify;
	EnemyDefs[EnemyInfoSlot].states[5].hitbox = &MicDrop->hitboxBadnik;
	++EnemyInfoSlot;
}