#include "cartridge.h"
#include "play_sfx.h"
#include "save.h"
#include "tetris.h"
#include <asm/sm83/types.h>
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

void tetris_game_over_scene(UINT8* keys, tetris_game_st* tetris_st) {
    UINT8 pressed = *keys & (UINT8)~tetris_st->previous_keys;

    if (!tetris_st->game_over_initialized) {
        clean_screen();
        draw_tetris_background();
        tetris_st->game_over_anim_row = 0;
        tetris_st->game_over_anim_done = FALSE;
        tetris_st->game_over_initialized = TRUE;
        play_game_over_sfx();
        save_try_insert_score(SAVE_GAME_TETRIS, tetris_st->final_score);
    }
    if (!tetris_st->game_over_anim_done) {
        fill_bkg_rect(0, tetris_st->game_over_anim_row, 20, 1, TILE_EMPTY);
        tetris_st->game_over_anim_row++;
        if (tetris_st->game_over_anim_row >= 18)
            tetris_st->game_over_anim_done = TRUE;
    } else {
        gotoxy(5, 7);
        printf("GAME OVER");
        gotoxy(3, 9);
        printf("PRESS START");
    }
    if (tetris_st->game_over_anim_done && (pressed & J_START)) {
        tetris_st->current_scene = TETRIS_MENU;
        tetris_st->game_over_initialized = FALSE;
        tetris_st->game_over_anim_row = 0;
        tetris_st->game_over_anim_done = FALSE;
        clean_screen();
        return;
    }
    tetris_st->previous_keys = *keys;
}
