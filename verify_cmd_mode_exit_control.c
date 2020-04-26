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
#include "iot_uart.h"

// this initializes values to 0
#define INITIALIZE_TO_ZERO 0

// This enumerator will set up all the different states with different integer values automatically upon compilation.
enum verifyExitCmdModeStates {enter_exit_init_st, // This is the initial state of the state Machine.
    verify_exit_cmd_start_st,
    call_verify_exit_cmd_mode_st,
    verify_exit_cmd_mode_st,
    clear_exit_buffer_st,
    inner_exit_delay_st,
    outer_exit_delay_st,
    verify_exit_cmd_finished
} verifyExitCmdModeState;


// here we assign the counter variables and set them to zero. it has been given a rather generous 32 bits.
static uint32_t exit_outer_count, exit_inner_count, exit_buffer_count= INITIALIZE_TO_ZERO;
static uint32_t exit_outer_limit = 10;
static uint32_t exit_inner_limit = 10;
static uint32_t exit_buffer_delay = 5;

//// This is a debug state print routine. It will print the names of the states each
//// time tick() is called. It only prints states if they are different than the
//// previous state.
//void debugStatePrint() {
//  static enum verifyCmdModeStates previousState;
//  static bool firstPass = true;
//  // Only print the message if:
//  // 1. This the first pass and the value for previousState is unknown.
//  // 2. previousState != currentState - this prevents reprinting the same state name over and over.
//  if (previousState != verifyCmdModeState || firstPass) {
//    firstPass = false;                // previousState will be defined, firstPass is false.
//    previousState = verifyCmdModeState;     // keep track of the last state that you were in.
////    printf("secondsCounter:%d\n\r", (int)secondsCounter);
//    switch(verifyCmdModeState) {            // This prints messages based upon the state that you were in.
//      case enter_init_st: // prints the init state
//        uart_print_string("enter_init_st\n\r");
//        break;
//      case verify_cmd_start_st:
//        uart_print_string("verify_cmd_start_st\n\r");
//        break;
//      case call_verify_cmd_mode_st:
//        uart_print_string("call_verify_cmd_mode_st\n\r");
//        break;
//
//      case verify_cmd_finished:
//        uart_print_string("verify_cmd_finished\n\r");
//        break;
//     }
//  }
//}









