#include "shooter.h"
#include "cartridge.h"
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

void shooter_game_scene(UINT8* keys, shooter_game_st* shooter_st) {
    (void)keys;
    (void)shooter_st;
    gotoxy(4, 8);
    printf("PLAY SCENE");
    gotoxy(2, 11);
    printf("SELECT = MENU");
}
