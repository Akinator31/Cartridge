#include "cartridge.h"
#include <gb/gb.h>

void switch_state(core_st* core, GAME_STATE new_state) {
    if (core->state != new_state) {
        clean_screen();
        switch (core->prev_state) {
        case GAME_STATE_SPLASH:
            break;
        case GAME_STATE_TITLE:
            break;
        case GAME_STATE_MENU:
            break;
        case GAME_STATE_TETRIS:
            unload_tetris(core->tetris_game);
            break;
        case GAME_STATE_SHOOTER:
            unload_shooter(core->shooter_game);
            break;
        case GAME_STATE_ARKANOID:
            unload_arkanoid(core->arkanoid);
            break;
        }
        core->prev_state = core->state;
        core->state = new_state;
        switch (core->state) {
        case GAME_STATE_SPLASH:
            break;
        case GAME_STATE_TITLE:
            break;
        case GAME_STATE_MENU:
            break;
        case GAME_STATE_TETRIS:
            core->tetris_game = load_tetris();
            break;
        case GAME_STATE_SHOOTER:
            core->shooter_game = load_shooter();
            break;
        case GAME_STATE_ARKANOID:
            core->arkanoid = load_arkanoid();
            break;
        }
    }
}

void handle_game_state(core_st* core) {
    switch (core->state) {
    case GAME_STATE_SPLASH:
        update_splash(core);
        break;
    case GAME_STATE_TITLE:
        update_title(core);
        break;
    case GAME_STATE_MENU:
        update_main_menu(core);
        break;
    case GAME_STATE_TETRIS:
        update_tetris(&core->keys, core->tetris_game);
        break;
    case GAME_STATE_SHOOTER:
        update_shooter(&core->keys, core->shooter_game);
        break;
    case GAME_STATE_ARKANOID:
        update_arkanoid(&core->keys, core->arkanoid);
        break;
    }
}
