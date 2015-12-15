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

#include "Public/Common/Param.h"
#include "Public/Render/RenderCommon.h"
#include "Public/Render/IPostProcessingEffect.h"
#include "Public/Render/IEffectsLib.h"

class CParam;

typedef Engine2::Vector<CParam> EffectParam;


// Maximum textures per pass
#define MAX_TEXTURES_PER_PASS 16

struct TexturePassInfo {
  TEXNUM m_Textures[MAX_TEXTURES_PER_PASS];
};



struct MaxMaterialTexInfo
{
  Engine2::String m_sName;
  Engine2::String m_sTexName;
  int m_iSlot; // This is MAXTableSlotMap
};


struct MaxMeshMaterial
{
  int m_iID;

  Engine2::String m_sName;
  Engine2::String m_sClass;

  CVec3 m_Diffuse;
  CVec3 m_Specular;
  CVec3 m_Ambient;

  float m_fGlossiness;
  float m_fOpacity;
  float m_fSpecularLevel;

  Engine2::Vector<MaxMaterialTexInfo> m_Textures;
};

// Add a proper text in 
enum eTextureType {
	eTexture_Diffuse0,
	eTexture_Diffuse1,
	eTexture_Diffuse2,
	eTexture_Diffuse3,
	eTexture_NormalMap,
  eTexture_NormalMapWithGloss,
  eTexture_ReflectionMap,
  eTexture_RefractionMap,
  eTexture_ScreenCopyMap,
  eTexture_ShadowMap,
  eTexture_EnvMap,
	eTexture_LightMap,
	eTexture_OpacityMap,
  eTexture_WaterNormal,
  eTexture_WaterReflection,
  eTexture_EnvMap2,
  eTexture_EnvReflection,

  eTexture_Last
};

struct TextureInfo {
  TEXNUM m_iTexture;
  eTextureType m_eTextureType : 8;
  int   m_iMinProfile : 8;
	TextureInfo():
		m_iTexture(-1),
		m_eTextureType(eTexture_Last),
    m_iMinProfile(100)
	{
	}
	TextureInfo(TEXNUM iTexture, eTextureType textureType, int minProfile):
		m_iTexture(iTexture),
		m_eTextureType(textureType),
    m_iMinProfile(minProfile)
	{
	}
};

struct ShaderSettings 
{
	enum {LAST_BLEND_GROUP = 127};
	enum {MAX_SHADOW_LIGHTS = 4};
	Engine2::Vector<TextureInfo> m_iTextures; //!
  Engine2::Vector<Engine2::String> m_sTexturesNames; //! Used only in pecche material!!!
	//Engine2::Vector<Engine2::String> m_sTextureNames; //!
	short int m_iFFShader; //! Сombo
	eCULL m_iCull; //!Сombo
	char m_iLightmapStage;
	char m_iRefractmapStage;	
	char m_iReflectmapStage;
	char m_iScreenCopyStage;
	char m_iBumpMapStage;
  char m_iShadowStages[MAX_SHADOW_LIGHTS];
	char m_iShadowMapCount;
  signed char m_iMaxMipLevel;
	eCMPFUNC m_iAlphaFunc; //! Сombo
//	BOOL m_bUseAlphaFunc;  
	BYTE m_iAlphaVal; //! Edit
	eBLEND m_iBlendSrcFunc; //! Сombo
	eBLEND m_iBlendDstFunc; //! Сombo
	char m_iBlendGroup;
	Engine2::String m_sEffect; //! Edit + 
	Engine2::String m_sTechnique; //! Edit + 
  int m_iEffectNum;
//  UINT m_iTechniqueHandle;
	BOOL m_bEffectIntegrated; //! Check
	eDEPTHSTATE m_iDepthState; //! Сombo
	eCMPFUNC m_iDepthFunc; //! Сombo
	float m_fZBias; //! Edit
	float m_fSlopeScaleBias; //
//	BOOL m_bCustomFFShader;
	eShaderType m_eRPType; //! Сombo
	Engine2::String m_sName; // Название материала
	Engine2::Vector<CParam> m_Params; // Список параметров для редактирования
	eVertexTypes m_eShaderNeedVertexFormat;
	short int m_iSamplerState;

