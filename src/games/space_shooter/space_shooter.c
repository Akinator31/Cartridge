#include "shooter.h"
#include "cartridge.h"
#include <gb/gb.h>
#include <stdlib.h>

static const shooter_scene_functions_st shooter_scene_functions[] = {
    { .scene_func = shooter_menu_scene },
    { .scene_func = shooter_game_scene },
    { .scene_func = shooter_scoreboard_scene }
};

shooter_game_st* load_shooter(void) {
    shooter_game_st* shooter_st = (shooter_game_st*)malloc(sizeof(shooter_game_st));
    shooter_st->previous_keys = 0;
    shooter_st->current_scene = SHOOTER_MENU;
    shooter_st->score = 0;
    return shooter_st;
}

void update_shooter(UINT8* keys, shooter_game_st* shooter_st) {
    shooter_scene_functions[shooter_st->current_scene].scene_func(keys, shooter_st);
}

void unload_shooter(void) {
    // Clean up Shooter game resources
}
