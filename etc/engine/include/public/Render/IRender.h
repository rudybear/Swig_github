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
#include "Public/Common/Common.h"
#include "Public/Common/Target.h"
#include "Public/Render/IGameRenderObject.h"
#include "Public/Core/IScene.h"
#include "Public/Core/IMeshInfo.h"
#include "Public/Render/IGUIRenderObject.h"
#include "Public/Core/ICore.h"
#include "Public/Render/ILight.h"
#include "Public/Render/IPostProcessingEffect.h"
#include "Public/Render/IHardwareConfig.h"
#include "Public/Render/IMeshBuilder.h"
#include "Public/Render/IShader.h"
#include "Public/Core/IAnimatedMesh.h"
#include "Public/Render/RenderCommon.h"
#include "IPostProcessingEffect.h"
#include "Public/Core/IStatistics.h"
#include "Public/Render/IParticle.h"

#ifdef _WIN32
typedef struct IDirect3DDevice9 *LPDIRECT3DDEVICE9, *PDIRECT3DDEVICE9;
typedef struct IDirect3DBaseTexture9 *LPDIRECT3DBASETEXTURE9, *PDIRECT3DBASETEXTURE9;
#endif

// Scenegraph section

class IMeshInfo;
class IBaseMeshInfo;
class CLight;

enum ERenderer
{
	eRN_D3D9,
	eRN_D3D10,
	eRN_OGL,
	eRN_OGL_ES,
	eRN_FLASH,
};

#ifndef FORCEINLINE
#define FORCEINLINE inline
#endif
// a b g r
FORCEINLINE int Color_RGBA(int r, int g, int b, int a, ERenderer rt)
{
  switch (rt)
  {
	case eRN_D3D9:
	case eRN_D3D10:
		return  COLOR_ARGB(a, r, g, b);
	case eRN_OGL:
		return  COLOR_ARGB(a, b, g, r);
	case eRN_OGL_ES:
	case eRN_FLASH:
	default:
		return  COLOR_RGBA( b, g, r, a);
  }
}
FORCEINLINE int Color_RGBA_Texture(int r, int g, int b, int a, ERenderer rt)
{
#if defined (TARGET_OS_IPHONE)
	return  COLOR_RGBA( r, g, b, a);
#else

	switch (rt)
	{
	case eRN_D3D9:
	case eRN_D3D10:
		return  COLOR_ARGB(a, r, g, b);
	case eRN_OGL:
		return  COLOR_ARGB(a, b, g, r);
	case eRN_OGL_ES:
	case eRN_FLASH:
	default:
		return  COLOR_RGBA( b, g, r, a);
	}
#endif
}

// IOctTree
class IVisAreaTree
{
public:
	virtual ~IVisAreaTree(void) {};
	// Dynamic objects!!!
	virtual void RegisterObject(IMeshInfo *) = 0;
	virtual void UnregisterObject(IMeshInfo *) = 0;
	virtual void MoveObject(IMeshInfo*) = 0;

	// Static objects!!!
	virtual void RegisterStaticObject(IMeshInfo* ) = 0;
	virtual void UnregisterStaticObject(IMeshInfo* ) = 0;

	// Lights
	virtual void RegisterLight(CLight*) = 0;
	virtual void UnregisterLight(CLight*) = 0;
	virtual void MoveLight(CLight*) = 0;

	virtual void SetAABB(const CAABBox& box) = 0;
	virtual const CAABBox& GetAABB() const = 0;
	virtual void SetPartialLimit(float) = 0;

	virtual void Draw(eRenderType type, bool bImmediate, RenderStatistics& stats) = 0;

	virtual void SetNewFrame() = 0;
	virtual void DecideVisibility() = 0;
	virtual void AddToDeleteList(void *) = 0;
	virtual void RemoveFromDeleteList(void *) = 0;

};


// IPortal
class IPortal 
{

public:

