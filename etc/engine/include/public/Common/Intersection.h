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

#include "Common.h"

//intersection
DLLIMPORT bool findIntersectionPlanes(const CPlane& nPlane1, const CPlane& nPlane2, const CPlane& nPlane3, CVec3& nPoint);
DLLIMPORT bool findIntersectionRayPlane(const CPlane& nPlane, const CVec3& nPos0, const CVec3& nDir, CVec3& nPos, float& nT);

//for both moving spheres
DLLIMPORT bool findIntersectionSphereSphere(const CSphere& nSphere1, const CVec3& nVelocity1, const CSphere& nSphere2, const CVec3& nVelocity2, const float fTime, CVec3& nFirstPoint, float& fFirstTime); 

DLLIMPORT bool testIntersectionRayTriangle(const CSegment& nRay, const CTriangle& nTriangle, CVec3& pIntersect);


DLLIMPORT bool testIntersectionRayAABBox(const CVec3& pRayOrigin, const CVec3& pRayDirection, const CVec3& pMinBox, const CVec3& pMaxBox);
DLLIMPORT bool testIntersectionRayAABBox(const CSegment& nRay, const CAABBox& nBox);

//moved sphere and static triangle
DLLIMPORT bool findIntersectionSphereTriangle(const CSphere& nSphere, const CVec3& nSphereVelocity, const CTriangle& nTriangle, const bool bCheckBackface, CVec3& nPoint, float& fDistance); 

//static sphere and static triangle
DLLIMPORT bool testIntersectionSphereTriangle(const CSphere& nSphere, const CTriangle& nTriangle);

//static ellipsoid
DLLIMPORT bool findIntersectionSegmentEllipsoid(const CSegment& nSegment, const CEllipsoid& nEllipsoid, int& nPoints, CVec3 akPoint[2]);

//static ellipsoid
DLLIMPORT bool findIntersectionSphereEllipsoid(const CSphere& nSphere, const CVec3& nSphereVelocity, const CEllipsoid& nEllipsoid, int& nPoints, CVec3 akPoint[2]);

DLLIMPORT bool findIntersectionSphereCylinder(const CSphere& nSphere, const CCylinder& nCylinder, CVec3 * pIntersect = NULL, CVec3 * pNormal = NULL);

DLLIMPORT bool findIntersectionTriangleCylinder(const CTriangle& nTriangle, const CCylinder& nCylinder, CVec3 * pIntersect = NULL, CVec3 * pNormal = NULL);

//static sphere and plane
DLLIMPORT bool testIntersectionSpherePlane(const CSphere& nSphere, const CVec3& nVecPlane, const CVec3& nVecNormal);
DLLIMPORT bool testIntersectionSpherePlane(const CSphere& nSphere, const CPlane& nPlane);

//static plane and moving sphere
DLLIMPORT bool testIntersectionSpherePlane(const CSphere& nSphere, const CVec3& nSphereVelocity, const CPlane& nPlane, float& fTime);

//moving sphere and plane
DLLIMPORT bool findIntersectionSpherePlane(const CSphere& nSphere, const CVec3& nSphereVelocity, const CVec3& nVecPlane1, const CVec3& nVecNormal1, const CVec3& nVecPlane2, const CVec3& nVecNormal2, float& fTime);

// triangles
DLLIMPORT bool testIntersectionTriangleTriangle(const CTriangle& nTriangle1, const CTriangle& nTriangle2);
DLLIMPORT bool findIntersectionTriangleTriangle(const CTriangle& nTriangle1, const CTriangle& nTriangle2, CVec3& vecIntersection);

//2d intersection
DLLIMPORT bool testIntersectionRectangleCircle(const CVec2& nBoxMin, const CVec2& nBoxMax, const CVec2& nCenter, const float& fRadius);

//! find intersection between 3 planes 
DLLIMPORT bool PlaneIntersection( CVec3* intersectPt, const CPlane* p0, const CPlane* p1, const CPlane* p2 );


namespace Engine2
{


  namespace Math
  {
    FORCEINLINE float ScalarTriple(CVec3& a, CVec3& b, CVec3 &c)
    {
      return a.Cross(b).Dot(c);
    }
  }


  namespace Intersection
  {

    FORCEINLINE bool IntersectTri 
      (
      const CVec3& p0,           // Triangle vertex 0 position
      const CVec3& p1,           // Triangle vertex 1 position
      const CVec3& p2,           // Triangle vertex 2 position
      const CVec3& rayPos,      // Ray origin
      const CVec3& rayDir,      // Ray direction
      float *pU,                       // Barycentric Hit Coordinates
      float *pV,                       // Barycentric Hit Coordinates
      float *pDist)                   // Ray-Intersection Parameter Distance
    {
      CVec3 e1 = p1 - p0;
      CVec3 e2 = p2 - p0;

      CVec3 p = rayDir.Cross(e2);

      float a = e1.Dot(p);
      const float epsilon = 0.000001f;

      if (a > -epsilon && a < epsilon)
        return false;

      CVec3 s = rayPos - p0;
      float u = s.Dot(p)/a;
      if (u < 0.0f || u > 1.0f)
        return false;

      CVec3 q = s.Cross(e1);
      float v = rayDir.Dot(q)/a;

      if (u < 0.0f || (u + v) > 1.0f)
        return false;

      *pU = u;
      *pV = v;
      *pDist = e2.Dot(q)/a;

      return true;
    }

    FORCEINLINE bool IntersectSegmentTriangle(const CVec3& p, const CVec3& q, const CVec3& a, const CVec3& b, const CVec3& c, CVec3& intersect)
    {
      CVec3 pq = q - p;
      CVec3 pa = a - p;
      CVec3 pb = b - p;
      CVec3 pc = c - p;
      // Test if pq is inside the edges bc, ca and ab. Done by testing
      // that the signed tetrahedral volumes, computed using scalar triple
      // products, are all positive
      float u = Math::ScalarTriple(pq, pc, pb);
      if (u < 0.0f) return false;
      float v = Math::ScalarTriple(pq, pa, pc);
      if (v < 0.0f) return false;
      float w = Math::ScalarTriple(pq, pb, pa);
      if (w < 0.0f) return false;

      // Compute the barycentric coordinates (u, v, w) determining the
      // intersection point r, r = u*a + v*b + w*c
      float denom = 1.0f / (u + v + w);
      u *= denom;
      v *= denom;
      w *= denom; // w = 1.0f - u - v;
      intersect = u*a + v*b + w*c;
      return true;

    }

    FORCEINLINE bool IntersectSegmentTrianle(const CSegment& seg, const CTriangle& tri, CVec3 & intersection)
    {
      return IntersectSegmentTriangle(seg.vecOrigin, seg.vecDestination, tri.t0, tri.t1, tri.t2, intersection);
    }

    inline int incm3(int i) {return i + 1& (i-2) >> 31; }
    inline int decm3(int i) {return i - 1 + ((i-1) >> 31 & 3);}

