/*
 * I2C_int.h
 *
 *  Created on: Jun 8, 2019
 *      Author: salsa
 */

#ifndef I2C_INT_H_
#define I2C_INT_H_

#define ENABLE_REPEATED_START  1
#define DISABLE_REPEATED_START 0

void I2C_voidInitialize(void);
uint8 I2C_uint8MasterTransmit(uint8 data,uint8 address,uint8 repeatedStart);
uint8 I2C_uint8MasterTransmit_RepeatedStart(uint8 data,uint8 address,uint8 repeatedStart);

uint8 I2C_uint8SlaveRecieve(void);
uint8 I2C_uint8SlaveTransmit(uint8 data);

#endif /* I2C_INT_H_ */
