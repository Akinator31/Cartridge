/**
 * @file cartridge.h
 * @brief Core engine and state management definitions for the Cartridge project.
 */

#pragma once
#include "arkanoid.h"
#include <asm/sm83/types.h>
#include "shooter/shooter.h"
#include "tetris.h"
#include <gb/gb.h>

/** @brief Minimum X coordinate for the screen. */
#define SCREEN_MIN_X 8
/** @brief Minimum Y coordinate for the screen. */
#define SCREEN_MIN_Y 16

/**
 * @brief Enum representing the various states of the application.
 */
typedef enum GAME_STATE {
    GAME_STATE_SPLASH,    /**< Animated splash screen. */
    GAME_STATE_TITLE,     /**< Main title screen waiting for input. */
    GAME_STATE_MENU,      /**< Game selection menu. */
    GAME_STATE_TETRIS,    /**< Tetris game state. */
    GAME_STATE_SHOOTER,   /**< Space Shooter game state. */
    GAME_STATE_ARKANOID   /**< Arkanoid game state. */
} GAME_STATE;

/**
 * @brief Structure representing the main menu state.
 */
typedef struct main_menu_s {
        unsigned char reserved; /**< Reserved byte for future use. */
} main_menu_st;

/**
 * @brief Core engine structure containing all game-related data and current state.
 */
typedef struct core_s {
        GAME_STATE state;             /**< Current game state. */
        GAME_STATE prev_state;        /**< Previous game state, used for clean-up. */
        tetris_game_st* tetris_game;  /**< Pointer to Tetris game data. */
        shooter_game_st* shooter_game; /**< Pointer to Shooter game data. */
        arkanoid_st* arkanoid;         /**< Pointer to Arkanoid game data. */
        main_menu_st* main_menu;       /**< Pointer to Main Menu data. */
        UINT8 keys;                    /**< Current state of the joypad keys. */
} core_st;

/**
 * @brief Switches the application state and handles initialization/cleanup.
 * @param core Pointer to the core structure.
 * @param new_state The state to transition to.
 */
void switch_state(core_st* core, GAME_STATE new_state);

/**
 * @brief Handles the logic for the current game state.
 * @param core Pointer to the core structure.
 */
void handle_game_state(core_st* core);

/**
 * @brief Starts the main game loop.
 * @param core Pointer to the core structure.
 */
void start_loop(core_st* core);

/**
 * @brief Updates the splash screen animation.
 * @param core Pointer to the core structure.
 */
void update_splash(core_st* core);

/**
 * @brief Updates the title screen logic.
 * @param core Pointer to the core structure.
 */
void update_title(core_st* core);

/**
 * @brief Updates the main menu selection logic.
 * @param core Pointer to the core structure.
 */
void update_main_menu(core_st* core);

/**
 * @brief Cleans the screen by hiding sprites and resetting background tiles.
 */
void clean_screen(void);

/**
 * @brief Plays the sound effect for scoring.
 */
void play_score_sfx(void);


// Game functions

// Tetris
tetris_game_st* load_tetris(void);
void update_tetris(UINT8* keys, tetris_game_st* tetris_st);
void unload_tetris(tetris_game_st* tetris_st);

// Shooter
shooter_game_st* load_shooter(void);
void update_shooter(UINT8* keys, shooter_game_st* shooter_st);
void unload_shooter(shooter_game_st* shooter_st);

// Arkanoid
arkanoid_st* load_arkanoid(void);
void update_arkanoid(UINT8* keys, arkanoid_st* arkanoid_st);
void unload_arkanoid(arkanoid_st* arkanoid_st);
