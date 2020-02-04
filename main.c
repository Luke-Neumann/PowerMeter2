/* Name: main.c
 * Author: <Luke Neumann>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */



#include <stdbool.h>
#include <util/delay.h>
#include <avr/io.h>
#include "iot_uart.h"
#include "iot_twi.h"
#include "iot_timer.h"
#include "iot_ads1115.h"
#include <avr/interrupt.h>
#include "iot_external_interrupts.h"
#include "rn4870.h"
#include "update.h"
#include <string.h>
#include "global_variables.h"
#include "command_control.h"
#include "verify_cmd_mode_control.h"
#include "verify_cmd_mode_exit_control.h"









void fast_mode();


ISR(INT5_vect) // this is for the external interrupt pin PE5s
{
    fast_mode(); // run a simple test function to read and print ADC data quickly
}
ISR(USART1_RX_vect){
    //uart_print_string("TRUE");
    char temp[5] = "";
    temp[0] = USART_Receive();
    memcpy(received+strlen(received), temp, strlen(temp));
}
ISR(TIMER0_OVF_vect) // interrupt for timer 0
{
    ++overFlowCount; // increment value when the timer register overflows and is reset to zero.
    //PINA = (PINA ^ 0xFF); // inverts the PA2 pin
    //PORTA = PORTA ^ 0x04;
    commandControl_tick();
    verifyCmdModeControl_tick();
    verifyCmdModeExitControl_tick();
    
}
ISR(TIMER1_OVF_vect) // interrupt for timer 1
{
    ++overFlowCount1; // increment value when the timer register overflows and is reset to zero.
}

// This function will simplify the process to read and print data from timer 1
void PrintTimer1(){
    uint16_t endTime = 0; // This is the final value read from the clock register when the timer is stopped.
    double Time = 0.0; // This is for holding the completed time calculation.
    char text[30] = "\tTimer1: "; // text for printing before the time.
    char text1[30] = " s\r"; // text for printing after the time.
    endTime = TIM16_ReadTCNT1(); // read from the time register.
    Time = 8.0*(overFlowCount1*65536.0+endTime)/ACUTAL_CLK_F; // convert the number into seconds.
    uart_print_string(text);
    uart_print_float(Time);
    uart_print_string(text1);
}
// This function will simplify the process to read and print data from timer 0
void stopAndPrintTimer0(){
    stop_timer0(); // stop timer zero from running
    uint8_t endTime = 0; // This is the final value read from the clock register when the timer is stopped.
//    int16_t upper_bits = 0;
//    int16_t lower_bits = 0;
    float Time = 0.0; // This is for holding the completed time calculation.
    char text[30] = "\t\t\t\t\tTimer0: ";// text for printing before the time.
    char text1[30] = " ms\r"; // text for printing after the time.

    endTime = TIM16_ReadTCNT0(); // read from the time register.
    TIM16_WriteTCNT0(0x00); // reset the timer register to 0
    Time = 8.0*(overFlowCount*256.0+endTime)*1000.0/ACUTAL_CLK_F; // convert the number into seconds.
    uart_print_string(text); // print messages.
    uart_print_float(Time);
    uart_print_string(text1);
    overFlowCount = 0; // reset the overflow count.
}

void stopAndPrintTimer1(){
    stop_16_bit_timer1(); // stop timer 1 from running
    uint16_t endTime = 0; // This is the final value read from the clock register when the timer is stopped.
//    int16_t upper_bits = 0;
//    int16_t lower_bits = 0;
    float Time = 0.0; // This is for holding the completed time calculation.
    char text2[30] = " end time ";
    char text3[30] = " overflow ";
    char text[30] = "\tTimer1: ";
    char text1[30] = " ms\r";

    endTime = TIM16_ReadTCNT1();// read from the time register.
    TIM16_WriteTCNT1(0); // reset the timer to 0
    Time = 8.0*(overFlowCount1*65536.0+endTime)*1000.0/ACUTAL_CLK_F; // convert the number into seconds.
    uart_print_string(text2); // print messages
    uart_print_int(endTime);
    uart_print_string(text3);
    uart_print_int(overFlowCount1);
    uart_print_string(text);
    uart_print_float(Time);
    uart_print_string(text1);
    overFlowCount1 = 0; // reset the overflow count.
}

