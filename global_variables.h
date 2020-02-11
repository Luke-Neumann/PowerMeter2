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

extern uint16_t overFlowCount;
extern uint16_t overFlowCount1;


extern char received[512];
extern char UUID[130];
extern char UUID_1[130];
extern char UUID_2[130];
extern char UUID_3[130];
extern char UUID_4[130];
extern char UUID_5[130];
extern char UUID_6[130];

extern char property_bitmap1[25];
extern char property_bitmap2[25];
extern char property_bitmap3[25];
extern char property_bitmap4[25];
extern char property_bitmap5[25];
extern char property_bitmap6[25];
extern char data_size[25];



extern char device_name[15];
extern char device_address[50];
extern char server_address[50];
extern char server_address_type[5];
extern char password[30];
extern char sample_interval[20];
extern char number_of_samples_per_interval[20];


extern const float VPS;
extern const float MVPS;
extern const float APS;


extern int global_verify_cmd_flag;
extern int global_cmd_start_flag;

extern int global_exit_cmd_start_flag;
extern int global_verify_exit_cmd_flag;

extern int global_open_start_gate;


extern int global_init_ble_module_flag;
extern int global_start_advertising_flag;
extern int global_stop_advertising_flag;
extern int wait_for_user_config_flag;
extern int disconnect_flag;
extern int connect_flag;
extern int send_data_flag;


extern int global_command_count_sequence;
extern bool global_command_count_status;
extern char * commandPtr[15];


// special command cluster
/*................................*/
extern char start_AD_cmd0[20];
extern char start_AD_cmd1[20];

extern char start_AD_exp0[20];
extern char start_AD_exp1[20];

extern char start_AD_spec0[20];

extern char * start_AD_cmd_ptr[5];
extern char * start_AD_exp_ptr[5];
extern char * start_AD_spec_ptr[5];

extern char ** start_AD_dptr[5];
/*................................*/


// special command pointer tree for setting device name
/*...............................................................................*/
// commands
char set_name_cmd0[20];
char set_name_cmd1[20];
char set_name_cmd2[20];
// expected return values
char set_name_exp0[20];
char set_name_exp1[20];
// read and writable data
char set_name_spec0[20];


// combine into pointer array
char * set_name_cmd_ptr[5];
char * set_name_exp_ptr[5];
char * set_name_spec_ptr[5];

// combine into a pointer of a pointer array
char ** set_name_dptr[5];
/*...............................................................................*/



extern char *** command_queue[5];

#endif /* global_variables_h */
