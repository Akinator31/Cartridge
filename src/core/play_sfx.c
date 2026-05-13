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