	virtual ~IPortal() {};
	virtual void AddPoint (const CVec3& point) = 0;
	virtual bool BuildFrustum(CFrustum& frustum, CVec3& eye) = 0;
	virtual bool BuildCameraFrustum(/*CFrustum& frustum*/) = 0;
	virtual int IsObjectVisible(CAABBox& box) = 0;
	virtual int IsObjectVisible(CSphere& sphere) = 0;
	virtual const CFrustum& GetFrustum() const = 0;
	virtual int GetVisArea1() const = 0;
	virtual int GetVisArea2() const = 0;
};


class ISceneGraph;

class IVisArea
{
public:
	virtual ~IVisArea() {}; 
	virtual int GetVisAreaNum() const = 0;
	virtual size_t GetNumPortals() const = 0;
	virtual size_t AddPortal(IPortal* portal) = 0;
	virtual void RemovePortal(size_t num) = 0;
	virtual IPortal * GetPortal(size_t num) = 0;
	virtual void SetVisAreaTree(IVisAreaTree * pTree ) = 0;
	virtual IVisAreaTree* GetVisAreaTree() = 0;
	virtual void AddVisibleArea(int num) = 0;
	virtual void RemoveVisibleArea(int num)  = 0;
	virtual void BuildVisArea(const ISceneGraph * pSceneGraph ) = 0;
	virtual const char * GetName() = 0 ;
	virtual void SetName(const char * str)  = 0;
	virtual void SetNewFrame() = 0;
	virtual void DrawPass(eRenderType type, RenderStatistics& stat, bool bImmediate ) = 0;
};

class ISceneGraph
{
public:
	//size_t AddVisArea();
	virtual ~ISceneGraph() {};
	virtual IVisArea * GetVisArea(int num) const  = 0;
	virtual size_t AddVisArea(IVisArea *) = 0;
	virtual size_t AddSimpleVisArea() = 0;
	virtual size_t GetMainVisAreaNum() = 0;
	virtual void SetVisAreaAsMain(size_t num)  = 0;
	virtual void SetNewFrame() = 0;
	virtual RenderStatistics DrawPass(eRenderType type, bool bImmediate) = 0;
};


class IBaseMeshInfo;
class IAnimatedMeshInfo;

typedef  Engine2::Vector<CParam> CreationParameters;

struct SDispFormat
{
	int m_Width;
	int m_Height;
	int m_BPP;
};
struct SAAFormat
{
	char szDescr[64];
	int nSamples;
	int nQuality;
	int nAPIType;
};



// Merge flags
// Force merge all meshinfos even with different basemeshes. Remove this flag if you would like 
// create mergerd mesh per unique base mesh
// Deprecated
//#define FORCE_MERGE_ALWAYS            0x00000001L
// Force material indices as identical. Remove this flag if you would like save all original materials
#define MM_USE_DIFFUSE_COLOR			0x00000001L
#define FORCE_MATERIALS_AS_IDENTICAL	0x00000002L
// Taking in account submeshes visibility
#define ALLOW_SUBMESHES_VISIBILITY		0x00000004L

#define CLEAR_COLLISION_INFO			0x00000008L
#define INSERT_INSTANCE_ID				0x00000010L
#define BONE_INSTANCE_ID				0x00000020L

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct MeshMergerInfo {
	MeshMergerInfo() : m_Flags(/*FORCE_MERGE_ALWAYS |*/ FORCE_MATERIALS_AS_IDENTICAL/* | BONE_INSTANCE_ID*/) {}
	// Vector of sourced meshes
	Engine2::Vector<IMeshInfo*> m_vSourceToMerge;
	// Vector of merged meshes
	Engine2::Vector<IMeshInfo*> m_vResultMeshes;
	// Vector of not processed meshes (wrong types, etc)
	Engine2::Vector<size_t> m_vNotProcessedMeshes;
	// Merge behavior
	uint32 m_Flags;
};



struct MeshMergerInstanceInfo {
	CMatrix44 m_Matrix;
	uint32 m_iDiffuseColor;
};

struct MeshMergerInfo2 {
	IMeshInfo * m_pSourceMeshInfo;
	Engine2::Vector<MeshMergerInstanceInfo> m_Instances;
	Engine2::Vector<IMeshInfo*> m_vResultMeshes;
	uint32 m_Flags2;
};



struct MeshAnimBakeInfo {

