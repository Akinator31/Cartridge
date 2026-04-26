#include "shooter/shooter.h"
#include "cartridge.h"
#include "save.h"
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

void shooter_scoreboard_scene(UINT8* keys, shooter_game_st* shooter_st) {
    UINT16 scores[SAVE_ENTRIES_PER_GAME];
    UINT8 i;
    UINT8 pressed = *keys & (UINT8)~shooter_st->previous_keys;

    if (pressed & J_START) {
        clean_screen();
        shooter_st->current_scene = SHOOTER_MENU;
        shooter_st->previous_keys = *keys;
        return;
    }

    save_load_scores(SAVE_GAME_SHOOTER, scores);

    gotoxy(4, 2);
    printf("HIGH SCORES");

    for (i = 0; i < SAVE_ENTRIES_PER_GAME; i++) {
        gotoxy(3, 5 + i * 2);
        printf("%u. %u", i + 1, scores[i]);
    }

    gotoxy(3, 16);
    printf("START = SELECT");

    shooter_st->previous_keys = *keys;
}