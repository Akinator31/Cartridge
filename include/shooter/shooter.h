#pragma once
#include <gb/gb.h>

#define SHOOTER_MAX_BULLETS   8
#define SHOOTER_INITIAL_LIVES 3

#define BLANK_TILE_INDEX  0
#define SHIP_TILE_INDEX   1
#define BULLET_TILE_INDEX 2
#define ENEMY_TILE_INDEX  3

#define SHIP_SPRITE_INDEX  0
#define BULLET_SPRITE_BASE 1
#define ENEMY_SPRITE_INDEX 9

#define SPRITE_HIDDEN_X 0
#define SPRITE_HIDDEN_Y 0

typedef enum { SHOOTER_MENU, SHOOTER_PLAY, SHOOTER_SCOREBOARD } shooter_scene;

typedef struct bullet_s {
        UINT8 active;
        UINT8 x;
        UINT8 y;
} bullet_st;

typedef struct enemy_s {
        UINT8 active;
        UINT8 x;
        UINT8 y;
} enemy_st;

typedef struct shooter_game_s {
        UINT8 previous_keys;
        shooter_scene current_scene;
        UINT16 score;
        UINT8 lives;
        UINT8 player_x;
        UINT8 player_y;
        UINT8 fire_cooldown;
        bullet_st bullets[SHOOTER_MAX_BULLETS];
        enemy_st enemy;
} shooter_game_st;

typedef struct shooter_scene_functions_s {
        void (*scene_func)(UINT8* keys, shooter_game_st* shooter_st);
} shooter_scene_functions_st;

void reset_shooter_play(shooter_game_st* shooter_st);

void shooter_menu_scene(UINT8* keys, shooter_game_st* shooter_st);
void shooter_game_scene(UINT8* keys, shooter_game_st* shooter_st);
void shooter_scoreboard_scene(UINT8* keys, shooter_game_st* shooter_st);