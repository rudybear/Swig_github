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
#include "IClientDraw.h"
//#include "..\..\DxLib\D3DUtil.h"
#include "Public/Common/Param.h"
#include "Public/Common/Camera.h"
#include "Public/Render/RenderCommon.h"
#include "IMeshInfo.h"
#include "ICore.h"
#include "Public/Core/IMeshArray.h"
#include "Public/Sound/ISoundManager.h"
#include "Public/Core/IDIHandler.h"
#include "Public/Core/IWeatherSystem.h"

class IScene //:public EnginePublic::IScene
{
public:
	IScene() {}; //:EnginePublic::IScene(){};
	~IScene(){};

  virtual size_t AddWeather() = 0;
  virtual void RemoveWeather(size_t ) = 0;
  virtual size_t GetWeathersCount(void) = 0;
  virtual size_t GetActiveWeather(void) = 0;
  virtual void SetActiveWeather(size_t ) = 0; // 0 - engine weather. Started from 1 - user settings

	virtual HRESULT ProjParams(float fFov,float fZNear,float fZFar)=0;
	virtual HRESULT Restore() = 0;
	virtual HRESULT Invalidate() = 0;
	virtual void RenderFrame(void) = 0;

	virtual CCamera * GetCamera() const  = 0;
	virtual void SetCamera(CCamera * ) = 0;

	virtual RenderStatistics RenderSceneObjects(eRenderType) = 0;
	virtual HRESULT ImmediateRenderSceneObjects(eRenderType Type) = 0;

	virtual HRESULT RenderScene2DObjects() = 0;
	virtual void Clear() = 0;
	
	virtual HRESULT ReInitRender(DWORD, DWORD, DWORD, BOOL) = 0;

	//! deprecated
	virtual size_t RegistryClientDrawer(IClientDraw* pDrawer, int nTextureID, int nBlendFunc, int nDepthFunc) = 0;
	//! deprecated
	virtual HRESULT UnRegistryClientDrawer(IClientDraw* pDrawer, int m_nTextureID, int nBlendFunc, int nDepthFunc) = 0;
	virtual void RemoveAllClientDrawers(void)=0;

	virtual IGameRenderObject *GetRenderObject(void) = 0;

	virtual IRender * GetRender() = 0;
	virtual IWeather * GetWeatherSystem() = 0;

public:
	virtual	IMeshArray*	GetMeshArray(void)=0;
	virtual IMeshInfo* AddCreateMesh(const CXmlElement * paraminfo, BOOL bSelfDraw) = 0;
	virtual void DeleteMesh(IMeshInfo*) = 0;
	virtual void SetSendEmptyEvent(bool b) = 0;
	virtual float GetGamma() = 0;
	virtual void SetGamma(float f) = 0;
	virtual IGameMod *GetGameMod() = 0;
};
