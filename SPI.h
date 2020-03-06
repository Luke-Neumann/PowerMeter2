//
//  SPI.h
//  BLE_Power_Monitor
//
//  Created by Luke Neumann on 2/28/20.
//  Copyright © 2020 Luke Neumann. All rights reserved.
//

#ifndef SPI_h
#define SPI_h



#include <stdio.h>



void SPI_MasterInit();

void SPI_MasterTransmit(char * Data);

#endif /* SPI_h */
