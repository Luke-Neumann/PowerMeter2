//
//  isr.c
//  BLE_Power_Monitor
//
//  Created by Luke Neumann on 1/25/20.
//  Copyright © 2020 Luke Neumann. All rights reserved.
//

#include "isr.h"
#include <avr/io.h>
#include "iot_uart.h"


//ISR(INT5_vect) // this is for the external interrupt pin PE5s
//{
//    fast_mode(); // run a simple test function to read and print ADC data quickly
//}
//ISR(USART1_RX_vect)
//{
//    //uart_print_string("TRUE");
//    char temp[5] = "";
//    temp[0] = USART_Receive();
//    memcpy(received+strlen(received), temp, strlen(temp));
//}
//ISR(TIMER0_OVF_vect) // interrupt for timer 0
//{
//    ++overFlowCount; // increment value when the timer register overflows and is reset to zero.
//    //PINA = (PINA ^ 0xFF); // inverts the PA2 pin
//    //PORTA = PORTA ^ 0x04;
//    commandControl_tick();
//}
//ISR(TIMER1_OVF_vect) // interrupt for timer 1
//{
//    ++overFlowCount1; // increment value when the timer register overflows and is reset to zero.
//}
