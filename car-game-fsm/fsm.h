#pragma once

#include <stdint.h>
#define BLOCK_WIDTH 16
#define BLOCK_HEIGHT 18

typedef enum {
    FSM_IDLE,
    FSM_GAME_MENU,
    FSM_GAME_PLAY,
    FSM_GAME_OVER
} fsm_state_t;

typedef struct {
    fsm_state_t state;
    uint16_t score;
    uint8_t ncount;
    uint8_t rndcount;
    struct {
        uint8_t top : 1;
        uint8_t mid : 1;
        uint8_t bot : 1;
    } carpos;
    uint8_t obstaclepos[3];
} fsm_output_t;

typedef struct {
    struct {
        uint8_t top : 1;
        uint8_t bot : 1;
    } button;
} fsm_input_t;

void fsm(fsm_output_t *o, fsm_input_t *i);