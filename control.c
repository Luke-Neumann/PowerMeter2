


#include "rn4870.h"
#include <stdint.h>
#include <stdio.h>
#include "control.h"
#include "global_variables.h"





// This enumerator will set up all the different states with different integer values automatically upon compilation.
enum MainCommandStates {main_init_st, // This is the initial state of the state Machine.
    configure_ble_module_st,
    reboot_st,
    set_default_values_state,
    begin_advertising_st,
    check_if_connected_st,
    stop_advertising_st,
    wait_for_user_update_st,
    write_updated_values_st,
    disconnect_st,
    connect_st,
    send_data_st,
    wait_for_configuration_update_st,
    main_reset_st
} MainCommandState;

// here we assign the counter variables and set them to zero. it has been given a rather generous 32 bits.
static uint32_t count1, count2, count3, limit1, limit2, limit3 = 0;



// Standard tick function.
void MainCommandControl_tick(char * received, char * commands){
    //debugStatePrint(); // this prints the current state to make it easier to debug the SM.
    switch(MainCommandState) { // transitions
        case main_init_st: // This state will immediately set the current
//            global_sequence_gate = 1;
            global_open_start_gate = 1;
            global_command_count_sequence = 0;
            MainCommandState = configure_ble_module_st;
            break;
        case configure_ble_module_st:
            if (global_open_start_gate == 2) {
                //global_sequence_gate = 1;
                global_open_start_gate = 1;
                global_command_count_sequence = 1;
                MainCommandState = reboot_st;
            }
            break;
        case reboot_st:
            if (global_open_start_gate == 2) {
                global_open_start_gate = 1;
                global_command_count_sequence = 2;
                MainCommandState = set_default_values_state;
            }
            break;
        case set_default_values_state:
            if (global_open_start_gate == 2) {
                global_open_start_gate = 1;
                global_command_count_sequence = 3;
                MainCommandState = begin_advertising_st;
            }
            break;
        case begin_advertising_st:
            if (global_open_start_gate == 2) {
                global_open_start_gate = 0;
                MainCommandState = check_if_connected_st;
            }
            break;
        case check_if_connected_st:
            if (quickly_check_if_connected_to_device()) {
                global_open_start_gate = 1;
                global_command_count_sequence = 4;
                MainCommandState = stop_advertising_st;
            }
            break;
        case stop_advertising_st:
            if (global_open_start_gate == 2) {
                global_open_start_gate = 1;
                global_command_count_sequence = 5;
                MainCommandState = wait_for_user_update_st;
            }
            break;
        case wait_for_user_update_st:
            if (global_open_start_gate == 2) {
                
                if(compare_ble_value(master_command[5][1])){
                    
                    set_update_status(master_command[6][1]);
                    set_update_status(master_command[6][2]);
                    set_update_status(master_command[6][3]);
                    set_update_status(master_command[6][4]);
                    set_update_status(master_command[6][5]);
                    set_update_status(master_command[6][6]);
                    
                    global_open_start_gate = 1;
                    global_command_count_sequence = 6;
                    MainCommandState = write_updated_values_st;
                }
                else{ // keep checking the update switch
                    global_open_start_gate = 1;
                    global_command_count_sequence = 5;
                    MainCommandState = wait_for_user_update_st;
                }

   
            }
            break;
        case write_updated_values_st:
            if (global_open_start_gate == 2) {
  
                reset_update_status(master_command[6][1]);
                reset_update_status(master_command[6][2]);
                reset_update_status(master_command[6][3]);
                reset_update_status(master_command[6][4]);
                reset_update_status(master_command[6][5]);
                reset_update_status(master_command[6][6]);
                reset_update_status(master_command[5][1]);
                global_open_start_gate = 1;
                global_command_count_sequence = 7;
                
                MainCommandState = disconnect_st;
            }
            break;
        case disconnect_st:
            if (global_open_start_gate == 2) {
                global_open_start_gate = 1;
                global_command_count_sequence = 8;
                MainCommandState = connect_st;
            }
            break;
        case connect_st:
            if (global_open_start_gate == 2) {
                
                MainCommandState = send_data_st;
            }
            break;
        case send_data_st:
            if (1) {
                MainCommandState = wait_for_configuration_update_st;
            }
            break;
        case wait_for_configuration_update_st:
            break;
            if (1) {
                MainCommandState = send_data_st;
            }
        case main_reset_st:
            break;
        default:
            // This should never be reached and if it is it will print an message.
            //printf("clockControl_tick state update: hit default\n\r");
            break;
    }

    switch(MainCommandState) {// state actions
        case main_init_st: // This state will immediately set the current
            break;
        case configure_ble_module_st:
            break;
        case reboot_st:
            break;
        case set_default_values_state:
            break;
        case begin_advertising_st:
            break;
        case check_if_connected_st:
            break;
        case stop_advertising_st:
            break;
        case wait_for_user_update_st:
            break;
        case write_updated_values_st:
            break;
        case disconnect_st:
            break;
        case connect_st:

            break;
        case send_data_st:

            break;
        case wait_for_configuration_update_st:
            break;
        case main_reset_st:
            break;
        default:
            // this default should never be reached.
            //printf("clockControl_tick state action: hit default\n\r");
            break;
    }
}

// Call this before you call clockControl_tick().
void MainCommandControl_init(){
    // set the first state to the initial state upon start up.
    MainCommandState = main_init_st;

}


