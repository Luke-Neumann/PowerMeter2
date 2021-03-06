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

#include "global_variables.h"



int hex_to_int(char c){
        int first = c / 16 - 3;
        int second = c % 16;
        int result = first*10 + second;
        if(result > 9) result--;
        return result;
}

int hex_to_ascii(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}

void convert_hex_to_char(char * Hex_address){
    
    int length = strlen(Hex_address);
    char address[50] = "";
    int i;
    int temp;
    char value_holder[5];
    char buf = 0;

    for(i = 0; i < length; i++){
        if(i % 2 != 0){
            temp = hex_to_ascii(buf, Hex_address[i]);
            sprintf(value_holder, "%c", temp);
            strncat(address, value_holder, strlen(value_holder));
        }else{
            buf = Hex_address[i];
        }
    }
    memset(Hex_address, 0, strlen(Hex_address)); // clear the old address
    memcpy(Hex_address, address, strlen(address)); // copy the converted value to Hex address
    
}


void char_to_hex(char * ascii_address, char * hex_address){
    int i =0;
    int j = 0;
    for(i=0,j=0;i<strlen(ascii_address);i++,j+=2)
    {
        sprintf((char*)hex_address+j,"%02X", ascii_address[i]);
    }
    hex_address[j]='\0'; /*adding NULL in the end*/
}




void send_command(char *** command){
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
        }
        
        if (atoi(command[2][0])-i>=0) {
            memcpy(appended_command + sum, command[2][i], strlen(command[2][i]));
            sum += strlen(command[2][i]);

        }


    }
    memset(received, 0, strlen(received)); // clear the old
    uart_print_string(appended_command);
}

bool verify_sent_command(char * received, char *** command){
    
    char * address_holder1 = received;
    char * address_holder2 = command[3][1];
    char * address_holder3 = command[3][2];
    int count = 0;
    int count1 = 0;
    int number_of_matching_chars = 0;
    char expected[200] = "";
    int sum = 0;
    
    // if the expected value size is 0 then we dont care about what is returned.
    if (atoi(command[1][0]) == 0) {
        return true;
    }
    
    
    // assemble messeage
    int i;
    for (i = 1; i < atoi(command[1][0])+1; i++){
        
        memcpy(expected + sum, command[1][i], strlen(command[1][i]));
        sum += strlen(command[1][i]);
    }
    
    
    if (atoi(command[3][0])==1) { // indicates if we are checking to update the values from the ble device
        
        if (atoi(command[3][3]) == 1) { // indicates that the old value has changed.
            
            memset(command[3][1], 0, strlen(command[3][1])); // clear the old
            while ((*received != '\r')&&(*received != '\0')) {
                *command[3][1] = *received;
                command[3][1]++;
                received++;
            }
            received = address_holder1;
            command[3][1] = address_holder2;
            convert_hex_to_char(command[3][1]);
            



        }
        else{
            
            memset(command[3][2], 0, strlen(command[3][2])); // clear the old
            while ((*received != '\r')&&(*received != '\0')) {
                *command[3][2] = *received;
                command[3][2]++;
                received++;
            }
            received = address_holder1;
            command[3][2] = address_holder3;
            convert_hex_to_char(command[3][2]);

        }
        
        
        
//        if (shr_count > 5) {
//            shr_count = 0;
//            return true;
//        }
//        else{
//            shr_count++;
//            return false;
//        }
            
        return true;

        

        
        
        
        
        
    }
    else{
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


}





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
    memset(received, 0, strlen(received));
    char cmd[10] = "test\r";
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
    uart_print_string("-");
}



bool quickly_check_if_connected_to_device(){

    if (!(((PIND & 0x40)>>6) == 0) && (((PIND & 0x80)>>7) == 0)) {
        return false;
    }
    else{
        return true;
    }

}

bool compare_ble_value(char *** command){
    char * address_holder1 = command[3][1];
    char * address_holder2 = command[3][2];
    
    while ((*command[3][1] != '\0')&&(command[3][2] != '\0')) {
        if (!(*command[3][1] == *command[3][2])) {
            command[3][1] = address_holder1;
            command[3][2] = address_holder2;
            
            set_update_status(command);
            
//            memset(command[3][3], 0, strlen(command[3][3])); // clear the old address
//            memcpy(command[3][3], "1", strlen("1")); // copy the converted value to Hex address
            
            return true; // this should mean the values are different
        }

        command[3][1]++;
        command[3][2]++;

    }
    
    
    command[3][1] = address_holder1;
    command[3][2] = address_holder2;
    
    
    return false;
}

