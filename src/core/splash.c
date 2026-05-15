#include "cartridge.h"
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

void draw_border(void) {
    UINT8 i;
    gotoxy(0, 0);
    printf("********************");
    for (i = 1; i < 17; i++) {
        gotoxy(0, i);
        printf("*");
        gotoxy(19, i);
        printf("*");
    }
    gotoxy(0, 17);
    printf("********************");
}

void update_splash(core_st* core) {
    static UINT16 frame = 0;

    if (core->keys & J_START) {
        frame = 0;
        BGP_REG = 0xE4;
        switch_state(core, GAME_STATE_TITLE);
        return;
    }

    if (frame == 0) {
        clean_screen();
        BGP_REG = 0x00;
        draw_border();
        gotoxy(4, 9);
        printf("E P I T E C H");
        gotoxy(3, 8);
        printf("E P I T E C H");
    } else if (frame == 120) {
        clean_screen();
        BGP_REG = 0x00;
        draw_border();
        gotoxy(2, 9);
        printf("C A R T R I D G E");
        gotoxy(1, 8);
        printf("C A R T R I D G E");
    }

    if ((frame % 4) == 0) {
        UINT8 local_f = (frame < 120) ? frame : (frame - 120);
        if (local_f < 32) {
            if (local_f == 0) BGP_REG = 0x00;
            else if (local_f == 8) BGP_REG = 0x40;
            else if (local_f == 16) BGP_REG = 0x90;
            else if (local_f == 24) BGP_REG = 0xE4;
        } else if (local_f > 88) {
            if (local_f == 88) BGP_REG = 0xE4;
            else if (local_f == 96) BGP_REG = 0x90;
            else if (local_f == 104) BGP_REG = 0x40;
            else if (local_f == 112) BGP_REG = 0x00;
        }
    }

    if (frame >= 240) {
        frame = 0;
        BGP_REG = 0xE4;
        switch_state(core, GAME_STATE_TITLE);
        return;
    }
    frame++;
}