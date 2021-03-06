#include "fsm.h"

void input(fsm_input_t *i) {
    // Input function here
}

void fsm(fsm_output_t *o, fsm_input_t *i, fsm_state_t *s) {
    int n;
    uint8_t newlane, isPass;

    if (*s == FSM_IDLE) {
        // Check button
        if (i->button.up || i->button.down) {
            *s = FSM_GAME_MENU;
        }
    } else if (*s == FSM_GAME_MENU) {
        // Check button
        if (i->button.up || i->button.down) {
            *s = FSM_GAME_PLAY;
        }
    } else if (*s == FSM_GAME_PLAY) {
        // Reset to default when starting game
        if (o->state != FSM_GAME_PLAY) {
            o->score = 0;
            o->ncount = BLOCK_WIDTH;
            o->rndcount = BLOCK_RAND;
            o->carpos = 0;

            for (n = 0; n < BLOCK_LANE; n++) {
                o->obstaclepos[n] = 0;
            }
        }

        // Only update on block width
        if (o->ncount++ >= BLOCK_WIDTH) {
            o->ncount = 0;

            // Move obstacle position
            isPass = 0;
            for (n = 0; n < BLOCK_LANE; n++) {
                o->obstaclepos[n] = (o->obstaclepos[n] >> 1);
                if (o->obstaclepos[n] & 1) isPass = 1;
            }
            // Add score if the user pass the car
            if (isPass) o->score++;
            // Check for car collision
            if (o->obstaclepos[o->carpos] & 1) {
                // Car crashed, show game over
                o->state = FSM_GAME_OVER;
            }
            // Generate new car
            if (o->rndcount++ >= BLOCK_RAND) {
                if (rand() & 4) {
                    // Get new lane configuration
                    newlane = (newlane % BLOCK_LANE_BIT) + 1;
                    // Reset the random counter
                    o->rndcount = 0;
                    // Create new obstacle on the screen
                    for (n = 0; n < BLOCK_LANE; n++) {
                        o->obstaclepos[n] |= (newlane & 0x1) << 7;
                        newlane = newlane >> 1;
                    }
                }
            }
        }

        // Update on every fsm cycle
        if (i->button.up) {
            if (o->carpos > 0) o->carpos--;
        } else if (i->button.down) {
            if (o->carpos < BLOCK_LANE - 1)  o->carpos++;
        }
    } else if (*s == FSM_GAME_OVER) {
        // Check button
        if (i->button.up || i->button.down) {
            *s = FSM_GAME_PLAY;
        }
    } else {
        *s = FSM_IDLE;
    }
}

void output(fsm_output_t *o, fsm_input_t *i, fsm_state_t *s) {
    // Output state
    if (*s = FSM_IDLE) {
        if (o->state != FSM_IDLE) {
            // Clear screen

            o->state = FSM_IDLE;
        }
    } else if (*s = FSM_GAME_MENU) {
        if (o->state != FSM_GAME_MENU) {
            // Main screen

            o->state = FSM_GAME_MENU;
        }
    } else if (*s = FSM_GAME_PLAY) {
        if (o->state != FSM_GAME_PLAY) {
            // Game screen

            o->state = FSM_GAME_PLAY;
        }
    } else if (*s = FSM_GAME_OVER) {
        if (o->state != FSM_GAME_OVER) {
            // Over screen

            o->state = FSM_GAME_OVER;
        }
    }

    // Copy the input state to the last input
    o->lastInput = *i;
}