	enum ErrorCode
	{
		eOk,
		eSourceFileNotFound,
		eDstFileNotCreated,
		eWrongMinLodlevel,
		eProvideNameForSourceAnimation
	};

	struct MeshAnimBakeFrameInfo
	{
		MeshAnimBakeFrameInfo() : m_nAnimId(-1) {}
		// Name OR Id
		Engine2::String m_strAnimName;
		// id
		int m_nAnimId;      
		Engine2::Vector<AnimationParam> m_vFramesInfo;
	};

	MeshAnimBakeInfo() : m_pSourceMeshInfo(0), m_nFrameNumBase(0),m_nMinLODLevel(0), m_bForceToBakeInSingleSubmesh(false) {}
	Engine2::String m_strSourceMeshName;
	IMeshInfo * m_pSourceMeshInfo;
	int m_nFrameNumBase;
	int m_nMinLODLevel;
	bool m_bForceToBakeInSingleSubmesh;
	Engine2::String m_strFramePrefix;
	Engine2::Vector<MeshAnimBakeFrameInfo> m_vAnimInfo;

	Engine2::String m_strResultMeshName;
	IMeshInfo* m_pResultMesh;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Engine2
{

	namespace Render
	{

		class MeshFactory
		{
		public:
			virtual IBaseMeshInfo * CreateBaseMesh(const char * name, const CreationParameters *) = 0;
			virtual IAnimatedMeshInfo * CreateAnimatedMesh(const char * name, const CreationParameters *) = 0;
			virtual IParticleEmitter * CreateParticleEmitter(eParticleType) = 0;

			virtual void MeshMerger(MeshMergerInfo& info) = 0;
			virtual void MeshMerger2(MeshMergerInfo2& info) = 0;
			virtual MeshAnimBakeInfo::ErrorCode BakeAnimations(MeshAnimBakeInfo& info) = 0;

			// TODO!
			virtual void CreateForest() = 0;
		protected:
			MeshFactory() {};
			virtual ~MeshFactory() {};
		};

		class SceneGraphFactory
		{
		public:
			// Its for _STANDARD_ realizations. If you need override classes - do it. 
			virtual IVisAreaTree * CreateOctTree() = 0;
			virtual IVisAreaTree * CreateQuadTree() = 0;
			virtual IVisAreaTree * CreateSimpleVisAreaTree(bool bSimpleCull = false) = 0;
			virtual IVisAreaTree * CreateOctTree(CAABBox& box, float partialLimit) = 0;
			virtual IVisAreaTree * CreateQuadTree(CAABBox& box, float partialLimit) = 0;
			virtual IVisAreaTree * CreateUmbraTree(bool bUseGPUQueries) = 0;
			virtual IPortal  * CreatePortal(int area1, int area2) = 0;
			virtual IVisArea * CreateVisArea() = 0;
			virtual ISceneGraph * GetSceneGraph() = 0;
			virtual void RecreateSceneGraph() = 0;
			virtual void ForceSimpleMainVisAreaTree(bool bSimpleCull = false) = 0;
			virtual void ForceOctTreeAsMainVisArea(CAABBox& box, float partialLimit) = 0;
			virtual void ForceQuadTreeAsMainVisArea(CAABBox& box, float partialLimit) = 0;
			virtual void ForceUmbraTreeAsMainVisArea(bool bUseGPUQueries) = 0;
			virtual void DeleteVisAreaTree(IVisAreaTree * ) = 0;



		protected:
			SceneGraphFactory() {};
			virtual ~SceneGraphFactory() {};

		};

		class IDecalManager 
		{
		public:
			virtual ~IDecalManager() {}
			virtual uint32 SpawnDecal(EngineDecalInfo&)  = 0; // - ID not an index! Id of decal
			virtual bool MoveDecal(uint32 decalID, EngineDecalInfo&) = 0;
			virtual const IMaterial * GetDecalMaterial(uint32 decalID) = 0;
			virtual IMeshInfo * GetDecalMesh(uint32 decalID) = 0;
			virtual bool RemoveDecal(uint32 id)  = 0; // remove decal with ID
			virtual void SetTransparency(uint32 id, float fTransparency) = 0;
			virtual float GetTransparency(uint32 id) = 0;
		};

		class AnimationManager
		{
		public:
			virtual bool PreloadAnimation(const char *) = 0;
			virtual void UnloadAnimation(const char *) = 0; 
		};

		enum EDeviceType {
			eDirectX9,
			eOpenGL_PC,
			eOpenGL_ES_PC,
			eOpenGL_ES_iOS,
			eOpenGL_ES_Android,
			eOpenGL_ES_Emscripten,
			eUnknownDevice
		};

		//! Device dependent information interface
		class IDeviceDependendentInfo
		{
		public:
			//! Return current render type
			virtual EDeviceType GetDeviceType() = 0;
			//! Return count of supported textures formats
			virtual int GetSupportedTextureFormatsCount() = 0;
			//! Return string with supported format
			virtual const char * GetSupportedTextureFormat(int num) = 0;
		};

	}
}

enum EDofParam
{
	EDofP_BlurAmount,
	EDofP_FocusRange,
	EDofP_MaxCoC,
	EDofP_NearBlurDistance,
	EDofP_FarBlurDistance,
	EDofP_FocusDistance,
	EDofP_Num
};
enum EBloomParam
{
	EBloomP_GlowAlphaIntensity,
	EBloomP_GlowIntensity,
  EBloomP_GlowBias,
	EBloomP_HighlightThreshold,
	EBloomP_Radius,
  EBloomP_HighlightOffset,
	EBloomP_Num
};
enum EMotionBlurParam
{
	EMotionBlurP_Intensity,
	EMotionBlurP_Num
};

struct SMemTextureInfo 
{
	// Use Lock instead
	/*uint8 * m_pData;*/
	uint32 m_iWidth, m_iHeight;
	TEXFORMAT m_Format;
};

struct SFontStatistics
{
	uint32 m_atlasHeight;
	uint32 m_atlasWidth;
	uint32 m_textureCount;
	uint32 m_generationTimeMs;
	uint32 m_textures[4];

