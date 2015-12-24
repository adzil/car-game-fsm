#pragma once

#include <stdint.h>
#include <stdlib.h>
#define BLOCK_WIDTH 16
#define BLOCK_HEIGHT 18
#define BLOCK_OFFSET_TOP 10
#define BLOCK_OFFSET_LEFT 0
#define BLOCK_LANE 3
#define BLOCK_RAND 3

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
    uint8_t carpos;
    uint8_t obstaclepos[BLOCK_LANE];
} fsm_output_t;

typedef struct {
    struct {
        uint8_t up : 1;
        uint8_t down : 1;
    } button;
} fsm_input_t;

void fsm(fsm_output_t *o, fsm_input_t *i, fsm_state_t *s);
