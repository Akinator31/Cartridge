#include "shooter.h"
#include "cartridge.h"
#include <gb/gb.h>
#include <stdlib.h>

#define SHIP_TILE_INDEX   0
#define SHIP_SPRITE_INDEX 0

#define PLAYER_START_X 80
#define PLAYER_START_Y 120

static const unsigned char ship_tile[] = {
    0x10, 0x10, 0x10, 0x10, 0x38, 0x38, 0x38, 0x38,
    0x7C, 0x7C, 0x7C, 0x7C, 0xD6, 0xD6, 0xFF, 0xFF
};

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
    shooter_st->player_x = PLAYER_START_X;
    shooter_st->player_y = PLAYER_START_Y;

    set_sprite_data(SHIP_TILE_INDEX, 1, ship_tile);
    set_sprite_tile(SHIP_SPRITE_INDEX, SHIP_TILE_INDEX);
    return shooter_st;
}

void update_shooter(UINT8* keys, shooter_game_st* shooter_st) {
    shooter_scene_functions[shooter_st->current_scene].scene_func(keys, shooter_st);
}

void unload_shooter(void) {
    // Clean up Shooter game resources
}
