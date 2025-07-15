/*
 * File:   I2C.c
 * Author: Eng.Yassmin
 *
 * Created on July 15, 2025, 1:16 PM
 */

#include "I2C.h"

void TWI_Init(void) {
    // Set SCL frequency
    TWSR = 0x00; // Prescaler = 1
    TWBR = ((F_CPU / 100000) - 16) / 2;

    // Enable TWI
    TWCR = (1 << TWEN);
}

uint8_t TWI_Start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // Send START
    while (!(TWCR & (1 << TWINT)));

    return (TWSR & 0xF8); // Return status
}

void TWI_Stop(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // Send STOP
}

uint8_t TWI_Write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN); // Clear interrupt, start transmission
    while (!(TWCR & (1 << TWINT)));

    return (TWSR & 0xF8); // Return status
}

uint8_t TWI_Read_ACK(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // ACK after receive
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

uint8_t TWI_Read_NACK(void) {
    TWCR = (1 << TWINT) | (1 << TWEN); // NACK after receive
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

void TWI_PinSetup(void) {
    DDRC &= ~((1 << PC4) | (1 << PC5)); // Set as input
    PORTC |= (1 << PC4) | (1 << PC5); // Enable internal pull-up (optional, external ones are better)
}

uint8_t TWI_ReadRegister(uint8_t devAddr, uint8_t regAddr) {
    uint8_t data;

    // Send START condition
    TWI_Start();

    // Send device address with write bit (0)
    TWI_Write(devAddr << 1 | 0); // Example: 0x68 << 1 | 0 = 0xD0

    // Send register address to read from
    TWI_Write(regAddr);

    // Send repeated START condition
    TWI_Start();

    // Send device address with read bit (1)
    TWI_Write(devAddr << 1 | 1); 

    // Read one byte and send NACK
    data = TWI_Read_NACK();

    // Send STOP condition
    TWI_Stop();

    return data;
}

uint8_t BCD_to_Dec(uint8_t val) {
    return ((val >> 4) * 10 + (val & 0x0F));
}

uint8_t Dec_to_BCD(uint8_t val) {
    return ((val / 10) << 4) | (val % 10);
}

void DS1307_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    TWI_Start();

    TWI_Write(0x68 << 1 | 0);  // DS1307 write address (0xD0)

    TWI_Write(0x00);  // Start at seconds register

    TWI_Write(Dec_to_BCD(seconds)); // Register 0x00
    TWI_Write(Dec_to_BCD(minutes)); // Register 0x01
    TWI_Write(Dec_to_BCD(hours));   // Register 0x02
    TWI_Stop();
}

void read_time(uint8_t *h, uint8_t *m, uint8_t *s) {

    *s = TWI_ReadRegister(0x68, 0x00);
    *m = TWI_ReadRegister(0x68, 0x01);
    *h = TWI_ReadRegister(0x68, 0x02);
}
