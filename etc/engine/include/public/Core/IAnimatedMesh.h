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
#include "IMeshInfo.h"
#include "../Render/ISkeleton.h"


/*! \addtogroup Mesh_related
*@{
*/



class ISkeleton;

// structure for animation info
struct AnimationParam
{
	AnimationParam() : m_fSpeed(1.0f), m_fWeight(1.0f), m_fCurrentTime(0.0f), m_iFirstAffectedBone(-1),
												m_iOnlyAffectedBone(-1), m_nLayer(0), m_bGameUpdate(false), m_bLooped(false),
												m_bAdditive(false),  m_bReverse(false), m_bStopAtTheEnd(false), m_bAdditive2(false),
												m_bDropToIdle(false) {};
	float m_fSpeed;
	float m_fWeight;
	float m_fCurrentTime;
	int m_iFirstAffectedBone;
	int m_iOnlyAffectedBone;
	uint32 m_nLayer;
	bool m_bGameUpdate : 1;
	bool m_bLooped : 1;
	bool m_bAdditive : 1;
	bool m_bReverse : 1;
	bool m_bStopAtTheEnd : 1;
	bool m_bAdditive2 : 1;
	bool m_bDropToIdle : 1;
};

struct UVAnimationParam
{
	UVAnimationParam() 
		: m_fSpeed(1.0f)
		, m_bGameUpdate(false)
		, m_bLooped(true) 
	{

	}

	float m_fSpeed;
	bool m_bGameUpdate : 1;
	bool m_bLooped : 1;
};

enum eMeshCreation {
	eUnknown,
	eLoaded,
	eInstanced
};

struct LightmapInfo {
	CVec2 m_vecLightmapWorldCoord;
	CVec2 m_vecLightmapSizeInWorld;
};

struct PreloadInfo {
	Engine2::Vector<Engine2::String> m_vecTextures;
};


class IBaseMeshInfo : public IMaterialInfo, public IXRefInfoMesh
{
public:

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  interface for submeshes
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// return number of submeshes
	virtual int GetNumSubmeshes() = 0;
	// return the name of submesh
	virtual const char* GetSubmeshName(int num) = 0;
	// get number from name
	virtual int GetSubmeshFromName(const char *) = 0;
	// get visibility
	virtual bool GetSubmeshVisibility(int num) = 0;
	// get true for fat\thin submesh
	virtual bool GetSubmeshIsFatThin(int num) = 0;
	//   
	virtual float GetSubmeshFatThinBalance(int num) = 0;
	// set visibility\unvisibitilty flag for submesh
	virtual void SetSubmeshFatThinBalance(int num, float balance) = 0;

	// set visibility\unvisibitilty flag for submesh
	virtual void SetSubmeshVisibility(int num, bool visible) = 0;
	// set visibility\unvisibility for array of submeshes
	virtual void SetSubmeshesVisibility(int * arrayptr, int count, bool visibility) = 0;
	// Analyze resources that required for the regular RebuildMesh.
	virtual bool PrebuildMesh(PreloadInfo& info) = 0;
	// Rebuild mesh. Builds actual GPU geometry and actual renderobject for render.
	virtual bool RebuildMesh(bool bAsync = false) = 0;
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
	// make a copy of triangles materials
	virtual bool GetSubmeshMaterialsForTriangles(int num, short int *) = 0;

	virtual bool IsSubmeshMaxMaterialUsed(int num, int mat) = 0;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// LODs interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual uint32 GetNumLods() = 0;
	//! Setr active access LOD index
	virtual void SetAccessibleLod(int32) = 0;
	//! Return single entry LOD switching distance
	virtual float GetLodDistance(int32) = 0;
	//! Set single entry LOD switching distance
	virtual void SetLodDistance(int32, float) = 0;
	//! Return current visible LOD
	virtual uint32 GetVisibleLod() = 0;
	//! Set dual point switch LOD distances
	virtual void SetLodDistances(int32 lod, float nearSwitch, float farSwitch) = 0;
	//! Return dual point switch LOD distances
	virtual void GetLodDistances(int32 lod, float& nearSwitch, float& farSwitch) = 0;
	//! Force to use only particular lod, if set -1 then restore old behavior
	virtual void ForceRenderingLod(int32) = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Collision interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool TestRayIntersectionSubmesh(int num, const CSegment& nRay, CVec3& vecIntersection, CVec3& vecNormal) = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Additional materials interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual uint32 GetNumMaterials() = 0; // Это для мешей - вернуть ОБЩЕЕ количество материалов. Для доступа к локальным наомер надо использовать GetVisibleMaterialsNum()!!!
	virtual uint32 GetVisibleGlobalMaterialNum(uint32 visibleNum) = 0; // Возвращает глобальный номер материала по локальному
	virtual uint32 GetVisibleFromGlobalMaterialNum(uint32 globalNum) = 0;// Возвращает локальный номер для активного лода по глобальному

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Additional max - materials interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual uint32 GetMaxMaterialsCount() const = 0;
	virtual const MaxMeshMaterial * GetMaxMaterial(uint32 num) const = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Hierarchy interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual ISkeleton * GetSkeleton() { return 0; }
	virtual IBaseSkeleton * GetBaseSkeleton() = 0;
	// deprecate old material accessors

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Root animations interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! Load root animation and return animation id
	virtual int LoadAnimation (const char *) = 0;
	//! 
	virtual int CreateAnimationCopy (const char *) = 0;
	//! 
	virtual int GetAnimationSize (const char *) = 0;
	//! Unload all root animations
	virtual void UnloadAnimations() = 0;
	//! Unload particular animation
	virtual void UnloadAnimation(uint32) = 0;
	//! Satrt root animation
	virtual void StartAnimation(uint32 id, AnimationParam& params) = 0;
	//! Stop root animation
	virtual void StopAnimation(uint32 id) = 0;
	//! Return number of root animations
	virtual int GetNumAnimations() = 0;
	//! Get root animations name
	virtual const char * GetAnimationName(uint32) = 0;
	//! Get root animation ID
	virtual int GetAnimationID(const char *) = 0;
	//! Get root animation ID
	virtual bool GetParams(uint32 id, AnimationParam&) = 0;
	//! Get root animation ID
	virtual bool UpdateParams(uint32 id, AnimationParam& param ) = 0;
	virtual float GetStartTime(uint32 id) = 0;
	virtual float GetEndTime(uint32 id) = 0;
	//! Set root bone for animation update
	virtual void SetRootBone(int ) = 0;


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// UVAnim interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual int LoadUVAnimation (const char *) = 0;
	virtual void UnloadUVAnimation(uint32) = 0;
	virtual int GetNumUVAnimations() = 0;
	virtual const char * GetUVAnimationName(uint32) = 0;
	virtual int GetUVAnimationID(const char *) = 0;
	virtual void StartUVAnimation(uint32 id, UVAnimationParam& params) = 0;
	virtual void StopUVAnimation(uint32 id) = 0;
	virtual bool GetParams(uint32 id, UVAnimationParam&) = 0;
	virtual bool UpdateParams(uint32 id, UVAnimationParam& param ) = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// XRef data interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual size_t GetXRefsCount() = 0;
	virtual IBaseMeshInfo * GetXRef(int) = 0;

