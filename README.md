# STM32 Lab Stands for Electrical Engineering

Firmware for five compact measurement stands built on the STM32 microcontroller. The stands replaced worn-out analog equipment for lab work in the Electrical Engineering course at Transbaikal State University (ZabGU), and students use them for measurements and lab reports.

> Student team project, March–May 2023: three students of group VMK-21 under the supervision of Associate Professor D. A. Deis. The project was described in a published article (in Russian). All code in this repository was written by me.

## Hardware

- **Microcontroller:** STM32 "Blue Pill" (STM32F103C8T6), reflashed with the community Arduino_STM32 bootloader so it can be programmed from the Arduino IDE
- **Displays:** 16×2 and 20×4 LCDs over I2C (two displays on one bus at different addresses) and a 4-digit 7-segment TM1637 module
- **Inputs:** potentiometers (analog inputs) and switches (digital inputs)

## The five stands

| Folder | Lab | Hardware |
| --- | --- | --- |
| `laba1` | Equivalent generator parameters | LCD 16×2, potentiometer, 2 switches |
| `laba2` | Series resonant circuit (voltage resonance) | LCD 20×4, TM1637, potentiometer, switch |
| `laba3` | Three-phase circuit, star connection | LCD 16×2 and 20×4, 5 switches, 3 potentiometers |
| `laba4` | Three-phase circuit, delta connection | LCD 16×2 and 20×4, 3 switches, 3 potentiometers |
| `laba5` | Parallel resonant circuit (current resonance) | LCD 20×4, TM1637, potentiometer, switch |

## Implementation notes

- The circuit formulas were provided by the supervisor; I implemented them in firmware, including a small complex-number class for the AC calculations in the three-phase stands.
- During testing we found that the I2C LCD library added enough delay to make the multiplexed 7-segment display flicker. We moved the digits to a dedicated TM1637 driver module, which fixed it.
- Prototypes were built and tested in the [Wokwi](https://wokwi.com/) simulator before assembling the hardware.

## Tech stack

C/C++ (Arduino framework) · STM32 · I2C · Wokwi · Git
