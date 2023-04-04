#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "GameAPI/Game.h"

typedef struct {
	bool32 originsHyperDash; // set to true to use origins S3&K-style controls/effects for hyper dash
	int32 hyperStyle; /* 0 - rainbow sonic, brighter super palettes for everyone else
	                     1 - rainbow sonic, super palettes + no hyper sparkles for everyone else
	                     2 - rainbow for all characters */
} ModConfig_t;

extern ModConfig_t ModConfig;

#endif //! MOD_CONFIG_H