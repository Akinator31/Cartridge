#pragma once

#define PLAYER_MIN_X   8
#define PLAYER_MAX_X   160
#define PLAYER_MIN_Y   16
#define PLAYER_MAX_Y   152
#define PLAYER_SPEED   2
#define PLAYER_START_X 80
#define PLAYER_START_Y 120

void update_player_movement(UINT8* keys, shooter_game_st* shooter_st);
void handle_player_fire(const UINT8* keys, shooter_game_st* shooter_st);
