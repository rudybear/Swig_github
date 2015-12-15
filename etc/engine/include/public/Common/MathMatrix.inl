////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __MATH_MATRIX_INL__
#define __MATH_MATRIX_INL__

FORCEINLINE CMatrix44::CMatrix44(const CQuaternion& Rotation)
{
	*this = FromQuaternion(Rotation);
	VALIDATE;
}

FORCEINLINE CMatrix44 CMatrix44::operator * (const CMatrix44& mx ) const
{
	CMatrix44 mResult;
	// Cache the invariants in registers
	float x = m[0][0];
	float y = m[0][1];
	float z = m[0][2];
	float w = m[0][3];
	// Perform the operation on the first row
	mResult.m[0][0] = (mx.m[0][0]*x)+(mx.m[1][0]*y)+(mx.m[2][0]*z)+(mx.m[3][0]*w);
	mResult.m[0][1] = (mx.m[0][1]*x)+(mx.m[1][1]*y)+(mx.m[2][1]*z)+(mx.m[3][1]*w);
	mResult.m[0][2] = (mx.m[0][2]*x)+(mx.m[1][2]*y)+(mx.m[2][2]*z)+(mx.m[3][2]*w);
	mResult.m[0][3] = (mx.m[0][3]*x)+(mx.m[1][3]*y)+(mx.m[2][3]*z)+(mx.m[3][3]*w);
	// Repeat for all the other rows
	x = m[1][0];
	y = m[1][1];
	z = m[1][2];
	w = m[1][3];
	mResult.m[1][0] = (mx.m[0][0]*x)+(mx.m[1][0]*y)+(mx.m[2][0]*z)+(mx.m[3][0]*w);
	mResult.m[1][1] = (mx.m[0][1]*x)+(mx.m[1][1]*y)+(mx.m[2][1]*z)+(mx.m[3][1]*w);
	mResult.m[1][2] = (mx.m[0][2]*x)+(mx.m[1][2]*y)+(mx.m[2][2]*z)+(mx.m[3][2]*w);
	mResult.m[1][3] = (mx.m[0][3]*x)+(mx.m[1][3]*y)+(mx.m[2][3]*z)+(mx.m[3][3]*w);
	x = m[2][0];
	y = m[2][1];
	z = m[2][2];
	w = m[2][3];
	mResult.m[2][0] = (mx.m[0][0]*x)+(mx.m[1][0]*y)+(mx.m[2][0]*z)+(mx.m[3][0]*w);
	mResult.m[2][1] = (mx.m[0][1]*x)+(mx.m[1][1]*y)+(mx.m[2][1]*z)+(mx.m[3][1]*w);
	mResult.m[2][2] = (mx.m[0][2]*x)+(mx.m[1][2]*y)+(mx.m[2][2]*z)+(mx.m[3][2]*w);
	mResult.m[2][3] = (mx.m[0][3]*x)+(mx.m[1][3]*y)+(mx.m[2][3]*z)+(mx.m[3][3]*w);
	x = m[3][0];
	y = m[3][1];
	z = m[3][2];
	w = m[3][3];
	mResult.m[3][0] = (mx.m[0][0]*x)+(mx.m[1][0]*y)+(mx.m[2][0]*z)+(mx.m[3][0]*w);
	mResult.m[3][1] = (mx.m[0][1]*x)+(mx.m[1][1]*y)+(mx.m[2][1]*z)+(mx.m[3][1]*w);
	mResult.m[3][2] = (mx.m[0][2]*x)+(mx.m[1][2]*y)+(mx.m[2][2]*z)+(mx.m[3][2]*w);
	mResult.m[3][3] = (mx.m[0][3]*x)+(mx.m[1][3]*y)+(mx.m[2][3]*z)+(mx.m[3][3]*w);
	VALIDATE_PTR(&mResult);
	return mResult;
}


FORCEINLINE CVec3 CMatrix44::operator * (const CVec3& vec) const
{
	CVec3 vecRet = vec * GetTransposed();
	return vecRet;
}

