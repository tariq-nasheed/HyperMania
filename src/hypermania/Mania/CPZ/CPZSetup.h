#ifndef OBJ_CPZSETUP_H
#define OBJ_CPZSETUP_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    uint16 aniTiles;
    TileLayer *background;
    TABLE(int32 deformation[64], { 1, 2, 1, 3, 1, 2, 2, 1, 2, 3, 1, 2, 1, 2, 0, 0, 2, 0, 3, 2, 2, 3, 2, 2, 1, 3, 0, 0, 1, 0, 1, 3,
                                   1, 2, 1, 3, 1, 2, 2, 1, 2, 3, 1, 2, 1, 2, 0, 0, 2, 0, 3, 2, 2, 3, 2, 2, 1, 3, 0, 0, 1, 0, 1, 3 });
    int32 bgTowerLightPalIndex;
    int32 rainbowLightPalIndex;
    int32 chemLiquidPalIndex1;
    int32 chemLiquidPalIndex2;
    int32 chemLiquidPalIndex3;
    uint16 aniTileFrame;
    Entity *outro;
} ObjectCPZSetup;

typedef struct {
    RSDK_ENTITY
} EntityCPZSetup;

extern ObjectCPZSetup *CPZSetup;

#endif //! OBJ_CPZSETUP_H
