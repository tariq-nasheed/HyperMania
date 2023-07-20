// WARNING: this file is heavily auto-generated, only modify if you know what you are doing
#include "Enemy.h"
// .c includes start on line 3
#include "Boilerplate/ERZ/PhantomMystic.c"
#include "Boilerplate/ERZ/PhantomShinobi.c"
#include "Boilerplate/ERZ/PhantomEgg.c"
#include "Boilerplate/TMZ/CrimsonEye.c"
#include "Boilerplate/MMZ/Gachapandora.c"
#include "Boilerplate/MMZ/EggPistonsMKII.c"
#include "Boilerplate/LRZ/RockDrill.c"
#include "Boilerplate/LRZ/HeavyKing.c"
#include "Boilerplate/LRZ/HeavyRider.c"
#include "Boilerplate/LRZ/DrillerdroidO.c"
#include "Boilerplate/LRZ/Drillerdroid.c"
#include "Boilerplate/OOZ/MegaOctus.c"
#include "Boilerplate/OOZ/MeterDroid.c"
#include "Boilerplate/MSZ/HeavyMystic.c"
#include "Boilerplate/MSZ/DBTower.c"
#include "Boilerplate/MSZ/UberCaterkiller.c"
#include "Boilerplate/HCZ/LaundroMobile.c"
#include "Boilerplate/SSZ/GigaMetal.c"
#include "Boilerplate/SSZ/MetalSonic.c"
#include "Boilerplate/SSZ/HotaruHiWatt.c"
#include "Boilerplate/PGZ/HeavyShinobi.c"
#include "Boilerplate/PGZ/Shiversaw.c"
#include "Boilerplate/FBZ/BigSqueeze.c"
#include "Boilerplate/SPZ/WeatherMobile.c"
#include "Boilerplate/CPZ/AmoebaDroid.c"
#include "Boilerplate/GHZ/DERobot.c"
#include "Boilerplate/GHZ/DDWrecker.c"


#include "Boilerplate/TMZ/FlasherMKII.c"
#include "Boilerplate/TMZ/TurboTurtle.c"
#include "Boilerplate/TMZ/SentryBug.c"
#include "Boilerplate/TMZ/BallHog.c"
#include "Boilerplate/MMZ/PohBee.c"
#include "Boilerplate/MMZ/Scarab.c"
#include "Boilerplate/MMZ/MechaBu.c"
#include "Boilerplate/LRZ/Fireworm.c"
#include "Boilerplate/LRZ/Rexon.c"
#include "Boilerplate/LRZ/Toxomister.c"
#include "Boilerplate/OOZ/Octus.c"
#include "Boilerplate/OOZ/Sol.c"
#include "Boilerplate/OOZ/Aquis.c"
#include "Boilerplate/MSZ/Rattlekiller.c"
#include "Boilerplate/MSZ/RollerMKII.c"
#include "Boilerplate/MSZ/Vultron.c"
#include "Boilerplate/MSZ/Bumpalo.c"
#include "Boilerplate/MSZ/Armadiloid.c"
#include "Boilerplate/MSZ/Cactula.c"
#include "Boilerplate/MSZ/Hatterkiller.c"
#include "Boilerplate/HCZ/TurboSpiker.c"
#include "Boilerplate/HCZ/Buggernaut.c"
#include "Boilerplate/HCZ/MegaChopper.c"
#include "Boilerplate/HCZ/Jawz.c"
#include "Boilerplate/HCZ/Jellygnite.c"
#include "Boilerplate/HCZ/Blastoid.c"
#include "Boilerplate/HCZ/Pointdexter.c"
#include "Boilerplate/SSZ/Kabasira.c"
#include "Boilerplate/SSZ/Dango.c"
#include "Boilerplate/SSZ/Kanabun.c"
#include "Boilerplate/SSZ/HotaruMKII.c"
#include "Boilerplate/SSZ/Hotaru.c"
#include "Boilerplate/PGZ/Woodrow.c"
#include "Boilerplate/PGZ/Dragonfly.c"
#include "Boilerplate/PGZ/IceBomba.c"
#include "Boilerplate/PGZ/JuggleSaw.c"
#include "Boilerplate/FBZ/FBZTrash.c"
#include "Boilerplate/FBZ/Technosqueek.c"
#include "Boilerplate/FBZ/Clucker.c"
#include "Boilerplate/FBZ/Blaster.c"
#include "Boilerplate/SPZ/Shutterbug.c"
#include "Boilerplate/SPZ/Canista.c"
#include "Boilerplate/SPZ/Tubinaut.c"
#include "Boilerplate/SPZ/MicDrop.c"
#include "Boilerplate/CPZ/Grabber.c"
#include "Boilerplate/CPZ/Spiny.c"
#include "Boilerplate/CPZ/CaterkillerJr.c"
#include "Boilerplate/CPZ/Bubbler.c"
#include "Boilerplate/GHZ/Splats.c"
#include "Boilerplate/GHZ/Newtron.c"
#include "Boilerplate/GHZ/Chopper.c"
#include "Boilerplate/GHZ/Crabmeat.c"
#include "Boilerplate/GHZ/Batbrain.c"
#include "Boilerplate/GHZ/Motobug.c"
#include "Boilerplate/GHZ/BuzzBomber.c"

