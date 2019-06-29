/*
 * I2C_prog.c
 *
 *  Created on: Jun 8, 2019
 *      Author: salsa
 */

#include "Std_Types.h"
#include "BitMath.h"
#include "I2C_reg.h"
#include "I2C_priv.h"
#include "I2C_config.h"
#include "I2C_int.h"
#include "DIO_int.h"

#define READ  		   1
#define WRITE 		   0
#define REPEATED_START 1

void I2C_voidInitialize(void){
	//Prescale
#if (PRE_SCALER_VALUE == PRE_SCALER_1)
	CLEAR_BIT(TWSR,TWPS0);
	CLEAR_BIT(TWSR,TWPS1);
#elif (PRE_SCALER_VALUE == PRE_SCALER_4)
	SET_BIT(TWSR,TWPS0);
	CLEAR_BIT(TWSR,TWPS1);
#elif (PRE_SCALER_VALUE == PRE_SCALER_16)
	CLEAR_BIT(TWSR,TWPS0);
	SET_BIT(TWSR,TWPS1);
#elif (PRE_SCALER_VALUE == PRE_SCALER_64)
	SET_BIT(TWSR,TWPS0);
	SET_BIT(TWSR,TWPS1);

#else
#error "Pre scaler value error"
#endif
#if MODE == SLAVE
	TWAR = (ADDRESS << 1);
#endif
	TWBR = BIT_RATE; //Baud Rate
	SET_BIT(TWCR,TWEN); //to enable I2C
	CLEAR_BIT(TWCR,TWIE); //to disable interrupt
}

static void I2C_voidTransmitAddress(uint8 address,uint8 RorW)
{
	if(RorW == WRITE){
		TWDR = (address << 1)|0x00; //Load the address and send W signal
	}else
	{
		TWDR = (address << 1)|0x01; //Load the address and send R signal
	}
	CLEAR_BIT(TWCR,TWSTA); //Disable Start Condition
	CLEAR_BIT(TWCR,TWSTO); //Disable Stop Condition "for safety"
	SET_BIT(TWCR,TWEN); //Make sure I2C is working
	SET_BIT(TWCR,TWINT); //Clear the Flag to start transmitting
	while(!GET_BIT(TWCR,TWINT)); //wait until transmitting it
}

static void I2C_voidTransmitData(uint8 data)
{
	TWDR = data;
	SET_BIT(TWCR,TWEN); //Make sure I2C is working
	SET_BIT(TWCR,TWINT); //Clear the Flag to start transmitting
	while(!GET_BIT(TWCR,TWINT));
}

static uint8 I2C_uint8ReceiveData()
{
	SET_BIT(TWCR,TWEN); //Make sure I2C is working
	CLEAR_BIT(TWCR,TWSTO);
	SET_BIT(TWCR,TWINT); //Clear the Flag to start transmitting
	while(!GET_BIT(TWCR,TWINT));
	return TWDR;
}

static void I2C_voidStartCondition(void)
{
	SET_BIT(TWCR,TWSTA); //Start Condition
	SET_BIT(TWCR,TWEN);  //Enable I2C
	SET_BIT(TWCR,TWINT); //Clear the Flag to start transmitting
	while(!GET_BIT(TWCR,TWINT));
}

static void I2C_voidStopCondition(void)
{
	SET_BIT(TWCR,TWSTO); //Enable Stop Condition
	SET_BIT(TWCR,TWEN);  //Enable I2C
	SET_BIT(TWCR,TWINT); //Clear the Flag to start transmitting Stop Condition
}

uint8 I2C_uint8MasterTransmit_RepeatedStart(uint8 data,uint8 address,uint8 repeatedStart)
{

	if(TWSR != 0x08 && TWSR != 0x10)
	{
		return 0;
	}
	I2C_voidTransmitAddress(address, WRITE); //Send the address+W
	if(TWSR == 20 || TWSR == 0x38)
	{
		I2C_voidStartCondition();
		return 0;
	}
	if(TWSR != 0x18)
	{
		return 0;
	}
	I2C_voidTransmitData(data); //Send the data
	if(TWSR == 0x30 || TWSR == 0x38)
	{
		I2C_voidStartCondition();
		return 0;
	}
	if(TWSR != 0x28)
	{
		DIO_voidSetPin(DIO_PIN_30, HIGH);
		return 0;
	}
	if(repeatedStart == ENABLE_REPEATED_START)
	{
		I2C_voidStartCondition(); //Repeated Start
	}else
	{
		I2C_voidStopCondition(); //Send stop condition
	}
	return 1;
}

uint8 I2C_uint8MasterTransmit(uint8 data,uint8 address,uint8 repeatedStart){
	I2C_voidStartCondition(); //Send start condition
	if(TWSR != 0x08)
	{
		return 0;
	}
	I2C_voidTransmitAddress(address, WRITE); //Send the address+W
	if(TWSR != 0x18)
	{
		return 0;
	}
	I2C_voidTransmitData(data); //Send the data
	if(TWSR != 0x28)
	{
		return 0;
	}
	if(repeatedStart == ENABLE_REPEATED_START)
	{
		I2C_voidStartCondition(); //Repeated Start
	}else
	{
		I2C_voidStopCondition(); //Send stop condition
	}
	return 1;
}

uint8 I2C_uint8SlaveRecieve(void){
	CLEAR_BIT(TWCR,TWSTO);
	CLEAR_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWEA);
	SET_BIT(TWCR,TWEN);
	SET_BIT(TWCR,TWINT);
	while(!GET_BIT(TWCR,TWINT));
	return I2C_uint8ReceiveData();
}


uint8 I2C_uint8SlaveTransmit(uint8 data)
{
	CLEAR_BIT(TWCR,TWSTO);
	CLEAR_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWEA);
	SET_BIT(TWCR,TWEN);
	SET_BIT(TWCR,TWINT);
	while(!GET_BIT(TWCR,TWINT));
	I2C_voidTransmitData(data);
	return 0;
}
