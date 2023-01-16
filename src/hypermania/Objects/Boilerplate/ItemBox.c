#include "ItemBox.h"

ObjectItemBox *ItemBox;
void (*ItemBox_State_Broken)(void);
void (*ItemBox_Break)(EntityItemBox*, EntityPlayer*);