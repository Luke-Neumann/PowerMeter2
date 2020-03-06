//
//  SPI.c
//  BLE_Power_Monitor
//
//  Created by Luke Neumann on 2/28/20.
//  Copyright © 2020 Luke Neumann. All rights reserved.
//

#include "SPI.h"
#include <avr/io.h>

#define DD_MOSI     DDB2
#define DD_SCK      DDB1
#define DDR_SPI     DDRB

void SPI_MasterInit(){
    
    // set mosi and sck output, all others, input
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
    // Enable SPI, Master, set clock rate fck/16
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


void SPI_MasterTransmit(char * Data){
    
    // start transmission
    while(*Data != '\0'){ // loop till the null character is reached.
        SPDR = *Data;
        while(!(SPSR & (1<<SPIF)));
        Data++;
    }
    
    
}
