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

enum eTerrainLayerType
{
	eMainLayer,
	eDetailLayer,
	eMaskLayer
};

#define TYPE_STANDARD  0
#define TYPE_REDUNDANT 1
#define TYPE_FLAT      2
#define TYPE_ERROR     4
#define TYPE_FFPVERTEX 8

#define TYPE_HAS_USERINFO  0x20
#define USERINFO_MASK     ~0x20

#define TYPE_HAS_MASK     0x40
#define MASK_MASK      ~0x40

#define TYPE_HAS_FLAT_WATER  0x80
#define WATER_FLAT_MASK      0x7F

#define TYPE_HAS_WATER_PATCH  0x10
#define WATER_PATCH_MASK      0x0F

#define MAX_LOD 4

struct TerrainTextureInfo
{
	const char * m_sTextureName;
	float m_fScale;
	int m_LayerType;
};

struct SIMPLE_PATCH_VERTEX_1 {
  //DWORD p;
  CVec3 p;
  DWORD n;//
};

struct SIMPLE_PATCH_VERTEX_2 : public SIMPLE_PATCH_VERTEX_1
{
  CVec2 t;
};


struct CommonPatchInfo
{
	CommonPatchInfo() {
		memset(m_WaterMaterial, 0, 32);
		memset(m_PatchMaterialName, 0, 32);
		memset(m_PatchSingleMaterialName, 0, 32);
		memset(m_BakedPatchEffectName, 0, 32);
	}
  int m_iStartX, m_iStartY;
  float m_WaterLevel;
  char m_Type;	
  float minY, maxY;
  float m_Errors[MAX_LOD];
  char m_WaterMaterial[32];
	char m_PatchMaterialName[32];
	char m_PatchSingleMaterialName[32];
	char m_BakedPatchEffectName[32]; // - .FX FILE!!!
  int m_iDetailShaderIndex;
  int m_iBaseShaderIndex;
  int m_iBigShaderIndex;
};

enum eMaskFormat {
  eRGBA_to_RGBA,
  eRGBA_to_DXT5,
  eDXT5_to_DXT5

};


struct TerrTerrainInfo
{

  char m_strLightMapPath[128];

  int m_iWidth;
  int m_iHeight;
  float m_fScale;

  short int m_iHeightp;
  short int m_iWidthp;

  short int m_iBaseHeight;
  short int m_iHeightScale;
  short int m_iPatchSize;

  float m_fOceanLevel;

  float m_fDetailScale1;
  float m_fDetailScale2;
  float m_fDetailScale3;

  float m_fDetailMicroScale1;
  float m_fDetailMicroScale2;
  float m_fDetailMicroScale3;

  eMaskFormat m_eMaskFormat; // The same as D3DFORMAT
  int m_nMaskMips;
};

//! New raw-data-patch format
// struct CommonPatchInfo
// int texNum; - number of textures
// If TYPE_REDUNDANT
// -- repeat texNum times --
// int texLentgth; - texture name lenght
// char [texLength]; - texture name
// ELSE TYPE_STANDARD
// -- repeat texNum times --
// int texIndex;
// -- repeat texNum times --
// 


struct PatchMaskInfo {
  int m_iSize;
  int m_iWidth;
  int m_iHeight;
};

//#define  PACK_HEIGHT_TO_DWORD(x, y, z, w) ( (x << 24) + (y << 16) + (z << 8) + (uint8)w)
#define  PACK_NORMAL_TO_DWORD(A) ( ((((uint32)(A.z * 255.0f)) & 0xFF ) << 16) + ((((uint32)(A.y * 255.0f)) & 0xFF ) << 8) + ((uint32)(A.x * 255.0f) & 0xFF ))
#define UNPACK_NORMAL_FROM_DWORD(A) CVec3(float((A>>16)&0xFF) / 255.0f, float((A>>8)&0xFF) / 255.0f, float((A>>0)&0xFF) / 255.0f);



class ITerrainInfo : public IMeshInfo
{
public:

  virtual void SetAsMainVisArea() = 0;
//	virtual bool TestRayIntersection(const CSegment& nRay, CVec3& vecIntersection, CVec3& vecNormal) = 0;
	virtual bool GetHeight(const CVec3& nPoint, CVec3& nClosest, CVec3 * pNormal = 0, const bool bInterpolateNormal = false) const = 0;
	virtual CAABBox * GetAABB() = 0;


  //virtual float GetVisibility() = 0;
  //virtual void SetVisibility(float ) = 0;
	// Debug interface
	virtual void SetDebugMode(bool) = 0;
	// get
	virtual int GetWidthPatches() = 0;
	virtual int GetHeightPatches() = 0;
	// forces load path into memory. return -1 if failed.
	virtual uint32 ForceLoadPatch(int, int) = 0;
	// get number of texture layers
	virtual uint32 GetPatchTextureCount(uint32) const = 0;

	virtual bool GetPatchTextureInfo (uint32 patch, uint32 layer, TerrainTextureInfo& info) const = 0;

	virtual bool SetPatchTextureInfo(uint32 patch, uint32 layer, const char * name) = 0;
	// get patch info
	virtual uint32 GetPatchWidth() = 0;
	virtual uint32 GetPatchHeight() = 0;
	// get geometry
	virtual bool GetPatchHeightmap(uint32 patch, float * heightMap) = 0;
	// set geometry
	virtual bool SetPatchHeightmap(uint32 patch, float * heightMap) = 0;

	virtual bool SaveTerrain(const char *) = 0;

	virtual eAsyncState GetPatchState(int, int) = 0;

	virtual const TPatchNotificationVector& GetPatchesNotification() = 0;

  virtual void UpdatePatchManually(uint32 patch, uint8 * data, uint32 size) = 0;

  virtual void UpdatePatchInfo(uint32 patch, uint32 offset, uint32 size) = 0;
  virtual void ReloadGeneralInfo() = 0;


  virtual void SetManualStatesVectorCleanup(bool) = 0;
  virtual void ClearStatesVector() = 0;
	virtual uint8 * AllocateMemoryForUpdate(size_t size) = 0;

	virtual void ClearMemoryForUpdate(uint8 * ptr) = 0;

  virtual bool IsLoadingComplete() = 0;

  virtual void ForceLoadAllVisiblePatches() = 0;


  // visibility stuff
  virtual void SetVisibilityDistance(float) = 0;
  virtual float GetVisibilityDistance() = 0;

  virtual void SetLoadingDistance(float) = 0;
  virtual float GetLoadingDistance() = 0;

  virtual void SetUnLoadingDistance(float) = 0;
  virtual float GetUnLoadingDistance() = 0;

  virtual void SetVisibleBounds(float min_x, float min_z, float max_x, float max_z) = 0;
  virtual void GetVisibleBounds(float* min_x, float* min_z, float* max_x, float* max_z) = 0;

};