// Standard tick function.
void verifyCmdModeExitControl_tick(){
    //debugStatePrint(); // this prints the current state to make it easier to debug the SM.
    switch(verifyExitCmdModeState) { // transitions
        case enter_exit_init_st: // This state will immediately set the current state to the never touched state.
            verifyExitCmdModeState = verify_exit_cmd_start_st;
            break;
        case verify_exit_cmd_start_st:
            if (global_exit_cmd_start_flag) {
                global_exit_cmd_start_flag =0;
                global_verify_exit_cmd_flag = 0;
                exit_outer_count = 0;
                exit_inner_count = 0;
                memset(received, 0, strlen(received)); // clear the buffer for the test
                verifyExitCmdModeState = clear_exit_buffer_st;
            }
            break;
        case clear_exit_buffer_st:
            if (exit_buffer_count > exit_buffer_delay) {
                exit_buffer_count = 0;
                verifyExitCmdModeState = call_verify_exit_cmd_mode_st;
            }
            else{
                verifyExitCmdModeState = clear_exit_buffer_st;
            }
            break;
        case call_verify_exit_cmd_mode_st:
            print_invalid_command(received);
            verifyExitCmdModeState = verify_exit_cmd_mode_st;
            break;
        case verify_exit_cmd_mode_st:
            if (strlen(received)) {
                verifyExitCmdModeState = inner_exit_delay_st;
            }
            else{
                global_verify_exit_cmd_flag = 1;
                verifyExitCmdModeState = verify_exit_cmd_finished;
            }
            break;
        case inner_exit_delay_st:
            if (exit_inner_count < exit_inner_limit) {
                verifyExitCmdModeState = verify_exit_cmd_mode_st;
            }
            else{
                uart_print_string("---\r");
                verifyExitCmdModeState = outer_exit_delay_st;
            }
            break;
        case outer_exit_delay_st:
            if (exit_outer_count < exit_outer_limit) {
                exit_inner_count = 0;
                verifyExitCmdModeState = clear_exit_buffer_st;
            }
            else{
                global_verify_exit_cmd_flag = 2;
                verifyExitCmdModeState = verify_exit_cmd_finished;
            }
            break;
        case verify_exit_cmd_finished:
            verifyExitCmdModeState = verify_exit_cmd_start_st;
            break;
        default:
            // This should never be reached and if it is it will print an message.
            //printf("clockControl_tick state update: hit default\n\r");
            break;
    }

    switch(verifyExitCmdModeState) {// state actions
        case enter_exit_init_st: // This state will immediately set the current state to the never touched state.
            break;
        case verify_exit_cmd_start_st:
            break;
        case clear_exit_buffer_st:
            exit_buffer_count++;
            break;
        case call_verify_exit_cmd_mode_st:
            break;
        case inner_exit_delay_st:
            exit_inner_count++;
            break;
        case verify_exit_cmd_mode_st:
            break;
        case outer_exit_delay_st:
            exit_outer_count++;
            break;
        case verify_exit_cmd_finished:
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
    verifyExitCmdModeState = enter_exit_init_st;

}




//#include "rn4870.h"
//#include "global_variables.h"
//#include <stdint.h>
//#include <stdio.h>
//
//// this initializes values to 0
//#define INITIALIZE_TO_ZERO 0
//
//
//
//// This enumerator will set up all the different states with different integer values automatically upon compilation.
//enum verifyCmdModeExitStates {exit_init_st, // This is the initial state of the state Machine.
//    verify_cmd_exit_start_st,
//    call_verify_cmd_mode_exit_st,
//    check_verify_cmd_exit_count_st,
//    verify_cmd_exit_time_delay,
//    verify_cmd_exit_finished
//} verifyCmdModeExitState;
//
//// here we assign the counter variables and set them to zero. it has been given a rather generous 32 bits.
//static uint32_t verify_exit_cmd_count, verify_exit_cmd_delay_count= INITIALIZE_TO_ZERO;
//static uint32_t exit_cmd_limit= 10;
//static uint32_t verify_exit_cmd_delay_limit = 10;
//
//
//
//
//// Standard tick function.
//void verifyCmdModeExitControl_tick(){
//    //debugStatePrint(); // this prints the current state to make it easier to debug the SM.
//    switch(verifyCmdModeExitState) { // transitions
//        case exit_init_st: // This state will immediately set the current state to the never touched state.
//            verifyCmdModeExitState = verify_cmd_exit_start_st;
//            break;
//        case verify_cmd_exit_start_st:
//            if (global_exit_cmd_start_flag) {
//                global_exit_cmd_start_flag = 0;
//                verifyCmdModeExitState = call_verify_cmd_mode_exit_st;
//            }
//            break;
//        case call_verify_cmd_mode_exit_st:
//            if (verify_exit_command_mode(received)) {
//                verifyCmdModeExitState = verify_cmd_exit_finished;
//            }
//            else{
//                verifyCmdModeExitState = check_verify_cmd_exit_count_st;
//            }
//            break;
//        case check_verify_cmd_exit_count_st:
//            if (verify_exit_cmd_count > exit_cmd_limit) {
//                global_verify_exit_cmd_flag = 2;
//                verifyCmdModeExitState = verify_cmd_exit_finished;
//            }
//            else{
//                verifyCmdModeExitState = verify_cmd_exit_time_delay;
//            }
//            break;
//        case verify_cmd_exit_time_delay:
//            if (verify_exit_cmd_delay_count>verify_exit_cmd_delay_limit) {
//                verifyCmdModeExitState = call_verify_cmd_mode_exit_st;
//            }
//            else{
//                verifyCmdModeExitState = verify_cmd_exit_time_delay;
//            }
//            break;
//        case verify_cmd_exit_finished:
//            global_exit_cmd_start_flag = 0;
//            verifyCmdModeExitState = verify_cmd_exit_start_st;
//            break;
//
//        default:
//            // This should never be reached and if it is it will print an message.
//            //printf("clockControl_tick state update: hit default\n\r");
//            break;
//    }
//
//    switch(verifyCmdModeExitState) {// state actions
//        case exit_init_st: // This state will immediately set the current state to the never touched state.
//            break;
//        case verify_cmd_exit_start_st:
//            break;
//        case call_verify_cmd_mode_exit_st:
//            verify_exit_cmd_count++;
//            break;
//        case check_verify_cmd_exit_count_st:
//            break;
//        case verify_cmd_exit_time_delay:
//            verify_exit_cmd_delay_count++;
//            break;
//        case verify_cmd_exit_finished:
//            break;
//        default:
//            // this default should never be reached.
//           // printf("clockControl_tick state action: hit default\n\r");
//            break;
//    }
//}
//
//// Call this before you call clockControl_tick().
//
//void verifyCmdModeExitControl_init(){
//    // set the first state to the initial state upon start up.
//    verifyCmdModeExitState = exit_init_st;
//
//}
//
//
