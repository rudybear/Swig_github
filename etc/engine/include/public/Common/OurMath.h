// Common constants and functions

#ifndef OUR_MATH_H
#define OUR_MATH_H

#pragma once

#include "OurTypes.h"
#include <math.h>

#define pgEPS 0.0000001f
#define pgEPSL 0.5f
#define pgFTWOPI 6.28318531f

#define M_GOLDSECT 0.381966f

#ifndef M_PI
const f32 M_PI  =  3.14159265358979323846264338327950288419716939937510f; // pi
#endif

const f32 M_PI2 =  3.14159265358979323846264338327950288419716939937510f*2; // 2*pi

const f64 sqrt2	= (f64)1.4142135623730950488016887242097;
const f64 sqrt3	= (f64)1.7320508075688772935274463415059;

const f32 PI180 = 0.01745329252f;

#define DegreeToRadian( degree ) ((degree) * (M_PI / 180.0f))
#define RadianToDegree( radian ) ((radian) * (180.0f / M_PI))

#ifndef MAX
#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#define	VEC_EPSILON	( 0.01f )
#ifndef DEG2RAD
#define DEG2RAD( a ) ( (a) * (M_PI/180.0f) )
#endif
#ifndef RAD2DEG
#define RAD2DEG( a ) ( (a) * (180.0f/M_PI) )
#endif

// 32/64 Bit versions.
#define SIGN_MASK(x) ((intptr_t)(x) >> ((sizeof(size_t)*8)-1))

#define DW_AS_FLT(DW) (*(FLOAT*)&(DW))
#define FLT_AS_DW(F) (*(DWORD*)&(F))
#define FLT_SIGN(F) ((FLT_AS_DW(F) & 0x80000000L))
#define ALMOST_ZERO(F) ((FLT_AS_DW(F) & 0x7f800000L)==0)
#define IS_SPECIAL(F)  ((FLT_AS_DW(F) & 0x7f800000L)==0x7f800000L)
#define FLOAT_EQUALITY_FUDGE 0.001f


#ifndef FLT_MAX
#define FLT_MAX 3.402823466e+38F
#endif

#ifndef FLT_MIN
#define FLT_MIN 1.175494351e-38F
#endif


FORCEINLINE bool feq(const float a, const float b)
{ 
    return fabsf(a-b) < FLOAT_EQUALITY_FUDGE; 
}

// special class for Iden
class CIdentity
{
public:
	static CIdentity* GetIdentity()
	{
		static CIdentity m_Identity;
		return &m_Identity;
	}

};


#endif
