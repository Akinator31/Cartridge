#pragma once
#include <asm/sm83/types.h>
#include <gb/gb.h>

typedef enum GAME_STATE {
    GAME_STATE_MENU,
    GAME_STATE_TETRIS,
    GAME_STATE_SHOOTER,
    GAME_STATE_KEVIN
} GAME_STATE;

void switch_state(GAME_STATE* state, GAME_STATE* prev_state, GAME_STATE new_state);
void handle_game_state(GAME_STATE state, UINT8* keys);
void start_loop(GAME_STATE* state, GAME_STATE* prev_state);

// Game functions

// Tetris
void load_tetris(void);
void update_tetris(UINT8* keys);
void unload_tetris(void);

// Shooter
void load_shooter(void);
void update_shooter(UINT8* keys);
void unload_shooter(void);

// Kevin
void load_kevin(void);
void update_kevin(UINT8* keys);
void unload_kevin(void);
