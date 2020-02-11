//
//  rn4870.c
//  two input adc test
//
//  Created by Luke Neumann on 10/5/19.
//

#include "rn4870.h"

#include <string.h>
#include <avr/io.h>

#include "iot_uart.h"



//
//void processCommands(char * received, char * commands){
//    
//    int count1 = 0;
//    int count2 = 0;
//    int count3 = 0;
//    int * count1p = &count1;
//    int * count2p = &count2;
//    int * count3p = &count3;
//    int limit1 = 100;
//    int limit2 = 100;
//    int limit3 = 100;
//    bool reset = false;
//    // start
//    
//    while (1) {
//        // enter command mode
//        enter_command_mode(count1p);
//        // verify that command mode has been entered
//        if (verify_command_mode(received)) {
//            break;
//        }
//        if (count1 > limit1) {
//            reset = true;
//            break;
//        }
//    }
//    
//    if (reset) {
//        // reset the device - unavailable with version 2.0 of the device.
//        return;
//    }
//    else{
//        
//        // Check if there are any Commands to send
//        if (check_command_queue(commands)) {
//            // Send Command
//            // Verify Command has bee Received
//            
//            // Check if More Commands are to be sent
//        }
//        
//        
//        while (1) {
//            // Exit command Mode
//            exit_command_mode(count3p);
//            // Verify that command mode has been Exited
//            if (verify_exit_command_mode(received)) {
//                break;
//            }
//            if (count1 > limit1) {
//                reset = true;
//                break;
//            }
//        }
//
//        // Finished process
//        
//    }
//}

void send_command(char ** command){
    int sum = 0;
    char appended_command[200] = "";
    int temp0 = atoi(command[0][0]);
    int temp1 = atoi(command[2][0]);
    int temp2 = 0;
    temp2 = temp1 > temp0 ? temp1:temp0;
    int i;
    for (i = 1; i < temp2+1; i++){
        

        
        if (atoi(command[0][0])-i>=0) {
            memcpy(appended_command + sum, command[0][i], strlen(command[0][i]));
            sum += strlen(command[0][i]);
            uart_print_string("h");
        }
        
        
        if (atoi(command[2][0])-i>=0) {
            memcpy(appended_command + sum, command[2][i], strlen(command[2][i]));
            sum += strlen(command[2][i]);
            uart_print_string("k");
        }


    }
    
    uart_print_string(appended_command);
}

bool verify_sent_command(char * received, char ** command){
    int count = 0;
    int count1 = 0;
    int number_of_matching_chars = 0;
    char expected[200] = "";
    int sum = 0;
    
    // assemble messeage
    int i;
    for (i = 1; i < atoi(command[1][0])+1; i++){
        
        memcpy(expected + sum, command[0][i], strlen(command[0][i]));
        sum += strlen(command[0][i]);
    }
    

    while(count<strlen(received)){
        if(received[count]==expected[0]){ // compare what is inside of the recieved character to the expected character
            while (count1<strlen(expected)) {
                if (received[count+count1]==expected[count1]) {
                    ++number_of_matching_chars;
                    if (number_of_matching_chars == strlen(expected)) {
                        return true;
                    }
                }
                else{
                    // failed
                    number_of_matching_chars = 0;
                    count1 = 0;
                    break;
                }
                ++count1;
            }
        }
        ++count;
    }
    return false;
}





//bool verify_command_mode(char * received){
//    int count = 0;
//    int number_of_matching_chars = 0;
//    char expected[20] = "Err\r\nCMD> ";
//
//
//    while(count<strlen(expected)){
//        if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//            ++number_of_matching_chars;
//        }
//        ++count;
//    }
//
//    if (number_of_matching_chars == strlen(expected)) {
//        return true;
//    }
//    return false;
//}


bool verify_command_mode(char * received){
    int count = 0;
    int count1 = 0;

    int number_of_matching_chars = 0;
    char expected[20] = "Err\r\nCMD> ";
    
    
    while(count<strlen(received)){
        if(received[count]==expected[0]){ // compare what is inside of the recieved character to the expected character
            while (count1<strlen(expected)) {
                if (received[count+count1]==expected[count1]) {
                    ++number_of_matching_chars;
                    if (number_of_matching_chars == strlen(expected)) {
                        return true;
                    }
                }
                else{
                    // failed
                    number_of_matching_chars = 0;
                    count1 = 0;
                    break;
                }
                ++count1;
            }
        }
        ++count;
    }
    return false;
}






