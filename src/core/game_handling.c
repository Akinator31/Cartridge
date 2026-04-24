#include "cartridge.h"
#include <gb/gb.h>

void switch_state(core_st* core, GAME_STATE new_state) {
    if (core->state != new_state) {
        clean_screen();
        switch (core->prev_state) {
        case GAME_STATE_MENU:
            break;
        case GAME_STATE_TETRIS:
            unload_tetris();
            break;
        case GAME_STATE_SHOOTER:
            unload_shooter();
            break;
        case GAME_STATE_KEVIN:
            unload_kevin();
            break;
        }
        core->prev_state = core->state;
        core->state = new_state;
        switch (core->state) {
        case GAME_STATE_MENU:
            break;
        case GAME_STATE_TETRIS:
            core->tetris_game = load_tetris();
            break;
        case GAME_STATE_SHOOTER:
            core->shooter_game = load_shooter();
            break;
        case GAME_STATE_KEVIN:
            core->kevin_game = load_kevin();
            break;
        }
    }
}

void handle_game_state(core_st* core) {
    switch (core->state) {
    case GAME_STATE_MENU:
        update_main_menu(core);
        break;
    case GAME_STATE_TETRIS:
        update_tetris(&core->keys, core->tetris_game);
        break;
    case GAME_STATE_SHOOTER:
        update_shooter(&core->keys, core->shooter_game);
        break;
    case GAME_STATE_KEVIN:
        update_kevin(&core->keys, core->kevin_game);
        break;
    }
}
