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

// Read pulse engine info
int PK_PEInfoGet(sPoKeysDevice* device)
{
    sPoKeysPEinfo * info = &device->PulseEngine->info;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x30, 0, 0, 0);
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	info->nrOfAxes = device->response[8];
	info->maxPulseFrequency = device->response[9];
	info->bufferDepth = device->response[10];
	info->slotTiming = device->response[11];

	return PK_OK;
}

// Read Pulse engine status
int PK_PEStatusGet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0, 0, 0, 0);
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	memcpy(&PE->CurrentPosition[0], &(device->response[8]), 4);
	memcpy(&PE->CurrentPosition[1], &(device->response[12]), 4);
	memcpy(&PE->CurrentPosition[2], &(device->response[16]), 4);
	
	PE->LimitStatusP = device->response[20];
	PE->LimitStatusN = device->response[21];
	PE->HomeStatus = device->response[22];
	PE->PulseEngineState = device->response[23];

	PE->AxisState[0] = device->response[24];
	PE->AxisState[1] = device->response[25];
	PE->AxisState[2] = device->response[26];

	PE->PulseEngineEnabled = device->response[27];
	PE->ChargePumpEnabled = device->response[28];

	return PK_OK;
}

// Set Pulse engine status
int PK_PEStatusSet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x06, PE->PulseEngineEnabled, PE->ChargePumpEnabled, 0);
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	return PK_OK;
}

// Set current position
int PK_PECurrentPositionSet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x01, 0, 0, 0);
	memcpy(&(device->request[8]), &PE->CurrentPosition[0], 4);
	memcpy(&(device->request[12]), &PE->CurrentPosition[1], 4);
	memcpy(&(device->request[16]), &PE->CurrentPosition[2], 4);
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	return PK_OK;
}

// Read Pulse engine axis configuration
int PK_PEAxisConfigurationGet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x12, 0, 0, 0);
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	PE->LimitConfigP = device->response[8];
	PE->LimitConfigN = device->response[9];
	PE->HomeConfig = device->response[10];

	PE->DirectionChange = device->response[11];
	PE->HomingDirectionChange = device->response[12];

	return PK_OK;
}

// Set Pulse engine axis configuration
int PK_PEAxisConfigurationSet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x13, 0, 0, 0);

	device->request[8] = PE->LimitConfigP;
	device->request[9] = PE->LimitConfigN;
	device->request[10] = PE->HomeConfig;

	device->request[11] = PE->DirectionChange;
	device->request[12] = PE->HomingDirectionChange;

	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;


	return PK_OK;
}

// Read Pulse engine keyboard configuration
int PK_PEKeyboardConfigurationGet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x14, 0, 0, 0);
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	PE->kb48CNCenabled = device->response[8];

	return PK_OK;
}

// Set Pulse engine keyboard configuration
int PK_PEKeyboardConfigurationSet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x15, 0, 0, 0);
	device->request[8] = PE->kb48CNCenabled;
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;


	return PK_OK;
}

// Set Pulse engine state
int PK_PEStateSet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x02, 0, 0, 0);
	device->request[8] = PE->PulseEngineState;
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;


	return PK_OK;
}

// Execute homing
int PK_PEHomingStart(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x20, 0, 0, 0);
	device->request[8] = (PE->AxesHomingFlags & 1) > 0 ? 1 : 0;
	device->request[9] = (PE->AxesHomingFlags & 2) > 0 ? 1 : 0;
	device->request[10] = (PE->AxesHomingFlags & 4) > 0 ? 1 : 0;
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	return PK_OK;
}

// Get parameters
int PK_PEParametersGet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x10, 0, 0, 0);
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	PE->MaxSpeed[0] = (uint32_t)(1e3 * (*(float *)&device->response[8]));
	PE->MaxSpeed[1] = (uint32_t)(1e3 * (*(float *)&device->response[12]));
	PE->MaxSpeed[2] = (uint32_t)(1e3 * (*(float *)&device->response[16]));

	PE->MaxAcceleration[0] = (uint32_t)(1e6 * (*(float *)&device->response[20]));
	PE->MaxAcceleration[1] = (uint32_t)(1e6 * (*(float *)&device->response[24]));
	PE->MaxAcceleration[2] = (uint32_t)(1e6 * (*(float *)&device->response[28]));

	PE->MaxDecceleration[0] = (uint32_t)(1e6 * (*(float *)&device->response[32]));
	PE->MaxDecceleration[1] = (uint32_t)(1e6 * (*(float *)&device->response[36]));
	PE->MaxDecceleration[2] = (uint32_t)(1e6 * (*(float *)&device->response[40]));

	PE->HomingSpeed = device->response[44];
	PE->HomingReturnSpeed = device->response[45];
	PE->EmergencySwitchPolarity = device->response[46];

	return PK_OK;
}

