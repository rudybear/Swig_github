////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __MATH_QUAT_INL__
#define __MATH_QUAT_INL__

CQuaternion::CQuaternion(const CVec3& Direction)
{
	assert(Direction.NotNULL());
	const CVec3 zAxis(Direction.GetNormalizedFast());

	// Build the Y vector of the matrix (handle the degenerate case
	// in the way that 3DS does) -- This is not the TRUE vector, only
	// a reference vector.

	CVec3 yAxis;
	if (fabsf(zAxis.x) < pgEPS && fabsf(zAxis.z) < pgEPS)
		yAxis = CVec3(-zAxis.y, 0.0f, 0.0f );
	else
		yAxis = CVec3(0.0f, 1.0f, 0.0f);

	// Build the X axis vector based on the two existing vectors
	const CVec3 xAxis = yAxis.Cross(zAxis).NormalizeFast();

	// Correct the Y reference vector
	yAxis = xAxis.Cross(zAxis).NormalizeFast();
	yAxis = -yAxis;

	CMatrix44 tmpMat(1);
	(CVec3&)tmpMat.m[0][0] = xAxis;
	(CVec3&)tmpMat.m[1][0] = yAxis;
	(CVec3&)tmpMat.m[2][0] = zAxis;
	SetFromMatrix(tmpMat);
}

FORCEINLINE CQuaternion CQuaternion::operator * (const CQuaternion& p) const
{
	VALIDATE;
	return CQuaternion(
        p.w*w -(p.x*x + p.y*y + p.z*z),
        p.y*z - p.z*y + p.w*x + p.x*w,
        p.z*x - p.x*z + p.w*y + p.y*w,
        p.x*y - p.y*x + p.w*z + p.z*w);
}

FORCEINLINE bool CQuaternion::IsUnit(void) const
{
	return ((CVec4*)this)->LengthSq() >= 1.f - VEC_EPSILON;
}

FORCEINLINE void CQuaternion::SetFromMatrix(const CMatrix44& M)
{
	FLOAT* m = (FLOAT*)&M;

	// trace
	FLOAT T = m[0] + m[5] + m[10];
	FLOAT S;

	if(T > 0.f) 
	{
		S = sqrtf(T + 1.f) * 2.f;
		x = (m[6] - m[9]) / S;
		y = (m[8] - m[2]) / S;
		z = (m[1] - m[4]) / S;
		w = 0.25f * S;
	}
	else
	{
		if (m[0] > m[5] && m[0] > m[10])  {	// Column 0: 
			S  = sqrtf(1.f + m[0] - m[5] - m[10]) * 2.f;
			x = 0.25f * S;
			y = (m[1] + m[4]) / S;
			z = (m[8] + m[2]) / S;
			w = (m[6] - m[9]) / S;
		} else if (m[5] > m[10]) {			// Column 1: 
			S  = sqrtf(1.f + m[5] - m[0] - m[10]) * 2.f;
			x = (m[1] + m[4]) / S;
			y = 0.25f * S;
			z = (m[6] + m[9]) / S;
			w = (m[8] - m[2]) / S;
		} else {						// Column 2:
			S  = sqrtf(1.f + m[10] - m[0] - m[5]) * 2.f;
			x = (m[8] + m[2]) / S;
			y = (m[6] + m[9]) / S;
			z = 0.25f * S;
			w = (m[1] - m[4]) / S;
		}
	}

	VALIDATE;
}

FORCEINLINE CQuaternion CQuaternion::GetConjugated(void) const
{
	VALIDATE;
	return CQuaternion(w, -x, -y, -z);
}

FORCEINLINE void CQuaternion::Normalize()
{
	((CVec4*)this)->NormalizeFast();
	VALIDATE;
}

FORCEINLINE CQuaternion CQuaternion::GetNormalized() const
{
	CQuaternion q(*this);
	q.Normalize();
	return q;
}

