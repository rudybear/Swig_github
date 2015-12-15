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
#include "Mathlib.h"
#include "Intersection.h"


enum Visibility { NO_CLIP, SOME_CLIP, NOT_VISIBLE, NOT_PROCESSED };

#define TOTALLYVISIBLE			0
#define TOSCREENLEFT				1
#define TOSCREENRIGHT				2
#define TOSCREENTOP					4
#define TOSCREENBOTTOM			8
#define TOSCREENBACK				16
#define TOSCREENFRONT				32



/*
  Base camera class. This class engine uses for internal puproses, only view\projection setting, no smart behaviour
*/
/*DLLIMPORT */class CCamera
{
private:

  //! Camera point
  CVec3 m_vEyePt;       // Attributes for view matrix
  //! Camera target point
  CVec3 m_vLookatPt;
  //! Camera up vector
  CVec3 m_vUpVec;
  //! Camera normalized view-direction
  CVec3 m_vView;
  //! Camera right-vector
  CVec3 m_vCross;
  //! Reindexing array
  int m_nVertexLUT[6];
  //! Boundaries points
  CVec3 m_pntList[8];
  //! Euler angles
  float m_ViewAngles[3]; // Yaw, Pitch, Roll
  //! Billboard matri
  CMatrix44  m_matBillboard; // Special matrix for billboarding effects
  //! Horizontal field-of-view
  float       m_fFOV;         // Attributes for projection matrix
  //! Vertical field-of-view
  float       m_fFOVv;         // Attributes for projection matrix
  //! Aspect ration
  float       m_fAspect;
  //! Near plane distance
  float       m_fNearPlane;
  //! Far plane distance
  float       m_fFarPlane;
  //! Projection matrix
  CMatrix44  m_matProj;
  //! View matrix
  CMatrix44  m_matView;
  //! Frustum planes in world-space
  CPlane m_FrustumPlane[6];
  //! Transformed frustum planes
  CPlane m_TransformedFrustumPlane[6];
  //! Latest frame camera change flag
  bool	m_bChanged;

  CVec3 m_vShadowEyePt;       // Attributes for view matrix
  //! Camera target point
  CVec3 m_vShadowDirection;

  //! 
  void						CalcCullPlanes();
public:

  CCamera()	:
      m_vEyePt(0,0,0),       // Attributes for view matrix
        m_vLookatPt(0,0,0),
        m_vUpVec(0,0,0),
        m_vView(0,0,0),
        m_vCross(0,0,0),
        m_matBillboard(0), // Special matrix for billboarding effects
        m_matProj(0),
        m_matView(0),
        m_vShadowEyePt(0,0,0),
        m_vShadowDirection(0,0,1)
      {
        // Set attributes for the projection matrix
        SetProjParams( DegreeToRadian(60.0f), 4.0f/3.0f, 3.0f, 4000.0f );
        // Set attributes for the view matrix
        SetViewParams( CVec3(0.0f,0.0f,0.0f), CVec3(0.0f,0.0f,1.0f), CVec3(0.0f,1.0f,0.0f) );
      }

      //! Return camera point
      inline const CVec3& GetEyePt()  const          /*{ return CVec3(m_matView._41,m_matView._42,m_matView._42);}; //*/{ return m_vEyePt; }
      //! Return target point
      inline const CVec3& GetLookatPt() const        { return m_vLookatPt; }
      //! Return up vector
      inline const CVec3& GetUpVec() const          { return m_vUpVec; }
      //! Return view direction
      inline const CVec3& GetViewDir() const        { return m_vView; }
      //! Return right-vector
      inline const CVec3& GetCross() const           { return m_vCross; }
      //! Return view matrix
      inline const CMatrix44&  GetViewMatrix() const     { return m_matView; }
      //! Return billboard matrix
      inline const CMatrix44&  GetBillboardMatrix() const { return m_matBillboard; }
      //! Return projection matrix
      inline const CMatrix44&  GetProjMatrix() const      { return m_matProj; }
      //! Return far plane distance
      inline float GetFarPlane() const { return m_fFarPlane;};
      //! Return near-plane distance
      inline float GetNearPlane() const { return m_fNearPlane;};
      //! Return horizontal field-of-view
      inline float GetFOV() const { return m_fFOV;};
      //! Return vertical field-of-view
      inline float GetFOVv() const { return m_fFOVv;};
      //! Return aspect ratio
      inline float GetAspect() const { return m_fAspect;};
      //! Set view matrix from ready matrix
      inline void SetViewMatrix(const CMatrix44 & mat );
      inline void SetShadowViewParams(const CVec3 &vEyePt, const CVec3& vDirection);
      inline void SetViewParams( const CVec3 &vEyePt, const CVec3& vLookatPt, const CVec3& vUpVec );
      inline void SetViewParams2(const CVec3& vLookatDir, const CVec3& vUpVec);
      inline void SetViewParams3(const CVec3 &vEyePt, const CVec3& vLookatDir, const CVec3& vUpVec );
      inline void SetProjParams( float fFOV, float fAspect, float fNearPlane, float fFarPlane, float fDeltaX=0.0f, float fDeltaY=0.0f );
      inline void GetProjParams( float *fFOV, float *fAspect, float *fNearPlane,	float *fFarPlane );
      inline void SetProjMatrix(const CMatrix44 & mat );
      inline void SetProjMatrixNoClipPlanes(const CMatrix44 & mat );
      inline void SetNearFar(float fNear, float fFar) { m_fNearPlane = fNear; m_fFarPlane = fFar; }

      //! Return shadow camera point
      inline const CVec3& GetShadowEyePt()  const  { return m_vShadowEyePt; }
      //! Return shadow direction
      inline const CVec3& GetShadowDirection() const        { return m_vShadowDirection; }

      inline void	MoveTo(const CVec3 &vEyePt);
      inline void	MoveToPlane(const CVec3 &vEyePt, float y);

      inline void SetViewParamsAngles(const CVec3 &vEyePt, float Yaw, float Picth, float Roll);

      inline float GetYaw() const { return m_ViewAngles[0];};
      inline float GetPicth() const { return m_ViewAngles[1];};
      inline float GetRoll() const { return m_ViewAngles[2];};

      inline Visibility	ComputeBoxVisibility(const float min[3], const float max[3]);
      inline Visibility	ComputeBoxVisibility(const CAABBox& box);

      inline bool	ComputeSphereVisibility(float x, float y, float z, float radius)
      {
        bool inside = true;
        CVec3 Center(x, y, z);

        for (int i=0; (i<6) && inside; i++)
          inside &= (m_TransformedFrustumPlane[i].DotCoord(Center) + radius) >= 0.0f;

        return inside;

      }

      inline bool	ComputeSphereVisibility(const float coord[4])
      {
        return ComputeSphereVisibility(coord[0],coord[1],coord[2],coord[3]);
      }

      inline bool	ComputeSphereVisibility(const CVec3& point, float radius)
      {
        return ComputeSphereVisibility(point.x,point.y,point.z,radius);
      }

      inline int ProjectionVisibilityTesting(CVec3 Point) const;

      inline bool LastFrameChanged();

      inline void ClearChangedFlag()
      {
        m_bChanged = false;
      }

      void SetChangedFlag()
      {
        m_bChanged = true;
      }

      inline void GetUnprojectedBoundingVertices(CVec3 *pVer) const;// should be 8 points
      inline void GetBoundingVertices(CVec3 *pVer) const;// should be 8 points
      inline const CPlane* GetFrustumPlane(int i) const;
      inline bool	ComputePointVisibility(const CVec3& point) const;

};