// Set parameters
int PK_PEParametersSet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x11, 0, 0, 0);

	(*(float *)&device->request[8]) = (float)((float)PE->MaxSpeed[0] / 1e3);
	(*(float *)&device->request[12]) = (float)((float)PE->MaxSpeed[1] / 1e3);
	(*(float *)&device->request[16]) = (float)((float)PE->MaxSpeed[2] / 1e3);

	(*(float *)&device->request[20]) = (float)((float)PE->MaxAcceleration[0] / 1e6);
	(*(float *)&device->request[24]) = (float)((float)PE->MaxAcceleration[1] / 1e6);
	(*(float *)&device->request[28]) = (float)((float)PE->MaxAcceleration[2] / 1e6);

	(*(float *)&device->request[32]) = (float)((float)PE->MaxDecceleration[0] / 1e6);
	(*(float *)&device->request[36]) = (float)((float)PE->MaxDecceleration[1] / 1e6);
	(*(float *)&device->request[40]) = (float)((float)PE->MaxDecceleration[2] / 1e6);

	device->request[44] = PE->HomingSpeed;
	device->request[45] = PE->HomingReturnSpeed;
	device->request[46] = PE->EmergencySwitchPolarity;

	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	return PK_OK;
}

// Execute move
int PK_PEMove(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x05, 0, 0, 0);

	memcpy(&device->request[8], PE->ReferencePosition, 12); // 3 axes, 4 bytes per axis
	
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	return PK_OK;
}

// Fill motion buffer and read pulse engine status
int PK_PEBufferFill(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;
    int bufferSize = PE->info.bufferDepth;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x35, PE->buffer.newEntries, 0, 0);	

	if (bufferSize > 55) bufferSize = 55;
	memcpy(&device->request[8], PE->buffer.buffer, bufferSize);

	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;



	PE->buffer.entriesAccepted = device->response[8];

	memcpy(&PE->CurrentPosition[0], &(device->response[9]), 4);
	memcpy(&PE->CurrentPosition[1], &(device->response[13]), 4);
	memcpy(&PE->CurrentPosition[2], &(device->response[17]), 4);

	PE->LimitStatusP = device->response[21];
	PE->LimitStatusN = device->response[22];
	PE->HomeStatus = device->response[23];
	PE->PulseEngineState = device->response[24];

	PE->AxisState[0] = device->response[25];
	PE->AxisState[1] = device->response[26];
	PE->AxisState[2] = device->response[27];

	return PK_OK;
}

// Flush motion buffer
int PK_PEBufferFlush(sPoKeysDevice* device)
{
	if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x36, 0, 0, 0);	
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	return PK_OK;
}

// Get the buffer free size
int PK_PEBufferFreeSizeGet(sPoKeysDevice* device)
{
	if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x37, 0, 0, 0);	
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	device->PulseEngine->buffer.FreeBufferSize = device->response[8];

	return PK_OK;
}

// Get MPG jog configuration
int PK_PEMPGJogConfigurationGet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x03, 0, 0, 0);	
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	PE->MPGjogActivated = device->response[8];

	PE->MPGjogMultiplier[0] = *(uint32_t *)(&device->response[9]);
	PE->MPGjogMultiplier[1] = *(uint32_t *)(&device->response[13]);
	PE->MPGjogMultiplier[2] = *(uint32_t *)(&device->response[17]);

	PE->MPGaxisEncoder[0] = device->response[21];
	PE->MPGaxisEncoder[1] = device->response[22];
	PE->MPGaxisEncoder[2] = device->response[23];

	return PK_OK;
}

// Set MPG jog configuration
int PK_PEMPGJogConfigurationSet(sPoKeysDevice* device)
{
    sPoKeysPE * PE = device->PulseEngine;

    if (device->info.iPulseEngine == 0) return PK_ERR_GENERIC;

	CreateRequest(device->request, 0x80, 0x03, 10, 0, 0);

	device->request[8] = PE->MPGjogActivated;

	*(uint32_t *)(&device->request[9]) = PE->MPGjogMultiplier[0];
	*(uint32_t *)(&device->request[13]) = PE->MPGjogMultiplier[1];
	*(uint32_t *)(&device->request[17]) = PE->MPGjogMultiplier[2];

	device->request[21] = PE->MPGaxisEncoder[0];
	device->request[22] = PE->MPGaxisEncoder[1];
	device->request[23] = PE->MPGaxisEncoder[2];

	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

	return PK_OK;
}
