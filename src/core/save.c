#include "save.h"
#include <gb/gb.h>

#define SAVE_MAGIC   0xCAFEU
#define SAVE_VERSION 1U

typedef struct save_data_s {
    UINT16 magic;
    UINT8  version;
    UINT8  reserved;
    UINT16 tetris_scores[SAVE_ENTRIES_PER_GAME];
    UINT16 shooter_scores[SAVE_ENTRIES_PER_GAME];
    UINT16 kevin_scores[SAVE_ENTRIES_PER_GAME];
} save_data_st;

#define SAVE_PTR ((volatile save_data_st*)0xA000)

static volatile UINT16* save_scores_for_game(save_game_id game) {
    if (game == SAVE_GAME_TETRIS)
        return SAVE_PTR->tetris_scores;
    if (game == SAVE_GAME_SHOOTER)
        return SAVE_PTR->shooter_scores;
    return SAVE_PTR->kevin_scores;
}

void save_init(void) {
    UINT8 i;

    ENABLE_RAM;
    SWITCH_RAM(0);

    if (SAVE_PTR->magic != SAVE_MAGIC || SAVE_PTR->version != SAVE_VERSION) {
        SAVE_PTR->magic = SAVE_MAGIC;
        SAVE_PTR->version = SAVE_VERSION;
        SAVE_PTR->reserved = 0;
        for (i = 0; i < SAVE_ENTRIES_PER_GAME; i++) {
            SAVE_PTR->tetris_scores[i] = 0;
            SAVE_PTR->shooter_scores[i] = 0;
            SAVE_PTR->kevin_scores[i] = 0;
        }
    }

    DISABLE_RAM;
}

void save_load_scores(save_game_id game, UINT16* out_scores) {
    volatile UINT16* scores;
    UINT8 i;

    ENABLE_RAM;
    SWITCH_RAM(0);
    scores = save_scores_for_game(game);
    for (i = 0; i < SAVE_ENTRIES_PER_GAME; i++)
        out_scores[i] = scores[i];
    DISABLE_RAM;
}

UINT8 save_try_insert_score(save_game_id game, UINT16 score) {
    volatile UINT16* scores;
    UINT8 rank, i;
    UINT8 result = 0;

    ENABLE_RAM;
    SWITCH_RAM(0);
    scores = save_scores_for_game(game);

    for (rank = 0; rank < SAVE_ENTRIES_PER_GAME; rank++) {
        if (score > scores[rank]) {
            for (i = SAVE_ENTRIES_PER_GAME - 1; i > rank; i--)
                scores[i] = scores[i - 1];
            scores[rank] = score;
            result = rank + 1;

            break;
        }
    }

    DISABLE_RAM;
    return result;
}