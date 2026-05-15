#pragma once

#include <asm/sm83/types.h>

#define ARKANOID_PADDING 17

typedef enum { ARKANOID_MENU, ARKANOID_PLAY, ARKANOID_SCOREBOARD } arkanoid_scene;

typedef struct arkanoid_s {
        UINT8 previous_keys;
        arkanoid_scene current_scene;
        UINT8 paddle_x;
        UINT8 ball_x;
        UINT8 ball_y;
        INT8 ball_dx;
        INT8 ball_dy;
        UINT8 game_over;
        UINT16 score;
        UINT8 bricks_left;
        UINT8 lives;
} arkanoid_st;

typedef struct arkanoid_scene_functions_s {
        void (*scene_func)(UINT8* keys, arkanoid_st* state);
} arkanoid_scene_functions_st;

void reset_arkanoid_game(arkanoid_st* state);
arkanoid_st* load_arkanoid(void);
void update_arkanoid(UINT8* keys, arkanoid_st* state);
void unload_arkanoid(arkanoid_st* state);

void arkanoid_menu_scene(UINT8* keys, arkanoid_st* state);
void arkanoid_game_scene(UINT8* keys, arkanoid_st* state);
void arkanoid_scoreboard_scene(UINT8* keys, arkanoid_st* state);
void arkanoid_setup_game_display(arkanoid_st* state);
