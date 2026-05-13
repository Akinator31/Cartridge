#include "arkanoid/arkanoid.h"
#include <stdlib.h>

static const arkanoid_scene_functions_st arkanoid_scene_functions[] = {
    { .scene_func = arkanoid_menu_scene },
    { .scene_func = arkanoid_game_scene }
};

void reset_arkanoid_game(arkanoid_st* state) {
    state->paddle_x = 72;
    state->ball_x = 80;
    state->ball_y = 100;
    state->ball_dx = 1;
    state->ball_dy = -1;
    state->game_over = 0;
    state->score = 0;
    state->bricks_left = 0;
    state->lives = 3;
}

arkanoid_st* load_arkanoid(void) {
    arkanoid_st* state = (arkanoid_st*)malloc(sizeof(arkanoid_st));

    if (!state)
        return NULL;
    reset_arkanoid_game(state);
    state->current_scene = ARKANOID_MENU;
    state->previous_keys = 0;
    return state;
}

void update_arkanoid(UINT8* keys, arkanoid_st* state) {
    arkanoid_scene_functions[state->current_scene].scene_func(keys, state);
    state->previous_keys = *keys;
}

void unload_arkanoid(arkanoid_st* state) {
    HIDE_SPRITES;
    free(state);
}
