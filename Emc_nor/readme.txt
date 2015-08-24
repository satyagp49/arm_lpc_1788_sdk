1. the example is SDRAM for HY-LPC1788-SDK.

2. instructions for use:
   (1) Project file path is: \UART\MDK-ARM\Project.uvproj.
   (2)	\EWARM: includes EWARM (IAR) project and configuration files
   (3)	\Keil:	includes RVMDK (Keil)project and configuration files 

   (2) The MDK 4.0 or later to open, The MDK version is too low will lead to not recognize the project.
   (3) Download and debugging tools is ULINK2 emulator ( JTAG clock must not too fast ).
   (4) Use the lpc17xx cmsis driver library.
   (5) Connect MINI-USB cable with computer and LPC1768-Mini-DK USB-COM, install the CP2102 driver (in Software files),
       open AccessPort( in Software files ), and configure the baudrate of 115200 bits, one stop bit, no parity
	   ( It can set the language is English or chinese ).
   (6) AccessPort will display information.