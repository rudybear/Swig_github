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

#ifndef DISABLE_CUSTOM_MEMORYALLOCATOR

struct MemoryUsageStatistics
{
	unsigned long long m_numAllocations;
	unsigned long long m_numDeallocations;
	unsigned long long m_numAllocated;
	unsigned long long m_numDeallocated;
	MemoryUsageStatistics() 
	{
		m_numAllocations = 0;
		m_numDeallocations = 0;
		m_numAllocated = 0;
		m_numDeallocated = 0;
	}
};

inline MemoryUsageStatistics& GetMemoryUsageStatistics() { static MemoryUsageStatistics stats; return stats; }

//#define LEAKDETECTOR

#if !defined(__APPLE__)
#ifndef LEAKDETECTOR
inline void* _Malloc(size_t size) throw()
{
	++GetMemoryUsageStatistics().m_numAllocations;
	GetMemoryUsageStatistics().m_numAllocated += size;
	return malloc(size);
}

inline void* _Calloc(size_t num,size_t size) throw()
{
	++GetMemoryUsageStatistics().m_numAllocations;
	GetMemoryUsageStatistics().m_numAllocated += size;

	return calloc(num, size);
}

inline void* _Realloc(void *memblock,size_t size) throw()
{
  GetMemoryUsageStatistics().m_numDeallocated += _msize(memblock);
	GetMemoryUsageStatistics().m_numAllocated += size;
  if (size == 0)
    ++GetMemoryUsageStatistics().m_numDeallocations;
	return realloc(memblock, size);
}

inline void  _Free(void *ptr) throw()
{
	if (ptr) {
		++GetMemoryUsageStatistics().m_numDeallocations;
		GetMemoryUsageStatistics().m_numDeallocated += _msize(ptr);
		free(ptr);
	}
}

#else

extern void* _Malloc(size_t size) throw();
extern void* _Calloc(size_t num,size_t size) throw();
extern void* _Realloc(void *memblock,size_t size) throw();
extern void  _Free(void *ptr) throw();

#endif
#endif

#endif