///////////////////////////////////////////////////////////////////////////////
//	File: Camera.cpp
//	Description: Camera
//	Copyright (c) 2004 Rudybear
///////////////////////////////////////////////////////////////////////////////




inline void CCamera::SetViewParams3(const CVec3 &vEyePt, const CVec3& vLookatDir, const CVec3& vUpVec)
{
  m_bChanged = true;
  m_vEyePt    = vEyePt;
  m_vLookatPt = vLookatDir + m_vEyePt;
  m_vUpVec    = vUpVec;
  m_vView = m_vLookatPt - m_vEyePt;
  m_vView.Normalize();
  m_vCross = m_vView.Cross(m_vUpVec);
  m_matView = MatrixLookAtLH(m_vEyePt, m_vLookatPt, m_vUpVec);
  m_matBillboard = m_matView.GetInvert();
  m_matBillboard._41 = 0.0f;
  m_matBillboard._42 = 0.0f;
  m_matBillboard._43 = 0.0f;
  CalcCullPlanes();
}


inline  void CCamera::SetViewParams2(const CVec3& vLookatDir, const CVec3& vUpVec )
{
  m_bChanged = true;
  m_vLookatPt = vLookatDir + m_vEyePt;
  m_vUpVec    = vUpVec;
  m_vView = m_vLookatPt - m_vEyePt;
  m_vView.Normalize();
  m_vCross = m_vView.Cross(m_vUpVec);
  m_matView = MatrixLookAtLH(m_vEyePt, m_vLookatPt, m_vUpVec);

  m_matBillboard = m_matView.GetInvert();
  m_matBillboard._41 = 0.0f;
  m_matBillboard._42 = 0.0f;
  m_matBillboard._43 = 0.0f;

  CalcCullPlanes();
}

