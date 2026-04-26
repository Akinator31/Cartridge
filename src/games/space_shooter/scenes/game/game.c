#include "shooter.h"
#include "cartridge.h"
#include <gb/gb.h>

#define PLAYER_MIN_X 8
#define PLAYER_MAX_X 160
#define PLAYER_MIN_Y 16
#define PLAYER_MAX_Y 152
#define PLAYER_SPEED 2
#define BULLET_SPEED 4
#define ENEMY_SPEED  1
#define FIRE_COOLDOWN_FRAMES 8

#define SHIP_SPRITE_INDEX  0
#define BULLET_SPRITE_BASE 1
#define ENEMY_SPRITE_INDEX 9

#define SPRITE_HIDDEN_X 0
#define SPRITE_HIDDEN_Y 0

static UINT8 spawn_jitter = 0;

static void respawn_enemy(enemy_st* e) {
    spawn_jitter += 37;
    e->active = 1;
    e->x = (UINT8)(PLAYER_MIN_X + (spawn_jitter % (PLAYER_MAX_X - PLAYER_MIN_X)));
    e->y = PLAYER_MIN_Y;
}

static UINT8 sprites_collide(UINT8 ax, UINT8 ay, UINT8 bx, UINT8 by) {
    return (ax + 8 > bx) && (bx + 8 > ax) && (ay + 8 > by) && (by + 8 > ay);
}

static void try_fire(shooter_game_st* s) {
    UINT8 i;
    if (s->fire_cooldown != 0)
        return;
    for (i = 0; i < SHOOTER_MAX_BULLETS; i++) {
        if (!s->bullets[i].active) {
            s->bullets[i].active = 1;
            s->bullets[i].x = s->player_x;
            s->bullets[i].y = s->player_y;
            s->fire_cooldown = FIRE_COOLDOWN_FRAMES;
            return;
        }
    }
}

void shooter_game_scene(UINT8* keys, shooter_game_st* shooter_st) {
    UINT8 i;
    bullet_st* b;

    // Player movement
    if (*keys & J_LEFT) {
        if (shooter_st->player_x >= PLAYER_MIN_X + PLAYER_SPEED)
            shooter_st->player_x -= PLAYER_SPEED;
        else
            shooter_st->player_x = PLAYER_MIN_X;
    }
    if (*keys & J_RIGHT) {
        if (shooter_st->player_x <= PLAYER_MAX_X - PLAYER_SPEED)
            shooter_st->player_x += PLAYER_SPEED;
        else
            shooter_st->player_x = PLAYER_MAX_X;
    }
    if (*keys & J_UP) {
        if (shooter_st->player_y >= PLAYER_MIN_Y + PLAYER_SPEED)
            shooter_st->player_y -= PLAYER_SPEED;
        else
            shooter_st->player_y = PLAYER_MIN_Y;
    }
    if (*keys & J_DOWN) {
        if (shooter_st->player_y <= PLAYER_MAX_Y - PLAYER_SPEED)
            shooter_st->player_y += PLAYER_SPEED;
        else
            shooter_st->player_y = PLAYER_MAX_Y;
    }

    // Fire (auto-fire while A held, gated by cooldown)
    if (shooter_st->fire_cooldown != 0)
        shooter_st->fire_cooldown--;
    if (*keys & J_A)
        try_fire(shooter_st);

    // Update bullets
    for (i = 0; i < SHOOTER_MAX_BULLETS; i++) {
        b = &shooter_st->bullets[i];
        if (!b->active)
            continue;
        if (b->y <= PLAYER_MIN_Y + BULLET_SPEED)
            b->active = 0;
        else
            b->y -= BULLET_SPEED;
    }

    // Update enemy
    if (shooter_st->enemy.active) {
        if (shooter_st->enemy.y >= PLAYER_MAX_Y)
            respawn_enemy(&shooter_st->enemy);
        else
            shooter_st->enemy.y += ENEMY_SPEED;
    }

    // Collisions: bullets vs enemy
    if (shooter_st->enemy.active) {
        for (i = 0; i < SHOOTER_MAX_BULLETS; i++) {
            b = &shooter_st->bullets[i];
            if (!b->active)
                continue;
            if (sprites_collide(b->x, b->y, shooter_st->enemy.x, shooter_st->enemy.y)) {
                b->active = 0;
                shooter_st->score++;
                respawn_enemy(&shooter_st->enemy);
                break;
            }
        }
    }

    // Render
    move_sprite(SHIP_SPRITE_INDEX, shooter_st->player_x, shooter_st->player_y);
    for (i = 0; i < SHOOTER_MAX_BULLETS; i++) {
        if (shooter_st->bullets[i].active)
            move_sprite(BULLET_SPRITE_BASE + i, shooter_st->bullets[i].x, shooter_st->bullets[i].y);
        else
            move_sprite(BULLET_SPRITE_BASE + i, SPRITE_HIDDEN_X, SPRITE_HIDDEN_Y);
    }
    if (shooter_st->enemy.active)
        move_sprite(ENEMY_SPRITE_INDEX, shooter_st->enemy.x, shooter_st->enemy.y);
    else
        move_sprite(ENEMY_SPRITE_INDEX, SPRITE_HIDDEN_X, SPRITE_HIDDEN_Y);

    shooter_st->previous_keys = *keys;
}
