#pragma once
#include "shooter.h"

#define HUD_TILE_BASE  200
#define HUD_DIGIT_BASE HUD_TILE_BASE
#define HUD_HEART_TILE (HUD_TILE_BASE + 10)

void hud_init(void);
void hud_render(const shooter_game_st* shooter_st);