void CQuaternion::Slerp(const CQuaternion &q1, const CQuaternion &q2, const float& t)
{
	CQuaternion p=q1,q=q2;

	FLOAT cosine = p.x*q.x + p.y*q.y + p.z*q.z + p.w*q.w;// (p|q);
	if (cosine < 0.f ) { cosine = -cosine; q = q * -1.0f;	} //take shortest arc
  if (cosine > 1.0f )
    cosine = 1.0f;

	// from now on, a division by 0 is not possible any more
	q.w	= q.w-p.w*cosine;
	q.x	= q.x-p.x*cosine;
	q.y	= q.y-p.y*cosine;
	q.z	= q.z-p.z*cosine;
	const FLOAT sine = MAX(pgEPS, sqrtf(1.f - cosine*cosine));
	const FLOAT angle = atan2f(sine, cosine)*t;
	const FLOAT s = sinf(angle);
  const FLOAT c = cosf(angle);

	w = p.w*c + q.w*s/sine;
	x = p.x*c + q.x*s/sine;
	y = p.y*c + q.y*s/sine;
	z = p.z*c + q.z*s/sine;
	VALIDATE;
}

void CQuaternion::FromDirection(const CVec3 &Direction, const CVec3 &Up)
{
	SetFromMatrix(MatrixLookAtRH(CVec3(0,0,0), Direction, Up));
}

void CQuaternion::FromAngleAxis(const float& rfAngle, const CVec3& rkAxis)
{
	assert(rkAxis.LengthSq() >= 1.f - VEC_EPSILON);
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)
	const float fHalfAngle = 0.5f * rfAngle;
	const float fSin = sinf(fHalfAngle);
	w = cosf(fHalfAngle);
	x = fSin*rkAxis.x;
	y = fSin*rkAxis.y;
	z = fSin*rkAxis.z;
	VALIDATE;
}

void CQuaternion::FromDirectionVecUP(const CVec3& Direction, const CVec3& VecUP)
{
	const CVec3 Axis = Direction.Cross(VecUP).Normalize();
	const float Angle = asinf(Direction.GetNormalized().z);
	FromAngleAxis(Angle,Axis);
	VALIDATE;
}

void CQuaternion::FromRotation(const CVec3& Rotation)
{
	CVec4	Angles(Rotation.y, Rotation.x, Rotation.z, 0.f);

	const CVec4 Sign(1.0f, -1.0f, -1.0f, 1.0f);

	const CVec4 HalfAngles = Angles * .5f;

	const CVec4 SinAngles = CVec4(sinf(HalfAngles.x), sinf(HalfAngles.y), sinf(HalfAngles.z), 0.f);
	const CVec4 CosAngles = CVec4(cosf(HalfAngles.x), cosf(HalfAngles.y), cosf(HalfAngles.z), 1.f);

	const CVec4 P0 = CVec4(SinAngles.x, CosAngles.x, CosAngles.x, CosAngles.x);
	const CVec4 P1 = CVec4(CosAngles.x, SinAngles.x, SinAngles.x, SinAngles.x);

	const CVec4 Y0 = CVec4(CosAngles.y, SinAngles.y, CosAngles.y, CosAngles.y);
	const CVec4 Y1 = CVec4(SinAngles.y, CosAngles.y, SinAngles.y, SinAngles.y);

	const CVec4 R0 = CVec4(CosAngles.z, CosAngles.z, SinAngles.z, CosAngles.z);
	const CVec4 R1 = CVec4(SinAngles.z, SinAngles.z, CosAngles.z, SinAngles.z);

	CVec4 Q1 = P1 * Sign;
	CVec4 Q0 = P0 * Y0;
	Q1 = Q1 * Y1;
	Q0 = Q0 * R0;

	Q0 = Q1 * R1 + Q0;
	x = Q0.x; y = Q0.y; z = Q0.z; w = Q0.w;
	VALIDATE;
}

#endif // __MATH_QUAT_INL__