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
#include "stdio.h"

// This structure is using real pin numbers
const sPoKeys_PinCapabilities pinCaps[] = {
    { PK_AllPinCap_digitalInput,        1, 55, 0, PK_DeviceMask_55 | PK_DeviceMask_56 | PK_DeviceMask_27 },
    { PK_AllPinCap_digitalOutput,       1, 55, 0, PK_DeviceMask_55 | PK_DeviceMask_56 | PK_DeviceMask_27 },
    { PK_AllPinCap_analogInput,        43, 47, 0, PK_DeviceMask_55 },
    { PK_AllPinCap_analogInput,        41, 47, 0, PK_DeviceMask_56 | PK_DeviceMask_27 },
    { PK_AllPinCap_analogOutput,       43, 43, 0, PK_DeviceMask_55 },
    { PK_AllPinCap_keyboardMapping,     1, 55, 0, PK_DeviceMask_55 | PK_DeviceMask_56U },
    { PK_AllPinCap_triggeredInput,      1, 55, 0, PK_DeviceMask_55 | PK_DeviceMask_56U },
    { PK_AllPinCap_digitalCounter,      1, 55, 1, PK_DeviceMask_56U | PK_DeviceMask_56E },
    { PK_AllPinCap_PWMOut,             17, 22, 0, PK_DeviceMask_55 | PK_DeviceMask_56 },
    { PK_AllPinCap_fastEncoder1A,       1,  1, 0, PK_DeviceMask_55 | PK_DeviceMask_56 },
    { PK_AllPinCap_fastEncoder1B,       2,  2, 0, PK_DeviceMask_55 | PK_DeviceMask_56 },
    { PK_AllPinCap_fastEncoder1I,       9,  9, 1, PK_DeviceMask_55 | PK_DeviceMask_56 },

    { PK_AllPinCap_fastEncoder2A,       3,  3, 1, PK_DeviceMask_55 },
    { PK_AllPinCap_fastEncoder2B,       4,  4, 1, PK_DeviceMask_55 },
    { PK_AllPinCap_fastEncoder2A,       5,  5, 1, PK_DeviceMask_55 | PK_DeviceMask_56 },
    { PK_AllPinCap_fastEncoder2B,       6,  6, 1, PK_DeviceMask_55 | PK_DeviceMask_56 },
    { PK_AllPinCap_fastEncoder2I,      11, 11, 1, PK_DeviceMask_55 | PK_DeviceMask_56 },

    { PK_AllPinCap_fastEncoder3A,      15, 15, 0, PK_DeviceMask_55 | PK_DeviceMask_56 },
    { PK_AllPinCap_fastEncoder3B,      16, 16, 0, PK_DeviceMask_55 | PK_DeviceMask_56 },
    { PK_AllPinCap_fastEncoder3I,      27, 27, 1, PK_DeviceMask_55 | PK_DeviceMask_56 },


    { PK_AllPinCap_digitalInput,        9, 19, 0, PK_DeviceMask_PoPLC58 },
    { PK_AllPinCap_digitalOutput,      20, 27, 0, PK_DeviceMask_PoPLC58 },
    { PK_AllPinCap_analogInput,         1,  8, 0, PK_DeviceMask_PoPLC58 },
    { PK_AllPinCap_MFanalogInput,       1,  8, 0, PK_DeviceMask_PoPLC58 },
    { -1, 0, 0, 0 }
};