	virtual eMeshCreation GetMeshCreation() = 0;

	virtual void SetTransparencyState(bool) = 0;
	virtual bool GetTransparencyState() const = 0;

	virtual void SetTransparency(float ) = 0;
	virtual float GetTransparency() const = 0;
	virtual void SetAlphaTest(float f) = 0;
	virtual float GetAlphaTest() const = 0;

	//
	virtual void SetLightmapSource( LightmapInfo& collisionTexCoordinates, TEXNUM lightmapTexture) = 0;
	//virtual void WriteToCache() {}

	virtual void SetImposterScale(float) = 0;
	virtual float GetImposterScale() = 0;

	virtual const CMatrix44 GetRootMatrix() = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Mesh interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual bool IsLastFrameVisible() const = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Instancing interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void SetInstancingPositions(const Engine2::Vector<CVec4>& positions) = 0;
};


class IAnimMeshInfo : public IBaseMeshInfo
{
public:

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Animation interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual int LoadAnimationSet(const char *) = 0;
	virtual int LoadAnimation (const char *) = 0;
	virtual void UnloadAnimation(uint32) = 0;
	virtual void UnloadAnimations() = 0;


	virtual int GetNumAnimations() = 0;
	virtual const char * GetAnimationName(uint32) = 0;
	virtual int GetAnimationID(const char *) = 0;


	virtual void StartAnimation(uint32 id, AnimationParam& params) = 0;
	virtual void DetachBoneFromAnimation(uint32 animationID, uint32 boneID) = 0;
	virtual void AttachBoneToAnimation(uint32 animationID, uint32 boneID) = 0;
	virtual bool IsBoneAttachedToAnimation(uint32 animationID, uint32 boneID) = 0;
	virtual void StopAnimation(uint32 id) = 0;
	virtual int GetAnimationSize (const char *) = 0;

	virtual bool GetParams(uint32 id, AnimationParam&) = 0;
	virtual bool UpdateParams(uint32 id, AnimationParam& param ) = 0;

	virtual ISkeleton * GetSkeleton() = 0;

	virtual bool Update(uint32 boneId = -1) = 0;

	virtual void SetTimeGameUpdate(uint32 id, bool) = 0;

	virtual float GetStartTime(uint32 id) = 0;
	virtual float GetEndTime(uint32 id) = 0;
	virtual void SetCurrentTrackTime(uint32 id, float) = 0;
	virtual float GetCurrentTrackTime(uint32 id) = 0;

	virtual float GetCurrentWeight(uint32 id) = 0;
	virtual void SetCurrentWeight(uint32, float) = 0;
	virtual uint32 GetGlobalIDFromLocalID(uint32) = 0; // i hate it. Why we need use local id's at all? For state machine we don't need this! I want deprecate this GunNumAnimationsStuff!

	virtual void SetBindPose() = 0;
	virtual bool IsAnimationPlay(uint32) = 0;
	virtual bool IsAnyAnimationPlay() = 0;

	virtual void SetMaxMipLevel(int nMaxMip) = 0;
	virtual int GetMaxMipLevel() = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// LOD interface
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual uint32 GetNumLods() = 0;
	virtual void SetAccessibleLod(int32) = 0;
	virtual float GetLodDistance(int32) = 0;
	virtual void SetLodDistance(int32, float) = 0;
	virtual uint32 GetActiveBonesCount() = 0;
	// return frame multiplier for LODs
	virtual uint32 GetLodUpdateMult(int32 lod) = 0;
	// set frame multiplier for LODs
	virtual void SetLodUpdateMult(int32 lod, uint32 mult) = 0;


	virtual bool TestRayIntersectionSubmesh(int num, const CSegment& nRay, CVec3& vecIntersection, CVec3& vecSkinnedIntersection, CVec3& vecNormal) = 0;


	virtual void SetUniformScale(float) = 0;

	//virtual void SetLightmapSource(LightmapInfo& lightMapInfo, TEXNUM lightmapTexture) = 0; // set -1 in lightmap texture for disabling lightmaps
};


