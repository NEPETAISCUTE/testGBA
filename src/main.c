#include <stdio.h>
#include <stdlib.h>
#include <tonc.h>

#include "common.h"
#include "display.h"
#include "enemy.h"
#include "player.h"
#include "test.h"

/*
void vblUpdate() {
	oam_copy(oam_mem, sprites, 128);
	REG_IF = IRQ_VBLANK;
}
*/

u32 frameCounter = 0;
Enemy enemies[64];
bool enemyIsUsed[64];

void assetInit(void) {
	memcpy32(pal_bg_mem, testPal, testPalLen / 4);
	memcpy32(pal_obj_mem, testPal, testPalLen / 4);
	memcpy32(&(tile_mem[0][0]), testTiles, testTilesLen / 4);
	memcpy32(tile_mem_obj, testTiles, testTilesLen / 4);
}

int main(void) {
	Player p;

	memset32(enemyIsUsed, 0, 64 / (4 / sizeof(*enemyIsUsed)));

	assetInit();
	displayInit();
	spriteIsUsed[0] = true;
	playerInit(&p, &(sprites[0]));

	while (true) {
		key_poll();
		playerUpdate(&p, key_tri_shoulder() * -128);
		if (key_hit(KEY_B)) {
			playerShootBullet(&p);
		}

		if (frameCounter < 16) {  //(frameCounter % 600 == 0) {
			for (size_t i = 0; i < 64; i++) {
				if (!enemyIsUsed[i]) {
					enemyIsUsed[i] = true;
					OBJ_ATTR* attr = displayAllocObjAttr();
					if (attr == NULL) break;

					EnemyInit(&(enemies[i]), attr, ENEMY_TYPE_NORMAL, frameCounter * 4096, float2fx(10.0), float2fx(1.0));
					break;
				}
			}
		}

		for (size_t i = 0; i < 64; i++) {
			if (enemyIsUsed[i]) EnemyUpdate(&(enemies[i]));
		}

		displayUpdate();
		frameCounter++;
	}

	return 0;
}