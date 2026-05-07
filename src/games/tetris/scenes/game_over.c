#include "cartridge.h"
#include "save.h"
#include "tetris.h"
#include <asm/sm83/types.h>
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

void tetris_game_over_scene(UINT8* keys, tetris_game_st* tetris_st) {
    static UINT8 initialized = 0;
    static UINT8 anim_row = 0;
    static UINT8 anim_done = 0;
    UINT8 pressed = *keys & (UINT8)~tetris_st->previous_keys;

    save_try_insert_score(SAVE_GAME_TETRIS, tetris_st->score);
    if (!initialized) {
        clean_screen();
        draw_tetris_background();
        anim_row = 0;
        anim_done = 0;
        initialized = 1;
    }
    if (!anim_done) {
        fill_bkg_rect(0, anim_row, 20, 1, TILE_EMPTY);
        anim_row++;
        if (anim_row >= 18)
            anim_done = 1;
    } else {
        gotoxy(5, 7);
        printf("GAME OVER");
        gotoxy(3, 9);
        printf("PRESS START");
    }
    if (anim_done && (pressed & J_START)) {
        tetris_st->current_scene = TETRIS_MENU;
        initialized = 0;
        clean_screen();
        return;
    }
    tetris_st->previous_keys = *keys;
}
