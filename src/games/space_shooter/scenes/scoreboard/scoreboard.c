#include "shooter/shooter.h"
#include "cartridge.h"
#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>

void shooter_scoreboard_scene(UINT8* keys, shooter_game_st* shooter_st) {
    (void)keys;
    (void)shooter_st;
    gotoxy(3, 4);
    printf("SCOREBOARD");
    gotoxy(2, 8);
    printf("NO SCORES YET");
    gotoxy(2, 14);
    printf("SELECT = MENU");
}