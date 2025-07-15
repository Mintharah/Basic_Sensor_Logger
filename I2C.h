/* 
 * File:   I2C.h
 * Author: Eng.Yassmin
 *
 * Created on July 15, 2025, 1:16 PM
 */

#ifndef I2C_H
#define	I2C_H

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <util/twi.h>


#define DS1307_ADDRESS 0x68


void TWI_Init(void);
uint8_t TWI_Start(void);
void TWI_Stop(void);
uint8_t TWI_Write(uint8_t data);
uint8_t TWI_Read_ACK(void);
uint8_t TWI_Read_NACK(void);
void TWI_PinSetup(void);
uint8_t TWI_ReadRegister(uint8_t devAddr, uint8_t regAddr);
uint8_t BCD_to_Dec(uint8_t val);
uint8_t Dec_to_BCD(uint8_t val);
void DS1307_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
void read_time(uint8_t *h, uint8_t *m, uint8_t *s);
#endif	/* I2C_H */

