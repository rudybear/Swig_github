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
#include "Public/Core/ICullObject.h"
#include "Public/Render/IShader.h"

class IMeshFactory;

typedef CSmartPtr<ICullObject> ICullObjectPtr;

// Error states 
#define MESHNOTCREATED -1


// Render flags
// Object cast shadows
#define OBJ_SHADOW_CASTER				0x00000001
// Object receive shadows
#define OBJ_SHADOW_RECEIVER			0x00000002
// Object receive lights
#define OBJ_LIGHT_RECEIVER			0x00000004
// Object shown in reflection
#define OBJ_IN_REFLECTION       0x00000008
// Object shown in refraction
#define OBJ_IN_REFRACTION       0x00000010
// Object is STATIC object(not changes his position)
#define OBJ_IS_STATIC						0x00000020
//
#define OBJ_IN_FRAME					0x00000040

#define OBJ_USE_IMPOSTER					0x00000080

#define OBJ_CAST_LIGHTMAP			0x00000100

#define OBJ_USAGE_ATTACHMENT     0x00000200

#define OBJ_USE_LIGHTMAP			0x00000400

#define OBJ_SILHOUETTE     		0x00000800
#define OBJ_OVERLAY       		0x00001000
#define OBJ_IGNORE_BRIGHTNESS	0x00002000
#define OBJ_NO_SKINNING       0x00004000
#define OBJ_TOON              0x00008000
#define OBJ_USE_TRACED_LIGHTMAP 0x00010000
#define OBJ_ROAD              0x00020000
#define OBJ_DONT_UPDATE_CM  	0x00040000
//! force mesh to skip culling. It's always rendered. Not implemented yet!
#define OBJ_ALWAYS_RENDERED  	0x00080000

#define OBJ_USE_INSTANCING  	0x00100000

class IMeshArray;

struct CollisionInfo {
	CollisionInfo() : m_iRequestedTextureLayer(0), m_bUseLOD(true), m_bGetTextureCoordinates(false)  {}
	CVec3 m_vecObjectIntersection;
	CVec3 m_vecIntersection;
	CVec3 m_vecNormal;
	CVec3 m_vecSkinnedIntersection;
	CVec2 m_vecTextureCoordinate; // return texture coordinates if passed m_bGetTextureCoordinates = true
	int m_iTextureID; //return texture id if passed m_bGetTextureCoordinates = true
	int m_iRequestedTextureLayer; // texture layer for equest (0 by default)
	int m_iAdditional;
	bool m_bUseLOD;
	bool m_bSaveAllCollisions;
	bool m_bGetTextureCoordinates;
	Engine2::Vector<CVec3> m_vecAllIntersections;
	Engine2::Vector<CVec3> m_vecAllNormals;
};


//! Class for node modification
class INodeModifier {

	// Actual node modification
	virtual void Update(IMeshInfo *) = 0;
};


//class INodeAnimation() {
//
//}

enum eDecalType
{
	eGenerateGeometry,
	eUseMeshes
};


struct EngineDecalInfo
{
	eDecalType            m_eDecalType;
	uint32								m_nDecalID;
	IMeshInfo*						m_pDecalOwner;
	CVec3									m_vDecalOffset;							// Decal offset below the ground
	CVec3                 m_vPos;											// Decal position (world coordinates)
	CVec3                 m_vNormal;									// Decal/face normal
	float									m_fWidth;										// Decal size
	float									m_fHeight;									// Decal size
	float									m_fLifeTime;								// Decal life time (in seconds)
	Engine2::String				m_szMaterialName;						// Material name
	float									m_fAngle;										// Angle of rotation
	float									m_fDotAcceptThreshold;	// Angle cos to check when accept triangle
	CVec3                 m_vHitDirection;						// Direction from weapon/player position to decal position (bullet direction)
	unsigned int          m_nGroupId;                 // Used for multi-component decals
	Engine2::Vector<IMeshInfo*> m_vecFoundedColliders;
	CVec3                 m_vFoundedIntersection;
	float                 m_fBoxWidth; // box extension
	float                 m_fBoxHeight; // box extension
	float                 m_fBoxLength; // box extension
	uint8									m_nSortPriority;
	uint8                 m_bTrustedCollision;
	uint8                 m_bUseBBoxCollision;

