#include "cartridge.h"
#include "save.h"
#include "shooter/shooter.h"
#include "shooter/bullets.h"
#include "shooter/player.h"
#include "shooter/enemy.h"
#include "shooter/hud.h"
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

    if (shooter_st->enemy.active &&
        sprites_collide(shooter_st->player_x, shooter_st->player_y,
                        shooter_st->enemy.x, shooter_st->enemy.y)) {
        if (shooter_st->lives > 0)
            shooter_st->lives--;
        if (shooter_st->lives == 0) {
            save_try_insert_score(SAVE_GAME_SHOOTER, shooter_st->score);
            clean_screen();
            shooter_st->current_scene = SHOOTER_MENU;
            return;
        }
        shooter_st->player_x = PLAYER_START_X;
        shooter_st->player_y = PLAYER_START_Y;
        respawn_enemy(&shooter_st->enemy);
    }

    move_sprite(SHIP_SPRITE_INDEX, shooter_st->player_x, shooter_st->player_y);
    update_bullets_positions(&i, shooter_st);
    update_enemy_position(shooter_st);

    hud_render(shooter_st);

    shooter_st->previous_keys = *keys;
}
