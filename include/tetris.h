#pragma once
#include <gb/gb.h>

typedef enum { TETRIS_PLAYER_1, TETRIS_PLAYER_2, TETRIS_PLAYER_3 } tetris_player;

typedef enum { TETRIS_MENU, TETRIS_SCOREBOARD, TETRIS_PLAY } tetris_scene;

typedef struct tetris_game_s {
        UINT8 previous_keys;
        tetris_player current_player;
        tetris_scene current_scene;
} tetris_game_st;

typedef struct tetris_scene_functions_s {
        void (*scene_func)(UINT8* keys, tetris_game_st* tetris_st);
} tetris_scene_functions_st;

void tetris_menu_scene(UINT8* keys, tetris_game_st* tetris_st);
