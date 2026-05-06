#include "tetris.h"
#include "cartridge.h"
#include <asm/types.h>
#include <gb/gb.h>
#include <stdlib.h>

static const tetris_scene_functions_st tetris_scene_functions[] = { { .scene_func = tetris_menu_scene },
                                                                    { .scene_func = NULL },
                                                                    { .scene_func = tetris_game_scene } };

static const unsigned char tetris_tile[] = { 0xFF, 0xFF, 0xFF, 0x81, 0xFF, 0x81, 0xFF, 0x81,
                                             0xFF, 0x81, 0xFF, 0x81, 0xFF, 0x81, 0xFF, 0xFF };

static const unsigned char tetris_bg_tiles[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF, 0xFF,
    0x11, 0x11, 0x22, 0x22, 0x44, 0x44, 0x88, 0x88, 0x11, 0x11, 0x22, 0x22, 0x44, 0x44, 0x88, 0x88,
    0xFF, 0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF, 0xFF
};

static void draw_box(UINT8 left, UINT8 top, UINT8 width, UINT8 height) {
    fill_bkg_rect(left, top, width, height, TILE_WALL);
    fill_bkg_rect(left + 1U, top + 1U, width - 2U, height - 2U, TILE_EMPTY);
}

void draw_tetris_background(void) {
    set_bkg_data(0, 4, tetris_bg_tiles);
    fill_bkg_rect(0, 0, 20, 18, TILE_EMPTY);

    draw_box(BOARD_LEFT - 1U, BOARD_TOP - 1U, BOARD_WIDTH + 2U, BOARD_HEIGHT + 2U);
    draw_box(NEXT_LEFT - 1U, NEXT_TOP - 1U, NEXT_WIDTH + 2U, NEXT_HEIGHT + 2U);

    for (UINT8 y = 0; y < BOARD_HEIGHT; ++y) {
        for (UINT8 x = 0; x < BOARD_WIDTH; ++x) {
            if (((x + y) & 0x01U) == 0U)
                set_bkg_tile_xy(BOARD_LEFT + x, BOARD_TOP + y, TILE_PATTERN);
        }
    }

    SHOW_BKG;
}

tetris_game_st* load_tetris(void) {
    tetris_game_st* tetris_st = (tetris_game_st*)malloc(sizeof(tetris_game_st));

    tetris_st->previous_keys = 0;
    tetris_st->current_player = TETRIS_PLAYER_1;
    tetris_st->current_scene = TETRIS_MENU;
    tetris_st->next_tetromino = get_random_tetromino();
    tetris_st->can_get_next_tetromino = TRUE;
    tetris_st->can_move = TRUE;
    set_sprite_data(0, 1, tetris_tile);
    for (uint8_t i = 0; i < 8; i++)
        set_sprite_tile(i, 0);
    return tetris_st;
}

void update_tetris(UINT8* keys, tetris_game_st* tetris_st) {
    tetris_scene_functions[tetris_st->current_scene].scene_func(keys, tetris_st);
}

void unload_tetris(void) {
    // Clean up Tetris game resources
}
