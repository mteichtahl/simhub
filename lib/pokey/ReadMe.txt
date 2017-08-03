PoKeysLib

---- About ----
PoKeysLib is a multi-platform library which allows an application to interface 
PoKeys55, PoKeys56 and PoKeys57 series of PoKeys devices.
It is meant as a replacement and enhancement of the original .NET-based commun-
ication library for Windows.

Presentation is available on PoLabs blog: http://blog.poscope.com/pokeys-pokeyslib-library/

---- License ----
This library is released under GNU Lesser General Public License (LGPL). By us-
ing this library in any way, you agree with the terms described in License.txt

This library uses sources from HIDAPI library.

---- Installation ----
Preferred:
GNU GCC compiler is used on Linux and OS X to compile and install the library. 
Use the following command
  make -f Makefile.noqmake install
on Linux and
  make -f Makefile.noqmake.osx install
on OS X. These will also install the library in /usr/lib folder and copy the 
header file to /usr/include. Sudo may be required to gain write access to these
two folders

Dependencies (Windows):
The library (and applications using it) must be linked with the following libra-
ries on Windows:
    setupapi.lib
    Ws2_32.lib
    iphlpapi.lib
with the following linker command
-lsetupapi -lWs2_32 -liphlpapi

Dependencies (other OS):
The library (and applications using it) must be linked with the following libra-
ry:
    usb-1.0 (libusb-1.0)
with the following linker command
-lusb-1.0

Also:
qmake can be used to build the librray using the attached project file 
PoKeysLib.pro.

---- Allowing the regular users access USB PoKeys device ----
Create a new file in the /etc/udev/rules.d named 90-usb-pokeys.rules with 
the following contents (insert your username in the group parameter):
SUBSYSTEM=="usb", ATTRS{idVendor}=="1dc3", ATTRS{idProduct}=="1001", GROUP="<your username or group you belong to>", MODE="664"

Save the file, then execute
udevadm control --reload-rules


---- Usage ----
PoKeysLib library has to be linked or included in the client application. 
On Linux and OS X, it depends on libusb-1.0 library that must be installed 
before compiling PoKeysLib.

The host system is assumed to be little-endian.

Example code: 
http://www.mypokeys.com/new-cross-platform-library-for-all-pokeys-devices

---- PoKeys56U device rules setup (Linux) ----
(coming soon)

---- Library status - verified commands ----
[x] Enumerating USB devices
[x] Enumerating network devices
[x] Connecting to USB devices
[x] Fast USB interface support
[x] Connecting to network devices
[x] Reading device data
[x] Reading digital inputs
[x] Writing digital outputs
[x] PoExtBus writing
[x] PoExtBus reading
[x] LCD operations
[x] Matrix LED
[x] Setting pin functions
[x] Reading pin functions
[ ] Setting pin key codes
[ ] Reading pin key codes
[x] PWM operations
[x] Pulse engine operations
[x] Matrix keyboard setup
[x] Matrix keyboard reading
[x] Using encoders
[x] I2C operations
[x] SPI operation
[x] PoIL operations
[x] 1-wire operations
[x] PoNET bus support

---- Credits ----
Author: Matevž Bošnak (matevz@poscope.com)


---- Change log ----
17.02.2017: Support for new firmware features, UART, CAN, updated wrappers, prebuilt binaries
18.07.2016: Support for various configuration of PoKeys57 series USB interfaces
08.06.2016: Addition of simplest IO functions (for applications that struggle with using structures)
05.12.2015: Implementation of the support for EasySensors, removed support for Pulse engine v1
18.10.2015: Updates to support new devices, cleaning up the code, support for new features, precompiled binaries for Windows included
28.05.2015: Minor update (analog input low-pass filter support)
15.04.2015: (Initial) support for new devices, bug fixes
31.12.2014: Improved support for newer devices, fixed Makefile
09.10.2014: Added support for PoKeys57 series, misc bugs fixed
25.08.2014: Fast USB interface supported (PoKeys56U), Multi-part PEv2 data introduced
10.03.2014: Support for 1-wire included
31.01.2014: Updated PoIL shared slot read/write (wrong indexing)
17.01.2014: Ethernet device timeout configuration option added, bug fixes
17.12.2013: Support for Pulse engine v2 added, unification of data types used
17.11.2013: Memory leak fixed, PoIL task status read supported
16.11.2013: Added support for UDP connection to PoKeys56E/57E devices
03.10.2013: Support for network device data, pin capability function, new devices, bug fixes
13.04.2013: Mulitple updates: PWM, PoIL, SPI, RTC
15.12.2012: Support for I2C added
24.10.2012: Public release
16.10.2012: OS X version of the library tested
08.10.2012: Updated library - pure C, tested on Raspberry Pi
23.09.2012: Initial Windows+Linux library

