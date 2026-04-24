#include "cartridge.h"
#include "tetris.h"
#include <asm/sm83/types.h>
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

void tetris_menu_scene(UINT8* keys, tetris_game_st* tetris_st) {
    static UINT8 selected = 0;
    static UINT8 frame = 0;
    UINT8 pressed = *keys & (UINT8)~tetris_st->previous_keys;
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
        if (selected == 0)
            tetris_st->current_scene = TETRIS_PLAY;
        else if (selected == 1)
            tetris_st->current_scene = TETRIS_SCOREBOARD;
        clean_screen();
        draw_tetris_background();
        return;
    }
    frame++;
    blink_on = ((frame >> 3U) & 0x01U);

    gotoxy(3, 3);
    printf("TETRIS");
    gotoxy(2, 5);
    printf("USE UP/DOWN");
    gotoxy(2, 6);
    printf("TO SELECT");
    gotoxy(2, 7);
    printf("PRESS START");
    gotoxy(2, 10);
    if (selected == 0 && !blink_on)
        printf("      ");
    else
        printf("PLAY");

    gotoxy(2, 12);
    if (selected == 1 && !blink_on)
        printf("          ");
    else
        printf("SCOREBOARD");

    tetris_st->previous_keys = *keys;
}
