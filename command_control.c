//
//  command_control.c
//  BLE_Power_Monitor
//
//  Created by Luke Neumann on 1/25/20.
//  Copyright © 2020 Luke Neumann. All rights reserved.
//

#include "command_control.h"
#include "rn4870.h"
#include "global_variables.h"
#include <stdint.h>
#include <stdio.h>


// this initializes values to 0
#define INITIALIZE_TO_ZERO 0



// This enumerator will set up all the different states with different integer values automatically upon compilation.
enum commandStates {init_st, // This is the initial state of the state Machine.
    start_gate,
    enter_command_mode_st,
    verify_command_mode_st,
    check_limit1,
    check_for_commands,
    send_command_st,
    verify_command_received,
    check_limit2,
    check_for_more_commands,
    exit_command_mode_st,
    check_limit3,
    verify_command_mode_exited,
    reset_module
} commandState;

// here we assign the counter variables and set them to zero. it has been given a rather generous 32 bits.
static uint32_t count1, count2, count3, enter_cmd_count, exit_cmd_count = INITIALIZE_TO_ZERO;
static uint32_t limit1, limit2, limit3 = 10;


// Standard tick function.
void commandControl_tick(){
    //debugStatePrint(); // this prints the current state to make it easier to debug the SM.
    switch(commandState) { // transitions
        case init_st: // This state will immediately set the current state to the never touched state.
            commandState = start_gate;
            break;
        case start_gate:
            if (global_open_start_gate) {
                global_open_start_gate = 0;
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = enter_command_mode_st;
            }
            break;
        case enter_command_mode_st:
            if (enter_cmd_count >= 3) { // wait until printing is finished
                enter_cmd_count = 0;
                global_cmd_start_flag = 1; // start the verify cmd mode process
                commandState = verify_command_mode_st;
            }
            else{
                enter_command_mode();  // prints "$"
                commandState = enter_command_mode_st;
            }
            break;
        case verify_command_mode_st:


            if ((global_verify_cmd_flag==1)&&(global_cmd_start_flag==0)){
                global_verify_cmd_flag = 0;
                global_cmd_start_flag = 0;
                commandState = check_for_commands;
            }
            else if ((global_verify_cmd_flag == 2)&&(global_cmd_start_flag==0)){
                global_verify_cmd_flag = 0;
                global_cmd_start_flag = 0;
                commandState = check_limit1;
            }
            else{
                commandState = verify_command_mode_st;
            }
            break;
        case check_limit1:
            if (count1>limit1){
                commandState = reset_module;
            }
            else{
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = enter_command_mode_st;
            }
            break;
        case check_for_commands:
            if (check_command_queue(*commands)){
                commandState = send_command_st;
            }
            else {
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = exit_command_mode_st;
            }
            break;
        case send_command_st:
                // call send command
                send_command(*commands);
                commandState = verify_command_received;
            break;
        case verify_command_received:
            if (verify_sent_command(received, *commands)){
                commandState = check_for_more_commands;
            }
            else {
                commandState = check_limit2;
            }
            break;
        case check_limit2:
            if (count2>limit2){
                commandState = verify_command_received;
            }
            else{
                commandState = send_command_st;
            }
            break;
        case check_for_more_commands:
            if (check_command_queue(*commands)) {
                commandState = send_command_st;
            }
            else{
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = exit_command_mode_st;
            }
            break;
        case exit_command_mode_st:
            
            if (exit_cmd_count >= 3) { // wait until printing is finished
                exit_cmd_count = 0;
                global_exit_cmd_start_flag = 1; // start the verify cmd mode process
                commandState = verify_command_mode_exited;
            }
            else{
                exit_command_mode();  // prints "-"
                commandState = exit_command_mode_st;
            }
            break;
        case verify_command_mode_exited:
            if ((global_verify_exit_cmd_flag==1)&&(global_exit_cmd_start_flag==0)){
                global_verify_exit_cmd_flag = 0;
                global_exit_cmd_start_flag = 0;
                commandState = start_gate;
            }
            else if ((global_verify_exit_cmd_flag == 2)&&(global_exit_cmd_start_flag==0)){
                global_verify_exit_cmd_flag = 0;
                global_exit_cmd_start_flag = 0;
                commandState = check_limit3;
            }
            else{
                commandState = verify_command_mode_exited;
            }
            break;
        case check_limit3:
            if (count3>limit3) {
                commandState = reset_module;
            }
            else{
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = exit_command_mode_st;
            }
            break;
        case reset_module:
            // print error message
            commandState = init_st;
            break;
        default:
            // This should never be reached and if it is it will print an message.
            //printf("clockControl_tick state update: hit default\n\r");
            break;
    }
    switch(commandState) {// state actions
        case init_st:
            commandState = start_gate;
            break;
        case start_gate:
            break;
        case enter_command_mode_st:
            enter_cmd_count++;
            break;
        case verify_command_mode_st:
            break;
        case check_limit1:
            count1++;
            break;
        case check_for_commands:
            break;
        case send_command_st:
            break;
        case verify_command_received:
            break;
        case check_limit2:
            count2++;
            break;
        case check_for_more_commands:
            break;
        case exit_command_mode_st:
            exit_cmd_count++;
            break;
        case verify_command_mode_exited:
            break;
        case check_limit3:
            count3++;
            break;
        case reset_module:
            break;
        default:
            // this default should never be reached.
           // printf("clockControl_tick state action: hit default\n\r");
            break;
    }
}

// Call this before you call clockControl_tick().
void commandControl_init(){
    // set the first state to the initial state upon start up.
    commandState = init_st;

}