EnemyInfo EnemyDefs[32];
int16 EnemyInfoSlot;






int8 EntAttackIndex[ENTITY_COUNT];
attackinfo_t AttackableClasses[MAX_ATTACKABLE_CLASSES];
uint32       AttackableClasses_size;
int32        AttackableClasses_startidx;

bool32 IsAttackableEntity(Entity* self, uint8 blacklist_mask) {
	if (!self || AttackableClasses_startidx > self->classID) return false;
	const uint32 index = self->classID - AttackableClasses_startidx;
	if (index >= MAX_ATTACKABLE_CLASSES || !AttackableClasses[index].checkVulnerable) return false;
	return (AttackableClasses[index].checkVulnerable(self) && !(AttackableClasses[index].flags & blacklist_mask)); // mask check happens at the very end to account for hotaru hi-watts BULLSHIT
}


bool32 Generic_CheckVulnerable(Entity* self) {
	return true;
}

Hitbox* Generic_GetHitbox(Entity* self) {
	return NULL;
}

void Generic_OnHit(EntityPlayer* player, Entity* self) {
	uint8 flags = EntAttackIndex[RSDK.GetEntitySlot(self)];
	Generic_BadnikBreak(player, self, (flags & ATKFLAG_NOANIMAL) ? false : true);
}







bool32 IsVulnerableEnemy(void* e, bool32 count_bosses) {
	if (!e) return false;

	EntityEnemy* entity = (EntityEnemy*)e;
	for (int32 i = 0; i != EnemyInfoSlot; ++i) {
		if (EnemyDefs[i].classID != entity->classID) continue;
		if (!count_bosses && EnemyDefs[i].boss) continue;
		if (EnemyDefs[i].check_func && EnemyDefs[i].check_func((Entity*)e)) return true;
		for (int32 l = 0; l != 8; ++l) {
			if (!EnemyDefs[i].states[l].func) {
				// special weird hacky shit for Rattlekiller
				if (l == 0) return true;
				break;
			}
			if (EnemyDefs[i].states[l].func == entity->state) {
				return true;
			}
		}
	}
	return false;
}

Hitbox* GetEnemyHitbox(void* e) {
	EntityEnemy* entity = (EntityEnemy*)e;
	for (int32 i = 0; i != EnemyInfoSlot; ++i) {
		if (EnemyDefs[i].classID != entity->classID) continue;
		if (EnemyDefs[i].hitbox_func) {
			Hitbox* ret = EnemyDefs[i].hitbox_func((Entity*)e);
			if (ret) return ret;
		}
		for (int32 l = 0; l != 8; ++l) {
			if (!EnemyDefs[i].states[l].func) {
				// special weird hacky shit for Rattlekiller
				if (l == 0) return EnemyDefs[i].states[0].hitbox;
				break;
			}
			if (EnemyDefs[i].states[l].func == entity->state) {
				return EnemyDefs[i].states[l].hitbox;
			}
		}
	}

	return NULL;
}

bool32 IsEnemyOnScreen(void* e) {
	EntityEnemy* entity = (EntityEnemy*)e;
	Hitbox* hitbox = GetEnemyHitbox(entity);
	if (!hitbox) return false;
	Vector2 range = {
		MAX(abs(hitbox->left), abs(hitbox->right)),
		MAX(abs(hitbox->top), abs(hitbox->bottom))
	};
	return RSDK.CheckOnScreen(entity, &range);
}