inline void CCamera::SetViewMatrix(const CMatrix44 & mat )
{
  // Set attributes for the view matrix
  m_bChanged = true;

  m_matView = mat;
  m_matBillboard = m_matView.GetInvert();

  m_matBillboard._41 = 0.0f;
  m_matBillboard._42 = 0.0f;
  m_matBillboard._43 = 0.0f;

  CalcCullPlanes();

}


inline void CCamera::SetProjMatrix(const CMatrix44 & mat )
{
  m_bChanged = true;
  m_matProj = mat;
  CalcCullPlanes();
}

inline void CCamera::SetProjMatrixNoClipPlanes(const CMatrix44 & mat )
{
  m_bChanged = true;
  m_matProj = mat;
}

inline void CCamera::SetViewParams(const CVec3 &vEyePt, const CVec3& vLookatPt, const CVec3& vUpVec )
{
  m_bChanged = true;
  // Set attributes for the view matrix
  m_vEyePt    = vEyePt;
  m_vLookatPt = vLookatPt;
  m_vUpVec    = vUpVec;

  m_vView = m_vLookatPt - m_vEyePt;
  m_vView.Normalize();
  m_vCross = m_vView.Cross(m_vUpVec);
  m_matView = MatrixLookAtLH(m_vEyePt, m_vLookatPt, m_vUpVec);
  m_matBillboard = m_matView.GetInvert();

  m_matBillboard._41 = 0.0f;
  m_matBillboard._42 = 0.0f;
  m_matBillboard._43 = 0.0f;

  CalcCullPlanes();

}

inline void CCamera::SetShadowViewParams(const CVec3 &vEyePt, const CVec3& vDirection)
{
  // Set shadow attributes for the view matrix
  m_vShadowEyePt    = vEyePt;
  m_vShadowDirection = vDirection;
}

// FIXME!!!
inline int CCamera::ProjectionVisibilityTesting(CVec3 Point) const
{
  CVec3 vRet;
  CMatrix44 m_matWorld;
  //	CMatrix4Identity(&m_matWorld);
  /*
  g_pScene->m_pRender->GetDevice()->GetViewport(&m_ViewPort);

  int res = TOTALLYVISIBLE;
  vRet = CVec3Project(&Point, &m_ViewPort, &m_matProj, &m_matView, &m_matWorld);


  if (vRet.x < m_ViewPort.X) 
  res |= TOSCREENLEFT;

  else if (vRet.x > m_ViewPort.Width) 
  res |= TOSCREENRIGHT;		

  if (vRet.y < m_ViewPort.Y)
  res |= TOSCREENTOP;

  else if (vRet.y > m_ViewPort.Height)
  res |= TOSCREENBOTTOM;

  if (vRet.z > m_ViewPort.MaxZ)
  res |= TOSCREENBACK;

  else if (vRet.z < m_ViewPort.MinZ) 
  res |= TOSCREENFRONT;


  return res;
  */
  return -1;
}