FORCEINLINE CMatrix44 CMatrix44::GetTransposed() const {
	VALIDATE;
	return CMatrix44(	_11, _21, _31, _41, 
										_12, _22, _32, _42, 
										_13, _23, _33, _43, 
										_14, _24, _34, _44);
}

FORCEINLINE CMatrix44& CMatrix44::Transpose()
{
	(*this) = GetTransposed();
	return (*this);
}

FORCEINLINE CMatrix44 CMatrix44::GetInvert(void) const
{
	CMatrix44 out(*this);

#define SWAP_ROWS(a, b) { float *_tmp = a; (a)=(b); (b)=_tmp; }

	float wtmp[4][8];
	float m0, m1, m2, m3, s;
	float *r0, *r1, *r2, *r3;

	r0 = wtmp[0]; r1 = wtmp[1]; r2 = wtmp[2]; r3 = wtmp[3];

	r0[0] = (*this)(0,0); r0[1] = (*this)(0,1);
	r0[2] = (*this)(0,2); r0[3] = (*this)(0,3);
	r0[4] = 1.0f; r0[5] = r0[6] = r0[7] = 0.0f;

	r1[0] = (*this)(1,0); r1[1] = (*this)(1,1);
	r1[2] = (*this)(1,2); r1[3] = (*this)(1,3);
	r1[5] = 1.0f; r1[4] = r1[6] = r1[7] = 0.0f;

	r2[0] = (*this)(2,0); r2[1] = (*this)(2,1);
	r2[2] = (*this)(2,2); r2[3] = (*this)(2,3);
	r2[6] = 1.0f; r2[4] = r2[5] = r2[7] = 0.0f;

	r3[0] = (*this)(3,0); r3[1] = (*this)(3,1);
	r3[2] = (*this)(3,2); r3[3] = (*this)(3,3);
	r3[7] = 1.0f; r3[4] = r3[5] = r3[6] = 0.0f;

	/* choose pivot - or die */
	if (fabsf(r3[0])>fabsf(r2[0])) SWAP_ROWS(r3, r2);
	if (fabsf(r2[0])>fabsf(r1[0])) SWAP_ROWS(r2, r1);
	if (fabsf(r1[0])>fabsf(r0[0])) SWAP_ROWS(r1, r0);

#ifdef _DEBUG_VALIDATE
	assert(fabsf(r0[0]) > pgEPS);
#endif

	/* eliminate first variable     */
	m1 = r1[0]/r0[0]; m2 = r2[0]/r0[0]; m3 = r3[0]/r0[0];
	s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
	s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
	s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
	s = r0[4];
	if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r0[5];
	if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r0[6];
	if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r0[7];
	if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

	/* choose pivot - or die */
	if (fabsf(r3[1])>fabsf(r2[1])) SWAP_ROWS(r3, r2);
	if (fabsf(r2[1])>fabsf(r1[1])) SWAP_ROWS(r2, r1);

#ifdef _DEBUG_VALIDATE
	assert(fabsf(r1[1]) > pgEPS);
#endif
	
	/* eliminate second variable */
	m2 = r2[1]/r1[1]; m3 = r3[1]/r1[1];
	r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
	r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
	s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

	/* choose pivot - or die */
	if (fabsf(r3[2])>fabsf(r2[2])) SWAP_ROWS(r3, r2);

#ifdef _DEBUG_VALIDATE
	assert(fabsf(r2[2]) > pgEPS);
#endif

	/* eliminate third variable */
	m3 = r3[2]/r2[2];
	r3[3] -= m3 * r2[3]; r3[4] -= m3 * r2[4];
	r3[5] -= m3 * r2[5]; r3[6] -= m3 * r2[6];
	r3[7] -= m3 * r2[7];

#ifdef _DEBUG_VALIDATE
	assert(fabsf(r3[3]) > pgEPS);
#endif

	s = 1.0f/r3[3];              /* now back substitute row 3 */
	r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

	m2 = r2[3];                 /* now back substitute row 2 */
	s  = 1.0f/r2[2];
	r2[4] = s * (r2[4] - r3[4] * m2); r2[5] = s * (r2[5] - r3[5] * m2);
		r2[6] = s * (r2[6] - r3[6] * m2); r2[7] = s * (r2[7] - r3[7] * m2);
	m1 = r1[3];
	r1[4] -= r3[4] * m1; r1[5] -= r3[5] * m1;
		r1[6] -= r3[6] * m1; r1[7] -= r3[7] * m1;
	m0 = r0[3];
	r0[4] -= r3[4] * m0; r0[5] -= r3[5] * m0;
		r0[6] -= r3[6] * m0; r0[7] -= r3[7] * m0;

	m1 = r1[2];                 /* now back substitute row 1 */
	s  = 1.0f/r1[1];
	r1[4] = s * (r1[4] - r2[4] * m1); r1[5] = s * (r1[5] - r2[5] * m1);
	r1[6] = s * (r1[6] - r2[6] * m1); r1[7] = s * (r1[7] - r2[7] * m1);
	m0 = r0[2];
	r0[4] -= r2[4] * m0; r0[5] -= r2[5] * m0;
	r0[6] -= r2[6] * m0; r0[7] -= r2[7] * m0;

	m0 = r0[1];                 /* now back substitute row 0 */
	s  = 1.0f/r0[0];
	r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0);
	r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

	out(0,0) = r0[4]; out(0,1) = r0[5];
	out(0,2) = r0[6]; out(0,3) = r0[7];
	out(1,0) = r1[4]; out(1,1) = r1[5];
	out(1,2) = r1[6]; out(1,3) = r1[7];
	out(2,0) = r2[4]; out(2,1) = r2[5];
	out(2,2) = r2[6]; out(2,3) = r2[7];
	out(3,0) = r3[4]; out(3,1) = r3[5];
	out(3,2) = r3[6]; out(3,3) = r3[7];

