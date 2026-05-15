#include "arkanoid.h"
#include "cartridge.h"
#include "save.h"
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

static const unsigned char arkanoid_tiles[] = {
    0x3C, 0x3C, 0x7E, 0x42, 0xFF, 0x81, 0xE7, 0x99, 0xE7, 0x99, 0xFF, 0x81, 0x7E, 0x42, 0x3C, 0x3C, /* ball */
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, /* brick */
    0x66, 0x66, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0x3C, 0x3C, 0x18, 0x18, /* heart */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  /* empty */
};

static void init_bricks(arkanoid_st* state) {
    state->bricks_left = 0;
    for (UINT8 y = 2; y < 5; y++) {
        for (UINT8 x = 2; x < 18; x++) {
            set_bkg_tile_xy(x, y, 129);
            state->bricks_left++;
        }
    }
}

void arkanoid_setup_game_display(arkanoid_st* state) {
    UINT8 i;

    set_sprite_data(0, 2, arkanoid_tiles);
    set_bkg_data(128, 4, arkanoid_tiles);

    init_bricks(state);

    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 1);

    move_sprite(0, state->ball_x, state->ball_y);
    move_sprite(1, state->paddle_x, 140);
    move_sprite(2, state->paddle_x + 8, 140);

    SHOW_SPRITES;
    SHOW_BKG;

    gotoxy(0, 0);
    printf("%u", state->score);
    for (i = 0; i < 3; i++)
        set_bkg_tile_xy(ARKANOID_PADDING + i, 0, (i < state->lives) ? 130 : 131);
}

void arkanoid_game_scene(UINT8* keys, arkanoid_st* state) {
    UINT8 i;
    UINT8 pressed = *keys & (UINT8)~state->previous_keys;

    if (state->game_over) {
        if (pressed & J_START) {
            clean_screen();
            state->current_scene = ARKANOID_MENU;
            reset_arkanoid_game(state);
        }
        return;
    }

    if ((*keys & J_LEFT) && state->paddle_x > 8)
        state->paddle_x -= 2;
    if ((*keys & J_RIGHT) && state->paddle_x < 144)
        state->paddle_x += 2;

    state->ball_x += state->ball_dx;
    state->ball_y += state->ball_dy;

    if (state->ball_x <= 8 || state->ball_x >= 160)
        state->ball_dx = -state->ball_dx;
    if (state->ball_y <= 16)
        state->ball_dy = -state->ball_dy;

    UINT8 tile_x = (state->ball_x - 8) / 8;
    UINT8 tile_y = (state->ball_y - 16) / 8;

    if (get_bkg_tile_xy(tile_x, tile_y) == 129) {
        set_bkg_tile_xy(tile_x, tile_y, 131);
        state->ball_dy = -state->ball_dy;
        state->score += 10;
        state->bricks_left--;

        gotoxy(0, 0);
        printf("%u", state->score);

        if (state->bricks_left == 0) {
            state->game_over = 1;
            save_try_insert_score(SAVE_GAME_ARKANOID, state->score);
            gotoxy(5, 10);
            printf("YOU WIN!");
            gotoxy(2, 12);
            printf("PRESS START");
        }
    }

    if (state->ball_y >= 132 && state->ball_y <= 140) {
        if (state->ball_x >= state->paddle_x && state->ball_x <= state->paddle_x + 16) {
            state->ball_dy = -state->ball_dy;
            state->ball_y = 131;
        }
    }

    if (state->ball_y > 150) {
        state->lives--;
        for (i = 0; i < 3; i++)
            set_bkg_tile_xy(ARKANOID_PADDING + i, 0, (i >= 3 - state->lives) ? 130 : 131);

        if (state->lives > 0) {
            state->ball_x = state->paddle_x + 4;
            state->ball_y = 130;
            state->ball_dx = 1;
            state->ball_dy = -1;
        } else {
            state->game_over = 1;
            save_try_insert_score(SAVE_GAME_ARKANOID, state->score);
            gotoxy(5, 10);
            printf("GAME OVER");
            gotoxy(5, 12);
            printf("PRESS START");
        }
    }

    move_sprite(0, state->ball_x, state->ball_y);
    move_sprite(1, state->paddle_x, 140);
    move_sprite(2, state->paddle_x + 8, 140);
}
