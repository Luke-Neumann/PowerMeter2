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

char debug_data[400];
//char debug_data[][100];
bool debug_test_print = false;
uint32_t debug_commandStates_counter = 0;


char received[512] = "";
char UUID[130] = "2D8E217F7D1B4C5A8A970D122F6DCD8B"; // random service identifier no dashes
char UUID_1[130] = "ED220715B3BD49558B0D8D6A794D876A"; // random service identifier for server BLE address
char UUID_2[130] = "6BB6DDA52DD24512B666BD5416882F68"; // random service identifier for server BLE type
char UUID_3[130] = "CE90B8CE148D4BF8A2BB0DB2BF2A7EA9"; // random service identifier for device name
char UUID_4[130] = "D64B24D5DD29443CAAADA1BB390B7BA6"; // random service identifier for password
char UUID_5[130] = "D64B24D5DD29443CAAADA1BB390B7BA7"; // random service identifier for sample interval
char UUID_6[130] = "D64B24D5DD29443CAAADA1BB390B7BA8"; // random service identifier for number of samples per interval
char UUID_7[130] = "D64B24D5DD29443CAAADA1BB390B7BA9"; // random service identifier for updated_status

char property_bitmap1[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap2[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap3[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap4[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap5[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap6[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap7[25] = "1C"; //The second parameter is a 8-bit property bitmap of the characteristic

char handle1[10] = "0072";
char handle2[10] = "0075";
char handle3[10] = "0078";
char handle4[10] = "007B";
char handle5[10] = "007E";
char handle6[10] = "0081";
char handle7[10] = "0084";




char data_size[25] = "F0"; //The third parameter is an 8-bit value that indicates the maximum data size in octet
                         //where the value of the characteristic is held.


//char server_address_type[5] = "0"; // not phone
//char server_address[20] = "801F12B4BDCE";
char device_name[15] = "Alpha 5";
char device_address[50] = "801F12B4BDBF";
char server_address[50] = "75B9550FC5CE"; // my phone
char server_address_type[5] = "1"; // phone
char password[30] = "0000";
char sample_interval[20] = "60"; // default to 60 seconds
char number_of_samples_per_interval[20] = "12"; // default to 12 samples
char update[10] = "0"; // this is initially zero meaning no update has been made yet.


const float VPS = PROG_GAIN_AMP_CONFIG_3/ (32768.0*VOLTAGE_DIVIDER); // volts per step. Use this conversion in place of Amps per step.
const float MVPS = PROG_GAIN_AMP_CONFIG_0*1000/ (32768.0*GAIN); // mili volts per step. Use this conversion in place of Amps per step.
const float APS = PROG_GAIN_AMP_CONFIG_0*SHUNT_AMP_LIMIT / (32768.0*SHUNT_VOLTAGE_LIMIT*GAIN); // Amps per step (7.8125uV/step)*(200amps/(gain*0.05V))


int global_verify_cmd_flag = 0;
int global_cmd_start_flag = 0;

int global_exit_cmd_start_flag = 0;
int global_verify_exit_cmd_flag = 0;

int global_open_start_gate = 0;
int global_sequence_gate = 0;


int global_init_ble_module_flag = 0;
int global_start_advertising_flag = 0;
int global_stop_advertising_flag = 0;
int wait_for_user_config_flag = 0;
int disconnect_flag = 0;
int connect_flag = 0;
int send_data_flag = 0;

int global_command_count_sequence = 0;
int global_command_sequence_limit = 2;
//bool global_command_count_status = true;

char * commandPtr[15] = {
    device_name,
    device_address,
    server_address,
    server_address_type,
    password,
    sample_interval,
    number_of_samples_per_interval
};

// special command pointer tree
/*...............................................................................*/
// commands
char start_AD_cmd0[20] = "1"; // indicates size of this command branch
char start_AD_cmd1[20] = "A,0014\r";
// expected return values
char start_AD_exp0[20] = "1"; // indicates size of this expected values branch
char start_AD_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char start_AD_spec0[20] = "0"; // indicates size of this data branch
// sets values from BLE
char start_AD_set0[20] = "0";

// combine into pointer array
char * start_AD_cmd_ptr[5] = {start_AD_cmd0,start_AD_cmd1};
char * start_AD_exp_ptr[5] = {start_AD_exp0,start_AD_exp1};
char * start_AD_spec_ptr[5] = {start_AD_spec0};
char * start_AD_set_ptr[5] = {start_AD_set0};
// combine into a pointer of a pointer array
char ** start_AD_dptr[10] = {
    start_AD_cmd_ptr,
    start_AD_exp_ptr,
    start_AD_spec_ptr,
    start_AD_set_ptr
};
/*...............................................................................*/


// special command pointer tree for setting device name
/*...............................................................................*/
// commands
char set_name_cmd0[20] = "2"; // indicates size of this command branch
char set_name_cmd1[20] = "SN,";
char set_name_cmd2[20] = "\r";
// expected return values
char set_name_exp0[20] = "1"; // indicates size of this expected values branch
char set_name_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char set_name_spec0[20] = "1"; // indicates size of this data branch
// sets values from BLE
char set_name_set0[20] = "0";

// combine into pointer array
char * set_name_cmd_ptr[5] = {set_name_cmd0,set_name_cmd1, set_name_cmd2};
char * set_name_exp_ptr[5] = {set_name_exp0,set_name_exp1};
char * set_name_spec_ptr[5] = {set_name_spec0, device_name};
char * set_name_set_ptr[5] = {set_name_set0};

// combine into a pointer of a pointer array
char ** set_name_dptr[10] = {
    set_name_cmd_ptr,
    set_name_exp_ptr,
    set_name_spec_ptr,
    set_name_set_ptr
};
/*...............................................................................*/


// special command pointer tree for setting the default services
/*...............................................................................*/
// commands
char set_default_cmd0[20] = "1"; // indicates size of this command branch
char set_default_cmd1[20] = "SS,C0\r";

// expected return values
char set_default_exp0[20] = "1"; // indicates size of this expected values branch
char set_default_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char set_default_spec0[20] = "0"; // indicates size of this data branch
// sets values from BLE
char set_default_set0[20] = "0";

// combine into pointer array
char * set_default_cmd_ptr[5] = {set_default_cmd0,set_default_cmd1};
char * set_default_exp_ptr[5] = {set_default_exp0,set_default_exp1};
char * set_default_spec_ptr[5] = {set_default_spec0};
char * set_default_set_ptr[5] = {set_default_set0};

// combine into a pointer of a pointer array
char ** set_default_dptr[10] = {
    set_default_cmd_ptr,
    set_default_exp_ptr,
    set_default_spec_ptr,
    set_default_set_ptr
};
/*...............................................................................*/

// special command pointer tree for clearing and services and characteristics
/*...............................................................................*/
// commands
char clear_ser_char_cmd0[20] = "1"; // indicates size of this command branch
char clear_ser_char_cmd1[20] = "PZ\r";

// expected return values
char clear_ser_char_exp0[20] = "1"; // indicates size of this expected values branch
char clear_ser_char_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char clear_ser_char_spec0[20] = "0"; // indicates size of this data branch
// sets values from BLE
char clear_ser_char_set0[20] = "0";

// combine into pointer array
char * clear_ser_char_cmd_ptr[5] = {clear_ser_char_cmd0,clear_ser_char_cmd1};
char * clear_ser_char_exp_ptr[5] = {clear_ser_char_exp0,clear_ser_char_exp1};
char * clear_ser_char_spec_ptr[5] = {clear_ser_char_spec0};
char * clear_ser_char_set_ptr[5] = {clear_ser_char_set0};

// combine into a pointer of a pointer array
char ** clear_ser_char_dptr[10] = {
    clear_ser_char_cmd_ptr,
    clear_ser_char_exp_ptr,
    clear_ser_char_spec_ptr,
    clear_ser_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for listing services and characteristics
/*...............................................................................*/
// commands
char list_ser_char_cmd0[20] = "1"; // indicates size of this command branch
char list_ser_char_cmd1[20] = "LS\r";

// expected return values
char list_ser_char_exp0[20] = "1"; // indicates size of this expected values branch
// read and writable data
char list_ser_char_spec0[20] = "0"; // indicates size of this data branch
// sets values from BLE
char list_ser_char_set0[20] = "0";

// combine into pointer array
char * list_ser_char_cmd_ptr[5] = {list_ser_char_cmd0,list_ser_char_cmd1};
char * list_ser_char_exp_ptr[5] = {list_ser_char_exp0,UUID};
char * list_ser_char_spec_ptr[5] = {list_ser_char_spec0};
char * list_ser_char_set_ptr[5] = {list_ser_char_set0};

// combine into a pointer of a pointer array
char ** list_ser_char_dptr[10] = {
    list_ser_char_cmd_ptr,
    list_ser_char_exp_ptr,
    list_ser_char_spec_ptr,
    list_ser_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for rebooting the module
/*...............................................................................*/
// commands
char reboot_cmd0[20] = "1"; // indicates size of this command branch
char reboot_cmd1[20] = "R,1\r";

// expected return values
char reboot_exp0[20] = "1"; // indicates size of this expected values branch
char reboot_exp1[20] = "Rebooting\r\n%REBOOT%";
// read and writable data
char reboot_spec0[20] = "0"; // indicates size of this data branch
// sets values from BLE
char reboot_set0[20] = "0";

// combine into pointer array
char * reboot_cmd_ptr[5] = {reboot_cmd0,reboot_cmd1};
char * reboot_exp_ptr[5] = {reboot_exp0,reboot_exp1};
char * reboot_spec_ptr[5] = {reboot_spec0};
char * reboot_set_ptr[5] = {reboot_set0};

// combine into a pointer of a pointer array
char ** reboot_dptr[10] = {
    reboot_cmd_ptr,
    reboot_exp_ptr,
    reboot_spec_ptr,
    reboot_set_ptr
};
/*...............................................................................*/

// special command pointer tree for reading server address from bluetooth.
/*...............................................................................*/
// commands #0
char set_ser_address_cmd0[20] = "1"; // indicates size of this command branch
char set_ser_address_cmd1[20] = "SHR,0072\r";

// expected return values #1
char set_ser_address_exp0[20] = "1"; // indicates size of this expected values branch
char set_ser_address_exp1[20] = "N/A\r\n\r\nCMD> ";
// read and writable data #2
char set_ser_address_spec0[20] = "0"; // indicates size of this data branch
// sets values from BLE #3
char set_ser_address_set0[20] = "1"; // indicates we are updating the server address
char set_ser_address_set1[20] = ""; // indicates that default was changed if a one is written in.

// combine into pointer array
char * set_ser_address_cmd_ptr[5] = {set_ser_address_cmd0,set_ser_address_cmd1};
char * set_ser_address_exp_ptr[5] = {set_ser_address_exp0,set_ser_address_exp1};
char * set_ser_address_spec_ptr[5] = {set_ser_address_spec0};
char * set_ser_address_set_ptr[5] = {set_ser_address_set0, server_address, set_ser_address_set1};

// combine into a pointer of a pointer array
char ** set_ser_address_dptr[10] = {
    set_ser_address_cmd_ptr,
    set_ser_address_exp_ptr,
    set_ser_address_spec_ptr,
    set_ser_address_set_ptr
};
/*...............................................................................*/





// special command pointer tree for creating update service
/*...............................................................................*/
// commands
char set_update_ser_cmd0[20] = "2"; // indicates size of this command branch
char set_update_ser_cmd1[20] = "PS,";
char set_update_ser_cmd2[20] = "\r";
// expected return values
char set_update_ser_exp0[20] = "1"; // indicates size of this expected values branch
char set_update_ser_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char set_update_ser_spec0[20] = "1"; // indicates size of this data branch
// sets values from BLE
char set_update_ser_set0[20] = "0";

// combine into pointer array
char * set_update_ser_cmd_ptr[5] = {set_update_ser_cmd0,set_update_ser_cmd1, set_update_ser_cmd2};
char * set_update_ser_exp_ptr[5] = {set_update_ser_exp0,set_update_ser_exp1};
char * set_update_ser_spec_ptr[5] = {set_update_ser_spec0, UUID};
char * set_update_ser_set_ptr[5] = {set_update_ser_set0};

// combine into a pointer of a pointer array
char ** set_update_ser_dptr[10] = {
    set_update_ser_cmd_ptr,
    set_update_ser_exp_ptr,
    set_update_ser_spec_ptr,
    set_update_ser_set_ptr
};
/*...............................................................................*/

// special command pointer tree for creating server address characteristic
/*...............................................................................*/
// commands
char set_update_address_char_cmd0[20] = "4"; // indicates size of this command branch
char set_update_address_char_cmd1[20] = "PC,";
char set_update_address_char_cmd2[20] = ",";
char set_update_address_char_cmd3[20] = ",";
char set_update_address_char_cmd4[20] = "\r";
// expected return values
char set_update_address_char_exp0[20] = "1"; // indicates size of this expected values branch
char set_update_address_char_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char set_update_address_char_spec0[20] = "3"; // indicates size of this data branch
// sets values from BLE
char set_update_address_char_set0[20] = "0";

// combine into pointer array
char * set_update_address_char_cmd_ptr[5] = {set_update_address_char_cmd0,set_update_address_char_cmd1, set_update_address_char_cmd2,set_update_address_char_cmd3,set_update_address_char_cmd4};
char * set_update_address_char_exp_ptr[5] = {set_update_address_char_exp0,set_update_address_char_exp1};
char * set_update_address_char_spec_ptr[5] = {set_update_address_char_spec0, UUID_1, property_bitmap1, data_size};
char * set_update_address_char_set_ptr[5] = {set_update_address_char_set0};

// combine into a pointer of a pointer array
char ** set_update_address_char_dptr[10] = {
    set_update_address_char_cmd_ptr,
    set_update_address_char_exp_ptr,
    set_update_address_char_spec_ptr,
    set_update_address_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for creating server address type characteristic
/*...............................................................................*/
// commands
char set_update_address_type_char_cmd0[20] = "4"; // indicates size of this command branch
char set_update_address_type_char_cmd1[20] = "PC,";
char set_update_address_type_char_cmd2[20] = ",";
char set_update_address_type_char_cmd3[20] = ",";
char set_update_address_type_char_cmd4[20] = "\r";
// expected return values
char set_update_address_type_char_exp0[20] = "1"; // indicates size of this expected values branch
char set_update_address_type_char_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char set_update_address_type_char_spec0[20] = "3"; // indicates size of this data branch
// sets values from BLE
char set_update_address_type_char_set0[20] = "0";

// combine into pointer array
char * set_update_address_type_char_cmd_ptr[5] = {set_update_address_type_char_cmd0,set_update_address_type_char_cmd1, set_update_address_type_char_cmd2,set_update_address_type_char_cmd3,set_update_address_type_char_cmd4};
char * set_update_address_type_char_exp_ptr[5] = {set_update_address_type_char_exp0,set_update_address_type_char_exp1};
char * set_update_address_type_char_spec_ptr[5] = {set_update_address_type_char_spec0, UUID_2, property_bitmap2, data_size};
char * set_update_address_type_char_set_ptr[5] = {set_update_address_type_char_set0};

// combine into a pointer of a pointer array
char ** set_update_address_type_char_dptr[10] = {
    set_update_address_type_char_cmd_ptr,
    set_update_address_type_char_exp_ptr,
    set_update_address_type_char_spec_ptr,
    set_update_address_type_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for creating device name characteristic
/*...............................................................................*/
// commands
char create_dev_name_char_cmd0[20] = "4"; // indicates size of this command branch
char create_dev_name_char_cmd1[20] = "PC,";
char create_dev_name_char_cmd2[20] = ",";
char create_dev_name_char_cmd3[20] = ",";
char create_dev_name_char_cmd4[20] = "\r";
// expected return values
char create_dev_name_char_exp0[20] = "1"; // indicates size of this expected values branch
char create_dev_name_char_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char create_dev_name_char_spec0[20] = "3"; // indicates size of this data branch
// sets values from BLE
char create_dev_name_char_set0[20] = "0";

// combine into pointer array
char * create_dev_name_char_cmd_ptr[5] = {create_dev_name_char_cmd0,create_dev_name_char_cmd1, create_dev_name_char_cmd2,create_dev_name_char_cmd3,create_dev_name_char_cmd4};
char * create_dev_name_char_exp_ptr[5] = {create_dev_name_char_exp0,create_dev_name_char_exp1};
char * create_dev_name_char_spec_ptr[5] = {create_dev_name_char_spec0, UUID_3, property_bitmap3, data_size};
char * create_dev_name_char_set_ptr[5] = {create_dev_name_char_set0};

// combine into a pointer of a pointer array
char ** create_dev_name_char_dptr[10] = {
    create_dev_name_char_cmd_ptr,
    create_dev_name_char_exp_ptr,
    create_dev_name_char_spec_ptr,
    create_dev_name_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for a password characteristic
/*...............................................................................*/
// commands
char create_password_char_cmd0[20] = "4"; // indicates size of this command branch
char create_password_char_cmd1[20] = "PC,";
char create_password_char_cmd2[20] = ",";
char create_password_char_cmd3[20] = ",";
char create_password_char_cmd4[20] = "\r";
// expected return values
char create_password_char_exp0[20] = "1"; // indicates size of this expected values branch
char create_password_char_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char create_password_char_spec0[20] = "3"; // indicates size of this data branch
// sets values from BLE
char create_password_char_set0[20] = "0";

// combine into pointer array
char * create_password_char_cmd_ptr[5] = {create_password_char_cmd0,create_password_char_cmd1, create_password_char_cmd2,create_password_char_cmd3,create_password_char_cmd4};
char * create_password_char_exp_ptr[5] = {create_password_char_exp0,create_password_char_exp1};
char * create_password_char_spec_ptr[5] = {create_password_char_spec0, UUID_4, property_bitmap4, data_size};
char * create_password_char_set_ptr[5] = {create_password_char_set0};

// combine into a pointer of a pointer array
char ** create_password_char_dptr[10] = {
    create_password_char_cmd_ptr,
    create_password_char_exp_ptr,
    create_password_char_spec_ptr,
    create_password_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for a sample interval characteristic
/*...............................................................................*/
// commands
char create_smp_int_char_cmd0[20] = "4"; // indicates size of this command branch
char create_smp_int_char_cmd1[20] = "PC,";
char create_smp_int_char_cmd2[20] = ",";
char create_smp_int_char_cmd3[20] = ",";
char create_smp_int_char_cmd4[20] = "\r";
// expected return values
char create_smp_int_char_exp0[20] = "1"; // indicates size of this expected values branch
char create_smp_int_char_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char create_smp_int_char_spec0[20] = "3"; // indicates size of this data branch
// sets values from BLE
char create_smp_int_char_set0[20] = "0";

// combine into pointer array
char * create_smp_int_char_cmd_ptr[5] = {create_smp_int_char_cmd0,create_smp_int_char_cmd1, create_smp_int_char_cmd2,create_smp_int_char_cmd3,create_smp_int_char_cmd4};
char * create_smp_int_char_exp_ptr[5] = {create_smp_int_char_exp0,create_smp_int_char_exp1};
char * create_smp_int_char_spec_ptr[5] = {create_smp_int_char_spec0, UUID_5, property_bitmap5, data_size};
char * create_smp_int_char_set_ptr[5] = {create_smp_int_char_set0};

// combine into a pointer of a pointer array
char ** create_smp_int_char_dptr[10] = {
    create_smp_int_char_cmd_ptr,
    create_smp_int_char_exp_ptr,
    create_smp_int_char_spec_ptr,
    create_smp_int_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for a number of samples per interval characteristic
/*...............................................................................*/
// commands
char create_smp_per_int_char_cmd0[20] = "4"; // indicates size of this command branch
char create_smp_per_int_char_cmd1[20] = "PC,";
char create_smp_per_int_char_cmd2[20] = ",";
char create_smp_per_int_char_cmd3[20] = ",";
char create_smp_per_int_char_cmd4[20] = "\r";
// expected return values
char create_smp_per_int_char_exp0[20] = "1"; // indicates size of this expected values branch
char create_smp_per_int_char_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char create_smp_per_int_char_spec0[20] = "3"; // indicates size of this data branch
// sets values from BLE
char create_smp_per_int_char_set0[20] = "0";

// combine into pointer array
char * create_smp_per_int_char_cmd_ptr[5] = {create_smp_per_int_char_cmd0,create_smp_per_int_char_cmd1, create_smp_per_int_char_cmd2,create_smp_per_int_char_cmd3,create_smp_per_int_char_cmd4};
char * create_smp_per_int_char_exp_ptr[5] = {create_smp_per_int_char_exp0,create_smp_per_int_char_exp1};
char * create_smp_per_int_char_spec_ptr[5] = {create_smp_per_int_char_spec0, UUID_6, property_bitmap6, data_size};
char * create_smp_per_int_char_set_ptr[5] = {create_smp_per_int_char_set0};

// combine into a pointer of a pointer array
char ** create_smp_per_int_char_dptr[10] = {
    create_smp_per_int_char_cmd_ptr,
    create_smp_per_int_char_exp_ptr,
    create_smp_per_int_char_spec_ptr,
    create_smp_per_int_char_set_ptr
};
/*...............................................................................*/


// special command pointer tree for a update complete characteristic
/*...............................................................................*/
// commands
char create_updated_char_cmd0[20] = "4"; // indicates size of this command branch
char create_updated_char_cmd1[20] = "PC,";
char create_updated_char_cmd2[20] = ",";
char create_updated_char_cmd3[20] = ",";
char create_updated_char_cmd4[20] = "\r";
// expected return values
char create_updated_char_exp0[20] = "1"; // indicates size of this expected values branch
char create_updated_char_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char create_updated_char_spec0[20] = "3"; // indicates size of this data branch
// sets values from BLE
char create_updated_char_set0[20] = "0";

// combine into pointer array
char * create_updated_char_cmd_ptr[5] = {create_updated_char_cmd0,create_updated_char_cmd1, create_updated_char_cmd2,create_updated_char_cmd3,create_updated_char_cmd4};
char * create_updated_char_exp_ptr[5] = {create_updated_char_exp0,create_updated_char_exp1};
char * create_updated_char_spec_ptr[5] = {create_updated_char_spec0, UUID_7, property_bitmap7, data_size};
char * create_updated_char_set_ptr[5] = {create_updated_char_set0};

// combine into a pointer of a pointer array
char ** create_updated_char_dptr[10] = {
    create_updated_char_cmd_ptr,
    create_updated_char_exp_ptr,
    create_updated_char_spec_ptr,
    create_updated_char_set_ptr
};
/*...............................................................................*/





// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_server_address_cmd0[20] = "3"; // indicates size of this command branch
char write_server_address_cmd1[20] = "SHW,";
char write_server_address_cmd2[20] = ",";
char write_server_address_cmd3[20] = "\r";
// expected return values
char write_server_address_exp0[20] = "1"; // indicates size of this expected values branch
char write_server_address_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char write_server_address_spec0[20] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_server_address_set0[20] = "0";

// combine into pointer array
char * write_server_address_cmd_ptr[5] = {write_server_address_cmd0,write_server_address_cmd1, write_server_address_cmd2,write_server_address_cmd3};
char * write_server_address_exp_ptr[5] = {write_server_address_exp0,write_server_address_exp1};
char * write_server_address_spec_ptr[5] = {write_server_address_spec0, handle1, server_address};
char * write_server_address_set_ptr[5] = {write_server_address_set0};

// combine into a pointer of a pointer array
char ** write_server_address_dptr[10] = {
    write_server_address_cmd_ptr,
    write_server_address_exp_ptr,
    write_server_address_spec_ptr,
    write_server_address_set_ptr
};
/*...............................................................................*/


// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_server_address_type_cmd0[20] = "3"; // indicates size of this command branch
char write_server_address_type_cmd1[20] = "SHW,";
char write_server_address_type_cmd2[20] = ",";
char write_server_address_type_cmd3[20] = "\r";
// expected return values
char write_server_address_type_exp0[20] = "1"; // indicates size of this expected values branch
char write_server_address_type_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char write_server_address_type_spec0[20] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_server_address_type_set0[20] = "0";

// combine into pointer array
char * write_server_address_type_cmd_ptr[5] = {write_server_address_type_cmd0,write_server_address_type_cmd1, write_server_address_type_cmd2,write_server_address_type_cmd3};
char * write_server_address_type_exp_ptr[5] = {write_server_address_type_exp0,write_server_address_type_exp1};
char * write_server_address_type_spec_ptr[5] = {write_server_address_type_spec0, handle2, server_address_type};
char * write_server_address_type_set_ptr[5] = {write_server_address_set0};

// combine into a pointer of a pointer array
char ** write_server_address_type_dptr[10] = {
    write_server_address_type_cmd_ptr,
    write_server_address_type_exp_ptr,
    write_server_address_type_spec_ptr,
    write_server_address_type_set_ptr
};
/*...............................................................................*/

// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_device_name_cmd0[20] = "3"; // indicates size of this command branch
char write_device_name_cmd1[20] = "SHW,";
char write_device_name_cmd2[20] = ",";
char write_device_name_cmd3[20] = "\r";
// expected return values
char write_device_name_exp0[20] = "1"; // indicates size of this expected values branch
char write_device_name_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char write_device_name_spec0[20] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_device_name_set0[20] = "0";

// combine into pointer array
char * write_device_name_cmd_ptr[5] = {write_device_name_cmd0,write_device_name_cmd1, write_device_name_cmd2,write_device_name_cmd3};
char * write_device_name_exp_ptr[5] = {write_device_name_exp0,write_device_name_exp1};
char * write_device_name_spec_ptr[5] = {write_device_name_spec0, handle3, device_name};
char * write_device_name_set_ptr[5] = {write_device_name_set0};

// combine into a pointer of a pointer array
char ** write_device_name_dptr[10] = {
    write_device_name_cmd_ptr,
    write_device_name_exp_ptr,
    write_device_name_spec_ptr,
    write_device_name_set_ptr
};
/*...............................................................................*/

// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_password_cmd0[20] = "3"; // indicates size of this command branch
char write_password_cmd1[20] = "SHW,";
char write_password_cmd2[20] = ",";
char write_password_cmd3[20] = "\r";
// expected return values
char write_password_exp0[20] = "1"; // indicates size of this expected values branch
char write_password_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char write_password_spec0[20] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_password_set0[20] = "0";

// combine into pointer array
char * write_password_cmd_ptr[5] = {write_password_cmd0,write_password_cmd1, write_password_cmd2,write_password_cmd3};
char * write_password_exp_ptr[5] = {write_password_exp0,write_password_exp1};
char * write_password_spec_ptr[5] = {write_password_spec0, handle4, password};
char * write_password_set_ptr[5] = {write_password_set0};

// combine into a pointer of a pointer array
char ** write_password_dptr[10] = {
    write_password_cmd_ptr,
    write_password_exp_ptr,
    write_password_spec_ptr,
    write_password_set_ptr
};
/*...............................................................................*/


// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_sample_interval_cmd0[20] = "3"; // indicates size of this command branch
char write_sample_interval_cmd1[20] = "SHW,";
char write_sample_interval_cmd2[20] = ",";
char write_sample_interval_cmd3[20] = "\r";
// expected return values
char write_sample_interval_exp0[20] = "1"; // indicates size of this expected values branch
char write_sample_interval_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char write_sample_interval_spec0[20] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_sample_interval_set0[20] = "0";

// combine into pointer array
char * write_sample_interval_cmd_ptr[5] = {write_sample_interval_cmd0,write_sample_interval_cmd1, write_sample_interval_cmd2,write_sample_interval_cmd3};
char * write_sample_interval_exp_ptr[5] = {write_sample_interval_exp0,write_sample_interval_exp1};
char * write_sample_interval_spec_ptr[5] = {write_sample_interval_spec0, handle5, sample_interval};
char * write_sample_interval_set_ptr[5] = {write_sample_interval_set0};

// combine into a pointer of a pointer array
char ** write_sample_interval_dptr[10] = {
    write_sample_interval_cmd_ptr,
    write_sample_interval_exp_ptr,
    write_sample_interval_spec_ptr,
    write_sample_interval_set_ptr
};
/*...............................................................................*/




// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_number_of_samples_per_interval_cmd0[20] = "3"; // indicates size of this command branch
char write_number_of_samples_per_interval_cmd1[20] = "SHW,";
char write_number_of_samples_per_interval_cmd2[20] = ",";
char write_number_of_samples_per_interval_cmd3[20] = "\r";
// expected return values
char write_number_of_samples_per_interval_exp0[20] = "1"; // indicates size of this expected values branch
char write_number_of_samples_per_interval_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char write_number_of_samples_per_interval_spec0[20] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_number_of_samples_per_interval_set0[20] = "0";

// combine into pointer array
char * write_number_of_samples_per_interval_cmd_ptr[5] = {write_number_of_samples_per_interval_cmd0,write_number_of_samples_per_interval_cmd1, write_number_of_samples_per_interval_cmd2,write_number_of_samples_per_interval_cmd3};
char * write_number_of_samples_per_interval_exp_ptr[5] = {write_number_of_samples_per_interval_exp0,write_number_of_samples_per_interval_exp1};
char * write_number_of_samples_per_interval_spec_ptr[5] = {write_number_of_samples_per_interval_spec0, handle6, number_of_samples_per_interval};
char * write_number_of_samples_per_interval_set_ptr[5] = {write_number_of_samples_per_interval_set0};

// combine into a pointer of a pointer array
char ** write_number_of_samples_per_interval_dptr[10] = {
    write_number_of_samples_per_interval_cmd_ptr,
    write_number_of_samples_per_interval_exp_ptr,
    write_number_of_samples_per_interval_spec_ptr,
    write_number_of_samples_per_interval_set_ptr
};
/*...............................................................................*/


// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_update_cmd0[20] = "3"; // indicates size of this command branch
char write_update_cmd1[20] = "SHW,";
char write_update_cmd2[20] = ",";
char write_update_cmd3[20] = "\r";
// expected return values
char write_update_exp0[20] = "1"; // indicates size of this expected values branch
char write_update_exp1[20] = "AOK\r\nCMD> ";
// read and writable data
char write_update_spec0[20] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_update_set0[20] = "0";

// combine into pointer array
char * write_update_cmd_ptr[5] = {write_update_cmd0,write_update_cmd1, write_update_cmd2,write_update_cmd3};
char * write_update_exp_ptr[5] = {write_update_exp0,write_update_exp1};
char * write_update_spec_ptr[5] = {write_update_spec0, handle7, update};
char * write_update_set_ptr[5] = {write_update_set0};

// combine into a pointer of a pointer array
char ** write_update_dptr[10] = {
    write_update_cmd_ptr,
    write_update_exp_ptr,
    write_update_spec_ptr,
    write_update_set_ptr
};
/*...............................................................................*/


char initialize_sequence_size[10] = "10"; // stores how many commands are in init sequence
char * initialize_sequence_size_ptr[10] = {initialize_sequence_size};
char ** initialize_sequence_size_dptr[10] = {initialize_sequence_size_ptr};
char *** initialize_sequence[20] = {
    initialize_sequence_size_dptr,
    clear_ser_char_dptr,
    set_name_dptr, // #1
    set_update_ser_dptr, // #2
    set_update_address_char_dptr, // #3
    set_update_address_type_char_dptr, // #4
    create_dev_name_char_dptr, // # 5
    create_password_char_dptr, // # 6
    create_smp_int_char_dptr, // # 7
    create_smp_per_int_char_dptr, // # 8
    create_updated_char_dptr, // # 9
};



char reboot_sequence_size[10] = "1"; // stores how many commands are in init sequence
char * reboot_sequence_size_ptr[10] = {reboot_sequence_size};
char ** reboot_sequence_size_dptr[10] = {reboot_sequence_size_ptr};
char *** reboot_sequence[20] = {
    reboot_sequence_size_dptr,
    reboot_dptr // reboot
};


char write_default_values_sequence_size[10] = "7"; // stores how many commands are in init sequence
char * write_default_values_sequence_size_ptr[10] = {write_default_values_sequence_size};
char ** write_default_values_sequence_size_dptr[10] = {write_default_values_sequence_size_ptr};
char *** write_default_values_sequence[20] = {
    write_default_values_sequence_size_dptr,
    write_server_address_dptr,
    write_server_address_type_dptr,
    write_device_name_dptr,
    write_password_dptr,
    write_sample_interval_dptr,
    write_number_of_samples_per_interval_dptr,
    write_update_dptr
};

char advertise_sequence_size[10] = "2"; // stores how many commands are in init sequence
char * advertise_sequence_size_ptr[10] = {advertise_sequence_size};
char ** advertise_sequence_size_dptr[10] = {advertise_sequence_size_ptr};
char *** advertise_sequence[20] = {
    advertise_sequence_size_dptr,
    list_ser_char_dptr,
    start_AD_dptr
};






char **** master_command[10] = {
    initialize_sequence,
    reboot_sequence,
    write_default_values_sequence,
    advertise_sequence
};
