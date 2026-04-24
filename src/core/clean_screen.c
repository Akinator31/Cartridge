#include "cartridge.h"
#include <gb/gb.h>
#include <gbdk/console.h>

void clean_screen(void) {
    UINT8 i;

    move_bkg(0, 0);
    move_win(7, 144);
    HIDE_WIN;

    fill_bkg_rect(0, 0, 32, 32, 0x00);
    fill_win_rect(0, 0, 32, 32, 0x00);

    for (i = 0; i != 40; ++i)
        move_sprite(i, 0, 0);

    cls();
}