	SFontStatistics()
	: m_atlasWidth()
	, m_atlasHeight()
	, m_textureCount()
	, m_generationTimeMs()
	{
		m_textures[0] = m_textures[1] = m_textures[2] = m_textures[3] = 0;
	}
};

class IDebugDrawInterface {
public:
	virtual ~IDebugDrawInterface() {}
	virtual void DrawAABB(const CAABBox& box, DWORD color, const char * text) = 0;
	virtual void DrawVector(const CVec3& origin, const CVec3& destination, DWORD color) = 0;
	virtual void DrawImage2D(float x, float y, float width, float height, int nTexture) = 0;
};

typedef void (*TGUICallback)(void);

class IPostProcessingEffect;
class IMeshInfo;

class IRender 
{
public:

#if defined(_WIN32) || defined(_WIN64)
	HMODULE m_pModule;
#endif

	IRender(){};
	virtual ~IRender(){};

	virtual IDebugDrawInterface* GetDebugDrawInterface() = 0;

	//Mesh implementation
	//virtual IMeshInfo * CreateMeshInfo(char * pMeshtype);

	virtual ERenderer GetRendererType() = 0;

	virtual int GetMaxRenderProfile() const = 0;
	//! If set 0 or minus that not force fixed rate
	virtual void SetFixedFrameRate(int newRate) = 0;
	//! Set ICore interface
	virtual void SetApplication(ICore *) = 0;
	//! Add texture by texture name, in another thread with temporary substitution
	virtual TEXNUM AddTexture(const char * tex, bool bStreamed = false, int source = 0, eMeshType  type=eClientMesh)=0;
	//!
	virtual TShaderCombinations *GetShaderCombinations()=0;
	virtual TShaderMask GetShaderMask(const char *szShader)=0;
	virtual int AddEffect(const char * tex, BOOL, TShaderMask mask, BOOL bReload=false)=0;
	virtual void SetTexture(TEXNUM tex, int stage)=0;
	virtual void RemoveTexture(int tex) = 0;
	virtual TEXNUM FindTexture(const char * name,TEXFORMAT format, BUFPOOL pool ) = 0;
	virtual IGameRenderObject *CreateClientGeom(void) = 0;