void set_update_status(char *** command){
    memset(command[3][3], 0, strlen(command[3][3])); // clear the old address
    memcpy(command[3][3], "1", strlen("1")); // copy the converted value to Hex address
}

void reset_update_status(char *** command){
    memset(command[3][3], 0, strlen(command[3][3])); // clear the old address
    memcpy(command[3][3], "0", strlen("0")); // copy the converted value to Hex address
}

void reset_BLE_High(){
    DDRA = (1 << 6);           /* make the LED pin an output */
    PORTA = (1 << 6);
}


void reset_BLE_Low(){
    DDRA = (1 << 6);           /* make the LED pin an output */
    PORTA = (0 << 6);
}

//void get_BLE_info(){
//    char cmd[5] = "D\r";
//    uart_print_string(cmd);
//    _delay_ms(10);  /* max is 262.14 ms / F_CPU in MHz */
//}
//
//bool reboot_device(char * received){
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    char expected[30] = "Rebooting\r\n%REBOOT%";
//    char cmd[10] = "R,1\r";
//    uart_print_string(cmd);
//    _delay_ms(300);  /* max is 262.14 ms / F_CPU in MHz */
//    while (count2<1000) {
//        count = 0;
//        count1 = 0;
//        _delay_ms(10);
//        while(count<strlen(expected)){
//            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        if (count1 == strlen(expected)) {
//            memset(received, 0, sizeof(received)); // clear the buffer
//            return true;
//        }
//        count2++;
//    }
//
//    return false; // unable to match the input data.
//     //return true;
//
//}
//
//bool disconnect_device(char * received){
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    char expected[30] = "AOK\r\nCMD> %DISCONNECT%";
//    char cmd[10] = "K,1\r";
//    uart_print_string(cmd);
//    _delay_ms(300);  /* max is 262.14 ms / F_CPU in MHz */
//    while (count2<1000) {
//        count = 0;
//        count1 = 0;
//        _delay_ms(10);
//        while(count<strlen(expected)){
//            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        if (count1 == strlen(expected)) {
//            memset(received, 0, sizeof(received)); // clear the buffer
//            return true;
//        }
//        count2++;
//    }
//
//    return false; // unable to match the input data.
//     //return true;
//
//}
//
//
//
//void get_signal_strength(char * address, char * type){ // the signal strength in dBm.
//
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    //char expected[10] = "\r";
//    char error[10] = "Err\r";
//
//
//    char cmd[10] = "M\r";
//    uart_print_string(cmd);
//    _delay_ms(10);  // wait for the return signal.
//
//    count = 0;
//    count1 = 0;
//    _delay_ms(10);
//    while(count<strlen(error)){ // check if there was an error
//        if(address[count]==error[count]){ // compare what is inside of the recieved character to the expected character
//            ++count1;
//        }
//        ++count;
//    }
//    count = 0;
//    if (count1 == strlen(error)) { // check if there was an error
//        memset(type, 0, sizeof(type)); // clear the buffer
//        memset(address, 0, sizeof(address)); // clear the buffer
//    }
//    else{
//        memset(type, 0, sizeof(type)); // clear the buffer
//        while(count < 3){ // copy the signal strength.
//            type[count] = address[count];
////            type++;
////            address++;
//            count++;
//        }
//        memset(address, 0, sizeof(address)); // clear the buffer
//    }
//
//
//}
//
//
//bool start_advertisement(char * address){ // the signal strength in dBm.
//
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    int count3 = 0;
//    char expected[15] = "AOK\r";
//    char error[10] = "Err\r";
//
//
//    char cmd[10] = "A,0014\r";
//    uart_print_string(cmd);
//    _delay_ms(10);  // wait for the return signal.
//
//
//
//    while(count3<50){
//        _delay_ms(10);
//        count = 0;
//        count1 = 0;
//        count2 = 0;
//        while(count<strlen(expected)){ // check if there was an error
//            if(address[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        count = 0;
////        while(count<strlen(error)){ // check if there was an error
////            if(address[count]==error[count]){ // compare what is inside of the recieved character to the expected character
////                ++count2;
////            }
////            ++count;
////        }
//        if (count1 == strlen(expected)) { // check if there was an error
//            memset(address, 0, sizeof(address)); // clear the buffer
//            return true;
//        }
////        if (count2 == strlen(error)) { // check if there was an error
////            memset(type, 0, sizeof(type)); // clear the buffer
////            memset(address, 0, sizeof(address)); // clear the buffer
////        }
//        count3++;
//
//    }
//
//    return false;
//}
//
//bool stop_advertisement(char * address){
//
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    int count3 = 0;
//    char expected[15] = "AOK\r";
//    char error[10] = "Err\r";
//
//
//    char cmd[10] = "Y\r";
//    uart_print_string(cmd);
//    _delay_ms(10);  // wait for the return signal.
//
//
//
//    while(count3<50){
//        _delay_ms(10);
//        count = 0;
//        count1 = 0;
//        count2 = 0;
//        while(count<strlen(expected)){ // check if there was an error
//            if(address[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        count = 0;
////        while(count<strlen(error)){ // check if there was an error
////            if(address[count]==error[count]){ // compare what is inside of the recieved character to the expected character
////                ++count2;
////            }
////            ++count;
////        }
//        if (count1 == strlen(expected)) { // check if there was an error
//            memset(address, 0, sizeof(address)); // clear the buffer
//            return true;
//        }
////        if (count2 == strlen(error)) { // check if there was an error
////            memset(type, 0, sizeof(type)); // clear the buffer
////            memset(address, 0, sizeof(address)); // clear the buffer
////        }
//        count3++;
//
//    }
//
//    return false;
//
//
//
//}
//
//
//// connects to a BLE device with the given address and address type
//bool connect_to_device(char * address, char * type, char * received){
////    char beginning[5] = "C,"; // This is the connect command
////    char middle[5] = ","; // This is the connect command
////    char ending[5] = "\r";
////    char total[40];
////    // build the string using memcpy
////    memcpy(total, beginning, strlen(beginning));
////    memcpy(total + strlen(beginning), type, strlen(type));
////    memcpy(total + strlen(beginning)+strlen(type), middle, strlen(middle));
////    memcpy(total + strlen(beginning)+strlen(type)+strlen(middle), address, strlen(address));
////    memcpy(total + strlen(beginning)+strlen(type)+strlen(middle)+strlen(address), ending, strlen(ending));
////    uart_print_string(total);
////    _delay_ms(500);  /* max is 262.14 ms / F_CPU in MHz */
//
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    int count3 = 0;
//    bool successful = false;
//    int unsuccessful = 0;
//    char expected[100] = "";
//    char unexpected[100] = "";
//    char exp0[30] = "Trying\r\n%CONNECT,";
//    char exp1[5] = ",";
//    char exp2[10] = "%%";
//    char exp3[15] = "STREAM_OPEN%";
//    char unexp0[30] = "DISCONNECT%Err\r";
//    //char unexp1[5] = "Err\r";
//
//    memcpy(expected, exp0, strlen(exp0));
//    memcpy(expected + strlen(exp0), type, strlen(type));
//    memcpy(expected + strlen(exp0)+strlen(type), exp1, strlen(exp1));
//    memcpy(expected + strlen(exp0)+strlen(type)+strlen(exp1), address, strlen(address));
////    memcpy(expected + strlen(exp0)+strlen(type)+strlen(exp1)+strlen(address),exp2, strlen(exp2));
////    memcpy(unexpected,expected,strlen(expected));
////    memcpy(unexpected+strlen(expected),unexp0,strlen(unexp0));
////    memcpy(expected + strlen(exp0)+strlen(type)+strlen(exp1)+strlen(address)+strlen(exp2),exp3,strlen(exp3));
//
//        //    uart_print_string(expected);
//        //    uart_print_string("\r");
//        //    uart_print_string(unexpected);
//
//
//    char beginning[5] = "C,"; // This is the connect command
//    char middle[5] = ","; // This is the connect command
//    char ending[5] = "\r";
//    char total[40]="";
//            // build the string using memcpy
//    memcpy(total, beginning, strlen(beginning));
//    memcpy(total + strlen(beginning), type, strlen(type));
//    memcpy(total + strlen(beginning)+strlen(type), middle, strlen(middle));
//    memcpy(total + strlen(beginning)+strlen(type)+strlen(middle), address, strlen(address));
//    memcpy(total + strlen(beginning)+strlen(type)+strlen(middle)+strlen(address), ending, strlen(ending));
//    uart_print_string(total);
//    //_delay_ms(500);  /* max is 262.14 ms / F_CPU in MHz */
//
//
//    while (count2<60) {
//        count = 0;
//        count1 = 0;
//        _delay_ms(100);
//        while(count<strlen(expected)){
//            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        count = 0;
//        while(count<strlen(unexpected)){
//            if(received[count]==unexpected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count3;
//            }
//            ++count;
//        }
//        if (count1 == strlen(expected)) {
//            memset(received, 0, sizeof(received)); // clear the buffer
//            return true;
//        }
//        count2++;
//
//    //            if (count3 == strlen(unexpected)) {
//    //                memset(received, 0, sizeof(received)); // clear the buffer
//    //                unsuccessful++;
//    //                break;
//    //            }
//
//    }
//    return false;
//}
//
//bool create_BLE_service(char * received, char * UUID){
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    char expected[10] = "AOK\r\n";
//
//    char cmd[5] = "PS,";
//    char endline[5] = "\r";
//    char total[256] = "";
//
//
//    memcpy(total, cmd, strlen(cmd));
//    memcpy(total + strlen(cmd), UUID, strlen(UUID));
//    memcpy(total + strlen(cmd) + strlen(UUID), endline, strlen(endline));
//
//    uart_print_string(total);
//    _delay_ms(50);  /* max is 262.14 ms / F_CPU in MHz */
//
//
//    // uart_print_string(address);
//
//    while (count2<50) {
//        count = 0;
//        count1 = 0;
//        _delay_ms(10);
//        while(count<strlen(expected)){
//            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        if (count1 == strlen(expected)) {
//            memset(received, 0, sizeof(received)); // clear the buffer
//            return true;
//        }
//        count2++;
//    }
//    return false; // unable to match the input data.
//     //return true;
//
//}
//
//bool create_BLE_characteristic(char * received, char * UUID,char * property_bitmap, char * data_size){
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    char expected[10] = "AOK\r\n";
//
//    char cmd[5] = "PC,";
//    char cmd1[5] = ",";
//    char cmd2[5] = ",";
//    char endline[5] = "\r";
//    char total[256] = "";
//
//
//    memcpy(total, cmd, strlen(cmd));
//    memcpy(total + strlen(cmd), UUID, strlen(UUID));
//    memcpy(total + strlen(cmd) + strlen(UUID), cmd1, strlen(cmd1));
//    memcpy(total + strlen(cmd) + strlen(UUID) + strlen(cmd1), property_bitmap, strlen(property_bitmap));
//    memcpy(total + strlen(cmd) + strlen(UUID) + strlen(cmd1) + strlen(property_bitmap), cmd2, strlen(cmd2));
//    memcpy(total + strlen(cmd) + strlen(UUID) + strlen(cmd1) + strlen(property_bitmap)+strlen(cmd2), data_size, strlen(data_size));
//    memcpy(total + strlen(cmd) + strlen(UUID) + strlen(cmd1) + strlen(property_bitmap)+strlen(cmd2)+strlen(data_size), endline, strlen(endline));
//
//    uart_print_string(total);
//    _delay_ms(50);  /* max is 262.14 ms / F_CPU in MHz */
//
//
//    // uart_print_string(address);
//
//    while (count2<50) {
//        count = 0;
//        count1 = 0;
//        _delay_ms(10);
//        while(count<strlen(expected)){
//            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        if (count1 == strlen(expected)) {
//            memset(received, 0, sizeof(received)); // clear the buffer
//            return true;
//        }
//        count2++;
//    }
//    return false; // unable to match the input data.
//     //return true;
//
//}
//
//bool clear_services_and_characteristics(char * received){
//    //memset(received, 0, sizeof(received)); // clear the buffer
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    char expected[15] = "AOK\r\nCMD> ";
//
//    char cmd[10] = "PZ\r";
//
//    //_delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string(cmd);
//
//
//
//    // uart_print_string(address);
//
//    while (count2<500) {
//        count = 0;
//        count1 = 0;
//        _delay_ms(10);
//        while(count<strlen(expected)){
//            //uart_print_string(received);
//            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        if (count1 == strlen(expected)) {
//            //uart_print_string("test\r\n");
//            memset(received, 0, sizeof(received)); // clear the buffer
//            return true;
//
//        }
//        count2++;
//    }
//    return false; // unable to match the input data.
//     //return true;
//
//}
//
//void list_services_and_characteristics(){
//    char cmd[10] = "LS\r";
//    uart_print_string(cmd);
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//}
//
//bool set_default_services(char * received){
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    char expected[15] = "AOK\r\nCMD> ";
//
//    char cmd[10] = "SS,F0\r";
//
//    //_delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string(cmd);
//
//
//
//    // uart_print_string(address);
//
//    while (count2<1000) {
//        count = 0;
//        count1 = 0;
//        _delay_ms(10);
//        while(count<strlen(expected)){
//            //uart_print_string(received);
//            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        if (count1 == strlen(expected)) {
//            //uart_print_string("test\r\n");
//            memset(received, 0, sizeof(received)); // clear the buffer
//            return true;
//        }
//        count2++;
//    }
//    return false; // unable to match the input data.
//     //return true;
//}
//
//void server_handel_read(){
//    char cmd1[10] = "SHR,0072\r";
//    char cmd2[10] = "SHR,0074\r";
//    char cmd3[10] = "SHR,0076\r";
//    char cmd4[10] = "SHR,0078\r";
//    char cmd5[10] = "SHR,007A\r";
//    char cmd6[10] = "SHR,007C\r";
//
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string(cmd1);
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string(cmd2);
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string(cmd3);
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string(cmd4);
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string(cmd5);
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string(cmd6);
//    _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//}
//
//bool check_BLE_characteristic_value(char * received, char * handle){
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    char expected[10] = "N/A\r\n\r\nCMD> ";
//    char unexpected[10] = "N/A\r\n\r\nCMD> ";
//    char cmd[5] = "SHR,";
//
//    char endline[5] = "\r";
//    char total[20] = "";
//
//
//    memcpy(total, cmd, strlen(cmd));
//    memcpy(total + strlen(cmd), handle, strlen(handle));
//    memcpy(total + strlen(cmd) + strlen(handle), endline, strlen(endline));
//
//    uart_print_string(total);
//    _delay_ms(50);  /* max is 262.14 ms / F_CPU in MHz */
//
//
//    // uart_print_string(address);
//
//    while (count2<50) {
//        count = 0;
//        count1 = 0;
//        _delay_ms(10);
//        while(count<strlen(expected)){
//            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        if (count1 == strlen(expected)) {
//            memset(received, 0, sizeof(received)); // clear the buffer
//            return true;
//        }
//        count2++;
//    }
//    return false; // unable to match the input data.
//     //return true;
//
//
//
//}
//
//void write_BLE_characteristic(){
//
//}
//
//bool set_device_name(char * received, char * name){
//    //memset(received, 0, sizeof(received)); // clear the buffer
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    char expected[15] = "AOK\r\nCMD> ";
//
//    char cmd[10] = "SN,";
//    char end[5] = "\r";
//    char total[30] = "";
//
//    memcpy(total, cmd, strlen(cmd));
//    memcpy(total + strlen(cmd), name, strlen(name));
//    memcpy(total + strlen(cmd) + strlen(name), end, strlen(end));
//
//
//    //_delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//
//    //_delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
//    uart_print_string(total);
//
//
//
//    // uart_print_string(address);
//
//    while (count2<500) {
//        count = 0;
//        count1 = 0;
//        _delay_ms(10);
//        while(count<strlen(expected)){
//            //uart_print_string(received);
//            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        if (count1 == strlen(expected)) {
//            //uart_print_string("test\r\n");
//            memset(received, 0, sizeof(received)); // clear the buffer
//            return true;
//
//        }
//        count2++;
//    }
//    return false; // unable to match the input data.
//     //return true;
//}
//
//bool get_connection_status(char * received){
//    int count = 0;
//    int count1 = 0;
//    int count2 = 0;
//    char expected[15] = "none\r\nCMD> ";
//    char cmd[10] = "GK\r";
//
//    uart_print_string(cmd);
//    while (count2<500) {
//        count = 0;
//        count1 = 0;
//        _delay_ms(10);
//        while(count<strlen(expected)){
//            if(received[count]==expected[count]){ // compare what is inside of the recieved character to the expected character
//                ++count1;
//            }
//            ++count;
//        }
//        if (count1 == strlen(expected)) {
//            memset(received, 0, sizeof(received)); // clear the buffer
//            return true;
//        }
//        count2++;
//    }
//    return false; // unable to match the input data.
//}




