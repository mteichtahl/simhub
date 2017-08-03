# -------------------------------------------------
# Project created by QtCreator 2012-09-17T20:22:45
# -------------------------------------------------
QT -= core gui

# Create a configuration for 32-bit and 64-bit libraries:
# 32-bit: "CONFIG+=makeDLL DLL32"
# 64-bit: "CONFIG+=makeDLL DLL64"        not needed: "QMAKE_LFLAGS_WINDOWS+=/NODEFAULTLIB:LIBCMT"

CONFIG += BUILD_WITH_LIBUSB

makeDLL {
    DLL32 {
        message("Building 32-bit DLL...")
    } else {
        message("Building 64-bit DLL...")
    }
    CONFIG += dll warn_on
    DEFINES += POKEYSDLL POKEYSDLLEXPORT
} else {
    message("Building library")
    CONFIG += staticlib warn_on
}

BUILD_WITH_LIBUSB {
    DEFINES += POKEYSLIB_USE_LIBUSB
    INCLUDEPATH += ../libusb/include/libusb-1.0

    DLL32 {
        LIBS += -L../libusb/MS32/static -llibusb-1.0
    } else {
        LIBS += -L../libusb/MS64/static -llibusb-1.0
    }
}

TEMPLATE = lib


SOURCES += PoKeysLibCore.c \
    PoKeysLibFastUSB.c \
    PoKeysLibEncoders.c \
    PoKeysLibMatrixLED.c \
    PoKeysLibMatrixKB.c \
    PoKeysLibLCD.c \
    PoKeysLibIO.c \
    PoKeysLibDeviceData.c \
    PoKeysLibCoreSockets.c \
    PoKeysLibI2C.c \
    PoKeysLibPoNET.c \
    PoKeysLibPoIL.c \
    PoKeysLibRTC.c \
    PoKeysLibSPI.c \
    PoKeysLibPulseEngine_v2.c \
    PoKeysLib1Wire.c \
    PoKeysLibEasySensors.c \
    PoKeysLibUART.c \
    PoKeysLibCAN.c

win32: SOURCES += hid.c

HEADERS += PoKeysLibCoreSockets.h \
    PoKeysLibCore.h \
    hidapi.h \
    PoKeysLib.h \

win32 {
    LIBS += -lsetupapi -lWs2_32 -liphlpapi

    makeDLL {
        DLL32 {
            message("x86 build")
            #TARGET = ../../dll/32/PoKeysLib
            TARGET = ../../pokeyslib/binaries/windows/dll/32/PoKeyslib
        } else {
            message("x86_64 build")
            #TARGET = ../../dll/64/PoKeysLib
            TARGET = ../../pokeyslib/binaries/windows/dll/64/PoKeyslib
        }
    } else {
        LIB64 {
            message("x86_64 lib build")
            TARGET = ../../pokeyslib/binaries/windows/lib/64/PoKeysLib
        } else {
            message("x86 lib build")
            TARGET = ../../pokeyslib/binaries/windows/lib/32/PoKeysLib
        }
    }
}
unix:!macx {
    SOURCES += hid-libusb.c
    INCLUDEPATH += /usr/include/libusb-1.0
    LIBS += -L/usr/lib/ -lusb-1.0
    HEADERS += /usr/include/libusb-1.0/libusb.h
    TARGET = PoKeys
}

macx {
    SOURCES += hid-mac.c
    DEFINES += APL=1 IBM=0 LIN=0
    QMAKE_LFLAGS += -flat_namespace -undefined suppress

    # On OS X, install MacPorts and type "sudo ports install libusb"
    INCLUDEPATH += /opt/local/include/libusb-1.0
    LIBS += -L/opt/local/lib/ -lusb-1.0
    HEADERS += /opt/local/include/libusb-1.0/libusb.h

    # The following line defines for which architectures we build.
    CONFIG += x86
    TARGET = PoKeys
}

OTHER_FILES += \
    ReadMe.txt

DISTFILES += \
    Makefile.noqmake \
    Makefile.noqmake.osx \
    Python/PoKeys.py \
    Python/PoKeysUsage.py \
    Python/ConvertCtoPython_RegExp.txt
