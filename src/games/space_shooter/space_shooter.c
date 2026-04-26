#include "shooter/shooter.h"
#include "cartridge.h"
#include <gb/gb.h>
#include <stdlib.h>

#define SHIP_TILE_INDEX   0
#define BULLET_TILE_INDEX 1
#define ENEMY_TILE_INDEX  2

#define SHIP_SPRITE_INDEX  0
#define BULLET_SPRITE_BASE 1
#define ENEMY_SPRITE_INDEX 9

#define PLAYER_START_X 80
#define PLAYER_START_Y 120
#define ENEMY_START_X  80
#define ENEMY_START_Y  16

static const unsigned char shooter_tiles[] = {
    // Tile 0: le ship
    0x10, 0x10, 0x10, 0x10, 0x38, 0x38, 0x38, 0x38,
    0x7C, 0x7C, 0x7C, 0x7C, 0xD6, 0xD6, 0xFF, 0xFF,
    // Tile 1: les bullets
    0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
    // Tile 2: l'enemy
    0x3C, 0x3C, 0x7E, 0x7E, 0xDB, 0xDB, 0xFF, 0xFF,
    0x5A, 0x5A, 0xDB, 0xDB, 0xA5, 0xA5, 0x42, 0x42
};

static const shooter_scene_functions_st shooter_scene_functions[] = {
    { .scene_func = shooter_menu_scene },
    { .scene_func = shooter_game_scene },
    { .scene_func = shooter_scoreboard_scene }
};

shooter_game_st* load_shooter(void) {
    shooter_game_st* shooter_st = (shooter_game_st*)malloc(sizeof(shooter_game_st));
    UINT8 i;

    shooter_st->previous_keys = 0;
    shooter_st->current_scene = SHOOTER_MENU;
    shooter_st->score = 0;
    shooter_st->player_x = PLAYER_START_X;
    shooter_st->player_y = PLAYER_START_Y;
    shooter_st->fire_cooldown = 0;

    for (i = 0; i < SHOOTER_MAX_BULLETS; i++) {
        shooter_st->bullets[i].active = 0;
        shooter_st->bullets[i].x = 0;
        shooter_st->bullets[i].y = 0;
    }

    shooter_st->enemy.active = 1;
    shooter_st->enemy.x = ENEMY_START_X;
    shooter_st->enemy.y = ENEMY_START_Y;

    set_sprite_data(SHIP_TILE_INDEX, 3, shooter_tiles);
    set_sprite_tile(SHIP_SPRITE_INDEX, SHIP_TILE_INDEX);
    for (i = 0; i < SHOOTER_MAX_BULLETS; i++)
        set_sprite_tile(BULLET_SPRITE_BASE + i, BULLET_TILE_INDEX);
    set_sprite_tile(ENEMY_SPRITE_INDEX, ENEMY_TILE_INDEX);

    return shooter_st;
}

void update_shooter(UINT8* keys, shooter_game_st* shooter_st) {
    shooter_scene_functions[shooter_st->current_scene].scene_func(keys, shooter_st);
}

void unload_shooter(void) {
    // Clean up Shooter game resources
}