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
#define ACUTAL_CLK_F 7300000.0 // This is used for getting the correct frequency for the timer formula.
#define COUNT_TO_SECONDS_RATIO 0.00897753

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

extern uint32_t overFlowCount;
extern uint16_t overFlowCount1;
extern uint32_t timeIntervalCount;
extern uint32_t sampleCount;

extern char debug_data[100];
uint32_t debug_commandStates_counter;
bool debug_test_print;

extern char received[200];
extern char UUID[50];
extern char UUID_1[50];
extern char UUID_2[50];
extern char UUID_3[50];
extern char UUID_4[50];
extern char UUID_5[50];
extern char UUID_6[50];

extern char UUID_8[50];
extern char UUID_9[50];
extern char UUID_10[50];


extern char property_bitmap1[25];
extern char property_bitmap2[25];
extern char property_bitmap3[25];
extern char property_bitmap4[25];
extern char property_bitmap5[25];
extern char property_bitmap6[25];

extern char property_bitmap7[25];

extern char property_bitmap9[25];
extern char property_bitmap10[25];


extern char data_size[25];

extern char handle1[10];
extern char handle2[10];
extern char handle3[10];
extern char handle4[10];
extern char handle5[10];
extern char handle6[10];
extern char handle7[10];


extern char handle9[10];
extern char handle10[10];


extern char device_name[15];
extern char device_address[50];
extern char server_address[50];
extern char server_address_type[5];
extern char password[30];
extern char sample_interval[20];
extern char number_of_samples_per_interval[20];
extern char update[10];


extern char battery_voltage[10];
extern char current[10];

//char device_name_temp[15];
//char device_address_temp[50];
//char server_address_temp[50]; // my phone
//char server_address_type_temp[5]; // phone
//char password_temp[30];
//char sample_interval_temp[20]; // default to 60 seconds
//char number_of_samples_per_interval_temp[20]; // default to 12 samples
//char update_temp[10]; // this is initially zero meaning no update has been made yet.

char device_name_hex[40];
char device_address_hex[60];
char server_address_hex[60];
char server_address_type_hex[5];
char password_hex[60];
char sample_interval_hex[40];
char number_of_samples_per_interval_hex[20];
char update_hex[20];


char battery_voltage_hex[10];
char current_hex[10];



extern const float VPS;
extern const float MVPS;
extern const float APS;


extern int global_verify_cmd_flag;
extern int global_cmd_start_flag;

extern int global_exit_cmd_start_flag;
extern int global_verify_exit_cmd_flag;

extern int global_open_start_gate;
extern int global_sequence_gate;


extern int global_init_ble_module_flag;
extern int global_start_advertising_flag;
extern int global_stop_advertising_flag;
extern int wait_for_user_config_flag;
extern int disconnect_flag;
extern int connect_flag;
extern int send_data_flag;


extern int global_command_count_sequence;
extern int global_command_sequence_limit;

extern int global_initialize_sequence_flag;
extern int global_reboot_sequence_flag;
extern int global_write_default_values_sequence_flag;
extern int global_advertise_sequence_flag;


extern int global_send_data_state;
extern int global_send_data_to_BLE;

//extern bool global_command_count_status;
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

// special command pointer tree for setting the default services
/*...............................................................................*/
// commands
char clear_ser_char_cmd0[20];
char clear_ser_char_cmd1[20];

// expected return values
char clear_ser_char_exp0[20];
char clear_ser_char_exp1[20];
// read and writable data
char clear_ser_char_spec0[20];
// sets values from BLE
char clear_ser_char_set0[20];

// combine into pointer array
char * clear_ser_char_cmd_ptr[5];
char * clear_ser_char_exp_ptr[5];
char * clear_ser_char_spec_ptr[5];
char * clear_ser_char_set_ptr[5];

// combine into a pointer of a pointer array
char ** clear_ser_char_dptr[10];
/*...............................................................................*/


// special command pointer tree for listing services and characteristics
/*...............................................................................*/
// commands
char list_ser_char_cmd0[20];
char list_ser_char_cmd1[20];

// expected return values
char list_ser_char_exp0[20];
// read and writable data
char list_ser_char_spec0[20];
// sets values from BLE
char list_ser_char_set0[20];

// combine into pointer array
char * list_ser_char_cmd_ptr[5];
char * list_ser_char_exp_ptr[5];
char * list_ser_char_spec_ptr[5];
char * list_ser_char_set_ptr[5];

