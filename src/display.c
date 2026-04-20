#include "display.h"

//! Get the screen entry index for a tile-coord pair.
/*! This is the fast (and possibly unsafe) way.
 *   \param bgcnt    Control flags for this background (to find its size)
 */

OBJ_ATTR sprites[128];
OBJ_AFFINE* objAffBuffer;
bool spriteIsUsed[128];

uint displayGetSEIndexFast(uint tx, uint ty, u16 bgcnt) {
	uint n = tx + ty * 32;
	if (tx >= 32) n += 0x03E0;
	if (ty >= 32 && (bgcnt & BG_REG_64x64) == BG_REG_64x64) n += 0x0400;
	return n;
}

u32 getAffineID(OBJ_AFFINE* affAttribute) { return (affAttribute - objAffBuffer); }

OBJ_ATTR* displayAllocObjAttr(void) {
	for (size_t i = 0; i < 128; i++) {
		if (!spriteIsUsed[i]) {
			spriteIsUsed[i] = true;
			return &(sprites[i]);
		}
	}
	return NULL;
}

void displayFreeObjAttr(OBJ_ATTR* attr) {
	obj_hide(attr);
	spriteIsUsed[(attr - sprites)] = false;
}

void displayInit(void) {
	objAffBuffer = (OBJ_AFFINE*)sprites;
	oam_init(sprites, 128);	 // initialize the oam properly to avoid weird render artifacts
	REG_DISPCNT =
		DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;	 // we don't really care about anything but sprites, and 1 background layer i guess
	u16 BG0Flags =
		BG_BUILD(DISPLAY_BG0_CBB, DISPLAY_BG0_SBB, BG_REG_32x32, BG_4BPP, BG_PRIO(0), false, false);  // background's not gonna be super fancy
	REG_BG0CNT = BG0Flags;
	se_fill(&se_mem[8][0], 0);
	memset32(spriteIsUsed, false, sizeof(spriteIsUsed) / sizeof(*spriteIsUsed));
}

void displayUpdate(void) {
	vid_vsync();
	obj_copy(obj_mem, sprites, 128);
	obj_aff_copy(obj_aff_mem, objAffBuffer, 1);
}