    inline uint8 IntersectRayAABB( const CSegment& ray,const CAABBox& aabb, CVec3& output1 ) {

      uint8 cflags;
      float cosine;
      CVec3 cut;
      //--------------------------------------------------------------------------------------
      //----         check if "ray.origin" is inside of AABB    ---------------------------
      //--------------------------------------------------------------------------------------
      cflags =(ray.vecOrigin.x>=aabb.getMin().x)<<0;
      cflags|=(ray.vecOrigin.x<=aabb.getMax().x)<<1;
      cflags|=(ray.vecOrigin.y>=aabb.getMin().y)<<2;
      cflags|=(ray.vecOrigin.y<=aabb.getMax().y)<<3;
      cflags|=(ray.vecOrigin.z>=aabb.getMin().z)<<4;
      cflags|=(ray.vecOrigin.z<=aabb.getMax().z)<<5;
      if (cflags==0x3f)	{	output1=ray.vecOrigin;	return 0x02; }

      //--------------------------------------------------------------------------------------
      //----         check intersection with planes           ------------------------------
      //--------------------------------------------------------------------------------------
      for(int i=0; i<3; i++) {
        if ( (ray.vecDestination[i]>0) && (ray.vecOrigin[i]<aabb.getMin()[i]) )	{
          cosine = (-ray.vecOrigin[i]+aabb.getMin()[i])/ray.vecDestination[i];
          cut[i]=aabb.getMin()[i]; 
          cut[incm3(i)]=ray.vecOrigin[incm3(i)]+(ray.vecDestination[incm3(i)]*cosine); 
          cut[decm3(i)]=ray.vecOrigin[decm3(i)]+(ray.vecDestination[decm3(i)]*cosine);
          if ((cut[incm3(i)]>aabb.getMin()[incm3(i)]) && (cut[incm3(i)]<aabb.getMax()[incm3(i)]) && (cut[decm3(i)]>aabb.getMin()[decm3(i)]) && (cut[decm3(i)]<aabb.getMax()[decm3(i)])) {
            output1=cut;	return 0x01;
          }
        }
        if ( (ray.vecDestination[i]<0) && (ray.vecOrigin[i]>aabb.getMax()[i]) )	{
          cosine = (+ray.vecOrigin[i]-aabb.getMax()[i])/ray.vecDestination[i];
          cut[i]=aabb.getMax()[i]; 
          cut[incm3(i)]=ray.vecOrigin[incm3(i)]-(ray.vecDestination[incm3(i)]*cosine); 
          cut[decm3(i)]=ray.vecOrigin[decm3(i)]-(ray.vecDestination[decm3(i)]*cosine);
          if ((cut[incm3(i)]>aabb.getMin()[incm3(i)]) && (cut[incm3(i)]<aabb.getMax()[incm3(i)]) && (cut[decm3(i)]>aabb.getMin()[decm3(i)]) && (cut[decm3(i)]<aabb.getMax()[decm3(i)])) {
            output1=cut;	return 0x01;
          }
        }
      }
      return 0x00;//no intersection
    }
  }

  //----------------------------------------------------------------------------------
  //  Ray_OBB
  //
  //	just ONE intersection point is calculated, and thats the entry point           - 
  //   Lineseg and OBB are assumed to be in the same space
  //
  //--- 0x00 = no intersection (output undefined)                                 ----
  //--- 0x01 = intersection (intersection point in output)              --------------
  //--- 0x02 = start of Lineseg is inside the OBB (ls.start is output) 
  //----------------------------------------------------------------------------------
  //   inline uint8 RayOBB( const CSegment& ray,const CVec3& pos,const COBB& obb, CVec3& output1 ) {

  //     CAABBox aabb(obb.c-obb.h,obb.c+obb.h);
  //     CSegment aray((ray.origin-pos)*obb.m33, ray.direction*obb.m33);

  //     uint8 cflags;
  //     float cosine;
  //     CVec3 cut;
  //     //--------------------------------------------------------------------------------------
  //     //----         check if "aray.origin" is inside of AABB    ---------------------------
  //     //--------------------------------------------------------------------------------------
  //     cflags =(aray.origin.x>aabb.getMin().x)<<0;
  //     cflags|=(aray.origin.x<aabb.getMax().x)<<1;
  //     cflags|=(aray.origin.y>aabb.getMin().y)<<2;
  //     cflags|=(aray.origin.y<aabb.getMax().y)<<3;
  //     cflags|=(aray.origin.z>aabb.getMin().z)<<4;
  //     cflags|=(aray.origin.z<aabb.getMax().z)<<5;
  //     if (cflags==0x3f)	{	output1=aray.origin;	return 0x02; }

  //     //--------------------------------------------------------------------------------------
  //     //----         check intersection with planes           ------------------------------
  //     //--------------------------------------------------------------------------------------
  //     for(int i=0; i<3; i++) {
  //       if ( (aray.direction[i]>0) && (aray.origin[i]<aabb.min[i]) )	{
  //         cosine = (-aray.origin[i]+aabb.min[i])/aray.direction[i];
  //         cut[i]=aabb.min[i]; 
  //         cut[incm3(i)]=aray.origin[incm3(i)]+(aray.direction[incm3(i)]*cosine); 
  //         cut[decm3(i)]=aray.origin[decm3(i)]+(aray.direction[decm3(i)]*cosine);
  //         if ((cut[incm3(i)]>aabb.min[incm3(i)]) && (cut[incm3(i)]<aabb.max[incm3(i)]) && (cut[decm3(i)]>aabb.min[decm3(i)]) && (cut[decm3(i)]<aabb.max[decm3(i)])) {
  //           output1=obb.m33*cut+pos;	return 0x01;
  //         }
  //       }
  //       if ( (aray.direction[i]<0) && (aray.origin[i]>aabb.max[i]) )	{
  //         cosine = (+aray.origin[i]-aabb.max[i])/aray.direction[i];
  //         cut[i]=aabb.max[i]; 
  //         cut[incm3(i)]=aray.origin[incm3(i)]-(aray.direction[incm3(i)]*cosine); 
  //         cut[decm3(i)]=aray.origin[decm3(i)]-(aray.direction[decm3(i)]*cosine);
  //         if ((cut[incm3(i)]>aabb.min[incm3(i)]) && (cut[incm3(i)]<aabb.max[incm3(i)]) && (cut[decm3(i)]>aabb.min[decm3(i)]) && (cut[decm3(i)]<aabb.max[decm3(i)])) {
  //           output1=obb.m33*cut+pos;	return 0x01;
  //         }
  //       }
  //     }
  //     return 0x00;//no intersection
  //   }
  //   //----------------------------------------------------------------------------------
  //   //  Lineseg_OBB
  //   //
  //   //	just ONE intersection point is calculated, and thats the entry point           - 
  //   //  Lineseg and OBB are assumed to be in the same space
  //   //
  //   //--- 0x00 = no intersection (output undefined)           --------------------------
  //   //--- 0x01 = intersection (intersection point in output)              --------------
  //   //--- 0x02 = start of Lineseg is inside the OBB (ls.start is output) 
  //   //----------------------------------------------------------------------------------
  //   inline uint8	Lineseg_OBB( const Lineseg& lseg,const Vec3& pos,const OBB& obb, Vec3& output1 ) {

