//
//  global_variables.c
//  BLE_Power_Monitor
//
//  Created by Luke Neumann on 1/25/20.
//  Copyright © 2020 Luke Neumann. All rights reserved.
//

#include "global_variables.h"


uint16_t overFlowCount = 0;
uint16_t overFlowCount1 = 0;
char commands[10][50];
char received[512] = "";
char UUID[130] = "2D8E217F7D1B4C5A8A970D122F6DCD8B"; // random service identifier no dashes
char UUID_1[130] = "ED220715B3BD49558B0D8D6A794D876A"; // random service identifier for server BLE address
char UUID_2[130] = "6BB6DDA52DD24512B666BD5416882F68"; // random service identifier for server BLE type
char UUID_3[130] = "CE90B8CE148D4BF8A2BB0DB2BF2A7EA9"; // random service identifier for device name
char UUID_4[130] = "D64B24D5DD29443CAAADA1BB390B7BA6"; // random service identifier for password
char UUID_5[130] = "D64B24D5DD29443CAAADA1BB390B7BA6"; // random service identifier for sample interval
char UUID_6[130] = "D64B24D5DD29443CAAADA1BB390B7BA6"; // random service identifier for number of samples per interval

char property_bitmap1[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap2[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap3[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap4[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap5[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap6[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char data_size[25] = "F0"; //The third parameter is an 8-bit value that indicates the maximum data size in octet
                         //where the value of the characteristic is held.


//char server_address_type[5] = "0"; // not phone
//char server_address[20] = "801F12B4BDCE";
char device_name[15] = "Alpha 5";
char device_address[50] = "801F12B4BDBF";
char server_address[50] = "75B9550FC5CE"; // my phone
char server_address_type[5] = "1"; // phone
char password[30] = "0000";
uint32_t sample_interval = 60; // default to 60 seconds
int32_t number_of_samples_per_interva = 12; // default to 12 samples


const float VPS = PROG_GAIN_AMP_CONFIG_3/ (32768.0*VOLTAGE_DIVIDER); // volts per step. Use this conversion in place of Amps per step.
const float MVPS = PROG_GAIN_AMP_CONFIG_0*1000/ (32768.0*GAIN); // mili volts per step. Use this conversion in place of Amps per step.
const float APS = PROG_GAIN_AMP_CONFIG_0*SHUNT_AMP_LIMIT / (32768.0*SHUNT_VOLTAGE_LIMIT*GAIN); // Amps per step (7.8125uV/step)*(200amps/(gain*0.05V))


int global_verify_cmd_flag = 0;
int global_cmd_start_flag = 0;

int global_exit_cmd_start_flag = 0;
int global_verify_exit_cmd_flag = 0;

int global_open_start_gate = 0;


int global_init_ble_module_flag = 0;
int global_start_advertising_flag = 0;
int global_stop_advertising_flag = 0;
int wait_for_user_config_flag = 0;
int disconnect_flag = 0;
int connect_flag = 0;
int send_data_flag = 0;
