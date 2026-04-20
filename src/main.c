#include "cartridge.h"
#include <gb/gb.h>

int main(void) {
    core_st core = { .state = GAME_STATE_MENU,
                     .prev_state = GAME_STATE_MENU,
                     .tetris_game = NULL,
                     .shooter_game = NULL,
                     .kevin_game = NULL,
                     .main_menu = NULL,
                     .keys = 0 };
    DISPLAY_ON;
    SHOW_SPRITES;

    start_loop(&core);
    return 0;
}
