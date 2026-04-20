#include "enemy.h"

#include "display.h"
#include "player.h"

void EnemyInit(Enemy* e, OBJ_ATTR* attrSlot, EnemyType type, u16 angle, Fx32 hp, Fx32 dmg) {
	e->enemyAttributes = attrSlot;
	e->enemyAffine = (OBJ_AFFINE*)attrSlot;
	e->type = type;
	e->cooldownTimer = 0;

	VecFx32 centerPos = (VecFx32){float2fx(PLAYER_POS_X), fx2int(float2fx(PLAYER_POS_Y)), 0};
	e->pos = centerPos;
	VecFx32 rotationOffset = (VecFx32){lu_cos(angle), lu_sin(angle), 0};
	vec_scale(&(rotationOffset), &(rotationOffset), float2fx(100.0));
	vec_add(&(e->pos), &(e->pos), &rotationOffset);

	vec_sub(&(e->vel), &centerPos, &(e->pos));
	vec_scale(&(e->vel), &(e->vel), float2fx(1.0 / 100.0));
	vec_scale(&(e->vel), &(e->vel), float2fx(1.0 / 60.0));

	e->hp = hp;
	e->dmg = dmg;

	obj_set_attr(e->enemyAttributes, ATTR0_4BPP | ATTR0_REG | ATTR0_SQUARE, ATTR1_SIZE_16x16, ATTR2_ID(18));
	obj_hide(e->enemyAttributes);
}

void EnemyUpdate(Enemy* e) {
	// vec_add(&(e->pos), &(e->pos), &(e->vel));

	if (e->pos.x > 0 && fx2int(e->pos.x) < SCREEN_WIDTH && e->pos.y > 0 && fx2int(e->pos.y) < SCREEN_HEIGHT) {
		obj_set_pos(e->enemyAttributes, fx2int(e->pos.x), fx2int(e->pos.y));
		obj_unhide(e->enemyAttributes, ATTR0_REG);
	} else {
		obj_hide(e->enemyAttributes);
	}

	// obj_aff_identity(e->enemyAffine);
	// obj_aff_rotscale(e->enemyAffine, float2fx(0.5f), float2fx(0.5f), ArcTan2(fx2int(e->vel.x), fx2int(e->vel.y)));
}