  //     AABB aabb(obb.c-obb.h,obb.c+obb.h);
  //     Lineseg ls((lseg.start-pos)*obb.m33,(lseg.end-pos)*obb.m33);

  //     uint8 cflags;
  //     float cosine;
  //     Vec3 cut;
  //     Vec3 lnormal=(ls.start-ls.end).GetNormalized();
  //     //--------------------------------------------------------------------------------------
  //     //----         check if "ls.start" is inside of AABB    ---------------------------
  //     //--------------------------------------------------------------------------------------
  //     cflags =(ls.start.x>aabb.getMin().x)<<0;
  //     cflags|=(ls.start.x<aabb.getMax().x)<<1;
  //     cflags|=(ls.start.y>aabb.getMin().y)<<2;
  //     cflags|=(ls.start.y<aabb.getMax().y)<<3;
  //     cflags|=(ls.start.z>aabb.getMin().z)<<4;
  //     cflags|=(ls.start.z<aabb.getMax().z)<<5;
  //     if (cflags==0x3f)	{ 
  //       //ls.start is inside of aabb
  //       output1=obb.m33*ls.start+pos;	return 0x02; 
  //     }

  //     //--------------------------------------------------------------------------------------
  //     //----         check intersection with x-planes           ------------------------------
  //     //--------------------------------------------------------------------------------------
  //     if (lnormal.x) {
  //       if ( (ls.start.x<aabb.getMin().x) && (ls.end.x>aabb.getMin().x) ) {
  //         cosine = (-ls.start.x+(+aabb.getMin().x))/lnormal.x;
  //         cut(aabb.getMin().x,ls.start.y+(lnormal.y*cosine),ls.start.z+(lnormal.z*cosine));
  //         //check if cut-point is inside YZ-plane border
  //         if ((cut.y>aabb.getMin().y) && (cut.y<aabb.getMax().y) && (cut.z>aabb.getMin().z) && (cut.z<aabb.getMax().z)) {
  //           output1=obb.m33*cut+pos;	return 0x01;
  //         }
  //       }
  //       if ( (ls.start.x>aabb.getMax().x) && (ls.end.x<aabb.getMax().x) ) {
  //         cosine = (+ls.start.x+(-aabb.getMax().x))/lnormal.x;
  //         cut(aabb.getMax().x,ls.start.y-(lnormal.y*cosine),ls.start.z-(lnormal.z*cosine));
  //         //check if cut-point is inside YZ-plane border
  //         if ((cut.y>aabb.getMin().y) && (cut.y<aabb.getMax().y) && (cut.z>aabb.getMin().z) && (cut.z<aabb.getMax().z)) {
  //           output1=obb.m33*cut+pos;	return 0x01;
  //         }
  //       }
  //     }
  //     //--------------------------------------------------------------------------------------
  //     //----         check intersection with z-planes           ------------------------------
  //     //--------------------------------------------------------------------------------------
  //     if (lnormal.z) {
  //       if ( (ls.start.z<aabb.getMin().z) && (ls.end.z>aabb.getMin().z) ) {
  //         cosine = (-ls.start.z+(+aabb.getMin().z))/lnormal.z;
  //         cut(ls.start.x+(lnormal.x*cosine),ls.start.y+(lnormal.y*cosine),aabb.getMin().z);
  //         //check if cut-point is inside XY-plane border
  //         if ((cut.x>aabb.getMin().x) && (cut.x<aabb.getMax().x) && (cut.y>aabb.getMin().y) && (cut.y<aabb.getMax().y)) {
  //           output1=obb.m33*cut+pos;	return 0x01;
  //         }
  //       }
  //       if ( (ls.start.z>aabb.getMax().z) && (ls.end.z<aabb.getMax().z) ) {
  //         cosine = (+ls.start.z+(-aabb.getMax().z))/lnormal.z;
  //         cut(ls.start.x-(lnormal.x*cosine),ls.start.y-(lnormal.y*cosine),aabb.getMax().z);
  //         //check if cut-point is inside XY-plane border
  //         if ((cut.x>aabb.getMin().x) && (cut.x<aabb.getMax().x) && (cut.y>aabb.getMin().y) && (cut.y<aabb.getMax().y)) {
  //           output1=obb.m33*cut+pos;	return 0x01;
  //         }
  //       }
  //     }
  //     //--------------------------------------------------------------------------------------
  //     //----         check intersection with y-planes           ------------------------------
  //     //--------------------------------------------------------------------------------------
  //     if (lnormal.y) {
  //       if ( (ls.start.y<aabb.getMin().y) && (ls.end.y>aabb.getMin().y) ) {
  //         cosine = (-ls.start.y+(+aabb.getMin().y))/lnormal.y;
  //         cut(ls.start.x+(lnormal.x*cosine), aabb.getMin().y, ls.start.z+(lnormal.z*cosine));
  //         //check if cut-point is inside XZ-plane border
  //         if ((cut.x>aabb.getMin().x) && (cut.x<aabb.getMax().x) && (cut.z>aabb.getMin().z) && (cut.z<aabb.getMax().z)) {
  //           output1=obb.m33*cut+pos;	return 0x01;
  //         }
  //       }
  //       if ( (ls.start.y>aabb.getMax().y) && (ls.end.y<aabb.getMax().y) ) {
  //         cosine = (+ls.start.y+(-aabb.getMax().y))/lnormal.y;
  //         cut(ls.start.x-(lnormal.x*cosine), aabb.getMax().y, ls.start.z-(lnormal.z*cosine));
  //         //check if cut-point is inside XZ-plane border
  //         if ((cut.x>aabb.getMin().x) && (cut.x<aabb.getMax().x) && (cut.z>aabb.getMin().z) && (cut.z<aabb.getMax().z)) {
  //           output1=obb.m33*cut+pos;	return 0x01;
  //         }
  //       }
  //     }
  //     //no intersection
  //     return 0x00;
  //   }


  namespace Overlapping {
    //   inline bool	Point_OBB(const Vec3& p, const Vec3& wpos, const OBB& obb) {
    //     AABB aabb=AABB(obb.c-obb.h,obb.c+obb.h);
    //     Vec3 t=(p-wpos)*obb.m33;
    //     return ((t.x>=aabb.getMin().x && t.x<=aabb.getMax().x) && (t.y>=aabb.getMin().y && t.y<=aabb.getMax().y) && (t.z>=aabb.getMin().z && t.z<=aabb.getMax().z));
    //   }

