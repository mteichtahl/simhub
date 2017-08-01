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

int PK_LCDConfigurationGet(sPoKeysDevice* device)
{	
	// Get LCD configuration
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    CreateRequest(device->request, 0xD0, 1, 0, 0, 0);
	if (SendRequest(device) == PK_OK)
    {
		device->LCD.Configuration = device->response[3];
		device->LCD.Rows = device->response[4];
		device->LCD.Columns = device->response[5];
	} else return PK_ERR_TRANSFER;

	return PK_OK;
}

int PK_LCDConfigurationSet(sPoKeysDevice* device)
{
    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    // Set LCD configuration
    CreateRequest(device->request, 0xD0, 0, device->LCD.Configuration, device->LCD.Rows, device->LCD.Columns);
	if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

    // Initialize LCD
    CreateRequest(device->request, 0xD1, 0, 0, 0, 0);
    if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;

    // Clear LCD
    CreateRequest(device->request, 0xD1, 0x10, 0, 0, 0);
    if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;


	return PK_OK;
}

int PK_LCDUpdate(sPoKeysDevice* device)
{
    unsigned char * lines[4];
	int i, n;

    if (device == NULL) return PK_ERR_NOT_CONNECTED;

    lines[0] = device->LCD.line1;
    lines[1] = device->LCD.line2;
    lines[2] = device->LCD.line3;
    lines[3] = device->LCD.line4;

	// Update LCD contents
	for (n = 0; n < 4; n++)
	{
		if (device->LCD.RowRefreshFlags & (1<<n))
		{
			CreateRequest(device->request, 0xD1, 0x85, n + 1, 0, 0);
			for (i = 0; i < 20; i++)
			{
                device->request[8 + i] = lines[n][i];
			}
			if (SendRequest(device) != PK_OK) return PK_ERR_TRANSFER;
			device->LCD.RowRefreshFlags &= ~(1<<n);
		}
	}
	return PK_OK;
}
