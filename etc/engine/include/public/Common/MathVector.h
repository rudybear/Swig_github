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

#include <math.h>
#include "OurMath.h"

struct CVec2;
struct CVec3;
struct CVec4;
struct CVec4A;
struct CMatrix44;
struct CQuaternion;
//struct RenderViewport;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                      CVec2
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C++ interface
struct CVec2 
{
	FLOAT x;
	FLOAT y;

	//Ctors
	CVec2() { };

	CVec2(int): x(0), y(0) {};

	inline CVec2(float _x, float _y) : x(_x), y(_y) 
	{ 
		VALIDATE;
	};

	CVec2& operator += ( const CVec2& v)
	{
		x += v.x;
		y += v.y;
		VALIDATE;
		return *this;
	}

	CVec2& operator -= ( const CVec2& v)
	{
		x -= v.x;
		y -= v.y;
		VALIDATE;
		return *this;
	}

	CVec2& operator *= ( FLOAT s)
	{
		x *= s;
		y *= s;
		VALIDATE;
		return *this;
	}

	CVec2& operator /= ( FLOAT s)
	{
		x /= s;
		y /= s;
		VALIDATE;
		return *this;
	}

	bool operator == ( const CVec2& v) const
	{
		return v.x == x && v.y == y;
	}

	bool operator != ( const CVec2& v) const
	{
		return v.x != x || v.y != y;
	}

	FORCEINLINE CVec2 operator + (const CVec2& v) const
	{
		return CVec2(x+v.x, y+v.y);
	}

	FORCEINLINE CVec2 operator - (const CVec2& v) const 
	{
		return CVec2(x-v.x, y-v.y);
	}

	FORCEINLINE CVec2 operator * (const float f) const 
	{
		return CVec2(x*f, y*f);
	}

	FORCEINLINE CVec2 operator / (const float f) const 
	{
		return CVec2(x/f, y/f);
	}

	FORCEINLINE bool NotNULL(void) const
	{
		return fabsf(x) > pgEPS || fabsf(y) > pgEPS;
	}

	FORCEINLINE FLOAT Dot(const CVec2& v) const
	{
		return x*v.x + y*v.y;
	}

	FORCEINLINE FLOAT Length() const 
	{
		return (FLOAT)sqrt(x*x + y*y);
	}

	FORCEINLINE FLOAT LengthSq() const
	{
		return x*x + y*y;
	};

	FORCEINLINE CVec2 Lerp(const CVec2& v, const float t)
	{
		// V0 + t * (V1 - V0)
		return CVec2(x + t *(v.x - x), y + t *(v.y - y));
	}

	FORCEINLINE CVec2& Normalize()
	{
		FLOAT lengthSq = LengthSq();
		if (lengthSq > 0.0f)
		{
			FLOAT length = 1.0f / (FLOAT)sqrt(lengthSq);
			x *= length;
			y *= length;
			VALIDATE;
		}
		return *this;
	}

	FORCEINLINE CVec2& NormalizeFast()
	{
		FLOAT length = 1.0f/Length();
		x *= length;
		y *= length;
		VALIDATE;
		return *this;
	}

	FORCEINLINE CVec2 GetNormalized() const
	{
		CVec2 tmp(*this);
		tmp.Normalize();
		return tmp;
	}

	FORCEINLINE CVec2 GetNormalizedFast() const
	{
		CVec2 tmp(*this);
		tmp.NormalizeFast();
		return tmp;
	}

	FORCEINLINE CVec2 operator - () const 
	{
		return CVec2(-x, -y); 
	};

#ifdef USE_D3DX
	FORCEINLINE CVec2(D3DXVECTOR2 v) : x(v.x), y(v.y)
	{
		VALIDATE;
	};
#endif

	FORCEINLINE void Validate(void)
	{
#ifdef _DEBUG_VALIDATE
		CheckFloat(x);
		CheckFloat(y);
#endif
	};

	CVec2 &operator =(const CVec4 &v);

	CVec2 &operator =(const CVec3 &v);
};

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)