inline bool	CCamera::ComputePointVisibility(const CVec3& point) const
{
  bool inside = true;

  for (int i=0; (i<6) && inside; i++)
    inside &= m_TransformedFrustumPlane[i].DotCoord(point) >= 0.0f;

  return inside;

}
inline Visibility	CCamera::ComputeBoxVisibility(const CAABBox& box)
{
  bool intersect = false;

  const CVec3 min=box.getMin();
  const CVec3 max=box.getMax();
  for (int i=0; i<6; i++)
  {
    int nV = m_nVertexLUT[i];
    // pVertex is diagonally opposed to nVertex
    CVec3 nVertex( (nV&1)?min[0]:max[0], (nV&2)?min[1]:max[1], (nV&4)?min[2]:max[2] );
    CVec3 pVertex( (nV&1)?max[0]:min[0], (nV&2)?max[1]:min[1], (nV&4)?max[2]:min[2] );

    if (m_TransformedFrustumPlane[i].DotCoord(nVertex) < 0.0f)
      return NOT_VISIBLE;
    if (m_TransformedFrustumPlane[i].DotCoord(pVertex) < 0.0f)
      intersect = true;

  }

  return (intersect)?SOME_CLIP : NO_CLIP;

}

inline Visibility	CCamera::ComputeBoxVisibility(const float min[3], const float max[3])
// Returns a visibility code indicating whether the axis-aligned box defined by {min, max} is
// completely inside the frustum, completely outside the frustum, or partially in.
{

  bool intersect = false;

  for (int i=0; i<6; i++)
  {
    int nV = m_nVertexLUT[i];
    // pVertex is diagonally opposed to nVertex
    CVec3 nVertex( (nV&1)?min[0]:max[0], (nV&2)?min[1]:max[1], (nV&4)?min[2]:max[2] );
    CVec3 pVertex( (nV&1)?max[0]:min[0], (nV&2)?max[1]:min[1], (nV&4)?max[2]:min[2] );

    if (m_TransformedFrustumPlane[i].DotCoord(nVertex) < 0.0f)
      return NOT_VISIBLE;
    if (m_TransformedFrustumPlane[i].DotCoord(pVertex) < 0.0f)
      intersect = true;

  }

  return (intersect)?SOME_CLIP : NO_CLIP;
}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
inline void CCamera::SetProjParams( float fFOV, float fAspect, float fNearPlane,
                                   float fFarPlane, float fDeltaX, float fDeltaY )
{
  m_bChanged = true;
  // Set attributes for the projection matrix
  m_fFOV        = atan(tan(fFOV/2) * fAspect ) * 2;//fFOV;//atan(tan(fFOV/2) / fAspect ) * 2;
  m_fFOVv		  = fFOV;
  m_fAspect     = fAspect;
  m_fNearPlane  = fNearPlane;
  m_fFarPlane   = fFarPlane;
  float	m_fFOVV =  fFOV;//atan(tan(m_fFOV/2) * fAspect ) * 2;

  m_matProj = MatrixPerspectiveFovLH(fFOV, fAspect, fNearPlane, fFarPlane );

  // Perspective off-center:
  //   fDeltaX = -1..1, where -1=center at left edge, 1=center at right edge
  //   fDeltaY = -1..1, where -1=center at bottom edge, 1=center at top edge
  m_matProj._31 = fDeltaX;
  m_matProj._32 = fDeltaY;

  const float ah1 = m_fFOV  * 0.5f * ( 1.0f - fDeltaX );
  const float ah2 = m_fFOV  * 0.5f * ( 1.0f + fDeltaX );
  const float av1 = m_fFOVV * 0.5f * ( 1.0f + fDeltaY );
  const float av2 = m_fFOVV * 0.5f * ( 1.0f - fDeltaY );

  m_FrustumPlane[0] = CPlane( 0, 0,  1,  m_fNearPlane);   // near
  m_FrustumPlane[1] = CPlane( 0, 0, -1, -m_fFarPlane );   // far
  m_FrustumPlane[2] = CPlane( -cos(ah1), 0, sin(ah1), 0); // right
  m_FrustumPlane[3] = CPlane(  cos(ah2), 0, sin(ah2), 0); // left
  m_FrustumPlane[4] = CPlane( 0, -cos(av1), sin(av1), 0); // top
  m_FrustumPlane[5] = CPlane( 0,  cos(av2), sin(av2), 0); // bottom


  CalcCullPlanes();
}