	FORCEINLINE EngineDecalInfo()
	{
		m_eDecalType = eGenerateGeometry;
		//memset(this,0,sizeof(*this));
		m_nSortPriority = 255;
		m_nDecalID = 0;
		m_pDecalOwner = 0;
		m_vDecalOffset = m_vPos = m_vNormal = m_vHitDirection = CVec3(0, 0, 0);
		m_fHeight = m_fWidth = 0;
		m_fLifeTime = 0;
		m_fAngle = 0;
		m_nGroupId = 0;
		m_bTrustedCollision = false;
		m_bUseBBoxCollision = false;
		m_fDotAcceptThreshold = 0;
	}
};


class IDecalInfo
{
public:
	virtual ~IDecalInfo() {};
};


class IDecalMeshAccepter
{
public:
	virtual ~IDecalMeshAccepter() {}
	virtual bool AcceptDecal(IDecalInfo *) = 0;
};


enum eDebugMode {
	eNoDebugMode = 0,
	eBoxDebugMode = 1,
	eNormalsDebugMode = 2,
	eBoxAndBonesDebugMode = 3
};

class IMeshInfoFriend;

class IMeshInfo : public IStreamedStated
{
	friend class IMeshFactory;
	friend class IMeshArray;
	friend class IMeshInfoFriend;

public:

	virtual IDecalMeshAccepter * GetDecalAccepter() {
		return 0;
	}

	//! Returen mesh type
	virtual eMeshType GetMeshType() const = 0;
	virtual void  NewFrameStarted() {};
	virtual HRESULT Cull(eRenderType, bool bFullyVisible) = 0;
	virtual HRESULT CullSimple(eRenderType, bool bFullyVisible) = 0;
	//!
	virtual HRESULT Restore() = 0;
	virtual HRESULT ImmediateDraw(eRenderType) = 0;
	//!
	virtual HRESULT SetParam(CParam *pParamInfo)
	{
		if (m_pMesh) return m_pMesh->SetParam(pParamInfo);
		return E_FAIL;
	}
	//!
	virtual HRESULT DeleteParam(CParam *pParamInfo)
	{
		if (m_pMesh) return m_pMesh->DeleteParam(pParamInfo);
		return E_FAIL;
	}

	virtual bool Update(bool bFromParent)
	{
		return false;
	}
	virtual HRESULT InitMeshInfo(const CXmlElement * paraminfo) = 0;
	BOOL IsVisible(void){ return m_bInVisibleList; };
	virtual void SetVisibleState(bool state) = 0;
	ICullObject * GetCullObject() { return m_pMesh; }
	virtual IMeshInfo * Copy() = 0;
	virtual unsigned int GetSortInt() { return 0; };
	uint32 GetRenderFlags() const { return m_RenderFlags; }
	void SetRenderFlags(uint32 flags) { m_RenderFlags = m_RenderFlags | flags; }
	void ForceSetRenderFlags(uint32 flags) { m_RenderFlags = flags; }
	void RemoveRenderFlags(uint32 flags) { m_RenderFlags = m_RenderFlags & ~flags; }
	void DrawCustom(eRenderType type) {}
	virtual bool DrawFogPass(eRenderType) { return true; }
	virtual void SetMatrix(const CMatrix44& mat, BOOL bFullUpdate = TRUE) {
		CVec3 newPos(mat.GetTranslation());
		if (newPos != m_AbsMat.GetTranslation()) {
			if (!bFullUpdate)
				SetBBoxTranslation(newPos);
			OnPositionChanged(newPos);
		}
		m_AbsMat = mat;
		if (bFullUpdate) {
			m_abBox = m_pMesh->m_abBox;
			m_abBox.extendByRotationAbsolute(mat);
			m_abBox.move(newPos);
		}
	}

	virtual void SetRotation(const CQuat& rot) {
		m_AbsMat.FromPosRot(m_AbsMat.GetTranslation(), rot);
	}

