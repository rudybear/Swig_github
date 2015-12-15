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

#if defined(_WIN32) || (_WIN64)
  #define TARGET_OS_WIN
  #include "WinSpecific.h"
#endif

#if defined(__APPLE__)
#define TARGET_OS_POSIX
    #if defined (__MAC_OS_X_VERSION_MAX_ALLOWED) //&& (defined(TARGET_OS_MAC) || defined(__APPLE_CC__)
        #ifndef TARGET_OS_MAC 
            #define TARGET_OS_MAC 1
        #endif
        #include "MacOsSpecific.h"
    #else

        #if defined(TARGET_OS_IPHONE) || defined(__APPLE_CC__) && !defined(TARGET_MOBILE_EMULATOR)

            #ifndef TARGET_OS_IPHONE
                #define TARGET_OS_IPHONE 1
            #endif

        #include "IOSSpecific.h"
        #endif

        #ifdef TARGET_IPHONE_SIMULATOR
            #include "IOSSpecific.h"
        #endif

    #endif
#endif

#if defined (ANDROID_NDK)
#define TARGET_OS_POSIX
  #define TARGET_OS_ANDROID 1
  #include "AndroidSpecific.h"
#elif defined(__linux__)
#define TARGET_OS_POSIX
#define TARGET_OS_LINUX
#include "LinuxSpecific.h"
#endif

#if defined (EMSCRIPTEN)
#define TARGET_OS_POSIX
#ifndef TARGET_OS_EMSCRIPTEN
# define TARGET_OS_EMSCRIPTEN
#endif
  #include "EmscriptenSpecific.h"

#define DISABLE_LIGHTMAPGEN
#define DISABLE_INDOOR_MESH
#define DISABLE_TERRAIN
#define DISABLE_SKYDOME
#define DISABLE_RAINAREA
#define DISABLE_DEFERRED_RENDER
#define DISABLE_FLARE
#if (EMSCRIPTEN_MORE_STRIPIFY)
#define DISABLE_POSTPROCESS
#define DISABLE_DOF
#define DISABLE_SSAO
#define DISABLE_BLOOM
#define DISABLE_MESH_MERGER
#define DISABLE_SHADOW_MAPS
#define DISABLE_WATERDROPS
#define DISABLE_SKYBOX
#define DISABLE_REFLECTIONS
#define DISABLE_REFRACTIONS
#ifdef DISABLE_REFLECTIONS
#define DISABLE_OCEAN
#endif
#define DISABLE_SILHOUETTE
#define DISABLE_TOON
#define DISABLE_SHADERS_DEBUG
#define DISABLE_GLOW
#define DISABLE_WATER_NORMALGEN
#define DISABLE_OVERLAY
#define DISABLE_HDR
#define DISABLE_MOTION_BLUR
#define DISABLE_COLOR_GRADING
#endif
#endif

#if defined (FLASH)
//#define __GNUC__
#define __FORUNIX__
#define TARGET_OS_POSIX
#define TARGET_OS_FLASH 1
#include "FlashSpecific.h"
#endif



