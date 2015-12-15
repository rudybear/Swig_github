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

struct CVec3;
struct CVec4;
struct CQuaternion;
struct CPlane;

struct /*_DECLSPEC_ALIGN_16_*/ CMatrix44
{
	union {
#ifdef USE_SSE
		__m128 r[4];
#endif
		struct {
			FLOAT _11, _12, _13, _14;
			FLOAT _21, _22, _23, _24;
			FLOAT _31, _32, _33, _34;
			FLOAT _41, _42, _43, _44;
		};
		FLOAT m[4][4];
	};

	FORCEINLINE CMatrix44() {};
	FORCEINLINE CMatrix44(int) { Identity(); }
	FORCEINLINE explicit CMatrix44(CFLOAT* pData) { memcpy(this, pData, sizeof(*this)); VALIDATE; }
	FORCEINLINE CMatrix44(CFLOAT __11, CFLOAT __12, CFLOAT __13, CFLOAT __14,
		CFLOAT __21, CFLOAT __22, CFLOAT __23, CFLOAT __24,
		CFLOAT __31, CFLOAT __32, CFLOAT __33, CFLOAT __34,
		CFLOAT __41, CFLOAT __42, CFLOAT __43, CFLOAT __44) :
		_11(__11), _12(__12), _13(__13), _14(__14),
		_21(__21), _22(__22), _23(__23), _24(__24),
		_31(__31), _32(__32), _33(__33), _34(__34),
		_41(__41), _42(__42), _43(__43), _44(__44)
	{
		VALIDATE;
	};
	FORCEINLINE explicit CMatrix44(const CQuaternion& Rotation);
	//CMatrix44 (const CVec3& Position, const CQuaternion& Rotation);
	FORCEINLINE const bool operator != (const CMatrix44& mx) const { return memcmp(this, &mx, sizeof(*this)) != 0; }
	FORCEINLINE CMatrix44& operator = (const CMatrix44& mx)
	{
		_11 = mx._11; _12 = mx._12; _13 = mx._13; _14 = mx._14;
		_21 = mx._21; _22 = mx._22; _23 = mx._23; _24 = mx._24;
		_31 = mx._31; _32 = mx._32; _33 = mx._33; _34 = mx._34;
		_41 = mx._41; _42 = mx._42; _43 = mx._43; _44 = mx._44;
		VALIDATE;
		return *this;
	};
	FORCEINLINE CMatrix44 operator * (const CMatrix44& mat) const;
	FORCEINLINE CVec3 operator* (const CVec3& vec) const;
	FORCEINLINE const FLOAT& operator[](const size_t n) const { assert(n < 16); return *(&m[0][0] + n); }
	FORCEINLINE FLOAT& operator[](const size_t n) { assert(n < 16); return *(&m[0][0] + n); }
	FORCEINLINE FLOAT& GetElement(const size_t n) { assert(n < 16); return *(&m[0][0] + n); }
	FORCEINLINE const FLOAT& operator() (const size_t row, const size_t col) const { assert(row < 4 && col < 4); return m[row][col]; }
	FORCEINLINE FLOAT& operator()(const size_t row, const size_t col) { assert(row < 4 && col < 4); return m[row][col]; }

	FORCEINLINE const CVec4* Vec4() const { return (const CVec4*)(&m[0][0]); }
	FORCEINLINE const CVec4& Row(const size_t n) const { return *(const CVec4*)(&m[n][0]); }
	FORCEINLINE const CVec3& Row3(const size_t n) const { return *(const CVec3*)(&m[n][0]); }
	FORCEINLINE CVec3 Col3(const size_t n) const {
		CVec3 v = CVec3(m[0][n], m[1][n], m[2][n]);
		return v;
	}

	FORCEINLINE void FromDirection(const CVec3 &vecDir);
	FORCEINLINE void FromPosRot(const CVec3 &vecPos, const CQuaternion &qRot);
	FORCEINLINE void FromPosRotScale(const CVec3 &vecPos, const CQuaternion &qRot, const CVec3 &vecScale);
	FORCEINLINE void FromYPR(const float fYaw, const float fPitch, const float fRoll);

