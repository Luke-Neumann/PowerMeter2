


#include "rn4870.h"
#include <stdint.h>
#include <stdio.h>
#include "control.h"


#define INITIALIZE_TO_ZERO 0



// This enumerator will set up all the different states with different integer values automatically upon compilation.
enum commandStates {main_init_st, // This is the initial state of the state Machine.
    main_start_gate_st,
    configure_ble_module_st,
    check_if_connected_st,
    stop_advertising_st,
    wait_for_user_update_st,
    disconnect_st,
    connect_st,
    send_data_st,
    wait_for_configuration_update_st,
    main_reset_st
} commandState;

// here we assign the counter variables and set them to zero. it has been given a rather generous 32 bits.
static uint32_t count1, count2, count3, limit1, limit2, limit3 = INITIALIZE_TO_ZERO;






//// This is a debug state print routine. It will print the names of the states each
//// time tick() is called. It only prints states if they are different than the
//// previous state.
//void debugStatePrint() {
//  static commandStates previousState;
//  static bool firstPass = true;
//  // Only print the message if:
//  // 1. This the first pass and the value for previousState is unknown.
//  // 2. previousState != currentState - this prevents reprinting the same state name over and over.
//  if (previousState != commandState || firstPass) {
//    firstPass = false;                // previousState will be defined, firstPass is false.
//    previousState = commandState;     // keep track of the last state that you were in.
//    printf("secondsCounter:%d\n\r", (int)secondsCounter);
//    switch(clockState) {            // This prints messages based upon the state that you were in.
//      case init_st: // prints the init state
//        printf("init_st\n\r");
//        break;
//      case never_touched_st: // prints the never touched state
//        printf("never_touched_st\n\r");
//        break;
//      case waiting_for_touch_st: // prints the wait for touch state
//        printf("waiting_for_touch_st\n\r");
//        break;
//      case adc_Counter_running_st: // prints the adc counter running state
//        printf("adc_Counter_running_st\n\r");
//        break;
//      case auto_Counter_running_st: // prints the auto counter running state state
//        printf("auto_Counter_running_st\n\r");
//        break;
//      case rate_Counter_runnning_st: // prints the rate counter running state
//        printf("rate_Counter_runnning_st\n\r");
//        break;
//      case rate_Counter_expired_st: // prints the rate counter expired state
//        printf("rate_Counter_expired_st\n\r");
//        break;
//      case add_second_to_clock_st: // prints the add second to clock state
//          printf("add_second_to_clock_st\n\r");
//          break;
//     }
//  }
//}

// Standard tick function.
void commandControl_tick(char * received, char * commands){
    //debugStatePrint(); // this prints the current state to make it easier to debug the SM.
    switch(commandState) { // transitions
        case main_init_st: // This state will immediately set the current
            break;
        case configure_ble_module_st:
            break;
        case check_if_connected_st:

            break;
        case stop_advertising_st:

            break;
        case wait_for_user_update_st:

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
            // This should never be reached and if it is it will print an message.
            printf("clockControl_tick state update: hit default\n\r");
            break;
    }

    switch(commandState) {// state actions
        case main_init_st: // This state will immediately set the current
            break;
        case configure_ble_module_st:
            break;
        case check_if_connected_st:

            break;
        case stop_advertising_st:

            break;
        case wait_for_user_update_st:

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
            printf("clockControl_tick state action: hit default\n\r");
            break;
    }
}

// Call this before you call clockControl_tick().
void commandControl_init(){
    // set the first state to the initial state upon start up.
    commandState = main_init_st;

}


