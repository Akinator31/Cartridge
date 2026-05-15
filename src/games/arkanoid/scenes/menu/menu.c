#include "arkanoid.h"
#include "cartridge.h"
#include <gbdk/console.h>
#include <stdio.h>

void arkanoid_menu_scene(UINT8* keys, arkanoid_st* state) {
    static UINT8 selected = 0;
    static UINT8 frame = 0;
    UINT8 pressed = *keys & (UINT8)~state->previous_keys;
    UINT8 blink_on;

    if (pressed & J_UP) {
        if (selected == 0)
            selected = 1;
        else
            --selected;
    }
    if (pressed & J_DOWN)
        selected = (selected + 1) % 2;

    if (pressed & J_START) {
        clean_screen();
        if (selected == 0) {
            reset_arkanoid_game(state);
            state->current_scene = ARKANOID_PLAY;
            arkanoid_setup_game_display(state);
        } else {
            state->current_scene = ARKANOID_SCOREBOARD;
        }
        return;
    }

    frame++;
    blink_on = ((frame >> 3U) & 0x01U);

    gotoxy(2, 3);
    printf("ARKANOID");
    gotoxy(2, 5);
    printf("USE UP/DOWN");
    gotoxy(2, 6);
    printf("TO SELECT");
    gotoxy(2, 7);
    printf("PRESS START");

    gotoxy(2, 10);
    if (selected == 0 && !blink_on)
        printf("    ");
    else
        printf("PLAY");

    gotoxy(2, 12);
    if (selected == 1 && !blink_on)
        printf("          ");
    else
        printf("SCOREBOARD");
}
