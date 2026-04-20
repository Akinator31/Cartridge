#include "cartridge.h"
#include <gb/gb.h>

void start_loop(core_st* core) {
    while (1) {
        wait_vbl_done();
        core->keys = joypad();
        if (core->keys & J_SELECT)
            switch_state(core, GAME_STATE_MENU);
        handle_game_state(core);
        vsync();
    }
}
