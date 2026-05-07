#include "tetris.h"
#include <rand.h>

static const UINT8 TETROMINO_SPRITES[7][TETROMINO_ROTATION_COUNT][TETROMINO_BLOCK_COUNT] = {
    { { 0U, 1U, 2U, 3U }, { 3U, 2U, 1U, 0U }, { 3U, 2U, 1U, 0U }, { 0U, 1U, 2U, 3U } },
    { { 0U, 1U, 2U, 3U }, { 3U, 2U, 0U, 1U }, { 3U, 2U, 1U, 0U }, { 1U, 0U, 2U, 3U } },
    { { 0U, 1U, 2U, 3U }, { 0U, 3U, 2U, 1U }, { 3U, 2U, 1U, 0U }, { 1U, 2U, 3U, 0U } },
    { { 0U, 1U, 2U, 3U }, { 1U, 3U, 0U, 2U }, { 3U, 2U, 1U, 0U }, { 2U, 0U, 3U, 1U } },
    { { 0U, 1U, 2U, 3U }, { 1U, 0U, 3U, 2U }, { 3U, 2U, 1U, 0U }, { 2U, 3U, 0U, 1U } },
    { { 0U, 1U, 2U, 3U }, { 3U, 0U, 2U, 1U }, { 3U, 2U, 1U, 0U }, { 1U, 2U, 0U, 3U } },
    { { 0U, 1U, 2U, 3U }, { 3U, 1U, 2U, 0U }, { 3U, 2U, 1U, 0U }, { 0U, 2U, 1U, 3U } }
};

tetromino_type get_random_tetromino(void) {
    return (tetromino_type)(rand() % 7);
}

void clear_board(tetris_game_st* tetris_st) {
    UINT8 y = 0;
    UINT8 x = 0;

    for (y = 0; y < BOARD_HEIGHT; ++y) {
        for (x = 0; x < BOARD_WIDTH; ++x)
            tetris_st->board[y][x] = TILE_EMPTY;
    }
}

void hide_tetromino_sprites(void) {
    for (UINT8 i = 0; i < TETROMINO_BLOCK_COUNT * 2U; ++i)
        move_sprite(i, 0U, 0U);
}

const UINT8* get_tetromino_rotation_sprites(tetromino_type type, UINT8 rotation) {
    return TETROMINO_SPRITES[type][rotation & (TETROMINO_ROTATION_COUNT - 1)];
}
