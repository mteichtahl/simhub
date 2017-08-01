/*

Copyright (C) 2013 Matevž Bošnak (matevz@poscope.com)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA 

*/

#include <stdlib.h>
#include "PoKeysLib.h"
#include "PoKeysLibCore.h"
#include "PoKeysLibCoreSockets.h"
#include "string.h"
#include "stdio.h"
//#define PK_COM_DEBUG

// Connection specific commands
int32_t PK_EnumerateUSBDevices()
{
    int32_t numDevices = 0;
    struct hid_device_info *devs, *cur_dev;

    devs = hid_enumerate(0x1DC3, 0x1001);
    cur_dev = devs;

    while (cur_dev)
    {
        /*printf("Device Found\n");
        printf("  Serial:      %ls\n", cur_dev->serial_number);
        printf("  Product:      %ls\n", cur_dev->product_string);
        printf("  Interface:    %d\n",  cur_dev->interface_number);
        printf("\n");*/
        if (cur_dev->interface_number == 1) numDevices++;
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

    return numDevices;
}

int32_t PK_GetCurrentDeviceConnectionType(sPoKeysDevice* device)
{
	return device->connectionType;
}

void InitializeNewDevice(sPoKeysDevice* device)
{
    uint32_t i;
	memset(&device->info, 0, sizeof(sPoKeysDevice_Info));
    memset(&device->DeviceData, 0, sizeof(sPoKeysDevice_Data));

    device->netDeviceData = 0;

	memset(&device->matrixKB, 0, sizeof(sMatrixKeyboard));
	memset(&device->PWM, 0, sizeof(sPoKeysPWM));
	memset(&device->LCD, 0, sizeof(sPoKeysLCD));
	

	device->FastEncodersConfiguration = 0;
	device->FastEncodersOptions = 0;
	device->UltraFastEncoderConfiguration = 0;
	device->UltraFastEncoderOptions = 0;

	device->UltraFastEncoderFilter = 0;

	memset(device->request, 0, 64);
	memset(device->response, 0, 64);

    PK_DeviceDataGet(device);

    device->Pins = (sPoKeysPinData*)malloc(sizeof(sPoKeysPinData) * device->info.iPinCount);
	memset(device->Pins, 0, sizeof(sPoKeysPinData) * device->info.iPinCount);


	for (i = 0; i < device->info.iPinCount; i++)
	{
		if (PK_IsCounterAvailable(device, i))
		{
			device->Pins[i].DigitalCounterAvailable = 1;
		} else
		{
			device->Pins[i].DigitalCounterAvailable = 0;
		}
	}

	device->Encoders = (sPoKeysEncoder*)malloc(sizeof(sPoKeysEncoder) * device->info.iEncodersCount);
	memset(device->Encoders, 0, sizeof(sPoKeysEncoder) * device->info.iEncodersCount);

	device->PWM.PWMduty = (uint32_t*)malloc(sizeof(uint32_t) * device->info.iPWMCount);
	memset(device->PWM.PWMduty, 0, sizeof(uint32_t) * device->info.iPWMCount);

	device->PWM.PWMenabledChannels = (unsigned char*)malloc(sizeof(unsigned char) * device->info.iPWMCount);
	memset(device->PWM.PWMenabledChannels, 0, sizeof(unsigned char) * device->info.iPWMCount);

	device->PoExtBusData = (unsigned char*)malloc(sizeof(unsigned char) * device->info.iPoExtBus);

    device->MatrixLED = (sPoKeysMatrixLED*)malloc(sizeof(sPoKeysMatrixLED) * device->info.iMatrixLED);
	memset(device->MatrixLED, 0, sizeof(sPoKeysMatrixLED) * device->info.iMatrixLED);

	if (device->info.iPulseEngine)
	{
		device->PulseEngine = (sPoKeysPE*)malloc(sizeof(sPoKeysPE));

		PK_PEInfoGet(device);

		// Allocate buffer
		device->PulseEngine->buffer.buffer = (unsigned char*)malloc(sizeof(unsigned char) * device->PulseEngine->info.bufferDepth);
		memset(device->PulseEngine->buffer.buffer, 0, sizeof(unsigned char) * device->PulseEngine->info.bufferDepth);

		device->PulseEngine->ReferencePosition = (uint32_t*)malloc(sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		memset(device->PulseEngine->ReferencePosition, 0, sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		device->PulseEngine->CurrentPosition = (uint32_t*)malloc(sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		memset(device->PulseEngine->CurrentPosition, 0, sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		device->PulseEngine->MaxSpeed = (uint32_t*)malloc(sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		memset(device->PulseEngine->MaxSpeed, 0, sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		device->PulseEngine->MaxAcceleration = (uint32_t*)malloc(sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		memset(device->PulseEngine->MaxAcceleration, 0, sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		device->PulseEngine->MaxDecceleration = (uint32_t*)malloc(sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		memset(device->PulseEngine->MaxDecceleration, 0, sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		device->PulseEngine->AxisState = (unsigned char*)malloc(sizeof(unsigned char) * device->PulseEngine->info.nrOfAxes);
		memset(device->PulseEngine->AxisState, 0, sizeof(unsigned char) * device->PulseEngine->info.nrOfAxes);

		device->PulseEngine->MPGjogMultiplier = (uint32_t*)malloc(sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		memset(device->PulseEngine->MPGjogMultiplier, 0, sizeof(uint32_t) * device->PulseEngine->info.nrOfAxes);
		device->PulseEngine->MPGaxisEncoder = (unsigned char*)malloc(sizeof(unsigned char) * device->PulseEngine->info.nrOfAxes);
		memset(device->PulseEngine->MPGaxisEncoder, 0, sizeof(unsigned char) * device->PulseEngine->info.nrOfAxes);

	} else device->PulseEngine = NULL;

    memset(&device->PEv2, 0, sizeof(sPoKeysPEv2));

    device->sendRetries = 3;
    device->readRetries = 10;
    device->socketTimeout = 100;
}

void CleanDevice(sPoKeysDevice* device)
{
	free(device->Pins);
	free(device->Encoders);
	free(device->PWM.PWMduty);
	free(device->PWM.PWMenabledChannels);
	free(device->PoExtBusData);
	free(device->MatrixLED);

    if (device->netDeviceData != 0)
    {
        free(device->netDeviceData);
        device->netDeviceData = 0;
    }

	if (device->PulseEngine != NULL)
	{
		free(device->PulseEngine->buffer.buffer);
		
		free(device->PulseEngine->ReferencePosition);
		free(device->PulseEngine->CurrentPosition);
		free(device->PulseEngine->MaxSpeed);
		free(device->PulseEngine->MaxAcceleration);
		free(device->PulseEngine->MaxDecceleration);
		free(device->PulseEngine->AxisState);

		free(device->PulseEngine->MPGjogMultiplier);
		free(device->PulseEngine->MPGaxisEncoder);
		free(device->PulseEngine);
	}
}

void PK_ReleaseDeviceStructure(sPoKeysDevice* device)
{
    CleanDevice(device);
}

void PK_CloneDeviceStructure(sPoKeysDevice* original, sPoKeysDevice *destination)
{
    // Reserve memory...
    destination->Pins = (sPoKeysPinData*)malloc(sizeof(sPoKeysPinData) * original->info.iPinCount);
    destination->Encoders = (sPoKeysEncoder*)malloc(sizeof(sPoKeysEncoder) * original->info.iEncodersCount);
    destination->PWM.PWMduty = (uint32_t*)malloc(sizeof(uint32_t) * original->info.iPWMCount);
    destination->PWM.PWMenabledChannels = (unsigned char*)malloc(sizeof(unsigned char) * original->info.iPWMCount);
    destination->MatrixLED = (sPoKeysMatrixLED*)malloc(sizeof(sPoKeysMatrixLED) * original->info.iMatrixLED);

    // Network device information structure...
    if (original->netDeviceData != 0)
    {
        destination->netDeviceData = (sPoKeysNetworkDeviceInfo *)malloc(sizeof(sPoKeysNetworkDeviceInfo));
        memcpy(destination->netDeviceData, original->netDeviceData, sizeof(sPoKeysNetworkDeviceInfo));
    } else
    {
        destination->netDeviceData = 0;
    }

    if (original->info.iPulseEngine)
    {
        destination->PulseEngine = (sPoKeysPE*)malloc(sizeof(sPoKeysPE));

        // Allocate buffer
        destination->PulseEngine->buffer.buffer
                = (unsigned char*)malloc(sizeof(unsigned char) * original->PulseEngine->info.bufferDepth);
        memset(destination->PulseEngine->buffer.buffer, 0,
               sizeof(unsigned char) * original->PulseEngine->info.bufferDepth);

        destination->PulseEngine->ReferencePosition
                = (uint32_t*)malloc(sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        destination->PulseEngine->CurrentPosition
                = (uint32_t*)malloc(sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        destination->PulseEngine->MaxSpeed
                = (uint32_t*)malloc(sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        destination->PulseEngine->MaxAcceleration
                = (uint32_t*)malloc(sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        destination->PulseEngine->MaxDecceleration
                = (uint32_t*)malloc(sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        destination->PulseEngine->AxisState
                = (unsigned char*)malloc(sizeof(unsigned char) * original->PulseEngine->info.nrOfAxes);

        destination->PulseEngine->MPGjogMultiplier
                = (uint32_t*)malloc(sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        destination->PulseEngine->MPGaxisEncoder
                = (unsigned char*)malloc(sizeof(unsigned char) * original->PulseEngine->info.nrOfAxes);

    } else destination->PulseEngine = NULL;
    destination->PoExtBusData = (unsigned char*)malloc(sizeof(unsigned char) * original->info.iPoExtBus);



    // Copy data
    destination->devHandle = original->devHandle;
    destination->devHandle2 = original->devHandle2;

    destination->info = original->info;
    destination->DeviceData = original->DeviceData;

    memcpy(&destination->Pins[0], &original->Pins[0],
            original->info.iPinCount * sizeof(sPoKeysPinData));
    memcpy(&destination->Encoders[0], &original->Encoders[0],
            original->info.iEncodersCount * sizeof(sPoKeysEncoder));

    destination->matrixKB = original->matrixKB;

    destination->PWM.PWMperiod = original->PWM.PWMperiod;
    memcpy(destination->PWM.PWMduty, original->PWM.PWMduty,
           sizeof(uint32_t) * original->info.iPWMCount);
    memcpy(destination->PWM.PWMenabledChannels, original->PWM.PWMenabledChannels,
           sizeof(unsigned char) * original->info.iPWMCount);

    memcpy(destination->MatrixLED, original->MatrixLED,
           sizeof(sPoKeysMatrixLED) * original->info.iMatrixLED);

    destination->LCD = original->LCD;

    if (original->info.iPulseEngine)
    {
        destination->PulseEngine->info = original->PulseEngine->info;

        memcpy(destination->PulseEngine->ReferencePosition, original->PulseEngine->ReferencePosition, sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        memcpy(destination->PulseEngine->CurrentPosition,   original->PulseEngine->CurrentPosition, sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        memcpy(destination->PulseEngine->MaxSpeed,          original->PulseEngine->MaxSpeed, sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        memcpy(destination->PulseEngine->MaxAcceleration,   original->PulseEngine->MaxAcceleration, sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        memcpy(destination->PulseEngine->MaxDecceleration,  original->PulseEngine->MaxDecceleration, sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        memcpy(destination->PulseEngine->AxisState,         original->PulseEngine->AxisState, sizeof(unsigned char) * original->PulseEngine->info.nrOfAxes);
        memcpy(destination->PulseEngine->MPGjogMultiplier,  original->PulseEngine->MPGjogMultiplier, sizeof(uint32_t) * original->PulseEngine->info.nrOfAxes);
        memcpy(destination->PulseEngine->MPGaxisEncoder,    original->PulseEngine->MPGaxisEncoder, sizeof(unsigned char) * original->PulseEngine->info.nrOfAxes);

        destination->PulseEngine->MPGjogActivated = original->PulseEngine->MPGjogActivated;

        destination->PulseEngine->PulseEngineEnabled = original->PulseEngine->PulseEngineEnabled;
        destination->PulseEngine->PulseEngineState = original->PulseEngine->PulseEngineState;

        destination->PulseEngine->LimitConfigP = original->PulseEngine->LimitConfigP;
        destination->PulseEngine->LimitConfigN = original->PulseEngine->LimitConfigN;
        destination->PulseEngine->LimitStatusP = original->PulseEngine->LimitStatusP;
        destination->PulseEngine->LimitStatusN = original->PulseEngine->LimitStatusN;
        destination->PulseEngine->HomeConfig = original->PulseEngine->HomeConfig;
        destination->PulseEngine->HomeStatus = original->PulseEngine->HomeStatus;

        destination->PulseEngine->DirectionChange = original->PulseEngine->DirectionChange;

        destination->PulseEngine->HomingDirectionChange = original->PulseEngine->HomingDirectionChange;
        destination->PulseEngine->HomingSpeed = original->PulseEngine->HomingSpeed;
        destination->PulseEngine->HomingReturnSpeed = original->PulseEngine->HomingReturnSpeed;
        destination->PulseEngine->AxesHomingFlags = original->PulseEngine->AxesHomingFlags;

        destination->PulseEngine->kb48CNCenabled = original->PulseEngine->kb48CNCenabled;
        destination->PulseEngine->ChargePumpEnabled = original->PulseEngine->ChargePumpEnabled;

        destination->PulseEngine->EmergencySwitchPolarity = original->PulseEngine->EmergencySwitchPolarity;
    }

    destination->PoNETmodule = original->PoNETmodule;
    destination->PoIL = original->PoIL;
    destination->RTC = original->RTC;


    destination->FastEncodersConfiguration =    original->FastEncodersConfiguration;
    destination->FastEncodersOptions =          original->FastEncodersOptions;
    destination->UltraFastEncoderConfiguration =original->UltraFastEncoderConfiguration;
    destination->UltraFastEncoderOptions =      original->UltraFastEncoderOptions;
    destination->UltraFastEncoderFilter =       original->UltraFastEncoderFilter;

    memcpy(destination->PoExtBusData, original->PoExtBusData, sizeof(unsigned char) * original->info.iPoExtBus);

    destination->connectionType = original->connectionType;
    destination->requestID = original->requestID;

}

sPoKeysDevice* PK_ConnectToDevice(uint32_t deviceIndex)
{
    int32_t numDevices = 0;
    struct hid_device_info *devs, *cur_dev;
    sPoKeysDevice* tmpDevice;

    devs = hid_enumerate(0x1DC3, 0x1001);
    cur_dev = devs;

    while (cur_dev)
    {
        if (cur_dev->interface_number == 1)
        {
            if (numDevices == deviceIndex)
            {
				tmpDevice = (sPoKeysDevice*)malloc(sizeof(sPoKeysDevice));

                //printf("Connect to this device...");
				tmpDevice->devHandle = (void*)hid_open_path(cur_dev->path);
                tmpDevice->devHandle2 = NULL;

				tmpDevice->connectionType = PK_DeviceType_USBDevice;

				if (tmpDevice->devHandle != NULL)
				{
                    InitializeNewDevice(tmpDevice);
				} else
				{
					free(tmpDevice);
					tmpDevice = NULL;
				}
                //hid_set_nonblocking(devHandle);
                hid_free_enumeration(devs);
                return tmpDevice;
            }
            numDevices++;
        }
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

    return NULL;
}

sPoKeysDevice* PK_ConnectToPoKeysDevice(uint32_t serialNumber, uint32_t checkForNetworkDevicesAndTimeout, uint32_t flags)
{
    int32_t numDevices = 0;
    struct hid_device_info *devs, *cur_dev;
    int32_t k;
    sPoKeysDevice* tmpDevice;
    uint8_t serialSearch[8];
    uint8_t serialSearch58[8];

    sPoKeysNetworkDeviceSummary * devices;
    int32_t iNet;

    devs = hid_enumerate(0x1DC3, 0x1001);
    cur_dev = devs;

    sprintf(serialSearch, "2.%05lu", serialNumber % 100000);
    sprintf(serialSearch58, "3.%05lu", serialNumber % 100000);

    while (cur_dev)
    {
        if (cur_dev->interface_number == 1)
        {
            if (cur_dev->serial_number[0] != 'P')
            {
                for (k = 0; k < 8 && cur_dev->serial_number[k] != 0; k++)
                {
                    if (cur_dev->serial_number[k] != serialSearch[k]) break;
                }

                if (k != 7)
                {
                    for (k = 0; k < 8 && cur_dev->serial_number[k] != 0; k++)
                    {
                        if (cur_dev->serial_number[k] != serialSearch58[k]) break;
                    }
                }

                if (k == 7)
                {
                    tmpDevice = (sPoKeysDevice*)malloc(sizeof(sPoKeysDevice));

                    //printf("Connect to this device...");
                    tmpDevice->devHandle = (void*)hid_open_path(cur_dev->path);
                    tmpDevice->devHandle2 = 0;

                    tmpDevice->connectionType = PK_DeviceType_USBDevice;
                    if (tmpDevice->devHandle != NULL)
                    {
                        InitializeNewDevice(tmpDevice);
                    } else
                    {
                        free(tmpDevice);
                        tmpDevice = NULL;
                    }
                    //hid_set_nonblocking(devHandle);
                    hid_free_enumeration(devs);
                    return tmpDevice;
                }
            } else
            {
                // Old, PoKeys55 device - we must to connect and read the serial number...
                tmpDevice = (sPoKeysDevice*)malloc(sizeof(sPoKeysDevice));
                tmpDevice->devHandle = (void*)hid_open_path(cur_dev->path);
                tmpDevice->devHandle2 = 0;

                if (tmpDevice->devHandle != NULL)
                {
                    InitializeNewDevice(tmpDevice);
                } else
                {
                    free(tmpDevice);
                    tmpDevice = NULL;
                    hid_free_enumeration(devs);
                    return NULL;
                }
                hid_free_enumeration(devs);

                tmpDevice->connectionType = PK_DeviceType_USBDevice;
                if (tmpDevice->DeviceData.SerialNumber == serialNumber)
                {
                    return tmpDevice;
                } else
                {
                    CleanDevice(tmpDevice);
                    free(tmpDevice);
                }
            }

            numDevices++;
        }
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

    if (checkForNetworkDevicesAndTimeout)
    {
        devices = (sPoKeysNetworkDeviceSummary*)malloc(sizeof(sPoKeysNetworkDeviceSummary) * 16);
        iNet = PK_SearchNetworkDevices(devices, checkForNetworkDevicesAndTimeout, serialNumber);

        if (iNet > 16) iNet = 16;

        for (k = 0; k < iNet; k++)
        {
            //printf("\nNetwork device found, serial = %lu at %u.%u.%u.%u", devices[k].SerialNumber, devices[k].IPaddress[0], devices[k].IPaddress[1], devices[k].IPaddress[2], devices[k].IPaddress[3]);
            if (devices[k].SerialNumber == serialNumber)
            {
                if (flags & 1) devices[k].useUDP = 1;
                tmpDevice = PK_ConnectToNetworkDevice(&devices[k]);
                if (tmpDevice == NULL)
                {
                    //CleanDevice(tmpDevice);
                    free(tmpDevice);
                    //printf("\nProblem connecting to the device...");
                } else
                {
                    free(devices);
                    InitializeNewDevice(tmpDevice);
                    return tmpDevice;
                }
            }
        }
        free(devices);
    }

    return NULL;
}


sPoKeysDevice* PK_ConnectToDeviceWSerial(uint32_t serialNumber, uint32_t checkForNetworkDevicesAndTimeout)
{
    return PK_ConnectToPoKeysDevice(serialNumber, checkForNetworkDevicesAndTimeout, 0);
}

sPoKeysDevice* PK_ConnectToDeviceWSerial_UDP(uint32_t serialNumber, uint32_t checkForNetworkDevicesAndTimeout)
{
    return PK_ConnectToPoKeysDevice(serialNumber, checkForNetworkDevicesAndTimeout, 1);
}

void PK_DisconnectDevice(sPoKeysDevice* device)
{
    if (device != NULL)
    {
		if (device->connectionType == PK_DeviceType_NetworkDevice) 
		{
			PK_DisconnectNetworkDevice(device);
		} else
		{
			if ((hid_device*)device->devHandle != NULL)
			{
				hid_close((hid_device*)device->devHandle);
			}
		}

		CleanDevice(device);
		free(device);
    }
}

int32_t CreateRequest(unsigned char * request, unsigned char type, unsigned char param1, unsigned char param2, unsigned char param3, unsigned char param4)
{
    if (request == NULL) return PK_ERR_NOT_CONNECTED;

    memset(request, 0, 64);

    request[1] = type;
    request[2] = param1;
    request[3] = param2;
    request[4] = param3;
    request[5] = param4;

    return PK_OK;
}

uint8_t getChecksum(uint8_t * data)
{
    uint8_t temp = 0;
    uint32_t i;

    for (i = 0; i < 7; i++)
    {
            temp += data[i];
    }
    return temp;
}

int32_t LastRetryCount = 0;
int32_t LastWaitCount = 0;


//#define PK_COM_DEBUG
int32_t SendRequest(sPoKeysDevice* device)
{
    // Initialize variables
    uint32_t waits = 0;
    uint32_t retries = 0;
    int32_t result = 0;
    uint8_t bufferOut[65] = {0};

    #ifdef PK_COM_DEBUG
        int i;
    #endif

    hid_device * devHandle;



    if (device == NULL) return PK_ERR_GENERIC;
	if (device->connectionType == PK_DeviceType_NetworkDevice)
	{
		return SendEthRequest(device);
	}

    devHandle = (hid_device*)device->devHandle;


    if (devHandle == NULL) return PK_ERR_GENERIC;

    // Request sending loop
    while (retries++ < 2)
    {
        device->request[0] = 0xBB;
        device->request[6] = ++device->requestID;
        device->request[7] = getChecksum(device->request);

        memcpy(bufferOut + 1, device->request, 64);

        #ifdef PK_COM_DEBUG
                printf("\n * SEND ");
                for (i = 0; i < 10; i++)
                {
                        printf("%X ", bufferOut[i]);
                }
        #endif

        result = hid_write(devHandle, bufferOut, 65);

        // In case of an error, try sending again
        if (result < 0)
        {
            //printf(" ERR %u", result);
            retries++;
            continue;
        }

        waits = 0;

        // Request receiving loop
        while (waits++ < 50)
        {
            result = hid_read(devHandle, device->response, 65);

            // Error is not an option
            if (result < 0)
            {
                    //printf(" Receive ERR %u", result);
                    break;
            }

#ifdef PK_COM_DEBUG
        printf("\n * RECV ");
        for (i = 0; i < 10; i++)
        {
                printf("%X ", device->response[i]);
        }

        printf(" (request ID: %X ?= %X", device->response[6], device->requestID);
#endif

                // Check the header and the request ID
                if (device->response[0] == 0xAA && device->response[6] == device->requestID)
                {
                    if (device->response[7] == getChecksum(device->response))
                    {
                        LastRetryCount = retries;
                        LastWaitCount = waits;
                        // This is it. Return from this function
                        return PK_OK;
                    }
                }
            }
    }

    return PK_ERR_TRANSFER;
}