	//! Setup vertex fog with color, mode (D3DRS_FOGVERTEXMODE, ), userange, with particular density and start\end distances
	virtual void SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density, FLOAT Start, FLOAT End) = 0;
	//! 
	virtual HRESULT Init(WIN_HWND hWnd, DWORD Width, DWORD Height, DWORD Bpp, BOOL bFullscreen, const char *szSplashScreen=NULL, BOOL externalInit = FALSE ) = 0;
	virtual void Close() = 0;
	virtual void Clear() = 0;
	virtual void ClearMeshes() = 0;
	virtual HRESULT RenderFrame() = 0;
	virtual double GetTime() = 0;
	virtual void SetSplashTexture(int nTexture) = 0;

	virtual bool GenerateLightmap(int nRes) = 0;

	virtual int EnumAAFormats(const SDispFormat &rDispFmt, SAAFormat *Formats) = 0;

	virtual void BeginLevel() = 0;
	virtual void EndLevel() = 0;

	virtual void RegisterSceneObject(IScene *) = 0;
	virtual double GetElapsedTime() = 0;
	virtual int GetBPP() = 0;
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
	virtual HRESULT ToggleFullscreen() = 0;
	virtual HRESULT ReCreateScreen(DWORD Width, DWORD Height, DWORD Bpp, BOOL bFullscreen ) = 0;

	// 0 - disablem 1 - full info, 2 - short info
	virtual void SetDebugState(int) = 0;
	virtual void ForceWireframe(BOOL) = 0;
	virtual void SaveScreenshot() = 0;
	virtual void SaveScreenShot(const char * name) = 0;
	virtual void RenderOnlyGUI(bool) = 0;


	// FONTS
	virtual int AddFont(const char* strFontName, DWORD dwHeight, DWORD dwFlags=0L ) = 0;
	virtual int AddFont(const char* strFontName, const char* strFontDesc, DWORD dwSpacing ) = 0;
	virtual void GetFontStatistics(int font, SFontStatistics* outStats) = 0;
	virtual HRESULT DrawText( int font,  FLOAT x, FLOAT y, DWORD dwColor,
		const char* strText, DWORD dwFlags=0L ) = 0;
	virtual HRESULT DrawTextScaled( int num, FLOAT x, FLOAT y, FLOAT z, 
		FLOAT fXScale, FLOAT fYScale, DWORD dwColor, 
		const char* strText, DWORD dwFlags=0L ) = 0;
	virtual void GetTextExtent(int font, const char* text, SIZE* outSize) = 0;
	virtual void GetCharExtent(int font, const char singleCharacter, SIZE* outSize) = 0;
	virtual void SetDebugInfoColor(int r, int g, int b, int a) = 0;

	virtual IGUIRenderObject * CreateGUIObject(void) = 0;


	virtual ILight* AddDynamicLight() = 0;
	virtual void DeleteLight(ILight*) = 0;

	virtual void SetAmbientLight(DWORD) = 0;
	virtual void SetAmbientShadow(DWORD) = 0;

	virtual Engine2::Vector<Engine2::String>& FillResolutionList(int * Curr)  = 0; 
	virtual Engine2::Vector<Engine2::String>& FillProfilesList(int * Curr) = 0; 
	virtual Engine2::Vector<Engine2::String>& FillMultisampleList(int * Curr) = 0; 

	virtual HRESULT AddPostEffect(const char *) = 0;
	virtual BOOL PostEffectActive(const char *) = 0;
	virtual void SetPostEffectState(const char *, eActiveType) = 0;
	virtual TEXNUM AddTexture(const char * texname, int width, int height, int mips, DWORD usage, TEXFORMAT format, BUFPOOL pool, eMeshType type = eClientMesh) = 0;
	virtual HRESULT MergeTextures(const char * source, const char * destination, UINT StartX, UINT StartY) = 0;
	virtual TEXNUM AddTextureFromMemory(const uint8 * data, int pitch, TEXFORMAT srcformat, int srcbits,
		int width, int height, int mips, int dstbits, DWORD usage, TEXFORMAT format, 
		BUFPOOL pool, const char * destname, bool bAsync, TEXNUM replaceTexture, eMeshType type = eClientMesh, int srcMips=1) = 0;

