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
    check_limit4,
    check_limit6,
    verify_command_mode_exited,
    reset_module
} commandState, previousState;









// here we assign the counter variables and set them to zero. it has been given a rather generous 32 bits.
static uint32_t count1, count2, count3, count4, count6, enter_cmd_count, exit_cmd_count = INITIALIZE_TO_ZERO;
static uint32_t limit1, limit2, limit3= 20;
static uint32_t limit6 = 300;
static uint32_t count5= 1;
static uint32_t limit4= 200;

bool firstPass = true;

//char init_st_print[5] = "1"; //init_st";
//char enter_command_mode_st_print[5] =  "2"; //"enter_command_mode_st";
//char verify_command_mode_st_print[5] =  "3"; //"verify_command_mode_st";
//char check_limit1_print[5] =  "4"; //"check_limit1";
//char check_for_commands_print[5] =  "5"; //"check_for_commands";
//char send_command_st_print[5] =  "6"; //"send_command_st";
//char verify_command_received_print[5] =  "7"; //"verify_command_received";
//char check_limit2_print[5] =  "8"; //"check_limit2";
//char check_for_more_commands_print[5] =  "9"; //"check_for_more_commands";
//char exit_command_mode_st_print[5] =  "a"; //"exit_command_mode_st";
//char check_limit3_print[5] =  "b"; //"check_limit3";
//char check_limit4_print[5] =  "c"; //"check_limit4";
//char check_limit6_print[5] = "d"; // "check_limit6";
//char verify_command_mode_exited_print[5] =  "e"; //"verify_command_mode_exited";
//char reset_module_print[5] =  "f"; //"reset_module";


// This is a debug state print routine. It will print the names of the states each
// time tick() is called. It only prints states if they are different than the
// previous state.
void debugStatePrint() {


    // Only print the message if:
    // 1. This the first pass and the value for previousState is unknown.
    // 2. previousState != currentState - this prevents reprinting the same state name over and over.
    if (previousState != commandState || firstPass) {
        firstPass = false;                // previousState will be defined, firstPass is false.
        previousState = commandState;     // keep track of the last state that you were in.
        //printf("secondsCounter:%d\n\r", (int)secondsCounter);
        switch(commandState) {            // This prints messages based upon the state that you were in.
            case init_st: // prints the init state
                memcpy(debug_data, "1", 1);
                //debug_data[debug_commandStates_counter][0] = init_st_print[0];
                break;
            case enter_command_mode_st: // prints the never touched state
                memcpy(debug_data, "2", 1);
                //debug_data[debug_commandStates_counter][0] = enter_command_mode_st_print[0];
                break;
            case verify_command_mode_st: // prints the wait for touch state
                memcpy(debug_data, "3", 1);
                //debug_data[debug_commandStates_counter][0] = verify_command_mode_st_print[0];
                break;
            case check_limit1: // prints the adc counter running state
                memcpy(debug_data, "4", 1);
                //debug_data[debug_commandStates_counter][0] = check_limit1_print[0];
                break;
            case check_for_commands: // prints the auto counter running state state
                memcpy(debug_data, "5", 1);
                //debug_data[debug_commandStates_counter][0] = check_for_commands_print[0];
                break;
            case send_command_st: // prints the rate counter running state
                memcpy(debug_data, "6", 1);
                //debug_data[debug_commandStates_counter][0] = send_command_st_print[0];
                break;
            case verify_command_received: // prints the rate counter expired state
                memcpy(debug_data, "7", 1);
                //debug_data[debug_commandStates_counter][0] = verify_command_received_print[0];
                break;
            case check_limit2: // prints the add second to clock state
                memcpy(debug_data, "8", 1);
                //debug_data[debug_commandStates_counter][0] = check_limit2_print[0];
                break;
            case check_for_more_commands: // prints the add second to clock state
                memcpy(debug_data, "9", 1);
                //debug_data[debug_commandStates_counter][0] = check_for_more_commands_print[0];
                break;
            case exit_command_mode_st: // prints the add second to clock state
                memcpy(debug_data, "a", 1);
                //debug_data[debug_commandStates_counter][0] = exit_command_mode_st_print[0];
               break;
            case check_limit3: // prints the add second to clock state
                memcpy(debug_data, "b", 1);
//                j = 0;
//                while(j<strlen(check_limit3_print)){
//                    debug_data[debug_commandStates_counter][j] = check_limit3_print[j];
//                    j++;
//                }
                break;
            case check_limit4: // prints the add second to clock state
                memcpy(debug_data, "c", 1);
//                j = 0;
//                while(j<strlen(check_limit4_print)){
//                    debug_data[debug_commandStates_counter][j] = check_limit4_print[j];
//                    j++;
//                }
                break;
            case check_limit6:
                memcpy(debug_data, "d", 1);
//                j = 0;
//                while(j<strlen(check_limit6_print)){
//                    debug_data[debug_commandStates_counter][j] = check_limit6_print[j];
//                    j++;
//                }
                break;
            case verify_command_mode_exited: // prints the add second to clock state
                memcpy(debug_data, "e", 1);
//                j = 0;
//                while(j<strlen(verify_command_mode_exited_print)){
//                    debug_data[debug_commandStates_counter][j] = verify_command_mode_exited_print[j];
//                    j++;
//                }
                break;
            case reset_module: // prints the add second to clock state
                memcpy(debug_data, "f", 1);
//                j = 0;
//                while(j<strlen(reset_module_print)){
//                    debug_data[debug_commandStates_counter][j] = reset_module_print[j];
//                    j++;
//                }
                break;
        }


        debug_commandStates_counter++;
  }
}