// combine into a pointer of a pointer array
char ** list_ser_char_dptr[10];
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



// special command pointer tree for creating update service
/*...............................................................................*/
// commands
char set_data_ser_cmd0[20];
char set_data_ser_cmd1[20];
char set_data_ser_cmd2[20];
// expected return values
char set_data_ser_exp0[20];
char set_data_ser_exp1[20];
// read and writable data
char set_data_ser_spec0[20];
// sets values from BLE
char set_data_ser_set0[20];

// combine into pointer array
char * set_data_ser_cmd_ptr[5];
char * set_data_ser_exp_ptr[5];
char * set_data_ser_spec_ptr[5];
char * set_data_ser_set_ptr[5];

// combine into a pointer of a pointer array
char ** set_data_ser_dptr[10];


// special command pointer tree for a battery voltage characteristic
/*...............................................................................*/
// commands
char create_battery_voltage_char_cmd0[20];
char create_battery_voltage_char_cmd1[20];
char create_battery_voltage_char_cmd2[20];
char create_battery_voltage_char_cmd3[20];
char create_battery_voltage_char_cmd4[20];
// expected return values
char create_battery_voltage_char_exp0[20];
char create_battery_voltage_char_exp1[20];
// read and writable data
char create_battery_voltage_char_spec0[20];
// sets values from BLE
char create_battery_voltage_char_set0[20];

// combine into pointer array
char * create_battery_voltage_char_cmd_ptr[5];
char * create_battery_voltage_char_exp_ptr[5];
char * create_battery_voltage_char_spec_ptr[5];
char * create_battery_voltage_char_set_ptr[5];

// combine into a pointer of a pointer array
char ** create_battery_voltage_char_dptr[10];





// special command pointer tree for a current characteristic
/*...............................................................................*/
// commands
char create_current_char_cmd0[20];
char create_current_char_cmd1[20];
char create_current_char_cmd2[20];
char create_current_char_cmd3[20];
char create_current_char_cmd4[20];
// expected return values
char create_current_char_exp0[20];
char create_current_char_exp1[20];
// read and writable data
char create_current_char_spec0[20];
// sets values from BLE
char create_current_char_set0[20];

// combine into pointer array
char * create_current_char_cmd_ptr[5];
char * create_current_char_exp_ptr[5];
char * create_current_char_spec_ptr[5];
char * create_current_char_set_ptr[5];

// combine into a pointer of a pointer array
char ** create_current_char_dptr[10];

// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_battery_voltage_cmd0[20];
char write_battery_voltage_cmd1[20];
char write_battery_voltage_cmd2[20];
char write_battery_voltage_cmd3[20];
// expected return values
char write_battery_voltage_exp0[20];
char write_battery_voltage_exp1[20];
// read and writable data
char write_battery_voltage_spec0[20];
// when this is high it means to set values from BLE module into the microcontroller
char write_battery_voltage_set0[20];

// combine into pointer array
char * write_battery_voltage_cmd_ptr[5];
char * write_battery_voltage_exp_ptr[5];
char * write_battery_voltage_spec_ptr[5];
char * write_battery_voltage_set_ptr[5];

// combine into a pointer of a pointer array
char ** write_battery_voltage_dptr[10];

// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_current_cmd0[20];
char write_current_cmd1[20];
char write_current_cmd2[20];
char write_current_cmd3[20];
// expected return values
char write_current_exp0[20];
char write_current_exp1[20];
// read and writable data
char write_current_spec0[20];
// when this is high it means to set values from BLE module into the microcontroller
char write_current_set0[20];

// combine into pointer array
char * write_current_cmd_ptr[5];
char * write_current_exp_ptr[5];
char * write_current_spec_ptr[5];
char * write_current_set_ptr[5];

// combine into a pointer of a pointer array
char ** write_current_dptr[10];










// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
extern char write_server_address_cmd0[20]; // indicates size of this command branch
extern char write_server_address_cmd1[20];
extern char write_server_address_cmd2[20];
extern char write_server_address_cmd3[20];
// expected return values
extern char write_server_address_exp0[20]; // indicates size of this expected values branch
extern char write_server_address_exp1[20];
// read and writable data
extern char write_server_address_spec0[20];// indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
extern char write_server_address_set0[20];

// combine into pointer array
extern char * write_server_address_cmd_ptr[5];
extern char * write_server_address_exp_ptr[5];
extern char * write_server_address_spec_ptr[5];
extern char * write_server_address_set_ptr[5];

