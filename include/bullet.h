#ifndef BULLET_H
#define BULLET_H

#include "common.h"

#define BULLET_TILE_ID 17

typedef struct Bullet {
	bool inUse;
	OBJ_ATTR* attrSlot;
	VecFx32 pos;
	VecFx32 vel;
	Fx32 damage;
} Bullet;

void bulletInit(Bullet* b, VecFx32* pos, VecFx32* vel, Fx32 damage, OBJ_ATTR* attrSlot);
void bulletUpdate(Bullet* b);

#endif	// BULLET_H