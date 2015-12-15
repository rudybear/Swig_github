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

class CSegment
{
public:
	CVec3 vecOrigin;
	CVec3 vecDestination;

	CSegment() {};
	CSegment(const CVec3& orig, const CVec3& dir) : vecOrigin(orig), vecDestination(dir) {}

	bool isPointInSegment(const CVec3& nPoint) const;

	CVec3 ClosestPointOnLine(const CVec3& nPoint) const;
	CVec3 ClosestPointOnSegment(const CVec3& nPoint) const; //closest point always lies between origin and destination
};

class CTriangle
{
public:
	// three points of triangle
	CVec3 t0;
	CVec3 t1;
	CVec3 t2;

	CTriangle(){};
	CTriangle(const CVec3& a, const CVec3& b, const CVec3& c) : t0(a), t1(b), t2(c) {}

	CVec3 CalcNormal() const
	{
		CVec3 r1 = t1 - t0;
		CVec3 r2 = t2 - t0;
		CVec3 normal = r1.Cross(r2);
		normal.Normalize();
		return normal;
	}

	CPlane CalcPlane() const
	{
		return CPlane(t0, t1, t2);
	}

	float SqrDistance(const CVec3& nPoint) const
	{
		// edge0 = t1-t0
		// edge1 = t2-t0

		CVec3 kDiff = t0 - nPoint;
		CVec3 vecEdge0 = t1 - t0, vecEdge1 = t2 - t0;

		float fA00 = vecEdge0.LengthSq();
		float fA01 = vecEdge0.Dot(vecEdge1);
		float fA11 = vecEdge1.LengthSq();
		float fB0 = kDiff.Dot(vecEdge0);
		float fB1 = kDiff.Dot(vecEdge1);
		float fC = kDiff.LengthSq();
		float fDet = fabs(fA00*fA11-fA01*fA01);
		float fS = fA01*fB1-fA11*fB0;
		float fT = fA01*fB0-fA00*fB1;
		float fSqrDist;

		if ( fS + fT <= fDet )
		{
			if ( fS < 0.0 )
			{
				if ( fT < 0.0 )  // region 4
				{
					if ( fB0 < 0.0 )
					{
						fT = 0.0;
						if ( -fB0 >= fA00 )
						{
							fS = 1.0;
							fSqrDist = fA00+2*fB0+fC;
						}
						else
						{
							fS = -fB0/fA00;
							fSqrDist = fB0*fS+fC;
						}
					}
					else
					{
						fS = 0.0;
						if ( fB1 >= 0.0 )
						{
							fT = 0.0;
							fSqrDist = fC;
						}
						else if ( -fB1 >= fA11 )
						{
							fT = 1.0;
							fSqrDist = fA11+2*fB1+fC;
						}
						else
						{
							fT = -fB1/fA11;
							fSqrDist = fB1*fT+fC;
						}
					}
				}
				else  // region 3
				{
					fS = 0.0;
					if ( fB1 >= 0.0 )
					{
						fT = 0.0;
						fSqrDist = fC;
					}
					else if ( -fB1 >= fA11 )
					{
						fT = 1.0;
						fSqrDist = fA11+2*fB1+fC;
					}
					else
					{
						fT = -fB1/fA11;
						fSqrDist = fB1*fT+fC;
					}
				}
			}
			else if ( fT < 0.0 )  // region 5
			{
				fT = 0.0;
				if ( fB0 >= 0.0 )
				{
					fS = 0.0;
					fSqrDist = fC;
				}
				else if ( -fB0 >= fA00 )
				{
					fS = 1.0;
					fSqrDist = fA00+2*fB0+fC;
				}
				else
				{
					fS = -fB0/fA00;
					fSqrDist = fB0*fS+fC;
				}
			}
			else  // region 0
			{
				// minimum at interior point
				float fInvDet = 1/fDet;
				fS *= fInvDet;
				fT *= fInvDet;
				fSqrDist = fS*(fA00*fS + fA01*fT + 2*fB0) + fT*(fA01*fS+fA11*fT + 2*fB1) + fC;
			}
		}
		else
		{
			float fTmp0, fTmp1, fNumer, fDenom;

			if ( fS < 0.0 )  // region 2
			{
				fTmp0 = fA01 + fB0;
				fTmp1 = fA11 + fB1;
				if ( fTmp1 > fTmp0 )
				{
					fNumer = fTmp1 - fTmp0;
					fDenom = fA00 - 2*fA01+fA11;
					if ( fNumer >= fDenom )
					{
						fS = 1.0;
						fT = 0.0;
						fSqrDist = fA00 + 2*fB0+fC;
					}
					else
					{
						fS = fNumer/fDenom;
						fT = 1.0f - fS;
						fSqrDist = fS*(fA00*fS + fA01*fT + 2.0f*fB0) + fT*(fA01*fS + fA11*fT + 2*fB1) + fC;
					}
				}
				else
				{
					fS = 0.0;
					if ( fTmp1 <= 0.0 )
					{
						fT = 1.0;
						fSqrDist = fA11 + 2*fB1+fC;
					}
					else if ( fB1 >= 0.0 )
					{
						fT = 0.0;
						fSqrDist = fC;
					}
					else
					{
						fT = -fB1/fA11;
						fSqrDist = fB1*fT+fC;
					}
				}
			}
			else if ( fT < 0.0 )  // region 6
			{
				fTmp0 = fA01 + fB1;
				fTmp1 = fA00 + fB0;
				if ( fTmp1 > fTmp0 )
				{
					fNumer = fTmp1 - fTmp0;
					fDenom = fA00 - 2*fA01 + fA11;
					if ( fNumer >= fDenom )
					{
						fT = 1.0;
						fS = 0.0;
						fSqrDist = fA11 + 2*fB1 + fC;
					}
					else
					{
						fT = fNumer/fDenom;
						fS = 1.0f - fT;
						fSqrDist = fS*(fA00*fS + fA01*fT + 2*fB0) + fT*(fA01*fS+fA11*fT + 2*fB1) + fC;
					}
				}
				else
				{
					fT = 0.0;
					if ( fTmp1 <= 0.0 )
					{
						fS = 1.0;
						fSqrDist = fA00 + 2*fB0 + fC;
					}
					else if ( fB0 >= 0.0 )
					{
						fS = 0.0;
						fSqrDist = fC;
					}
					else
					{
						fS = -fB0/fA00;
						fSqrDist = fB0*fS + fC;
					}
				}
			}
			else  // region 1
			{
				fNumer = fA11 + fB1 - fA01 - fB0;
				if ( fNumer <= 0.0 )
				{
					fS = 0.0;
					fT = 1.0;
					fSqrDist = fA11 + 2*fB1 + fC;
				}
				else
				{
					fDenom = fA00 - 2.0f*fA01 + fA11;
					if ( fNumer >= fDenom )
					{
						fS = 1.0;
						fT = 0.0;
						fSqrDist = fA00 + 2*fB0 + fC;
					}
					else
					{
						fS = fNumer/fDenom;
						fT = 1.0f - fS;
						fSqrDist = fS*(fA00*fS + fA01*fT + 2*fB0) + fT*(fA01*fS+fA11*fT + 2*fB1) + fC;
					}
				}
			}
		}

		return fabs(fSqrDist);
	}

