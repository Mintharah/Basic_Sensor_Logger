# Temperature Logger with RTC – ATmega328P

This project logs temperature readings using an **LM35 sensor** and timestamps them with a **DS1307 Real-Time Clock** (RTC), all handled by an **ATmega328P** microcontroller. Data is sent via **USART** and visualized in **Proteus**.

## Features
- Reads temperature using the ADC from an LM35 sensor
- Timestamps data using DS1307 via I2C
- Sends data over serial (USART) to a virtual terminal
- Compatible with Proteus simulation

## Tools & Components
- ATmega328P
- LM35 Temperature Sensor
- DS1307 RTC Module
- Proteus (for simulation)
- MPLAB X + MCC (for code generation)

## Output Format
HH:MM:SS Temperature
Example: 02:14:36 26°C


## How to Use
1. Flash the code to ATmega328P or run the project in Proteus.
2. Open a serial terminal at 9600 baud.
3. Observe real-time temperature readings with timestamps.

## License
This project is open source under the MIT License.
