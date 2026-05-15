#pragma once
#include "shooter.h"

#define ENEMY_SPEED 1

void respawn_enemy(enemy_st* e);
void update_enemies(shooter_game_st* shooter_st);
void update_enemies_positions(shooter_game_st* shooter_st);
void next_wave(shooter_game_st* shooter_st);