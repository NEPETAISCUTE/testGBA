#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"

typedef enum EnemyType {
	ENEMY_TYPE_NORMAL = 0,
} EnemyType;

typedef struct Enemy {
	EnemyType type;	 // might not be used in the end

	OBJ_ATTR* enemyAttributes;
	OBJ_AFFINE* enemyAffine;

	VecFx32 pos;
	VecFx32 vel;

	Fx32 hp;
	Fx32 dmg;

	u32 cooldownTimer;
} Enemy;

void EnemyInit(Enemy* e, OBJ_ATTR* attrSlot, EnemyType type, u16 angle, Fx32 hp, Fx32 dmg);
void EnemyUpdate(Enemy* e);

#endif	// ENEMY_H