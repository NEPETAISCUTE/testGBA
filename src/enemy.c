#include "enemy.h"

#include "display.h"
#include "enemy.h"
#include "player.h"

void EnemyInit(Enemy* e, OBJ_ATTR* attrSlot, EnemyType type, u16 angle, Fx32 hp, Fx32 dmg) {
	e->enemyAttributes = attrSlot;
	e->enemyAffine = (OBJ_AFFINE*)attrSlot;
	e->type = type;
	e->cooldownTimer = 0;

	const VecFx32 centerPos = (VecFx32){
		.x = float2fx(PLAYER_POS_X + PLAYER_WIDTH / 2.0f - ENEMY_WIDTH / 2.0f),
		.y = float2fx(PLAYER_POS_Y + PLAYER_HEIGHT / 2.0f - ENEMY_HEIGHT / 2.0f),
		.z = (Fx32)0,
	};

	const VecFx32 directionFromCenter = (VecFx32){
		.x = lu_cos(angle),
		.y = lu_sin(angle),
		.z = (Fx32)0,
	};

	VecFx32 directionToCenter = (VecFx32){
		.x = -lu_cos(angle),
		.y = -lu_sin(angle),
		.z = (Fx32)0,
	};

	VecFx32 posOffset;
	vec_scale(&posOffset, &directionFromCenter, float2fx(ENEMY_SPAWN_RADIUS));
	vec_add(&(e->pos), &centerPos, &posOffset);

	e->vel = directionToCenter;
	vec_scale(&(e->vel), &(e->vel), float2fx(ENEMY_SPEED));

	e->hp = hp;
	e->dmg = dmg;

	obj_set_attr(e->enemyAttributes, ATTR0_4BPP | ATTR0_REG | ATTR0_SQUARE, ATTR1_SIZE_16x16, ATTR2_ID(18));
	obj_hide(e->enemyAttributes);
}

void EnemyUpdate(Enemy* e) {
	vec_add(&(e->pos), &(e->pos), &(e->vel));

	if (e->pos.x + float2fx(ENEMY_WIDTH / 2.0f) > (Fx32)0 && e->pos.x < int2fx(SCREEN_WIDTH) && e->pos.y + float2fx(ENEMY_HEIGHT / 2.0f) > 0 &&
		fx2int(e->pos.y) < SCREEN_HEIGHT) {
		obj_set_pos(e->enemyAttributes, fx2int(e->pos.x), fx2int(e->pos.y));
		obj_unhide(e->enemyAttributes, ATTR0_REG);
	} else {
		obj_hide(e->enemyAttributes);
	}

	// obj_aff_identity(e->enemyAffine);
	// obj_aff_rotscale(e->enemyAffine, float2fx(0.5f), float2fx(0.5f), ArcTan2(fx2int(e->vel.x), fx2int(e->vel.y)));
}
