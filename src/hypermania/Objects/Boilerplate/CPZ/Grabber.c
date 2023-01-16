#include "Grabber.h"

ObjectGrabber *Grabber;
void (*Grabber_State_CheckForGrab)(void);
void (*Grabber_State_GrabDelay)(void);
void (*Grabber_State_HandleTurn)(void);
void (*Grabber_State_TryToGrab)(void);
void (*Grabber_State_RiseUp)(void);
void (*Grabber_State_GrabbedPlayer)(void);
void (*Grabber_State_Struggle)(void);
void (*Grabber_State_PlayerEscaped)(void);

void Grabber_EnemyInfoHook(void) {
	Mod.Super(Grabber->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Grabber->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Grabber_State_CheckForGrab;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Grabber->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Grabber_State_GrabDelay;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Grabber->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Grabber_State_HandleTurn;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Grabber->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = Grabber_State_TryToGrab;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Grabber->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[4].func = Grabber_State_RiseUp;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &Grabber->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[5].func = Grabber_State_GrabbedPlayer;
	EnemyDefs[EnemyInfoSlot].states[5].hitbox = &Grabber->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[6].func = Grabber_State_Struggle;
	EnemyDefs[EnemyInfoSlot].states[6].hitbox = &Grabber->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[7].func = Grabber_State_PlayerEscaped;
	EnemyDefs[EnemyInfoSlot].states[7].hitbox = &Grabber->hitboxBadnik;
	++EnemyInfoSlot;
}