int16_t process3(){ // because this is used for fast mode there is no need to reset the config register
    return get_conversion_register(); // return the data.
}


// prints by reading only 1 input of ADC which makes it possible
// to sample faster than a 16 ms period.
void fast_mode(){
    char text0[8] = "Shunt: ";
    char text2[6] = " mV\r";
    float shunt_voltage = 0.0;
    shunt_voltage = process3();  // (float)process3(); // read in a value and cast it to a float
    shunt_voltage *= APS; // convert to milivolts
    shunt_voltage += BIAS; // convert to milivolts
    uart_print_string(text0); // print message
    uart_print_float(shunt_voltage);
    uart_print_string(text2);
}



void start_fast_mode(){ // initiate a fast mode.
    uint8_t upper_bits = generate_upper_config_param(OS_HIGH, MUX_0, FSR_5, MODE_0); // enter config values
    uint8_t lower_bits = generate_lower_config_param(SPS_0, COMP_MODE_0, COMP_POL_0, COMP_LAT_0, COMP_QUE_0);
    set_Hi_thresh_register(0x80, 0x00); // set the MSB high to activate the config ready alert pin
    set_Lo_thresh_register(0x00, 0x00); // set the MSB Low to activate the config ready alert pin
    set_config_register(upper_bits, lower_bits); // set the config register
    enable_interrupt_INT5(); // turn on the external interrupt pin.
}

void stop_fast_mode(){
    disable_interrupt_INT5(); // disable the external interrupt
}

int16_t process1(){
    set_config_register(0x8a, 0x83); // sets ADC to read the data from pins a0 and a1
    return get_conversion_register(); // read and return values
}

int16_t process2(){
    set_config_register(0xb4, 0x83); // sets ADC to read the data from pins a2 and a3
    return get_conversion_register(); // read and return values
}



void generate_message(){ // reads both values from the ADC and prints them.
    char text0[8] = "Shunt: ";
    char text1[15] = " A, Battery: ";
    char text2[5] = " V\r";
    float shunt_voltage;
    float battery_voltage;
    shunt_voltage = process1(); //(float)process1();
    battery_voltage = process2(); // (float)process2();
    shunt_voltage *= APS; // convert value to milivolts
    shunt_voltage += BIAS; // convert value to milivolts
    battery_voltage *= VPS; // convert value to volts
    uart_print_string(text0); // print message.
    uart_print_float(shunt_voltage);
    uart_print_string(text1);
    uart_print_float(battery_voltage);
    uart_print_string(text2);
}



void read_pin_test(){ // used for testing the pin inputs from the BLE module to get the status of the module
    char text1[15] = "\t\tst1: ";
    char text2[15] = ":";
    char text3[15] = "\r";
    uart_print_string(text1);
    uart_print_int((PIND & 0x40)>>6); // reads pd5 and shifts the bit to the right
    uart_print_string(text2);
    uart_print_int((PIND & 0x80)>>7);
    uart_print_string(text3);
    _delay_ms(300);
}


