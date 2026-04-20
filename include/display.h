#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.h"

#define DISPLAY_BG0_CBB 0
#define DISPLAY_BG0_SBB 8

extern OBJ_ATTR sprites[128];
extern OBJ_AFFINE* objAffBuffer;
extern bool spriteIsUsed[128];

uint displayGetSEIndexFast(uint tx, uint ty, u16 bgcnt);

void displayInit();
void displayUpdate();

u32 getAffineID(OBJ_AFFINE* affAttribute);
OBJ_ATTR* displayAllocObjAttr(void);
void displayFreeObjAttr(OBJ_ATTR* attr);

#endif	// DISPLAY_H