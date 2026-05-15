#include "arkanoid.h"
#include "cartridge.h"
#include "save.h"
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

void arkanoid_scoreboard_scene(UINT8* keys, arkanoid_st* state) {
    UINT16 scores[SAVE_ENTRIES_PER_GAME];
    UINT8 i;
    UINT8 pressed = *keys & (UINT8)~state->previous_keys;

    if (pressed & J_START) {
        clean_screen();
        state->current_scene = ARKANOID_MENU;
        return;
    }

    save_load_scores(SAVE_GAME_ARKANOID, scores);

    gotoxy(4, 2);
    printf("HIGH SCORES");

    for (i = 0; i < SAVE_ENTRIES_PER_GAME; i++) {
        gotoxy(3, 5 + i * 2);
        printf("%u. %u", i + 1, scores[i]);
    }

    gotoxy(3, 16);
    printf("START = SELECT");
}
