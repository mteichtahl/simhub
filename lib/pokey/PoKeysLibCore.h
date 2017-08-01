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

#include "hidapi.h"
#include <stdio.h>
#include <string.h>

#ifndef __POKEYSLIBCORE
	#define __POKEYSLIBCORE

	void InitializeNewDevice(sPoKeysDevice* device);
	void CleanDevice(sPoKeysDevice* device);
	void PK_DisconnectNetworkDevice(sPoKeysDevice* device);

	int CreateRequest(unsigned char * request, unsigned char type, unsigned char param1, unsigned char param2, unsigned char param3, unsigned char param4);
	unsigned char getChecksum(unsigned char * data);
	int SendRequest(sPoKeysDevice * device);


#endif