int32_t PK_DeviceDataGet(sPoKeysDevice* device)
{
    int32_t i;
    sPoKeysDevice_Data * data;
    sPoKeysDevice_Info * info;

    uint8_t devSeries55 = 0;
    uint8_t devSeries56 = 0;
    uint8_t devSeries27 = 0;
    uint8_t devSeries58 = 0;
    uint8_t devUSB = 0;
    uint8_t devEth = 0;
    uint8_t devBootloader = 0;

    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    data = &device->DeviceData;
    info = &device->info;

	memset(info, 0, sizeof(sPoKeysDevice_Info));

	memset(device->request, 0, 64);
	memset(device->response, 0, 64);

	// Read serial and firmware version
	CreateRequest(device->request, 0x00, 0, 0, 0, 0);
	if (SendRequest(device) == PK_OK)
    {
        if (device->response[8] == 'P' && device->response[9] == 'K'
                && device->response[10] == '5' && device->response[11] == '8')
        {
            // Series 58 device
            data->FirmwareVersionMajor = device->response[4];
            data->FirmwareVersionMinor = device->response[5];

            data->SerialNumber = (int)device->response[12] + ((int)device->response[13] << 8)
                    + ((int)device->response[14] << 16) + ((int)device->response[15] << 24);
            data->HWtype = device->response[18];

            // Read device name
            memset(data->DeviceName, 0, 11);
            memcpy(data->DeviceName, device->response + 31, 10);

            // Read build date
            memset(data->BuildDate, 0, 12);
            memcpy(data->BuildDate, device->response + 20, 11);

        } else
        {
            data->FirmwareVersionMajor = device->response[4];
            data->FirmwareVersionMinor = device->response[5];

            data->SerialNumber = ((long)device->response[2]*256 + (long)device->response[3]);
            data->DeviceName[0] = 0;
            data->BuildDate[0] = 0;
        }
    } else return PK_ERR_TRANSFER;

	// Read User ID
    CreateRequest(device->request, 0x03, 0, 0, 0, 0);
	if (SendRequest(device) == PK_OK)
    {
        data->UserID = device->response[2];
        data->DeviceLockStatus = device->response[3];
	} else return PK_ERR_TRANSFER;

	// Resolve device type
    if (data->SerialNumber == 0xFFFF)
    {
		data->DeviceType = 3; // old bootloader - recovery mode
		devSeries55 = 1;
		devBootloader = 1;

        data->DeviceTypeID = PK_DeviceMask_Bootloader | PK_DeviceMask_Bootloader55;
    
	// PoKeys56 devices have serial numbers above 20000
    } else if (data->SerialNumber >= 20000 && data->SerialNumber < 65536)
    {
		// PoKeys56 bootloaders have bit 7 set in the major firmware version
		if ((data->FirmwareVersionMajor & (1 << 7)) > 0)
        {
            if (device->connectionType == PK_DeviceType_NetworkDevice)
            {
                data->DeviceType = 16; // PoKeys56E bootloader
				devBootloader = 1;
				devSeries56 = 1;

                data->DeviceTypeID = PK_DeviceMask_Bootloader | PK_DeviceMask_Bootloader56 | PK_DeviceMask_Bootloader56E;
            }
            else
            {
                data->DeviceType = 15; // PoKeys56U bootloader
				devUSB = 1;
				devBootloader = 1;
				devSeries56 = 1;

                data->DeviceTypeID = PK_DeviceMask_Bootloader | PK_DeviceMask_Bootloader56 | PK_DeviceMask_Bootloader56U;
            }
        }
        else
        {
            // PoTLog27
            if (data->FirmwareVersionMajor == 64)
            {
				if (device->connectionType == PK_DeviceType_NetworkDevice)
                {
                    data->DeviceType = 21; // PoTLog27E
					devSeries27 = 1;
					devEth = 1;

                    data->DeviceTypeID = PK_DeviceMask_27 | PK_DeviceMask_27E;
                }
                else
                {
					devUSB = 1;
					devSeries27 = 1;
                    data->DeviceType = 20; // PoTLog27U
                    data->DeviceTypeID = PK_DeviceMask_27 | PK_DeviceMask_27U;
                }
            }
            else
            {
                if (device->connectionType == PK_DeviceType_NetworkDevice)
                {
                    data->DeviceType = 11; // PoKeys56E
					devSeries56 = 1;
					devEth = 1;
                    data->DeviceTypeID = PK_DeviceMask_56 | PK_DeviceMask_56E;
                }
                else
                {
					devUSB = 1;
                    data->DeviceType = 10; // PoKeys56U
    				devSeries56 = 1;
                    data->DeviceTypeID = PK_DeviceMask_56 | PK_DeviceMask_56U;
                }
            }
        }
    } else if (data->SerialNumber >= 50000)
    {
        // PoKeys58 series devices report their type by themselves
        data->DeviceType = data->HWtype;
        devSeries58 = 1;

        devUSB = 1;
        devEth = 1;

        switch (data->DeviceType)
        {
            // PoKeys58EU
            case 40:
                data->DeviceTypeID = PK_DeviceMask_58;
                break;
            // PoBootload series 58
            case 41:
                data->DeviceTypeID = PK_DeviceMask_Bootloader58;
                devBootloader = 1;
                break;
            // PoPLC58
            case 50:
                data->DeviceTypeID = PK_DeviceMask_PoPLC58;
                break;
        }
    }
	// PoKeys55 v3
    else if (data->SerialNumber >= 11500)
    {
		devUSB = 1;
		devSeries55 = 1;
        data->DeviceType = 2;
        data->DeviceTypeID = PK_DeviceMask_55 | PK_DeviceMask_55v3;
    }
	// PoKeys55 v2
    else if (data->SerialNumber >= 10113)
    {
		devUSB = 1;
		devSeries55 = 1;
        data->DeviceType = 1;
        data->DeviceTypeID = PK_DeviceMask_55 | PK_DeviceMask_55v2;
    }
	// PoKeys55 v1
    else
	{
		devUSB = 1;
		devSeries55 = 1;
        data->DeviceType = 0;
        data->DeviceTypeID = PK_DeviceMask_55 | PK_DeviceMask_55v1;
    }

	// Resolve the type names
	switch (data->DeviceType)
    {
        case 0:
            sprintf(data->DeviceTypeName, "generic PoKeys device");
			break;
        case 1:
            sprintf(data->DeviceTypeName, "PoKeys55");
			break;
        case 2:
            sprintf(data->DeviceTypeName, "PoKeys55");
			break;
        case 3:
            sprintf(data->DeviceTypeName, "PoKeys55 - recovery");
			break;
        case 10:
            sprintf(data->DeviceTypeName, "PoKeys56U");
			break;
        case 11:
            sprintf(data->DeviceTypeName, "PoKeys56E");
			break;
        case 15:
            sprintf(data->DeviceTypeName, "PoKeys56U - recovery");
			break;
        case 16:
            sprintf(data->DeviceTypeName, "PoKeys56E - recovery");
			break;
        case 20:
            sprintf(data->DeviceTypeName, "PoTLog27U");
			break;
        case 21:
            sprintf(data->DeviceTypeName, "PoTLog27E");
			break;
        case 40:
            sprintf(data->DeviceTypeName, "PoKeys58EU");
            break;
        case 41:
            sprintf(data->DeviceTypeName, "PoBootload");
            break;
        case 50:
            sprintf(data->DeviceTypeName, "PoPLC58");
            break;
        default:
            sprintf(data->DeviceTypeName, "PoKeys");
			break;
    }

	switch (data->DeviceType)
    {
		// PoKeys55
        case 0:
		case 1:
		case 2:
			info->iPinCount = 55;
			info->iEncodersCount = 25;
			info->iPWMCount = 6;
			info->iBasicEncoderCount = 25;

			device->info.PWMinternalFrequency = 12000000;
			break;

		// PoKeys55 bootloader
		case 3:
			info->iPinCount = 0;
			info->iEncodersCount = 0;
			info->iPWMCount = 0;
			info->iBasicEncoderCount = 0;
			break;
        
		// PoKeys56U, PoKeys56E
		case 10:
		case 11:
			info->iPinCount = 55;
			info->iEncodersCount = 26;
			info->iBasicEncoderCount = 25;
			info->iPWMCount = 6;

			device->info.PWMinternalFrequency = 25000000;
			break;

		// PoKeys56U, PoKeys56E bootloader
		case 15:
        case 16:
			info->iPinCount = 0;
			info->iEncodersCount = 0;
			info->iBasicEncoderCount = 0;
			info->iPWMCount = 0;
			break;
		
		// PoTLog27U, PoTLog27E
		case 20:
		case 21:
			info->iPinCount = 55;
			info->iBasicEncoderCount = 0;
			info->iEncodersCount = 0;
			info->iPWMCount = 0;
			break;

        // PoKeys58EU
        case 40:
            break;

        // PoBootload
        case 41:
            info->iPinCount = 0;
            info->iEncodersCount = 0;
            info->iBasicEncoderCount = 0;
            info->iPWMCount = 0;
            break;

        // PoPLC58
        case 50:
            info->iPinCount = 27;
            info->iEncodersCount = 0;
            info->iPWMCount = 0;
            info->iBasicEncoderCount = 0;
            break;

		default:
			info->iPinCount = 0;
			info->iBasicEncoderCount = 0;
			info->iEncodersCount = 0;
			info->iPWMCount = 0;

			break;
    }

    if (devEth)
    {
        device->netDeviceData = (sPoKeysNetworkDeviceInfo *)malloc(sizeof(sPoKeysNetworkDeviceInfo));

        // Get network device information...
        CreateRequest(device->request, 0xE0, 0, 0, 0, 0);
        if (SendRequest(device) == PK_OK)
        {
            device->netDeviceData->DHCP = device->response[8];

            memcpy(device->netDeviceData->IPAddressSetup, device->response + 9, 4);
            memcpy(device->netDeviceData->IPAddressCurrent, device->response + 13, 4);

            device->netDeviceData->TCPtimeout = (unsigned short)device->response[17] + ((unsigned short)device->response[18] << 8);

            memcpy(device->netDeviceData->DefaultGateway, device->response + 19, 4);
            memcpy(device->netDeviceData->Subnetmask, device->response + 23, 4);

            if ((device->response[27] & 0xA0) == 0xA0)
            {
                device->netDeviceData->AdditionalNetworkOptions = device->response[27];
            }
            else
            {
                device->netDeviceData->AdditionalNetworkOptions = 0;
            }
        } else return PK_ERR_TRANSFER;
    } else
    {
        device->netDeviceData = 0;
    }

    if (!devSeries58)
    {
        // Read device name
        CreateRequest(device->request, 0x06, 0, 0, 0, 0);
        if (SendRequest(device) == PK_OK)
        {
            for (i = 0; i < 10; i++)
            {
                data->DeviceName[i] = device->response[8 + i];
            }
        } else return PK_ERR_TRANSFER;
    }

	// If the device name is empty, rewrite the name with the type name
    if (strlen(data->DeviceName) == 0)
	{
        strcpy(data->DeviceName, data->DeviceTypeName);
	}

    if (!devSeries58)
    {
        // Read firmware build date
        CreateRequest(device->request, 0x04, 0, 0, 0, 0);
        if (SendRequest(device) == PK_OK)
        {
            for (i = 0; i < 4; i++)	data->BuildDate[i + 0] = device->response[2 + i];
        } else return PK_ERR_TRANSFER;

        CreateRequest(device->request, 0x04, 1, 0, 0, 0);
        if (SendRequest(device) == PK_OK)
        {
            for (i = 0; i < 4; i++)	data->BuildDate[i + 4] = device->response[2 + i];
        } else return PK_ERR_TRANSFER;

        CreateRequest(device->request, 0x04, 2, 0, 0, 0);
        if (SendRequest(device) == PK_OK)
        {
            for (i = 0; i < 3; i++)	data->BuildDate[i + 8] = device->response[2 + i];
            data->BuildDate[11] = 0;
        } else return PK_ERR_TRANSFER;
    }


	// Check device capabilities
	if (!devBootloader)
	{
        if (!devSeries58)
        {
            if (devUSB)						info->iKeyMapping = 1;
            if (devUSB && !devSeries27)		info->iTriggeredKeyMapping = 1;
            if (devUSB && !devSeries27)		info->iKeyRepeatDelay = 1;
            if (devSeries56)				info->iDigitalCounters = 1;
            if (devUSB)						info->iJoystickButtonAxisMapping = 1;
            if (devUSB)						info->iJoystickAnalogToDigitalMapping = 1;
            if (devSeries55 || devSeries56)	info->iFastEncoders = 3;
            if (devSeries56)				info->iUltraFastEncoders = 1;
            if (devUSB)						info->iMacros = 1;
                                            info->iMatrixKeyboard = 1;
            if (devUSB)						info->iMatrixKeyboardTriggeredMapping = 1;
            if (devSeries56)				info->iPoNET = 1;
            if (!devSeries27)				info->iLCD = 1;
            if (!devSeries27)				info->iMatrixLED = 2;
            if (!devSeries27)				info->iConnectionSignal = 1;
            if (!devSeries27)				info->iPoExtBus = 10;
            if (!devSeries55)				info->iInitOutputsStart = 1;
            if (devSeries56 || devSeries27) info->iprotI2C = 1;
            if (devSeries56)				info->iprot1wire = 1;
            if (devSeries56 && !(data->FirmwareVersionMajor == 32 && data->FirmwareVersionMinor < 13)) info->iAdditionalOptions = 1;
            if (!devSeries27)				info->iCustomDeviceName = 1;
            if (devSeries56 || devSeries27) info->iPoTLog27support = 1;
            if (devSeries56 || devSeries27) info->iSensorList = 1;
            if (devEth)						info->iWebInterface = 1;
            if (devSeries56)				info->iFailSafeSettings = 1;
            if (devSeries56 && devUSB)		info->iJoystickHATswitch = 1;
        }
		if (1)							info->iAnalogInputs = 1;
		if (1)	  						info->iAnalogFiltering = 1;
		if (!devSeries27)				info->iLoadStatus = 1;
	}

	// Read activated options
    CreateRequest(device->request, 0x8F, 0, 0, 0, 0);
	if (SendRequest(device) == PK_OK)
    {
		data->ActivatedOptions = device->response[8];
	} else return PK_ERR_TRANSFER;

    // Firmware < 3.0.59
    if (data->FirmwareVersionMajor == 32 && data->FirmwareVersionMinor < 59)
    {
        if (data->ActivatedOptions & 1) info->iPulseEngine = 1;
    } else if (data->FirmwareVersionMajor == 32 && data->FirmwareVersionMinor >= 59)
    {
        // On 3.0.59 and on, Pulse engine is automatically activated
        info->iPulseEngine = 1;
    } else if (data->FirmwareVersionMajor == 33)
    {
        // On 3.1.0 and on, Pulse engine v2 is automatically activated
        info->iPulseEnginev2 = 1;
    }

	return PK_OK;
}

