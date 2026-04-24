#pragma once
#include "kevin.h"
#include "shooter.h"
#include "tetris.h"
#include <asm/sm83/types.h>
#include <gb/gb.h>

typedef enum GAME_STATE {
    GAME_STATE_MENU,
    GAME_STATE_TETRIS,
    GAME_STATE_SHOOTER,
    GAME_STATE_KEVIN
} GAME_STATE;

typedef struct main_menu_s {
        unsigned char reserved;
} main_menu_st;

typedef struct core_s {
        GAME_STATE state;
        GAME_STATE prev_state;
        tetris_game_st* tetris_game;
        shooter_game_st* shooter_game;
        kevin_game_st* kevin_game;
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
void unload_tetris(void);

// Shooter
shooter_game_st* load_shooter(void);
void update_shooter(UINT8* keys, shooter_game_st* shooter_st);
void unload_shooter(void);

// Kevin
kevin_game_st* load_kevin(void);
void update_kevin(UINT8* keys, kevin_game_st* kevin_st);
void unload_kevin(void);
