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

#include "Vector.h"
#if defined(_WIN32)
#include <Windows.h>

#else

//#include "D3DX.h"
//#include <math.h>

#endif
#include "OurMath.h"

//#define _DEBUG_VALIDATE

// VALIDATE MACROS

#ifdef _DEBUG_VALIDATE
#	define CheckFloat(x) 
#else
#	define CheckFloat(x) assert(_finite(x));
#endif

// Float type for math
#ifndef FLOAT
#	define FLOAT float
#endif

//[Alexey] SWIG madness
//#	define CFLOAT const FLOAT
#	define CFLOAT float

// Use cast operators for standard D3DX types
#ifdef D3D_SDK_VERSION
#	define USE_D3DX
#endif

// Use SSE instructions on win platforms
#ifdef WIN_PLATFORM
#	define USE_SSE
#endif

// Use VMX instructions on arm platforms
#ifdef ARM_PLATFORM
#	define USE_VMX
#endif


#ifdef _DEBUG_VALIDATE
#	define VALIDATE Validate()
#	define VALIDATE_PTR(x) (x)->Validate()
#else
#	define VALIDATE
#	define VALIDATE_PTR(x)
#endif

#if !defined(MATH_NO_ALIGNMENT)
#	define _DECLSPEC_ALIGN_16_   __declspec(align(16))
#else
#	define _DECLSPEC_ALIGN_16_
#endif

#include "MathVector.h"
#include "CPlane.h"
#include "MathQuaternion.h"
#include "MathMatrix.h"
#include "CAABBox.h"
#include "Shapes.h"
#include "Intersection.h"
#include "MathQuaternionT.h"
#include "Frustum.h"
#include <stdlib.h> // for rand() and RAND_MAX

//#ifdef USE_SSE
//#	include "MathMatrixSSE.inl"
//#	include "MathPlaneSSE.inl"
//#	include "MathQuaternionSSE.inl"
//#else
#	include "MathMatrix.inl"
#	include "MathPlane.inl"
#	include "MathQuaternion.inl"
//#endif

DLLIMPORT CVec3 MakeVecFromStr(const char *str); // CVec3 из строкового значения в виде x,y,z "без пробелов"
DLLIMPORT CMatrix44 MakeMatrixFromStr(const char *str); //CMatrix44 из строки. пока не понятно, как.

inline float CustomRand(float fff){
	return fff * 2 * rand() / RAND_MAX - fff;
}

#if defined(_WIN32) && !defined(_WIN64)
#pragma warning (disable:4793) // '__asm' : causes native code generation for function 'int fptoint(float)' 

inline int fptoint(float val)
{
	int retval;
	_asm {
		fld val
			fistp retval
	}
	return retval;
}

inline float fastsqrt(float f)
{
	float retval;
	_asm {
		mov eax, f
			sub eax, 0x3f800000
			sar eax, 1
			add eax, 0x3f800000
			mov retval, eax
	}
	return retval;
}

#endif

inline f32 __fsel(const f32 _a, const f32 _b, const f32 _c) { return (_a < 0.0f) ? _c : _b; }
inline f32 __fres(const f32 _a) { return 1.f / _a; }
inline int32 __iszero(f32 x)
{
	union { f32 f; int32 i; } u;
	u.f = x; u.i &= 0x7FFFFFFF; return -(u.i >> 31 ^ (u.i - 1) >> 31);
}
template<class T> inline T _clamp(T X, T Min, T Max)
{
	return X<Min ? Min : X<Max ? X : Max;
}


DLLIMPORT void TangentBasis(CVec3 &tangent, CVec3 &binormal, float &sign,
	const CVec3 &v0, const CVec3 &v1, const CVec3 &v2,
	const CVec2 &t0, const CVec2 &t1, const CVec2 &t2,
	const CVec3 &normal);

//point location
DLLIMPORT bool isPointBehindPlanes(const CVec3& nPos, int nNumPlanes, CPlane* nPlanes);
DLLIMPORT bool isPointBehindPlane(const CVec3& nPos, const CPlane& nPlane);

//auxiliary functions
DLLIMPORT bool findContactSetCoplanarTri(const CVec3 &akU0, const CVec3 &akU1, const CVec3 &akU2, const CVec3 &akV0, const CVec3 &akV1, const CVec3 &akV2, int& riQuantity, CVec3 akP[6]);
DLLIMPORT void ClipConvexPolygonAgainstPlane(const CVec3& rkNormal, float fConstant, int& riQuantity, CVec3* akP);
DLLIMPORT bool ComputeBarycenter(const CVec3& rkV0, const CVec3& rkV1, const CVec3& rkV2, const CVec3& rkP, float& afBaryU, float& afBaryV, float& afBaryW);

// square equation... uhuh!
DLLIMPORT bool getLowestRoot(float a, float b, float c, float maxR, float* root);
DLLIMPORT bool getRoots(float a, float b, float c, float& root1, float& root2);

DLLIMPORT float GetSegmentDistance(const CVec3 &vecPoint, const CVec3 &vecA, const CVec3 &vecB);
DLLIMPORT const CVec3 &GetClosestPointOnSegment(const CVec3 &vecPoint, const CVec3 &vecA, const CVec3 &vecB);

DLLIMPORT void TriangulateBBox(const CVec3& nBoxMin, const CVec3& nBoxMax, Engine2::Vector<CTriangle>& nOut);




namespace InterpolationContainer
{

	/*! \addtogroup HelperClasses
	*@{
	*/
	//!класс для интерполяции кватернионов
	class QuatInterpolator
	{
	public:
		QuatInterpolator(){};
		~QuatInterpolator(){};


		CQuaternion operator ()(const CQuaternion& a, const CQuaternion& b, CFLOAT fTime)
		{
			CQuaternion res;
			res.Slerp(a, b, fTime);
			return res;
		};
	};



	//! \brief класс для интерполяции матриц
	class MatrixInterpolator
	{
	public:
		MatrixInterpolator(){};
		~MatrixInterpolator(){};


		CMatrix44 operator ()(const CMatrix44 &a, const CMatrix44 &b, CFLOAT fTime)
		{
			CMatrix44 res = a.Slerp(a, b, fTime);
			return res;
		};
	};
	//@}
}



template<class T>
inline void Swap(T& a, T& b)
{
	T c(a);
	a = b;
	b = c;
}
