////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OURTYPES_H
#define OURTYPES_H

#pragma once


#define _CPU_X86
#define _CPU_SSE

#ifdef _WIN32
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE inline
#endif

#if defined(_WIN32)
#include <malloc.h>
#include <io.h>
#include <direct.h>


#include <new.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////////
// Define platform independent types.
//////////////////////////////////////////////////////////////////////////
#ifndef byte
typedef unsigned char		byte;
#endif
typedef signed char         int8;
typedef signed short        int16;
typedef signed int			int32;
typedef signed __int64		int64;
#ifndef uint8
typedef unsigned char		uint8;
#endif
#ifndef uint16
typedef unsigned short		uint16;
#endif
#ifndef uint32
typedef unsigned int		uint32;
#endif
typedef unsigned __int64	uint64;
typedef float               f32;
typedef double              f64;
typedef double              real;  //biggest float-type on this machine

typedef unsigned long      DWORD;

#if defined(_WIN64)
typedef __int64 INT_PTR, *PINT_PTR;
typedef unsigned __int64 UINT_PTR, *PUINT_PTR;

typedef __int64 LONG_PTR, *PLONG_PTR;
typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;

typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
#else
typedef __w64 int INT_PTR, *PINT_PTR;
typedef __w64 unsigned int UINT_PTR, *PUINT_PTR;

typedef __w64 long LONG_PTR, *PLONG_PTR;
typedef __w64 unsigned long ULONG_PTR, *PULONG_PTR;

typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
#endif


#else

// APPLE
// ANDROID

#include <new>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////////
// Define platform independent types.
//////////////////////////////////////////////////////////////////////////
typedef signed char         int8;
typedef signed short        int16;
typedef signed int			int32;
typedef long long             int64;
#ifndef uint8
typedef unsigned char		uint8;
#endif
#ifndef uint16
typedef unsigned short		uint16;
#endif
#ifndef uint32
#ifndef byte
typedef unsigned char		byte;
#endif

typedef unsigned int		uint32;
#endif
typedef unsigned long long	uint64;
typedef float               f32;
typedef double              f64;
typedef double              real;  //biggest float-type on this machine

// Candidates for separate header with Windows-types
#if (defined(__linux__) && !defined(ANDROID)) || defined(_MAC64) || defined(__APPLE__)
typedef unsigned int        DWORD;
#else
typedef unsigned long       DWORD;
#endif
typedef DWORD * LPDWORD;
typedef unsigned short WORD;

#undef FALSE
#define FALSE   0
#undef TRUE
#define TRUE    1
typedef int BOOL;

typedef void VOID;
typedef unsigned char BYTE;
typedef char TCHAR;
typedef int INT;
typedef void * LPVOID;
#if (defined(__linux__) && !defined(ANDROID)) || defined(_MAC64) || defined(__APPLE__)
typedef int * PLONG;
typedef int LONG;
#else
typedef long * PLONG;
typedef long LONG;
#endif

#define WPARAM uint32
#define LPARAM uint32
#define LOWORD(l) (l & 0xffff)  
#define HIWORD(l) ((l>>16) & 0xffff)  
#define HIBYTE(w) (w >> 8)
#define LOBYTE(w) (w && 0xFF)

#if defined(_MAC64) || (__x86_64__)
typedef long long INT_PTR, *PINT_PTR;
typedef unsigned long long UINT_PTR, *PUINT_PTR;

typedef long long LONG_PTR, *PLONG_PTR;
typedef unsigned long long ULONG_PTR, *PULONG_PTR;

typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
#else
typedef  int INT_PTR, *PINT_PTR;
typedef  unsigned int UINT_PTR, *PUINT_PTR;

typedef  int LONG_PTR, *PLONG_PTR;
typedef  unsigned int ULONG_PTR, *PULONG_PTR;

typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
#endif


#endif


typedef void *THREAD_HANDLE;
typedef void *EVENT_HANDLE;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{ if(p) { delete (p);		(p)=NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release();	(p)=NULL; } }
#endif

#ifdef _WIN32
#define DEFINE_ALIGNED_DATA( type, name, alignment ) _declspec(align(alignment)) type name;
#define DEFINE_ALIGNED_DATA_STATIC( type, name, alignment ) static _declspec(align(alignment)) type name;
#define DEFINE_ALIGNED_DATA_CONST( type, name, alignment ) const _declspec(align(alignment)) type name;
#else
#define DEFINE_ALIGNED_DATA( type, name, alignment ) __attribute__ ((aligned(alignment))) type name;
#define DEFINE_ALIGNED_DATA_STATIC( type, name, alignment ) static __attribute__(aligned(alignment)) type name;
#define DEFINE_ALIGNED_DATA_CONST( type, name, alignment ) const __attribute__(aligned(alignment)) type name;
#endif
typedef uint32 COLOR;

// maps unsigned 8 bits/channel to D3DCOLOR
#define COLOR_ARGB(a,r,g,b) \
((COLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define COLOR_RGBA(r,g,b,a) COLOR_ARGB(a,r,g,b)
#define COLOR_XRGB(r,g,b)   COLOR_ARGB(0xff,r,g,b)

#define COLOR_XYUV(y,u,v)   COLOR_ARGB(0xff,y,u,v)
#define COLOR_AYUV(a,y,u,v) COLOR_ARGB(a,y,u,v)

#define COLOR_VEC4(dw)																																			\
CVec4(FLOAT((unsigned char)(dw >> 16)) / 255.f, FLOAT((unsigned char)(dw >>  8)) / 255.f,	\
FLOAT((unsigned char)(dw >>  0)) / 255.f,	FLOAT((unsigned char)(dw >> 24)) / 255.f)

#define COLOR_COLORVALUE(r,g,b,a) \
COLOR_RGBA((DWORD)((r)*255.f),(DWORD)((g)*255.f),(DWORD)((b)*255.f),(DWORD)((a)*255.f))




// Used in a bit flags
#define BIT(x) (1<<(x))

#ifdef _MSC_VER
# define PRII64x "I64x"
#else
# define PRII64x "llx"
#endif


#endif