	virtual TEXNUM AddTextureFromMemory2(const char * pData, size_t count, const char * texName, TEXFORMAT expectedFormat, eMeshType type = eClientMesh, bool bOverride=false, bool bForceMips=false) = 0;

	virtual bool StretchRectCopy(TEXNUM dsttex, const RECT* dstrect, TEXNUM srctex, const RECT* srcrect) = 0;

	virtual bool ReloadTexture(TEXNUM) = 0;
	// 		(const uint8 * data, int pitch, int width, int height, int mips, int bits,
	// 		DWORD usage = 0, D3DFORMAT format = D3DFMT_DXT5, D3DPOOL pool = D3DPOOL_MANAGED) = 0;

	virtual int GetTextureWidth(int tex) = 0;
	virtual int GetTextureHeight(int tex) = 0;

	virtual HRESULT Lock(int num, LOCKED_RECT *pLocked, RECT *pRect, DWORD Usage) = 0;
	virtual void Unlock(int) = 0;

	virtual void SetupFog(DWORD Color, DWORD ColorEnd, DWORD ColorWater, FLOAT Start, FLOAT End, FLOAT Density, FLOAT MaxDensity)  = 0;
	virtual void EnableFog(BOOL bEnable) = 0;

	virtual	HRESULT AddCreatePostEffect(PostProcessingEffectPtr& ptr,const char * name, Engine2::Vector<CParam>* params) = 0;
	virtual	void DeletePostEffect(IPostProcessingEffect*) = 0;

	virtual void SetTransform(DWORD, CMatrix44 *) = 0;
	virtual void SetGammaLevel(float gamma, float contrast, float brightness) = 0; 
	virtual const sHardwareConfig * GetHardwareConfiguration() = 0;

	virtual IMeshBuilder * CreateMeshBuilder() = 0;

	virtual void SetMinLOD(int) = 0;
	virtual int GetMinLOD() = 0;

	//virtual void AddDebugInfo(const char * text) = 0;
	virtual void AddDebugInfo(const char * text, ...) = 0;
	virtual void AddDebugInfoExt(int nRow, const char * text, ...) = 0;
	virtual int AddSamplerState(const char * Name) = 0;

	//! Добавляет custom projection matrix. нужно в основном для shadow volume
	virtual int AddProjectionMatrix(float fFOV,float fAspect,float fNear,float fFar) = 0;
	//! Устанавливает 0 матрицу проекции - матрицу проекции камеры
	virtual void SetCameraProjectionMatrix(float fFOV,float fAspect,float fNear,float fFar) = 0;
	virtual CVec3 ProjectPoint(const CVec3& Point) const = 0;
	virtual CVec3 UnprojectPoint(const CVec3& Point) const = 0;
	virtual void SetParam(CParam *) = 0;

	virtual void SetWaterDropsAmount(float fAmount) = 0;
	virtual void SetDofParam(EDofParam eType, float fParam) = 0;
	virtual void SetBloomParam(EBloomParam eType, float fParam) = 0;
	virtual void SetMotionBlurParam(EMotionBlurParam eType, float fParam) = 0;

	virtual ERendererError GetLastError() = 0;

	virtual int GetMaxShadowLights() = 0;
	virtual BOOL FindShader(const char * pShaderName) = 0; 

	virtual IMeshInfo *AddCreateMesh(const CXmlElement * paraminfo) = 0; //Adds created from .X file mesh to Scene->MeshArray
	virtual bool ReloadMesh(const char* name) = 0;
	virtual HRESULT DeleteMesh(IMeshInfo *) = 0;

	//! Model viewer only! Метод для обновления библиотеки шейдеров
	virtual HRESULT ReloadShaderLib() = 0;

	virtual CParam* GetGamma() = 0;

	virtual bool UpdateStats(IStats *pStats) = 0;

	virtual void ShowCursor(BOOL) = 0;

	virtual bool IsFullScreen() = 0;
	virtual bool IsShadowsEnable() = 0;
	virtual bool IsShowFPSEnable() = 0;
	virtual bool IsVSyncEnable() = 0;