#undef SWAP_ROWS

	VALIDATE_PTR(&out);
	return out;
}

FORCEINLINE CMatrix44& CMatrix44::Identity()
{
	(*this) = CMatrix44(1,  0,  0, 0,
										 0,  1,  0, 0,
										 0,  0,  1, 0,
										 0,  0,  0, 1);
	return (*this);
}

FORCEINLINE CQuaternion CMatrix44::GetRotQuaternion(void) const
{
	VALIDATE;
	return CQuaternion(*this);
}

FORCEINLINE void CMatrix44::SetTranslation(const CVec3& vecPos)
{
	(*this)[12] = vecPos.x;
	(*this)[13] = vecPos.y;
	(*this)[14] = vecPos.z;
	VALIDATE;
}

FORCEINLINE const CVec3& CMatrix44::GetTranslation(void) const
{
	const CVec3& vecRes = (const CVec3&)(*this)[12];
	VALIDATE_PTR(&vecRes);
	return vecRes;
}

FORCEINLINE CMatrix44 CMatrix44::FromQuaternion(const CQuaternion& q)
{
  CVec3 v = CVec3(q.x, q.y, q.z);
	const CVec3 v2 = v + v;
	CFLOAT xx=1.f-v2.x*q.x;	CFLOAT yy=v2.y*q.y;		CFLOAT xw=v2.x*q.w;
	CFLOAT xy=v2.y*q.x;			CFLOAT yz=v2.z*q.y;		CFLOAT yw=v2.y*q.w;
	CFLOAT xz=v2.z*q.x;			CFLOAT zz=v2.z*q.z;		CFLOAT zw=v2.z*q.w;
	CMatrix44 M(1.f-yy-zz,				xy+zw,					xz-yw,	0,
							xy-zw,						xx-zz,					yz+xw,	0,
							xz+yw,						yz-xw,					xx-yy,	0,
							0,								0,							0,			1.f);
	VALIDATE_PTR(&M);	
	return M;
}