	float Distance(const CVec3& nPoint) const
	{
		return sqrt(SqrDistance(nPoint));
	}


	void Projection(const CVec3& nPoint, float& rfMin, float& rfMax) const
	{
		float afDot[3] = { nPoint.Dot(t0), nPoint.Dot(t1), nPoint.Dot(t2) };

		rfMin = afDot[0];
		rfMax = rfMin;

		if ( afDot[1] < rfMin )
			rfMin = afDot[1];
		else if ( afDot[1] > rfMax )
			rfMax = afDot[1];

		if ( afDot[2] < rfMin )
			rfMin = afDot[2];
		else if ( afDot[2] > rfMax )
			rfMax = afDot[2];

	}

	bool isPointInside(const CVec3& vecPoint) const
	{
		CVec3 e10 = t1 - t0;
		CVec3 e20 = t2 - t0;
		float a, b, c, ac_bb, d, e, x, y, z;

		a = e10.Dot(e10);
		b = e10.Dot(e20);
		c = e20.Dot(e20);
		ac_bb = (a*c) - (b*b);
		CVec3 vp = vecPoint - t0;
		d = vp.Dot(e10);
		e = vp.Dot(e20);
		x = (d * c) - (e * b);
		y = (e * a) - (d * b);
		z = x + y - ac_bb;
		return (( int(z)& ~(int(x)|int(y)) ) & 0x80000000)!= 0;
	}

