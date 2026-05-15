#include "cartridge.h"
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

void draw_border(void);

void update_title(core_st* core) {
    static UINT8 frame = 0;
    static UINT8 initialized = 0;
    static UINT8 previous_keys = 0;

    if (!initialized) {
        clean_screen();
        draw_border();
        gotoxy(2, 6);
        printf("C A R T R I D G E");
        gotoxy(3, 7);
        printf("C A R T R I D G E");
        initialized = 1;
    }

    if ((frame & 0x10U) == 0) {
        gotoxy(4, 12);
        printf("PRESS SELECT");
    } else {
        gotoxy(4, 12);
        printf("            ");
    }

    if ((core->keys & J_SELECT) && !(previous_keys & J_SELECT)) {
        initialized = 0;
        switch_state(core, GAME_STATE_MENU);
        return;
    }

    previous_keys = core->keys;
    frame++;
}
