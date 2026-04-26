#pragma once
#include "shooter.h"

#define ENEMY_SPEED 1

void respawn_enemy(enemy_st* e);
void update_enemy(shooter_game_st* shooter_st);
void update_enemy_position(shooter_game_st* shooter_st);