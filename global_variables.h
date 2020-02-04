//
//  global_variables.h
//  BLE_Power_Monitor
//
//  Created by Luke Neumann on 1/25/20.
//  Copyright © 2020 Luke Neumann. All rights reserved.
//

#ifndef global_variables_h
#define global_variables_h

#include <stdio.h>
#include "iot_ads1115.h"

#define F_CPU 8000000    // AVR clock frequency in Hz, used by util/delay.h
#define ACUTAL_CLK_F 8000000 //7300000.0 // This is used for getting the correct frequency for the timer formula.
#define BAUD_RATE 115200 // This can be any other baud rate.
#define BAUD_RATE_REGISTER 3//(F_CPU/(16*BAUD_RATE))-1 // formula to set the baud rate register

// battery sensing info
#define R1 150000 // ideally should be 150k. Used for dividing VCC
#define R2 11090 // ideally should be 11k. Used for dividing VCC
// the goal is to get a voltage division ratio of 2.048/30 which is about 0.068323
// This will allow for VCC to go up to 30 volts without going out of the range of the ADC.
#define VOLTAGE_DIVIDER 0.068171//R2/(R1+R2)

// current sensing info
#define GAIN 5.1 // This is the gain of the op amp that feeds into the shunt. It is used to calculate the voltage
#define SHUNT_VOLTAGE_LIMIT 0.05 // for example 200 amps gives 50 mv
#define SHUNT_AMP_LIMIT 200 // This is the shunts rated amperage.
#define BIAS 0.0 //0.16677 // Can be used to correct biased data.

extern uint16_t overFlowCount = 0;
extern uint16_t overFlowCount1 = 0;

extern char commands[10][50];
extern char received[512] = "";
extern char UUID[130] = "2D8E217F7D1B4C5A8A970D122F6DCD8B"; // random service identifier no dashes
extern char UUID_1[130] = "ED220715B3BD49558B0D8D6A794D876A"; // random service identifier for server BLE address
extern char UUID_2[130] = "6BB6DDA52DD24512B666BD5416882F68"; // random service identifier for server BLE type
extern char UUID_3[130] = "CE90B8CE148D4BF8A2BB0DB2BF2A7EA9"; // random service identifier for device name
extern char UUID_4[130] = "D64B24D5DD29443CAAADA1BB390B7BA6"; // random service identifier for password
extern char UUID_5[130] = "D64B24D5DD29443CAAADA1BB390B7BA6"; // random service identifier for sample interval
extern char UUID_6[130] = "D64B24D5DD29443CAAADA1BB390B7BA6"; // random service identifier for number of samples per interval

extern char property_bitmap1[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
extern char property_bitmap2[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
extern char property_bitmap3[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
extern char property_bitmap4[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
extern char property_bitmap5[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
extern char property_bitmap6[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
extern char data_size[25] = "F0"; //The third parameter is an 8-bit value that indicates the maximum data size in octet
                         //where the value of the characteristic is held.


//char server_address_type[5] = "0"; // not phone
//char server_address[20] = "801F12B4BDCE";
extern char device_name[15] = "Alpha 5";
extern char device_address[50] = "801F12B4BDBF";
extern char server_address[50] = "75B9550FC5CE"; // my phone
extern char server_address_type[5] = "1"; // phone
extern char password[30] = "0000";
extern uint32_t sample_interval = 60; // default to 60 seconds
extern int32_t number_of_samples_per_interva = 12; // default to 12 samples


extern const float VPS = PROG_GAIN_AMP_CONFIG_3/ (32768.0*VOLTAGE_DIVIDER); // volts per step. Use this conversion in place of Amps per step.
extern onst float MVPS = PROG_GAIN_AMP_CONFIG_0*1000/ (32768.0*GAIN); // mili volts per step. Use this conversion in place of Amps per step.
extern onst float APS = PROG_GAIN_AMP_CONFIG_0*SHUNT_AMP_LIMIT / (32768.0*SHUNT_VOLTAGE_LIMIT*GAIN); // Amps per step (7.8125uV/step)*(200amps/(gain*0.05V))


extern int global_verify_cmd_flag = 0;
extern int global_cmd_start_flag = 0;

extern int global_exit_cmd_start_flag = 0;
extern int global_verify_exit_cmd_flag = 0;

extern int global_open_start_gate = 0;


extern int global_init_ble_module_flag = 0;
extern int global_start_advertising_flag = 0;
extern int global_stop_advertising_flag = 0;
extern int wait_for_user_config_flag = 0;
extern int disconnect_flag = 0;
extern int connect_flag = 0;
extern int send_data_flag = 0;








#endif /* global_variables_h */
