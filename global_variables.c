//
//  global_variables.c
//  BLE_Power_Monitor
//
//  Created by Luke Neumann on 1/25/20.
//  Copyright © 2020 Luke Neumann. All rights reserved.
//

#include "global_variables.h"

char hamp0[4] = "0\r\n";
char hamp1[4] = "1\r\n";
char hamp2[4] = "2\r\n";
char hamp3[4] = "3\r\n";
char hamp4[4] = "4\r\n";
char hamp5[4] = "5\r\n";
char hamp6[4] = "6\r\n";
char hamp7[4] = "7\r\n";
char hamp8[4] = "8\r\n";
char hamp9[4] = "9\r\n";

uint32_t overFlowCount = 0;
uint16_t overFlowCount1 = 0;
uint32_t timeIntervalCount = 0;
uint32_t sampleCount = 0;

char debug_data[100];
//char debug_data[][100];
bool debug_test_print = false;
uint32_t debug_commandStates_counter = 0;


char received[100] = "";
char UUID[33] = "2D8E217F7D1B4C5A8A970D122F6DCD8B"; // random service identifier no dashes
char UUID_1[33] = "ED220715B3BD49558B0D8D6A794D876A"; // random service identifier for server BLE address
char UUID_2[33] = "6BB6DDA52DD24512B666BD5416882F68"; // random service identifier for server BLE type
char UUID_3[33] = "CE90B8CE148D4BF8A2BB0DB2BF2A7EA9"; // random service identifier for device name
char UUID_4[33] = "D64B24D5DD29443CAAADA1BB390B7BA6"; // random service identifier for password
char UUID_5[33] = "D64B24D5DD29443CAAADA1BB390B7BA7"; // random service identifier for sample interval
char UUID_6[33] = "D64B24D5DD29443CAAADA1BB390B7BA8"; // random service identifier for number of samples per interval
char UUID_7[33] = "D64B24D5DD29443CAAADA1BB390B7BA9"; // random service identifier for updated_status

char UUID_8[33] = "8b9b4c051b874f23be0ffe6162881a35"; // Data Service identifier
char UUID_9[33] = "7bf3638be4ac498d97daf8802ea3c201"; // Battery voltage identifier
char UUID_10[33] = "8ead23b48f014137aabc7dc3f826543e"; // Battery voltage identifier




char property_bitmap1[3] = "1E"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap2[3] = "1E"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap3[3] = "1E"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap4[3] = "1E"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap5[3] = "1E"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap6[3] = "1E"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap7[3] = "1E"; //The second parameter is a 8-bit property bitmap of the characteristic

char property_bitmap9[3] = "1E"; //The second parameter is a 8-bit property bitmap of the characteristic
char property_bitmap10[3] = "1E"; //The second parameter is a 8-bit property bitmap of the characteristic


char handle1[5] = "0072";
char handle2[5] = "0075";
char handle3[5] = "0078";
char handle4[5] = "007B";
char handle5[5] = "007E";
char handle6[5] = "0081";
char handle7[5] = "0084";


char handle9[5] = "0092";
char handle10[5] = "0095";

char data_size[3] = "F0"; //The third parameter is an 8-bit value that indicates the maximum data size in octet
                         //where the value of the characteristic is held.


//char server_address_type[5] = "0"; // not phone
//char server_address[20] = "801F12B4BDCE";
char device_name[15] = "Alpha 5";
char device_address[13] = "801F12B4BDBF";
char server_address[13] = "75B9550FC5CE"; // my phone
char server_address_type[1] = "1"; // phone
char password[15] = "0000";
char sample_interval[15] = "60"; // default to 60 seconds
char number_of_samples_per_interval[15] = "12"; // default to 12 samples
char update[1] = "0"; // this is initially zero meaning no update has been made yet.

char battery_voltage[17] = "0000";
char current[17] = "0000";

//char device_name_temp[15] = "Alpha 5";
//char device_address_temp[50] = "801F12B4BDBF";
//char server_address_temp[50] = "75B9550FC5CE"; // my phone
//char server_address_type_temp[5] = "1"; // phone
//char password_temp[30] = "0000";
//char sample_interval_temp[20] = "60"; // default to 60 seconds
//char number_of_samples_per_interval_temp[20] = "12"; // default to 12 samples
//char update_temp[10] = "0"; // this is initially zero meaning no update has been made yet.


char device_name_hex[30] = "";
char device_address_hex[26] ="";
char server_address_hex[26] = ""; // my phone
char server_address_type_hex[2] = ""; // phone
char password_hex[30] = "";
char sample_interval_hex[30] = ""; // default to 60 seconds
char number_of_samples_per_interval_hex[30] = ""; // default to 12 samples
char update_hex[2] = ""; // this is initially zero meaning no update has been made yet.

char battery_voltage_hex[34] = "";
char current_hex[34] = "";


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
int global_command_sequence_limit = 3;

int global_initialize_sequence_flag = 0;
int global_reboot_sequence_flag=0;
int global_write_default_values_sequence_flag=0;
int global_advertise_sequence_flag=0;

int global_send_data_state=0;

int global_send_data_to_BLE = 0;


//bool global_command_count_status = true;

