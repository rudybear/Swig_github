////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __MATH_QUAT_SSE_INL__
#define __MATH_QUAT_SSE_INL__

namespace 
{
	FORCEINLINE float as_float(const int i) { float v = (float&)i; return v; }
	// Using a control vector made up of 16 bytes from 0-31, remap V1 and V2's byte
	// entries into a single 16 byte vector and return it. Index 0-15 = V1,
	// 16-31 = V2
	FORCEINLINE CVec4 XMVectorPermute(const CVec4& V1, const CVec4& V2, const CVec4& Control)
	{
		const BYTE *aByte[2];
		CVec4 Result;
		UINT i, uIndex, VectorIndex;
		const BYTE *pControl;
		BYTE *pWork;

		// Indices must be in range from 0 to 31
		assert(((const int&)Control.x & 0xE0E0E0E0) == 0);
		assert(((const int&)Control.y & 0xE0E0E0E0) == 0);
		assert(((const int&)Control.z & 0xE0E0E0E0) == 0);
		assert(((const int&)Control.w & 0xE0E0E0E0) == 0);

		// 0-15 = V1, 16-31 = V2
		aByte[0] = (const BYTE*)(&V1);
		aByte[1] = (const BYTE*)(&V2);
		i = 16;
		pControl = (const BYTE *)(&Control);
		pWork = (BYTE *)(&Result);
		do {
			// Get the byte to map from
			uIndex = pControl[0];
			++pControl;
			VectorIndex = (uIndex>>4)&1;
			uIndex &= 0x0F;
			pWork[0] = aByte[VectorIndex][uIndex];
			++pWork;
		} while (--i);
		return Result;
	}

	FORCEINLINE CVec4 XMVectorSelect(const CVec4& V1, const CVec4& V2, const CVec4& Control)
	{
		CVec4 Result;
		(int&)Result.x = ((const int&)V1.x & ~(const int&)Control.x) | ((const int&)V2.x & (const int&)Control.x);
		(int&)Result.y = ((const int&)V1.y & ~(const int&)Control.y) | ((const int&)V2.y & (const int&)Control.y);
		(int&)Result.z = ((const int&)V1.z & ~(const int&)Control.z) | ((const int&)V2.z & (const int&)Control.z);
		(int&)Result.w = ((const int&)V1.w & ~(const int&)Control.w) | ((const int&)V2.w & (const int&)Control.w);
		return Result;
	}

	FORCEINLINE CVec4 XMVectorGreaterOrEqual(const CVec4& V1, const CVec4& V2)
	{
		CVec4 Control;
		(int&)Control.x = (V1.x >= V2.x) ? 0xFFFFFFFF : 0;
		(int&)Control.y = (V1.y >= V2.y) ? 0xFFFFFFFF : 0;
		(int&)Control.z = (V1.z >= V2.z) ? 0xFFFFFFFF : 0;
		(int&)Control.w = (V1.w >= V2.w) ? 0xFFFFFFFF : 0;
		return Control;
	}
}


#endif // __MATH_QUAT_SSE_INL__