FORCEINLINE void CMatrix44::FromPosRot(const CVec3 &vecPos, const CQuaternion &qRot)
{
	FromPosRot(vecPos, CMatrix44(qRot));
}

FORCEINLINE void CMatrix44::FromPosRot(const CVec3 &vecPos, const CMatrix44 &matRot)
{
	(*this) = matRot;
	(*this)[12] = vecPos.x;
	(*this)[13] = vecPos.y;
	(*this)[14] = vecPos.z;
	VALIDATE;
}

FORCEINLINE void CMatrix44::FromDirection(const CVec3 &vecDir)
{
	assert(vecDir.NotNULL());
	CVec3 zAxis(vecDir);
	zAxis.Normalize();

	// Build the Y vector of the matrix (handle the degenerate case
	// in the way that 3DS does) -- This is not the TRUE vector, only
	// a reference vector.

	CVec3 yAxis;

	if (!zAxis.x && !zAxis.z)
		yAxis = CVec3(-zAxis.y, 0.0f, 0.0f );
	else
		yAxis = CVec3(0.0f, 1.0f, 0.0f);

	// Build the X axis vector based on the two existing vectors

	CVec3 xAxis = yAxis.Cross( zAxis );
	xAxis.Normalize();

	// Correct the Y reference vector

	yAxis = xAxis.Cross( zAxis );
	yAxis.Normalize();
	yAxis = -yAxis;

	(*this)[0] = xAxis.x;
	(*this)[1] = xAxis.y;
	(*this)[2] = xAxis.z;
  (*this)[3] = 0.f;

	(*this)[4] = yAxis.x;
	(*this)[5] = yAxis.y;
	(*this)[6] = yAxis.z;
  (*this)[7] = 0.f;

	(*this)[8] = zAxis.x;
	(*this)[9] = zAxis.y;
	(*this)[10] = zAxis.z;
  (*this)[11] = 0.f;

  (*this)[12] = 0;
  (*this)[13] = 0;
  (*this)[14] = 0;
  (*this)[15] = 1;

	VALIDATE;
}

FORCEINLINE void CMatrix44::FromPosRotScale(const CVec3 &vecPos, const CQuaternion &qRot, const CVec3 &vecScale)
{
	FromPosRotScale(vecPos, CMatrix44(qRot), vecScale);
}

FORCEINLINE void CMatrix44::FromPosRotScale(const CVec3 &vecPos, const CMatrix44 &matRot, const CVec3 &vecScale)
{
	(*this) = CMatrix44(1);
	SetScale(vecScale);
	(*this) = (*this) * matRot;
	(*this)[12] = vecPos.x;
	(*this)[13] = vecPos.y;
	(*this)[14] = vecPos.z;
	VALIDATE;
}

FORCEINLINE CMatrix44 CMatrix44::GetRotation(const bool bNormalize) const
{
	CMatrix44 matAlLCopy(*this);
	CVec3 vecPos(matAlLCopy[12],matAlLCopy[13],matAlLCopy[14]);
	matAlLCopy[12] = 0;
	matAlLCopy[13] = 0;
	matAlLCopy[14] = 0;

	matAlLCopy[03] = 0;
	matAlLCopy[07] = 0;
	matAlLCopy[11] = 0;

	CMatrix44 matAdd;

	if(bNormalize)
	{
		CVec3 vec1 = CVec3(0,0,1) * matAlLCopy;
		vec1.Normalize();
		matAdd.FromDirection(vec1);
	}
	else
	{
		matAdd = matAlLCopy;
	}

	VALIDATE_PTR(&matAdd);
	return matAdd;
}

FORCEINLINE CMatrix44 CMatrix44::Slerp(const CMatrix44 &q1, const CMatrix44 &q2, CFLOAT t)
{
	if(fabsf(t) < FLOAT_EQUALITY_FUDGE)
		return q1;
	if(fabsf(t) > 1 - FLOAT_EQUALITY_FUDGE)
		return q2;
	CMatrix44 out;
	for(int i=0;i<16;i++)
		out[i] = q1[i]*(1-t)+q2[i]*t;
	VALIDATE_PTR(&out);
	return out;
}

