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

struct CVec3;
struct CMatrix44;

struct /*_DECLSPEC_ALIGN_16_*/ CQuaternion
{
	union
	{
//#ifdef USE_SSE
//		__m128 v;
//#endif
		struct { FLOAT x, y, z, w; }; 
	};
	// Constructors
	FORCEINLINE CQuaternion() : x(0.f), y(0.f), z(0.f), w(1.f) { };
	FORCEINLINE CQuaternion(const FLOAT _w, const FLOAT _x, const FLOAT _y, const FLOAT _z)
														: x(_x), y(_y), z(_z), w(_w) { VALIDATE; }
	FORCEINLINE CQuaternion(const CVec3& Direction); //from direction vector
	FORCEINLINE explicit CQuaternion(const CMatrix44& matRot) { SetFromMatrix(matRot); }
	FORCEINLINE CQuaternion (const CQuaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) { VALIDATE; };

	// Operators
	FORCEINLINE CQuaternion operator + (const CQuaternion& q2) const { VALIDATE; return CQuaternion(w + q2.w, x + q2.x, y + q2.y, z + q2.z);};
	FORCEINLINE CQuaternion operator - (const CQuaternion& q2) const { VALIDATE; return CQuaternion(w - q2.w, x - q2.x, y - q2.y, z - q2.z);};
	FORCEINLINE CQuaternion operator * (CFLOAT f) const { VALIDATE; return CQuaternion(w * f, x * f, y * f, z * f);};
	FORCEINLINE CQuaternion operator * (const CQuaternion&) const;

	// Methods
	FORCEINLINE CQuaternion GetConjugated(void) const;
	FORCEINLINE void Normalize(void);
	FORCEINLINE CQuaternion GetNormalized() const;
	FORCEINLINE void SetIdentity() {w = 1.0f;x = 0.0f;y = 0.0f;z = 0.0f; };
	FORCEINLINE void Slerp(const CQuaternion &q1, const CQuaternion &q2, const float& t);
	FORCEINLINE void SetFromMatrix(const CMatrix44& m);
	FORCEINLINE void FromAngleAxis (const float& rfAngle, const CVec3& rkAxis);
	FORCEINLINE void FromDirectionVecUP (const CVec3& Direction, const CVec3& VecUP);
	FORCEINLINE void FromRotation(const CVec3 &Rotation);
	FORCEINLINE void FromDirection(const CVec3 &Direction, const CVec3 &Up);
	FORCEINLINE bool NotNULL(void) const {  VALIDATE; return (fabsf(x) > pgEPS && fabsf(y) > pgEPS && fabsf(z) > pgEPS && fabsf(w) < 1.f - pgEPS); }
	FORCEINLINE bool IsUnit(void) const;
	FORCEINLINE void Validate(void) const
	{
#ifdef _DEBUG_VALIDATE
		CheckFloat(x);
		CheckFloat(y);
		CheckFloat(z);
		CheckFloat(w);
#endif
	}

  FORCEINLINE bool operator == ( const CQuaternion& v) const
  {
    return x == v.x && y == v.y && z == v.z  && w == v.w;
  }

};

typedef CQuaternion CQuat;