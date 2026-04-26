#include "shooter/bullets.h"
#include "shooter/player.h"

void update_bullets(UINT8 *i, bullet_st *b, shooter_game_st* shooter_st) {
    for (*i = 0; *i < SHOOTER_MAX_BULLETS; *i += 1) {
        b = &shooter_st->bullets[*i];
        if (!b->active)
            continue;
        if (b->y <= PLAYER_MIN_Y + BULLET_SPEED)
            b->active = 0;
        else
            b->y -= BULLET_SPEED;
    }
}

void update_bullets_positions(UINT8* i, shooter_game_st* shooter_st) {
    for (*i = 0; *i < SHOOTER_MAX_BULLETS; *i += 1) {
        if (shooter_st->bullets[*i].active)
            move_sprite(BULLET_SPRITE_BASE + *i, shooter_st->bullets[*i].x, shooter_st->bullets[*i].y);
        else
            move_sprite(BULLET_SPRITE_BASE + *i, SPRITE_HIDDEN_X, SPRITE_HIDDEN_Y);
    }
}