FORCEINLINE void CMatrix44::FromYPR(CFLOAT fYaw, CFLOAT fPitch, CFLOAT fRoll) 
{ 
	CQuaternion q;
	q.FromRotation(CVec3(fYaw, fPitch, fRoll));
	(*this) = FromQuaternion(q);
	VALIDATE;
}

FORCEINLINE CMatrix44 MatrixRotationX(CMatrix44 * mat, CFLOAT yaw)
{
	const CVec3 trans = mat->GetTranslation();
	CQuaternion q;
	q.FromRotation(CVec3(yaw, 0.0f, 0.0f));
	*mat = mat->FromQuaternion(q);
	VALIDATE_PTR(mat);
	mat->SetTranslation(trans);
	return *mat;
}

FORCEINLINE CMatrix44 MatrixRotationY(CMatrix44 * mat, CFLOAT pitch)
{
	const CVec3 trans = mat->GetTranslation();
	CQuaternion q;
	q.FromRotation(CVec3(0.0f, pitch, 0.0f));
	*mat = mat->FromQuaternion(q);
	VALIDATE_PTR(mat);
	mat->SetTranslation(trans);
	return *mat;
}

FORCEINLINE CMatrix44 MatrixRotationZ(CMatrix44 * mat, CFLOAT roll)
{
	const CVec3 trans = mat->GetTranslation();
	CQuaternion q;
	q.FromRotation(CVec3(0.0f, 0.0f, roll));
	*mat = mat->FromQuaternion(q);
	VALIDATE_PTR(mat);
	mat->SetTranslation(trans);
	return *mat;
}

FORCEINLINE float CMatrix44::GetUniformScale(const size_t row) const
{
	CFLOAT x = m[row][0];
	CFLOAT y = m[row][1];
	CFLOAT z = m[row][2];

	CFLOAT len = x*x + y*y + z*z;
	if (len > pgEPS)
		return sqrtf(len);

	return 1.f;
}

FORCEINLINE void CMatrix44::SetScale(const CVec3& v)
{
  const CMatrix44 out(v.x,  0,  0,   0,
											0,    v.y,0,   0,
											0,    0,  v.z, 0,
											0,    0,  0,   1);
	(*this) = out * (*this);
	VALIDATE;
}
// Standalone matrix construction functions
FORCEINLINE CMatrix44 MatrixPerspectiveFovLH(CFLOAT fovy, CFLOAT Aspect, CFLOAT zn, CFLOAT zf)
{
	CFLOAT yScale = 1.f / tanf(fovy * .5f);
	CFLOAT xScale = yScale / Aspect;
	const CMatrix44 matT(	xScale,		0,			0,							 0, 
												0,				yScale, 0,							 0, 
												0,				0,			zf/(zf-zn),			 1.f, 
												0,				0,			-zn*zf/(zf-zn),	 0);
	VALIDATE_PTR(&matT);
	return matT;
}

FORCEINLINE CMatrix44 MatrixRotationYawPitchRoll(CFLOAT Yaw, CFLOAT Pitch, CFLOAT Roll)
{
	CMatrix44 matT(1);
	matT.FromYPR(Yaw, Pitch, Roll);
	return matT;
}

FORCEINLINE CMatrix44 MatrixOrthoOffCenterLH(CFLOAT l, CFLOAT r, CFLOAT b, CFLOAT t, CFLOAT zn, CFLOAT zf)
{
	const CMatrix44 matT(	2.0f/(r-l),		0,			      0,			    0, 
												0,				  2.0f/(t-b),	    0,					0, 
												0,				  0,			      1.0f/(zf-zn),	0, 
												(l+r)/(l-r),(t+b)/(b-t),  zn/(zn-zf),	1.0f);
	VALIDATE_PTR(&matT);
	return matT;
}