void print_invalid_command(char * received){
    char cmd[10] = "p\r";
    uart_print_string(cmd);
}

void reset_module(){
    
}




void enter_command_mode(){
    char cmd[10] = "$";
    uart_print_string(cmd);
}





bool verify_exit_command_mode(char * received){
    int count = 0;
    int number_of_matching_chars = 0;
    char expected[10] = "Err\r\nCMD> ";
    
    memset(received, 0, sizeof(received)); // clear the buffer for the test
    
    print_invalid_command(received); // print a false command to receive a reliable answer
    //_delay_ms(10);
    while(count<strlen(expected)){
        if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
            ++number_of_matching_chars;
        }
        ++count;
    }
    if (number_of_matching_chars == strlen(expected)) {
        return false;
    }
    return true;
    
    
}

void exit_command_mode(){
   // char cmd[3] = "-";
    uart_print_string("-");
//    _delay_ms(50);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string(cmd);
//    _delay_ms(50);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string(cmd);
//    _delay_ms(50);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string("\r");
//    (*countP)++;
}


void get_BLE_info(){
    char cmd[5] = "D\r";
    uart_print_string(cmd);
    _delay_ms(10);  /* max is 262.14 ms / F_CPU in MHz */
}

bool reboot_device(char * received){
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    char expected[30] = "Rebooting\r\n%REBOOT%";
    char cmd[10] = "R,1\r";
    uart_print_string(cmd);
    _delay_ms(300);  /* max is 262.14 ms / F_CPU in MHz */
    while (count2<1000) {
        count = 0;
        count1 = 0;
        _delay_ms(10);
        while(count<strlen(expected)){
            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        if (count1 == strlen(expected)) {
            memset(received, 0, sizeof(received)); // clear the buffer
            return true;
        }
        count2++;
    }
    
    return false; // unable to match the input data.
     //return true;
    
}

bool disconnect_device(char * received){
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    char expected[30] = "AOK\r\nCMD> %DISCONNECT%";
    char cmd[10] = "K,1\r";
    uart_print_string(cmd);
    _delay_ms(300);  /* max is 262.14 ms / F_CPU in MHz */
    while (count2<1000) {
        count = 0;
        count1 = 0;
        _delay_ms(10);
        while(count<strlen(expected)){
            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        if (count1 == strlen(expected)) {
            memset(received, 0, sizeof(received)); // clear the buffer
            return true;
        }
        count2++;
    }
    
    return false; // unable to match the input data.
     //return true;
    
}



void get_signal_strength(char * address, char * type){ // the signal strength in dBm.
    
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    //char expected[10] = "\r";
    char error[10] = "Err\r";
    
    
    char cmd[10] = "M\r";
    uart_print_string(cmd);
    _delay_ms(10);  // wait for the return signal.
    
    count = 0;
    count1 = 0;
    _delay_ms(10);
    while(count<strlen(error)){ // check if there was an error
        if(address[count]==error[count]){ // compare what is inside of the recieved character to the expected character
            ++count1;
        }
        ++count;
    }
    count = 0;
    if (count1 == strlen(error)) { // check if there was an error
        memset(type, 0, sizeof(type)); // clear the buffer
        memset(address, 0, sizeof(address)); // clear the buffer
    }
    else{
        memset(type, 0, sizeof(type)); // clear the buffer
        while(count < 3){ // copy the signal strength.
            type[count] = address[count];
//            type++;
//            address++;
            count++;
        }
        memset(address, 0, sizeof(address)); // clear the buffer
    }

    
}


bool start_advertisement(char * address){ // the signal strength in dBm.
    
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    char expected[15] = "AOK\r";
    char error[10] = "Err\r";
    
    
    char cmd[10] = "A,0014\r";
    uart_print_string(cmd);
    _delay_ms(10);  // wait for the return signal.
    

    
    while(count3<50){
        _delay_ms(10);
        count = 0;
        count1 = 0;
        count2 = 0;
        while(count<strlen(expected)){ // check if there was an error
            if(address[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        count = 0;
//        while(count<strlen(error)){ // check if there was an error
//            if(address[count]==error[count]){ // compare what is inside of the recieved character to the expected character
//                ++count2;
//            }
//            ++count;
//        }
        if (count1 == strlen(expected)) { // check if there was an error
            memset(address, 0, sizeof(address)); // clear the buffer
            return true;
        }
//        if (count2 == strlen(error)) { // check if there was an error
//            memset(type, 0, sizeof(type)); // clear the buffer
//            memset(address, 0, sizeof(address)); // clear the buffer
//        }
        count3++;

    }
    
    return false;
}

bool stop_advertisement(char * address){
    
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    char expected[15] = "AOK\r";
    char error[10] = "Err\r";
    
    
    char cmd[10] = "Y\r";
    uart_print_string(cmd);
    _delay_ms(10);  // wait for the return signal.
    

    
    while(count3<50){
        _delay_ms(10);
        count = 0;
        count1 = 0;
        count2 = 0;
        while(count<strlen(expected)){ // check if there was an error
            if(address[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        count = 0;
//        while(count<strlen(error)){ // check if there was an error
//            if(address[count]==error[count]){ // compare what is inside of the recieved character to the expected character
//                ++count2;
//            }
//            ++count;
//        }
        if (count1 == strlen(expected)) { // check if there was an error
            memset(address, 0, sizeof(address)); // clear the buffer
            return true;
        }
//        if (count2 == strlen(error)) { // check if there was an error
//            memset(type, 0, sizeof(type)); // clear the buffer
//            memset(address, 0, sizeof(address)); // clear the buffer
//        }
        count3++;

    }
    
    return false;


    
}


// connects to a BLE device with the given address and address type
bool connect_to_device(char * address, char * type, char * received){
//    char beginning[5] = "C,"; // This is the connect command
//    char middle[5] = ","; // This is the connect command
//    char ending[5] = "\r";
//    char total[40];
//    // build the string using memcpy
//    memcpy(total, beginning, strlen(beginning));
//    memcpy(total + strlen(beginning), type, strlen(type));
//    memcpy(total + strlen(beginning)+strlen(type), middle, strlen(middle));
//    memcpy(total + strlen(beginning)+strlen(type)+strlen(middle), address, strlen(address));
//    memcpy(total + strlen(beginning)+strlen(type)+strlen(middle)+strlen(address), ending, strlen(ending));
//    uart_print_string(total);
//    _delay_ms(500);  /* max is 262.14 ms / F_CPU in MHz */
    
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    bool successful = false;
    int unsuccessful = 0;
    char expected[100] = "";
    char unexpected[100] = "";
    char exp0[30] = "Trying\r\n%CONNECT,";
    char exp1[5] = ",";
    char exp2[10] = "%%";
    char exp3[15] = "STREAM_OPEN%";
    char unexp0[30] = "DISCONNECT%Err\r";
    //char unexp1[5] = "Err\r";

    memcpy(expected, exp0, strlen(exp0));
    memcpy(expected + strlen(exp0), type, strlen(type));
    memcpy(expected + strlen(exp0)+strlen(type), exp1, strlen(exp1));
    memcpy(expected + strlen(exp0)+strlen(type)+strlen(exp1), address, strlen(address));
//    memcpy(expected + strlen(exp0)+strlen(type)+strlen(exp1)+strlen(address),exp2, strlen(exp2));
//    memcpy(unexpected,expected,strlen(expected));
//    memcpy(unexpected+strlen(expected),unexp0,strlen(unexp0));
//    memcpy(expected + strlen(exp0)+strlen(type)+strlen(exp1)+strlen(address)+strlen(exp2),exp3,strlen(exp3));

        //    uart_print_string(expected);
        //    uart_print_string("\r");
        //    uart_print_string(unexpected);


    char beginning[5] = "C,"; // This is the connect command
    char middle[5] = ","; // This is the connect command
    char ending[5] = "\r";
    char total[40]="";
            // build the string using memcpy
    memcpy(total, beginning, strlen(beginning));
    memcpy(total + strlen(beginning), type, strlen(type));
    memcpy(total + strlen(beginning)+strlen(type), middle, strlen(middle));
    memcpy(total + strlen(beginning)+strlen(type)+strlen(middle), address, strlen(address));
    memcpy(total + strlen(beginning)+strlen(type)+strlen(middle)+strlen(address), ending, strlen(ending));
    uart_print_string(total);
    //_delay_ms(500);  /* max is 262.14 ms / F_CPU in MHz */


    while (count2<60) {
        count = 0;
        count1 = 0;
        _delay_ms(100);
        while(count<strlen(expected)){
            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        count = 0;
        while(count<strlen(unexpected)){
            if(received[count]==unexpected[count]){ // compare what is inside of the recieved character to the expected character
                ++count3;
            }
            ++count;
        }
        if (count1 == strlen(expected)) {
            memset(received, 0, sizeof(received)); // clear the buffer
            return true;
        }
        count2++;

    //            if (count3 == strlen(unexpected)) {
    //                memset(received, 0, sizeof(received)); // clear the buffer
    //                unsuccessful++;
    //                break;
    //            }

    }
    return false;
}

bool create_BLE_service(char * received, char * UUID){
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    char expected[10] = "AOK\r\n";
     
    char cmd[5] = "PS,";
    char endline[5] = "\r";
    char total[256] = "";
    
    
    memcpy(total, cmd, strlen(cmd));
    memcpy(total + strlen(cmd), UUID, strlen(UUID));
    memcpy(total + strlen(cmd) + strlen(UUID), endline, strlen(endline));

    uart_print_string(total);
    _delay_ms(50);  /* max is 262.14 ms / F_CPU in MHz */

     
    // uart_print_string(address);
     
    while (count2<50) {
        count = 0;
        count1 = 0;
        _delay_ms(10);
        while(count<strlen(expected)){
            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        if (count1 == strlen(expected)) {
            memset(received, 0, sizeof(received)); // clear the buffer
            return true;
        }
        count2++;
    }
    return false; // unable to match the input data.
     //return true;
    
}

bool create_BLE_characteristic(char * received, char * UUID,char * property_bitmap, char * data_size){
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    char expected[10] = "AOK\r\n";
     
    char cmd[5] = "PC,";
    char cmd1[5] = ",";
    char cmd2[5] = ",";
    char endline[5] = "\r";
    char total[256] = "";
    
    
    memcpy(total, cmd, strlen(cmd));
    memcpy(total + strlen(cmd), UUID, strlen(UUID));
    memcpy(total + strlen(cmd) + strlen(UUID), cmd1, strlen(cmd1));
    memcpy(total + strlen(cmd) + strlen(UUID) + strlen(cmd1), property_bitmap, strlen(property_bitmap));
    memcpy(total + strlen(cmd) + strlen(UUID) + strlen(cmd1) + strlen(property_bitmap), cmd2, strlen(cmd2));
    memcpy(total + strlen(cmd) + strlen(UUID) + strlen(cmd1) + strlen(property_bitmap)+strlen(cmd2), data_size, strlen(data_size));
    memcpy(total + strlen(cmd) + strlen(UUID) + strlen(cmd1) + strlen(property_bitmap)+strlen(cmd2)+strlen(data_size), endline, strlen(endline));

    uart_print_string(total);
    _delay_ms(50);  /* max is 262.14 ms / F_CPU in MHz */

     
    // uart_print_string(address);
     
    while (count2<50) {
        count = 0;
        count1 = 0;
        _delay_ms(10);
        while(count<strlen(expected)){
            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        if (count1 == strlen(expected)) {
            memset(received, 0, sizeof(received)); // clear the buffer
            return true;
        }
        count2++;
    }
    return false; // unable to match the input data.
     //return true;
    
}

bool clear_services_and_characteristics(char * received){
    //memset(received, 0, sizeof(received)); // clear the buffer
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    char expected[15] = "AOK\r\nCMD> ";
     
    char cmd[10] = "PZ\r";
    
    //_delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */

    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
    uart_print_string(cmd);
    

     
    // uart_print_string(address);
     
    while (count2<500) {
        count = 0;
        count1 = 0;
        _delay_ms(10);
        while(count<strlen(expected)){
            //uart_print_string(received);
            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        if (count1 == strlen(expected)) {
            //uart_print_string("test\r\n");
            memset(received, 0, sizeof(received)); // clear the buffer
            return true;
            
        }
        count2++;
    }
    return false; // unable to match the input data.
     //return true;
    
}

void list_services_and_characteristics(){
    char cmd[10] = "LS\r";
    uart_print_string(cmd);
    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
}

bool set_default_services(char * received){
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    char expected[15] = "AOK\r\nCMD> ";
     
    char cmd[10] = "SS,F0\r";
    
    //_delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */

    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
    uart_print_string(cmd);
    

     
    // uart_print_string(address);
     
    while (count2<1000) {
        count = 0;
        count1 = 0;
        _delay_ms(10);
        while(count<strlen(expected)){
            //uart_print_string(received);
            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        if (count1 == strlen(expected)) {
            //uart_print_string("test\r\n");
            memset(received, 0, sizeof(received)); // clear the buffer
            return true;
        }
        count2++;
    }
    return false; // unable to match the input data.
     //return true;
}

void server_handel_read(){
    char cmd1[10] = "SHR,0072\r";
    char cmd2[10] = "SHR,0074\r";
    char cmd3[10] = "SHR,0076\r";
    char cmd4[10] = "SHR,0078\r";
    char cmd5[10] = "SHR,007A\r";
    char cmd6[10] = "SHR,007C\r";
    
    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
    uart_print_string(cmd1);
    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
    uart_print_string(cmd2);
    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
    uart_print_string(cmd3);
    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
    uart_print_string(cmd4);
    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
    uart_print_string(cmd5);
    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
    uart_print_string(cmd6);
    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
}

bool check_BLE_characteristic_value(char * received, char * handle){
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    char expected[10] = "N/A\r\n\r\nCMD> ";
    char unexpected[10] = "N/A\r\n\r\nCMD> ";
    char cmd[5] = "SHR,";

    char endline[5] = "\r";
    char total[20] = "";
    
    
    memcpy(total, cmd, strlen(cmd));
    memcpy(total + strlen(cmd), handle, strlen(handle));
    memcpy(total + strlen(cmd) + strlen(handle), endline, strlen(endline));

    uart_print_string(total);
    _delay_ms(50);  /* max is 262.14 ms / F_CPU in MHz */

     
    // uart_print_string(address);
     
    while (count2<50) {
        count = 0;
        count1 = 0;
        _delay_ms(10);
        while(count<strlen(expected)){
            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        if (count1 == strlen(expected)) {
            memset(received, 0, sizeof(received)); // clear the buffer
            return true;
        }
        count2++;
    }
    return false; // unable to match the input data.
     //return true;
    
    
    
}

void write_BLE_characteristic(){
    
}

bool set_device_name(char * received, char * name){
    //memset(received, 0, sizeof(received)); // clear the buffer
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    char expected[15] = "AOK\r\nCMD> ";
     
    char cmd[10] = "SN,";
    char end[5] = "\r";
    char total[30] = "";
    
    memcpy(total, cmd, strlen(cmd));
    memcpy(total + strlen(cmd), name, strlen(name));
    memcpy(total + strlen(cmd) + strlen(name), end, strlen(end));

    
    //_delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */

    //_delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
    uart_print_string(total);
    

     
    // uart_print_string(address);
     
    while (count2<500) {
        count = 0;
        count1 = 0;
        _delay_ms(10);
        while(count<strlen(expected)){
            //uart_print_string(received);
            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        if (count1 == strlen(expected)) {
            //uart_print_string("test\r\n");
            memset(received, 0, sizeof(received)); // clear the buffer
            return true;
            
        }
        count2++;
    }
    return false; // unable to match the input data.
     //return true;
}

bool get_connection_status(char * received){
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    char expected[15] = "none\r\nCMD> ";
    char cmd[10] = "GK\r";
    
    uart_print_string(cmd);
    while (count2<500) {
        count = 0;
        count1 = 0;
        _delay_ms(10);
        while(count<strlen(expected)){
            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
                ++count1;
            }
            ++count;
        }
        if (count1 == strlen(expected)) {
            memset(received, 0, sizeof(received)); // clear the buffer
            return true;
        }
        count2++;
    }
    return false; // unable to match the input data.
}




