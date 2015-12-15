////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __MATH_PLANE_INL__
#define __MATH_PLANE_INL__

FORCEINLINE CPlane::CPlane(const CVec3& vecPoint, const CVec3& vecNormal) : normalized(false)
{ 
	(CVec3&)(*this) = vecNormal;
	d = -vecNormal.Dot(vecPoint);
	VALIDATE;
	Normalize();
}

FORCEINLINE CPlane::CPlane(const CVec3& vecPoint1, const CVec3& vecPoint2, const CVec3& vecPoint3) : normalized(false)
{
	normalized = false;
	const CVec3 vecNormal = (vecPoint2 - vecPoint1).Cross(vecPoint3 - vecPoint2);
	(*this) = CPlane(vecPoint1, vecNormal);
}

FORCEINLINE void CPlane::Normalize()
{
	assert(!normalized);
	CVec3& n = *(CVec3* const)this;
	CFLOAT l = n.Length();
    // FIXME ANDREY
	//assert(l > pgEPS);
	n /= l;
	d /= l;
	normalized = true;
	VALIDATE;
}

FORCEINLINE CFLOAT CPlane::Distance(const CVec3& nPos) const
{
	return fabsf(SignedDistance(nPos));
}

FORCEINLINE CFLOAT CPlane::SignedDistance(const CVec3& nPos) const
{
	assert(normalized);
	return nPos.Dot((const CVec3&)(*this)) + d;
}

FORCEINLINE CVec3 CPlane::ClosestPoint(const CVec3& nPoint) const
{
	CVec3 out;
	IntersectLine(nPoint, nPoint + GetNormal(), &out);
	return out;
}

FORCEINLINE bool CPlane::IntersectLine(const CVec3& v0, const CVec3& v1, CVec3* const pIsection/* = NULL*/) const
{
	assert(normalized);
	const CVec3 u = v1 - v0;
	CFLOAT t = -SignedDistance(v0) / GetNormal().Dot(u);
	if(pIsection)
		(*pIsection) = v0 + u*t;
	return t >= (0.f - pgEPS) && t <= (1.f + pgEPS);
}

FORCEINLINE CVec3 CPlane::GetNormal() const
{
	assert(normalized);
	return *(CVec3* const)this;
}

#endif // __MATH_PLANE_INL__
