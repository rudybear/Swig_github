//
//  D3DX.h
//  Engine2


#pragma once

#define CONST const
#define FLOAT float
#define BOOL bool
#define WORD int16

typedef struct D3DXFLOAT16
{
#ifdef __cplusplus
public:
    D3DXFLOAT16() {};
    D3DXFLOAT16( FLOAT );
    D3DXFLOAT16( CONST D3DXFLOAT16& );
    
    // casting
    operator FLOAT ();
    
    // binary operators
    BOOL operator == ( CONST D3DXFLOAT16& ) const;
    BOOL operator != ( CONST D3DXFLOAT16& ) const;
    
protected:
#endif //__cplusplus
    WORD value;
} D3DXFLOAT16, *LPD3DXFLOAT16;


//--------------------------
// 2D Vector
//--------------------------
typedef struct D3DXVECTOR2
{
#ifdef __cplusplus
public:
    D3DXVECTOR2() {};
    D3DXVECTOR2( CONST FLOAT * );
    D3DXVECTOR2( CONST D3DXFLOAT16 * );
    D3DXVECTOR2( FLOAT x, FLOAT y );
    
    // casting
    operator FLOAT* ();
    operator CONST FLOAT* () const;
    
    // assignment operators
    D3DXVECTOR2& operator += ( CONST D3DXVECTOR2& );
    D3DXVECTOR2& operator -= ( CONST D3DXVECTOR2& );
    D3DXVECTOR2& operator *= ( FLOAT );
    D3DXVECTOR2& operator /= ( FLOAT );
    
    // unary operators
    D3DXVECTOR2 operator + () const;
    D3DXVECTOR2 operator - () const;
    
    // binary operators
    D3DXVECTOR2 operator + ( CONST D3DXVECTOR2& ) const;
    D3DXVECTOR2 operator - ( CONST D3DXVECTOR2& ) const;
    D3DXVECTOR2 operator * ( FLOAT ) const;
    D3DXVECTOR2 operator / ( FLOAT ) const;
    
    friend D3DXVECTOR2 operator * ( FLOAT, CONST D3DXVECTOR2& );
    
    BOOL operator == ( CONST D3DXVECTOR2& ) const;
    BOOL operator != ( CONST D3DXVECTOR2& ) const;
    
    
public:
#endif //__cplusplus
    FLOAT x, y;
} D3DXVECTOR2, *LPD3DXVECTOR2;

typedef struct _D3DVECTOR {
	float x;
	float y;
	float z;
} D3DVECTOR;

typedef struct D3DXVECTOR3 : public D3DVECTOR
{
public:
    D3DXVECTOR3() {};
    D3DXVECTOR3( CONST FLOAT * );
    D3DXVECTOR3( CONST D3DVECTOR& );
    D3DXVECTOR3( CONST D3DXFLOAT16 * );
    D3DXVECTOR3( FLOAT x, FLOAT y, FLOAT z );
    
    // casting
    operator FLOAT* ();
    operator CONST FLOAT* () const;
    
    // assignment operators
    D3DXVECTOR3& operator += ( CONST D3DXVECTOR3& );
    D3DXVECTOR3& operator -= ( CONST D3DXVECTOR3& );
    D3DXVECTOR3& operator *= ( FLOAT );
    D3DXVECTOR3& operator /= ( FLOAT );
    
    // unary operators
    D3DXVECTOR3 operator + () const;
    D3DXVECTOR3 operator - () const;
    
    // binary operators
    D3DXVECTOR3 operator + ( CONST D3DXVECTOR3& ) const;
    D3DXVECTOR3 operator - ( CONST D3DXVECTOR3& ) const;
    D3DXVECTOR3 operator * ( FLOAT ) const;
    D3DXVECTOR3 operator / ( FLOAT ) const;
    
    friend D3DXVECTOR3 operator * ( FLOAT, CONST struct D3DXVECTOR3& );
    
    BOOL operator == ( CONST D3DXVECTOR3& ) const;
    BOOL operator != ( CONST D3DXVECTOR3& ) const;
    
} D3DXVECTOR3, *LPD3DXVECTOR3;


