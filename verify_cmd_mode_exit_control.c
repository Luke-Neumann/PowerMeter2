//
//  verify_cmd_mode_exit_control.c
//  BLE_Power_Monitor
//
//  Created by Luke Neumann on 1/27/20.
//  Copyright © 2020 Luke Neumann. All rights reserved.
//

#include "verify_cmd_mode_exit_control.h"
#include "rn4870.h"
#include "global_variables.h"
#include <stdint.h>
#include <stdio.h>

// this initializes values to 0
#define INITIALIZE_TO_ZERO 0



// This enumerator will set up all the different states with different integer values automatically upon compilation.
enum verifyCmdModeExitStates {exit_init_st, // This is the initial state of the state Machine.
    verify_cmd_exit_start_st,
    call_verify_cmd_mode_exit_st,
    check_verify_cmd_exit_count_st,
    verify_cmd_exit_time_delay,
    verify_cmd_exit_finished
} verifyCmdModeExitState;

// here we assign the counter variables and set them to zero. it has been given a rather generous 32 bits.
static uint32_t verify_exit_cmd_count, verify_exit_cmd_delay_count= INITIALIZE_TO_ZERO;
static uint32_t exit_cmd_limit= 10;
static uint32_t verify_exit_cmd_delay_limit = 10;




// Standard tick function.
void verifyCmdModeExitControl_tick(){
    //debugStatePrint(); // this prints the current state to make it easier to debug the SM.
    switch(verifyCmdModeExitState) { // transitions
        case exit_init_st: // This state will immediately set the current state to the never touched state.
            verifyCmdModeExitState = verify_cmd_exit_start_st;
            break;
        case verify_cmd_exit_start_st:
            if (global_exit_cmd_start_flag) {
                global_exit_cmd_start_flag = 0;
                verifyCmdModeExitState = call_verify_cmd_mode_exit_st;
            }
            break;
        case call_verify_cmd_mode_exit_st:
            if (verify_exit_command_mode(received)) {
                verifyCmdModeExitState = verify_cmd_exit_finished;
            }
            else{
                verifyCmdModeExitState = check_verify_cmd_exit_count_st;
            }
            break;
        case check_verify_cmd_exit_count_st:
            if (verify_exit_cmd_count > exit_cmd_limit) {
                global_verify_exit_cmd_flag = 2;
                verifyCmdModeExitState = verify_cmd_exit_finished;
            }
            else{
                verifyCmdModeExitState = verify_cmd_exit_time_delay;
            }
            break;
        case verify_cmd_exit_time_delay:
            if (verify_exit_cmd_delay_count>verify_exit_cmd_delay_limit) {
                verifyCmdModeExitState = call_verify_cmd_mode_exit_st;
            }
            else{
                verifyCmdModeExitState = verify_cmd_exit_time_delay;
            }
            break;
        case verify_cmd_exit_finished:
            global_exit_cmd_start_flag = 0;
            verifyCmdModeExitState = verify_cmd_exit_start_st;
            break;

        default:
            // This should never be reached and if it is it will print an message.
            //printf("clockControl_tick state update: hit default\n\r");
            break;
    }

    switch(verifyCmdModeExitState) {// state actions
        case exit_init_st: // This state will immediately set the current state to the never touched state.
            break;
        case verify_cmd_exit_start_st:
            break;
        case call_verify_cmd_mode_exit_st:
            verify_exit_cmd_count++;
            break;
        case check_verify_cmd_exit_count_st:
            break;
        case verify_cmd_exit_time_delay:
            verify_exit_cmd_delay_count++;
            break;
        case verify_cmd_exit_finished:
            break;
        default:
            // this default should never be reached.
           // printf("clockControl_tick state action: hit default\n\r");
            break;
    }
}

// Call this before you call clockControl_tick().

void verifyCmdModeExitControl_init(){
    // set the first state to the initial state upon start up.
    verifyCmdModeExitState = exit_init_st;

}


