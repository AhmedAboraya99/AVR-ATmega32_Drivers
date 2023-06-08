# AVR Smart Home Project

## Introduction

This project is a smart home system that allows you to control the fan speed, light intensity, and door open/close using PWM. The system has two modes, automatic and manual. In the automatic mode, the system uses sensors to adjust the fan speed and light intensity based on the temperature and light levels respectively. In the manual mode, the user can control the fan speed and light intensity manually. 

The system also includes a Bluetooth module that allows users to access the system through a virtual terminal. The system has two modes of access, admin and normal user login, each mode requiring a password that is stored on the external EEPROM. 

## Modules Used

The following modules were used in this project:

- DIO (Digital Input/Output)
- EXTIm (External Interrupt)
- Timer0 (8-bit Timer/Counter)
- Timer1 (16-bit Timer/Counter)
- TWI (Two-Wire Interface)
- UART (Universal Asynchronous Receiver/Transmitter)

## Features

The AVR Smart Home Project includes the following features:

- Fan speed controller using PWM with automatic and manual modes
- Light intensity controller using PWM with automatic and manual modes
- Door open and close using motor controller
- Bluetooth module for virtual terminal access with admin and normal user login modes
- Password storage on external EEPROM
- LCD display to show system status

## Automatic Mode

In the automatic mode, the system uses a temperature sensor to adjust the fan speed based on the temperature of the room. The system adjusts the fan speed to maintain a constant temperature.

The system also uses an LDR (Light Dependent Resistor) sensor to adjust the light intensity based on the ambient light level. The system adjusts the light intensity to maintain a constant light level.

## Manual Mode

In the manual mode, the user can control the fan speed and light intensity manually using push buttons. The system includes two push buttons for fan speed control and two push buttons for light intensity control.

## Bluetooth Module

The Bluetooth module allows users to access the system through a virtual terminal. The system has two modes of access, admin and normal user login, each mode requiring a password that is stored on the external EEPROM.

Users can use the virtual terminal to adjust the fan speed, light intensity, and door open/close. The system also displays the current status of the system on the virtual terminal.

## LCD Display

The LCD display shows the current status of the system, including the temperature, light level, fan speed, and door status. The display also shows the current mode of the system, either automatic or manual.

## Conclusion

The AVR Smart Home Project is a versatile and efficient system that allows users to control the fan speed, light intensity, and door open/close using PWM. The system includes automatic and manual modes, as well as a Bluetooth module for virtual terminal access. The system also has an LCD display to show the current status of the system.
