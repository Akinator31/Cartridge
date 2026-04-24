#include "tetris.h"
#include "cartridge.h"
#include <gb/gb.h>
#include <stdlib.h>

static const tetris_scene_functions_st tetris_scene_functions[] = { { .scene_func = tetris_menu_scene },
                                                                    { .scene_func = NULL },
                                                                    { .scene_func = tetris_game_scene } };

static const unsigned char tetris_tile[] = { 0xFF, 0x00, 0x81, 0x01, 0x81, 0x01, 0x81, 0x01,
                                             0x81, 0x01, 0x81, 0x01, 0x81, 0x1F, 0xFF, 0xFF };

tetris_game_st* load_tetris(void) {
    tetris_game_st* tetris_st = (tetris_game_st*)malloc(sizeof(tetris_game_st));
    tetris_st->previous_keys = 0;
    tetris_st->current_player = TETRIS_PLAYER_1;
    tetris_st->current_scene = TETRIS_MENU;

    set_sprite_data(0, 1, tetris_tile);
    for (uint8_t i = 0; i < 4; i++)
        set_sprite_tile(i, 0);
    return tetris_st;
}

void update_tetris(UINT8* keys, tetris_game_st* tetris_st) {
    tetris_scene_functions[tetris_st->current_scene].scene_func(keys, tetris_st);
}

void unload_tetris(void) {
    // Clean up Tetris game resources
}