// Standard tick function.
void commandControl_tick(){
    debugStatePrint(); // this prints the current state to make it easier to debug the SM.
    switch(commandState) { // transitions
        case init_st: // This state will immediately set the current state to the never touched state.
            commandState = start_gate;
            break;
        case start_gate:
            if (global_open_start_gate == 1) {
                
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = enter_command_mode_st;
            }
            break;
        case enter_command_mode_st:
            if (enter_cmd_count >= 4) { // wait until printing is finished
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
            if (global_verify_cmd_flag==1){
                global_verify_cmd_flag = 0;
                commandState = check_for_commands;
            }
            else if (global_verify_cmd_flag == 2){
                global_verify_cmd_flag = 0;
                commandState = check_limit1;
            }
            else{
                commandState = verify_command_mode_st;
            }
            break;
        case check_limit1:
            if (count1>limit1){
                count1 = 0;
                commandState = reset_module;
            }
            else{
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = enter_command_mode_st;
            }
            break;
        case check_for_commands:
            if (atoi(master_command[global_command_count_sequence][0][0][0]) >= count5){
                
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = send_command_st;
            }
            else {
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = exit_command_mode_st;
            }
            break;
        case send_command_st:
                // call send command
            if (global_command_count_sequence == 1) {
                send_command(master_command[global_command_count_sequence][count5]);
                commandState = check_limit6;
            }
            else{
                send_command(master_command[global_command_count_sequence][count5]);
                commandState = verify_command_received;
            }
            
            break;
        case verify_command_received:
            if (verify_sent_command(received, master_command[global_command_count_sequence][count5])){
                count5++;
                commandState = check_for_more_commands;
            }
            else {
                commandState = check_limit4;
            }
            break;
        case check_limit2:
            if (count2<limit2){
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = send_command_st;  
            }
            else{
                count2 = 0;
                commandState = exit_command_mode_st;
            }
            break;
        case check_for_more_commands:
            if (atoi(master_command[global_command_count_sequence][0][0][0]) >= count5) {
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = send_command_st;
            }
            else{
                count5 = 1;
                //global_command_count_status = false;
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = exit_command_mode_st;
            }
            break;
        case exit_command_mode_st:
            
            if (exit_cmd_count >= 4) { // wait until printing is finished
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
                global_open_start_gate = 0;
                global_sequence_gate = 2;
                //debug_test_print = true;
                uart_print_string(debug_data);
                uart_print_string("\r");
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
                count3 = 0;
                commandState = reset_module;
            }
            else{
                memset(received, 0, sizeof(received)); // clear the buffer
                commandState = exit_command_mode_st;
            }
            break;
        case check_limit4:
            if (count4<limit4){
                commandState = verify_command_received;
            }
            else{
                count4 = 0;
                commandState = check_limit2;
            }
            break;
        case check_limit6:
            if (count6>limit6) {
                count6 = 0;
                global_open_start_gate = 0;
                global_sequence_gate = 2;
                commandState = start_gate;
            }
            else{
                commandState = check_limit6;
            }
            break;
        case reset_module:
            // print error message
            global_open_start_gate = 0;
            uart_print_string("error reset called\r");
            commandState = init_st;
            break;
        default:
            // This should never be reached and if it is it will print an message.
            //printf("clockControl_tick state update: hit default\n\r");
            break;
    }
    switch(commandState) {// state actions
        case init_st:
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
        case check_limit4:
            count4++;
            break;
        case check_limit6:
            count6++;
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


