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

#define PLATFORM_PC
//#define LOG g_pApplication->AddToLog

#include <stdio.h>

#define WIN_HWND HWND
#define WIN_HINSTANCE HINSTANCE

inline void _debugbreak()
{
  __debugbreak();
}

namespace Engine2
{
  namespace Platform
  {
    FORCEINLINE errno_t  fopen_s( FILE ** _File,  const char * _Filename,  const char * _Mode)
    {
      return ::fopen_s(_File, _Filename, _Mode);
    }
  }
}