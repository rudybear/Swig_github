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

#include "Shapes.h"
#include "Mathlib.h"

class CTriangle;
class CSphere;
struct CVec3;
struct CQuaternion;
struct CMatrix44;

class CAABBox
{
public:
	// constructors
	CAABBox() {};
	CAABBox(int){reset();};
	CAABBox(const CVec3& nMin, const CVec3& nMax) : minVertex(nMin), maxVertex(nMax)  {};
	CAABBox(const CVec3& nMid, float dx, float dy, float dz) : minVertex(nMid[0]-dx/2.0f, nMid[1]-dy/2.0f, nMid[2]-dz/2.0f),
		maxVertex(nMid[0]+dx/2.0f, nMid[1]+dy/2.0f, nMid[2]+dz/2.0f) {};

	inline void setMin(const CVec3& nVertex) {minVertex = nVertex;}; // Sets one corner of the bounding box
	inline void setMax(const CVec3& nVertex) {maxVertex = nVertex;}; // Sets another corner of the bounding box
	inline void setMid(const CVec3& nMid, float d) { setMid(nMid, d,d,d); }; // Resets the box to be centered at nMid and to have each side of length d
	inline void setMid(const CVec3& nMid, float dx, float dy, float dz) { minVertex = CVec3(nMid[0]-dx/2.0f, nMid[1]-dy/2.0f, nMid[2]-dz/2.0f);	maxVertex = CVec3(nMid[0]+dx/2.0f, nMid[1]+dy/2.0f, nMid[2]+dz/2.0f);}; // Resets the box to be centered at nMid and to have size dx,dy,dz
	inline void SetTranslation(const CVec3& v) {
		CVec3 ext = getExtents();
		minVertex = v - ext;
		maxVertex = v + ext;
	}

	const CVec3& getMin() const { return minVertex; }; // returns one point of the box
	const CVec3& getMax() const  {  return maxVertex;  }; // returns the other point of the box

	inline CVec3 getMid() const {return (maxVertex+minVertex)/2.0f;}; // Calculates and returns the center of the box
	inline void move(const CVec3& nMove) {minVertex += nMove;  maxVertex += nMove;}; // Moves the box by nMove
	inline void reset() { maxVertex = CVec3(-100000.f,-100000.f,-100000.f); minVertex = CVec3(100000.f,100000.f,100000.f);}; // Resets the box to contain everything

	inline CVec3 getExtents() const {return (maxVertex - minVertex)/2.0f;};

	void addVertex(const CVec3& nVertex)
	{
		// is there a new max
		if (maxVertex.x <= -100000.f)
			maxVertex = nVertex;
		else
		{
			if (nVertex.x > maxVertex.x)
				maxVertex.x = nVertex.x;
			if (nVertex.y > maxVertex.y)
				maxVertex.y = nVertex.y;
			if (nVertex.z > maxVertex.z)
				maxVertex.z = nVertex.z;
		}

		// is there a new min
		if (minVertex.x >= 100000.f)
			minVertex = nVertex;
		else
		{
			if (nVertex.x < minVertex.x)
				minVertex.x = nVertex.x;
			if (nVertex.y < minVertex.y)
				minVertex.y = nVertex.y;
			if (nVertex.z < minVertex.z)
				minVertex.z = nVertex.z;
		}
	};

	void addBox(const CAABBox& nOther)
	{
		addVertex(nOther.maxVertex);
		addVertex(nOther.minVertex);
	};

	void addTriangle(const CTriangle& nTriangle)
	{
		addVertex(nTriangle.t0);
		addVertex(nTriangle.t1);
		addVertex(nTriangle.t2);
	};

	bool doesOverlap(const CAABBox& nOther) const
	{
		return !(minVertex.x>=nOther.maxVertex.x || nOther.minVertex.x>=maxVertex.x ||
			minVertex.y>=nOther.maxVertex.y || nOther.minVertex.y>=maxVertex.y ||
			minVertex.z>=nOther.maxVertex.z || nOther.minVertex.z>=maxVertex.z);
	};