	virtual void SetShadowMode(int) = 0;
	virtual void SetShowFPS(bool) = 0;
	virtual void SetVSyncEnable(bool) = 0;
	virtual void SetMultisampeMode(int) = 0;
	virtual const char * GetProfileName(int) = 0;
	virtual int GetCurrentProfile() const = 0;
	virtual HRESULT		PlayVideo(const char *) = 0;
	virtual void StopVideo() = 0;
	virtual BOOL IsVideoPlaying() = 0;

	virtual ETarget GetTarget() = 0;

	virtual IRenderToTextureObject * GetRenderToTextureObject(bool bZBuffer=true) = 0;

	// TEMPORARY HACK FOR THE GUI	// TEMPORARY HACK FOR THE GUI	// TEMPORARY HACK FOR THE GUI
	virtual void SetGUICallback(TGUICallback) = 0;
	virtual void SetGUIInvalidateCallback(TGUICallback) = 0;
	virtual void SetGUIRestoreCallback(TGUICallback) = 0;

	// Set color chart with optional blending
	virtual bool SetColorChart(const TEXNUM tex0, const TEXNUM tex1 = -1, float fBlendFactor = 0.f /* 0..1 */ ) = 0;

	// Load texture to system memory
	virtual TEXNUM LoadTextureToSystemMemory(const char * name, bool bStreamed) = 0;

	virtual HRESULT LockTexture(int num, LOCKED_RECT *pLocked, RECT *pRect, DWORD Usage) = 0;
	virtual void UnlockTexture(int num) = 0;

	virtual bool SaveTextureToFile(TEXNUM num, const char * filename, IMAGE_FILEFORMAT format) = 0;

	virtual const SRenderStatistics* GetStatistics(uint32 nFlags=0) const = 0;

	virtual bool RegisterGraph(SRenderGraph& Graph) = 0;
	virtual int UnregisterGraph(const char *szName) = 0;
	virtual bool EnableGraph(const char *szName, bool bEnable) = 0;

	virtual Engine2::Render::MeshFactory * GetFactory() const= 0;
	virtual Engine2::Render::SceneGraphFactory * GetSceneGraphFactory() const= 0;
	virtual Engine2::Render::IDecalManager * GetDecalManager() const= 0;
	virtual Engine2::Render::IDeviceDependendentInfo * GetDeviceDependendentInfo() const = 0;
	virtual Engine2::Render::AnimationManager * GetAnimationManager() const= 0;
	virtual eAsyncState GetTextureState(TEXNUM num) = 0;
	virtual BOOL GetTextureInfo(TEXNUM num,   SMemTextureInfo& info) = 0;


	virtual IMaterialLib* GetMaterialLib() = 0;

	virtual void AddToBatchCount(uint32) = 0;

	virtual void ForceRenderMask(TShaderMask mask) = 0;
	virtual TShaderMask GetForcedRenderMask() = 0;

	virtual void DumpTextures(Engine2::Vector<Engine2::String> * pDest = 0) = 0;
  virtual void DumpMeshes(Engine2::Vector<Engine2::String> * pDest = 0) = 0;
  virtual void DumpAnimations(Engine2::Vector<Engine2::String> * pDest = 0) = 0;


	virtual void SetRenderViewport(RenderViewport& view) = 0;
	virtual RenderViewport GetRenderViewport() = 0;

	virtual void SetRenderScissors(const RECT& rect ) = 0;
	virtual RECT GetRenderScissors() const = 0;

	virtual void SetTextureStreamingSource(int) = 0;
	virtual int GetTextureStreamingSource() = 0;


	virtual bool IsActive() const = 0;
  
  virtual void TimerActivate() = 0;
  virtual void TimerDeactivate() = 0;
	//=========================================================================================
	// TEMPORARY HACK FOR THE GUI	// TEMPORARY HACK FOR THE GUI	// TEMPORARY HACK FOR THE GUI
	//#ifdef WIN32
#if defined(_WIN32)
	virtual LPDIRECT3DBASETEXTURE9 GetTextureInterface(TEXNUM num) = 0;
	virtual LPDIRECT3DDEVICE9 GetDevice() const = 0;
#endif
};


