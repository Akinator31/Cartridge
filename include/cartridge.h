#pragma once
#include "arkanoid.h"
#include <asm/sm83/types.h>
#include "shooter/shooter.h"
#include "tetris.h"
#include <gb/gb.h>

#define SCREEN_MIN_X 8
#define SCREEN_MIN_Y 16

typedef enum GAME_STATE {
    GAME_STATE_MENU,
    GAME_STATE_TETRIS,
    GAME_STATE_SHOOTER,
    GAME_STATE_ARKANOID
} GAME_STATE;

typedef struct main_menu_s {
        unsigned char reserved;
} main_menu_st;

typedef struct core_s {
        GAME_STATE state;
        GAME_STATE prev_state;
        tetris_game_st* tetris_game;
        shooter_game_st* shooter_game;
        arkanoid_st* arkanoid;
        main_menu_st* main_menu;
        UINT8 keys;
} core_st;

void switch_state(core_st* core, GAME_STATE new_state);
void handle_game_state(core_st* core);
void start_loop(core_st* core);
void update_main_menu(core_st* core);
void clean_screen(void);

// Game functions

// Tetris
tetris_game_st* load_tetris(void);
void update_tetris(UINT8* keys, tetris_game_st* tetris_st);
void unload_tetris(tetris_game_st* tetris_st);

// Shooter
shooter_game_st* load_shooter(void);
void update_shooter(UINT8* keys, shooter_game_st* shooter_st);
void unload_shooter(shooter_game_st* shooter_st);

// Arkanoid
arkanoid_st* load_arkanoid(void);
void update_arkanoid(UINT8* keys, arkanoid_st* arkanoid_st);
void unload_arkanoid(arkanoid_st* arkanoid_st);