//int8_t convert_hex_to_db(char * signal_strength){
//
//    char *p = signal_strength;
//    uint8_t intVal;
//    uint8_t * p1 = &intVal;
//
//    char temp[5] = "";
////    char * p2 = temp;
//
//    if (signal_strength[0] == '-') {
//        temp[0] = signal_strength[1];
//        temp[1] = signal_strength[2];
//        //uart_print_string(temp);
//        //USART_Transmit(signal_strength[0]);
//        //return (1*((int16_t)strtol(temp,NULL,16)));
//        sscanf(temp, "%X", &intVal);
////        temp = p2;
//        //signal_strength = p;
//        return -1*(int8_t)intVal;
//    }
//    else{
//        USART_Transmit(signal_strength[0]);
//        USART_Transmit(signal_strength[1]);
//        USART_Transmit(signal_strength[2]);
//        //return (int16_t)strtol(signal_strength,NULL,16);
//        sscanf(signal_strength, "%x", &intVal);
//        signal_strength = p;
//        return intVal;
//    }
//
//
////    }
//    //uart_print_string(signal_strength);
////    char * pEnd;
////    uart_print_int((int8_t)strtol(signal_strength,&pEnd,16));
////    uart_print_int((int8_t)strtol(pEnd,&pEnd,16));
////    const char *hexstring = "0x4f";
//    //return (int8_t)strtol(hexstring[1],NULL,16);
////    char * dtm[5];
////    strcpy(dtm, signal_strength[0]);
////    USART_Transmit(*(signal_strength+2));
//
//
//
////    sscanf(p, "%x", &intVal);
//////    signal_strength = p;
////    if (&intVal == p1) {
////        uart_print_string("true\r");
////    }
////    //uart_print_int(intVal);
////    return intVal;
////    return atoi(signal_strength);
//
////    if(signal_strength[0] == "-"){
////        signal_strength[1]
////    }
////    else{
////        char *tmpSign = "";
////    }
//
//
//    // Print as parts, note that you need 0-padding for fractional bit.
//
//    //sprintf (dataString, "%s%d", tmpSign, tmpInt1);
//
//
//
//}
//
//void set_BLE_device_name(){
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!enter_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!set_device_name(received, device_name)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    _delay_ms(500);  /* max is 262.14 ms / F_CPU in MHz */
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!exit_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//}
//
//void set_up_characteristics(){
//
////    while(!enter_command_mode(received)){ // enter command mode
////        memset(received, 0, sizeof(received)); // clear the buffer
////    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//
//    while(!create_BLE_characteristic(received, UUID_1, property_bitmap1, data_size)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!create_BLE_characteristic(received, UUID_2, property_bitmap2, data_size)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!create_BLE_characteristic(received, UUID_3, property_bitmap3, data_size)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!create_BLE_characteristic(received, UUID_4, property_bitmap4, data_size)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!create_BLE_characteristic(received, UUID_5, property_bitmap5, data_size)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!create_BLE_characteristic(received, UUID_6, property_bitmap6, data_size)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//
////    while(!exit_command_mode(received)){
////        memset(received, 0, sizeof(received)); // clear the buffer
////    }
//
////    memset(received, 0, sizeof(received)); // clear the buffer
//
//}
//
///* *************************************************************
//      Set up the services and characteristics
// ************************************************************* */
//void set_up_services_and_characteristics(){
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!enter_command_mode(received)){ // enter command mode
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//    while(!set_default_services(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//    while(!clear_services_and_characteristics(received)){ // clear any prevously defined services and characteristics
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//
//    while(!reboot_device(received)){ // reboot the BLE module for changes to take hold.
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//    while(!enter_command_mode(received)){ // enter command mode
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//
//
////    while(!enter_command_mode(received)){ // enter command mode again
////        memset(received, 0, sizeof(received)); // clear the buffer
////    }
////
////    memset(received, 0, sizeof(received)); // clear the buffer
//
//
//
//
//
//    while(!create_BLE_service(received, UUID)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    //memset(received, 0, sizeof(received)); // clear the buffer
////    while(!reboot_device(received)){ // reboot the BLE module for changes to take hold.
////        memset(received, 0, sizeof(received)); // clear the buffer
////    }
//
//    //create_BLE_service(received, UUID);
//    memset(received, 0, sizeof(received)); // clear the buffer
//    set_up_characteristics();
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!reboot_device(received)){ // reboot the BLE module for changes to take hold.
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//
////    while(!exit_command_mode(received)){
////        memset(received, 0, sizeof(received)); // clear the buffer
////    }
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//    _delay_ms(50);  /* max is 262.14 ms / F_CPU in MHz */
//}
//
//
//void disconnect(){
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!enter_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(! disconnect_device(received)){ // reboot the BLE module for changes to take hold.
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!exit_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//
//}
//
//
//
//void print_services_and_characteristics(){
//
//    while(!enter_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//    list_services_and_characteristics();
//    _delay_ms(1000);  /* max is 262.14 ms / F_CPU in MHz */
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//    while(!exit_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//}
//
//
///* *************************************************************
// Start advertising so the device can be connected to by a phone
// ************************************************************* */
//void start_advertising(){
//
//
//    while(!enter_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!start_advertisement(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    _delay_ms(1000);  /* max is 262.14 ms / F_CPU in MHz */
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!exit_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    //_delay_ms(25000);  /* max is 262.14 ms / F_CPU in MHz */
//}
//
//void stop_advertising(){
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!enter_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!stop_advertisement(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    _delay_ms(300);  /* max is 262.14 ms / F_CPU in MHz */
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!exit_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    //_delay_ms(25000);  /* max is 262.14 ms / F_CPU in MHz */
//
//
//}
//
//
//void read_server_handle(){
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!enter_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//    server_handel_read();
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//   // exit_command_mode_robustly(received);
//    while(!exit_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    //_delay_ms(5000);  /* max is 262.14 ms / F_CPU in MHz */
//    //memset(received, 0, sizeof(received)); // clear the buffer
//}
//
//
//bool update_server_address(){
//    bool temp = false;
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!enter_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//    temp = set_server_address(server_address, received);
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//   // exit_command_mode_robustly(received);
//    while(!exit_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    //_delay_ms(5000);  /* max is 262.14 ms / F_CPU in MHz */
//    //memset(received, 0, sizeof(received)); // clear the buffer
//
//    return temp;
//
//}
//
//
//bool update_server_address_type(){
//    bool temp = false;
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!enter_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//    temp = set_server_address_type(server_address_type, received);
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//   // exit_command_mode_robustly(received);
//    while(!exit_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//    //_delay_ms(5000);  /* max is 262.14 ms / F_CPU in MHz */
//    //memset(received, 0, sizeof(received)); // clear the buffer
//
//    return temp;
//
//}
//
//// instead of using the command line to check the connection status
//// use the status 1 and status 0 pins to determine the connection state.
//void check_if_connected_to_device(){
//    while (!(((PIND & 0x40)>>6) == 0) && (((PIND & 0x80)>>7) == 0)) {
//        _delay_ms(50);  /* max is 262.14 ms / F_CPU in MHz */
//    }
//}
//
//bool quickly_check_if_connected_to_device(){
//
//    if (!(((PIND & 0x40)>>6) == 0) && (((PIND & 0x80)>>7) == 0)) {
//        return false;
//    }
//    else{
//        return true;
//    }
//
//}
//
//
//void parameter_configuration(){
//    bool temp1 = false;
//    bool temp2 = false;
//
//    while (!((temp1)&&(temp2))) {
////        temp3 = check_server_address();
////        temp4 = check_server_address_type();
//
//        uart_print_string("Hey 1\r");
//
//        if(!temp1){
//            if(update_server_address()){
//                temp1 = true;
//            }
//
//        }
//        uart_print_string("Hey 2\r");
//        uart_print_string(server_address);
//        uart_print_string("\r");
//        uart_print_string("Hey 3\r");
//        if(!temp2){
//            if(update_server_address_type()){
//                temp2 = true;
//            }
//
//        }
//        uart_print_string(server_address_type);
//        uart_print_string("\r");
//        uart_print_string("Hey 4\r");
//        _delay_ms(5000);
//    }
//}
//
//void connect_device(){
//    bool success2 = 0;
//
//
//
//    memset(received, 0, sizeof(received)); // clear the buffer
//    while(!enter_command_mode(received)){
//        memset(received, 0, sizeof(received)); // clear the buffer
//    }
//    memset(received, 0, sizeof(received)); // clear the buffer
//
//
//    while(!quickly_check_if_connected_to_device()){
//        memset(received, 0, sizeof(received));
//        //uart_print_string("Hey 5\r");
//
//        success2 = connect_to_device(server_address, server_address_type, received);
//        //uart_print_string("Hey 6\r");
//    }
//
//}

int main(void)
{
    char signal_strength[100] = "";
    OSCCAL = 0x57; // this determines the frequency of the rc ocilator
    _delay_ms(1000);
//    bool  success = 0;
//    bool  success1 = 0;
//    int count_test = 0;
    //DDRA = 0x04; // set pin 49 pa2 to an output pin.


    USART_Init(BAUD_RATE_REGISTER); // initialize the baudrate of the uart

    //enable_interrupt_PCINT0();  // enable the uart interrupts
    
    _delay_ms(500);
    verifyCmdModeControl_init();
    verifyCmdModeExitControl_init();
    

    start_timer0();
    

    /* insert your hardware initialization here */
    while(1){
        
        global_open_start_gate = 1;
        _delay_ms(5000);
        //generate_message();
    }
    return 0;
}