	CVec3 ClosestPoint(const CVec3& nPoint) const
	{
		CVec3 Rab = CSegment(t0, t1).ClosestPointOnSegment(nPoint);
		CVec3 Rbc = CSegment(t1, t2).ClosestPointOnSegment(nPoint);
		CVec3 Rca = CSegment(t2, t0).ClosestPointOnSegment(nPoint);

		double dAB = (nPoint - Rab).Length();
		double dBC = (nPoint - Rbc).Length();
		double dCA = (nPoint - Rca).Length();
		double min = dAB;
		CVec3 result = Rab;

		if (dBC < min)
		{
			min = dBC;
			result = Rbc;
		}

		if (dCA < min)
			result = Rca;

		return (result);	
	}

	float Area() const
	{
		CVec3 r1 = t1 - t0;
		CVec3 r2 = t2 - t0;
		CVec3 normal = r1.Cross(r2);
		return normal.Length()/2;
	}

};


class CSphere
{
public:
	CVec3 vecOrigin;
	float fRadius;

	CSphere() {};
	CSphere(const CVec3& orig, const float radius) : vecOrigin(orig), fRadius(radius) {};
	bool isPointInside(const CVec3& vecPoint) const;
};

class CEllipsoid
{
	// center-matrix form, (X-C)^T A (X-C) = 1, where A is a positive
	// definite matrix

public:
	CEllipsoid()
	{
		m_vecCenter = CVec3(0,0,0);
	};

	CEllipsoid(CVec3 vecCenter, CVec3 vecRotationYPR, CVec3 vecScale)
	{
		m_vecCenter = vecCenter;
		m_qRotation.FromRotation(vecRotationYPR);
		m_vecScale = vecScale;
		UpdateA();
	}

	CEllipsoid(const CEllipsoid& eldSrc)
	{
		//just copy all
		m_vecCenter = eldSrc.m_vecCenter;
		m_qRotation = eldSrc.m_qRotation;
		m_vecScale = eldSrc.m_vecScale;
		m_matA = eldSrc.m_matA;
	}

	FORCEINLINE void Rescale(CVec3 vecNewScale)
	{
		vecNewScale /= 2.0f;
		m_vecScale = vecNewScale;
		UpdateA();
	}


	CVec3 m_vecCenter;
	CMatrix44 m_matA;
	CQuaternion m_qRotation;
	CVec3 m_vecScale;
private:

	FORCEINLINE void UpdateA()
	{
		CMatrix44 matDiagonal, matRotation(m_qRotation), matRotationInverse;
		matDiagonal._11 = 1/(m_vecScale.x*m_vecScale.x);
		matDiagonal._22 = 1/(m_vecScale.y*m_vecScale.y);
		matDiagonal._33 = 1/(m_vecScale.z*m_vecScale.z);
		matRotationInverse = matRotation.GetInvert();
		m_matA = matRotation * matDiagonal * matRotationInverse;
	}

};

class CCylinder
{
public:
	CCylinder(){};
	CCylinder(CVec3 fPointA, CVec3 fPointB, float fRadius) : m_vecPointA(fPointA), m_vecPointB(fPointB), m_fRadius(fRadius) {};
	CVec3 GetCenter(){return (m_vecPointA+m_vecPointB)/2;};
	float GetHeight(){return (m_vecPointA - m_vecPointB).Length();};

public:
	CVec3 m_vecPointA;
	CVec3 m_vecPointB;
	float m_fRadius;
};

class CCapsule
{
public:
	CVec3 m_vecOrigin;
	CVec3 m_vecExtent;
	float m_fRadius;
};
