# WATCHDOG TIMER FOR ANOTHER MICROCONTROLLER
The project focuses on implementing MSP430 as a watchdog timer for another controller e.g. Arduino Uno

The code is primarily designed for MSP430F5529 of MSP430 family.

(WDT: Watchdog timer) A watchdog timer (WDT) is a timer that monitors microcontroller (MCU) programs to see if they are out of control or have stopped operating. It acts as a “watchdog” watching over MCU operation.

The MSP430 uses two timers TimerA0 and TimerA1.

Timer A0 pets the Watchdog timer of MSP430 itself to restart the program in case of program failure.

Timer A1 serves as a watchdog timer for another microcontroller which if not petted regularly, will shut down the power supply to the microcontroller.

After cutting off the power supply, the Timer A1 will wait for some time and restart the Power supply again using Timer Interrupts.

TimerA1 will be petted regularly using a SPI signal from the slave microntroller.

Serial Peripheral Interface (SPI) is a de facto standard (with many variants) for synchronous serial communication, used primarily in embedded systems for short-distance wired communication between integrated circuits

More about the Program functions and applications can be learned using User Guide and Datasheet of MSP430F5529 widely available in web.
