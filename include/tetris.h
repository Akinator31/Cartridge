#pragma once
#include <asm/types.h>
#include <gb/gb.h>
#include <stdint.h>

#define TILE_EMPTY 0U
#define TILE_WALL 1U
#define TILE_PATTERN 2U

#define BOARD_LEFT 3U
#define BOARD_TOP 1U
#define BOARD_WIDTH 10U
#define BOARD_HEIGHT 16U

#define NEXT_LEFT 16U
#define NEXT_TOP 5U
#define NEXT_WIDTH 6U
#define NEXT_HEIGHT 5U

#define TILE_LOCKED 3U

#define TETROMINO_BLOCK_COUNT 4U
#define TETROMINO_ROTATION_COUNT 4U

typedef enum { TETRIS_PLAYER_1, TETRIS_PLAYER_2, TETRIS_PLAYER_3 } tetris_player;

typedef enum { TETRIS_MENU, TETRIS_SCOREBOARD, TETRIS_PLAY } tetris_scene;

typedef enum { TETRIS_LEFT, TETRIS_RIGHT, TETRIS_DOWN, TETRIS_UP } tetris_direction;

typedef enum {
    TETROMINO_I,
    TETROMINO_J,
    TETROMINO_L,
    TETROMINO_O,
    TETROMINO_S,
    TETROMINO_T,
    TETROMINO_Z
} tetromino_type;

typedef struct {
        int8_t x;
        int8_t y;
} coords_t;

typedef struct tetris_game_s {
        UINT8 board[BOARD_HEIGHT][BOARD_WIDTH];
        UINT8 previous_keys;
        UINT8 frame;
        tetris_player current_player;
        tetris_scene current_scene;
        tetromino_type current_tetromino;
        tetromino_type next_tetromino;
        UINT8 current_rotation;
        coords_t current_position;
        BOOLEAN can_get_next_tetromino;
        BOOLEAN can_move;
} tetris_game_st;

typedef struct tetris_scene_functions_s {
        void (*scene_func)(UINT8* keys, tetris_game_st* tetris_st);
} tetris_scene_functions_st;

typedef struct {
        coords_t blocs[4];
        uint8_t bloc_len;
} tetromino_t;

void tetris_menu_scene(UINT8* keys, tetris_game_st* tetris_st);
void tetris_game_scene(UINT8* keys, tetris_game_st* tetris_st);
void draw_tetromino(
    tetromino_type type, UINT8 rotation, coords_t* position, UINT8 sprite_index, tetris_game_st* tetris_st);
void draw_tetris_background(void);
tetromino_type get_random_tetromino(void);
void clear_board(tetris_game_st* tetris_st);
void hide_tetromino_sprites(void);
const UINT8* get_tetromino_rotation_sprites(tetromino_type type, UINT8 rotation);