// combine into a pointer of a pointer array
extern char ** write_server_address_dptr[10];
/*...............................................................................*/

// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_server_address_type_cmd0[20];
char write_server_address_type_cmd1[20];
char write_server_address_type_cmd2[20];
char write_server_address_type_cmd3[20];
// expected return values
char write_server_address_type_exp0[20];
char write_server_address_type_exp1[20];
// read and writable data
char write_server_address_type_spec0[20];
// when this is high it means to set values from BLE module into the microcontroller
char write_server_address_type_set0[20];

// combine into pointer array
char * write_server_address_type_cmd_ptr[5];
char * write_server_address_type_exp_ptr[5];
char * write_server_address_type_spec_ptr[5];
char * write_server_address_type_set_ptr[5];

// combine into a pointer of a pointer array
char ** write_server_address_type_dptr[10];
/*...............................................................................*/

// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_device_name_cmd0[20];
char write_device_name_cmd1[20];
char write_device_name_cmd2[20];
char write_device_name_cmd3[20];
// expected return values
char write_device_name_exp0[20];
char write_device_name_exp1[20];
// read and writable data
char write_device_name_spec0[20];
// when this is high it means to set values from BLE module into the microcontroller
char write_device_name_set0[20];

// combine into pointer array
char * write_device_name_cmd_ptr[5];
char * write_device_name_exp_ptr[5];
char * write_device_name_spec_ptr[5];
char * write_device_name_set_ptr[5];

// combine into a pointer of a pointer array
char ** write_device_name_dptr[10];
/*...............................................................................*/

// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_password_cmd0[20];
char write_password_cmd1[20];
char write_password_cmd2[20];
char write_password_cmd3[20];
// expected return values
char write_password_exp0[20];
char write_password_exp1[20];
// read and writable data
char write_password_spec0[20];
// when this is high it means to set values from BLE module into the microcontroller
char write_password_set0[20];

// combine into pointer array
char * write_password_cmd_ptr[5];
char * write_password_exp_ptr[5];
char * write_password_spec_ptr[5];
char * write_password_set_ptr[5];

// combine into a pointer of a pointer array
char ** write_password_dptr[10];
/*...............................................................................*/

// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_sample_interval_cmd0[20];
char write_sample_interval_cmd1[20];
char write_sample_interval_cmd2[20];
char write_sample_interval_cmd3[20];
// expected return values
char write_sample_interval_exp0[20];
char write_sample_interval_exp1[20];
// read and writable data
char write_sample_interval_spec0[20];
// when this is high it means to set values from BLE module into the microcontroller
char write_sample_interval_set0[20];

// combine into pointer array
char * write_sample_interval_cmd_ptr[5];
char * write_sample_interval_exp_ptr[5];
char * write_sample_interval_spec_ptr[5];
char * write_sample_interval_set_ptr[5];

// combine into a pointer of a pointer array
char ** write_sample_interval_dptr[10];
/*...............................................................................*/


// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_number_of_samples_per_interval_cmd0[20];
char write_number_of_samples_per_interval_cmd1[20];
char write_number_of_samples_per_interval_cmd2[20];
char write_number_of_samples_per_interval_cmd3[20];
// expected return values
char write_number_of_samples_per_interval_exp0[20];
char write_number_of_samples_per_interval_exp1[20];
// read and writable data
char write_number_of_samples_per_interval_spec0[20];
// when this is high it means to set values from BLE module into the microcontroller
char write_number_of_samples_per_interval_set0[20];

// combine into pointer array
char * write_number_of_samples_per_interval_cmd_ptr[5];
char * write_number_of_samples_per_interval_exp_ptr[5];
char * write_number_of_samples_per_interval_spec_ptr[5];;

// combine into a pointer of a pointer array
char ** write_number_of_samples_per_interval_dptr[10];
/*...............................................................................*/


// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_update_cmd0[20];
char write_update_cmd1[20];
char write_update_cmd2[20];
char write_update_cmd3[20];
// expected return values
char write_update_exp0[20];
char write_update_exp1[20];
// read and writable data
char write_update_spec0[20];
// when this is high it means to set values from BLE module into the microcontroller
char write_update_set0[20];

// combine into pointer array
char * write_update_cmd_ptr[5];
char * write_update_exp_ptr[5];
char * write_update_spec_ptr[5];
char * write_update_set_ptr[5];

// combine into a pointer of a pointer array
char ** write_update_dptr[10];
/*...............................................................................*/

