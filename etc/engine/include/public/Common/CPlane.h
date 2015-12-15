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

class CTriangle;
struct CVec3;

struct CPlane
{
protected:
	FLOAT a, b, c, d;
	bool	normalized;
	FORCEINLINE void Normalize();
public:

	FORCEINLINE CPlane() : normalized(false) {};
	FORCEINLINE CPlane(CFLOAT _a, CFLOAT _b, CFLOAT _c, CFLOAT _d) :  a(_a), b(_b), c(_c), d(_d), normalized(false) { VALIDATE; Normalize(); };
	FORCEINLINE CPlane(const CVec3& vecNormal, CFLOAT _d) { (*this) = CPlane(vecNormal.x, vecNormal.y, vecNormal.z, _d); }

	FORCEINLINE CPlane(const CVec3& vecPoint, const CVec3& vecNormal);
	FORCEINLINE CPlane(const CVec3& vecPoint1, const CVec3& vecPoint2, const CVec3& vecPoint3);
	FORCEINLINE const bool operator==(const CPlane& p) const { assert(normalized && p.normalized); return feq(a,p.a) && feq(b, p.b) && feq(c, p.c) && feq(d, p.d); }

	FORCEINLINE bool IntersectLine(const CVec3& vecLineStart, const CVec3& vecLineEnd, CVec3* const pIsection = NULL) const;
	FORCEINLINE CFLOAT DotNormal(const CVec3& vecNormal) const { assert(normalized); return a*vecNormal.x + b*vecNormal.y + c*vecNormal.z; }
	FORCEINLINE CFLOAT DotCoord(const CVec3& vecCoord) const { return SignedDistance(vecCoord); }

	//distance
	FORCEINLINE CFLOAT Distance(const CVec3& nPos) const;
	FORCEINLINE CFLOAT SignedDistance(const CVec3& nPos) const;

	FORCEINLINE CVec3 ClosestPoint(const CVec3& nPoint) const;

	FORCEINLINE CVec3 GetNormal() const;
	FORCEINLINE CFLOAT GetD() const { assert(normalized); return d; }

	FORCEINLINE void Validate() const
	{
#ifdef _DEBUG_VALIDATE
		CheckFloat(a);
		CheckFloat(b);
		CheckFloat(c);
		CheckFloat(d);
#endif
	}
};