	char m_bUseLight : 1; //! Check
	char m_bUseReadyLightArray : 1;
	char m_bUsed : 1;
	char m_bAcceptmark : 1;
	char m_bAutoBind : 1; // Automatically binds techniques etc
	char m_bUseLightmap : 1;
	char m_bUseReflectmap : 1; 
	char m_bUseRefractmap : 1; 
	char m_bUseEnvmap : 1; 
	char m_bUseScreenCopy : 1;
	char m_bUseShadows : 1;
	char m_bUniqueRP : 1;
	char m_bUseClipPlanes : 1;
	char m_bUseInstancing : 1;
  //char m_bIgnoreProfiles : 1;

	ShaderSettings()
	{
//    m_iTechniqueHandle = -1;
//    m_iEffectNum = -1;
		m_eShaderNeedVertexFormat = eVERTEX_PNT1;
		m_iCull = CULL_CW;
		m_bUseLightmap = FALSE;
		m_bUseReflectmap = FALSE; 
		m_bUseRefractmap = FALSE;
		m_bUseScreenCopy = FALSE;
		m_bUseShadows = FALSE;
		m_bUseEnvmap = FALSE;
    //m_bIgnoreProfiles = FALSE;
		m_bEffectIntegrated = TRUE;
		m_iFFShader = 0;
    m_bAcceptmark = TRUE;
		m_iLightmapStage = 1;
		for (int i =0;i < MAX_SHADOW_LIGHTS; ++i)
			m_iShadowStages[i]= -1;	
    m_iRefractmapStage = -1;	
    m_iReflectmapStage= -1;	
    m_iScreenCopyStage= -1;	
		m_iBumpMapStage = -1;
		m_iShadowMapCount = 0;
		m_iAlphaFunc = CMP_ALWAYS;
		m_iAlphaVal = 0;
		m_iDepthState = DEPTH_ZZWENABLE;
		m_iDepthFunc = CMP_LESSEQUAL;
		m_fZBias = 0.0f;
		m_fSlopeScaleBias = 0.0f;
		m_iBlendSrcFunc = BLEND_ZERO;
		m_iBlendDstFunc = BLEND_ONE;
		m_iBlendGroup = 0;
		m_eRPType = eBase;
		m_bUniqueRP = FALSE;
		m_bUseLight = TRUE;
		m_bUsed = FALSE;
		//m_pReflectEffect = 0;
		//m_pRefractEffect = 0;
		//m_pScreenCopyEffect = 0;
		//m_pShadowEffect = 0;
		m_iSamplerState = 0;
		m_bUseReadyLightArray = true;
		m_bUseClipPlanes = 1;
		m_bAutoBind = false;
		m_bUseInstancing = true;
	};

};


//typedef ShaderInfo ShaderSettings;


// Render pass structure
struct ScenePass {

  void Enable(bool b) {
    m_bEnabled = b;
  }

  bool IsEnabled() const {
    return m_bEnabled;
  }

  const ShaderSettings& GetShaderSettings() const {
    return m_Settings;
  }

  // Please use IsRenderTypeInMask or GetFirstTypeInMask for checking mask
  TRenderTypeMask GetRenderMask() const {
    return m_iMask;
  }

  void SetRenderType(eRenderType type) {
    m_iMask |= 1 << (int)type;
  }

  void RemoveRenderType(eRenderType type) {
    m_iMask &= !(1 << (int)type);
  }

  ShaderSettings m_Settings;
private:
  //  Engine2::Vector<eRenderType> 
  bool m_bEnabled;
  TRenderTypeMask m_iMask;
};


#define MATERIAL_SHADOWCASTER      0x00000001
#define MATERIAL_SHADOWRECEIVER    0x00000002
//#define MATERIAL_

struct IMaterialLib;

struct IMaterial : public IRefSmartPtr {


  IMaterial() : m_iMaterialID(0) {}

  virtual ~IMaterial() {}
  //! 
  virtual const char * GetName() const = 0;
  //! 
  virtual unsigned int GetScenePassesCount() const  = 0;
  //!
  virtual ScenePass* GetScenePass(unsigned int num) const = 0;
  //! Creation on fly 
  virtual void AddScenePass(ScenePass * pass, eRenderType type) = 0;

