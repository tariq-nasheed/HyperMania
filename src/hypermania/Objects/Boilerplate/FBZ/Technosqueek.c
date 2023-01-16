#include "Technosqueek.h"

ObjectTechnosqueek *Technosqueek;
void (*Technosqueek_State_MoveHorizontal)(void);
void (*Technosqueek_State_TurnHorizontal)(void);
void (*Technosqueek_State_MoveVertical)(void);
void (*Technosqueek_State_TurnVertical)(void);
void (*Technosqueek_State_Fall)(void);

void Technosqueek_EnemyInfoHook(void) {
	Mod.Super(Technosqueek->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Technosqueek->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Technosqueek_State_MoveHorizontal;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &Technosqueek->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[1].func = Technosqueek_State_TurnHorizontal;
	EnemyDefs[EnemyInfoSlot].states[1].hitbox = &Technosqueek->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[2].func = Technosqueek_State_MoveVertical;
	EnemyDefs[EnemyInfoSlot].states[2].hitbox = &Technosqueek->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[3].func = Technosqueek_State_TurnVertical;
	EnemyDefs[EnemyInfoSlot].states[3].hitbox = &Technosqueek->hitboxBadnik;
	EnemyDefs[EnemyInfoSlot].states[4].func = Technosqueek_State_Fall;
	EnemyDefs[EnemyInfoSlot].states[4].hitbox = &Technosqueek->hitboxBadnik;
	++EnemyInfoSlot;
}