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

#include "Common.h"

DLLIMPORT void *EngineMalloc(size_t size);
DLLIMPORT void EngineFree(void * pointee);
DLLIMPORT void * EngineRealloc(void * ptr, size_t size);

//#include <malloc.h>
#include <assert.h>

#if defined(_WIN32)
inline void HeapCheck()
{
  int Result = _heapchk();
  assert(Result!=_HEAPBADBEGIN);
  assert(Result!=_HEAPBADNODE);
  assert(Result!=_HEAPBADPTR);
  assert(Result!=_HEAPEMPTY);
  assert(Result==_HEAPOK);
}
#endif

namespace Engine2
{
	//struct BaseAllocator 
	//{
	//	typedef void * pointer_type;
	//	pointer_type allocate(size_t size);
	//	void  deallocate(pointer_type ptr, size_t size);
	//};

	template<class T1, class T2>
	void swap(T1& a, T2& b)
	{
		T1 c(a);
		a = static_cast<T1>(b);
		b = static_cast<T2>(c);
	}


	struct StandardAllocator /*: public BaseAllocator*/
	{
		typedef void * pointer_type;

		static pointer_type allocate(size_t size) {
			return EngineMalloc(size) ;
		}
		static pointer_type reallocate(pointer_type ptr, size_t size) {
			return EngineRealloc(ptr, size);
		}
		static void  deallocate(pointer_type ptr, size_t size) {
			EngineFree(ptr);
		}
	};

}
