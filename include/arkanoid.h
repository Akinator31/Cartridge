#pragma once
#include <gb/gb.h>

#define ARKANOID_PADDING 17

typedef enum {
    ARKANOID_MENU,
    ARKANOID_PLAY
} arkanoid_scene_e;

typedef struct arkanoid_s {
    uint8_t paddle_x;
    uint8_t ball_x;
    uint8_t ball_y;
    int8_t ball_dx;
    int8_t ball_dy;
    uint8_t game_over;
    uint16_t score;
    uint8_t bricks_left;
    uint8_t lives;
    arkanoid_scene_e current_scene;
    UINT8 previous_keys;
} arkanoid_st;