inline void CCamera::GetProjParams( float *fFOV, float *fAspect, float *fNearPlane,	float *fFarPlane )
{
  m_bChanged = true;
  *fFOV		  = m_fFOVv;
  *fAspect     = m_fAspect;
  *fNearPlane  = m_fNearPlane;
  *fFarPlane   = m_fFarPlane;
}



inline void CCamera::CalcCullPlanes()
{

  CMatrix44 matrix = m_matView * m_matProj;

  CVec4 column4( matrix._14, matrix._24, matrix._34, matrix._44 );
  CVec4 column1( matrix._11, matrix._21, matrix._31, matrix._41 );
  CVec4 column2( matrix._12, matrix._22, matrix._32, matrix._42 );
  CVec4 column3( matrix._13, matrix._23, matrix._33, matrix._43 );

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
    m_TransformedFrustumPlane[p] = CPlane( planes[p].x, planes[p].y, planes[p].z, planes[p].w );

  //  build a bit-field that will tell us the indices for the nearest and farthest vertices from each plane...
  for (int i=0; i<6; i++)
    m_nVertexLUT[i] = ((planes[i].x<0.f)?1:0) | ((planes[i].y<0.f)?2:0) | ((planes[i].z<0.f)?4:0);

  for (int i=0; i<8; i++)  // compute extrema
  {
    const CPlane& p0 = (i&1)?m_TransformedFrustumPlane[4] : m_TransformedFrustumPlane[5];
    const CPlane& p1 = (i&2)?m_TransformedFrustumPlane[3] : m_TransformedFrustumPlane[2];
    const CPlane& p2 = (i&4)?m_TransformedFrustumPlane[0] : m_TransformedFrustumPlane[1];

    PlaneIntersection( &m_pntList[i], &p0, &p1, &p2 );
  }

	SetChangedFlag();
}

inline void CCamera::SetViewParamsAngles(const CVec3& vEyePt, float Yaw, float Pitch, float Roll)
{
  m_bChanged = true;
  m_ViewAngles[0] = DegreeToRadian(Yaw)  ;
  m_ViewAngles[1] = DegreeToRadian(Pitch);
  m_ViewAngles[2] = DegreeToRadian(Roll);

  m_vEyePt = vEyePt;
  CVec3 vLook(0.0f,0.0f,1.0f); 
  CVec3 vUp(0.0f,1.0f,0.0f); 
  CVec3 vRight(1.0f,0.0f,0.0f); 

  CMatrix44 matR;

  matR = MatrixRotationYawPitchRoll(m_ViewAngles[0],m_ViewAngles[1],m_ViewAngles[2]);

  vLook = vLook.TransformNormal(matR);
  vRight = vRight.TransformNormal(matR);
  vUp = vUp.TransformNormal(matR);

  m_vView = vLook;

  m_matView.Identity();
  m_matView._11 = vRight.x; m_matView._12 = vUp.x; m_matView._13 = vLook.x;
  m_matView._21 = vRight.y; m_matView._22 = vUp.y; m_matView._23 = vLook.y;
  m_matView._31 = vRight.z; m_matView._32 = vUp.z; m_matView._33 = vLook.z;
  m_matView._41 = - m_vEyePt.Dot(vRight);
  m_matView._42 = - m_vEyePt.Dot(vUp );
  m_matView._43 = - m_vEyePt.Dot(vLook );

  m_matBillboard = m_matView.GetInvert();

  CalcCullPlanes();
}

