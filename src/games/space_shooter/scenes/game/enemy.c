#include "shooter/shooter.h"
#include "shooter/player.h"
#include "shooter/enemy.h"
#include "play_sfx.h"
#include "cartridge.h"

static UINT8 spawn_jitter = 0;

void respawn_enemy(enemy_st* e) {
    spawn_jitter += 37;
    e->active = 1;
    e->x = (UINT8)(PLAYER_MIN_X + (spawn_jitter % (PLAYER_MAX_X - PLAYER_MIN_X)));
    e->y = PLAYER_MIN_Y;
}

void next_wave(shooter_game_st* shooter_st) {
    UINT8 i;
    shooter_st->wave++;
    play_wave_up_sfx(); 

    for (i = 0; i < SHOOTER_MAX_ENEMIES; i++) {
        if (i < shooter_st->wave && i < SHOOTER_MAX_ENEMIES) {
            if (!shooter_st->enemies[i].active) {
                respawn_enemy(&shooter_st->enemies[i]);
            }
        } else {
            shooter_st->enemies[i].active = 0;
        }
    }
}

void update_enemies(shooter_game_st* shooter_st) {
    UINT8 i;
    UINT8 speed = ENEMY_SPEED + (shooter_st->wave / 3);

    for (i = 0; i < SHOOTER_MAX_ENEMIES; i++) {
        if (shooter_st->enemies[i].active) {
            if (shooter_st->enemies[i].y >= PLAYER_MAX_Y) {
                respawn_enemy(&shooter_st->enemies[i]);
            } else {
                shooter_st->enemies[i].y += speed;
            }
        }
    }

    if (shooter_st->score >= (shooter_st->wave * 10)) {
        next_wave(shooter_st);
    }
}

void update_enemies_positions(shooter_game_st* shooter_st) {
    UINT8 i;
    for (i = 0; i < SHOOTER_MAX_ENEMIES; i++) {
        if (shooter_st->enemies[i].active)
            move_sprite(ENEMY_SPRITE_BASE + i, shooter_st->enemies[i].x, shooter_st->enemies[i].y);
        else
            move_sprite(ENEMY_SPRITE_BASE + i, SPRITE_HIDDEN_X, SPRITE_HIDDEN_Y);
    }
}