typedef struct D3DXVECTOR4
{
#ifdef __cplusplus
public:
	D3DXVECTOR4() {};
	D3DXVECTOR4( CONST FLOAT* );
	D3DXVECTOR4( CONST D3DXFLOAT16* );
	D3DXVECTOR4( CONST D3DVECTOR& xyz, FLOAT w );
	D3DXVECTOR4( FLOAT x, FLOAT y, FLOAT z, FLOAT w );

	// casting
	operator FLOAT* ();
	operator CONST FLOAT* () const;

	// assignment operators
	D3DXVECTOR4& operator += ( CONST D3DXVECTOR4& );
	D3DXVECTOR4& operator -= ( CONST D3DXVECTOR4& );
	D3DXVECTOR4& operator *= ( FLOAT );
	D3DXVECTOR4& operator /= ( FLOAT );

	// unary operators
	D3DXVECTOR4 operator + () const;
	D3DXVECTOR4 operator - () const;

	// binary operators
	D3DXVECTOR4 operator + ( CONST D3DXVECTOR4& ) const;
	D3DXVECTOR4 operator - ( CONST D3DXVECTOR4& ) const;
	D3DXVECTOR4 operator * ( FLOAT ) const;
	D3DXVECTOR4 operator / ( FLOAT ) const;

	friend D3DXVECTOR4 operator * ( FLOAT, CONST D3DXVECTOR4& );

	BOOL operator == ( CONST D3DXVECTOR4& ) const;
	BOOL operator != ( CONST D3DXVECTOR4& ) const;

public:
#endif //__cplusplus
	FLOAT x, y, z, w;
} D3DXVECTOR4, *LPD3DXVECTOR4;

typedef struct _D3DMATRIX {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};
} D3DMATRIX;

typedef struct D3DXMATRIX : public D3DMATRIX
{
public:
	D3DXMATRIX() {};
	D3DXMATRIX( CONST FLOAT * );
	D3DXMATRIX( CONST D3DMATRIX& );
	D3DXMATRIX( CONST D3DXFLOAT16 * );
	D3DXMATRIX( FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
		FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
		FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
		FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44 );


	// access grants
	FLOAT& operator () ( UINT Row, UINT Col );
	FLOAT  operator () ( UINT Row, UINT Col ) const;

	// casting operators
	operator FLOAT* ();
	operator CONST FLOAT* () const;

	// assignment operators
	D3DXMATRIX& operator *= ( CONST D3DXMATRIX& );
	D3DXMATRIX& operator += ( CONST D3DXMATRIX& );
	D3DXMATRIX& operator -= ( CONST D3DXMATRIX& );
	D3DXMATRIX& operator *= ( FLOAT );
	D3DXMATRIX& operator /= ( FLOAT );

	// unary operators
	D3DXMATRIX operator + () const;
	D3DXMATRIX operator - () const;

	// binary operators
	D3DXMATRIX operator * ( CONST D3DXMATRIX& ) const;
	D3DXMATRIX operator + ( CONST D3DXMATRIX& ) const;
	D3DXMATRIX operator - ( CONST D3DXMATRIX& ) const;
	D3DXMATRIX operator * ( FLOAT ) const;
	D3DXMATRIX operator / ( FLOAT ) const;

	friend D3DXMATRIX operator * ( FLOAT, CONST D3DXMATRIX& );

	BOOL operator == ( CONST D3DXMATRIX& ) const;
	BOOL operator != ( CONST D3DXMATRIX& ) const;

} D3DXMATRIX, *LPD3DXMATRIX;

typedef struct _D3DXMATRIXA16 : public D3DXMATRIX
{
	_D3DXMATRIXA16() {}
	_D3DXMATRIXA16( CONST FLOAT * );
	_D3DXMATRIXA16( CONST D3DMATRIX& );
	_D3DXMATRIXA16( CONST D3DXFLOAT16 * );
	_D3DXMATRIXA16( FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
		FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
		FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
		FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44 );

	// new operators
	void* operator new   ( size_t );
	void* operator new[] ( size_t );

	// delete operators
	void operator delete   ( void* );   // These are NOT virtual; Do not 
	void operator delete[] ( void* );   // cast to D3DXMATRIX and delete.

	// assignment operators
	_D3DXMATRIXA16& operator = ( CONST D3DXMATRIX& );

} _D3DXMATRIXA16;

