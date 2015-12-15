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

#include "Public/Common/Common.h"

#if defined(__APPLE__)

#include <mach/mach_time.h>

FORCEINLINE LARGE_INTEGER  StartProfiling()
{
    LARGE_INTEGER res;
    res.QuadPart = mach_absolute_time();
    return res;    
}

FORCEINLINE double  EndProfiling(LARGE_INTEGER start)
{
    LARGE_INTEGER res;
    res.QuadPart = mach_absolute_time() - start.QuadPart;
    
    static bool bInit = true;
    static mach_timebase_info_data_t info;
    
    if (bInit)
    {
      bInit = false;
      mach_timebase_info(&info);
    }
    
    double r = res.QuadPart;
    r = r * info.numer / info.denom;
    r /= 1000000.0f;
    
    return r;
}



#else


#if defined(TARGET_OS_ANDROID) || defined(TARGET_OS_EMSCRIPTEN) || defined(TARGET_OS_LINUX)

FORCEINLINE LARGE_INTEGER  StartProfiling()
{
    struct timeval now;
    struct timezone zone;

    gettimeofday(&now, &zone);

	return now;

}


FORCEINLINE double  EndProfiling(LARGE_INTEGER start)
{
    struct timeval now;
    struct timezone zone;

    gettimeofday(&now, &zone);

	  double elapsed = (now.tv_sec - start.tv_sec) * 1000.0 + 
              ((now.tv_usec - start.tv_usec)/1000.0);

    return elapsed;
}

#endif

#if defined(TARGET_OS_FLASH)

FORCEINLINE LARGE_INTEGER  StartProfiling()
{
  struct timeval now;
  struct timezone zone;

  gettimeofday(&now, &zone);

  return now;

}


FORCEINLINE double  EndProfiling(LARGE_INTEGER start)
{
  struct timeval now;
  struct timezone zone;

  gettimeofday(&now, &zone);

  double elapsed = (now.tv_sec - start.tv_sec) * 1000.0 + 
    ((now.tv_usec - start.tv_usec)/1000.0);

  return elapsed;
}

#endif



#ifdef _WIN64
LARGE_INTEGER _inline StartProfiling()
{
	LARGE_INTEGER start;//, stop, freq;
	QueryPerformanceCounter(&start);

	return start;
};

double _inline EndProfiling(LARGE_INTEGER start)
{
	LARGE_INTEGER stop;

  static __int64 freq = 0;

	QueryPerformanceCounter(&stop);
  if (!freq)
	  QueryPerformanceFrequency((LARGE_INTEGER*)&freq);

	double sec = (double)((__int64&)stop - (__int64&)start) / (double)((__int64&)freq);

	return sec * 1000.;	// to milliseconds
};

//extern 
#else
//#include <intrin.h>
//#pragma intrinsic(__rdtsc)
#ifdef _WIN32
extern __int64 _profiler_freq;
extern void CalculateFrequency(__int64 * freq);

_inline __int64 _rdtsc() {

  __int64 x;
  _asm {
    rdtsc
    mov dword ptr x,eax
    mov dword ptr x[4],edx
  };

  return x;
}

LARGE_INTEGER _inline StartProfiling()
{
  __int64 start = _rdtsc();//, stop, freq;
  return (LARGE_INTEGER&)start;
};

double _inline EndProfiling(LARGE_INTEGER start)
{
  __int64 stop = _rdtsc();

  static __int64 freq = 0;

  if (!_profiler_freq)
    //if(!QueryPerformanceFrequency((LARGE_INTEGER*)&_profiler_freq))
			CalculateFrequency(&_profiler_freq);

  double sec = (double)(stop - (__int64&)start) / (double)(_profiler_freq);

  return sec * 1000.0;	// to milliseconds
};

//#endif

//#ifndef _WIN64
DWORD _inline StartTickProfiling()
{
	DWORD dwStart;
	_asm{
	RDTSC 
	mov dwStart, eax
	}
	return dwStart;
}

DWORD _inline EndTickProfiling(DWORD dwStart)
{
	DWORD dwEnd;
	_asm{
	RDTSC
	sub eax, dwStart
	mov dwEnd, eax
	}
	return dwEnd;
}
#endif
#endif
#endif

