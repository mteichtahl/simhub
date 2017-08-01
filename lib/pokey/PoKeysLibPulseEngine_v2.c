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

#include "PoKeysLib.h"
#include "PoKeysLibCore.h"


void PK_PEv2_DecodeStatus(sPoKeysDevice * device)
{
    uint8_t * ans;
    if (device == NULL) return;

    ans = device->response;

    device->PEv2.SoftLimitStatus = ans[3];
    device->PEv2.AxisEnabledStatesMask = ans[4];
    device->PEv2.LimitOverride = ans[5];

    // Basic engine states
    device->PEv2.PulseEngineEnabled = ans[8];
    device->PEv2.PulseEngineActivated = ans[9];
    device->PEv2.PulseEngineState = ans[10];
    device->PEv2.ChargePumpEnabled = ans[11];
    device->PEv2.PulseGeneratorType = ans[15];

    // Switch states
    device->PEv2.LimitStatusP = ans[12];
    device->PEv2.LimitStatusN = ans[13];
    device->PEv2.HomeStatus = ans[14];

    memcpy(device->PEv2.AxesState, ans + 16, 8);
    memcpy(device->PEv2.CurrentPosition, ans + 24, 8*4);

    // Engine info
    device->PEv2.info.nrOfAxes = ans[56];
    device->PEv2.info.maxPulseFrequency = ans[57];
    device->PEv2.info.bufferDepth = ans[58];
    device->PEv2.info.slotTiming = ans[59];

    device->PEv2.EmergencySwitchPolarity = ans[60];

    // Other inputs
    device->PEv2.ErrorInputStatus = ans[61];
    device->PEv2.MiscInputStatus = ans[62];
}

int32_t PK_PEv2_StatusGet(sPoKeysDevice * device)
{
    // Do some 'random' magic with numbers
    uint8_t tstB;
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    tstB = (0x10 + device->requestID) % 199;

    // Send request
    CreateRequest(device->request, 0x85, 0x00, tstB, 0, 0);
    if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

    // Check if response is valid
    if (device->response[63] == (uint8_t)(tstB + 0x5A))
    {
        // Decode status
        PK_PEv2_DecodeStatus(device);
        return PK_OK;
    } else
    {
        device->PEv2.PulseEngineActivated = 0;
        device->PEv2.PulseEngineEnabled = 0;
        return PK_ERR_GENERIC;
    }

}

// Configure (setup) the pulse engine
int32_t PK_PEv2_PulseEngineSetup(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    CreateRequest(device->request, 0x85, 0x01, 0, 0, 0);

    // Fill the information
    device->request[8] = device->PEv2.PulseEngineEnabled;
    device->request[9] = device->PEv2.ChargePumpEnabled;
    device->request[10] = device->PEv2.PulseGeneratorType;
    device->request[11] = device->PEv2.PulseEngineBufferSize;
    device->request[12] = device->PEv2.EmergencySwitchPolarity;
    device->request[13] = device->PEv2.AxisEnabledStatesMask;

    // Send request
    return SendRequest(device);
}


// Retrieve single axis parameters. Axis ID is in param1
int32_t PK_PEv2_AxisConfigurationGet(sPoKeysDevice * device)
{
    sPoKeysPEv2 * pe;
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    if (device->PEv2.param1 >= 8) return PK_ERR_PARAMETER;

    // Send request
    CreateRequest(device->request, 0x85, 0x10, device->PEv2.param1, 0, 0);
    if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

    // Pointer to PEv2 structure for better code readability
    pe = &device->PEv2;

    // Read the structure
    pe->AxesConfig[pe->param1] = device->response[8];
    pe->AxesSwitchConfig[pe->param1] = device->response[9];

    pe->PinHomeSwitch[pe->param1] = device->response[10];
    pe->PinLimitMSwitch[pe->param1] = device->response[11];
    pe->PinLimitPSwitch[pe->param1] = device->response[12];

    pe->HomingSpeed[pe->param1] = device->response[13];
    pe->HomingReturnSpeed[pe->param1] = device->response[14];

    pe->MPGjogEncoder[pe->param1] = device->response[15];

    // Convert parameters... assume little-endian format
    pe->MaxSpeed[pe->param1] = *(float*)(device->response + 16);
    pe->MaxAcceleration[pe->param1] = *(float*)(device->response + 20);
    pe->MaxDecceleration[pe->param1] = *(float*)(device->response + 24);

    pe->SoftLimitMinimum[pe->param1] = *(int32_t*)(device->response + 28);
    pe->SoftLimitMaximum[pe->param1] = *(int32_t*)(device->response + 32);

    pe->MPGjogMultiplier[pe->param1] = *(int16_t*)(device->response + 36);

    pe->AxisEnableOutputPins[pe->param1] = device->response[38];
    pe->InvertAxisEnable[pe->param1] = device->response[39];

    return PK_OK;
}

