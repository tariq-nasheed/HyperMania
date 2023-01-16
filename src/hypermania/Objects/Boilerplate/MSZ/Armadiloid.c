#include "Armadiloid.h"

ObjectArmadiloid *Armadiloid;
void (*Armadiloid_State_Rider)(void);

Hitbox hitbox;

void Armadiloid_EnemyInfoHook(void) {
	hitbox.left   = -10;
	hitbox.top    = -40;
	hitbox.right  = 10;
	hitbox.bottom = -20;
	Mod.Super(Armadiloid->classID, SUPER_STAGELOAD, NULL);
	EnemyDefs[EnemyInfoSlot].classID = Armadiloid->classID;
	EnemyDefs[EnemyInfoSlot].animal = true;
	EnemyDefs[EnemyInfoSlot].states[0].func = Armadiloid_State_Rider;
	EnemyDefs[EnemyInfoSlot].states[0].hitbox = &hitbox;
	++EnemyInfoSlot;
}
