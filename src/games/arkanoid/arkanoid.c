#include "arkanoid.h"
#include "cartridge.h"

static arkanoid_st game_state;

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
        // todo implement scene menu
    } else if (state->current_scene == ARKANOID_PLAY) {
        // todo implement scene "game"
    }
    state->previous_keys = *keys;
}

void unload_arkanoid(void) {
    HIDE_SPRITES;
}
