/*
 * I2C_reg.h
 *
 *  Created on: Jun 8, 2019
 *      Author: salsa
 */

#ifndef I2C_REG_H_
#define I2C_REG_H_

#define TWDR *((volatile uint8 *)0x23) //I2C data register

#define TWAR *((volatile uint8 *)0x22)
#define TWGCE 0

#define TWSR *((volatile uint8 *)0x21)
#define TWS7 7
#define TWS6 6
#define TWS5 5
#define TWS4 4
#define TWS3 3
#define TWPS1 1
#define TWPS0 0

#define TWBR *((volatile uint8 *)0x20)

#define TWCR *((volatile uint8 *)0x56)
#define TWINT 7
#define TWEA 6
#define TWSTA 5
#define TWSTO 4
#define TWWC 3
#define TWEN 2
#define TWIE 0

#endif /* I2C_REG_H_ */