    //   /*!
    //   * we use the SEPARATING AXIS TEST to check if two OBB's overlap.
    //   *
    //   * Example:
    //   *  bool result=Overlap::Lineseg_OBB( lineseg, pos,obb );
    //   */
    //   inline bool Lineseg_OBB ( const Lineseg &ls, const Vec3 &pos, const OBB &obb ) {
    //     //the new center-position of Lineseg and OBB in world-space
    //     Vec3 wposobb	=	obb.m33*obb.c + pos;
    //     Vec3 wposls	=	(ls.start+ls.end)*0.5f;
    //     //"t" is the transfer-vector from one center to the other
    //     Vec3 t		= (wposls-wposobb)*obb.m33;
    //     //calculate line-direction in local obb-space
    //     Vec3 ld  =  ( (ls.end-ls.start)*obb.m33 )*0.5f;
    //     if( fabsf(t.x) > (obb.m_vHalf.x + fabsf(ld.x)) ) return 0;
    //     if( fabsf(t.y) > (obb.m_vHalf.y + fabsf(ld.y)) ) return 0;
    //     if( fabsf(t.z) > (obb.m_vHalf.z + fabsf(ld.z)) ) return 0;
    //     if( fabsf(t.z*ld.y-t.y*ld.z) > (fabsf(obb.m_vHalf.y*ld.z) + fabsf(obb.m_vHalf.z*ld.y)) ) return 0;
    //     if( fabsf(t.x*ld.z-t.z*ld.x) > (fabsf(obb.m_vHalf.x*ld.z) + fabsf(obb.m_vHalf.z*ld.x)) ) return 0;
    //     if( fabsf(t.y*ld.x-t.x*ld.y) > (fabsf(obb.m_vHalf.x*ld.y) + fabsf(obb.m_vHalf.y*ld.x)) ) return 0;
    //     return 1; //no separating axis found, objects overlap
    //   }

    //   //----------------------------------------------------------------------------------
    //   //  Sphere_OBB
    //   //	VERY IMPORTANT: Sphere is assumed to be in the space of the OBB, otherwise it won't work 
    //   //
    //   //--- 0 = no overlap                                     ---------------------------
    //   //--- 1 = overlap                                                  -----------------
    //   //----------------------------------------------------------------------------------
    //   inline bool Sphere_OBB( const Sphere &s, const OBB &obb ) {
    //     //first we transform the sphere-center into the AABB-space of the OBB
    //     Vec3 SphereInOBBSpace	=	s.center*obb.m33;
    //     //the rest ist the same as the "Overlap::Sphere_AABB" calculation
    //     float quatradius = s.radius * s.radius;
    //     Vec3 quat(0,0,0);
    //     AABB aabb=AABB(obb.c-obb.h,obb.c+obb.h);
    //     if(SphereInOBBSpace.x < aabb.getMin().x) { quat.x = SphereInOBBSpace.x - aabb.getMin().x;	} 
    //     else if(SphereInOBBSpace.x > aabb.getMax().x) {	quat.x = SphereInOBBSpace.x - aabb.getMax().x;}
    //     if(SphereInOBBSpace.y < aabb.getMin().y) { quat.y = SphereInOBBSpace.y - aabb.getMin().y;	}	
    //     else if(SphereInOBBSpace.y > aabb.getMax().y) {	quat.y = SphereInOBBSpace.y - aabb.getMax().y;	}
    //     if(SphereInOBBSpace.z < aabb.getMin().z) { quat.z=SphereInOBBSpace.z-aabb.getMin().z;	} 
    //     else if(SphereInOBBSpace.z > aabb.getMax().z) {	quat.z = SphereInOBBSpace.z - aabb.getMax().z; }
    //     return((quat|quat) < quatradius);
    //   }

    //   /*!
    //   *
    //   * we use the SEPARATING-AXIS-TEST for OBB/Plane overlap.
    //   *
    //   * Example:
    //   *  bool result=Overlap::OBB_Plane( pos,obb, plane );
    //   *
    //   */
    //   inline bool OBB_Plane( const Vec3 &pos, const OBB &obb, const Plane &plane ) {
    //     //the new center-position in world-space
    //     Vec3 p	=	obb.m33*obb.c + pos;
    //     //extract the orientation-vectors from the columns of the 3x3 matrix
    //     //and scale them by the half-lengths
    //     Vec3 ax	= Vec3(obb.m33.m00, obb.m33.m10, obb.m33.m20)*obb.m_vHalf.x;
    //     Vec3 ay	= Vec3(obb.m33.m01, obb.m33.m11, obb.m33.m21)*obb.m_vHalf.y;
    //     Vec3 az	= Vec3(obb.m33.m02, obb.m33.m12, obb.m33.m22)*obb.m_vHalf.z;
    //     //check OBB against Plane, using the plane-normal as separating axis
    //     return	fabsf(plane|p) < (fabsf(plane.n|ax) + fabsf(plane.n|ay) + fabsf(plane.n|az));
    //   }

#define FINDMINMAX(x0,x1,x2,min,max) \
  min = max = x0;   \
  if(x1<min) min=x1;\
  if(x1>max) max=x1;\
  if(x2<min) min=x2;\
  if(x2>max) max=x2;