int32_t PK_DeviceNameSet(sPoKeysDevice* device)
{
    uint32_t i;

    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    CreateRequest(device->request, 0x06, 0x01, 0, 0, 0);

    for (i = 0; i < 10; i++)
    {
        device->request[8+i] = device->DeviceData.DeviceName[i];
    }

    if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

    return PK_OK;
}

int32_t PK_NetworkConfigurationSet(sPoKeysDevice* device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    CreateRequest(device->request, 0xE0, 10, 0, 0, 0);

    device->request[8] = device->netDeviceData->DHCP;

    memcpy(device->request + 9, device->netDeviceData->IPAddressSetup, 4);
    memcpy(device->request + 13, device->netDeviceData->IPAddressCurrent, 4);

    device->request[17] = device->netDeviceData->TCPtimeout & 0xFF;
    device->request[18] = (device->netDeviceData->TCPtimeout >> 8) & 0xFF;

    memcpy(device->request + 19, device->netDeviceData->DefaultGateway, 4);
    memcpy(device->request + 23, device->netDeviceData->Subnetmask, 4);

    device->request[27] = 1; // This request supports subnet and gateway
    device->request[28] = 0xA0 | (device->netDeviceData->AdditionalNetworkOptions & 0x0F);

    if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

    return PK_OK;
}