FORCEINLINE CMatrix44 MatrixOrthoLH(CFLOAT w, CFLOAT h, CFLOAT zn, CFLOAT zf)
{
  const CMatrix44 matT(	2.f/w,		0,			0,							 0, 
    0,				2.f/h,	0,							 0, 
    0,				0,			1.f/(zf-zn),		 0, 
    0,				0,			zn/(zn-zf),			1.f);
  VALIDATE_PTR(&matT);
  return matT;
}


FORCEINLINE CMatrix44 MatrixPerspectiveLH(CFLOAT w, CFLOAT h, CFLOAT zn, CFLOAT zf)
{
	const CMatrix44 matT(	2.f*zn/w,	0,				0,							0, 
												0,				2.f*zn/h,	0,							0, 
												0,				0,				zf/(zf-zn),			1.f, 
												0,				0,				zn*zf/(zn-zf),	0);
	VALIDATE_PTR(&matT);
	return matT;
}

FORCEINLINE CMatrix44 MatrixReflect(const CPlane& plane)
{
//	assert(!_isnan(plane.GetD()));	// in order to check if the plane in normalized (the check is inside GetD())
	const CVec4& P = (CVec4&)plane;
	const CMatrix44 matT(	-2 * P.x * P.x + 1,  -2 * P.y * P.x,      -2 * P.z * P.x,        0,
												-2 * P.x * P.y,      -2 * P.y * P.y + 1,  -2 * P.z * P.y,        0,
												-2 * P.x * P.z,      -2 * P.y * P.z,      -2 * P.z * P.z + 1,    0,
												-2 * P.x * P.w,      -2 * P.y * P.w,      -2 * P.z * P.w,        1);
	VALIDATE_PTR(&matT);
	return matT;
}

FORCEINLINE CMatrix44 MatrixLookAtLH(const CVec3& nEye, const CVec3& nAt, const CVec3& nUp)
{
	assert(nEye != nAt);
	assert(nUp != CVec3(0,0,0));

	const CVec3 EyeDir = nAt - nEye;

	const CVec3 R2 = EyeDir.GetNormalizedFast();
	const CVec3 R0 = nUp.Cross(R2).GetNormalizedFast();
	const CVec3 R1 = R2.Cross(R0);

	const CVec3 NegEyePos = -nEye;

	CFLOAT D0 = R0.Dot(NegEyePos);
	CFLOAT D1 = R1.Dot(NegEyePos);
	CFLOAT D2 = R2.Dot(NegEyePos);

	CMatrix44 M;
	((CVec3&)M.m[0][0]) = R0;
	M.m[0][3] = D0;
	((CVec3&)M.m[1][0]) = R1;
	M.m[1][3] = D1;
	((CVec3&)M.m[2][0]) = R2;
	M.m[2][3] = D2;
	((CVec4&)M.m[3][0]) = CVec4(0,0,0,1);
	M = M.GetTransposed();

	VALIDATE_PTR(&M);
	return M;
}

FORCEINLINE CMatrix44 MatrixLookAtRH(const CVec3& nEye, const CVec3& nAt, const CVec3& nUp)
{
	assert(nEye != nAt);
	assert(nUp != CVec3(0,0,0));

	const CVec3 zaxis = (nEye - nAt).GetNormalizedFast();

	const CVec3 xaxis = nUp.Cross(zaxis).GetNormalizedFast();
	const CVec3 yaxis = zaxis.Cross(xaxis);

	CFLOAT D0 = -xaxis.Dot(nEye);
	CFLOAT D1 = -yaxis.Dot(nEye);
	CFLOAT D2 = -zaxis.Dot(nEye);

	const CMatrix44 M(xaxis.x, yaxis.x, zaxis.x, 0,
										xaxis.y, yaxis.y, zaxis.y, 0,
										xaxis.z, yaxis.z, zaxis.z, 0,
										D0,		D1,		D2,		1);
	VALIDATE_PTR(&M);
	return M;
}

#endif // __MATH_MATRIX_INL__