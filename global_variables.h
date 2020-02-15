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

char debug_data[][100];
uint32_t debug_commandStates_counter;
bool debug_test_print;

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

extern char ** start_AD_dptr[10];
/*................................*/


// special command pointer tree for setting device name
/*...............................................................................*/
// commands
extern char set_name_cmd0[20];
extern char set_name_cmd1[20];
extern char set_name_cmd2[20];
// expected return values
extern char set_name_exp0[20];
extern char set_name_exp1[20];
// read and writable data
extern char set_name_spec0[20];


// combine into pointer array
extern char * set_name_cmd_ptr[5];
extern char * set_name_exp_ptr[5];
extern char * set_name_spec_ptr[5];

// combine into a pointer of a pointer array
extern char ** set_name_dptr[10];
/*...............................................................................*/

// special command pointer tree for setting the default services
/*...............................................................................*/
// commands
char set_default_cmd0[20];
char set_default_cmd1[20];

// expected return values
char set_default_exp0[20];
char set_default_exp1[20];
// read and writable data
char set_default_spec0[20];
// sets values from BLE
char set_default_set0[20];

// combine into pointer array
char * set_default_cmd_ptr[5];
char * set_default_exp_ptr[5];
char * set_default_spec_ptr[5];
char * set_default_set_ptr[5];

// combine into a pointer of a pointer array
char ** set_default_dptr[10];
/*...............................................................................*/

// special command pointer tree for rebooting the module
/*...............................................................................*/
// commands
char reboot_cmd0[20];
char reboot_cmd1[20];

// expected return values
char reboot_exp0[20];
char reboot_exp1[20];
// read and writable data
char reboot_spec0[20];
// sets values from BLE
char reboot_set0[20];

// combine into pointer array
char * reboot_cmd_ptr[5];
char * reboot_exp_ptr[5];
char * reboot_spec_ptr[5];
char * reboot_set_ptr[5];

// combine into a pointer of a pointer array
char ** reboot_dptr[10];
/*...............................................................................*/



// special command pointer tree for setting device name
/*...............................................................................*/
// commands
extern char set_ser_address_cmd0[20];
extern char set_ser_address_cmd1[20];

// expected return values
extern char set_ser_address_exp0[20];
extern char set_ser_address_exp1[20];
// read and writable data
extern char set_ser_address_spec0[20];
// sets values from BLE
extern char set_ser_address_set0[20];
extern char set_ser_address_set1[20];

// combine into pointer array
extern char * set_ser_address_cmd_ptr[5];
extern char * set_ser_address_exp_ptr[5];
extern char * set_ser_address_spec_ptr[5];
extern char * set_ser_address_set_ptr[5];

// combine into a pointer of a pointer array
extern char ** set_ser_address_dptr[10];
/*...............................................................................*/


// special command pointer tree for creating update service
/*...............................................................................*/
// commands
char set_update_ser_cmd0[20];
char set_update_ser_cmd1[20];
char set_update_ser_cmd2[20];
// expected return values
char set_update_ser_exp0[20];
char set_update_ser_exp1[20];
// read and writable data
char set_update_ser_spec0[20];
// sets values from BLE
char set_update_ser_set0[20];

// combine into pointer array
char * set_update_ser_cmd_ptr[5];
char * set_update_ser_exp_ptr[5];
char * set_update_ser_spec_ptr[5];
char * set_update_ser_set_ptr[5];

// combine into a pointer of a pointer array
char ** set_update_ser_dptr[10];
/*...............................................................................*/

// special command pointer tree for creating server address characteristic
/*...............................................................................*/
// commands
char set_update_address_char_cmd0[20];
char set_update_address_char_cmd1[20];
char set_update_address_char_cmd2[20];
char set_update_address_char_cmd3[20];
char set_update_address_char_cmd4[20];
// expected return values
char set_update_address_char_exp0[20];
char set_update_address_char_exp1[20];
// read and writable data
char set_update_address_char_spec0[20];
// sets values from BLE
char set_update_address_char_set0[20];

// combine into pointer array
char * set_update_address_char_cmd_ptr[5];
char * set_update_address_char_exp_ptr[5];
char * set_update_address_char_spec_ptr[5];
char * set_update_address_char_set_ptr[5];

// combine into a pointer of a pointer array
char ** set_update_address_char_dptr[10];
/*...............................................................................*/

// special command pointer tree for creating server address type characteristic
/*...............................................................................*/
// commands
char set_update_address_type_char_cmd0[20];
char set_update_address_type_char_cmd1[20];
char set_update_address_type_char_cmd2[20];
char set_update_address_type_char_cmd3[20];
char set_update_address_type_char_cmd4[20];
// expected return values
char set_update_address_type_char_exp0[20];
char set_update_address_type_char_exp1[20];
// read and writable data
char set_update_address_type_char_spec0[20];
// sets values from BLE
char set_update_address_type_char_set0[20];

