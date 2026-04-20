#include "cartridge.h"
#include <gb/gb.h>

int main(void) {
    GAME_STATE state = GAME_STATE_MENU;
    GAME_STATE prev_state = state;
    DISPLAY_ON;
    SHOW_SPRITES;

    start_loop(&state, &prev_state);
    return 0;
}
