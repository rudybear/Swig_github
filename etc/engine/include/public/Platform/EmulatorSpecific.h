#pragma once

#define PLATFORM_PC
//#define LOG g_pApplication->AddToLog

#include <stdio.h>

#define WIN_HWND HWND
#define WIN_HINSTANCE HINSTANCE

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