FORCEINLINE CVec2  CVec2BaryCentric(const CVec2& v1, const CVec2& v2, const CVec2& v3, float f, float g)
{
	return CVec2(v1.x+f*(v2.x-v1.x)+g*(v3.x-v1.x), v1.y+f*(v2.y-v1.y)+g*(v3.y-v1.y));
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                      CVec3
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct 
#ifdef USE_D3DX
	DLLIMPORT
#endif
	CVec3
{
	FLOAT x, y, z;

	FORCEINLINE CVec3(const CIdentity*) : x(0), y(0),  z(0) {}

	FORCEINLINE CVec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) 
	{
		VALIDATE;
	};

	// Ctors
	FORCEINLINE CVec3() {};

	FORCEINLINE explicit CVec3(const CQuaternion& q);

	FORCEINLINE explicit CVec3(const CMatrix44& mat);

	FORCEINLINE void Set(float _x, float _y, float _z) 
	{
		x = _x; y = _y; z =_z;
		VALIDATE;
	}

	FORCEINLINE CVec3 &operator =(const CVec3 &rhv) 
	{
		x = rhv.x;
		y = rhv.y;
		z = rhv.z;
		VALIDATE;
		return *this;
	}

	CVec3& operator += ( const CVec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		VALIDATE;
		return *this;
	}

	CVec3& operator -= ( const CVec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		VALIDATE;
		return *this;
	}

	CVec3& operator *= ( FLOAT s)
	{
		x *= s;
		y *= s;
		z *= s;
		VALIDATE;
		return *this;
	}

	CVec3& operator /= ( FLOAT s)
	{
		x /= s;
		y /= s;
		z /= s;
		VALIDATE;
		return *this;
	}

	bool operator == ( const CVec3& v) const
	{
		return v.x == x && v.y == y && v.z == z;
	}

	bool operator != ( const CVec3& v) const
	{
		return v.x != x || v.y != y || v.z != z;
	}

	CVec3& operator =(const CVec4 &v);

	CVec3& operator =(const CVec2 &v);

	FORCEINLINE CVec3 operator - () const 
	{
		return CVec3(-x, -y, -z);
	}

	FORCEINLINE CVec3 operator + (const CVec3& v) const 
	{
		return CVec3(x+v.x, y+v.y, z+v.z);
	}

	FORCEINLINE CVec3 operator - (const CVec3& v) const 
	{
		return CVec3(x-v.x, y-v.y, z-v.z);
	}

	FORCEINLINE CVec3 operator * (const FLOAT f)  const 
	{
		return  CVec3(x*f, y*f, z*f);
	}

	FORCEINLINE CVec3 operator / (const FLOAT f)  const 
	{
		return CVec3(x/f, y/f, z/f); 
	}

	// Per-component vector division
	FORCEINLINE CVec3 operator / (const CVec3& v) const 
	{ 
		return CVec3(x/v.x, y/v.y, z/v.z);
	}

	//Per-component vector multiplication
	FORCEINLINE CVec3 operator * (const CVec3& v) const
	{
		return CVec3(x*v.x, y*v.y, z*v.z);
	}

	FORCEINLINE CVec3 operator * (const CMatrix44& mat) const;

	friend CVec3 operator * ( FLOAT, const CVec3& );

	FORCEINLINE FLOAT LengthSq() const 
	{
		return x*x + y*y + z*z;
	}

	FORCEINLINE FLOAT Length() const 
	{
		return (FLOAT)sqrt(x*x + y*y + z*z);
	}

	FORCEINLINE FLOAT Dot(const CVec3& v) const 
	{
		return x*v.x + y*v.y + z*v.z;
	}

	// casting
	operator FLOAT* ()
	{
		return &x;
	}

	operator const FLOAT* () const
	{
		return &x;
	}

	FORCEINLINE CVec3 Cross(const CVec3& v1) const
	{
		return CVec3(	(y * v1.z) - (z * v1.y),
			(z * v1.x) - (x * v1.z),
			(x * v1.y) - (y * v1.x));
	}

	FORCEINLINE CVec3 Lerp(CVec3& v, float t) const
	{
		return CVec3(x + t *(v.x - x), y + t *(v.y - y), z + t *(v.z - z));
	}

	FORCEINLINE CVec3 TransformNormal(const CMatrix44& mat) const;

	FORCEINLINE CVec3 TransformPoint(const CMatrix44& mat) const;

	FORCEINLINE CVec3& SetScale(const float v) {
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	//! check for max bounds
	FORCEINLINE void CheckMax(const CVec3 &other)
	{
		x = MAX(other.x, x);
		y = MAX(other.y, y);
		z = MAX(other.z, z);
	}
	//! check for min bounds
	FORCEINLINE void CheckMin(const CVec3 &other)
	{
		x = MIN(other.x, x);
		y = MIN(other.y, y);
		z = MIN(other.z, z);
	}

	FORCEINLINE CVec3 Scale(const float v) 
	{
		return CVec3( x * v, y * v, z * v);
	}

	FORCEINLINE bool NotNULL(void) const
	{
		return fabsf(x) > pgEPS || fabsf(y) > pgEPS || fabsf(z) > pgEPS;
	}

	FORCEINLINE CVec3& NormalizeFast (void)
	{
		VALIDATE;
		FLOAT length = 1.0f/Length();
		x *= length;
		y *= length;
		z *= length;
		VALIDATE;
		return *this;

	}

	FORCEINLINE CVec3& Normalize (void)
	{
		VALIDATE;
		FLOAT lengthSq = LengthSq();
		if (lengthSq > 0.0f)
		{
			FLOAT length = 1.0f / (FLOAT)sqrt(lengthSq);
			x *= length;
			y *= length;
			z *= length;
			VALIDATE;
		}
		return *this;
	}

	FORCEINLINE CVec3 GetNormalized() const
	{
		CVec3 tmp(*this);
		tmp.Normalize();
		return tmp;
	}

	FORCEINLINE CVec3 GetNormalizedFast() const
	{
		CVec3 tmp(*this);
		tmp.NormalizeFast();
		return tmp;
	}

	CVec3 GetRotation(void)
	{
		FLOAT fRotX = 0.f;
		FLOAT fRotY = 0.f;

		if(fabsf(z) < pgEPS)
		{
			if(x >= 0.f)
				fRotX = 90.f*PI180;
			else
				fRotX = 270.f*PI180;
		}
		else
		{
			if(fabsf(x) > pgEPS)
			{
				fRotX = atan2f(x,z);
			}
			else if(z > 0.f)
			{
				fRotX = 0.f;
			}
			else
			{
				fRotX = 180.f*PI180;
			}
		}

		if(fabsf(y) < pgEPS)
		{
			fRotY = 0.f;
		}
		else
		{
			if(fabsf(x) < pgEPS && fabsf(z) < pgEPS)
			{
				if(y > 0.f)
					fRotY = 90.f*PI180;
				else
					fRotY = -90.f*PI180;
			}
			else
			{
				float len = sqrtf(x*x+z*z);
				fRotY = atan2f(y,len); //гиппотенуза... да
			}
		}

		CVec3 out;
		out.x = fRotX;
		out.y = fRotY;
		return out;
	}

	FLOAT GetDistance(const CVec3& v) const
	{
		return (FLOAT)sqrtf((x-v.x)*(x-v.x)+(y-v.y)*(y-v.y)+(z-v.z)*(z-v.z)); 
	}

	FLOAT GetDistanceSq(const CVec3& v) const
	{
		return (FLOAT)(x-v.x)*(x-v.x)+(y-v.y)*(y-v.y)+(z-v.z)*(z-v.z); 
	}

	void SetLength(FLOAT s)
	{
		FLOAT length = LengthSq();
		if (s < pgEPS)
			return;
		length = s * (1.0f/sqrtf(length));
		x *= length; 
		y *= length;
		z *= length;
	}

	inline void Validate(void) const
	{
#ifdef _DEBUG_VALIDATE
		CheckFloat(x);
		CheckFloat(y);
		CheckFloat(z);
#endif
	};

#ifdef USE_D3DX
	FORCEINLINE CVec3(const D3DXVECTOR3& v) : x(v.x), y(v.y), z(v.z) 
	{
		VALIDATE;
	};

	FORCEINLINE CVec3 &operator =(const D3DXVECTOR3 &rhv) 
	{
		x = rhv.x;
		y = rhv.y;
		z = rhv.z;
		VALIDATE;
		return *this;
	}
#endif

};

FORCEINLINE CVec3 operator * ( FLOAT f, const CVec3& v)
{
	return CVec3(v.x * f, v.y * f, v.z * f);
}

#ifdef USE_D3DX
FORCEINLINE D3DXVECTOR3* Vec3ToD3DXVECTOR3(CVec3 * v)
{
	return (D3DXVECTOR3*)v;
}
#endif



struct CVec4 
{
	CVec4() {};

	FLOAT x, y, z, w;

	FORCEINLINE CVec4(FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _w) : x(_x), y(_y), z(_z), w(_w) {};

	inline explicit CVec4(uint32 dColor) {x = ((dColor>>0)&0xff)/255.0f; y = ((dColor>>8)&0xff)/255.0f; z = ((dColor>>16)&0xff)/255.0f; w = ((dColor>>24)&0xff)/255.0f; }

	FORCEINLINE explicit CVec4(const FLOAT c) : x(c), y(c), z(c), w(c) {};

	FORCEINLINE CVec4(const CVec3& v, float _w) : x(v.x), y(v.y), z(v.z), w(_w) {};

	FORCEINLINE CVec4(CQuaternion&);

	FORCEINLINE CVec4 operator + (const CVec4& v) const
	{
		return CVec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	FORCEINLINE CVec4 operator - (const CVec4& v) const
	{
		return CVec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	FORCEINLINE CVec4 operator * (const CVec4& v) const
	{
		return CVec4(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	FORCEINLINE CVec4 operator * (const FLOAT f) const
	{
		return CVec4(x * f, y * f, z * f, w * f);
	}

	FORCEINLINE CVec4 operator / (const FLOAT f) const
	{
		return CVec4(x / f, y / f, z / f, w / f);
	}

	operator FLOAT* () 
	{
		return &x;
	}
	operator const FLOAT* () const
	{
		return &x;
	}

	// assignment operators
	CVec4& operator += ( const CVec4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	CVec4& operator -= ( const CVec4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	CVec4& operator *= ( FLOAT s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	CVec4& operator /= ( FLOAT s)
	{
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}

	// unary operators
	CVec4 operator + () const
	{
		return *this;
	}

	CVec4 operator - () const
	{
		return CVec4(-x, -y, -z, -w);
	}


	friend CVec4 operator * ( FLOAT, const CVec4& );

	bool operator == ( const CVec4& v) const
	{
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	bool operator != ( const CVec4& v) const
	{	
		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	FORCEINLINE CVec4 operator * (const CMatrix44&) const;

	FORCEINLINE CVec4 operator * (const CQuaternion&) const;

	FORCEINLINE bool NotNULL(void) const
	{
		return fabsf(x) > pgEPS || fabsf(y) > pgEPS || fabsf(z) > pgEPS || fabsf(w) > pgEPS;
	}

	FORCEINLINE FLOAT Dot(const CVec4& v) const 
	{
		return x*v.x + y*v.y + z*v.z + w*w;
	}

  void Set(FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _w)
  {
    x = _x;
    y = _y;
    z = _z;
    w = _w;
  }

	FORCEINLINE CVec4 Cross(const CVec4& v1, const CVec4& v2, const CVec4& v3)
	{
		CVec4 res;
		res.x = (((v2.z*v3.w)-(v2.w*v3.z))*v1.y)-(((v2.y*v3.w)-(v2.w*v3.y))*v1.z)+(((v2.y*v3.z)-(v2.z*v3.y))*v1.w);
		res.y = (((v2.w*v3.z)-(v2.z*v3.w))*v1.x)-(((v2.w*v3.x)-(v2.x*v3.w))*v1.z)+(((v2.z*v3.x)-(v2.x*v3.z))*v1.w);
		res.z = (((v2.y*v3.w)-(v2.w*v3.y))*v1.x)-(((v2.x*v3.w)-(v2.w*v3.x))*v1.y)+(((v2.x*v3.y)-(v2.y*v3.x))*v1.w);
		res.w = (((v2.z*v3.y)-(v2.y*v3.z))*v1.x)-(((v2.z*v3.x)-(v2.x*v3.z))*v1.y)+(((v2.y*v3.x)-(v2.x*v3.y))*v1.z);

		return res;
	}


	FORCEINLINE FLOAT Length() const 
	{
		return (FLOAT) sqrt(x*x + y*y + z*z + w*w);
	}

	FORCEINLINE FLOAT LengthSq() const 
	{
		return x*x + y*y + z*z + w*w;
	}

	FORCEINLINE CVec4 Lerp(const CVec4& v, const FLOAT t)
	{
		return CVec4(x + t *(v.x - x), y + t *(v.y - y), z + t *(v.z - z), w + t *(v.w - w));
	}


	FORCEINLINE CVec4& NormalizeFast (void)
	{
		VALIDATE;
		FLOAT length = 1.0f/Length();
		x *= length;
		y *= length;
		z *= length;
		w *= length;
		VALIDATE;
		return *this;

	}

	FORCEINLINE CVec4& Normalize (void)
	{
		VALIDATE;
		FLOAT lengthSq = LengthSq();
		if (lengthSq > 0.0f)
		{
			FLOAT length = 1.0f / (FLOAT)sqrt(lengthSq);
			x *= length;
			y *= length;
			z *= length;
			w *= length;
			VALIDATE;
		}
		return *this;
	}

	FORCEINLINE CVec4 GetNormalized() const
	{
		CVec4 tmp(*this);
		tmp.Normalize();
		return tmp;
	}

	FORCEINLINE CVec4 GetNormalizedFast() const
	{
		CVec4 tmp(*this);
		tmp.NormalizeFast();
		return tmp;
	}


	FORCEINLINE CVec4 TransformPoint(const CMatrix44& mat) const;

	FORCEINLINE CVec4& operator =(const CVec2 &v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	FORCEINLINE CVec4& operator =(const CVec3 &v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}


	inline void Validate(void)
	{
#ifdef _DEBUG_VALIDATE
		CheckFloat(x);
		CheckFloat(y);
		CheckFloat(z);
		CheckFloat(w);
#endif
	};

#ifdef USE_D3DX
	FORCEINLINE CVec4(D3DXVECTOR4 v) : x(v.x), y(v.y), z(v.z), w(v.w) {};
#endif
};

#include "MathMatrix.h"
#include "MathQuaternion.h"

FORCEINLINE CVec4 operator * ( FLOAT s, const CVec4& v)
{
	return CVec4(v.x * s, v.y * s, v.z * s, v.w * s);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

FORCEINLINE CVec2 CVec2Lerp(const CVec2& v0, const CVec2& v1, float t)
{
	// V0 + t * (V1 - V0)
	return CVec2(v0.x + t *(v1.x - v0.x), v0.y + t *(v1.y - v0.y));
}

FORCEINLINE CVec2 CVec2Normalize(const CVec2& v)
{
	FLOAT LengthSq = v.LengthSq();
	if (LengthSq > 0.0f)
	{
		FLOAT length = 1.0f / (FLOAT)sqrt(LengthSq);
		return CVec2(v*length);
	}

	return CVec2(0);
}


FORCEINLINE CVec2 CVec2NormalizeFast(const CVec2& v)
{
	FLOAT length = 1.0f/v.Length();
	return CVec2(v*length);
}


#ifdef USE_D3DX
FORCEINLINE D3DXVECTOR2* Vec2ToD3DXVECTOR2(CVec2 * v)
{
	return (D3DXVECTOR2*)v;
}
#endif


FORCEINLINE CVec2 &CVec2::operator =(const CVec4 &v) {
	x = v.x;
	y = v.y;
	return *this;
}

FORCEINLINE CVec2 &CVec2::operator =(const CVec3 &v) {
	x = v.x;
	y = v.y;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

FORCEINLINE CVec3* CVec3Cross(CVec3* vOut, const CVec3* v0, const CVec3* v1) 
{
	vOut->x = (v0->y * v1->z) - (v0->z * v1->y);
	vOut->y = (v0->z * v1->x) - (v0->x * v1->z);
	vOut->z = (v0->x * v1->y) - (v0->y * v1->x);

	return vOut;
}

FORCEINLINE FLOAT CVec3Dot(const CVec3* v0, const CVec3* v1) 
{
	return v0->x*v1->x + v0->y*v1->y + v0->z*v1->z;
}

FORCEINLINE CVec3* CVec3Lerp(CVec3 * vOut, const CVec3* v0, const CVec3* v1, float t)
{
	// V0 + t * (V1 - V0)
	vOut->x = v0->x + t * (v1->x - v0->x);
	vOut->y = v0->y + t * (v1->y - v0->y);
	vOut->z = v0->z + t * (v1->z - v0->z);

	return vOut;
}


FORCEINLINE bool operator < (const CVec3& lhs, const CVec3& rhs)
{
	CVec3 d = lhs - rhs;
	const float f = pgEPS;
	if (d.x < -f) return true;
	if (d.x > f) return false;
	if (d.y < -f) return true;
	if (d.y > f) return false;
	if (d.z < -f) return true;
	return false;
}

FORCEINLINE bool operator > (const CVec3& lhs, const CVec3& rhs)
{
	if (lhs == rhs) return false;
	return !(lhs < rhs);
}

FORCEINLINE CVec3 CVec3TransformCoord(CVec3* vOut, const CVec3 * vIn, const CMatrix44 * mIn )
{
#ifdef USE_SSE
	//TODO: Add SIMD support here!

#else

	vOut->x = mIn->_11*vIn->x + mIn->_21*vIn->y + mIn->_31*vIn->z + mIn->_41;
	vOut->y = mIn->_12*vIn->x + mIn->_22*vIn->y + mIn->_32*vIn->z + mIn->_42;
	vOut->z = mIn->_13*vIn->x + mIn->_23*vIn->y + mIn->_33*vIn->z + mIn->_43;

	FLOAT div = (mIn->_14*vIn->x + mIn->_24*vIn->y + mIn->_34*vIn->z + mIn->_44);
	FLOAT w = 1.0f;
	if (div != 0.0f)
	 w /= div;

	vOut->x *= w;
	vOut->y *= w;
	vOut->z *= w;

	return *vOut;
#endif
}

FORCEINLINE CVec4 CVec3Transform(CVec4* vOut, const CVec3 * vIn, const CMatrix44 * mIn )
{
#ifdef USE_SSE
	//TODO: Add SIMD support here!

#else

	vOut->x = mIn->_11*vIn->x + mIn->_21*vIn->y + mIn->_31*vIn->z + mIn->_41;
	vOut->y = mIn->_12*vIn->x + mIn->_22*vIn->y + mIn->_32*vIn->z + mIn->_42;
	vOut->z = mIn->_13*vIn->x + mIn->_23*vIn->y + mIn->_33*vIn->z + mIn->_43;
	vOut->w = mIn->_14*vIn->x + mIn->_24*vIn->y + mIn->_34*vIn->z + mIn->_44;

	return *vOut;
#endif
}


FORCEINLINE CVec3 CVec3TransformNormal(CVec3* vOut, const CVec3 * vIn, const CMatrix44 * mIn )
{
#ifdef USE_SSE
	//TODO: Add SIMD support here!

#else
	vOut->x = mIn->_11*vIn->x + mIn->_21*vIn->y + mIn->_31*vIn->z;
	vOut->y = mIn->_12*vIn->x + mIn->_22*vIn->y + mIn->_32*vIn->z;
	vOut->z = mIn->_13*vIn->x + mIn->_23*vIn->y + mIn->_33*vIn->z;
	return *vOut;

	//	return v1;
#endif


}

#include "Public/Render/RenderCommon.h"

FORCEINLINE CVec3 CVec3Project(const CVec3& pt, const RenderViewport& viewport,
							   const CMatrix44& projection, const CMatrix44& view, const CMatrix44& world)
{
	CVec3 point;
	CMatrix44 transform = world * view * projection;

	point = pt.TransformPoint(transform);

	point.x = viewport.X + ( 1.0f + point.x ) * viewport.Width  / 2.0f;
	point.y = viewport.Y + ( 1.0f - point.y ) * viewport.Height / 2.0f;

	point.z = viewport.MinZ + point.z * ( viewport.MaxZ - viewport.MinZ );
	return point;
}

// Project vector from screen space into object space
FORCEINLINE CVec3 CVec3Unproject(const CVec3& pt, const RenderViewport& viewport,
								 const CMatrix44& projection, const CMatrix44& view, const CMatrix44& world)
{
	CVec3 point;
	CMatrix44 transform = world * view * projection;
	transform = transform.GetInvert();

	point.x = 2.0f * ( pt.x - viewport.X ) / viewport.Width - 1.0f;
	point.y = 1.0f - 2.0f * ( pt.y - viewport.Y ) / viewport.Height;
	point.z = ( pt.z - viewport.MinZ) / ( viewport.MaxZ - viewport.MinZ );


	point = point.TransformPoint(transform);
	return point;
}


CVec3::CVec3(const CQuaternion& q)
{
	CMatrix44 matTMP(q);
	CVec3 vecTMP;
	vecTMP = CVec3(0,0,1);
	CVec3TransformCoord(this, &vecTMP, &matTMP);
	VALIDATE;
};

FORCEINLINE CVec3::CVec3(const CMatrix44& mat)
{
	CVec3 vecTMP;
	vecTMP = CVec3(0,0,1);
	CVec3TransformCoord(this, &vecTMP, &mat);
	VALIDATE;
};

FORCEINLINE CVec3 CVec3::operator * (const CMatrix44& mat) const 
{
	CVec3 vecRet;
	CVec3TransformCoord( &vecRet, this, &mat );
	return vecRet;
};

FORCEINLINE CVec3 CVec3::TransformNormal(const CMatrix44& mat) const
{
	CVec3 vecRet;
	CVec3TransformNormal(&vecRet, this, &mat);
	return vecRet;
}

FORCEINLINE CVec3 CVec3::TransformPoint(const CMatrix44& mat) const
{
	CVec3 vecRet;
	CVec3TransformCoord(&vecRet, this, &mat);
	return vecRet;
}

FORCEINLINE CVec3 FromQuakeAngleToDir(int fAngle)
{
	CVec3 ret;
	switch(fAngle)
	{
	case -1:
		ret.x = 0; ret.y = 1; ret.z = 0; break;
	case -2:
		ret.x = 0; ret.y = -1; ret.z = 0; break;
	default:
		ret.x = cos(DegreeToRadian(fAngle)); ret.y = 0; ret.z = sin(DegreeToRadian(fAngle));
	}
	return ret;
}

FORCEINLINE CVec3 FromQuakeAngleToEuler(int fAngle)
{
	CVec3 ret;
	switch(fAngle)
	{
	case -1:
		ret.x = 0; ret.y = DegreeToRadian(90); ret.z = 0; break;
	case -2:
		ret.x = 0; ret.y = DegreeToRadian(-90); ret.z = 0; break;
	default:
		ret.x = DegreeToRadian(fAngle); ret.y = 0; ret.z = 0;
	}

	return ret;
}

FORCEINLINE CVec3 operator * (const CQuaternion &q, const CVec3 &v) 
{
	CVec3 out,r2;
	r2.x = (q.y * v.z - q.z * v.y) + q.w * v.x;
	r2.y = (q.z * v.x - q.x * v.z) + q.w * v.y;
	r2.z = (q.x* v.y - q.y * v.x) + q.w * v.z;
	out.x = (r2.z * q.y - r2.y * q.z); 
	out.x += out.x + v.x;
	out.y = (r2.x * q.z - r2.z * q.x); 
	out.y += out.y + v.y;
	out.z = (r2.y * q.x - r2.x * q.y); 
	out.z += out.z + v.z;
	return out;
}

FORCEINLINE CVec3 operator * (const CVec3 &v, const CQuaternion &q) 
{
	CVec3 out,r2;
	r2.x = (q.z * v.y - q.y * v.z) + q.w * v.x;
	r2.y = (q.x * v.z - q.z * v.x) + q.w * v.y;
	r2.z = (q.y * v.x - q.x * v.y) + q.w * v.z;
	out.x = (r2.y * q.z - r2.z * q.y);
	out.x += out.x + v.x;
	out.y = (r2.z * q.x - r2.x * q.z); 
	out.y += out.y + v.y;
	out.z = (r2.x * q.y - r2.y*q.x); 
	out.z += out.z + v.z;
	return out;
}

FORCEINLINE CVec3 &CVec3::operator =(const CVec4 &v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

FORCEINLINE CVec3 &CVec3::operator =(const CVec2 &v) {
	x = v.x;
	y = v.y;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


FORCEINLINE CVec4::CVec4(CQuaternion& q)
{
	CVec4 Dir = CVec4(0,0,1,1);
	Dir = Dir * q;
	Dir.Normalize();
	x = Dir.x;
	y = Dir.y;
	z = Dir.z;
	w = 1;
}

FORCEINLINE CVec4 CVec4TransformPoint(CVec4 * vOut, const CVec4 * vIn, const CMatrix44* mat)
{
#ifdef USE_SSE
	//TODO: Add SIMD support here!

#else
	CVec4 tmp;
	tmp.x = mat->_11 * vIn->x + mat->_21 * vIn->y + mat->_31 * vIn->z + mat->_41 * vIn->w;
	tmp.y = mat->_12 * vIn->x + mat->_22 * vIn->y + mat->_32 * vIn->z + mat->_42 * vIn->w;
	tmp.z = mat->_13 * vIn->x + mat->_23 * vIn->y + mat->_33 * vIn->z + mat->_43 * vIn->w;
	tmp.w = mat->_14 * vIn->x + mat->_24 * vIn->y + mat->_34 * vIn->z + mat->_43 * vIn->w;
	return tmp;
#endif
}


FORCEINLINE CVec4 CVec4::operator * (const CMatrix44 &f) const {
	CVec4 out;
	return CVec4TransformPoint(&out, this, &f);
}


FORCEINLINE CVec4 CVec4::operator * (const CQuaternion& q) const
{
	CMatrix44 tmpMat(q);
	CVec4 out;
	return CVec4TransformPoint(&out, this, &tmpMat);
}

FORCEINLINE CVec4 CVec4::TransformPoint(const CMatrix44& mat) const
{
#ifdef USE_SSE
	//TODO: Add SIMD support here!

#else
	CVec4 tmp;
	tmp.x = mat._11 * x + mat._21 * y + mat._31 * z + mat._41 * w;
	tmp.y = mat._12 * x + mat._22 * y + mat._32 * z + mat._42 * w;
	tmp.z = mat._13 * x + mat._23 * y + mat._33 * z + mat._43 * w;
	tmp.w = mat._14 * x + mat._24 * y + mat._34 * z + mat._43 * w;
	return tmp;
#endif
}

FORCEINLINE CVec4* CVec4Lerp(CVec4 * vOut, const CVec4* v0, const CVec4* v1, float t)
{
	// V0 + t * (V1 - V0)
	vOut->x = v0->x + t * (v1->x - v0->x);
	vOut->y = v0->y + t * (v1->y - v0->y);
	vOut->z = v0->z + t * (v1->z - v0->z);
	vOut->w = v0->w + t * (v1->w - v0->w);

	return vOut;
}

