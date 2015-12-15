////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MEMORY_MANAGER
#define _MEMORY_MANAGER

#pragma once 

#define MEMORYMANAGER_API


MEMORYMANAGER_API void Free(void *p);
MEMORYMANAGER_API void *Realloc(void *memblock, size_t size);
MEMORYMANAGER_API void *Malloc(size_t size);
MEMORYMANAGER_API void*	Calloc(size_t num,size_t size);

#undef malloc
#undef calloc
#undef realloc
#undef free
#define malloc        Malloc
#define calloc        Calloc
#define realloc       Realloc
#define free          Free

#endif