typedef _D3DXMATRIXA16 D3DXMATRIXA16, *LPD3DXMATRIXA16;

FORCEINLINE D3DXMATRIX* D3DXMatrixIdentity
( D3DXMATRIX *pOut )
{
#ifdef D3DX_DEBUG
	if(!pOut)
		return NULL;
#endif

	pOut->m[0][1] = pOut->m[0][2] = pOut->m[0][3] =
		pOut->m[1][0] = pOut->m[1][2] = pOut->m[1][3] =
		pOut->m[2][0] = pOut->m[2][1] = pOut->m[2][3] =
		pOut->m[3][0] = pOut->m[3][1] = pOut->m[3][2] = 0.0f;

	pOut->m[0][0] = pOut->m[1][1] = pOut->m[2][2] = pOut->m[3][3] = 1.0f;
	return pOut;
}

D3DXMATRIX* WINAPI D3DXMatrixRotationYawPitchRoll
( D3DXMATRIX *pOut, FLOAT Yaw, FLOAT Pitch, FLOAT Roll );

D3DXMATRIX* WINAPI D3DXMatrixTranspose
( D3DXMATRIX *pOut, CONST D3DXMATRIX *pM );

D3DXMATRIX* WINAPI D3DXMatrixMultiply
( D3DXMATRIX *pOut, CONST D3DXMATRIX *pM1, CONST D3DXMATRIX *pM2 );

D3DXMATRIX* WINAPI D3DXMatrixPerspectiveFovLH
( D3DXMATRIX *pOut, FLOAT fovy, FLOAT Aspect, FLOAT zn, FLOAT zf );

D3DXMATRIX* WINAPI D3DXMatrixOrthoLH
( D3DXMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf );

typedef struct D3DXQUATERNION
{
#ifdef __cplusplus
public:
	D3DXQUATERNION() {}
	D3DXQUATERNION( CONST FLOAT * );
	D3DXQUATERNION( CONST D3DXFLOAT16 * );
	D3DXQUATERNION( FLOAT x, FLOAT y, FLOAT z, FLOAT w );

	// casting
	operator FLOAT* ();
	operator CONST FLOAT* () const;

	// assignment operators
	D3DXQUATERNION& operator += ( CONST D3DXQUATERNION& );
	D3DXQUATERNION& operator -= ( CONST D3DXQUATERNION& );
	D3DXQUATERNION& operator *= ( CONST D3DXQUATERNION& );
	D3DXQUATERNION& operator *= ( FLOAT );
	D3DXQUATERNION& operator /= ( FLOAT );

	// unary operators
	D3DXQUATERNION  operator + () const;
	D3DXQUATERNION  operator - () const;

	// binary operators
	D3DXQUATERNION operator + ( CONST D3DXQUATERNION& ) const;
	D3DXQUATERNION operator - ( CONST D3DXQUATERNION& ) const;
	D3DXQUATERNION operator * ( CONST D3DXQUATERNION& ) const;
	D3DXQUATERNION operator * ( FLOAT ) const;
	D3DXQUATERNION operator / ( FLOAT ) const;

	friend D3DXQUATERNION operator * (FLOAT, CONST D3DXQUATERNION& );

	BOOL operator == ( CONST D3DXQUATERNION& ) const;
	BOOL operator != ( CONST D3DXQUATERNION& ) const;

#endif //__cplusplus
	FLOAT x, y, z, w;
} D3DXQUATERNION, *LPD3DXQUATERNION;

// Build a quaternion from a rotation matrix.
D3DXQUATERNION* WINAPI D3DXQuaternionRotationMatrix
( D3DXQUATERNION *pOut, CONST D3DXMATRIX *pM);

FORCEINLINE D3DXQUATERNION* D3DXQuaternionConjugate
( D3DXQUATERNION *pOut, CONST D3DXQUATERNION *pQ )
{
#ifdef D3DX_DEBUG
	if(!pOut || !pQ)
		return NULL;
#endif

	pOut->x = -pQ->x;
	pOut->y = -pQ->y;
	pOut->z = -pQ->z;
	pOut->w =  pQ->w;
	return pOut;
}

D3DXQUATERNION* WINAPI D3DXQuaternionNormalize
( D3DXQUATERNION *pOut, CONST D3DXQUATERNION *pQ );


