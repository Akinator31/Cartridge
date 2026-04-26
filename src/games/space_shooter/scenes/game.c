#include "shooter.h"
#include "cartridge.h"
#include <gb/gb.h>

#define PLAYER_MIN_X 8
#define PLAYER_MAX_X 160
#define PLAYER_MIN_Y 16
#define PLAYER_MAX_Y 152
#define PLAYER_SPEED 2

#define SHIP_SPRITE_INDEX 0

void shooter_game_scene(UINT8* keys, shooter_game_st* shooter_st) {
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

    move_sprite(SHIP_SPRITE_INDEX, shooter_st->player_x, shooter_st->player_y);
}