	bool isPointInside(const CVec3& nVertex) const
	{
		return (nVertex.x < maxVertex.x && nVertex.x > minVertex.x &&
			nVertex.y < maxVertex.y && nVertex.y > minVertex.y &&
			nVertex.z < maxVertex.z && nVertex.z > minVertex.z);
	};

	void extendByRotation(const CQuaternion& qRot)
	{
		CVec3 corners[8];
		CVec3 center = (minVertex + maxVertex)/2;
		corners[0] = CVec3(minVertex.x, minVertex.y, minVertex.z) - center;
		corners[1] = CVec3(maxVertex.x, minVertex.y, minVertex.z) - center;
		corners[2] = CVec3(minVertex.x, maxVertex.y, minVertex.z) - center;
		corners[3] = CVec3(maxVertex.x, maxVertex.y, minVertex.z) - center;
		corners[4] = CVec3(minVertex.x, minVertex.y, maxVertex.z) - center;
		corners[5] = CVec3(maxVertex.x, minVertex.y, maxVertex.z) - center;
		corners[6] = CVec3(minVertex.x, maxVertex.y, maxVertex.z) - center;
		corners[7] = CVec3(maxVertex.x, maxVertex.y, maxVertex.z) - center;
    minVertex = CVec3(FLT_MAX, FLT_MAX, FLT_MAX);
    maxVertex = -minVertex;

    //center = center + center*qRot;
		for (int i = 0; i < 8; i++)
		{
			corners[i] = qRot * corners[i] * qRot.GetConjugated();// + center;
      addVertex(corners[i]);
		}

    move(center);
	};

  void extendByRotationAbsolute(const CMatrix44& qRot)
  {
    CVec3 corners[8];
    //CVec3 center = (minVertex + maxVertex) * 0.5f;
    corners[0] = CVec3(minVertex.x, minVertex.y, minVertex.z);// - center;
    corners[1] = CVec3(maxVertex.x, minVertex.y, minVertex.z);// - center;
    corners[2] = CVec3(minVertex.x, maxVertex.y, minVertex.z);// - center;
    corners[3] = CVec3(maxVertex.x, maxVertex.y, minVertex.z);// - center;
    corners[4] = CVec3(minVertex.x, minVertex.y, maxVertex.z);// - center;
    corners[5] = CVec3(maxVertex.x, minVertex.y, maxVertex.z);// - center;
    corners[6] = CVec3(minVertex.x, maxVertex.y, maxVertex.z);// - center;
    corners[7] = CVec3(maxVertex.x, maxVertex.y, maxVertex.z);// - center;
    minVertex = CVec3(FLT_MAX, FLT_MAX, FLT_MAX);
    maxVertex = -minVertex;

    for (int i = 0; i < 8; i++)
    {
      corners[i] = corners[i].TransformNormal(qRot);// + center;
      addVertex(corners[i]);
    }
    //move(center);
  };

   bool doesOverlap( const CAABBox &aabb1) {
    if  (aabb1.minVertex.x>=maxVertex.x) return false;
    if  (aabb1.minVertex.y>=maxVertex.y) return false; 
    if 	(aabb1.minVertex.z>=maxVertex.z) return false; 
    if  (aabb1.maxVertex.x<=minVertex.x) return false;
    if  (aabb1.maxVertex.y<=minVertex.y) return false;
    if  (aabb1.maxVertex.z<=minVertex.z) return false; 
    return true; //the aabb's overlap
  }

