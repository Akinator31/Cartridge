#pragma once
#include <gb/gb.h>

#define SAVE_ENTRIES_PER_GAME 5

typedef enum {
    SAVE_GAME_TETRIS,
    SAVE_GAME_SHOOTER,
    SAVE_GAME_KEVIN
} save_game_id;

void save_init(void);
void save_load_scores(save_game_id game, UINT16* out_scores);
UINT8 save_try_insert_score(save_game_id game, UINT16 score);
