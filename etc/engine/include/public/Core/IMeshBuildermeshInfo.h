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
//#include "public\Render\IBSPShader.h"

/*! \addtogroup Mesh_related Group Description
*@{
*/


class IMeshBuilder;
class IMaterialInfo;


class IMeshBuilderMeshInfo : public IMaterialInfo
{
protected:
	BOOL m_bStaticCull;
public:

	IMeshBuilderMeshInfo() : m_bStaticCull(FALSE) {};
	virtual IMeshBuilder * GetMeshBuilder() = 0; 
	virtual HRESULT AddBatch(int faceStart, int faceCount, int vertexStart, int vertexCount) = 0;
  virtual HRESULT ChangeBatch(int faceStart, int faceCount, int vertexStart, int vertexCount) = 0;
  virtual void ClearBatches() = 0;
  virtual HRESULT FillIB(short int * pIndices, int NumIndices) = 0;
	void SetStaticCull(BOOL b) { m_bStaticCull = b;};

	virtual HRESULT AddLODBatch(uint32 lod, uint32 fs, uint32 fc, uint32 vs, uint32 vc) = 0;
	// Return LODs count
	virtual uint32 GetLODCount() = 0;
	// Set LOD distance
	virtual void SetLODDistance(uint32 lod, float distance) = 0;
	// Get LOD distance
	virtual float GetLODDistance(uint32 lod) = 0;

	virtual void SetVisibleMaterialTextureFullDesc(uint32 stage, uint32 nexTexId, const char * nexTex) = 0;
  virtual void SetVisibleMaterialTexture(uint32 stage, const char * nexTex) = 0;

 	virtual MaxMeshMaterial * GetMaxMaterial() const = 0;

private:
  //! Override material texture
  virtual void SetVisibleMaterialTexture(uint32 mat, uint32 stage, uint32 nexTexId, const char * nexTex) = 0;
  //! Override material texture
  virtual void SetVisibleMaterialTexture(uint32 mat, uint32 stage, const char * nexTex) = 0;

};

class ICallbackDrawer
{
public:
	virtual void Draw(int iBegin, int iSize, IMeshBuilder * pMeshBuilder, bool b2D) = 0;//
	virtual void PreDrawUpdate() {}
	virtual int GetSize() = 0;
};


class IDynamicMeshBuilderMeshInfo : public IMaterialInfo
{
protected:
	BOOL m_bStaticCull;
public:
	IDynamicMeshBuilderMeshInfo() : m_bStaticCull(FALSE) {};
	virtual IMeshBuilder * GetMeshBuilder() = 0; 
	void SetStaticCull(BOOL b) { m_bStaticCull = b;};
	virtual HRESULT AddDrawer(ICallbackDrawer * pDrawer/*, int iCount*/) = 0;
	virtual HRESULT DeleteDrawer(ICallbackDrawer * pDrawer) = 0;
	virtual void SetVisibleMaterialTexture(uint32 stage, const char * nexTex) = 0;
  virtual MaxMeshMaterial * GetMaxMaterial() const = 0;
  virtual void UseTriangles(bool) = 0;
  virtual void SetVisibleDistance(float fDist) = 0;
  virtual float GetVisibleDistance() = 0;
};