char * commandPtr[8] = {
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
char start_AD_cmd0[2] = "1"; // indicates size of this command branch
char start_AD_cmd1[10] = "A,0014\r";
// expected return values
char start_AD_exp0[2] = "1"; // indicates size of this expected values branch
char start_AD_exp1[12] = "AOK\r\nCMD> ";
// read and writable data
char start_AD_spec0[2] = "0"; // indicates size of this data branch
// sets values from BLE
char start_AD_set0[2] = "0";

// combine into pointer array
char * start_AD_cmd_ptr[2] = {start_AD_cmd0,start_AD_cmd1};
char * start_AD_exp_ptr[2] = {start_AD_exp0,start_AD_exp1};
char * start_AD_spec_ptr[1] = {start_AD_spec0};
char * start_AD_set_ptr[1] = {start_AD_set0};
// combine into a pointer of a pointer array
char ** start_AD_dptr[4] = {
    start_AD_cmd_ptr,
    start_AD_exp_ptr,
    start_AD_spec_ptr,
    start_AD_set_ptr
};
/*...............................................................................*/


// special command pointer tree for setting device name
/*...............................................................................*/
// commands
char set_name_cmd0[1] = "2"; // indicates size of this command branch
char set_name_cmd1[4] = "SN,";
char set_name_cmd2[2] = "\r";
// expected return values
char set_name_exp0[1] = "1"; // indicates size of this expected values branch
char set_name_exp1[11] = "AOK\r\nCMD> ";
// read and writable data
char set_name_spec0[1] = "1"; // indicates size of this data branch
// sets values from BLE
char set_name_set0[1] = "0";

// combine into pointer array
char * set_name_cmd_ptr[3] = {set_name_cmd0,set_name_cmd1, set_name_cmd2};
char * set_name_exp_ptr[2] = {set_name_exp0,set_name_exp1};
char * set_name_spec_ptr[2] = {set_name_spec0, device_name};
char * set_name_set_ptr[1] = {set_name_set0};

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
char set_default_cmd0[2] = "1"; // indicates size of this command branch
char set_default_cmd1[8] = "SS,C0\r";

// expected return values
char set_default_exp0[2] = "1"; // indicates size of this expected values branch
char set_default_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char set_default_spec0[2] = "0"; // indicates size of this data branch
// sets values from BLE
char set_default_set0[2] = "0";

// combine into pointer array
char * set_default_cmd_ptr[2] = {set_default_cmd0,set_default_cmd1};
char * set_default_exp_ptr[2] = {set_default_exp0,set_default_exp1};
char * set_default_spec_ptr[1] = {set_default_spec0};
char * set_default_set_ptr[1] = {set_default_set0};

// combine into a pointer of a pointer array
char ** set_default_dptr[4] = {
    set_default_cmd_ptr,
    set_default_exp_ptr,
    set_default_spec_ptr,
    set_default_set_ptr
};
/*...............................................................................*/

// special command pointer tree for clearing and services and characteristics
/*...............................................................................*/
// commands
char clear_ser_char_cmd0[2] = "1"; // indicates size of this command branch
char clear_ser_char_cmd1[5] = "PZ\r";

// expected return values
char clear_ser_char_exp0[2] = "1"; // indicates size of this expected values branch
char clear_ser_char_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char clear_ser_char_spec0[2] = "0"; // indicates size of this data branch
// sets values from BLE
char clear_ser_char_set0[2] = "0";

// combine into pointer array
char * clear_ser_char_cmd_ptr[2] = {clear_ser_char_cmd0,clear_ser_char_cmd1};
char * clear_ser_char_exp_ptr[2] = {clear_ser_char_exp0,clear_ser_char_exp1};
char * clear_ser_char_spec_ptr[1] = {clear_ser_char_spec0};
char * clear_ser_char_set_ptr[1] = {clear_ser_char_set0};

// combine into a pointer of a pointer array
char ** clear_ser_char_dptr[4] = {
    clear_ser_char_cmd_ptr,
    clear_ser_char_exp_ptr,
    clear_ser_char_spec_ptr,
    clear_ser_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for listing services and characteristics
/*...............................................................................*/
// commands
char list_ser_char_cmd0[2] = "1"; // indicates size of this command branch
char list_ser_char_cmd1[4] = "LS\r";

// expected return values
char list_ser_char_exp0[2] = "1"; // indicates size of this expected values branch
// read and writable data
char list_ser_char_spec0[2] = "0"; // indicates size of this data branch
// sets values from BLE
char list_ser_char_set0[2] = "0";

// combine into pointer array
char * list_ser_char_cmd_ptr[2] = {list_ser_char_cmd0,list_ser_char_cmd1};
char * list_ser_char_exp_ptr[2] = {list_ser_char_exp0,UUID};
char * list_ser_char_spec_ptr[1] = {list_ser_char_spec0};
char * list_ser_char_set_ptr[1] = {list_ser_char_set0};

// combine into a pointer of a pointer array
char ** list_ser_char_dptr[4] = {
    list_ser_char_cmd_ptr,
    list_ser_char_exp_ptr,
    list_ser_char_spec_ptr,
    list_ser_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for rebooting the module
/*...............................................................................*/
// commands
char reboot_cmd0[2] = "1"; // indicates size of this command branch
char reboot_cmd1[5] = "R,1\r";

// expected return values
char reboot_exp0[2] = "1"; // indicates size of this expected values branch
char reboot_exp1[20] = "Rebooting\r\n%REBOOT%";
// read and writable data
char reboot_spec0[2] = "0"; // indicates size of this data branch
// sets values from BLE
char reboot_set0[2] = "0";

// combine into pointer array
char * reboot_cmd_ptr[2] = {reboot_cmd0,reboot_cmd1};
char * reboot_exp_ptr[2] = {reboot_exp0,reboot_exp1};
char * reboot_spec_ptr[1] = {reboot_spec0};
char * reboot_set_ptr[1] = {reboot_set0};

// combine into a pointer of a pointer array
char ** reboot_dptr[4] = {
    reboot_cmd_ptr,
    reboot_exp_ptr,
    reboot_spec_ptr,
    reboot_set_ptr
};
/*...............................................................................*/







// special command pointer tree for creating update service
/*...............................................................................*/
// commands
char set_update_ser_cmd0[2] = "2"; // indicates size of this command branch
char set_update_ser_cmd1[4] = "PS,";
char set_update_ser_cmd2[3] = "\r";
// expected return values
char set_update_ser_exp0[2] = "1"; // indicates size of this expected values branch
char set_update_ser_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char set_update_ser_spec0[2] = "1"; // indicates size of this data branch
// sets values from BLE
char set_update_ser_set0[2] = "0";

// combine into pointer array
char * set_update_ser_cmd_ptr[3] = {set_update_ser_cmd0,set_update_ser_cmd1, set_update_ser_cmd2};
char * set_update_ser_exp_ptr[2] = {set_update_ser_exp0,set_update_ser_exp1};
char * set_update_ser_spec_ptr[2] = {set_update_ser_spec0, UUID};
char * set_update_ser_set_ptr[1] = {set_update_ser_set0};

// combine into a pointer of a pointer array
char ** set_update_ser_dptr[4] = {
    set_update_ser_cmd_ptr,
    set_update_ser_exp_ptr,
    set_update_ser_spec_ptr,
    set_update_ser_set_ptr
};
/*...............................................................................*/

// special command pointer tree for creating server address characteristic
/*...............................................................................*/
// commands
char set_update_address_char_cmd0[2] = "4"; // indicates size of this command branch
char set_update_address_char_cmd1[4] = "PC,";
char set_update_address_char_cmd2[2] = ",";
char set_update_address_char_cmd3[2] = ",";
char set_update_address_char_cmd4[3] = "\r";
// expected return values
char set_update_address_char_exp0[2] = "1"; // indicates size of this expected values branch
char set_update_address_char_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char set_update_address_char_spec0[2] = "3"; // indicates size of this data branch
// sets values from BLE
char set_update_address_char_set0[2] = "0";

// combine into pointer array
char * set_update_address_char_cmd_ptr[5] = {set_update_address_char_cmd0,set_update_address_char_cmd1, set_update_address_char_cmd2,set_update_address_char_cmd3,set_update_address_char_cmd4};
char * set_update_address_char_exp_ptr[2] = {set_update_address_char_exp0,set_update_address_char_exp1};
char * set_update_address_char_spec_ptr[4] = {set_update_address_char_spec0, UUID_1, property_bitmap1, data_size};
char * set_update_address_char_set_ptr[1] = {set_update_address_char_set0};

// combine into a pointer of a pointer array
char ** set_update_address_char_dptr[4] = {
    set_update_address_char_cmd_ptr,
    set_update_address_char_exp_ptr,
    set_update_address_char_spec_ptr,
    set_update_address_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for creating server address type characteristic
/*...............................................................................*/
// commands
char set_update_address_type_char_cmd0[2] = "4"; // indicates size of this command branch
char set_update_address_type_char_cmd1[4] = "PC,";
char set_update_address_type_char_cmd2[2] = ",";
char set_update_address_type_char_cmd3[2] = ",";
char set_update_address_type_char_cmd4[3] = "\r";
// expected return values
char set_update_address_type_char_exp0[2] = "1"; // indicates size of this expected values branch
char set_update_address_type_char_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char set_update_address_type_char_spec0[2] = "3"; // indicates size of this data branch
// sets values from BLE
char set_update_address_type_char_set0[2] = "0";

// combine into pointer array
char * set_update_address_type_char_cmd_ptr[5] = {set_update_address_type_char_cmd0,set_update_address_type_char_cmd1, set_update_address_type_char_cmd2,set_update_address_type_char_cmd3,set_update_address_type_char_cmd4};
char * set_update_address_type_char_exp_ptr[2] = {set_update_address_type_char_exp0,set_update_address_type_char_exp1};
char * set_update_address_type_char_spec_ptr[4] = {set_update_address_type_char_spec0, UUID_2, property_bitmap2, data_size};
char * set_update_address_type_char_set_ptr[1] = {set_update_address_type_char_set0};

// combine into a pointer of a pointer array
char ** set_update_address_type_char_dptr[4] = {
    set_update_address_type_char_cmd_ptr,
    set_update_address_type_char_exp_ptr,
    set_update_address_type_char_spec_ptr,
    set_update_address_type_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for creating device name characteristic
/*...............................................................................*/
// commands
char create_dev_name_char_cmd0[2] = "4"; // indicates size of this command branch
char create_dev_name_char_cmd1[4] = "PC,";
char create_dev_name_char_cmd2[2] = ",";
char create_dev_name_char_cmd3[2] = ",";
char create_dev_name_char_cmd4[3] = "\r";
// expected return values
char create_dev_name_char_exp0[2] = "1"; // indicates size of this expected values branch
char create_dev_name_char_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char create_dev_name_char_spec0[2] = "3"; // indicates size of this data branch
// sets values from BLE
char create_dev_name_char_set0[2] = "0";

// combine into pointer array
char * create_dev_name_char_cmd_ptr[5] = {create_dev_name_char_cmd0,create_dev_name_char_cmd1, create_dev_name_char_cmd2,create_dev_name_char_cmd3,create_dev_name_char_cmd4};
char * create_dev_name_char_exp_ptr[2] = {create_dev_name_char_exp0,create_dev_name_char_exp1};
char * create_dev_name_char_spec_ptr[4] = {create_dev_name_char_spec0, UUID_3, property_bitmap3, data_size};
char * create_dev_name_char_set_ptr[1] = {create_dev_name_char_set0};

// combine into a pointer of a pointer array
char ** create_dev_name_char_dptr[4] = {
    create_dev_name_char_cmd_ptr,
    create_dev_name_char_exp_ptr,
    create_dev_name_char_spec_ptr,
    create_dev_name_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for a password characteristic
/*...............................................................................*/
// commands
char create_password_char_cmd0[2] = "4"; // indicates size of this command branch
char create_password_char_cmd1[4] = "PC,";
char create_password_char_cmd2[2] = ",";
char create_password_char_cmd3[2] = ",";
char create_password_char_cmd4[3] = "\r";
// expected return values
char create_password_char_exp0[2] = "1"; // indicates size of this expected values branch
char create_password_char_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char create_password_char_spec0[2] = "3"; // indicates size of this data branch
// sets values from BLE
char create_password_char_set0[2] = "0";

// combine into pointer array
char * create_password_char_cmd_ptr[5] = {create_password_char_cmd0,create_password_char_cmd1, create_password_char_cmd2,create_password_char_cmd3,create_password_char_cmd4};
char * create_password_char_exp_ptr[2] = {create_password_char_exp0,create_password_char_exp1};
char * create_password_char_spec_ptr[4] = {create_password_char_spec0, UUID_4, property_bitmap4, data_size};
char * create_password_char_set_ptr[1] = {create_password_char_set0};

// combine into a pointer of a pointer array
char ** create_password_char_dptr[4] = {
    create_password_char_cmd_ptr,
    create_password_char_exp_ptr,
    create_password_char_spec_ptr,
    create_password_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for a sample interval characteristic
/*...............................................................................*/
// commands
char create_smp_int_char_cmd0[2] = "4"; // indicates size of this command branch
char create_smp_int_char_cmd1[4] = "PC,";
char create_smp_int_char_cmd2[2] = ",";
char create_smp_int_char_cmd3[2] = ",";
char create_smp_int_char_cmd4[3] = "\r";
// expected return values
char create_smp_int_char_exp0[2] = "1"; // indicates size of this expected values branch
char create_smp_int_char_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char create_smp_int_char_spec0[2] = "3"; // indicates size of this data branch
// sets values from BLE
char create_smp_int_char_set0[2] = "0";

// combine into pointer array
char * create_smp_int_char_cmd_ptr[5] = {create_smp_int_char_cmd0,create_smp_int_char_cmd1, create_smp_int_char_cmd2,create_smp_int_char_cmd3,create_smp_int_char_cmd4};
char * create_smp_int_char_exp_ptr[2] = {create_smp_int_char_exp0,create_smp_int_char_exp1};
char * create_smp_int_char_spec_ptr[4] = {create_smp_int_char_spec0, UUID_5, property_bitmap5, data_size};
char * create_smp_int_char_set_ptr[1] = {create_smp_int_char_set0};

// combine into a pointer of a pointer array
char ** create_smp_int_char_dptr[4] = {
    create_smp_int_char_cmd_ptr,
    create_smp_int_char_exp_ptr,
    create_smp_int_char_spec_ptr,
    create_smp_int_char_set_ptr
};
/*...............................................................................*/

// special command pointer tree for a number of samples per interval characteristic
/*...............................................................................*/
// commands
char create_smp_per_int_char_cmd0[2] = "4"; // indicates size of this command branch
char create_smp_per_int_char_cmd1[4] = "PC,";
char create_smp_per_int_char_cmd2[2] = ",";
char create_smp_per_int_char_cmd3[2] = ",";
char create_smp_per_int_char_cmd4[3] = "\r";
// expected return values
char create_smp_per_int_char_exp0[2] = "1"; // indicates size of this expected values branch
char create_smp_per_int_char_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char create_smp_per_int_char_spec0[2] = "3"; // indicates size of this data branch
// sets values from BLE
char create_smp_per_int_char_set0[2] = "0";

// combine into pointer array
char * create_smp_per_int_char_cmd_ptr[5] = {create_smp_per_int_char_cmd0,create_smp_per_int_char_cmd1, create_smp_per_int_char_cmd2,create_smp_per_int_char_cmd3,create_smp_per_int_char_cmd4};
char * create_smp_per_int_char_exp_ptr[2] = {create_smp_per_int_char_exp0,create_smp_per_int_char_exp1};
char * create_smp_per_int_char_spec_ptr[4] = {create_smp_per_int_char_spec0, UUID_6, property_bitmap6, data_size};
char * create_smp_per_int_char_set_ptr[1] = {create_smp_per_int_char_set0};

// combine into a pointer of a pointer array
char ** create_smp_per_int_char_dptr[4] = {
    create_smp_per_int_char_cmd_ptr,
    create_smp_per_int_char_exp_ptr,
    create_smp_per_int_char_spec_ptr,
    create_smp_per_int_char_set_ptr
};
/*...............................................................................*/


// special command pointer tree for a update complete characteristic
/*...............................................................................*/
// commands
char create_updated_char_cmd0[2] = "4"; // indicates size of this command branch
char create_updated_char_cmd1[4] = "PC,";
char create_updated_char_cmd2[2] = ",";
char create_updated_char_cmd3[2] = ",";
char create_updated_char_cmd4[3] = "\r";
// expected return values
char create_updated_char_exp0[2] = "1"; // indicates size of this expected values branch
char create_updated_char_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char create_updated_char_spec0[2] = "3"; // indicates size of this data branch
// sets values from BLE
char create_updated_char_set0[2] = "0";

// combine into pointer array
char * create_updated_char_cmd_ptr[5] = {create_updated_char_cmd0,create_updated_char_cmd1, create_updated_char_cmd2,create_updated_char_cmd3,create_updated_char_cmd4};
char * create_updated_char_exp_ptr[2] = {create_updated_char_exp0,create_updated_char_exp1};
char * create_updated_char_spec_ptr[4] = {create_updated_char_spec0, UUID_7, property_bitmap7, data_size};
char * create_updated_char_set_ptr[1] = {create_updated_char_set0};

// combine into a pointer of a pointer array
char ** create_updated_char_dptr[4] = {
    create_updated_char_cmd_ptr,
    create_updated_char_exp_ptr,
    create_updated_char_spec_ptr,
    create_updated_char_set_ptr
};
/*...............................................................................*/





















// special command pointer tree for creating update service
/*...............................................................................*/
// commands
char set_data_ser_cmd0[2] = "2"; // indicates size of this command branch
char set_data_ser_cmd1[4] = "PS,";
char set_data_ser_cmd2[3] = "\r";
// expected return values
char set_data_ser_exp0[2] = "1"; // indicates size of this expected values branch
char set_data_ser_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char set_data_ser_spec0[2] = "1"; // indicates size of this data branch
// sets values from BLE
char set_data_ser_set0[2] = "0";

// combine into pointer array
char * set_data_ser_cmd_ptr[3] = {set_data_ser_cmd0,set_data_ser_cmd1, set_data_ser_cmd2};
char * set_data_ser_exp_ptr[2] = {set_data_ser_exp0,set_data_ser_exp1};
char * set_data_ser_spec_ptr[2] = {set_data_ser_spec0, UUID_8};
char * set_data_ser_set_ptr[1] = {set_data_ser_set0};

// combine into a pointer of a pointer array
char ** set_data_ser_dptr[4] = {
    set_data_ser_cmd_ptr,
    set_data_ser_exp_ptr,
    set_data_ser_spec_ptr,
    set_data_ser_set_ptr
};

// special command pointer tree for a battery voltage characteristic
/*...............................................................................*/
// commands
char create_battery_voltage_char_cmd0[2] = "4"; // indicates size of this command branch
char create_battery_voltage_char_cmd1[4] = "PC,";
char create_battery_voltage_char_cmd2[2] = ",";
char create_battery_voltage_char_cmd3[2] = ",";
char create_battery_voltage_char_cmd4[3] = "\r";
// expected return values
char create_battery_voltage_char_exp0[2] = "1"; // indicates size of this expected values branch
char create_battery_voltage_char_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char create_battery_voltage_char_spec0[2] = "3"; // indicates size of this data branch
// sets values from BLE
char create_battery_voltage_char_set0[2] = "0";

// combine into pointer array
char * create_battery_voltage_char_cmd_ptr[5] = {create_battery_voltage_char_cmd0,create_battery_voltage_char_cmd1, create_battery_voltage_char_cmd2,create_battery_voltage_char_cmd3,create_battery_voltage_char_cmd4};
char * create_battery_voltage_char_exp_ptr[2] = {create_battery_voltage_char_exp0,create_battery_voltage_char_exp1};
char * create_battery_voltage_char_spec_ptr[4] = {create_battery_voltage_char_spec0, UUID_9, property_bitmap9, data_size};
char * create_battery_voltage_char_set_ptr[1] = {create_battery_voltage_char_set0};

// combine into a pointer of a pointer array
char ** create_battery_voltage_char_dptr[4] = {
    create_battery_voltage_char_cmd_ptr,
    create_battery_voltage_char_exp_ptr,
    create_battery_voltage_char_spec_ptr,
    create_battery_voltage_char_set_ptr
};

// special command pointer tree for a current characteristic
/*...............................................................................*/
// commands
char create_current_char_cmd0[2] = "4"; // indicates size of this command branch
char create_current_char_cmd1[4] = "PC,";
char create_current_char_cmd2[2] = ",";
char create_current_char_cmd3[2] = ",";
char create_current_char_cmd4[3] = "\r";
// expected return values
char create_current_char_exp0[2] = "1"; // indicates size of this expected values branch
char create_current_char_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char create_current_char_spec0[2] = "3"; // indicates size of this data branch
// sets values from BLE
char create_current_char_set0[2] = "0";

// combine into pointer array
char * create_current_char_cmd_ptr[5] = {create_current_char_cmd0,create_current_char_cmd1, create_current_char_cmd2,create_current_char_cmd3,create_current_char_cmd4};
char * create_current_char_exp_ptr[2] = {create_current_char_exp0,create_current_char_exp1};
char * create_current_char_spec_ptr[4] = {create_current_char_spec0, UUID_10, property_bitmap10, data_size};
char * create_current_char_set_ptr[1] = {create_current_char_set0};

// combine into a pointer of a pointer array
char ** create_current_char_dptr[4] = {
    create_current_char_cmd_ptr,
    create_current_char_exp_ptr,
    create_current_char_spec_ptr,
    create_current_char_set_ptr
};


// special command pointer tree for writing battery voltage value into BLE module
/*...............................................................................*/
// commands
char write_battery_voltage_cmd0[2] = "3"; // indicates size of this command branch
char write_battery_voltage_cmd1[5] = "SHW,";
char write_battery_voltage_cmd2[2] = ",";
char write_battery_voltage_cmd3[3] = "\r";
// expected return values
char write_battery_voltage_exp0[2] = "1"; // indicates size of this expected values branch
char write_battery_voltage_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char write_battery_voltage_spec0[2] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_battery_voltage_set0[2] = "0";

// combine into pointer array
char * write_battery_voltage_cmd_ptr[4] = {write_battery_voltage_cmd0,write_battery_voltage_cmd1, write_battery_voltage_cmd2,write_battery_voltage_cmd3};
char * write_battery_voltage_exp_ptr[2] = {write_battery_voltage_exp0,write_battery_voltage_exp1};
char * write_battery_voltage_spec_ptr[4] = {write_battery_voltage_spec0, handle9, battery_voltage_hex,battery_voltage};
char * write_battery_voltage_set_ptr[1] = {write_battery_voltage_set0};

// combine into a pointer of a pointer array
char ** write_battery_voltage_dptr[4] = {
    write_battery_voltage_cmd_ptr,
    write_battery_voltage_exp_ptr,
    write_battery_voltage_spec_ptr,
    write_battery_voltage_set_ptr
};


// special command pointer tree for writing electric current value into BLE module
/*...............................................................................*/
// commands
char write_current_cmd0[2] = "3"; // indicates size of this command branch
char write_current_cmd1[5] = "SHW,";
char write_current_cmd2[2] = ",";
char write_current_cmd3[3] = "\r";
// expected return values
char write_current_exp0[2] = "1"; // indicates size of this expected values branch
char write_current_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char write_current_spec0[2] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_current_set0[2] = "0";

// combine into pointer array
char * write_current_cmd_ptr[4] = {write_current_cmd0,write_current_cmd1, write_current_cmd2,write_current_cmd3};
char * write_current_exp_ptr[2] = {write_current_exp0,write_current_exp1};
char * write_current_spec_ptr[4] = {write_current_spec0, handle10, current_hex,current};
char * write_current_set_ptr[1] = {write_current_set0};

// combine into a pointer of a pointer array
char ** write_current_dptr[4] = {
    write_current_cmd_ptr,
    write_current_exp_ptr,
    write_current_spec_ptr,
    write_current_set_ptr
};







// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_server_address_cmd0[2] = "3"; // indicates size of this command branch
char write_server_address_cmd1[5] = "SHW,";
char write_server_address_cmd2[2] = ",";
char write_server_address_cmd3[3] = "\r";
// expected return values
char write_server_address_exp0[2] = "1"; // indicates size of this expected values branch
char write_server_address_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char write_server_address_spec0[2] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_server_address_set0[2] = "0";

// combine into pointer array
char * write_server_address_cmd_ptr[4] = {write_server_address_cmd0,write_server_address_cmd1, write_server_address_cmd2,write_server_address_cmd3};
char * write_server_address_exp_ptr[2] = {write_server_address_exp0,write_server_address_exp1};
char * write_server_address_spec_ptr[4] = {write_server_address_spec0, handle1, server_address_hex,server_address};
char * write_server_address_set_ptr[1] = {write_server_address_set0};

// combine into a pointer of a pointer array
char ** write_server_address_dptr[4] = {
    write_server_address_cmd_ptr,
    write_server_address_exp_ptr,
    write_server_address_spec_ptr,
    write_server_address_set_ptr
};
/*...............................................................................*/


// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_server_address_type_cmd0[2] = "3"; // indicates size of this command branch
char write_server_address_type_cmd1[5] = "SHW,";
char write_server_address_type_cmd2[2] = ",";
char write_server_address_type_cmd3[3] = "\r";
// expected return values
char write_server_address_type_exp0[2] = "1"; // indicates size of this expected values branch
char write_server_address_type_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char write_server_address_type_spec0[2] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_server_address_type_set0[2] = "0";

// combine into pointer array
char * write_server_address_type_cmd_ptr[4] = {write_server_address_type_cmd0,write_server_address_type_cmd1, write_server_address_type_cmd2,write_server_address_type_cmd3};
char * write_server_address_type_exp_ptr[2] = {write_server_address_type_exp0,write_server_address_type_exp1};
char * write_server_address_type_spec_ptr[4] = {write_server_address_type_spec0, handle2, server_address_type_hex,server_address_type};
char * write_server_address_type_set_ptr[1] = {write_server_address_set0};

// combine into a pointer of a pointer array
char ** write_server_address_type_dptr[4] = {
    write_server_address_type_cmd_ptr,
    write_server_address_type_exp_ptr,
    write_server_address_type_spec_ptr,
    write_server_address_type_set_ptr
};
/*...............................................................................*/

// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_device_name_cmd0[2] = "3"; // indicates size of this command branch
char write_device_name_cmd1[5] = "SHW,";
char write_device_name_cmd2[2] = ",";
char write_device_name_cmd3[3] = "\r";
// expected return values
char write_device_name_exp0[2] = "1"; // indicates size of this expected values branch
char write_device_name_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char write_device_name_spec0[2] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_device_name_set0[2] = "0";

// combine into pointer array
char * write_device_name_cmd_ptr[4] = {write_device_name_cmd0,write_device_name_cmd1, write_device_name_cmd2,write_device_name_cmd3};
char * write_device_name_exp_ptr[2] = {write_device_name_exp0,write_device_name_exp1};
char * write_device_name_spec_ptr[4] = {write_device_name_spec0, handle3, device_name_hex,device_name};
char * write_device_name_set_ptr[1] = {write_device_name_set0};

// combine into a pointer of a pointer array
char ** write_device_name_dptr[4] = {
    write_device_name_cmd_ptr,
    write_device_name_exp_ptr,
    write_device_name_spec_ptr,
    write_device_name_set_ptr
};
/*...............................................................................*/

// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_password_cmd0[2] = "3"; // indicates size of this command branch
char write_password_cmd1[5] = "SHW,";
char write_password_cmd2[2] = ",";
char write_password_cmd3[3] = "\r";
// expected return values
char write_password_exp0[2] = "1"; // indicates size of this expected values branch
char write_password_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char write_password_spec0[2] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_password_set0[2] = "0";

// combine into pointer array
char * write_password_cmd_ptr[4] = {write_password_cmd0,write_password_cmd1, write_password_cmd2,write_password_cmd3};
char * write_password_exp_ptr[2] = {write_password_exp0,write_password_exp1};
char * write_password_spec_ptr[4] = {write_password_spec0, handle4, password_hex,password};
char * write_password_set_ptr[1] = {write_password_set0};

// combine into a pointer of a pointer array
char ** write_password_dptr[4] = {
    write_password_cmd_ptr,
    write_password_exp_ptr,
    write_password_spec_ptr,
    write_password_set_ptr
};
/*...............................................................................*/


// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_sample_interval_cmd0[2] = "3"; // indicates size of this command branch
char write_sample_interval_cmd1[5] = "SHW,";
char write_sample_interval_cmd2[2] = ",";
char write_sample_interval_cmd3[3] = "\r";
// expected return values
char write_sample_interval_exp0[2] = "1"; // indicates size of this expected values branch
char write_sample_interval_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char write_sample_interval_spec0[2] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_sample_interval_set0[2] = "0";

// combine into pointer array
char * write_sample_interval_cmd_ptr[4] = {write_sample_interval_cmd0,write_sample_interval_cmd1, write_sample_interval_cmd2,write_sample_interval_cmd3};
char * write_sample_interval_exp_ptr[2] = {write_sample_interval_exp0,write_sample_interval_exp1};
char * write_sample_interval_spec_ptr[4] = {write_sample_interval_spec0, handle5, sample_interval_hex, sample_interval};
char * write_sample_interval_set_ptr[1] = {write_sample_interval_set0};

// combine into a pointer of a pointer array
char ** write_sample_interval_dptr[4] = {
    write_sample_interval_cmd_ptr,
    write_sample_interval_exp_ptr,
    write_sample_interval_spec_ptr,
    write_sample_interval_set_ptr
};
/*...............................................................................*/




// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_number_of_samples_per_interval_cmd0[2] = "3"; // indicates size of this command branch
char write_number_of_samples_per_interval_cmd1[5] = "SHW,";
char write_number_of_samples_per_interval_cmd2[2] = ",";
char write_number_of_samples_per_interval_cmd3[3] = "\r";
// expected return values
char write_number_of_samples_per_interval_exp0[2] = "1"; // indicates size of this expected values branch
char write_number_of_samples_per_interval_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char write_number_of_samples_per_interval_spec0[2] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_number_of_samples_per_interval_set0[2] = "0";

// combine into pointer array
char * write_number_of_samples_per_interval_cmd_ptr[4] = {write_number_of_samples_per_interval_cmd0,write_number_of_samples_per_interval_cmd1, write_number_of_samples_per_interval_cmd2,write_number_of_samples_per_interval_cmd3};
char * write_number_of_samples_per_interval_exp_ptr[2] = {write_number_of_samples_per_interval_exp0,write_number_of_samples_per_interval_exp1};
char * write_number_of_samples_per_interval_spec_ptr[4] = {write_number_of_samples_per_interval_spec0, handle6, number_of_samples_per_interval_hex,number_of_samples_per_interval};
char * write_number_of_samples_per_interval_set_ptr[1] = {write_number_of_samples_per_interval_set0};

// combine into a pointer of a pointer array
char ** write_number_of_samples_per_interval_dptr[4] = {
    write_number_of_samples_per_interval_cmd_ptr,
    write_number_of_samples_per_interval_exp_ptr,
    write_number_of_samples_per_interval_spec_ptr,
    write_number_of_samples_per_interval_set_ptr
};
/*...............................................................................*/


// special command pointer tree for writing default server address value into BLE module
/*...............................................................................*/
// commands
char write_update_cmd0[2] = "3"; // indicates size of this command branch
char write_update_cmd1[5] = "SHW,";
char write_update_cmd2[2] = ",";
char write_update_cmd3[3] = "\r";
// expected return values
char write_update_exp0[2] = "1"; // indicates size of this expected values branch
char write_update_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char write_update_spec0[2] = "2"; // indicates size of this data branch
// when this is high it means to set values from BLE module into the microcontroller
char write_update_set0[2] = "0";

// combine into pointer array
char * write_update_cmd_ptr[4] = {write_update_cmd0,write_update_cmd1, write_update_cmd2,write_update_cmd3};
char * write_update_exp_ptr[2] = {write_update_exp0,write_update_exp1};
char * write_update_spec_ptr[4] = {write_update_spec0, handle7, update_hex, update};
char * write_update_set_ptr[1] = {write_update_set0};

// combine into a pointer of a pointer array
char ** write_update_dptr[4] = {
    write_update_cmd_ptr,
    write_update_exp_ptr,
    write_update_spec_ptr,
    write_update_set_ptr
};
/*...............................................................................*/




// special command pointer tree - stops advertising
/*...............................................................................*/
// commands
char stop_AD_cmd0[2] = "1"; // indicates size of this command branch
char stop_AD_cmd1[4] = "Y\r";
// expected return values
char stop_AD_exp0[2] = "1"; // indicates size of this expected values branch
char stop_AD_exp1[13] = "AOK\r\nCMD> ";
// read and writable data
char stop_AD_spec0[2] = "0"; // indicates size of this data branch
// sets values from BLE
char stop_AD_set0[2] = "0";

// combine into pointer array
char * stop_AD_cmd_ptr[2] = {stop_AD_cmd0,stop_AD_cmd1};
char * stop_AD_exp_ptr[2] = {stop_AD_exp0,stop_AD_exp1};
char * stop_AD_spec_ptr[1] = {stop_AD_spec0};
char * stop_AD_set_ptr[1] = {stop_AD_set0};
// combine into a pointer of a pointer array
char ** stop_AD_dptr[4] = {
    stop_AD_cmd_ptr,
    stop_AD_exp_ptr,
    stop_AD_spec_ptr,
    stop_AD_set_ptr
};
/*...............................................................................*/




// special command pointer tree for reading server address from bluetooth.
/*...............................................................................*/
// commands #0
char set_ser_address_cmd0[2] = "2"; // indicates size of this command branch
char set_ser_address_cmd1[5] = "SHR,";
char set_ser_address_cmd2[3] = "\r";
// expected return values #1
char set_ser_address_exp0[2] = "1"; // indicates size of this expected values branch
char set_ser_address_exp1[17] = "N/A\r\n\r\nCMD> ";
// read and writable data #2
char set_ser_address_spec0[2] = "1"; // indicates size of this data branch
// sets values from BLE #3
char set_ser_address_set0[2] = "1"; // indicates we are updating the server address
char set_ser_address_set1[2] = ""; // indicates that default was changed if a one is written in.
char set_ser_address_set2[2] = "0"; // used as a boolean to indicate that data has changed.

// combine into pointer array
char * set_ser_address_cmd_ptr[2] = {set_ser_address_cmd0,set_ser_address_cmd1};
char * set_ser_address_exp_ptr[2] = {set_ser_address_exp0,set_ser_address_exp1};
char * set_ser_address_spec_ptr[2] = {set_ser_address_spec0, handle1};
char * set_ser_address_set_ptr[4] = {set_ser_address_set0, server_address, set_ser_address_set1, set_ser_address_set2};

// combine into a pointer of a pointer array
char ** set_ser_address_dptr[4] = {
    set_ser_address_cmd_ptr,
    set_ser_address_exp_ptr,
    set_ser_address_spec_ptr,
    set_ser_address_set_ptr
};
/*...............................................................................*/



// special command pointer tree for reading server address type from bluetooth.
/*...............................................................................*/
// commands #0
char set_ser_address_type_cmd0[2] = "2"; // indicates size of this command branch
char set_ser_address_type_cmd1[5] = "SHR,";
char set_ser_address_type_cmd2[3] = "\r";
// expected return values #1
char set_ser_address_type_exp0[2] = "1"; // indicates size of this expected values branch
char set_ser_address_type_exp1[17] = "N/A\r\n\r\nCMD> ";
// read and writable data #2
char set_ser_address_type_spec0[2] = "1"; // indicates size of this data branch
// sets values from BLE #3
char set_ser_address_type_set0[2] = "1"; // indicates we are updating the server address
char set_ser_address_type_set1[2] = ""; // indicates that default was changed if a one is written in.
char set_ser_address_type_set2[2] = "0"; // used as a boolean to indicate that data has changed.

// combine into pointer array
char * set_ser_address_type_cmd_ptr[2] = {set_ser_address_type_cmd0,set_ser_address_type_cmd1};
char * set_ser_address_type_exp_ptr[2] = {set_ser_address_type_exp0,set_ser_address_type_exp1};
char * set_ser_address_type_spec_ptr[2] = {set_ser_address_type_spec0, handle2};
char * set_ser_address_type_set_ptr[4] = {set_ser_address_type_set0, server_address_type, set_ser_address_type_set1, set_ser_address_type_set2};

// combine into a pointer of a pointer array
char ** set_ser_address_type_dptr[4] = {
    set_ser_address_type_cmd_ptr,
    set_ser_address_type_exp_ptr,
    set_ser_address_type_spec_ptr,
    set_ser_address_type_set_ptr
};
/*...............................................................................*/

// special command pointer tree for reading server address type from bluetooth.
/*...............................................................................*/
// commands #0
char set_device_name_cmd0[2] = "2"; // indicates size of this command branch
char set_device_name_cmd1[5] = "SHR,";
char set_device_name_cmd2[3] = "\r";
// expected return values #1
char set_device_name_exp0[2] = "1"; // indicates size of this expected values branch
char set_device_name_exp1[17] = "N/A\r\n\r\nCMD> ";
// read and writable data #2
char set_device_name_spec0[2] = "1"; // indicates size of this data branch
// sets values from BLE #3
char set_device_name_set0[2] = "1"; // indicates we are updating the server address
char set_device_name_set1[2] = ""; // indicates that default was changed if a one is written in.
char set_device_name_set2[2] = "0"; // used as a boolean to indicate that data has changed.

// combine into pointer array
char * set_device_name_cmd_ptr[2] = {set_device_name_cmd0,set_device_name_cmd1};
char * set_device_name_exp_ptr[2] = {set_device_name_exp0,set_device_name_exp1};
char * set_device_name_spec_ptr[2] = {set_device_name_spec0, handle3};
char * set_device_name_set_ptr[4] = {set_device_name_set0, device_name, set_device_name_set1, set_device_name_set2};

// combine into a pointer of a pointer array
char ** set_device_name_dptr[4] = {
    set_device_name_cmd_ptr,
    set_device_name_exp_ptr,
    set_device_name_spec_ptr,
    set_device_name_set_ptr
};
/*...............................................................................*/




// special command pointer tree for reading server address type from bluetooth.
/*...............................................................................*/
// commands #0
char set_password_cmd0[2] = "2"; // indicates size of this command branch
char set_password_cmd1[5] = "SHR,";
char set_password_cmd2[3] = "\r";
// expected return values #1
char set_password_exp0[2] = "1"; // indicates size of this expected values branch
char set_password_exp1[17] = "N/A\r\n\r\nCMD> ";
// read and writable data #2
char set_password_spec0[2] = "1"; // indicates size of this data branch
// sets values from BLE #3
char set_password_set0[2] = "1"; // indicates we are updating the server address
char set_password_set1[2] = ""; // indicates that default was changed if a one is written in.
char set_password_set2[2] = "0"; // used as a boolean to indicate that data has changed.

// combine into pointer array
char * set_password_cmd_ptr[2] = {set_password_cmd0,set_password_cmd1};
char * set_password_exp_ptr[2] = {set_password_exp0,set_password_exp1};
char * set_password_spec_ptr[2] = {set_password_spec0, handle4};
char * set_password_set_ptr[4] = {set_password_set0, password, set_password_set1, set_password_set2};

// combine into a pointer of a pointer array
char ** set_password_dptr[4] = {
    set_password_cmd_ptr,
    set_password_exp_ptr,
    set_password_spec_ptr,
    set_password_set_ptr
};
/*...............................................................................*/


// special command pointer tree for reading server address type from bluetooth.
/*...............................................................................*/
// commands #0
char set_sample_interval_cmd0[2] = "2"; // indicates size of this command branch
char set_sample_interval_cmd1[5] = "SHR,";
char set_sample_interval_cmd2[3] = "\r";
// expected return values #1
char set_sample_interval_exp0[2] = "1"; // indicates size of this expected values branch
char set_sample_interval_exp1[17] = "N/A\r\n\r\nCMD> ";
// read and writable data #2
char set_sample_interval_spec0[2] = "1"; // indicates size of this data branch
// sets values from BLE #3
char set_sample_interval_set0[2] = "1"; // indicates we are updating the server address
char set_sample_interval_set1[2] = ""; // indicates that default was changed if a one is written in.
char set_sample_interval_set2[2] = "0"; // used as a boolean to indicate that data has changed.

// combine into pointer array
char * set_sample_interval_cmd_ptr[2] = {set_sample_interval_cmd0,set_sample_interval_cmd1};
char * set_sample_interval_exp_ptr[2] = {set_sample_interval_exp0,set_sample_interval_exp1};
char * set_sample_interval_spec_ptr[2] = {set_sample_interval_spec0, handle5};
char * set_sample_interval_set_ptr[4] = {set_sample_interval_set0, sample_interval, set_sample_interval_set1, set_sample_interval_set2};

// combine into a pointer of a pointer array
char ** set_sample_interval_dptr[4] = {
    set_sample_interval_cmd_ptr,
    set_sample_interval_exp_ptr,
    set_sample_interval_spec_ptr,
    set_sample_interval_set_ptr
};
/*...............................................................................*/


// special command pointer tree for reading server address type from bluetooth.
/*...............................................................................*/
// commands #0
char set_number_of_samples_per_interval_cmd0[2] = "2"; // indicates size of this command branch
char set_number_of_samples_per_interval_cmd1[5] = "SHR,";
char set_number_of_samples_per_interval_cmd2[3] = "\r";
// expected return values #1
char set_number_of_samples_per_interval_exp0[2] = "1"; // indicates size of this expected values branch
char set_number_of_samples_per_interval_exp1[17] = "N/A\r\n\r\nCMD> ";
// read and writable data #2
char set_number_of_samples_per_interval_spec0[2] = "1"; // indicates size of this data branch
// sets values from BLE #3
char set_number_of_samples_per_interval_set0[2] = "1"; // indicates we are updating the server address
char set_number_of_samples_per_interval_set1[2] = ""; // indicates that default was changed if a one is written in.
char set_number_of_samples_per_interval_set2[2] = "0"; // used as a boolean to indicate that data has changed.

// combine into pointer array
char * set_number_of_samples_per_interval_cmd_ptr[2] = {set_number_of_samples_per_interval_cmd0,set_number_of_samples_per_interval_cmd1};
char * set_number_of_samples_per_interval_exp_ptr[2] = {set_number_of_samples_per_interval_exp0,set_number_of_samples_per_interval_exp1};
char * set_number_of_samples_per_interval_spec_ptr[2] = {set_number_of_samples_per_interval_spec0, handle6};
char * set_number_of_samples_per_interval_set_ptr[4] = {set_number_of_samples_per_interval_set0, number_of_samples_per_interval, set_number_of_samples_per_interval_set1, set_number_of_samples_per_interval_set2};

// combine into a pointer of a pointer array
char ** set_number_of_samples_per_interval_dptr[4] = {
    set_number_of_samples_per_interval_cmd_ptr,
    set_number_of_samples_per_interval_exp_ptr,
    set_number_of_samples_per_interval_spec_ptr,
    set_number_of_samples_per_interval_set_ptr
};
/*...............................................................................*/


// special command pointer tree for getting the update status from the ble device
/*...............................................................................*/
// commands #0
char check_update_status_cmd0[2] = "2"; // indicates size of this command branch
char check_update_status_cmd1[5] = "SHR,";
char check_update_status_cmd2[3] = "\r";
// expected return values #1
char check_update_status_exp0[2] = "1"; // indicates size of this expected values branch
char check_update_status_exp1[17] = "N/A\r\n\r\nCMD> ";
// read and writable data #2
char check_update_status_spec0[2] = "1"; // indicates size of this data branch
// sets values from BLE #3
char check_update_status_set0[2] = "1"; // indicates we are updating the server address
char check_update_status_set1[2] = ""; // serves as a temporary variable to hold the ble data for comparison.
char check_update_status_set2[2] = "0"; // used as a boolean to indicate that data has changed.

// combine into pointer array
char * check_update_status_cmd_ptr[2] = {check_update_status_cmd0,check_update_status_cmd1};
char * check_update_status_exp_ptr[2] = {check_update_status_exp0,check_update_status_exp1};
char * check_update_status_spec_ptr[2] = {check_update_status_spec0, handle7};
char * check_update_status_set_ptr[4] = {check_update_status_set0, update, check_update_status_set1,check_update_status_set2};

// combine into a pointer of a pointer array
char ** check_update_status_dptr[4] = {
    check_update_status_cmd_ptr,
    check_update_status_exp_ptr,
    check_update_status_spec_ptr,
    check_update_status_set_ptr
};
/*...............................................................................*/

/*...............................................................................*/
// commands
char disconnect_cmd0[2] = "1"; // indicates size of this command branch
char disconnect_cmd1[6] = "K,1\r";
// expected return values
char disconnect_exp0[2] = "0"; // indicates size of this expected values branch
//char disconnect_exp1[25] = "AOK\r\nCMD> %DISCONNECT%";
// read and writable data
char disconnect_spec0[2] = "0"; // indicates size of this data branch
// sets values from BLE
char disconnect_set0[2] = "0";

// combine into pointer array
char * disconnect_cmd_ptr[2] = {disconnect_cmd0,disconnect_cmd1};
char * disconnect_exp_ptr[2] = {disconnect_exp0};
char * disconnect_spec_ptr[1] = {disconnect_spec0};
char * disconnect_set_ptr[1] = {disconnect_set0};
// combine into a pointer of a pointer array
char ** disconnect_dptr[4] = {
    disconnect_cmd_ptr,
    disconnect_exp_ptr,
    disconnect_spec_ptr,
    disconnect_set_ptr
};
/*...............................................................................*/


/*...............................................................................*/
// commands
char connect_cmd0[2] = "3"; // indicates size of this command branch
char connect_cmd1[3] = "C,";
char connect_cmd2[2] = ",";
char connect_cmd3[3] = "\r";

// expected return values
char connect_exp0[2] = "0"; // indicates size of this expected values branch
//char connect_exp1[25] = "Trying\r\n%CONNECT,";
//char connect_exp2[25] = ",";
//char connect_exp3[25] = "%%";


// read and writable data
char connect_spec0[2] = "2"; // indicates size of this data branch
// sets values from BLE
char connect_set0[2] = "0";

// combine into pointer array
char * connect_cmd_ptr[2] = {connect_cmd0,connect_cmd1};
char * connect_exp_ptr[2] = {connect_exp0};
char * connect_spec_ptr[3] = {connect_spec0,server_address_type,server_address};
char * connect_set_ptr[1] = {connect_set0};
// combine into a pointer of a pointer array
char ** connect_dptr[4] = {
    connect_cmd_ptr,
    connect_exp_ptr,
    connect_spec_ptr,
    connect_set_ptr
};
/*...............................................................................*/


char initialize_sequence_size[3] = "13"; // stores how many commands are in init sequence
char * initialize_sequence_size_ptr[1] = {initialize_sequence_size};
char ** initialize_sequence_size_dptr[1] = {initialize_sequence_size_ptr};
char *** initialize_sequence[15] = {
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
    set_data_ser_dptr,
    create_battery_voltage_char_dptr,
    create_current_char_dptr
    
};



char reboot_sequence_size[2] = "1"; // stores how many commands are in init sequence
char * reboot_sequence_size_ptr[1] = {reboot_sequence_size};
char ** reboot_sequence_size_dptr[1] = {reboot_sequence_size_ptr};
char *** reboot_sequence[2] = {
    reboot_sequence_size_dptr,
    reboot_dptr // reboot
};


char write_default_values_sequence_size[2] = "8"; // stores how many commands are in init sequence
char * write_default_values_sequence_size_ptr[1] = {write_default_values_sequence_size};
char ** write_default_values_sequence_size_dptr[1] = {write_default_values_sequence_size_ptr};
char *** write_default_values_sequence[10] = {
    write_default_values_sequence_size_dptr,
    list_ser_char_dptr,
    write_server_address_dptr,
    write_server_address_type_dptr,
    write_device_name_dptr,
    write_password_dptr,
    write_sample_interval_dptr,
    write_number_of_samples_per_interval_dptr,
    write_update_dptr
};

char advertise_sequence_size[2] = "1"; // stores how many commands are in init sequence
char * advertise_sequence_size_ptr[1] = {advertise_sequence_size};
char ** advertise_sequence_size_dptr[1] = {advertise_sequence_size_ptr};
char *** advertise_sequence[2] = {
    advertise_sequence_size_dptr,
    start_AD_dptr
};

char stop_advertise_sequence_size[2] = "1"; // stores how many commands are in init sequence
char * stop_advertise_sequence_size_ptr[1] = {stop_advertise_sequence_size};
char ** stop_advertise_sequence_size_dptr[1] = {stop_advertise_sequence_size_ptr};
char *** stop_advertise_sequence[2] = {
    stop_advertise_sequence_size_dptr,
    stop_AD_dptr
};

char check_update_status_sequence_size[2] = "1"; // stores how many commands are in init sequence
char * check_update_status_sequence_size_ptr[1] = {check_update_status_sequence_size};
char ** check_update_status_sequence_size_dptr[1] = {check_update_status_sequence_size_ptr};
char *** check_update_status_sequence[2] = {
    check_update_status_sequence_size_dptr,
    check_update_status_dptr
};


char write_updated_ble_values_sequence_size[2] = "6"; // stores how many commands are in init sequence
char * write_updated_ble_values_sequence_size_ptr[1] = {write_updated_ble_values_sequence_size};
char ** write_updated_ble_values_sequence_size_dptr[1] = {write_updated_ble_values_sequence_size_ptr};
char *** write_updated_ble_values_sequence[8] = {
    write_updated_ble_values_sequence_size_dptr,
    set_ser_address_dptr, // sets the new server address value
    set_ser_address_type_dptr,
    set_device_name_dptr,
    set_password_dptr,
    set_sample_interval_dptr,
    set_number_of_samples_per_interval_dptr
};


char disconnect_sequence_size[2] = "1"; // stores how many commands are in init sequence
char * disconnect_sequence_size_ptr[1] = {disconnect_sequence_size};
char ** disconnect_sequence_size_dptr[1] = {disconnect_sequence_size_ptr};
char *** disconnect_sequence[2] = {
    disconnect_sequence_size_dptr,
    disconnect_dptr
};

char connect_sequence_size[2] = "1"; // stores how many commands are in init sequence
char * connect_sequence_size_ptr[1] = {connect_sequence_size};
char ** connect_sequence_size_dptr[1] = {connect_sequence_size_ptr};
char *** connect_sequence[2] = {
    connect_sequence_size_dptr,
    connect_dptr
};



char write_data_sequence_size[2] = "2"; // stores how many commands are in init sequence
char * write_data_sequence_size_ptr[1] = {write_data_sequence_size};
char ** write_data_sequence_size_dptr[1] = {write_data_sequence_size_ptr};
char *** write_data_sequence[3] = {
    write_data_sequence_size_dptr,
    write_current_dptr,
    write_battery_voltage_dptr
};






char **** master_command[10] = {
    initialize_sequence,
    reboot_sequence,
    write_default_values_sequence,
    advertise_sequence,
    stop_advertise_sequence,
    check_update_status_sequence,
    write_updated_ble_values_sequence,
    disconnect_sequence,
    connect_sequence,
    write_data_sequence
};
