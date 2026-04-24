#include "tetris.h"
#include "cartridge.h"
#include <gb/gb.h>
#include <stdlib.h>

static const tetris_scene_functions_st tetris_scene_functions[] = {
    { .scene_func = tetris_menu_scene },
};

tetris_game_st* load_tetris(void) {
    tetris_game_st* tetris_st = (tetris_game_st*)malloc(sizeof(tetris_game_st));
    tetris_st->previous_keys = 0;
    tetris_st->current_player = TETRIS_PLAYER_1;
    tetris_st->current_scene = TETRIS_MENU;
    return tetris_st;
}

void update_tetris(UINT8* keys, tetris_game_st* tetris_st) {
    tetris_scene_functions[tetris_st->current_scene].scene_func(keys, tetris_st);
}

void unload_tetris(void) {
    // Clean up Tetris game resources
}