int32_t PK_DeviceActivation(sPoKeysDevice* device)
{
	if (device == NULL) return PK_ERR_NOT_CONNECTED;

	// Send new activation code
    CreateRequest(device->request, 0x8F, 0x01, 0, 0, 0);
	memcpy(&(device->request[8]), device->DeviceData.ActivationCode, 8);
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	device->DeviceData.ActivatedOptions = device->response[8];

	return PK_OK;
}

int32_t PK_DeviceActivationClear(sPoKeysDevice* device)
{
	if (device == NULL) return PK_ERR_NOT_CONNECTED;

	// Send new activation code
    CreateRequest(device->request, 0x8F, 0xFF, 0, 0, 0);
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	device->DeviceData.ActivatedOptions = device->response[8];

	return PK_OK;
}

int32_t PK_SaveConfiguration(sPoKeysDevice* device)
{
	if (device == NULL) return PK_ERR_NOT_CONNECTED;

    CreateRequest(device->request, 0x50, 0xAA, 0x55, 0, 0);
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	return PK_OK;
}

int32_t PK_ClearConfiguration(sPoKeysDevice* device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    CreateRequest(device->request, 0x52, 0xAA, 0x55, 0, 0);
    if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

    return PK_OK;
}

int32_t PK_CheckPinCapabilityByDevice(long deviceTypeMask, unsigned int pin, ePK_AllPinCap cap)
{
    const sPoKeys_PinCapabilities * ptr;

    ptr = &pinCaps[0];

    while (ptr->cap != -1)
    {
        if ((ptr->devTypes & deviceTypeMask) && (ptr->cap == cap))
        {
            if (pin + 1 >= ptr->pinStart &&
                pin + 1 <= ptr->pinEnd)
            {
                if (ptr->additionalCheck == 0) return 1;
                switch (ptr->cap)
                {
                    case PK_AllPinCap_digitalCounter:
                        return PK_IsCounterAvailableByDevice(deviceTypeMask, pin);

                    case PK_AllPinCap_fastEncoder1I:
                    case PK_AllPinCap_fastEncoder2I:
                    case PK_AllPinCap_fastEncoder3I:
                        if (deviceTypeMask & PK_DeviceMask_56) return 1; else return 0;

                    case PK_AllPinCap_fastEncoder2A:
                        if (deviceTypeMask & PK_DeviceMask_56) return 1; else return 0;
                        break;
                    case PK_AllPinCap_fastEncoder2B:
                        if (deviceTypeMask & PK_DeviceMask_56) return 1; else return 0;
                        break;
                }
            }
        }
        ptr++;
    }


    return 0;
}