	bool doesOverlap(const CSphere& nOtherSphere) const
	{ 
		float d = 0.0f;

		CVec3 center = getMid();
		CVec3 extents = getExtents();

		float mRadius2 = nOtherSphere.fRadius*nOtherSphere.fRadius;

		float tmp,s;

		tmp = nOtherSphere.vecOrigin.x - center.x;
		s = tmp + extents.x;

		if(s < 0.0f)
		{
			d += s*s;
			if(d > mRadius2)	return false;
		}
		else
		{
			s = tmp - extents.x;
			if(s > 0.0f)
			{
				d += s*s;
				if(d > mRadius2)	return false;
			}
		}

		tmp = nOtherSphere.vecOrigin.y - center.y;
		s = tmp + extents.y;

		if(s<0.0f)
		{
			d += s*s;
			if(d>mRadius2)	return false;
		}
		else
		{
			s = tmp - extents.y;
			if(s>0.0f)
			{
				d += s*s;
				if(d>mRadius2)	return false;
			}
		}

		tmp = nOtherSphere.vecOrigin.z - center.z;
		s = tmp + extents.z;

		if(s<0.0f)
		{
			d += s*s;
			if(d>mRadius2)	return false;
		}
		else
		{
			s = tmp - extents.z;
			if(s>0.0f)
			{
				d += s*s;
				if(d>mRadius2)	return false;
			}
		}
		return d <= mRadius2;
	} ;

	bool DoesIntersectSegment(const CVec3 &vecStart,const CVec3 &vecEnd)
	{
		if(isPointInside(vecStart) || isPointInside(vecEnd))
		{
			return true;
		}
		if( (vecStart.x > maxVertex.x && vecEnd.x> maxVertex.x)
			|| (vecStart.x < minVertex.x && vecEnd.x < minVertex.x))
		{
			if( (vecStart.y > maxVertex.y && vecEnd.y> maxVertex.y)
				|| (vecStart.y < minVertex.y && vecEnd.y < minVertex.y))
			{
				if( (vecStart.z > maxVertex.z && vecEnd.z> maxVertex.z)
					|| (vecStart.z < minVertex.z && vecEnd.z < minVertex.z))
				{
					return false;
				}
			}
		}

		CPlane Plane[6] = {
			CPlane(minVertex,CVec3(-1,0,0)),
			CPlane(minVertex,CVec3(0,-1,0)),
			CPlane(minVertex,CVec3(0,0,-1)),

			CPlane(maxVertex,CVec3( 1,0,0)),
			CPlane(maxVertex,CVec3(0, 1,0)),
			CPlane(maxVertex,CVec3(0,0, 1))
		};

		CVec3 tmpOut(0,0,0);
		for(size_t i=0;i<6;i++)
			if(Plane[i].IntersectLine(vecStart, vecEnd, &tmpOut) && isPointNear(tmpOut,0.1f))
				return true;

		return false;
	};

	bool isPointNear(const CVec3& nVertex, float fMaxDistance) const
	{
		return(nVertex.x < maxVertex.x + fMaxDistance && nVertex.x > minVertex.x - fMaxDistance &&
			nVertex.y < maxVertex.y + fMaxDistance && nVertex.y > minVertex.y - fMaxDistance &&
			nVertex.z < maxVertex.z + fMaxDistance && nVertex.z > minVertex.z - fMaxDistance );

	};

	float GetVolume(void) const
	{

		return (maxVertex.x - minVertex.x)*(maxVertex.y - minVertex.y)*(maxVertex.z - minVertex.z);
	}

	float GetRadius() const
	{
		return CVec3(maxVertex - minVertex).Length() * 0.5f;
	}

//protected:
	CVec3 minVertex, maxVertex;

};



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// struct OBB
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class COBB {

public:

  CQuat m_qRot; 
  CVec3 m_vHalf;		
  CVec3 m_vCenter;	

  inline COBB() {}
  COBB(const CQuat& q, const CVec3& hlv, const CVec3& center  ) {  m_qRot=q; m_vHalf=hlv; m_vCenter=center;	}
  ~COBB( void ) {};

  inline void SetOBB( const CQuat& q, const CVec3& hlv, const CVec3& center  ) {  m_qRot=q; m_vHalf=hlv; m_vCenter=center;	}

  inline void SetOBBfromAABB( const CQuat& q, const CAABBox& aabb ) {
    m_qRot	=	q;
    m_vHalf		=	aabb.getExtents();
    m_vCenter		=	aabb.getMid();
  }
  inline void SetOBBfromAABB( const CMatrix44& mat, const CAABBox& aabb ) {
    m_qRot	=	CQuat(mat);
    m_vHalf		=	aabb.getExtents();
    m_vCenter		=	aabb.getMid();
  }
 
};
