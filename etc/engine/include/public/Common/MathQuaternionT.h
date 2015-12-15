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

#ifndef _Quat_T
#define _Quat_T

#include "math.h"
#include "MathQuaternion.h"
#include "MathVector.h"
#include "MathMatrix.h"

#define _DX_COMPATIBLE

//#ifdef _DX_COMPATIBLE

class CQuatTS;

class CQuatT
{
public:
	CQuat q;
	CVec3 t;

	FORCEINLINE	CQuatT() {};
	FORCEINLINE CQuatT(const CQuat& _q, const CVec3& _t) : q(_q), t(_t) { };
	FORCEINLINE CQuatT(const CQuatTS& _q);// : q(_q.q), t(_q.t) { };
	FORCEINLINE CQuatT(CIdentity* ) { q.SetIdentity(); t = CVec3(CIdentity::GetIdentity()); }

	FORCEINLINE explicit CQuatT(const CMatrix44& m)
	{
		q.SetFromMatrix(m);
		t = m.GetTranslation();
	}

	FORCEINLINE void SetIdentity()
	{
		q.SetIdentity(); t = CVec3(CIdentity::GetIdentity());
	}

	CMatrix44 GetMatrix() const 
	{
		CMatrix44 mat(q);
		mat.SetTranslation(t);
		return mat;
	}
	FORCEINLINE CQuatT GetInverted() const 
	{
		CQuatT qpos;
		qpos.q=q.GetConjugated(); 	qpos.t=-t*q;
		return qpos;
	}

  FORCEINLINE bool operator == ( const CQuatT& v) const
  {
    return q == v.q && t == v.t;
  }

};

 FORCEINLINE CQuatT operator * ( const CQuatT &p, const CQuat &q) 
 {
	return CQuatT(q*p.q,p.t);
}

 FORCEINLINE CQuatT operator * ( const CQuatT &q, const CQuatT &p) 
 {
	 return CQuatT( p.q*q.q, q.q*p.t+q.t );
 }

 FORCEINLINE CVec3 operator * (const CQuatT &q, const CVec3 &v) 
 {
	 //assert((fabs_tpl(1-(q.q|q.q)))<0.01); //check if unit-quaternion
	 //muls=15 / adds=15+3
	 CVec3 out,r2;
	 r2.x=(q.q.y*v.z-q.q.z*v.y)+q.q.w*v.x;
	 r2.y=(q.q.z*v.x-q.q.x*v.z)+q.q.w*v.y;
	 r2.z=(q.q.x*v.y-q.q.y*v.x)+q.q.w*v.z;
	 out.x =(r2.z*q.q.y-r2.y*q.q.z); out.x+=out.x+v.x+q.t.x;
	 out.y =(r2.x*q.q.z-r2.z*q.q.x); out.y+=out.y+v.y+q.t.y;
	 out.z =(r2.y*q.q.x-r2.x*q.q.y); out.z+=out.z+v.z+q.t.z;
	 return out;
 }

 class CQuatTS
 {
 public:
	 CQuat q;
	 CVec3 t;
	 float s;

	 FORCEINLINE CQuatTS() {};
	 FORCEINLINE explicit  CQuatTS(const CQuatT& _q) : q(_q.q), t(_q.t), s(1.0f)  {};
	 FORCEINLINE explicit  CQuatTS(const CQuatT& _q, float _s) : q(_q.q), t(_q.t), s(_s)  {};

	 FORCEINLINE CQuatTS(const CQuat& _q, const CVec3& _t) : q(_q), t(_t), s(1.0f) { };
	 FORCEINLINE CQuatTS(const CQuat& _q, const CVec3& _t, const float _s) : q(_q), t(_t), s(_s) { };
	 FORCEINLINE CQuatTS(CIdentity* ) { q.SetIdentity(); t = CVec3(CIdentity::GetIdentity()); s = 1.0f;}

	 FORCEINLINE explicit CQuatTS(const CMatrix44& m)
	 {
		 s = m.GetUniformScale(0);
		 q.SetFromMatrix(m);
		 q.Normalize();
		 t = m.GetTranslation();
	 }

	 FORCEINLINE void SetIdentity()
	 {
		 q.SetIdentity(); t = CVec3(CIdentity::GetIdentity()); s = 1.0f;
	 }

	 CMatrix44 GetMatrix()
	 {
		 CMatrix44 mat(q);
		 mat.SetTranslation(t);
		 mat.SetUniformScale(s);
		 return mat;
	 }

	 FORCEINLINE CQuatTS GetInverted() const 
	 {
		 CQuatTS qpos;
		 qpos.s = 1/s;
		 qpos.q=q.GetConjugated(); 	qpos.t=-t*q*qpos.s;

		 return qpos;
	 }

   FORCEINLINE bool operator == ( const CQuatTS& v) const
   {
     return q == v.q && t == v.t && s == v.s;
   }


 };

 FORCEINLINE CQuatTS operator * ( const CQuatTS &p, const CQuat &q) 
 {
	 return CQuatTS(q*p.q,p.t);
 }

 FORCEINLINE CQuatTS operator * ( const CQuatTS &q, const CQuatT &p) 
 {
	 return CQuatTS( p.q*q.q, q.q*p.t+q.t, q.s);
 }

 FORCEINLINE CQuatTS operator * ( const CQuatTS &q, const CQuatTS &p) 
 {
	 return CQuatTS( p.q*q.q, q.q*p.t*p.s+q.t,  p.s*q.s);
 }

 FORCEINLINE CVec3 operator * (const CQuatTS &q, const CVec3 &v) 
 {
	 return q.q * v * q.s + q.t;
 }

 FORCEINLINE CQuatT::CQuatT(const CQuatTS& _q) : q(_q.q), t(_q.t) { };
#endif // _Quat_T
