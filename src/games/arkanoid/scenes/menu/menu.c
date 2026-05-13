#include "arkanoid.h"
#include "cartridge.h"
#include <gbdk/console.h>
#include <stdio.h>

void arkanoid_menu_scene(UINT8* keys, arkanoid_st* state) {
    static UINT8 frame = 0;
    UINT8 pressed = *keys & (UINT8)~state->previous_keys;

    if (pressed & J_START) {
        clean_screen();
        state->current_scene = ARKANOID_PLAY;
        arkanoid_setup_game_display(state);
        return;
    }

    frame++;
    UINT8 blink_on = ((frame >> 3U) & 0x01U);

    gotoxy(2, 3);
    printf("ARKANOID");
    gotoxy(2, 6);
    printf("BREAK ALL");
    gotoxy(2, 7);
    printf("THE BRICKS");
    gotoxy(2, 9);
    printf("USE LEFT/RIGHT");
    gotoxy(2, 10);
    printf("TO MOVE PADDLE");

    gotoxy(2, 13);
    if (!blink_on)
        printf("              ");
    else
        printf("PRESS START");
}