  int GetMaterialID() const {
    return m_iMaterialID;
  }

  virtual TShaderMask GetMaterialMask() const = 0;

  virtual void TryToSetRenderMask(TShaderMask& mask) const = 0;

  // Please DO NOT use this method!
  virtual void ForceSetRenderMask(TShaderMask mask) const = 0;

  virtual uint32 GetMaterialParamCount() const = 0;
  //! Get specified CParam from material and index
  virtual CParam * GetMaterialParam(uint32 param) const = 0;
  //! Add a new parameter to the material
  virtual bool AddMaterialParam(CParam& param) const = 0;
	//! Add a new pointer to parameter to the material
	virtual bool AddMaterialParamPtr(CParam* param) const = 0;

  //virtual void FillAllParametersFromShader(EffectParam&) = 0;

  virtual void SetDesiredVertexFormat(eVertexTypes) = 0;
  //! Get textures count for specified material
  virtual uint32 GetMaterialTextures() const = 0;
  //! Get texture from material and stage
  virtual TEXNUM GetMaterialTexture(uint32 stage) const = 0;
  //! Get texture name from 
  virtual const char * GetMaterialTextureName(uint32 stage) const = 0;
  //! Override material texture
  virtual void SetMaterialTexture(uint32 stage, uint32 nexTexId, const char * nexTex) const = 0;
  //! Override material texture
  virtual void SetMaterialTexture(uint32 stage, const char * nexTex) const= 0;

  //virtual Engine2::String GetMaterialMainTechniqueAnnotation() const = 0;
//private:
//  friend struct IMaterialLib;
  int m_iMaterialID;

};

struct MaterialInfo {
  eVertexTypes m_DesiredVertexFormat;
  Engine2::Vector<eTextureType> m_iDesiredTextureSlots;
};

struct MaterialTemplateAnalyzeInfo {
  Engine2::Vector<Engine2::String> vt[eVERTEX_LAST_INST];
};

struct MaxMeshMaterial;

#define MATERIAL_NOT_LOAD_TEXTURES          0x1
#define MATERIAL_SUPPRESS_ERRORS            0x2
#define MATERIAL_FROM_PRECACHE		          0x4
#define MATERIAL_NO_EFFECTS   		          0x8
#define MATERIAL_USE_DEFAULT_TEMPLATE   	 0x10
#define MATERIAL_PRECACHE (MATERIAL_NOT_LOAD_TEXTURES|MATERIAL_SUPPRESS_ERRORS|MATERIAL_FROM_PRECACHE)


struct IMaterialLib {
  //! Load material by name

	virtual ~IMaterialLib() {};
  //! Return number of material templates
  virtual size_t GetMaterialTemplatesCount() = 0;
  //!
  virtual const char * GetMaterialTemplateName(uint32 ) = 0;

  virtual void AnalyzeMaterialTemplates(MaterialTemplateAnalyzeInfo& info) = 0;
  virtual IMaterial * LoadMaterial(const char * name, const char * alias, MaxMeshMaterial * maxMat, eMeshType type, DWORD flags = 0) = 0;
  //! 
  virtual IMaterial * DuplicateMaterial(const char * srcname, const char * dupname, bool bCopyTextures = false, bool bCopyParameters = false) = 0;
  //!
  virtual IMaterial * DuplicateMaterial(const IMaterial * srcmat, const char * dupname, bool bCopyTextures = false, bool bCopyParameters= false) = 0;

	virtual IMaterial * CopyMaterialTextures(const IMaterial * srcmat, IMaterial * destmat) = 0;
  //!
  virtual IMaterial * CreateMaterial(const char * name) = 0;

  virtual void Reload() = 0;

  virtual bool GetMaterialInfo(const char * name, MaterialInfo& info) = 0;

  virtual eVertexTypes GetMaterialVertexType(const char * name, const char * alias, MaxMeshMaterial * maxMat, int flag, int& minProfile) = 0;
};


