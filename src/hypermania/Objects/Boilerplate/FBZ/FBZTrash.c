#include "FBZTrash.h"

Hitbox hitbox;
ObjectFBZTrash *FBZTrash;
void (*FBZTrash_State_OrbinautMove)(void);

void FBZTrash_EnemyInfoHook(void) {
	hitbox.left   = -8;
	hitbox.top    = -8;
	hitbox.right  = 8;
	hitbox.bottom = 8;
	Mod.Super(FBZTrash->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = FBZTrash->classID;
	EnemyDefs[EnemyInfoSlot].animal = false;
	EnemyDefs[EnemyInfoSlot].states[0].func = FBZTrash_State_OrbinautMove;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &hitbox;
	++EnemyInfoSlot;
}
