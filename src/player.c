#include "player.h"

#include "display.h"

void playerInit(Player* p, OBJ_ATTR* attrSlot) {
	p->hp = PLAYER_BASE_HP;
	p->mp = PLAYER_BASE_MP;
	p->rotation = 0;
	p->bulletCount = 0;

	p->playerAttributes = attrSlot;
	p->playerAffine = (OBJ_AFFINE*)attrSlot;
	obj_set_attr(p->playerAttributes, ATTR0_4BPP | ATTR0_AFF_DBL | ATTR0_SQUARE, ATTR1_AFF_ID(0) | ATTR1_SIZE_32x32, ATTR2_ID(PLAYER_TILE_ID));
	obj_unhide(p->playerAttributes, ATTR0_AFF_DBL);
	obj_set_pos(p->playerAttributes, fx2int(float2fx(PLAYER_POS_X)), fx2int(float2fx(PLAYER_POS_Y)));
}

void playerUpdate(Player* p, s16 rotChange) {
	p->rotation += rotChange;
	obj_aff_identity(p->playerAffine);
	obj_aff_rotscale(p->playerAffine, float2fx(2.0f), float2fx(2.0f), p->rotation);

	for (u32 i = 0; i < 64; i++) {
		Bullet* b = &(p->bulletArray[i]);

		if (b->inUse) {
			bulletUpdate(b);

			if (b->pos.x > int2fx(SCREEN_WIDTH) || b->pos.y > int2fx(SCREEN_HEIGHT) || b->pos.x < 0 || b->pos.y < 0) {	// if bullet offscreen
				b->inUse = false;
				displayFreeObjAttr(b->attrSlot);
				p->bulletCount--;
			}
		}
	}
}

bool playerShootBullet(Player* p) {
	if (p->bulletCount >= 64) return false;

	int i;
	for (i = 0; i < 64; i++) {
		if (!p->bulletArray[i].inUse) break;
	}

	OBJ_ATTR* bulletAttrSlot = displayAllocObjAttr();
	if (bulletAttrSlot == NULL) return false;  // no attr slot free, so let's just give up on shooting that bullet

	Bullet* newBullet = &(p->bulletArray[i]);
	p->bulletCount++;

	VecFx32 shootDir = (VecFx32){-lu_sin(p->rotation), -lu_cos(p->rotation), 0};
	VecFx32 bulletOffset;
	vec_scale(&bulletOffset, &shootDir, float2fx(0.75));  // scaling by size of player divided by 2

	// 32.0 is the size of the player divided by 2
	// 4.0 is the size of the bullet divided by 2
	// this is just to center the bullet on the player as initial position, we'll then offset it to make it shoot out of the cannon instead
	VecFx32 pos = (VecFx32){float2fx(PLAYER_POS_X + 32.0 - 4), float2fx(PLAYER_POS_Y + 32.0 - 4), 0};
	vec_add(&pos, &pos, &bulletOffset);
	VecFx32 vel = (VecFx32){-lu_sin(p->rotation), -lu_cos(p->rotation), 0};
	vec_scale(&vel, &vel, float2fx(0.25));
	bulletInit(newBullet, &pos, &vel, PLAYER_BASE_DAMAGE, bulletAttrSlot);

	return true;
}

Bullet* playerGetBullets(Player* p) { return p->bulletArray; }