inline void	CCamera::MoveTo(const CVec3 &vEyePt)
{
  m_bChanged = true;
  m_vEyePt.x = m_vEyePt.x + vEyePt.x * m_vView.x;
  m_vEyePt.y = m_vEyePt.y + vEyePt.y * m_vView.y;
  m_vEyePt.z = m_vEyePt.z + vEyePt.z * m_vView.z;

  CVec3 vLook(0.0f,0.0f,1.0f);  
  CVec3 vUp(0.0f,1.0f,0.0f); 
  CVec3 vRight(1.0f,0.0f,0.0f); 

  CMatrix44 matR;

  matR = MatrixRotationYawPitchRoll(m_ViewAngles[0],m_ViewAngles[1],m_ViewAngles[2]);

  vLook = vLook.TransformNormal(matR);
  vRight = vRight.TransformNormal(matR);
  vUp = vUp.TransformNormal(matR);

  m_vView = vLook;

  m_matView.Identity();
  m_matView._11 = vRight.x; m_matView._12 = vUp.x; m_matView._13 = vLook.x;
  m_matView._21 = vRight.y; m_matView._22 = vUp.y; m_matView._23 = vLook.y;
  m_matView._31 = vRight.z; m_matView._32 = vUp.z; m_matView._33 = vLook.z;
  m_matView._41 = - m_vEyePt.Dot(vRight);
  m_matView._42 = - m_vEyePt.Dot(vUp );
  m_matView._43 = - m_vEyePt.Dot(vLook );

  m_matBillboard = m_matView.GetInvert();

  CalcCullPlanes();
}

inline void	CCamera::MoveToPlane(const CVec3 &vEyePt, float y)
{
  m_bChanged = true;
  m_vEyePt.x = m_vEyePt.x + vEyePt.x * m_vView.x;
  m_vEyePt.y = y;
  m_vEyePt.z = m_vEyePt.z + vEyePt.z * m_vView.z;

  CVec3 vLook(0.0f,0.0f,1.0f);  
  CVec3 vUp(0.0f,1.0f,0.0f); 
  CVec3 vRight(1.0f,0.0f,0.0f); 

  CMatrix44 matR;

  matR = MatrixRotationYawPitchRoll(m_ViewAngles[0],m_ViewAngles[1],m_ViewAngles[2]);

  vLook = vLook.TransformNormal(matR);
  vRight = vRight.TransformNormal(matR);
  vUp = vUp.TransformNormal(matR);

  m_vView = vLook;

  m_matView.Identity();// defined in d3dutil.h and d3dutil.cpp 
  m_matView._11 = vRight.x; m_matView._12 = vUp.x; m_matView._13 = vLook.x;
  m_matView._21 = vRight.y; m_matView._22 = vUp.y; m_matView._23 = vLook.y;
  m_matView._31 = vRight.z; m_matView._32 = vUp.z; m_matView._33 = vLook.z;
  m_matView._41 = - m_vEyePt.Dot(vRight); 
  m_matView._42 = - m_vEyePt.Dot(vUp);
  m_matView._43 = - m_vEyePt.Dot(vLook);

  m_matBillboard = m_matView.GetInvert();
  CalcCullPlanes();
}


inline bool CCamera::LastFrameChanged()
{
  return m_bChanged;
}


inline void CCamera::GetUnprojectedBoundingVertices(CVec3 *pVer) const// should be 8 points
{
  CMatrix44 inverse = (m_matView * m_matProj).GetInvert();

  for (int i = 0; i < 8; ++i) {
    pVer[i] = m_pntList[i] * inverse;
  }
}

inline void CCamera::GetBoundingVertices(CVec3 *pVer) const// should be 8 points
{
  for (int i = 0; i < 8; ++i) {
    pVer[i] = m_pntList[i];
  }
}

inline const CPlane* CCamera::GetFrustumPlane(int i) const
{
  return &m_TransformedFrustumPlane[i];
}

