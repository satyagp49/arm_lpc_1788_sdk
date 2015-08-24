1. the example is UART1 for HY-LPC1788-SDK.

2. How to run:
   (1)	\IAR-EWARM: includes EWARM (IAR) project and configuration files.
   (2)	\KEIL-MDK:	includes RVMDK (Keil) project and configuration files, 
                    MDK 4.0 or later version to open, The MDK version is too low will lead to not recognize the project.
   (3) RVMDK (Keil) project Download and debugging tools is ULINK2 emulator ( JTAG clock must not too fast ).
   (3) EWARM (IAR) project Download and debugging tools is JLINK emulator ( JTAG clock must not too fast ).
   (4) Use the lpc17xx cmsis driver library v1.0 Jul.29.2011.
   (5) Connect MINI-USB cable with computer and HY-LPC1788-SDK USB-COM, install the CP2102 driver (in Software files),
       open Terminal.exe( in Software files ), and configure the baudrate of 115200 bits, 8 data bit, one stop bit, no parity,
	   No flow control.
   (6) Terminal will display information.