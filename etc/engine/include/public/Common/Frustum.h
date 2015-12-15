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


#include "Mathlib.h"

class CSphere;
class CAABBox;
struct CVec3;
struct CMatrix44;
struct CPlane;

class CFrustum
{
public:

  CFrustum(void);
  CFrustum( const CMatrix44& matrix );
  CFrustum(int planes);


  ~CFrustum(void);

  void SetFromPoints(const Engine2::Vector<CVec3>& srcPoints, const CVec3& eye)
  {
    size_t num = srcPoints.size();
    camPlanes.resize(num);
    for (size_t i = 0 ; i < num; ++i)
    {
      CVec3 v1(srcPoints[(i + 1) % num]);
      CVec3 v2(srcPoints[i]);

      camPlanes[i] = CPlane(eye, v1, v2);
    }
  }



  size_t GetPlanesCount() const { return camPlanes.size(); }
  const  CPlane* GetPlanes() const { return &camPlanes[0]; }
  void SetPlane(size_t num, CPlane& plane);
  void UpdatePlanes();

  bool TestSphere     ( const CSphere& sphere ) const;
  int  TestBox        ( const CAABBox& box ) const;
  bool TestSweptSphere( const CSphere& sphere, const CVec3& sweepDir ) const;

protected:

  //int m_iPlanes;
  //int m_iPoints;

  Engine2::Vector<CPlane> camPlanes;
  Engine2::Vector<int> nVertexLUT;
  Engine2::Vector<CVec3> pntList;

};

FORCEINLINE CFrustum::CFrustum(void)
{
	int m_iPlanes = 6;
	int m_iPoints = 8;
	camPlanes.resize(m_iPlanes);
	nVertexLUT.resize(m_iPlanes);
	pntList.resize(m_iPoints);
}

FORCEINLINE CFrustum::~CFrustum(void)
{
}

FORCEINLINE CFrustum::CFrustum(int planes)
{
	int m_iPlanes = planes;
	camPlanes.resize(m_iPlanes);
	nVertexLUT.resize(m_iPlanes);
}

FORCEINLINE void CFrustum::SetPlane(size_t num, CPlane& plane)
{
	if (num < camPlanes.size())
	{
		camPlanes[num] = plane;
		nVertexLUT[num] = ((camPlanes[num].GetNormal().x<0.f)?1:0) | ((camPlanes[num].GetNormal().y<0.f)?2:0) | ((camPlanes[num].GetNormal().z<0.f)?4:0);
	}
}

FORCEINLINE void CFrustum::UpdatePlanes()
{
	for (size_t i=0; i<camPlanes.size(); i++)
		nVertexLUT[i] = ((camPlanes[i].GetNormal().x<0.f)?1:0) | ((camPlanes[i].GetNormal().y<0.f)?2:0) | ((camPlanes[i].GetNormal().z<0.f)?4:0);

}



//  build a frustum from a camera (projection, or viewProjection) matrix
FORCEINLINE CFrustum::CFrustum(const CMatrix44& matrix)
{
	//  build a view frustum based on the current view & projection matrices...
	CVec4 column4( matrix._14, matrix._24, matrix._34, matrix._44 );
	CVec4 column1( matrix._11, matrix._21, matrix._31, matrix._41 );
	CVec4 column2( matrix._12, matrix._22, matrix._32, matrix._42 );
	CVec4 column3( matrix._13, matrix._23, matrix._33, matrix._43 );

	int m_iPlanes = 6;
	int m_iPoints = 8;
	camPlanes.resize(m_iPlanes);
	nVertexLUT.resize(m_iPlanes);
	pntList.resize(m_iPoints);

	CVec4 planes[6];
	planes[0] = column4 - column1;  // left
	planes[1] = column4 + column1;  // right
	planes[2] = column4 - column2;  // bottom
	planes[3] = column4 + column2;  // top
	planes[4] = column4 - column3;  // near
	planes[5] = column4 + column3;  // far
	// ignore near & far plane

	int p;

	for (p=0; p<6; p++)  // normalize the planes
	{
		float dot = planes[p].x*planes[p].x + planes[p].y*planes[p].y + planes[p].z*planes[p].z;
		dot = 1.f / sqrtf(dot);
		planes[p] = planes[p] * dot;
	}

	for (p=0; p<6; p++)
		camPlanes[p] = CPlane( planes[p].x, planes[p].y, planes[p].z, planes[p].w );

	//  build a bit-field that will tell us the indices for the nearest and farthest vertices from each plane...
	for (int i=0; i<6; i++)
		nVertexLUT[i] = ((planes[i].x<0.f)?1:0) | ((planes[i].y<0.f)?2:0) | ((planes[i].z<0.f)?4:0);

	for (int i=0; i<8; i++)  // compute extrema
	{
		const CPlane& p0 = (i&1)?camPlanes[4] : camPlanes[5];
		const CPlane& p1 = (i&2)?camPlanes[3] : camPlanes[2];
		const CPlane& p2 = (i&4)?camPlanes[0] : camPlanes[1];

		PlaneIntersection( &pntList[i], &p0, &p1, &p2 );
	}
}

