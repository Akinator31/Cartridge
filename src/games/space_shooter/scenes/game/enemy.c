#include "shooter/shooter.h"
#include "shooter/player.h"
#include "shooter/enemy.h"
#include "cartridge.h"

static UINT8 spawn_jitter = 0;

void respawn_enemy(enemy_st* e) {
    spawn_jitter += 37;
    e->active = 1;
    e->x = (UINT8)(PLAYER_MIN_X + (spawn_jitter % (PLAYER_MAX_X - PLAYER_MIN_X)));
    e->y = PLAYER_MIN_Y;
}

void update_enemy(shooter_game_st* shooter_st) {
    if (shooter_st->enemy.active) {
        if (shooter_st->enemy.y >= PLAYER_MAX_Y)
            respawn_enemy(&shooter_st->enemy);
        else
            shooter_st->enemy.y += ENEMY_SPEED;
    }
}

void update_enemy_position(shooter_game_st* shooter_st) {
    if (shooter_st->enemy.active)
        move_sprite(ENEMY_SPRITE_INDEX, shooter_st->enemy.x, shooter_st->enemy.y);
    else
        move_sprite(ENEMY_SPRITE_INDEX, SPRITE_HIDDEN_X, SPRITE_HIDDEN_Y);
}