// Set single axis parameters. Axis ID is in param1
int32_t PK_PEv2_AxisConfigurationSet(sPoKeysDevice * device)
{
    sPoKeysPEv2 * pe;
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    if (device->PEv2.param1 >= 8) return PK_ERR_PARAMETER;

    // Create request
    CreateRequest(device->request, 0x85, 0x11, device->PEv2.param1, 0, 0);

    // Pointer to PEv2 structure for better code readability
    pe = &device->PEv2;

    // Fill the structure
    device->request[8] = pe->AxesConfig[pe->param1];
    device->request[9] = pe->AxesSwitchConfig[pe->param1];

    device->request[10] = pe->PinHomeSwitch[pe->param1];
    device->request[11] = pe->PinLimitMSwitch[pe->param1];
    device->request[12] = pe->PinLimitPSwitch[pe->param1];

    device->request[13] = pe->HomingSpeed[pe->param1];
    device->request[14] = pe->HomingReturnSpeed[pe->param1];

    device->request[15] = pe->MPGjogEncoder[pe->param1];

    *(float*)(device->request + 16) = pe->MaxSpeed[pe->param1];
    *(float*)(device->request + 20) = pe->MaxAcceleration[pe->param1];
    *(float*)(device->request + 24) = pe->MaxDecceleration[pe->param1];

    *(int32_t*)(device->request + 28) = pe->SoftLimitMinimum[pe->param1];
    *(int32_t*)(device->request + 32) = pe->SoftLimitMaximum[pe->param1];
    *(int16_t*)(device->request + 36) = (int16_t)pe->MPGjogMultiplier[pe->param1];

    device->request[38] = pe->AxisEnableOutputPins[pe->param1];
    device->request[39] = pe->InvertAxisEnable[pe->param1];

    // Send request
    return SendRequest(device);
}

// Set positions - param2 is used for bit-mapped axis selection
int32_t PK_PEv2_PositionSet(sPoKeysDevice * device)
{
    int i;
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    if (device->PEv2.param2 == 0) return PK_ERR_PARAMETER;

    // Create request
    CreateRequest(device->request, 0x85, 0x03, device->PEv2.param2, 0, 0);

    for (i = 0; i < 8; i++)
    {
        *(int32_t*)(&device->request[8+i*4]) = device->PEv2.PositionSetup[i];
    }

    // Send request
    return SendRequest(device);
}

// Set pulse engine state
int32_t PK_PEv2_PulseEngineStateSet(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Create request
    CreateRequest(device->request, 0x85, 0x02, device->PEv2.PulseEngineStateSetup, device->PEv2.LimitOverrideSetup, 0);

    // Send request
    return SendRequest(device);
}

// Execute the move. Position or speed is specified by the ReferencePositionSpeed
int32_t PK_PEv2_PulseEngineMove(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Create request
    CreateRequest(device->request, 0x85, 0x20, 0, 0, 0);

    memcpy(&device->request[8], device->PEv2.ReferencePositionSpeed, 8*4);

    // Send request
    return SendRequest(device);
}

