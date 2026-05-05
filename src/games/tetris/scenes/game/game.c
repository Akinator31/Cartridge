#include "cartridge.h"
#include "tetris.h"
#include <asm/types.h>
#include <gb/gb.h>

static const tetromino_t TETROMINOS[7] = {
    { .blocs = { { -1, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 } }, .bloc_len = 4 },
    { .blocs = { { -1, -1 }, { -1, 0 }, { 0, 0 }, { 1, 0 } }, .bloc_len = 4 },
    { .blocs = { { 1, -1 }, { -1, 0 }, { 0, 0 }, { 1, 0 } }, .bloc_len = 4 },
    { .blocs = { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } }, .bloc_len = 4 },
    { .blocs = { { 0, -1 }, { 1, -1 }, { -1, 0 }, { 0, 0 } }, .bloc_len = 4 },
    { .blocs = { { 0, -1 }, { -1, 0 }, { 0, 0 }, { 1, 0 } }, .bloc_len = 4 },
    { .blocs = { { -1, -1 }, { 0, -1 }, { 0, 0 }, { 1, 0 } }, .bloc_len = 4 }
};

static int8_t tetromino_min_x(tetromino_type type) {
    int8_t min_x = TETROMINOS[type].blocs[0].x;

    for (UINT8 i = 1; i < TETROMINO_BLOCK_COUNT; ++i) {
        if (TETROMINOS[type].blocs[i].x < min_x)
            min_x = TETROMINOS[type].blocs[i].x;
    }
    return min_x;
}

static int8_t tetromino_max_x(tetromino_type type) {
    int8_t max_x = TETROMINOS[type].blocs[0].x;

    for (UINT8 i = 1; i < TETROMINO_BLOCK_COUNT; ++i) {
        if (TETROMINOS[type].blocs[i].x > max_x)
            max_x = TETROMINOS[type].blocs[i].x;
    }
    return max_x;
}

static int8_t tetromino_min_y(tetromino_type type) {
    int8_t min_y = TETROMINOS[type].blocs[0].y;

    for (UINT8 i = 1; i < TETROMINO_BLOCK_COUNT; ++i) {
        if (TETROMINOS[type].blocs[i].y < min_y)
            min_y = TETROMINOS[type].blocs[i].y;
    }
    return min_y;
}

static UINT8 tetromino_can_place(tetromino_type type, coords_t position, tetris_game_st* tetris_st) {
    for (UINT8 i = 0; i < TETROMINO_BLOCK_COUNT; ++i) {
        INT16 board_x = (INT16)position.x + TETROMINOS[type].blocs[i].x;
        INT16 board_y = (INT16)position.y + TETROMINOS[type].blocs[i].y;

        if (board_x < 0 || board_x >= (INT16)BOARD_WIDTH)
            return 0;
        if (board_y < 0)
            continue;
        if (board_y >= (INT16)BOARD_HEIGHT)
            return 0;
        if (tetris_st->board[(UINT8)board_y][(UINT8)board_x] != TILE_EMPTY)
            return 0;
    }
    return 1;
}

static void draw_locked_block(UINT8 board_x, UINT8 board_y) {
    set_bkg_tile_xy(BOARD_LEFT + board_x, BOARD_TOP + board_y, TILE_LOCKED);
}

static void lock_current_tetromino(tetris_game_st* tetris_st) {
    INT16 board_x = 0;
    INT16 board_y = 0;

    for (UINT8 i = 0; i < TETROMINO_BLOCK_COUNT; ++i) {
        board_x = (INT16)tetris_st->current_position.x + TETROMINOS[tetris_st->current_tetromino].blocs[i].x;
        board_y = (INT16)tetris_st->current_position.y + TETROMINOS[tetris_st->current_tetromino].blocs[i].y;
        if (board_x >= 0 && board_x < (INT16)BOARD_WIDTH && board_y >= 0 && board_y < (INT16)BOARD_HEIGHT) {
            tetris_st->board[(UINT8)board_y][(UINT8)board_x] = TILE_LOCKED;
            draw_locked_block((UINT8)board_x, (UINT8)board_y);
        }
    }
    hide_tetromino_sprites();
    tetris_st->can_get_next_tetromino = TRUE;
}
static void spawn_tetromino(tetris_game_st* tetris_st) {
    int8_t min_x = 0;
    int8_t max_x = 0;
    int8_t min_y = 0;

    if (!tetris_st->can_get_next_tetromino)
        return;
    tetris_st->current_tetromino = tetris_st->next_tetromino;
    tetris_st->next_tetromino = get_random_tetromino();
    tetris_st->current_tetromino = tetris_st->current_tetromino;
    tetris_st->can_get_next_tetromino = FALSE;
    min_x = tetromino_min_x(tetris_st->current_tetromino);
    max_x = tetromino_max_x(tetris_st->current_tetromino);
    min_y = tetromino_min_y(tetris_st->current_tetromino);
    tetris_st->current_position.x =
        (INT8)(((INT16)BOARD_WIDTH - ((INT16)max_x - (INT16)min_x + 1)) / 2) - min_x;
    tetris_st->current_position.y = (INT8)(-min_y);
    if (!tetromino_can_place(tetris_st->current_tetromino, tetris_st->current_position, tetris_st)) {
        clear_board(tetris_st);
        tetris_st->current_position.x =
            (INT8)(((INT16)BOARD_WIDTH - ((INT16)max_x - (INT16)min_x + 1)) / 2) - min_x;
        tetris_st->current_position.y = (INT8)(-min_y);
    }
}

void draw_tetromino(tetromino_type type, coords_t* position, tetris_game_st* tetris_st) {
    tetromino_t tetromino = TETROMINOS[type];
    INT16 x_final = 0;
    INT16 y_final = 0;

    for (UINT8 i = 0; i < tetromino.bloc_len; i++) {
        x_final = ((INT16)BOARD_LEFT + (INT16)position->x + tetromino.blocs[i].x) * 8 + SCREEN_MIN_X;
        y_final = ((INT16)BOARD_TOP + (INT16)position->y + tetromino.blocs[i].y) * 8 + SCREEN_MIN_Y;
        move_sprite(i, (UINT8)x_final, (UINT8)y_final);
    }
}

static void try_move_tetromino(int8_t dx, int8_t dy, tetris_game_st* tetris_st) {
    coords_t next_position = tetris_st->current_position;

    next_position.x += dx;
    next_position.y += dy;
    if (tetromino_can_place(tetris_st->current_tetromino, next_position, tetris_st)) {
        tetris_st->current_position = next_position;
        return;
    }
    if (dy > 0) {
        lock_current_tetromino(tetris_st);
        spawn_tetromino(tetris_st);
    }
}

void tetris_game_scene(UINT8* keys, tetris_game_st* tetris_st) {
    spawn_tetromino(tetris_st);
    if (*keys & J_DOWN)
        try_move_tetromino(0, 1, tetris_st);
    else if (*keys & J_LEFT)
        try_move_tetromino(-1, 0, tetris_st);
    else if (*keys & J_RIGHT)
        try_move_tetromino(1, 0, tetris_st);
    draw_tetromino(tetris_st->current_tetromino, &tetris_st->current_position, tetris_st);
}
