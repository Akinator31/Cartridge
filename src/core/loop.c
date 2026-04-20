#include "cartridge.h"
#include <gb/gb.h>

void start_loop(GAME_STATE* state, GAME_STATE* prev_state) {
    UINT8 keys = 0;

    while (1) {
        wait_vbl_done();
        keys = joypad();
        if (keys & J_SELECT)
            switch_state(state, prev_state, GAME_STATE_MENU);
        handle_game_state(*state, &keys);
        vsync();
    }
}