	virtual void SetRotation(const CVec3& rot) {
		m_AbsMat.FromDirection(rot);
	}

	virtual void SetRotation(float yaw, float pitch, float roll) {
		m_AbsMat.FromYPR(yaw, pitch, roll);
	}

	const CMatrix44& GetMatrix() const {
		return m_AbsMat;
	}

	// Its already translation for BBOx too
	virtual void SetTranslation(const CVec3& vec) {
		if (vec != m_AbsMat.GetTranslation()) {
			SetBBoxTranslation(vec);
			OnPositionChanged(vec);
			m_AbsMat.SetTranslation(vec);
		}
	}

	virtual void SetMatrixTranslation(const CVec3& vec) {
		if (vec != m_AbsMat.GetTranslation()) {
			OnPositionChanged(vec);
			m_AbsMat.SetTranslation(vec);
		}
	}

	virtual void SetBBoxTranslation(const CVec3& vec) {
		m_abBox = m_pMesh->m_abBox;
		m_abBox.move(vec);
	}

	void SetBBox(const CAABBox& box) {
		OnBBoxChanged(box);
		m_abBox = box;
	}

	const CAABBox& GetBBox() const {
		return m_abBox;
	}

	float GetRadius() const {
		return m_fRadius;
	}

	void SetRadius(float rad) {
		m_fRadius = rad;
	}

	virtual bool TestRayIntersection(const CSegment& nRay, CollisionInfo *) = 0;

	virtual void RemoveFromList(IMeshInfo*) {};

	void SetDebugMode(eDebugMode mode) {
		m_eDebugMode = mode;
	}

	eDebugMode GetDebugMode() const {
		return (eDebugMode)m_eDebugMode;
	}

	virtual bool IsImmediate() const {
		return false;
	}

	virtual void SetBrightness(CVec4 vBrightness) {
		m_vBrightness = vBrightness;
	}
	virtual CVec4 GetBrightness() const {
		return m_vBrightness;
	}


	//protected: 

	virtual void OnPositionChanged(const CVec3& newPos) = 0;
	virtual void OnBBoxChanged(const CAABBox& newBox) = 0;

	virtual void SetLightInfo(CLightArray * array, int group) {}

	bool IsCopy() const  { return m_bCopy; }
public:
	IMeshInfo* GetNext() const { return m_pNext; }
	IMeshInfo* GetPrev() const { return m_pPrev; }

	void SetNext(IMeshInfo* p) { m_pNext = p; }
	void SetPrev(IMeshInfo* p) { m_pPrev = p; }

	Engine2::String m_strFileName;
	//Engine2::String m_strMeshType;
	ICullObjectPtr m_pMesh;
	ICullObjectPtr m_pOriginalMesh;
	IMeshInfo * m_pParent;
	void * m_pSector;
protected:

	IMeshInfo * m_pPrev;
	IMeshInfo * m_pNext;

	CMatrix44 m_AbsMat; //Matrix which contains position and rotation of Object
	CAABBox m_abBox;
	float m_fRadius;
	CVec4 m_vBrightness;
	uint32 m_RenderFlags;
	char m_eDebugMode;
	bool m_bInVisibleList;
	bool m_bCopy;
	//bool m_bSelfDraw;
	virtual ICullObject * CreateObject(void) = 0;
	virtual ~IMeshInfo(void){}
	virtual void Delete() { delete this; }
	//! Конструктор защищенный, ибо нефиг.
	IMeshInfo(void)
	{
		m_RenderFlags = OBJ_SHADOW_CASTER | OBJ_SHADOW_RECEIVER | OBJ_LIGHT_RECEIVER | OBJ_IN_REFLECTION | OBJ_IN_REFRACTION | OBJ_IN_FRAME;
		//m_bVisible = TRUE;
		m_bInVisibleList = false;
		//m_iUsageFlag = 0;
		m_AbsMat.Identity();
		m_fRadius = 0.0f;
		m_abBox.setMin(CVec3(0, 0, 0));
		m_abBox.setMax(CVec3(0, 0, 0));
		m_pParent = 0;
		m_eDebugMode = eNoDebugMode;
		m_pPrev = m_pNext = 0;
		m_pSector = 0;
		m_vBrightness = CVec4(0, 0, 0, 1);
		m_bCopy = false;
		//		m_abBox.setMid(CVec3(0,0,0));
	}
};