	FORCEINLINE void FromPosRot(const CVec3 &vecPos, const CMatrix44 &matRot);
	FORCEINLINE void FromPosRotScale(const CVec3 &vecPos, const CMatrix44 &matRot, const CVec3 &vecScale);
	FORCEINLINE CMatrix44 GetInvert(void) const;

	FORCEINLINE CQuaternion GetRotQuaternion(void) const;

	FORCEINLINE CVec3 GetScale() const { return CVec3(GetUniformScale(0), GetUniformScale(1), GetUniformScale(2)); }
	FORCEINLINE float GetUniformScale(const size_t row = 0) const;

	FORCEINLINE CMatrix44& Transpose();
	FORCEINLINE CMatrix44 GetTransposed() const;

	FORCEINLINE void SetTranslation(const CVec3& vecPos);
	FORCEINLINE const CVec3& GetTranslation(void) const;
	FORCEINLINE CMatrix44 GetRotation(const bool bNormalize = false) const;

	FORCEINLINE CMatrix44& Identity();
	FORCEINLINE static CMatrix44 Slerp(const CMatrix44 &q1, const CMatrix44 &q2, CFLOAT t);
	FORCEINLINE static CMatrix44 FromQuaternion(const CQuaternion& q);

	FORCEINLINE void SetUniformScale(CFLOAT s) { SetScale(CVec3(s, s, s)); }
	FORCEINLINE void SetScale(const CVec3& v);

#ifdef USE_D3DX
	FORCEINLINE CMatrix44(const D3DXMATRIX& m) :
		_11(m._11), _12(m._12), _13(m._13), _14(m._14),
		_21(m._21), _22(m._22), _23(m._23), _24(m._24),
		_31(m._31), _32(m._32), _33(m._33), _34(m._34),
		_41(m._41), _42(m._42), _43(m._43), _44(m._44)
	{
		VALIDATE;
	};
	FORCEINLINE operator D3DXMATRIX() { return (D3DXMATRIX&)*this; }
#endif

	FORCEINLINE void Validate(void) const
	{
#ifdef _DEBUG_VALIDATE
		for (int i = 0; i < 16; i++)
			CheckFloat((*this)[i]);
#endif
	};
};

// Standalone matrix construction functions
FORCEINLINE CMatrix44 MatrixOrthoLH(CFLOAT w, CFLOAT h, CFLOAT zn, CFLOAT zf);
FORCEINLINE CMatrix44 MatrixOrthoOffCenterLH(CFLOAT l, CFLOAT r, CFLOAT b, CFLOAT t, CFLOAT zn, CFLOAT zf);
FORCEINLINE CMatrix44 MatrixLookAtLH(const CVec3& nEye, const CVec3& nAt, const CVec3& nUp);
FORCEINLINE CMatrix44 MatrixLookAtRH(const CVec3& nEye, const CVec3& nAt, const CVec3& nUp);
FORCEINLINE CMatrix44 MatrixRotationYawPitchRoll(CFLOAT Yaw, CFLOAT Pitch, CFLOAT Roll);
FORCEINLINE CMatrix44 MatrixPerspectiveFovLH(CFLOAT fovy, CFLOAT Aspect, CFLOAT zn, CFLOAT zf);
FORCEINLINE CMatrix44 MatrixPerspectiveLH(CFLOAT w, CFLOAT h, CFLOAT zn, CFLOAT zf);
FORCEINLINE CMatrix44 MatrixReflect(const CPlane& plane);
FORCEINLINE CMatrix44 MatrixRotationX(CMatrix44 * mat, CFLOAT yaw);
FORCEINLINE CMatrix44 MatrixRotationY(CMatrix44 * mat, CFLOAT pitch);
FORCEINLINE CMatrix44 MatrixRotationZ(CMatrix44 * mat, CFLOAT roll);