# MSP430 Watchdog Timer Project

This project implements an MSP430 microcontroller as a watchdog timer for another controller, such as an Arduino Uno. The code is primarily designed for the MSP430F5529 of the MSP430 family.

## Description

A watchdog timer (WDT) is a timer that monitors microcontroller (MCU) programs to check if they are out of control or have stopped operating. It acts as a "watchdog" watching over MCU operation.

In this project, the MSP430 uses two timers, TimerA0 and TimerA1.

- **Timer A0** pets the Watchdog Timer of the MSP430 itself to restart the program in case of program failure.
- **Timer A1** serves as a watchdog timer for another microcontroller. If Timer A1 is not petted regularly, it will shut down the power supply to the external microcontroller. After cutting off the power supply, Timer A1 will wait for some time and restart the power supply again using timer interrupts. Timer A1 will be petted regularly using an SPI signal from the slave microcontroller.

The Serial Peripheral Interface (SPI) is a standard for synchronous serial communication, used primarily in embedded systems for short-distance wired communication between integrated circuits.

## Code Overview

### Main Function

- **Pin Definitions**:
  - P1.0: Red LED
  - P1.1: OBC (On-Board Computer) regulation

- **Initialization**:
  - Disable high-impedance mode
  - Set P1.0 and P1.1 as output
  - Enable power supply to OBC (P1.1)

- **Timer A0 Initialization**:
  - Set CCR0 to 400
  - Use ACLK, UP mode
  - Enable interrupt

- **Timer A1 Initialization**:
  - Set CCR0 to 50000
  - Use ACLK, UP mode, slow speed
  - Enable interrupt

- **SPI Initialization**:
  - Set UCSWRST to initiate reset
  - Select SMCLK
  - Set baud rate
  - Enable synchronous mode and master mode
  - Select pins for SPI
  - Clear UCSWRST to release for operation
  - Enable receive interrupt

### Interrupt Service Routines (ISRs)

- **Timer0 ISR**: Pets the MSP430 WDT by clearing WDT.
- **Timer1 ISR**: Manages power supply to the external microcontroller. Shuts down power if not petted and restarts after a delay.
- **USCI_A0 ISR**: Handles SPI communication. Resets Timer A1 if the received data matches a specific value.

## More Information

More about the program functions and applications can be learned using the User Guide and Datasheet of MSP430F5529, which are widely available on the web.