FORCEINLINE D3DXVECTOR2* D3DXVec2Lerp
( D3DXVECTOR2 *pOut, CONST D3DXVECTOR2 *pV1, CONST D3DXVECTOR2 *pV2,
 FLOAT s )
{
#ifdef D3DX_DEBUG
	if(!pOut || !pV1 || !pV2)
		return NULL;
#endif

	pOut->x = pV1->x + s * (pV2->x - pV1->x);
	pOut->y = pV1->y + s * (pV2->y - pV1->y);
	return pOut;
}

D3DXVECTOR2* WINAPI D3DXVec2Normalize
( D3DXVECTOR2 *pOut, CONST D3DXVECTOR2 *pV );

// Transform (x, y, z, 1) by matrix, project result back into w=1.
D3DXVECTOR3* WINAPI D3DXVec3TransformCoord
( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DXMATRIX *pM );

FORCEINLINE D3DXVECTOR3* D3DXVec3Cross
( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV1, CONST D3DXVECTOR3 *pV2 )
{
	D3DXVECTOR3 v;

#ifdef D3DX_DEBUG
	if(!pOut || !pV1 || !pV2)
		return NULL;
#endif

	v.x = pV1->y * pV2->z - pV1->z * pV2->y;
	v.y = pV1->z * pV2->x - pV1->x * pV2->z;
	v.z = pV1->x * pV2->y - pV1->y * pV2->x;

	*pOut = v;
	return pOut;
}

FORCEINLINE D3DXVECTOR3* D3DXVec3Lerp
( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV1, CONST D3DXVECTOR3 *pV2,
 FLOAT s )
{
#ifdef D3DX_DEBUG
	if(!pOut || !pV1 || !pV2)
		return NULL;
#endif

	pOut->x = pV1->x + s * (pV2->x - pV1->x);
	pOut->y = pV1->y + s * (pV2->y - pV1->y);
	pOut->z = pV1->z + s * (pV2->z - pV1->z);
	return pOut;
}

D3DXVECTOR3* WINAPI D3DXVec3Normalize
( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV );

D3DXVECTOR3* WINAPI D3DXVec3TransformNormal
( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DXMATRIX *pM );

// Transform vector by matrix.
D3DXVECTOR4* WINAPI D3DXVec4Transform
( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV, CONST D3DXMATRIX *pM );

FORCEINLINE D3DXVECTOR4* D3DXVec4Lerp
( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV1, CONST D3DXVECTOR4 *pV2,
 FLOAT s )
{
#ifdef D3DX_DEBUG
	if(!pOut || !pV1 || !pV2)
		return NULL;
#endif

	pOut->x = pV1->x + s * (pV2->x - pV1->x);
	pOut->y = pV1->y + s * (pV2->y - pV1->y);
	pOut->z = pV1->z + s * (pV2->z - pV1->z);
	pOut->w = pV1->w + s * (pV2->w - pV1->w);
	return pOut;
}

D3DXVECTOR4* WINAPI D3DXVec4Normalize
( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV );

FORCEINLINE D3DXVECTOR4* D3DXVec4Add
( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV1, CONST D3DXVECTOR4 *pV2)
{
#ifdef D3DX_DEBUG
	if(!pOut || !pV1 || !pV2)
		return NULL;
#endif

	pOut->x = pV1->x + pV2->x;
	pOut->y = pV1->y + pV2->y;
	pOut->z = pV1->z + pV2->z;
	pOut->w = pV1->w + pV2->w;
	return pOut;
}

FORCEINLINE D3DXVECTOR4* D3DXVec4Subtract
( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV1, CONST D3DXVECTOR4 *pV2)
{
#ifdef D3DX_DEBUG
	if(!pOut || !pV1 || !pV2)
		return NULL;
#endif

	pOut->x = pV1->x - pV2->x;
	pOut->y = pV1->y - pV2->y;
	pOut->z = pV1->z - pV2->z;
	pOut->w = pV1->w - pV2->w;
	return pOut;
}

FORCEINLINE D3DXVECTOR4* D3DXVec4Scale
( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV, FLOAT s)
{
#ifdef D3DX_DEBUG
	if(!pOut || !pV)
		return NULL;
#endif

	pOut->x = pV->x * s;
	pOut->y = pV->y * s;
	pOut->z = pV->z * s;
	pOut->w = pV->w * s;
	return pOut;
}

