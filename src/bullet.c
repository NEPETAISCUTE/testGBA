#include "bullet.h"

void bulletInit(Bullet* b, VecFx32* pos, VecFx32* vel, Fx32 damage, OBJ_ATTR* attrSlot) {
	b->inUse = true;
	b->pos = *pos;
	b->vel = *vel;
	b->damage = damage;
	b->attrSlot = attrSlot;
	obj_set_attr(b->attrSlot, ATTR0_REG | ATTR0_SQUARE | ATTR0_4BPP, ATTR1_SIZE_8x8, ATTR2_ID(BULLET_TILE_ID));
	obj_hide(b->attrSlot);
}

void bulletUpdate(Bullet* b) {
	obj_unhide(b->attrSlot, ATTR0_REG);
	vec_add(&b->pos, &b->pos, &b->vel);
	obj_set_pos(b->attrSlot, fx2int(b->pos.x), fx2int(b->pos.y));
}