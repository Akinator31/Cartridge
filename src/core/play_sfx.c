#include "play_sfx.h"
#include <gb/hardware.h>

void play_score_sfx(void) {
    NR52_REG = 0x80U;
    NR50_REG = 0x77U;
    NR51_REG = 0x11U;

    NR10_REG = 0x00U;
    NR11_REG = 0x80U;
    NR12_REG = 0xF3U;
    NR13_REG = 0x70U;
    NR14_REG = 0x86U;
}

void play_game_over_sfx(void) {
    NR52_REG = 0x80U;
    NR50_REG = 0x77U;
    NR51_REG = 0x22U;

    NR21_REG = 0x40U;
    NR22_REG = 0xF2U;
    NR23_REG = 0x20U;
    NR24_REG = 0xC7U;
}

void play_wave_up_sfx(void) {
    NR52_REG = 0x80U;
    NR50_REG = 0x77U;
    NR51_REG = 0x11U;

    NR10_REG = 0x15U;
    NR11_REG = 0x80U;
    NR12_REG = 0x73U;
    NR13_REG = 0x00U;
    NR14_REG = 0x83U;
}