void Generic_BadnikBreak(EntityPlayer* player, Entity* badnik, bool32 spawnAnimals) {
	if (spawnAnimals) CREATE_ENTITY(Animals, INT_TO_VOID((Animals->animalTypes[(RSDK.Rand(0, 32) >> 4)]) + 1), badnik->position.x, badnik->position.y);
	EntityExplosion *explosion = CREATE_ENTITY(Explosion, INT_TO_VOID(EXPLOSION_ENEMY), badnik->position.x, badnik->position.y);
	explosion->drawGroup       = Zone->objectDrawGroup[1];
	RSDK.PlaySfx(Explosion->sfxDestroy, false, 255);

	if (Zone_GetZoneID() > ZONE_INVALID) {
		int32 characterID = 0;
		switch (player->characterID) {
			case ID_SONIC: characterID = 1; break;
			case ID_TAILS: characterID = 2; break;
			case ID_KNUCKLES: characterID = 3; break;
#if MANIA_USE_PLUS
			case ID_MIGHTY: characterID = 4; break;
			case ID_RAY: characterID = 5; break;
#endif
			default: characterID = 0; break;
		}

#if MANIA_USE_PLUS
		//StatInfo info;
		/*TimeAttackData_TrackEnemyDefeat(&info, Zone_GetZoneID(), Zone->actID, characterID, SceneInfo->filter == (FILTER_BOTH | FILTER_ENCORE),
		                                FROM_FIXED(badnik->position.x), FROM_FIXED(badnik->position.y)); // TODO import*/
		//API.TryTrackStat(&info);
#else
		//APICallback_TrackEnemyDefeat(Zone_GetZoneID(), Zone->actID, characterID, FROM_FIXED(badnik->position.x), FROM_FIXED(badnik->position.y)); // TODO import
#endif
	}

	if (globals->gameMode != MODE_COMPETITION) player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
	EntityScoreBonus* scoreBonus = CREATE_ENTITY(ScoreBonus, NULL, badnik->position.x, badnik->position.y);
	scoreBonus->drawGroup        = Zone->objectDrawGroup[1];
	scoreBonus->animator.frameID = player->scoreBonus;

	switch (player->scoreBonus) {
		case 0: Player_GiveScore(player, 100); break;
		case 1: Player_GiveScore(player, 200); break;
		case 2: Player_GiveScore(player, 500); break;
		case 14: Player_GiveScore(player, 1000); break;
		case 15: Player_GiveScore(player, 10000); break;
		default: break;
	}
	if (player->scoreBonus < 15) player->scoreBonus++;

	destroyEntity(badnik);
	badnik->active = ACTIVE_DISABLED;
}

// hotaru lol
// and rexon!
void Generic_BadnikBreak_NoEntity(EntityPlayer* player, Vector2 position, bool32 spawnAnimals) {
	if (spawnAnimals) CREATE_ENTITY(Animals, INT_TO_VOID((Animals->animalTypes[(RSDK.Rand(0, 32) >> 4)]) + 1), position.x, position.y);
	EntityExplosion *explosion = CREATE_ENTITY(Explosion, INT_TO_VOID(EXPLOSION_ENEMY), position.x, position.y);
	explosion->drawGroup       = Zone->objectDrawGroup[1];
	RSDK.PlaySfx(Explosion->sfxDestroy, false, 255);

	if (Zone_GetZoneID() > ZONE_INVALID) {
		int32 characterID = 0;
		switch (player->characterID) {
			case ID_SONIC: characterID = 1; break;
			case ID_TAILS: characterID = 2; break;
			case ID_KNUCKLES: characterID = 3; break;
#if MANIA_USE_PLUS
			case ID_MIGHTY: characterID = 4; break;
			case ID_RAY: characterID = 5; break;
#endif
			default: characterID = 0; break;
		}

#if MANIA_USE_PLUS
		//StatInfo info;
		/*TimeAttackData_TrackEnemyDefeat(&info, Zone_GetZoneID(), Zone->actID, characterID, SceneInfo->filter == (FILTER_BOTH | FILTER_ENCORE),
		                                FROM_FIXED(position.x), FROM_FIXED(position.y)); // TODO import*/
		//API.TryTrackStat(&info);
#else
		//APICallback_TrackEnemyDefeat(Zone_GetZoneID(), Zone->actID, characterID, FROM_FIXED(position.x), FROM_FIXED(position.y)); // TODO import
#endif
	}

	if (globals->gameMode != MODE_COMPETITION) player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
	EntityScoreBonus* scoreBonus = CREATE_ENTITY(ScoreBonus, NULL, position.x, position.y);
	scoreBonus->drawGroup        = Zone->objectDrawGroup[1];
	scoreBonus->animator.frameID = player->scoreBonus;

	switch (player->scoreBonus) {
		case 0: Player_GiveScore(player, 100); break;
		case 1: Player_GiveScore(player, 200); break;
		case 2: Player_GiveScore(player, 500); break;
		case 14: Player_GiveScore(player, 1000); break;
		case 15: Player_GiveScore(player, 10000); break;
		default: break;
	}
	if (player->scoreBonus < 15) player->scoreBonus++;
}

void HitEnemy(EntityPlayer* player, void* e) {
	Entity* entity = (Entity*)e;
	for (int32 i = 0; i != EnemyInfoSlot; ++i) {
		if (EnemyDefs[i].classID == entity->classID) {
			if (EnemyDefs[i].destroy_func) {
				EnemyDefs[i].destroy_func(player, entity);
			} else if (!EnemyDefs[i].boss) {
				Generic_BadnikBreak(player, entity, EnemyDefs[i].animal);
			}
		}
	}
}