// special command pointer tree
/*...............................................................................*/
// commands
char stop_AD_cmd0[20]; // indicates size of this command branch
char stop_AD_cmd1[20];
// expected return values
char stop_AD_exp0[20]; // indicates size of this expected values branch
char stop_AD_exp1[20];
// read and writable data
char stop_AD_spec0[20]; // indicates size of this data branch
// sets values from BLE
char stop_AD_set0[20];

// combine into pointer array
char * stop_AD_cmd_ptr[5];
char * stop_AD_exp_ptr[5];
char * stop_AD_spec_ptr[5];
char * stop_AD_set_ptr[5];
// combine into a pointer of a pointer array
char ** stop_AD_dptr[10];
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
extern char set_ser_address_set2[20];

// combine into pointer array
extern char * set_ser_address_cmd_ptr[5];
extern char * set_ser_address_exp_ptr[5];
extern char * set_ser_address_spec_ptr[5];
extern char * set_ser_address_set_ptr[5];

// combine into a pointer of a pointer array
extern char ** set_ser_address_dptr[10];
/*...............................................................................*/


// special command pointer tree for reading server address type from bluetooth.
/*...............................................................................*/
// commands #0
char set_ser_address_type_cmd0[20];
char set_ser_address_type_cmd1[20];
char set_ser_address_type_cmd2[20];
// expected return values #1
char set_ser_address_type_exp0[20];
char set_ser_address_type_exp1[20];
// read and writable data #2
char set_ser_address_type_spec0[20];
// sets values from BLE #3
char set_ser_address_type_set0[20];
char set_ser_address_type_set1[20];
char set_ser_address_type_set2[20];

// combine into pointer array
char * set_ser_address_type_cmd_ptr[5];
char * set_ser_address_type_exp_ptr[5];
char * set_ser_address_type_spec_ptr[5];
char * set_ser_address_type_set_ptr[5];

// combine into a pointer of a pointer array
char ** set_ser_address_type_dptr[10];
/*...............................................................................*/


// special command pointer tree for reading server address type from bluetooth.
/*...............................................................................*/
// commands #0
char set_device_name_cmd0[20];
char set_device_name_cmd1[20];
char set_device_name_cmd2[20];
// expected return values #1
char set_device_name_exp0[20];
char set_device_name_exp1[20];
// read and writable data #2
char set_device_name_spec0[20];
// sets values from BLE #3
char set_device_name_set0[20];
char set_device_name_set1[20];
char set_device_name_set2[20];

// combine into pointer array
char * set_device_name_cmd_ptr[5];
char * set_device_name_exp_ptr[5];
char * set_device_name_spec_ptr[5];
char * set_device_name_set_ptr[5];

// combine into a pointer of a pointer array
char ** set_device_name_dptr[10];
/*...............................................................................*/



// special command pointer tree for reading server address type from bluetooth.
/*...............................................................................*/
// commands #0
char set_password_cmd0[20];
char set_password_cmd1[20];
char set_password_cmd2[20];
// expected return values #1
char set_password_exp0[20];
char set_password_exp1[20];
// read and writable data #2
char set_password_spec0[20];
// sets values from BLE #3
char set_password_set0[20];
char set_password_set1[20];
char set_password_set2[20];

// combine into pointer array
char * set_password_cmd_ptr[5];
char * set_password_exp_ptr[5];
char * set_password_spec_ptr[5];
char * set_password_set_ptr[5];

// combine into a pointer of a pointer array
char ** set_password_dptr[10];
/*...............................................................................*/


// special command pointer tree for reading server address type from bluetooth.
/*...............................................................................*/
// commands #0
char set_sample_interval_cmd0[20];
char set_sample_interval_cmd1[20];
char set_sample_interval_cmd2[20];
// expected return values #1
char set_sample_interval_exp0[20];
char set_sample_interval_exp1[20];
// read and writable data #2
char set_sample_interval_spec0[20];
// sets values from BLE #3
char set_sample_interval_set0[20];
char set_sample_interval_set1[20];
char set_sample_interval_set2[20];

// combine into pointer array
char * set_sample_interval_cmd_ptr[5];
char * set_sample_interval_exp_ptr[5];
char * set_sample_interval_spec_ptr[5];
char * set_sample_interval_set_ptr[5];

// combine into a pointer of a pointer array
char ** set_sample_interval_dptr[10];
/*...............................................................................*/



