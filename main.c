#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <util/twi.h>
#include "I2C.h"

char buffer[16];
char time_str[16];
adc_result_t result = 0;
adc_result_t Temp_Cel = 0;



int main(void) {
    SYSTEM_Initialize();
    USART0_Initialize();
    TWI_Init();
    ADC_Initialize();
    ADC_Enable();

    DS1307_SetTime(6, 16, 0);

    uint8_t h = 0, m = 0, s = 0;

    while (1) {
        read_time(&h, &m, &s);
        result = ADC_GetConversion(0);
        Temp_Cel = result * 0.488;
        
        sprintf(time_str, "%02u:%02u:%02u ", h, m, s);
        sprintf(buffer, "%u\r\n", Temp_Cel);

        for (int i = 0; time_str[i] != '\0'; i++) USART0_Write(time_str[i]);
        for (int i = 0; buffer[i] != '\0'; i++) USART0_Write(buffer[i]);

        if (Temp_Cel > 26)
            IO_PB0_SetHigh();
        else
            IO_PB0_SetLow();

        _delay_ms(1000);
    }
}
