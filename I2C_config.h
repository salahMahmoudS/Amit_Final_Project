/*
 * I2C_config.h
 *
 *  Created on: Jun 8, 2019
 *      Author: salsa
 */

#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

//in this MODE we choose the mode of the controller to be either a master or slave, you can choose between the following
/*
 * MASTER
 * SLAVE
 */
#define MODE MASTER

/*if SLAVE mode is selected, please give it an address*/

#define ADDRESS 0x01

//in this we can choose the pre scaler value of the controller, you can choose between the following
/*
 * PRE_SCALER_1
 * PRE_SCALER_4
 * PRE_SCALER_16
 * PRE_SCALER_64
 */
#define PRE_SCALER_VALUE PRE_SCALER_1
//here you can set the SCL frequency according to the following equation
// CPU_CLOCK/(16 + 2*(BIT_RATE)*(4^PRE_SCALER)
// you can choose any number between 0 and 256
#define BIT_RATE 0b01100010//0000110

#endif /* I2C_CONFIG_H_ */