// special command pointer tree for reading server address type from bluetooth.
/*...............................................................................*/
// commands #0
char set_number_of_samples_per_interval_cmd0[20];
char set_number_of_samples_per_interval_cmd1[20];
char set_number_of_samples_per_interval_cmd2[20];
// expected return values #1
char set_number_of_samples_per_interval_exp0[20];
char set_number_of_samples_per_interval_exp1[20];
// read and writable data #2
char set_number_of_samples_per_interval_spec0[20];
// sets values from BLE #3
char set_number_of_samples_per_interval_set0[20];
char set_number_of_samples_per_interval_set1[20];
char set_number_of_samples_per_interval_set2[20];

// combine into pointer array
char * set_number_of_samples_per_interval_cmd_ptr[5];
char * set_number_of_samples_per_interval_exp_ptr[5];
char * set_number_of_samples_per_interval_spec_ptr[5];
char * set_number_of_samples_per_interval_set_ptr[5];

// combine into a pointer of a pointer array
char ** set_number_of_samples_per_interval_dptr[10];
/*...............................................................................*/


// special command pointer tree for getting the update status from the ble device
/*...............................................................................*/
// commands #0
char check_update_status_cmd0[20];
char check_update_status_cmd1[20];
char check_update_status_cmd2[20];
// expected return values #1
char check_update_status_exp0[20];
char check_update_status_exp1[20];
// read and writable data #2
char check_update_status_spec0[20];
// sets values from BLE #3
char check_update_status_set0[20];
char check_update_status_set1[20];

// combine into pointer array
char * check_update_status_cmd_ptr[5];
char * check_update_status_exp_ptr[5];
char * check_update_status_spec_ptr[5];
char * check_update_status_set_ptr[5];

// combine into a pointer of a pointer array
char ** check_update_status_dptr[10];
/*...............................................................................*/


/*...............................................................................*/
// commands
char disconnect_cmd0[20];
char disconnect_cmd1[20];
// expected return values
char disconnect_exp0[20];
char disconnect_exp1[25];
// read and writable data
char disconnect_spec0[20];
// sets values from BLE
char disconnect_set0[20];

// combine into pointer array
char * disconnect_cmd_ptr[5];
char * disconnect_exp_ptr[5];
char * disconnect_spec_ptr[5];
char * disconnect_set_ptr[5];
// combine into a pointer of a pointer array
char ** disconnect_dptr[10];
/*...............................................................................*/

/*...............................................................................*/
// commands
char connect_cmd0[20];
char connect_cmd1[20];
char connect_cmd2[20];
char connect_cmd3[20];

// expected return values
char connect_exp0[20];
char connect_exp1[25];
// read and writable data
char connect_spec0[20];
// sets values from BLE
char connect_set0[20];

// combine into pointer array
char * connect_cmd_ptr[5];
char * connect_exp_ptr[5];
char * connect_spec_ptr[5];
char * connect_set_ptr[5];
// combine into a pointer of a pointer array
char ** connect_dptr[10];
/*...............................................................................*/

extern char initialize_sequence_size[10];
extern char * initialize_sequence_size_ptr[10];
extern char ** initialize_sequence_size_dptr[10];
extern char *** initialize_sequence[20];



extern char reboot_sequence_size[10];
extern char * reboot_sequence_size_ptr[10];
extern char ** reboot_sequence_size_dptr[10];
extern char *** reboot_sequence[20];


extern char advertise_sequence_size[10];
extern char * advertise_sequence_size_ptr[10];
extern char ** advertise_sequence_size_dptr[10];
extern char *** advertise_sequence[20];


char stop_advertise_sequence_size[10];
char * stop_advertise_sequence_size_ptr[10];
char ** stop_advertise_sequence_size_dptr[10];
char *** stop_advertise_sequence[20];


char check_update_status_sequence_size[10];
char * check_update_status_sequence_size_ptr[10];
char ** check_update_status_sequence_size_dptr[10];
char *** check_update_status_sequence[20];

char disconnect_sequence_size[10];
char * disconnect_sequence_size_ptr[10];
char ** disconnect_sequence_size_dptr[10];
char *** disconnect_sequence[20];

char connect_sequence_size[10];
char * connect_sequence_size_ptr[10];
char ** connect_sequence_size_dptr[10];
char *** connect_sequence[20];


char write_data_sequence_size[10];
char * write_data_sequence_size_ptr[10];
char ** write_data_sequence_size_dptr[10];
char *** write_data_sequence[20];

extern char **** master_command[15];

#endif /* global_variables_h */