    //   /*!
    //   *
    //   * we use the SEPARATING AXIS TEST to check if a triangle and an OBB overlaps.
    //   *
    //   * Example:
    //   *  bool result=Overlap::OBB_Trinagle( pos1,obb1, tv0,tv1,tv2 );
    //   *
    //   */
    inline bool OBB_Triangle( const COBB &obb,  const CTriangle& tr ) {

      CQuat m_qRot = obb.m_qRot; 
      //CVec3 m_vecHalf = obb.m_vHalf;
      CVec3 m_vecCenter = obb.m_vCenter;

			CMatrix44 mat(m_qRot);

			CVec3 p(m_vecCenter);
			p.TransformPoint(mat);

     // CVec3 p	=	m_vecCenter*m_qRot;									//the new center-position in world-space

      //move everything so that the boxcenter is in (0,0,0)
      CVec3 v0	=	(tr.t0-p).TransformPoint(mat);; //pre-transform
      CVec3 v1	=	(tr.t1-p).TransformPoint(mat);; //pre-transform
      CVec3 v2	=	(tr.t2-p).TransformPoint(mat);; //pre-transform


      //compute triangle edges
      CVec3 e0	=	v1-v0;
      CVec3 e1	=	v2-v1;
      CVec3 e2	=	v0-v2;

      //--------------------------------------------------------------------------------------
      //    use SEPARATING AXIS THEOREM to test intersection between AABB and triangle
      //    cross-product(edge from triangle, {x,y,z}-direction),  this are 3x3=9 tests
      //--------------------------------------------------------------------------------------
      float min,max,p0,p1,p2,rad,fex,fey,fez;  
      fex = fabsf(e0.x);
      fey = fabsf(e0.y);
      fez = fabsf(e0.z);

      //AXISTEST_X01(e0.z, e0.y, fez, fey);
      p0 = e0.z*v0.y - e0.y*v0.z;  
      p2 = e0.z*v2.y - e0.y*v2.z;   
      if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} 
      rad = fez * obb.m_vHalf.y + fey * obb.m_vHalf.z; 
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Y02(e0.z, e0.x, fez, fex);
      p0 = -e0.z*v0.x + e0.x*v0.z;
      p2 = -e0.z*v2.x + e0.x*v2.z;
      if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;}
      rad = fez * obb.m_vHalf.x + fex * obb.m_vHalf.z;
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Z12(e0.y, e0.x, fey, fex);
      p1 = e0.y*v1.x - e0.x*v1.y;
      p2 = e0.y*v2.x - e0.x*v2.y;
      if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;}
      rad = fey * obb.m_vHalf.x + fex * obb.m_vHalf.y;
      if(min>rad || max<-rad) return 0;

      //-----------------------------------------------

      fex = fabsf(e1.x);
      fey = fabsf(e1.y);
      fez = fabsf(e1.z);
      //AXISTEST_X01(e1.z, e1.y, fez, fey);
      p0 = e1.z*v0.y - e1.y*v0.z;
      p2 = e1.z*v2.y - e1.y*v2.z;
      if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;}
      rad = fez * obb.m_vHalf.y + fey * obb.m_vHalf.z;
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Y02(e1.z, e1.x, fez, fex);
      p0 = -e1.z*v0.x + e1.x*v0.z;
      p2 = -e1.z*v2.x + e1.x*v2.z;
      if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;}
      rad = fez * obb.m_vHalf.x + fex * obb.m_vHalf.z;
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Z0(e1.y, e1.x, fey, fex);
      p0 = e1.y*v0.x - e1.x*v0.y;
      p1 = e1.y*v1.x - e1.x*v1.y;
      if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;}
      rad = fey * obb.m_vHalf.x + fex * obb.m_vHalf.y;
      if(min>rad || max<-rad) return 0;

      //-----------------------------------------------

      fex = fabsf(e2.x);
      fey = fabsf(e2.y);
      fez = fabsf(e2.z);
      //AXISTEST_X2(e2.z, e2.y, fez, fey);
      p0 = e2.z*v0.y - e2.y*v0.z;
      p1 = e2.z*v1.y - e2.y*v1.z;
      if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;}
      rad = fez * obb.m_vHalf.y + fey * obb.m_vHalf.z;
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Y1(e2.z, e2.x, fez, fex);
      p0 = -e2.z*v0.x + e2.x*v0.z;
      p1 = -e2.z*v1.x + e2.x*v1.z;
      if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;}
      rad = fez * obb.m_vHalf.x + fex * obb.m_vHalf.z;
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Z12(e2.y, e2.x, fey, fex);
      p1 = e2.y*v1.x - e2.x*v1.y;
      p2 = e2.y*v2.x - e2.x*v2.y;
      if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;}
      rad = fey * obb.m_vHalf.x + fex * obb.m_vHalf.y;
      if(min>rad || max<-rad) return 0;

      //the {x,y,z}-directions (actually, since we use the AABB of the triangle we don't even need to test these) 
      //first test overlap in the {x,y,z}-directions
      //find min, max of the triangle each direction, and test for overlap in that direction -- 
      //this is equivalent to testing a minimal AABB around the triangle against the AABB
      CAABBox taabb;
      FINDMINMAX(v0.x, v1.x, v2.x, taabb.minVertex.x,taabb.maxVertex.x);
      FINDMINMAX(v0.y, v1.y, v2.y, taabb.minVertex.y,taabb.maxVertex.y);
      FINDMINMAX(v0.z, v1.z, v2.z, taabb.minVertex.z,taabb.maxVertex.z);

      // test in X-direction
      FINDMINMAX(v0.x, v1.x, v2.x, taabb.minVertex.x,taabb.maxVertex.x);
      if(taabb.minVertex.x>obb.m_vHalf.x || taabb.maxVertex.x<-obb.m_vHalf.x) return 0;

      // test in Y-direction
      FINDMINMAX(v0.y, v1.y, v2.y, taabb.minVertex.y,taabb.maxVertex.y);
      if(taabb.minVertex.y>obb.m_vHalf.y || taabb.maxVertex.y<-obb.m_vHalf.y) return 0;

      // test in Z-direction
      FINDMINMAX(v0.z, v1.z, v2.z, taabb.minVertex.z,taabb.maxVertex.z);
      if(taabb.minVertex.z>obb.m_vHalf.z || taabb.maxVertex.z<-obb.m_vHalf.z) return 0;

      //test if the box overlaps the plane of the triangle
      //compute plane equation of triangle: normal*x+d=0
      CPlane plane(v0, e0.Cross(e1));

      CVec3 vmin,vmax;
      if(plane.GetNormal().x>0.0f) {  vmin.x=-obb.m_vHalf.x; vmax.x=+obb.m_vHalf.x; } 
      else { vmin.x=+obb.m_vHalf.x; vmax.x=-obb.m_vHalf.x; }
      if(plane.GetNormal().y>0.0f) {  vmin.y=-obb.m_vHalf.y; vmax.y=+obb.m_vHalf.y; } 
      else { vmin.y=+obb.m_vHalf.y; vmax.y=-obb.m_vHalf.y; }
      if(plane.GetNormal().z>0.0f) {	vmin.z=-obb.m_vHalf.z; vmax.z=+obb.m_vHalf.z; } 
      else {	vmin.z=+obb.m_vHalf.z;	vmax.z=-obb.m_vHalf.z;	}
      if( (plane.DotCoord(vmin)) > 0.0f) return 0;
      if( (plane.DotCoord(vmax)) < 0.0f) return 0;
      return 1;
    }

    inline bool AABB_Triangle ( const CAABBox &aabb,  const CTriangle& tr) {

      const CVec3 tv0 = tr.t0;
      const CVec3 tv1 = tr.t1;
      const CVec3 tv2 = tr.t2; 
      //------ convert AABB into half-length AABB -----------
      CVec3 h	=	(aabb.getMax()-aabb.getMin())*0.5f;	//calculate the half-length-vectors
      CVec3 c	=	(aabb.getMax()+aabb.getMin())*0.5f;	//the center is relative to the PIVOT

      //move everything so that the boxcenter is in (0,0,0)
      CVec3 v0	=	tv0-c;
      CVec3 v1	=	tv1-c;
      CVec3 v2	=	tv2-c;

      //compute triangle edges
      CVec3 e0	=	v1-v0;
      CVec3 e1	=	v2-v1;
      CVec3 e2	=	v0-v2;

      //--------------------------------------------------------------------------------------
      //    use SEPARATING AXIS THEOREM to test overlap  between AABB and triangle
      //    cross-product(edge from triangle, {x,y,z}-direction),  this are 3x3=9 tests
      //--------------------------------------------------------------------------------------
      float min,max,p0,p1,p2,rad,fex,fey,fez;  
      fex = fabsf(e0.x);
      fey = fabsf(e0.y);
      fez = fabsf(e0.z);

      //AXISTEST_X01(e0.z, e0.y, fez, fey);
      p0 = e0.z*v0.y - e0.y*v0.z;  
      p2 = e0.z*v2.y - e0.y*v2.z;   
      if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} 
      rad = fez * h.y + fey * h.z; 
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Y02(e0.z, e0.x, fez, fex);
      p0 = -e0.z*v0.x + e0.x*v0.z;
      p2 = -e0.z*v2.x + e0.x*v2.z;
      if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;}
      rad = fez * h.x + fex * h.z;
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Z12(e0.y, e0.x, fey, fex);
      p1 = e0.y*v1.x - e0.x*v1.y;
      p2 = e0.y*v2.x - e0.x*v2.y;
      if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;}
      rad = fey * h.x + fex * h.y;
      if(min>rad || max<-rad) return 0;

      //-----------------------------------------------

      fex = fabsf(e1.x);
      fey = fabsf(e1.y);
      fez = fabsf(e1.z);
      //AXISTEST_X01(e1.z, e1.y, fez, fey);
      p0 = e1.z*v0.y - e1.y*v0.z;
      p2 = e1.z*v2.y - e1.y*v2.z;
      if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;}
      rad = fez * h.y + fey * h.z;
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Y02(e1.z, e1.x, fez, fex);
      p0 = -e1.z*v0.x + e1.x*v0.z;
      p2 = -e1.z*v2.x + e1.x*v2.z;
      if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;}
      rad = fez * h.x + fex * h.z;
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Z0(e1.y, e1.x, fey, fex);
      p0 = e1.y*v0.x - e1.x*v0.y;
      p1 = e1.y*v1.x - e1.x*v1.y;
      if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;}
      rad = fey * h.x + fex * h.y;
      if(min>rad || max<-rad) return 0;

      //-----------------------------------------------

      fex = fabsf(e2.x);
      fey = fabsf(e2.y);
      fez = fabsf(e2.z);
      //AXISTEST_X2(e2.z, e2.y, fez, fey);
      p0 = e2.z*v0.y - e2.y*v0.z;
      p1 = e2.z*v1.y - e2.y*v1.z;
      if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;}
      rad = fez * h.y + fey * h.z;
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Y1(e2.z, e2.x, fez, fex);
      p0 = -e2.z*v0.x + e2.x*v0.z;
      p1 = -e2.z*v1.x + e2.x*v1.z;
      if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;}
      rad = fez * h.x + fex * h.z;
      if(min>rad || max<-rad) return 0;

      //AXISTEST_Z12(e2.y, e2.x, fey, fex);
      p1 = e2.y*v1.x - e2.x*v1.y;
      p2 = e2.y*v2.x - e2.x*v2.y;
      if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;}
      rad = fey * h.x + fex * h.y;
      if(min>rad || max<-rad) return 0;

      //the {x,y,z}-directions (actually, since we use the AABB of the triangle we don't even need to test these) 
      //first test overlap in the {x,y,z}-directions
      //find min, max of the triangle each direction, and test for overlap in that direction -- 
      //this is equivalent to testing a minimal AABB around the triangle against the AABB
      CAABBox taabb;
      FINDMINMAX(v0.x, v1.x, v2.x, taabb.minVertex.x,taabb.maxVertex.x);
      FINDMINMAX(v0.y, v1.y, v2.y, taabb.minVertex.y,taabb.maxVertex.y);
      FINDMINMAX(v0.z, v1.z, v2.z, taabb.minVertex.z,taabb.maxVertex.z);

      //test in X-direction
      FINDMINMAX(v0.x, v1.x, v2.x, taabb.minVertex.x,taabb.maxVertex.x);
      if(taabb.minVertex.x>h.x || taabb.maxVertex.x<-h.x) return 0;

      //test in Y-direction
      FINDMINMAX(v0.y, v1.y, v2.y, taabb.minVertex.y,taabb.maxVertex.y);
      if(taabb.minVertex.y>h.y || taabb.maxVertex.y<-h.y) return 0;

      //test in Z-direction
      FINDMINMAX(v0.z, v1.z, v2.z, taabb.minVertex.z,taabb.maxVertex.z);
      if(taabb.minVertex.z>h.z || taabb.maxVertex.z<-h.z) return 0;

