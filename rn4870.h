//
//  rn4870.h
//  two input adc test
//
//  Created by Luke Neumann on 10/5/19.
//

#ifndef rn4870_h
#define rn4870_h

#include <stdio.h>
#include "iot_uart.h"
#include <util/delay.h>
#include <string.h>

void enter_command_mode();
void exit_command_mode();
void exit_command_mode_robustly(char * received);
void print_invalid_command(char * received);
bool verify_command_mode(char * received);
bool verify_exit_command_mode(char * received);
void send_command(char *** command);
bool verify_sent_command(char * received, char *** command);
void reset_update_status(char *** command);
void set_update_status(char *** command);

int hex_to_int(char c);

int hex_to_ascii(char c, char d);
void convert_hex_to_char(char * Hex_address);
void char_to_hex(char * ascii_address, char * hex_address);
bool quickly_check_if_connected_to_device();
bool compare_ble_value(char *** command);

//void get_BLE_info();
//bool reboot_device(char * received);
//bool disconnect_device(char * received);
//void get_signal_strength(char * address, char * type); // the signal strength in dBm.
//bool start_advertisement(char * address);
//bool connect_to_device(char * address, char * type, char * received);
//bool create_BLE_service(char * received, char * UUID);
//bool create_BLE_characteristic(char * received, char * UUID,char * property_bitmap, char * data_size);
//bool clear_services_and_characteristics(char * received);
//void list_services_and_characteristics();
//bool set_default_services(char * received);
//bool set_device_name(char * received, char * name);
//void server_handel_read();
//bool get_connection_status(char * received);
//bool stop_advertisement(char * address);







#endif /* rn4870_h */
