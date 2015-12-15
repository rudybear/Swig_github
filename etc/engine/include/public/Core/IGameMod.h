///////////////////////////////////////////////////////////////////////////////
//	File: IGameMod.h
//	Description: Abstract GameMod
//	Copyright (c) 2004 Rudybear
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Public/Core/IMeshArray.h"
#include "Public/Core/ICore.h"
#include "Public/Core/INet.h"
#include "Public/Core/ITypeLib.h"
#include "Public/Core/IControls.h"
#include "Public/Render/IRender.h"
#include "Public/Sound/ISoundManager.h"

struct GameModImport
{
   IMeshArray * pArray;
	IRender * pRender;
	IScene * pScene;
	ICore * pCore;
	ISoundLib * pSoundLib;
	IControlsManager * pControlsManager;
	CXmlParams * pConsole;
	CXmlElement * pGameConfig;

	GameModImport() : pArray(NULL), pRender(NULL), pScene(NULL), pCore(NULL), pSoundLib(NULL), 
		pControlsManager(NULL), pConsole(NULL), pGameConfig(NULL) {};
};

class ILevelLogData;

  /*! \addtogroup Engine_related
  *@{
   */

//! интерфейс дл€ взаимодействи€ между игрой и Engine

class IGameMod
{
public:
#ifdef _WIN32
    HMODULE m_pModule;
#endif

    IGameMod() {}
    virtual ~IGameMod() {}

    virtual HRESULT ImportVars(const GameModImport& pImport) = 0;
    //!вызываетс€ Engine-ом при инициализации игры
    virtual HRESULT Init()=0;
    virtual HRESULT Restore()=0;
    //!вызываетс€ Engine-ом на каждом кадре, получить FrameTime можно из ICore
    virtual HRESULT Move()=0;
    virtual void KillGame() = 0;

    //!получение ориентации камеры из игры Deprecated
    virtual HRESULT GetCameraPosRot(CVec3 &Pos, CMatrix44 &Rot) { return S_OK; }

    virtual const SCoreStatistics* GetStatistics() const = 0;
    virtual ILevelLogData* GetLevelLog(void) { return NULL; }
    virtual void ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam ) {}

    ///////////////////////////////////////////////////////////////////////////
    // ѕретенденты на удаление:
    //////////////////////////////////////////////////////////////////////////
    // используетс€ везде, но вызываетс€ сразу после Init
    virtual HRESULT PostConstruct() { return S_OK; } 
    // используютс€ ли эти функции в других проектах?
    virtual BOOL GetMouseInverted() { return FALSE; }
    virtual void UpdateLoadingScreen() {}
    virtual void GiveAll() {}
    virtual void NoClip() {}
    //////////////////////////////////////////////////////////////////////////
};
//@}