// Read external outputs state - save them to ExternalRelayOutputs and ExternalOCOutputs
int32_t PK_PEv2_ExternalOutputsGet(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Send request
    CreateRequest(device->request, 0x85, 0x04, 0, 0, 1);
    if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

    device->PEv2.ExternalRelayOutputs = device->response[3];
    device->PEv2.ExternalOCOutputs = device->response[4];

    return PK_OK;
}

// Set external outputs state (from ExternalRelayOutputs and ExternalOCOutputs)
int32_t PK_PEv2_ExternalOutputsSet(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Create request
    CreateRequest(device->request, 0x85, 0x04, device->PEv2.ExternalRelayOutputs, device->PEv2.ExternalOCOutputs, 0);
    // Send request
    return SendRequest(device);
}

// Transfer motion buffer to device. The number of new entries (newMotionBufferEntries) must be specified
// The number of accepted entries is saved to motionBufferEntriesAccepted.
// In addition, pulse engine state is read (PEv2_GetStatus)
int32_t PK_PEv2_BufferFill(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Create request
    CreateRequest(device->request, 0x85, 0xFF, device->PEv2.newMotionBufferEntries, device->PEv2.PulseEngineEnabled & 0x0F, 0);

    // Copy buffer
    memcpy(&device->request[8], device->PEv2.MotionBuffer, 56);

    // Send request
    if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

    device->PEv2.motionBufferEntriesAccepted = device->response[2];

    // Decode status
    PK_PEv2_DecodeStatus(device);

    return PK_OK;
}

// Clear motion buffer in device
int32_t PK_PEv2_BufferClear(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Create request
    CreateRequest(device->request, 0x85, 0xF0, 0, 0, 0);
    // Send request
    return SendRequest(device);
}

// Reboot pulse engine v2
int32_t PK_PEv2_PulseEngineReboot(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Create request
    CreateRequest(device->request, 0x85, 0x05, 0, 0, 0);
    // Send request
    return SendRequest(device);
}

// Start the homing procedure. Home offsets must be provided in the HomeOffsets
// Axes to home are selected as bit-mapped HomingStartMaskSetup value
int32_t PK_PEv2_HomingStart(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Create request
    CreateRequest(device->request, 0x85, 0x21, device->PEv2.HomingStartMaskSetup, 0, 0);

    memcpy(&device->request[8], device->PEv2.HomeOffsets, 8 * 4);

    // Send request
    return SendRequest(device);
}

// Finish the homing procedure
int32_t PK_PEv2_HomingFinish(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Create request
    CreateRequest(device->request, 0x85, 0x22, 0, 0, 0);
    // Send request
    return SendRequest(device);
}

// Star the probing procedure.
// ProbeMaxPosition defines the maximum position in position ticks where probing error will be thrown
// ProbeSpeed defines the probing speed (1 = max speed)
// ProbeInput defines the extenal input (values 1-8) or PoKeys pin (0-based Pin ID + 9)
// ProbeInputPolarity defines the polarity of the probe signal
int32_t PK_PEv2_ProbingStart(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Create request
    CreateRequest(device->request, 0x85, 0x23, device->PEv2.ProbeStartMaskSetup, 0, 0);

    memcpy(&device->request[8], device->PEv2.ProbeMaxPosition, 8 * 4);
    *(float*)(&device->request[40]) = device->PEv2.ProbeSpeed;
    device->request[44] = device->PEv2.ProbeInput;
    device->request[45] = device->PEv2.ProbeInputPolarity;

    // Send request
    return SendRequest(device);
}

// Finish the probing procedure. Probe position and status are saved to ProbePosition and ProbeStatus
int32_t PK_PEv2_ProbingFinish(sPoKeysDevice * device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Create request
    CreateRequest(device->request, 0x85, 0x24, 0, 0, 0);

    // Send request
    if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

    // Copy the probe result position
    memcpy(device->PEv2.ProbePosition, &device->response[8], 8*4);
    device->PEv2.ProbeStatus = device->response[40];

    return PK_OK;
}
