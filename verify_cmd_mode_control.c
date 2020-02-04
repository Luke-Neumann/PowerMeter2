//
//  verify_cmd_mode_control.c
//  BLE_Power_Monitor
//
//  Created by Luke Neumann on 1/25/20.
//  Copyright © 2020 Luke Neumann. All rights reserved.
//

#include "verify_cmd_mode_control.h"
#include "rn4870.h"
#include "global_variables.h"
#include <stdint.h>
#include <stdio.h>
#include "iot_uart.h"

// this initializes values to 0
#define INITIALIZE_TO_ZERO 0

// This enumerator will set up all the different states with different integer values automatically upon compilation.
enum verifyCmdModeStates {enter_init_st, // This is the initial state of the state Machine.
    verify_cmd_start_st,
    call_verify_cmd_mode_st,
    check_verify_cmd_count_st,
    verify_cmd_time_delay,
    verify_cmd_finished
} verifyCmdModeState;


// here we assign the counter variables and set them to zero. it has been given a rather generous 32 bits.
static uint32_t verify_cmd_count, verify_cmd_delay_count= INITIALIZE_TO_ZERO;
static uint32_t cmd_limit= 10;
static uint32_t verify_cmd_delay_limit = 10;


// This is a debug state print routine. It will print the names of the states each
// time tick() is called. It only prints states if they are different than the
// previous state.
void debugStatePrint() {
  static enum verifyCmdModeStates previousState;
  static bool firstPass = true;
  // Only print the message if:
  // 1. This the first pass and the value for previousState is unknown.
  // 2. previousState != currentState - this prevents reprinting the same state name over and over.
  if (previousState != verifyCmdModeState || firstPass) {
    firstPass = false;                // previousState will be defined, firstPass is false.
    previousState = verifyCmdModeState;     // keep track of the last state that you were in.
//    printf("secondsCounter:%d\n\r", (int)secondsCounter);
    switch(verifyCmdModeState) {            // This prints messages based upon the state that you were in.
      case enter_init_st: // prints the init state
        uart_print_string("enter_init_st\n\r");
        break;
      case verify_cmd_start_st:
        uart_print_string("verify_cmd_start_st\n\r");
        break;
      case call_verify_cmd_mode_st:
        uart_print_string("call_verify_cmd_mode_st\n\r");
        break;
      case check_verify_cmd_count_st:
        uart_print_string("check_verify_cmd_count_st\n\r");
        break;
      case verify_cmd_time_delay:
        uart_print_string("verify_cmd_time_delay\n\r");
        break;
      case verify_cmd_finished:
        uart_print_string("verify_cmd_finished\n\r");
        break;
     }
  }
}









// Standard tick function.
void verifyCmdModeControl_tick(){
    //debugStatePrint(); // this prints the current state to make it easier to debug the SM.
    switch(verifyCmdModeState) { // transitions
        case enter_init_st: // This state will immediately set the current state to the never touched state.
            verifyCmdModeState = verify_cmd_start_st;
            break;
        case verify_cmd_start_st:
            if (global_cmd_start_flag) {
                global_verify_cmd_flag = 0;
                verifyCmdModeState = call_verify_cmd_mode_st;
            }
            break;
        case call_verify_cmd_mode_st:
            if (verify_command_mode(received)) {
                verifyCmdModeState = verify_cmd_finished;
            }
            else{
                verifyCmdModeState = check_verify_cmd_count_st;
            }
            break;
        case check_verify_cmd_count_st:
            if (verify_cmd_count > cmd_limit) {
                global_verify_cmd_flag = 2;
                verifyCmdModeState = verify_cmd_finished;
            }
            else{
                verifyCmdModeState = verify_cmd_time_delay;
            }
            break;
        case verify_cmd_time_delay:

            if (verify_cmd_delay_count>verify_cmd_delay_limit) {
                verifyCmdModeState = call_verify_cmd_mode_st;
            }
            else{
                verifyCmdModeState = verify_cmd_time_delay;
            }
            break;
        case verify_cmd_finished:
            global_cmd_start_flag = 0;
            verifyCmdModeState = verify_cmd_start_st;
   
            break;

        default:
            // This should never be reached and if it is it will print an message.
            //printf("clockControl_tick state update: hit default\n\r");
            break;
    }

    switch(verifyCmdModeState) {// state actions
        case enter_init_st: // This state will immediately set the current state to the never touched state.
            break;
        case verify_cmd_start_st:
            break;
        case call_verify_cmd_mode_st:
            verify_cmd_count++;
            break;
        case check_verify_cmd_count_st:
            break;
        case verify_cmd_time_delay:
            verify_cmd_delay_count++;
            break;
        case verify_cmd_finished:
            break;
        default:
            // this default should never be reached.
           // printf("clockControl_tick state action: hit default\n\r");
            break;
    }
}

// Call this before you call clockControl_tick().
void verifyCmdModeControl_init(){
    // set the first state to the initial state upon start up.
    verifyCmdModeState = enter_init_st;

}