/*
      CPlane plane;
      plane.FromPoints(tv0, tv1, tv2);

      //test if the box intersects the plane of the triangle
      //compute plane equation of triangle: normal*x+d=0
      //CPlane plane;
      //plane.FromPointNormal(v0, e1.Cross(e0));

      CVec3 vmin,vmax;
      if(plane.a>0.0f) {  vmin.x=-h.x; vmax.x=+h.x; } 
      else { vmin.x=+h.x; vmax.x=-h.x; }
      if(plane.b>0.0f) {  vmin.y=-h.y; vmax.y=+h.y; } 
      else { vmin.y=+h.y; vmax.y=-h.y; }
      if(plane.c>0.0f) {	vmin.z=-h.z; vmax.z=+h.z; } 
      else {	vmin.z=+h.z;	vmax.z=-h.z;	}
      if( (plane.DotCoord(vmin)) > 0.0f) return 0;
      if( (plane.DotCoord(vmax)) < 0.0f) return 0;
*/
      return 1;
    }


  }

  //   /*!
  //   *
  //   * we use the SEPARATING AXIS TEST to check if and AABB and an OBB overlap.
  //   *
  //   * Example:
  //   *  bool result=Overlap::AABB_OBB( aabb, pos,obb );
  //   *
  //   */
  //   inline bool AABB_OBB ( const AABB& aabb,  const Vec3& pos,const OBB& obb ) {

  //     Vec3 h	=	(aabb.max-aabb.min)*0.5f;	//calculate the half-length-vectors
  //     Vec3 c	=	(aabb.max+aabb.min)*0.5f;	//the center in world-space

  //     //"t" is the transfer-vector from one center to the other
  //     Vec3 t	= obb.m33*obb.c+pos-c;

  //     f32 ra,rb;

  //     //--------------------------------------------------------------------------
  //     //--  we use the vectors "1,0,0","0,1,0" and "0,0,1" as separating axis
  //     //--------------------------------------------------------------------------
  //     rb	=	fabsf(obb.m33.m00*obb.m_vHalf.x) + fabsf(obb.m33.m01*obb.m_vHalf.y) + fabsf(obb.m33.m02*obb.m_vHalf.z);
  //     if(   fabsf(t.x) > (fabsf(h.x)+rb) ) return 0;
  //     rb	=	fabsf(obb.m33.m10*obb.m_vHalf.x) + fabsf(obb.m33.m11*obb.m_vHalf.y) + fabsf(obb.m33.m12*obb.m_vHalf.z);
  //     if(   fabsf(t.y) > (fabsf(h.y)+rb) ) return 0;
  //     rb	=	fabsf(obb.m33.m20*obb.m_vHalf.x) + fabsf(obb.m33.m21*obb.m_vHalf.y) + fabsf(obb.m33.m22*obb.m_vHalf.z);
  //     if(   fabsf(t.z) > (fabsf(h.z)+rb) ) return 0;

  //     //--------------------------------------------------------------------------
  //     //--  we use the orientation-vectors "Mx","My" and "Mz" as separating axis
  //     //--------------------------------------------------------------------------
  //     ra	= fabsf(obb.m33.m00*h.x) + fabsf(obb.m33.m10*h.y) + fabsf(obb.m33.m20*h.z);
  //     if( fabsf(t|Vec3(obb.m33.m00,obb.m33.m10,obb.m33.m20)) > (ra+obb.m_vHalf.x) ) return 0;
  //     ra	= fabsf(obb.m33.m01*h.x) + fabsf(obb.m33.m11*h.y) + fabsf(obb.m33.m21*h.z);
  //     if( fabsf(t|Vec3(obb.m33.m01,obb.m33.m11,obb.m33.m21)) > (ra+obb.m_vHalf.y) ) return 0;
  //     ra	= fabsf(obb.m33.m02*h.x) + fabsf(obb.m33.m12*h.y) + fabsf(obb.m33.m22*h.z);
  //     if( fabsf(t|Vec3(obb.m33.m02,obb.m33.m12,obb.m33.m22)) > (ra+obb.m_vHalf.z) ) return 0;

  //     //---------------------------------------------------------------------
  //     //----  using 9 cross products we generate new separating axis
  //     //---------------------------------------------------------------------
  //     ra = h.y*fabsf(obb.m33.m20) + h.z*fabsf(obb.m33.m10);
  //     rb = obb.m_vHalf.y*fabsf(obb.m33.m02) + obb.m_vHalf.z*fabsf(obb.m33.m01);
  //     if( fabsf(t.z*obb.m33.m10-t.y*obb.m33.m20) > (ra+rb) ) return 0;
  //     ra = h.y*fabsf(obb.m33.m21) + h.z*fabsf(obb.m33.m11);
  //     rb = obb.m_vHalf.x*fabsf(obb.m33.m02) + obb.m_vHalf.z*fabsf(obb.m33.m00);
  //     if( fabsf(t.z*obb.m33.m11-t.y*obb.m33.m21) > (ra+rb) ) return 0;
  //     ra = h.y*fabsf(obb.m33.m22) + h.z*fabsf(obb.m33.m12);
  //     rb = obb.m_vHalf.x*fabsf(obb.m33.m01) + obb.m_vHalf.y*fabsf(obb.m33.m00);
  //     if( fabsf(t.z*obb.m33.m12-t.y*obb.m33.m22) > (ra+rb) ) return 0;


  //     ra = h.x*fabsf(obb.m33.m20) + h.z*fabsf(obb.m33.m00);
  //     rb = obb.m_vHalf.y*fabsf(obb.m33.m12) + obb.m_vHalf.z*fabsf(obb.m33.m11);
  //     if( fabsf(t.x*obb.m33.m20-t.z*obb.m33.m00) > (ra+rb) ) return 0;
  //     ra = h.x*fabsf(obb.m33.m21) + h.z*fabsf(obb.m33.m01);
  //     rb = obb.m_vHalf.x*fabsf(obb.m33.m12) + obb.m_vHalf.z*fabsf(obb.m33.m10);
  //     if( fabsf(t.x*obb.m33.m21-t.z*obb.m33.m01) > (ra+rb) ) return 0;
  //     ra = h.x*fabsf(obb.m33.m22) + h.z*fabsf(obb.m33.m02);
  //     rb = obb.m_vHalf.x*fabsf(obb.m33.m11) + obb.m_vHalf.y*fabsf(obb.m33.m10);
  //     if( fabsf(t.x*obb.m33.m22-t.z*obb.m33.m02) > (ra+rb) ) return 0;


  //     ra = h.x*fabsf(obb.m33.m10) + h.y*fabsf(obb.m33.m00);
  //     rb = obb.m_vHalf.y*fabsf(obb.m33.m22) + obb.m_vHalf.z*fabsf(obb.m33.m21);
  //     if( fabsf(t.y*obb.m33.m00-t.x*obb.m33.m10) > (ra+rb) ) return 0;
  //     ra = h.x*fabsf(obb.m33.m11) + h.y*fabsf(obb.m33.m01);
  //     rb = obb.m_vHalf.x*fabsf(obb.m33.m22) + obb.m_vHalf.z*fabsf(obb.m33.m20);
  //     if( fabsf(t.y*obb.m33.m01-t.x*obb.m33.m11) > (ra+rb) ) return 0;
  //     ra = h.x*fabsf(obb.m33.m12) + h.y*fabsf(obb.m33.m02);
  //     rb = obb.m_vHalf.x*fabsf(obb.m33.m21) + obb.m_vHalf.y*fabsf(obb.m33.m20);
  //     if( fabsf(t.y*obb.m33.m02-t.x*obb.m33.m12) > (ra+rb) ) return 0;

  //     //no separating axis found, we have an intersection
  //     return 1;
  //   }

     /*!
     *
     * we use the SEPARATING AXIS TEST to check if two OBB's overlap.
     *
     * Example:
     *  bool result=Overlap::OBB_OBB( pos1,obb1, pos2,obb2 );
     *
     */
     inline bool OBB_OBB ( const CVec3 &pos1,const COBB &obb1,  const CVec3 &pos2,const COBB &obb2 ) {

       //transform obb2 in local space of obb1
       CMatrix44 M(obb1.m_qRot.GetConjugated()*obb2.m_qRot);

       //the new center-position in world-space
       CVec3 p1	=	obb1.m_qRot*obb1.m_vCenter + pos1;
       CVec3 p2	=	obb2.m_qRot*obb2.m_vCenter + pos2;

       //"t" is the transfer-vector from one center to the other
       CVec3 t		= (p2-p1)*obb1.m_qRot;

       float ra,rb;

       //--------------------------------------------------------------------------
       //--  we use the vectors "1,0,0","0,1,0" and "0,0,1" as separating axis
       //--------------------------------------------------------------------------
       rb	=	fabsf(M.m[0][0]*obb2.m_vHalf.x) + fabsf(M.m[0][1]*obb2.m_vHalf.y) + fabsf(M.m[0][2]*obb2.m_vHalf.z);
       if(   fabsf(t.x) > (fabsf(obb1.m_vHalf.x)+rb) ) return 0;
       rb	=	fabsf(M.m[1][0]*obb2.m_vHalf.x) + fabsf(M.m[1][0]*obb2.m_vHalf.y) + fabsf(M.m[1][2]*obb2.m_vHalf.z);
       if(   fabsf(t.y) > (fabsf(obb1.m_vHalf.y)+rb) ) return 0;
       rb	=	fabsf(M.m[2][0]*obb2.m_vHalf.x) + fabsf(M.m[2][1]*obb2.m_vHalf.y) + fabsf(M.m[2][2]*obb2.m_vHalf.z);
       if(   fabsf(t.z) > (fabsf(obb1.m_vHalf.z)+rb) ) return 0;

       //--------------------------------------------------------------------------
       //--  we use the orientation-vectors "Mx","My" and "Mz" as separating axis
       //--------------------------------------------------------------------------
       ra	= fabsf(M.m[0][0]*obb1.m_vHalf.x) + fabsf(M.m[1][0]*obb1.m_vHalf.y) + fabsf(M.m[2][0]*obb1.m_vHalf.z);
       if( fabsf(t.Dot(CVec3(M.m[0][0],M.m[1][0],M.m[2][0]))) > (ra+obb2.m_vHalf.x) ) return 0;
       ra	= fabsf(M.m[0][1]*obb1.m_vHalf.x) + fabsf(M.m[1][0]*obb1.m_vHalf.y) + fabsf(M.m[2][1]*obb1.m_vHalf.z);
       if( fabsf(t.Dot(CVec3(M.m[0][1],M.m[1][0],M.m[2][1]))) > (ra+obb2.m_vHalf.y) ) return 0;
       ra	= fabsf(M.m[0][2]*obb1.m_vHalf.x) + fabsf(M.m[1][2]*obb1.m_vHalf.y) + fabsf(M.m[2][2]*obb1.m_vHalf.z);
       if( fabsf(t.Dot(CVec3(M.m[0][2],M.m[1][2],M.m[2][2]))) > (ra+obb2.m_vHalf.z) ) return 0;

       //---------------------------------------------------------------------
       //----  using 9 cross products we generate new separating axis
       //---------------------------------------------------------------------
       ra = obb1.m_vHalf.y*fabsf(M.m[2][0]) + obb1.m_vHalf.z*fabsf(M.m[1][0]);
       rb = obb2.m_vHalf.y*fabsf(M.m[0][2]) + obb2.m_vHalf.z*fabsf(M.m[0][1]);
       if( fabsf(t.z*M.m[1][0]-t.y*M.m[2][0]) > (ra+rb) ) return 0;
       ra = obb1.m_vHalf.y*fabsf(M.m[2][1]) + obb1.m_vHalf.z*fabsf(M.m[1][0]);
       rb = obb2.m_vHalf.x*fabsf(M.m[0][2]) + obb2.m_vHalf.z*fabsf(M.m[0][0]);
       if( fabsf(t.z*M.m[1][0]-t.y*M.m[2][1]) > (ra+rb) ) return 0;
       ra = obb1.m_vHalf.y*fabsf(M.m[2][2]) + obb1.m_vHalf.z*fabsf(M.m[1][2]);
       rb = obb2.m_vHalf.x*fabsf(M.m[0][1]) + obb2.m_vHalf.y*fabsf(M.m[0][0]);
       if( fabsf(t.z*M.m[1][2]-t.y*M.m[2][2]) > (ra+rb) ) return 0;


       ra = obb1.m_vHalf.x*fabsf(M.m[2][0]) + obb1.m_vHalf.z*fabsf(M.m[0][0]);
       rb = obb2.m_vHalf.y*fabsf(M.m[1][2]) + obb2.m_vHalf.z*fabsf(M.m[1][0]);
       if( fabsf(t.x*M.m[2][0]-t.z*M.m[0][0]) > (ra+rb) ) return 0;
       ra = obb1.m_vHalf.x*fabsf(M.m[2][1]) + obb1.m_vHalf.z*fabsf(M.m[0][1]);
       rb = obb2.m_vHalf.x*fabsf(M.m[1][2]) + obb2.m_vHalf.z*fabsf(M.m[1][0]);
       if( fabsf(t.x*M.m[2][1]-t.z*M.m[0][1]) > (ra+rb) ) return 0;
       ra = obb1.m_vHalf.x*fabsf(M.m[2][2]) + obb1.m_vHalf.z*fabsf(M.m[0][2]);
       rb = obb2.m_vHalf.x*fabsf(M.m[1][0]) + obb2.m_vHalf.y*fabsf(M.m[1][0]);
       if( fabsf(t.x*M.m[2][2]-t.z*M.m[0][2]) > (ra+rb) ) return 0;


       ra = obb1.m_vHalf.x*fabsf(M.m[1][0]) + obb1.m_vHalf.y*fabsf(M.m[0][0]);
       rb = obb2.m_vHalf.y*fabsf(M.m[2][2]) + obb2.m_vHalf.z*fabsf(M.m[2][1]);
       if( fabsf(t.y*M.m[0][0]-t.x*M.m[1][0]) > (ra+rb) ) return 0;
       ra = obb1.m_vHalf.x*fabsf(M.m[1][0]) + obb1.m_vHalf.y*fabsf(M.m[0][1]);
       rb = obb2.m_vHalf.x*fabsf(M.m[2][2]) + obb2.m_vHalf.z*fabsf(M.m[2][0]);
       if( fabsf(t.y*M.m[0][1]-t.x*M.m[1][0]) > (ra+rb) ) return 0;
       ra = obb1.m_vHalf.x*fabsf(M.m[1][2]) + obb1.m_vHalf.y*fabsf(M.m[0][2]);
       rb = obb2.m_vHalf.x*fabsf(M.m[2][1]) + obb2.m_vHalf.y*fabsf(M.m[2][0]);
       if( fabsf(t.y*M.m[0][2]-t.x*M.m[1][2]) > (ra+rb) ) return 0;

       return true; //no separating axis found, we have an overlap
     }




  // }


  namespace Clipping
  {
    // Sutherland-Hodgman algorithm. Clip shape with the plane and return new vector with corners
    FORCEINLINE size_t ClipPlane(const Engine2::Vector<CVec3>& src, Engine2::Vector<CVec3>& dst, const CPlane& plane)
    {

      for (size_t i =0, num = src.size(); i < num; ++i) {
        CVec3 v1(src[i]);
        CVec3 v2(src[(i + 1) % num]);

        float t1 = plane.Distance(v1);
        float t2 = plane.Distance(v2);

        if (t1 >= 0.0f) 
        {
          dst.push_back(v1);
        }

        if (t1 * t2 < 0.0f)
        {
          float k1 =  t2 / (t2 - t1);
          float k2 = -t1 / (t2 - t1);

          dst.push_back(CVec3(v1.x * k1 + v2.x * k2, v1.y * k1 + v2.y * k2, v1.z * k1 + v2.z * k2));
        }
      }

      return dst.size();
    }


    // Clip shape with planes
    FORCEINLINE size_t ClipPolygon(const Engine2::Vector<CVec3>& src, Engine2::Vector<CVec3>& dst, const CPlane * planes, uint32 numPlanes /*const Engine2::Vector<CPlane>& planes*/)
    {
      Engine2::Vector<CVec3> tmp(src);
      for (uint32 i = 0; i < numPlanes; ++i)  {
        ClipPlane(dst, tmp, planes[i]);
        tmp.swap(dst);
      }

      tmp.swap(dst);
      return dst.size();
    }
  }
}