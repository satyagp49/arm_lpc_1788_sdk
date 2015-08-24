1. the example is uCOSII2.91+lwip-1.3.2 for LPC1768-Mini-DK.

2. instructions for use:
   (1) Project file path is: \uCOSII2.91+lwip-1.3.2\MDK-ARM\Project.uvproj.
   (2) The MDK 4.0 or later to open, The MDK version is too low will lead to not recognize the project.
   (3) Download and debugging tools is ULINK2 emulator ( JTAG clock must not too fast ).
   (4) Use the lpc17xx cmsis driver library.
   (5) Modify the library file lpc17xx_emac.c and lpc17xx_emac.h to support DM9161A.
   (6) Connect Ethernet cable with computer and LPC1768-Mini-DK.
   (7) LPC1768-Mini-DK IP address is 192.168.0.100.
