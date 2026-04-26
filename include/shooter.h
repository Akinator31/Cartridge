#pragma once
#include <gb/gb.h>

typedef enum { SHOOTER_MENU, SHOOTER_PLAY, SHOOTER_SCOREBOARD } shooter_scene;

typedef struct shooter_game_s {
        UINT8 previous_keys;
        shooter_scene current_scene;
        UINT16 score;
} shooter_game_st;

typedef struct shooter_scene_functions_s {
        void (*scene_func)(UINT8* keys, shooter_game_st* shooter_st);
} shooter_scene_functions_st;

void shooter_menu_scene(UINT8* keys, shooter_game_st* shooter_st);
void shooter_game_scene(UINT8* keys, shooter_game_st* shooter_st);
void shooter_scoreboard_scene(UINT8* keys, shooter_game_st* shooter_st);
