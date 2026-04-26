#pragma once
#include "shooter.h"

#define BULLET_SPEED 4
#define FIRE_COOLDOWN_FRAMES 8

void update_bullets(UINT8 *i, bullet_st *b, shooter_game_st* shooter_st);
void update_bullets_positions(UINT8* i, shooter_game_st* shooter_st);