// Cross-product in 4 dimensions.
D3DXVECTOR4* WINAPI D3DXVec4Cross
( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV1, CONST D3DXVECTOR4 *pV2,
 CONST D3DXVECTOR4 *pV3);

typedef struct D3DXPLANE
{
#ifdef __cplusplus
public:
	D3DXPLANE() {}
	D3DXPLANE( CONST FLOAT* );
	D3DXPLANE( CONST D3DXFLOAT16* );
	D3DXPLANE( FLOAT a, FLOAT b, FLOAT c, FLOAT d );

	// casting
	operator FLOAT* ();
	operator CONST FLOAT* () const;

	// assignment operators
	D3DXPLANE& operator *= ( FLOAT );
	D3DXPLANE& operator /= ( FLOAT );

	// unary operators
	D3DXPLANE operator + () const;
	D3DXPLANE operator - () const;

	// binary operators
	D3DXPLANE operator * ( FLOAT ) const;
	D3DXPLANE operator / ( FLOAT ) const;

	friend D3DXPLANE operator * ( FLOAT, CONST D3DXPLANE& );

	BOOL operator == ( CONST D3DXPLANE& ) const;
	BOOL operator != ( CONST D3DXPLANE& ) const;

#endif //__cplusplus
	FLOAT a, b, c, d;
} D3DXPLANE, *LPD3DXPLANE;

// Construct a plane from a point and a normal
D3DXPLANE* WINAPI D3DXPlaneFromPointNormal
( D3DXPLANE *pOut, CONST D3DXVECTOR3 *pPoint, CONST D3DXVECTOR3 *pNormal);

// Construct a plane from 3 points
D3DXPLANE* WINAPI D3DXPlaneFromPoints
( D3DXPLANE *pOut, CONST D3DXVECTOR3 *pV1, CONST D3DXVECTOR3 *pV2,
 CONST D3DXVECTOR3 *pV3);


// Normalize plane (so that |a,b,c| == 1)
D3DXPLANE* WINAPI D3DXPlaneNormalize
( D3DXPLANE *pOut, CONST D3DXPLANE *pP);

D3DXVECTOR3* WINAPI D3DXPlaneIntersectLine
( D3DXVECTOR3 *pOut, CONST D3DXPLANE *pP, CONST D3DXVECTOR3 *pV1,
 CONST D3DXVECTOR3 *pV2);

FORCEINLINE FLOAT D3DXVec3Dot
( CONST D3DXVECTOR3 *pV1, CONST D3DXVECTOR3 *pV2 )
{
#ifdef D3DX_DEBUG
	if(!pV1 || !pV2)
		return 0.0f;
#endif

	return pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z;
}

D3DXQUATERNION* WINAPI D3DXQuaternionSlerp
( D3DXQUATERNION *pOut, CONST D3DXQUATERNION *pQ1,
 CONST D3DXQUATERNION *pQ2, FLOAT t );

D3DXMATRIX* WINAPI D3DXMatrixLookAtRH
( D3DXMATRIX *pOut, CONST D3DXVECTOR3 *pEye, CONST D3DXVECTOR3 *pAt,
 CONST D3DXVECTOR3 *pUp );

D3DXQUATERNION* WINAPI D3DXQuaternionRotationYawPitchRoll
( D3DXQUATERNION *pOut, FLOAT Yaw, FLOAT Pitch, FLOAT Roll );

D3DXMATRIX* WINAPI D3DXMatrixRotationQuaternion
( D3DXMATRIX *pOut, CONST D3DXQUATERNION *pQ);

D3DXMATRIX* WINAPI D3DXMatrixScaling
( D3DXMATRIX *pOut, FLOAT sx, FLOAT sy, FLOAT sz );

D3DXMATRIX* WINAPI D3DXMatrixInverse
( D3DXMATRIX *pOut, FLOAT *pDeterminant, CONST D3DXMATRIX *pM );

D3DXMATRIX* WINAPI D3DXMatrixLookAtLH
( D3DXMATRIX *pOut, CONST D3DXVECTOR3 *pEye, CONST D3DXVECTOR3 *pAt,
 CONST D3DXVECTOR3 *pUp );