//  test if a sphere is within the view frustum
FORCEINLINE bool CFrustum::TestSphere(const CSphere& sphere) const
{
	bool inside = true;
	float radius = sphere.fRadius;

	for (size_t i=0; (i<camPlanes.size()) && inside; i++)
		inside &= ((camPlanes[i].DotCoord(sphere.vecOrigin) + radius) >= 0.f);

	return inside;
}

//  Tests if an AABB is inside/intersecting the view frustum
FORCEINLINE int CFrustum::TestBox( const CAABBox& box ) const
{
	bool intersect = false;

	for (size_t i=0; i<camPlanes.size(); i++)
	{
		int nV = nVertexLUT[i];
		// pVertex is diagonally opposed to nVertex
		CVec3 nVertex( (nV&1)?box.getMid().x:box.getMax().x, (nV&2)?box.getMid().y:box.getMax().y, (nV&4)?box.getMid().z:box.getMax().z );
		CVec3 pVertex( (nV&1)?box.getMax().x:box.getMid().x, (nV&2)?box.getMax().y:box.getMid().y, (nV&4)?box.getMax().z:box.getMid().z );

		if ( camPlanes[i].DotCoord(nVertex) < 0.f )
			return 0;
		if ( camPlanes[i].DotCoord(pVertex) < 0.f )
			intersect = true;
	}

	return (intersect)?2 : 1;
}

//  this function tests if the projection of a bounding sphere along the light direction intersects
//  the view frustum 

FORCEINLINE bool SweptSpherePlaneIntersect(float& t0, float& t1, const CPlane& plane, const CSphere& sphere, const CVec3& Dir)
{
	float b_dot_n = plane.DotCoord(sphere.vecOrigin);
	float d_dot_n = plane.DotNormal(Dir);

	if (fabsf(d_dot_n) < FLOAT_EQUALITY_FUDGE)
	{
		if (b_dot_n <= sphere.fRadius)
		{
			//  effectively infinity
			t0 = 0.f;
			t1 = 1e32f;
			return true;
		}
		else
			return false;
	}
	else
	{
		float tmp0 = ( sphere.fRadius - b_dot_n) / d_dot_n;
		float tmp1 = (-sphere.fRadius - b_dot_n) / d_dot_n;
		t0 = MIN(tmp0, tmp1);
		t1 = MAX(tmp0, tmp1);
		return true;
	}
}

FORCEINLINE bool CFrustum::TestSweptSphere(const CSphere& sphere, const CVec3& sweepDir) const
{
	//  algorithm -- get all 12 intersection points of the swept sphere with the view frustum
	//  for all points >0, displace sphere along the sweep driection.  if the displaced sphere
	//  is inside the frustum, return TRUE.  else, return FALSE
	float displacements[12];
	int cnt = 0;
	float a, b;
	bool inFrustum = false;

	for (size_t i=0; i<camPlanes.size(); i++)
	{
		if (SweptSpherePlaneIntersect(a, b, camPlanes[i], sphere, sweepDir))
		{
			if (a>=0.f)
				displacements[cnt++] = a;
			if (b>=0.f)
				displacements[cnt++] = b;
		}
	}

	for (int i=0; i<cnt; i++)
	{
		CSphere displacedSphere(sphere);
		displacedSphere.vecOrigin += (sweepDir)*displacements[i];
		displacedSphere.fRadius *= 1.1f;
		inFrustum |= TestSphere(displacedSphere);
	}
	return inFrustum;
}
