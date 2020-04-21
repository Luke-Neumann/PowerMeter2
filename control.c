


#include "rn4870.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
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
} MainCommandState, previousState;

// here we assign the counter variables and set them to zero. it has been given a rather generous 32 bits.
uint32_t count4_Main= 0;
static uint32_t limit4_Main = 4;

bool firstPass = true;

void debugStatePrint() {


    // Only print the message if:
    // 1. This the first pass and the value for previousState is unknown.
    // 2. previousState != currentState - this prevents reprinting the same state name over and over.
    if (previousState != MainCommandState || firstPass) {
        firstPass = false;                // previousState will be defined, firstPass is false.
        previousState = MainCommandState;     // keep track of the last state that you were in.
        //printf("secondsCounter:%d\n\r", (int)secondsCounter);
        switch(MainCommandState) {            // This prints messages based upon the state that you were in.
            case main_init_st: // prints the init state
                uart_print_string("main_init_st\r\n");

                break;
            case configure_ble_module_st: // prints the never touched state
                uart_print_string("configure_ble_module_st\r\n");
                break;
            case reboot_st: // prints the wait for touch state
                uart_print_string("reboot_st\r\n");
                break;
            case set_default_values_state: // prints the adc counter running state
                uart_print_string("set_default_values_state\r\n");
                break;
            case begin_advertising_st: // prints the auto counter running state state
                uart_print_string("begin_advertising_st\r\n");
                break;
            case check_if_connected_st: // prints the rate counter running state
                uart_print_string("check_if_connected_st\r\n");
                break;
            case stop_advertising_st: // prints the rate counter expired state
                uart_print_string("stop_advertising_st\r\n");
                break;
            case wait_for_user_update_st: // prints the add second to clock state
                uart_print_string("wait_for_user_update_st\r\n");
                break;
            case write_updated_values_st: // prints the add second to clock state
                uart_print_string("write_updated_values_st\r\n");
                break;
            case disconnect_st: // prints the add second to clock state
                uart_print_string("disconnect_st\r\n");
               break;
            case connect_st: // prints the add second to clock state
                uart_print_string("connect_st\r\n");
                break;
            case send_data_st: // prints the add second to clock state
                uart_print_string("send_data_st\r\n");
                break;
            case wait_for_configuration_update_st:

                uart_print_string("wait_for_configuration_update_st\r\n");
                break;
            case main_reset_st: // prints the add second to clock state

                uart_print_string("main_reset_st\r\n");
                break;

        }


        //debug_commandStates_counter++;
  }
}




// Standard tick function.
void MainCommandControl_tick(){
    debugStatePrint(); // this prints the current state to make it easier to debug the SM.
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
            if ((global_open_start_gate == 2)&&quickly_check_if_connected_to_device()) {
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
            if ((global_open_start_gate == 2)&&(quickly_check_if_connected_to_device())) {
                
                global_send_data_to_BLE = 0;
                // now disable the command control machine
                MainCommandState = send_data_st;
            }
            break;
        case send_data_st:
            
            if ((sampleCount > atoi(number_of_samples_per_interval)) &&
                (timeIntervalCount > atoi(sample_interval))) {
                sampleCount = 0;
                timeIntervalCount = 0;
                global_send_data_state = 0;
                global_send_data_to_BLE = 0;
                MainCommandState = wait_for_configuration_update_st;
            }
            else{
                if (global_send_data_to_BLE == 1) { // this writes the data to the ble module
                    global_send_data_state = 1;
                    global_command_count_sequence = 9;
                    global_send_data_to_BLE = 0;
//                    shunt_voltage *= APS; // convert value to milivolts
//                    shunt_voltage += BIAS; // convert value to milivolts
                    //battery_voltage *= VPS; // convert value to volts
                    uart_print_string("Shunt: "); // print message.
                    uart_print_string(current);
                    uart_print_string(" A, Battery: ");
                    uart_print_string(battery_voltage);
                    uart_print_string(" V\r");
                    
                }
                MainCommandState = send_data_st;
            }
            break;
        case wait_for_configuration_update_st:
            if (quickly_check_if_connected_to_device()&&(!compare_ble_value(master_command[5][1]))) {
                MainCommandState = send_data_st;
            }
            else{
                global_open_start_gate = 1;
                global_command_count_sequence = 8;
                MainCommandState = connect_st;
            }
            break;
        case main_reset_st:
            
            if (count4_Main > limit4_Main) {
                count4_Main = 0;
                reset_BLE_Low();
                MainCommandState = main_init_st;
            }
            else {
                MainCommandState = main_reset_st;
            }
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
            count4_Main++;
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


