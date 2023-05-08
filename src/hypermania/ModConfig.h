#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "GameAPI/Game.h"

typedef struct {
	int32 hyperStyle; /* 0 - rainbow sonic, brighter super palettes for everyone else
	                     1 - rainbow sonic, super palettes + no hyper sparkles for everyone else
	                     2 - rainbow for all characters */
	bool32 hyperFlashDropDash; // set to true to activate drop dash instantly when using hyper flash
	bool32 hyperFlashForwarding; // set to true to treat no directional input as pressing forward when using hyper flash
	float screenFlashFactor; // set to control intensity of screen flashes, with 1.0 being full intensity and 0.0 disabling flashes
	bool32 twoHeavensMode; // set to true to enable "Two Heavens mode" letting you choose between turning super OR hyper with the latter form consuming rings at a faster rate
	bool32 enableHyperMusic; // set to true to enable hyper music (duhhh!!!!!)
} ModConfig_t;

extern ModConfig_t ModConfig;

#endif //! MOD_CONFIG_H