int32_t PK_CheckPinCapability(sPoKeysDevice* device, unsigned int pin, ePK_AllPinCap cap)
{
    const sPoKeys_PinCapabilities * ptr;

    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    ptr = &pinCaps[0];

    while (ptr->cap != -1)
    {
        if ((device->DeviceData.DeviceTypeID & ptr->devTypes) && (ptr->cap == cap))
        {
            if (pin + 1 >= ptr->pinStart &&
                pin + 1 <= ptr->pinEnd)
            {
                if (ptr->additionalCheck == 0) return 1;
                switch (ptr->cap)
                {
                    case PK_AllPinCap_digitalCounter:
                        return PK_IsCounterAvailable(device, pin);

                    case PK_AllPinCap_fastEncoder1I:
                    case PK_AllPinCap_fastEncoder2I:
                    case PK_AllPinCap_fastEncoder3I:
                        if (device->FastEncodersOptions == 1) return 1;
                        break;

                    case PK_AllPinCap_fastEncoder2A:
                        if (device->FastEncodersConfiguration == 1 && pin == 2) return 1;
                        else if (device->FastEncodersConfiguration == 10 && pin == 4) return 1;
                        break;
                    case PK_AllPinCap_fastEncoder2B:
                        if (device->FastEncodersConfiguration == 1 && pin == 3) return 1;
                        else if (device->FastEncodersConfiguration == 10 && pin == 5) return 1;
                        break;
                }
            }
        }

        ptr++;
    }


    return 0;
}


int32_t PK_CheckPinEnabledCapability(sPoKeysDevice* device, unsigned int pin, ePK_AllPinCap cap)
{
    return 0;
}
