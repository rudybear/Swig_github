////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_DEPRECATE


#define _USE_RTM_VERSION


#if !defined(__APPLE__)
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <windows.h>
#include <hash_map>
#endif

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <assert.h>
#pragma warning(disable : 4995)

namespace Engine2
{

};

using namespace Engine2;