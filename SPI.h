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

#define DD_MOSI     DDB2
#define DD_SCK      DDB1

void SPI_MasterInit();

void SPI_MasterTransmit(char * Data);

#endif /* SPI_h */
