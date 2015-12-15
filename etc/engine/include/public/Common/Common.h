////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __COMMON_H
#define __COMMON_H

#pragma once

#if (_MSC_VER > 1700)
#define NOT_USE_BOOST

#define SHARED_PTR_NAMESPACE std
#define UNIQUE_PTR unique_ptr

#endif

#if defined(__APPLE__) || (defined(__linux__) && !defined(ANDROID)) || (__cplusplus >= 201103L)
#include <memory>

#define SHARED_PTR_NAMESPACE std
#define UNIQUE_PTR unique_ptr

#define NOT_USE_BOOST

#endif

#ifndef NOT_USE_BOOST
	#define SHARED_PTR_NAMESPACE boost
	#define UNIQUE_PTR scoped_ptr
#endif

#define _DLL_CORE

#ifndef SWIG
#ifdef _DLL_CORE
#if defined(_WIN32)
// FIXME:!!!!
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __attribute__ ((visibility("default")))
#endif
#else
#define DLLIMPORT 
#endif
#else
#define DLLIMPORT 
#endif


#pragma warning(disable : 4275)


#include <assert.h>
#if !defined(__APPLE__) && !defined(FLASH)
#include <malloc.h>
#endif

#include <new>

#include "Public/Common/OurTypes.h"
#include "Public/Platform/Platform.h"

#if 1 //defined(__APPLE__) || defined (TARGET_OS_ANDROID) || defined(TARGET_OS_FLASH) || defined(TARGET_OS_EMSCRIPTEN) || defined(TARGET_OS_LINUX)
#ifdef DONT_USE_MEMORYALLOCATOR
  #undef DONT_USE_MEMORYALLOCATOR
#endif
#define DONT_USE_MEMORYALLOCATOR
#if defined (DEBUG)
#ifndef _DEBUG
#define _DEBUG
#endif
#endif
#endif

#ifdef _DEBUG
  #ifndef DONT_USE_MEMORYALLOCATOR
    #define DONT_USE_MEMORYALLOCATOR
  #endif
#endif

#ifndef DONT_USE_MEMORYALLOCATOR

#include "Specific.h"
//extern "C"
//{
//	void* _Malloc(size_t size) throw();
//	void* _Calloc(size_t num,size_t size) throw();
//	void* _Realloc(void *memblock,size_t size) throw();
//	void  _Free(void *ptr) throw();
//}

#if defined(_WIN32)
inline void * __cdecl operator new   (size_t size) throw (/*std::bad_alloc*/) { return _Malloc(size); }
inline void * __cdecl operator new   (size_t size, const std::nothrow_t &nothrow) throw() { return _Malloc(size); }
inline void * __cdecl operator new[] (size_t size) throw (/*std::bad_alloc*/) { return _Malloc(size); }
inline void * __cdecl operator new[] (size_t size, const std::nothrow_t &nothrow) throw() { return _Malloc(size); }
inline void __cdecl operator delete  (void *p) throw (){ _Free(p); };
inline void __cdecl operator delete[](void *p) throw (){ _Free(p); };
inline void __cdecl operator delete  (void *p, const std::nothrow_t &nothrow) throw (){ _Free(p); };
inline void __cdecl operator delete[](void *p, const std::nothrow_t &nothrow) throw (){ _Free(p); };

#define malloc        _Malloc
#define calloc        _Calloc
#define realloc       _Realloc
#define free          _Free

#else 

//#define malloc EngineMalloc
//#define free EngineFree

#define _Malloc malloc        
#define _Calloc calloc        
#define _Realloc realloc       
#define _Free free          

#endif
#endif

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }

#ifdef _DEBUG_RELEASE
 #define SAFE_RELEASE(p)      { if(p) { UINT res = (p)->Release();  assert(res == 0); (p)=NULL; } }
#else
 #define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

#define ASSERT_X(p)       { if(p != S_OK) { return p; } }

#define COMPILE_TIME_ASSERT(x) { switch(false) {	case false:	case (x):	; } }

//#include "types.h"

template <class T>
inline void ZeroStruct( T &t ) { memset( &t,0,sizeof(t) ); }


template<class T>
class CSingleton 
{
public:
  static T& Instance()
  {
    static T inst;
    return inst;
  }

};

#ifdef MIN
#undef MIN
#endif
template <typename T>
FORCEINLINE const T& MIN(const T& a, const T& b)
{
	return a < b ? a : b; 
}

#ifdef MAX
#undef MAX
#endif
template <typename T>
FORCEINLINE const T& MAX(const T& a, const T& b)
{
	return a > b ? a : b; 
}

#define REF(x) (void)x

#define ENGINE_BUILD "$Rev: 927 $ ";

#ifndef _DEBUG
//#define _HAS_ITERATOR_DEBUGGING 0
#undef _HAS_ITERATOR_DEBUGGING
//#define _SECURE_SCL 0
#endif

DLLIMPORT void *EngineMalloc(size_t size);
DLLIMPORT void EngineFree(void * pointee);
DLLIMPORT void * EngineRealloc(void * ptr, size_t size);

#endif
