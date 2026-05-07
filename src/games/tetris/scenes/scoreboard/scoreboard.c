#include "cartridge.h"
#include "save.h"
#include "tetris.h"
#include <asm/types.h>
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

void tetris_scoreboard_scene(UINT8* keys, tetris_game_st* tetris_st) {
    UINT16 scores[SAVE_ENTRIES_PER_GAME];
    UINT8 i;
    UINT8 pressed = *keys & (UINT8)~tetris_st->previous_keys;
    static BOOLEAN has_clear = FALSE;

    if (!has_clear) {
        clean_screen();
        has_clear = TRUE;
    }
    if (pressed & J_START) {
        clean_screen();
        tetris_st->current_scene = TETRIS_MENU;
        tetris_st->previous_keys = *keys;
        return;
    }
    save_load_scores(SAVE_GAME_TETRIS, scores);
    gotoxy(4, 2);
    printf("HIGH SCORES");
    for (i = 0; i < SAVE_ENTRIES_PER_GAME; i++) {
        gotoxy(3, 5 + i * 2);
        printf("%u. %u", i + 1, scores[i]);
    }
    gotoxy(3, 16);
    printf("START = SELECT");
    tetris_st->previous_keys = *keys;
}
