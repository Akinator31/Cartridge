#include "cartridge.h"
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

void update_main_menu(core_st* core) {
    static UINT8 selected = 0;
    static UINT8 previous_keys = 0;
    static UINT8 frame = 0;
    UINT8 pressed;
    UINT8 blink_on;

    pressed = core->keys & (UINT8)~previous_keys;

    if (pressed & J_UP) {
        if (selected == 0)
            selected = 2;
        else
            --selected;
    }
    if (pressed & J_DOWN)
        selected = (selected + 1) % 3;

    if (pressed & J_START) {
        if (selected == 0)
            switch_state(core, GAME_STATE_TETRIS);
        else if (selected == 1)
            switch_state(core, GAME_STATE_SHOOTER);
        else
            switch_state(core, GAME_STATE_ARKANOID);
        return;
    }

    frame++;
    blink_on = ((frame >> 3U) & 0x01U);

    gotoxy(3, 3);
    printf("SELECT A GAME");
    gotoxy(2, 5);
    printf("USE UP/DOWN");

    gotoxy(5, 8);
    if (selected == 0 && !blink_on)
        printf("      ");
    else
        printf("TETRIS");

    gotoxy(5, 10);
    if (selected == 1 && !blink_on)
        printf("       ");
    else
        printf("SHOOTER");

    gotoxy(5, 12);
    if (selected == 2 && !blink_on)
        printf("        ");
    else
        printf("ARKANOID");

    gotoxy(3, 15);
    printf("PRESS START");

    previous_keys = core->keys;
}
