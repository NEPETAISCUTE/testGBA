#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.h"
#include "common.h"

#define PLAYER_TILE_ID 1

#define PLAYER_POS_X (SCREEN_WIDTH / 2) - (64 / 2)
#define PLAYER_POS_Y (SCREEN_HEIGHT / 2) - (64 / 2)
#define PLAYER_WIDTH 0.5
#define PLAYER_HEIGHT 0.5

#define PLAYER_BASE_HP 10.0
#define PLAYER_BASE_MP 0.0

#define PLAYER_BASE_DAMAGE 1.0

typedef struct Player {
	OBJ_ATTR* playerAttributes;
	OBJ_AFFINE* playerAffine;

	Bullet bulletArray[64];
	u32 bulletCount;

	Fx32 hp;
	Fx32 mp;
	u16 rotation;
} Player;

void playerInit(Player* p, OBJ_ATTR* attrSlot);

// returns the amount of bullets that dispawned this frame
void playerUpdate(Player* p, s16 rotChange);

bool playerShootBullet(Player* p);

#endif	// PLAYER_H