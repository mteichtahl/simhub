project(PoKeys)

cmake_minimum_required(VERSION 3.2)

include(FindPkgConfig)

pkg_check_modules(USB1 REQUIRED libusb-1.0>=1.0.16)

add_library(PoKeys SHARED
            PoKeysLibCore.c
            PoKeysLibCoreSockets.c
            hid-libusb.c
            PoKeysLibFastUSB.c
            PoKeysLibDeviceData.c
            PoKeysLibIO.c
            PoKeysLibEncoders.c
            PoKeysLibMatrixLED.c
            PoKeysLibMatrixKB.c
            PoKeysLibPoNET.c
            PoKeysLibLCD.c
            PoKeysLibRTC.c
            PoKeysLibEasySensors.c
            PoKeysLibI2C.c
            PoKeysLib1Wire.c
            PoKeysLibSPI.c
            PoKeysLibPulseEngine_v2.c)

install(FILES PoKeysLib.h DESTINATION include)
install(TARGETS PoKeys DESTINATION lib)