//!-----------------------------------------------------------------------------
//! Name: class IShader
//! Desc: Интерфейс всех шейдеров - FFP, SM и FX
//!		  
//!-----------------------------------------------------------------------------


class IShader
{
public:
	
	//! Метод инициализации 
	virtual void Init() = 0; 
	//! Установка шейдера 
	virtual void SetShader() = 0;
	//! Завершить работу с этим шейдером. Здесь можно восстанавливать уникальные параметры шейдера  в дефолтное состояние
	virtual void EndShader() = 0;
	//! Установка текущего прохода. 
	virtual void SetPass(unsigned int) = 0;
  //! Begin shader rendering
  virtual void Begin( UINT* passes, UINT dwFlags) = 0;
	//! Завершить проход
	virtual void EndPass() = 0; 
	//! Установка уникальных параметров для текущего вызова. Нужно для эффектов
	virtual void CommitChanges() = 0;
	//! Передача параметра
	virtual HRESULT SetParam(CParam *)=0;
	//! Передача параметра, значения копируются
	virtual HRESULT SetConstParam(const CParam *)=0;
	//! Удаление параметра
	virtual HRESULT DeleteParam(CParam *)=0;
	//! Удаление всех параметров
	virtual HRESULT DeleteAllParam()=0;
	//! Вернуть параметр по имени
	virtual CParam * GetParamByName(const char *) = 0;
	//! Проверить - нужен ли такой параметр. Метод МЕНЯЕТ значение m_sHandle в CParam!!!
	virtual bool ValidateParam(CParam *) = 0;
	//! Материал прозрачный?
	const BOOL IsTransparent() const 
	{
		return m_bTransparent;
	}
	//! Функция сравнения шейдеров 
	virtual bool CompareShaders(IShader *) = 0;

	// dtor
	virtual ~IShader() {};

	//! Установить прозрачность материала шейдера
	void SetTransparent(BOOL b)
	{
		m_bTransparent = b;
	}

  //virtual const BOOL IsAlphatest() const = 0;
  //{
  //  return m_bAlphatest;
  //}

  //void SetAlphatest(BOOL b)
  //{
  //  m_bAlphatest = b;
  //}

	//! Вернуть тип шейдера
	const eShaderType GetType() const
	{
		return m_eType;
	}

	//! Вернуть число проходов
	virtual unsigned int GetPasses() = 0;

	void SetWorldMatrix(CMatrix44*  mat)
	{
		m_pWorld = mat;
	}

	// IDTag  - это int с номером шейдера. Исользуется для оптимизации батчей
	const int GetIDTag() const
	{
		return m_iIDTag;
	}

	//! Вернуть группу блендинга

	const int GetBlendGroup() const 
	{
		return m_iBlendGroup;
	}

	//! Установить группу блендинга
	void SetBlendGroup(int b)
	{
		m_iBlendGroup = b;
	}

	void SetUseLightArray(bool b)
	{
		m_bUseReadyLightArray = b;
	}

	bool GetUseLightArray()
	{
		return m_bUseReadyLightArray;
	}

	void SetUseClipPlanes(BOOL b)
	{
		m_bUseClipPlanes = b;
	}

	BOOL GetUseClipPlanes()
	{
		return m_bUseClipPlanes;
	}

	virtual void ForceTechnique()
	{

	}

protected:
	IShader(): m_bTransparent(FALSE), m_iIDTag(-1), m_iBlendGroup(0) {}

	// Вернуть уникальный handle для шейдеров, имеющих одинаковые общие параметры

	//! Прозрачный шейдер?
	BOOL m_bTransparent; 

	//! Установка общих параметров шейдера
	virtual void SetStateOnce() = 0; 
	//! Установка уникальных параметров шейдера 
	virtual void SetState() = 0; 
	//! Некий уникальный handle для шейдеров, имеющих одинаковые общие параметры
	int m_iIDTag;

	//! Тип шейдера
	eShaderType m_eType;

	//! 
	int m_iBlendGroup;
	//HACK
	CMatrix44 * m_pWorld;

	bool m_bUseReadyLightArray;
	BOOL m_bUseClipPlanes;
  //BOOL m_bAlphatest;
};

