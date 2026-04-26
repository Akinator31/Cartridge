#include "cartridge.h"
#include "shooter/shooter.h"
#include "shooter/bullets.h"
#include "shooter/player.h"
#include "shooter/enemy.h"
#include <gb/gb.h>

static UINT8 sprites_collide(UINT8 ax, UINT8 ay, UINT8 bx, UINT8 by) {
    return (ax + 8 > bx) && (bx + 8 > ax) && (ay + 8 > by) && (by + 8 > ay);
}

void shooter_game_scene(UINT8* keys, shooter_game_st* shooter_st) {
    UINT8 i;
    bullet_st* b = NULL;

    update_player_movement(keys, shooter_st);
    handle_player_fire(keys, shooter_st);
    update_bullets(&i, b, shooter_st);
    update_enemy(shooter_st);

    if (shooter_st->enemy.active) {
        for (i = 0; i < SHOOTER_MAX_BULLETS; i++) {
            b = &shooter_st->bullets[i];
            if (!b->active)
                continue;
            if (sprites_collide(b->x, b->y, shooter_st->enemy.x, shooter_st->enemy.y)) {
                b->active = 0;
                shooter_st->score++;
                respawn_enemy(&shooter_st->enemy);
                break;
            }
        }
    }

    move_sprite(SHIP_SPRITE_INDEX, shooter_st->player_x, shooter_st->player_y);
    update_bullets_positions(&i, shooter_st);
    update_enemy_position(shooter_st);

    shooter_st->previous_keys = *keys;
}