/*
*@}
*/

class IMeshFactory {
public:
	void DeleteMeshInfo(IMeshInfo * mi) { mi->Delete(); };
	ICullObject * CreateObject(IMeshInfo * mi) { return mi->CreateObject(); };
	//void SetMeshInfoInVisibleList(IMeshInfo * mi, bool b) { mi->m_bInVisibleList = b; }
protected:
	IMeshFactory() {};
};

struct XRefInfo {
	CMatrix44 m_Mat;
	Engine2::String m_sName;
	Engine2::String m_sFileName;
};


class IXRefInfoMesh {
public:
	virtual size_t GetXRefInfoNum() = 0;
	virtual XRefInfo * GetXRefInfo(size_t ind) = 0;
};

class IMaterialInfo : public IMeshInfo {
public:
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// General functions
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! Get visible materials count
	virtual uint32 GetVisibleMaterialsCount() = 0;
	//! Get visible material name
	virtual const char * GetVisibleMaterialName(uint32) = 0;
	//! Get visible material by index
	virtual const IMaterial * GetVisibleMaterial(uint32 num) = 0;
	//! Set new visible material
	virtual bool SetVisibleMaterial(uint32 num, const IMaterial*) = 0;
	//! Set visible material by new material name
	virtual bool SetVisibleMaterialByMaterialName(uint32 mat, const char * newMat) = 0;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Quick access functions
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! Get count of params for material
	virtual uint32 GetVisibleMaterialParamCount(uint32 mat) = 0;
	////! Get specified CParam from material and index
	virtual CParam * GetVisibleMaterialParam(uint32 mat, uint32 param) = 0;
	////! Add a new parameter to the material
	virtual bool AddVisibleMaterialParam(uint32 mat, CParam& param) = 0;

	virtual bool AddVisibleMaterialParamPtr(uint32 mat, CParam* param) { return false; };
};





// Indoor mesh info
// Empty yet. To be improved
class IIndoorMeshInfo : public IMeshInfo, public IXRefInfoMesh
{
public:
	virtual int GetNumSubmeshes() = 0;
	// return the name of submesh
	virtual const char* GetSubmeshName(int num) = 0;
	// get number from name
	virtual int GetSubmeshFromName(const char *) = 0;
	// get visibility
	virtual bool GetSubmeshVisibility(int num) = 0;
	// set visibility\unvisibitilty flag for submesh
	virtual void SetSubmeshVisibility(int num, bool visible) = 0;
	// set visibility\unvisibility for array of submeshes
	virtual void SetSubmeshesVisibility(int * arrayptr, int count, bool visibility) = 0;
	// update state
	virtual bool RebuildMesh() = 0;

	virtual void SetActivationDistance(float dist) = 0;
	virtual float GetActivationDistance() = 0;

	// get number of subset vertices
	virtual int GetSubmeshVertCount(int num) = 0;
	// get number of subset indices
	virtual int GetSubmeshIndCount(int num) = 0;
	// make a system copy of positions vertices, pointer should be allocated
	virtual bool GetSubmeshPositions(int num, CVec3 *) = 0;
	// make a system copy of normals, pointer should be allocated
	virtual bool GetSubmeshNormals(int num, CVec3 *) = 0;
	// make a copy of indices 
	virtual bool GetSubmeshIndices(int num, short int *) = 0;
};


class IMeshInfoFriend
{
public:
	void SetVisibleState(bool b, IMeshInfo * pInfo) {
		pInfo->m_bInVisibleList = b;
	}
};

class IRainAreaInfo : public IMeshInfo
{
public:

	virtual void SetDropScale(float xscale, float yscale) = 0;
	virtual void GetDropScale(float& xscale, float& yscale) = 0;

	virtual void SetDropSpeed(float speedMin, float speedMax) = 0;
	virtual void GetDropSpeed(float& speedMin, float& speedMax) = 0;

};