// combine into pointer array
char * set_update_address_type_char_cmd_ptr[5];
char * set_update_address_type_char_exp_ptr[5];
char * set_update_address_type_char_spec_ptr[5];
char * set_update_address_type_char_set_ptr[5];

// combine into a pointer of a pointer array
char ** set_update_address_type_char_dptr[10];
/*...............................................................................*/

// special command pointer tree for creating device name characteristic
/*...............................................................................*/
// commands
char create_dev_name_char_cmd0[20];
char create_dev_name_char_cmd1[20];
char create_dev_name_char_cmd2[20];
char create_dev_name_char_cmd3[20];
char create_dev_name_char_cmd4[20];
// expected return values
char create_dev_name_char_exp0[20];
char create_dev_name_char_exp1[20];
// read and writable data
char create_dev_name_char_spec0[20];
// sets values from BLE
char create_dev_name_char_set0[20];

// combine into pointer array
char * create_dev_name_char_cmd_ptr[5];
char * create_dev_name_char_exp_ptr[5];
char * create_dev_name_char_spec_ptr[5];
char * create_dev_name_char_set_ptr[5];

// combine into a pointer of a pointer array
char ** create_dev_name_char_dptr[10];
/*...............................................................................*/

// special command pointer tree for a password characteristic
/*...............................................................................*/
// commands
char create_password_char_cmd0[20];
char create_password_char_cmd1[20];
char create_password_char_cmd2[20];
char create_password_char_cmd3[20];
char create_password_char_cmd4[20];
// expected return values
char create_password_char_exp0[20];
char create_password_char_exp1[20];
// read and writable data
char create_password_char_spec0[20];
// sets values from BLE
char create_password_char_set0[20];

// combine into pointer array
char * create_password_char_cmd_ptr[5];
char * create_password_char_exp_ptr[5];
char * create_password_char_spec_ptr[5];
char * create_password_char_set_ptr[5];

// combine into a pointer of a pointer array
char ** create_password_char_dptr[10];
/*...............................................................................*/

// special command pointer tree for a sample interval characteristic
/*...............................................................................*/
// commands
char create_smp_int_char_cmd0[20];
char create_smp_int_char_cmd1[20];
char create_smp_int_char_cmd2[20];
char create_smp_int_char_cmd3[20];
char create_smp_int_char_cmd4[20];
// expected return values
char create_smp_int_char_exp0[20];
char create_smp_int_char_exp1[20];
// read and writable data
char create_smp_int_char_spec0[20];
// sets values from BLE
char create_smp_int_char_set0[20];

// combine into pointer array
char * create_smp_int_char_cmd_ptr[5];
char * create_smp_int_char_exp_ptr[5];
char * create_smp_int_char_spec_ptr[5];
char * create_smp_int_char_set_ptr[5];

// combine into a pointer of a pointer array
char ** create_smp_int_char_dptr[10];
/*...............................................................................*/

// special command pointer tree for a number of samples per interval characteristic
/*...............................................................................*/
// commands
char create_smp_per_int_char_cmd0[20];
char create_smp_per_int_char_cmd1[20];
char create_smp_per_int_char_cmd2[20];
char create_smp_per_int_char_cmd3[20];
char create_smp_per_int_char_cmd4[20];
// expected return values
char create_smp_per_int_char_exp0[20];
char create_smp_per_int_char_exp1[20];
// read and writable data
char create_smp_per_int_char_spec0[20];
// sets values from BLE
char create_smp_per_int_char_set0[20];

// combine into pointer array
char * create_smp_per_int_char_cmd_ptr[5];
char * create_smp_per_int_char_exp_ptr[5];
char * create_smp_per_int_char_spec_ptr[5];
char * create_smp_per_int_char_set_ptr[5];

// combine into a pointer of a pointer array
char ** create_smp_per_int_char_dptr[10];
/*...............................................................................*/


// special command pointer tree for a update complete characteristic
/*...............................................................................*/
// commands
char create_updated_char_cmd0[20];
char create_updated_char_cmd1[20];
char create_updated_char_cmd2[20] ;
char create_updated_char_cmd3[20];
char create_updated_char_cmd4[20];
// expected return values
char create_updated_char_exp0[20];
char create_updated_char_exp1[20];
// read and writable data
char create_updated_char_spec0[20];
// sets values from BLE
char create_updated_char_set0[20];

// combine into pointer array
char * create_updated_char_cmd_ptr[5];
char * create_updated_char_exp_ptr[5];
char * create_updated_char_spec_ptr[5];
char * create_updated_char_set_ptr[5];

// combine into a pointer of a pointer array
char ** create_updated_char_dptr[10];
/*...............................................................................*/


extern char initialize_sequence_size[10];
extern char * initialize_sequence_size_ptr[10];
extern char ** initialize_sequence_size_dptr[10];
extern char *** initialize_sequence[20];


extern char **** master_command[10];

#endif /* global_variables_h */
