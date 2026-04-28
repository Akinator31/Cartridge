#include "arkanoid.h"
#include "cartridge.h"
#include <gbdk/console.h>
#include <stdio.h>

static arkanoid_st game_state;

const unsigned char arkanoid_tiles[] = {
    0x3C,0x3C,0x42,0x42,0x81,0x81,0xA5,0xA5,0x81,0x81,0xA5,0xA5,0x42,0x42,0x3C,0x3C, // paddle
    0x3C,0x3C,0x7E,0x42,0xFF,0x81,0xE7,0x99,0xE7,0x99,0xFF,0x81,0x7E,0x42,0x3C,0x3C, // ball
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 // brick
};

static void arkanoid_menu_scene(UINT8* keys, arkanoid_st* state) {
    static UINT8 frame = 0;
    UINT8 blink_on;

    if (*keys & J_START) {
        clean_screen();
        state->current_scene = ARKANOID_PLAY;
        // todo add setup game display when start button is pressed :p
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
        // todo implement scene "game"
    }
    state->previous_keys = *keys;
}

void unload_arkanoid(void) {
    HIDE_SPRITES;
}
