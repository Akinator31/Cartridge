#include "arkanoid.h"
#include "cartridge.h"
#include <gbdk/console.h>
#include <stdio.h>

static arkanoid_st game_state;

const unsigned char arkanoid_tiles[] = {
    0x3C,0x3C,0x7E,0x42,0xFF,0x81,0xE7,0x99,0xE7,0x99,0xFF,0x81,0x7E,0x42,0x3C,0x3C, // ball
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // brick
    0x66,0x66,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7E,0x7E,0x3C,0x3C,0x18,0x18, // heart
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // empty
};

void init_bricks(arkanoid_st* state) {
    uint8_t x, y;
    state->bricks_left = 0;
    for (y = 2; y < 5; y++) {
        for (x = 2; x < 18; x++) {
            set_bkg_tile_xy(x, y, 129);
            state->bricks_left++;
        }
    }
}

static void setup_game_display(arkanoid_st* state) {
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
    printf("%04d", state->score); // j'arrive pas a afficher 0000 comment dans le space shooter
    for (uint8_t i = 0; i < 3; i++) {
        set_bkg_tile_xy(ARKANOID_PADDING + i, 0, (i < state->lives) ? 130 : 131);
    }
}

static void arkanoid_menu_scene(UINT8* keys, arkanoid_st* state) {
    static UINT8 frame = 0;
    UINT8 blink_on;

    if (*keys & J_START) {
        clean_screen();
        state->current_scene = ARKANOID_PLAY;
        setup_game_display(state);
        return;
    }

    frame++;
    blink_on = ((frame >> 3U) & 0x01U);

    gotoxy(2, 3);
    printf("ARKANOID");
    gotoxy(2, 6);
    printf("BREAK ALL");
    gotoxy(2, 7);
    printf("THE BRICKS");
    gotoxy(2, 9);
    printf("USE LEFT/RIGHT");
    gotoxy(2, 10);
    printf("TO MOVE PADDLE");

    gotoxy(2, 13);
    if (!blink_on)
        printf("              ");
    else
        printf("PRESS START");
}

static void arkanoid_play_scene(UINT8* keys, arkanoid_st* state) {
    if (state->game_over) {
        if (*keys & J_START) {
            state->current_scene = ARKANOID_MENU;
            clean_screen();
            game_state.paddle_x = 72;
            game_state.ball_x = 80;
            game_state.ball_y = 100;
            game_state.ball_dx = 1;
            game_state.ball_dy = -1;
            game_state.game_over = 0;
            game_state.score = 0;
            game_state.lives = 3;
        }
        return;
    }

    if (*keys & J_LEFT && state->paddle_x > 8) {
        state->paddle_x -= 2;
    }
    if (*keys & J_RIGHT && state->paddle_x < 144) {
        state->paddle_x += 2;
    }

    state->ball_x += state->ball_dx;
    state->ball_y += state->ball_dy;

    if (state->ball_x <= 8 || state->ball_x >= 160) state->ball_dx = -state->ball_dx;
    if (state->ball_y <= 16) state->ball_dy = -state->ball_dy;

    uint8_t tile_x = (state->ball_x - 8) / 8;
    uint8_t tile_y = (state->ball_y - 16) / 8;
    
    if (get_bkg_tile_xy(tile_x, tile_y) == 129) {
        set_bkg_tile_xy(tile_x, tile_y, 131);
        state->ball_dy = -state->ball_dy;
        state->score += 10;
        state->bricks_left--;
        
        gotoxy(7, 0);
        printf("%u", state->score);

        if (state->bricks_left == 0) {
            state->game_over = 1;
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
        for (uint8_t i = 0; i < 3; i++) {
            set_bkg_tile_xy(ARKANOID_PADDING + i, 0,
                (i >= 3 - state->lives) ? 130 : 131);
        }
        
        if (state->lives > 0) {
            state->ball_x = state->paddle_x + 4;
            state->ball_y = 130;
            state->ball_dx = 1;
            state->ball_dy = -1;
        } else {
            state->game_over = 1;
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

arkanoid_st* load_arkanoid(void) {
    game_state.paddle_x = 72;
    game_state.ball_x = 80;
    game_state.ball_y = 100;
    game_state.ball_dx = 1;
    game_state.ball_dy = -1;
    game_state.game_over = 0;
    game_state.score = 0;
    game_state.lives = 3;
    game_state.current_scene = ARKANOID_MENU;
    game_state.previous_keys = 0;

    return &game_state;
}

void update_arkanoid(UINT8* keys, arkanoid_st* state) {
    if (state->current_scene == ARKANOID_MENU) {
        arkanoid_menu_scene(keys, state);
    } else if (state->current_scene == ARKANOID_PLAY) {
        arkanoid_play_scene(keys, state);
    }
    state->previous_keys = *keys;
}

void unload_arkanoid(void) {
    HIDE_SPRITES;
}
