#include "cartridge.h"
#include <gb/gb.h>

void switch_state(GAME_STATE* state, GAME_STATE* prev_state, GAME_STATE new_state) {
    if (*state != new_state) {
        switch (*prev_state) {
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
        *prev_state = *state;
        *state = new_state;
        switch (*state) {
        case GAME_STATE_MENU:
            break;
        case GAME_STATE_TETRIS:
            load_tetris();
            break;
        case GAME_STATE_SHOOTER:
            load_shooter();
            break;
        case GAME_STATE_KEVIN:
            load_kevin();
            break;
        }
    }
}

void handle_game_state(GAME_STATE state, UINT8* keys) {
    switch (state) {
    case GAME_STATE_MENU:
        // handle menu input and rendering
        break;
    case GAME_STATE_TETRIS:
        update_tetris(keys);
        break;
    case GAME_STATE_SHOOTER:
        update_shooter(keys);
        break;
    case GAME_STATE_KEVIN:
        update_kevin(keys);
        break;
    }
}
