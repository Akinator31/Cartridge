#include "tetris.h"
#include <rand.h>

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
    for (UINT8 i = 0; i < TETROMINO_BLOCK_COUNT; ++i)
        move_sprite(i, 0U, 0U);
}
