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

bool firstPass = true;
//int j = 0;
//char init_st_print[50] = "init_st";
//char enter_command_mode_st_print[50] = "enter_command_mode_st";
//char verify_command_mode_st_print[50] = "verify_command_mode_st";
//char check_limit1_print[50] = "check_limit1";
//char check_for_commands_print[50] = "check_for_commands";
//char send_command_st_print[50] = "send_command_st";
//char verify_command_received_print[50] = "verify_command_received";
//char check_limit2_print[50] = "check_limit2";
//char check_for_more_commands_print[50] = "check_for_more_commands";
//char exit_command_mode_st_print[50] = "exit_command_mode_st";
//char check_limit3_print[50] = "check_limit3";
//char check_limit4_print[50] = "check_limit4";
//char verify_command_mode_exited_print[50] = "verify_command_mode_exited";
//char reset_module_print[50] = "reset_module";


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
                memcpy(debug_data + debug_commandStates_counter, "1", strlen("1"));
                debug_commandStates_counter += strlen("1");
                break;
            case enter_command_mode_st: // prints the never touched state
                memcpy(debug_data+ debug_commandStates_counter, "2", strlen("2"));
                debug_commandStates_counter += strlen("2");
                break;
            case verify_command_mode_st: // prints the wait for touch state
                memcpy(debug_data+ debug_commandStates_counter, "3", strlen("3"));
                debug_commandStates_counter += strlen("3");
                break;
            case check_limit1: // prints the adc counter running state
                memcpy(debug_data+ debug_commandStates_counter, "4", strlen("4"));
                debug_commandStates_counter += strlen("4");
                break;
            case check_for_commands: // prints the auto counter running state state
                memcpy(debug_data+ debug_commandStates_counter, "5", strlen("5"));
                debug_commandStates_counter += strlen("5");
                break;
            case send_command_st: // prints the rate counter running state
                memcpy(debug_data+ debug_commandStates_counter, "6", strlen("6"));
                debug_commandStates_counter += strlen("6");
                break;
            case verify_command_received: // prints the rate counter expired state
                memcpy(debug_data+ debug_commandStates_counter, "7", strlen("7"));
                debug_commandStates_counter += strlen("7");
                break;
            case check_limit2: // prints the add second to clock state
                memcpy(debug_data+ debug_commandStates_counter, "8", strlen("8"));
                debug_commandStates_counter += strlen("8");
                break;
            case check_for_more_commands: // prints the add second to clock state
                memcpy(debug_data+ debug_commandStates_counter, "9", strlen("9"));
                debug_commandStates_counter += strlen("9");
                break;
            case exit_command_mode_st: // prints the add second to clock state
                memcpy(debug_data+ debug_commandStates_counter, "a", strlen("a"));
                debug_commandStates_counter += strlen("a");
               break;
            case check_limit3: // prints the add second to clock state
                memcpy(debug_data+ debug_commandStates_counter, "b", strlen("b"));
                debug_commandStates_counter += strlen("b");
                break;
            case check_limit4: // prints the add second to clock state
                memcpy(debug_data+ debug_commandStates_counter, "c", strlen("c"));
                debug_commandStates_counter += strlen("c");
                break;
            case check_limit6:
                memcpy(debug_data+ debug_commandStates_counter, "d", strlen("d"));
                debug_commandStates_counter += strlen("d");
                break;
            case verify_command_mode_exited: // prints the add second to clock state
                memcpy(debug_data+ debug_commandStates_counter, "e", strlen("e"));
                debug_commandStates_counter += strlen("e");
                break;
            case reset_module: // prints the add second to clock state
                memcpy(debug_data+ debug_commandStates_counter, "f", strlen("f"));
                debug_commandStates_counter += strlen("f");
                break;
        }


        //debug_commandStates_counter++;
  }
}







// here we assign the counter variables and set them to zero. it has been given a rather generous 32 bits.
uint32_t count1 = 0;
uint32_t count2 = 0;
uint32_t count3 = 0;
uint32_t count4 = 0;
uint32_t count6 = 0;
uint32_t enter_cmd_count = 0;
uint32_t exit_cmd_count = 0;
static int limit1= 3;
static int limit2= 3;
static int limit3= 3;
static int limit6 = 30;
static int count5= 1;
static int limit4= 30;
// Standard tick function.
void commandControl_tick(){
    //debugStatePrint(); // this prints the current state to make it easier to debug the SM.
    switch(commandState) { // transitions
        case init_st: // This state will immediately set the current state to the never touched state.
            commandState = start_gate;
            break;
        case start_gate:
            if (global_open_start_gate == 1) {
                
                memset(received, 0, sizeof(received)); // clear the buffer
                enter_cmd_count = 0;
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
                reset_BLE_Low();
                commandState = reset_module;
            }
            else{
                memset(received, 0, sizeof(received)); // clear the buffer
                enter_cmd_count = 0;
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
                exit_cmd_count = 0;
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
                if((global_command_count_sequence==2)&&(count5>1)){
                    char_to_hex(master_command[global_command_count_sequence][count5][2][3], master_command[global_command_count_sequence][count5][2][2]);
                }
                send_command(master_command[global_command_count_sequence][count5]);
                commandState = verify_command_received;
            }
            
            break;
        case verify_command_received:
            if (verify_sent_command(received, master_command[global_command_count_sequence][count5])){
                count5++;
                //shr_count = 0;
                commandState = check_for_more_commands;
            }
            else {
//                if (shr_count > 0) {
//                    commandState = verify_command_received;
//                }
//                else{
//                    commandState = check_limit4;
//                }
                
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
                commandState = check_limit1;
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
                exit_cmd_count = 0;
                commandState = exit_command_mode_st;
            }
            break;
        case exit_command_mode_st:
            
            if (exit_cmd_count >= 4) { // wait until printing is finished
                exit_cmd_count = 0;
                uart_print_string("\r");
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
                global_open_start_gate = 2;
                //global_sequence_gate = 2;
                //debug_test_print = true;
                //uart_print_string("HEY:");
                //uart_print_string(debug_data);
                //uart_print_string("\r");
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
                reset_BLE_Low();
                commandState = reset_module;
            }
            else{
                memset(received, 0, sizeof(received)); // clear the buffer
                exit_cmd_count = 0;
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
                global_open_start_gate = 2;
                //global_sequence_gate = 2;
                commandState = start_gate;
            }
            else{
                commandState = check_limit6;
            }
            break;
        case reset_module:
            // print error message
            global_open_start_gate = 2;
            reset_BLE_High();
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


