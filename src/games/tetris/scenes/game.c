#include "cartridge.h"
#include "tetris.h"
#include <gb/gb.h>

static const tetromino_t TETROMINOS[7] = { { .blocs = { { -1, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 } } },
                                           { .blocs = { { -1, -1 }, { -1, 0 }, { 0, 0 }, { 1, 0 } } },
                                           { .blocs = { { 1, -1 }, { -1, 0 }, { 0, 0 }, { 1, 0 } } },
                                           { .blocs = { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } } },
                                           { .blocs = { { 0, -1 }, { 1, -1 }, { -1, 0 }, { 0, 0 } } },
                                           { .blocs = { { 0, -1 }, { -1, 0 }, { 0, 0 }, { 1, 0 } } },
                                           { .blocs = { { -1, -1 }, { 0, -1 }, { 0, 0 }, { 1, 0 } } } };

void draw_tetromino(tetromino_type type, coords_t* position) {
    tetromino_t tetromino = TETROMINOS[type];
    INT16 x_final = 0;
    INT16 y_final = 0;

    for (UINT8 i = 0; i < 4; i++) {
        x_final = ((INT16)position->x + tetromino.blocs[i].x) * 8 + SCREEN_MIN_X;
        y_final = ((INT16)position->y + tetromino.blocs[i].y) * 8 + SCREEN_MIN_Y;
        move_sprite(i, (UINT8)x_final, (UINT8)y_final);
    }
}

void tetris_game_scene(UINT8* keys, tetris_game_st* tetris_st) {
    coords_t position = { .x = 5, .y = 10 };
    draw_tetromino(TETROMINO_I, &position);
}
