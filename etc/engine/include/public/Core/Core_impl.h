////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __core_impl_h__
#define __core_impl_h__
#pragma once

#include "ICore.h"


//////////////////////////////////////////////////////////////////////////
// If not in static library.
#if !defined(__APPLE__)
#include "Crc32.cpp"
#endif

#endif // __core_impl_h__
