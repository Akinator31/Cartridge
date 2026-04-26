#include "shooter/shooter.h"
#include "shooter/bullets.h"
#include "shooter/player.h"
#include "cartridge.h"
#include <gb/gb.h>

void update_player_movement(const UINT8* keys, shooter_game_st* shooter_st) {
    if (*keys & J_LEFT) {
        if (shooter_st->player_x >= PLAYER_MIN_X + PLAYER_SPEED)
            shooter_st->player_x -= PLAYER_SPEED;
        else
            shooter_st->player_x = PLAYER_MIN_X;
    }
    if (*keys & J_RIGHT) {
        if (shooter_st->player_x <= PLAYER_MAX_X - PLAYER_SPEED)
            shooter_st->player_x += PLAYER_SPEED;
        else
            shooter_st->player_x = PLAYER_MAX_X;
    }
    if (*keys & J_UP) {
        if (shooter_st->player_y >= PLAYER_MIN_Y + PLAYER_SPEED)
            shooter_st->player_y -= PLAYER_SPEED;
        else
            shooter_st->player_y = PLAYER_MIN_Y;
    }
    if (*keys & J_DOWN) {
        if (shooter_st->player_y <= PLAYER_MAX_Y - PLAYER_SPEED)
            shooter_st->player_y += PLAYER_SPEED;
        else
            shooter_st->player_y = PLAYER_MAX_Y;
    }
}

static void try_fire(shooter_game_st* s) {
    UINT8 i;
    if (s->fire_cooldown != 0)
        return;
    for (i = 0; i < SHOOTER_MAX_BULLETS; i++) {
        if (!s->bullets[i].active) {
            s->bullets[i].active = 1;
            s->bullets[i].x = s->player_x;
            s->bullets[i].y = s->player_y;
            s->fire_cooldown = FIRE_COOLDOWN_FRAMES;
            return;
        }
    }
}

void handle_player_fire(const UINT8* keys, shooter_game_st* shooter_st) {
    if (shooter_st->fire_cooldown != 0)
        shooter_st->fire_cooldown--;
    if (*keys & J_A)
        try_fire(shooter_st);
}