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
#include "Public/Common/STLHelpers.h"
#include "Public/Core/IVFSFileManager.h"
#include "Public/Core/IStreaming.h"
#include "Public/Core/IStats.h"
#include "Public/Common/Profiler.h"
#include "Public/Core/IWindow.h"
#include "Public/Core/IInput.h"
#include "Public/EntitySystem/IEntitySystem.h"

enum eLogAttr {
	e_Release,
	e_Debug,
	e_ParanoidalLogging,

	eLastLogDummy = (int)0xFFFFFFF
};

#define ENGINE2_REV     0x1000

#define LogErrorMask   0x10000000
#define LogNoCaretMask 0x01000000

class CXmlElement;
class IClientDraw;
class IGameRenderObject;
class IGameMod;
class IGameWorld;
class IScene;
class IStats;
class IControlsManager;
class IInput;


#include "Public/Render/IEffectsLib.h"


struct ComponentInfo {
	uint32 m_iParent; // - parent id in statistics vector
	char m_strName[512];
	uint64 m_iMemoryUsage;
	uint64 m_iCount;
};

struct SCoreStatistics {
	Engine2::Vector<ComponentInfo> m_Components;

};

//======================================================================================================

class IChangesSubscription
{
public:
	//!
	virtual size_t GetNumSubfolders() = 0;
	//!
	virtual const char * GetSubfolder(size_t ) = 0;
	//!
	virtual size_t GetNumExtensions() = 0;
	//!
	virtual const char * GetExtension(size_t ) = 0;
	// callback
	virtual void FileChanged(const char *) = 0;
};

/*! \addtogroup Engine_related Engine Classes
*@{
*/

//!Engine Core Interface

typedef void(*pLoggingFunction)(const char *);



class IStatisticsManager {
public:
	//!
	virtual void AddTexturesReadBytesStats(size_t ) = 0;
	//!
	virtual void AddModelsReadBytesStats(size_t) = 0;
	//!
	virtual size_t GetTexturesReadBytesStats() = 0;
	//!
	virtual size_t GetModelsReadBytesStats() = 0;
	//!
	virtual size_t GetTotalReadBytesStats() = 0;
	//!
	virtual void DumpToLog() = 0;
	//!
	virtual void DumpToScreen() = 0;
	//! 
	virtual IStats *CreateStats(EStatsType eStats, float fInterval) = 0;

};

enum eStartGameType {
	eNoCrashHandling,
	eCrashDump,
	eCrashLog,
	eNoCrashHandlingNoLog,
	eCrashDumpNoLog,
	eCrashLogNoLog
};


class ILogListener {
public:
	//!
	virtual void AddError(const char *) { };
	//!
	virtual void AddWarning(const char *) { };
};

class IProfilerListener {
public:
	//!
	virtual void StartLog() {};
	//!
	virtual void AddLogMessage(const char *) {};
	//!
	virtual void EndLog() {};
};
// get HWND via GetAppHWND
typedef void(*pWindowChangesFunction)(IWindow * );

class ILoadingProfilerManager
{
public:
	//!
	virtual void EnableProfiling(bool b) = 0;
	//!
	virtual void DumpStatsToXML(const char * ) = 0;
	//!
	virtual Engine2::String DumpStatsToString() = 0;
	//!
	virtual int StartLoadingSection(const char * eventType, const char * evenName) = 0;
	//!
	virtual void EndLoadingSection(int, double) = 0;
	//!
	virtual int StartProfilerInfo(const char * section, const char * name) = 0;
	//!
	virtual void EndProfilerInfo(int, double) = 0;
	//!
	virtual void Clear() = 0;
};

enum ERendererError
{
	eRNE_OK,
	eRNE_Unknown,
	eRNE_D3DDeviceCreateFailed,
	eRNE_UnknownResolution,
	eRNE_UnsupportedShaderVersion,
	eRNE_HWFogNotSupported,
	eRNE_24BitDepthNotSupported,
	eRNE_32BitBufferNotSupported,
};


class IDebugInformationManager
{
public:
	//!
	//! Load param vaelu from config file
	virtual void LoadParam(CParam *) = 0;
	//! Add parameter for Editor
	virtual void AddDebugParam(CParam *, const char * section) = 0;
	// Remove parameter for Editor
	virtual void RemoveDebugParam(CParam *) = 0;
	//! Get number of registered parameters
	virtual uint32 GetDebugParamNums() = 0;
	//! Return section for debug parameter
	virtual const char * GetDebugParamSection(uint32 num) = 0;
	//! Return  debug parameter
	virtual CParam * GetDebugParam(uint32 num) = 0;
	virtual CParam * GetDebugParamByName( const char *sParamName ) = 0;
	virtual void ExecuteString(const char *) = 0;
	virtual int GetNumCVars() = 0;
	virtual const char * GetCVarName(int num) = 0;
	virtual const char * GetCVarValue(int num) = 0;
	virtual const char * GetCVarType(int num) = 0;

	// Helper functions to set parameter by name
	virtual bool SetDebugParamInt( const char *sParamName,int value ) = 0;
	virtual bool SetDebugParamFloat( const char *sParamName,float value ) = 0;
	virtual bool SetDebugParamString( const char *sParamName,const char *sValue ) = 0;
};

class IPerformanceProfilerManager
{
public:
	//!
	virtual int StartProfilerInfo(const char * section, const char * name) = 0;
	//!
	virtual void EndProfilerInfo(int, double) = 0;
	//!
	virtual void DumpProfilerInfoToLog() = 0;
	//!
	virtual void SetProfilerListener(IProfilerListener* ) = 0;

};

class IConfigFile
{
public:
	//! Return game type as constant string
	virtual const char *GetGameType() = 0;
	//! Get path to the folder
	virtual const char * GetPath(const char *) = 0; 
	//! Get 
	virtual uint32 GetTexturesPathCount() = 0;

	virtual const char * GetTexturesPath(uint32) = 0;
	virtual uint32 GetModelsPathCount() = 0;
	virtual const char * GetModelsPath(uint32) = 0;
	virtual const char * GetTerrainPath() = 0;
	virtual uint32 GetEffectsPathCount() = 0;
	virtual const char * GetEffectsPath(uint32) = 0;
  virtual const char * GetEffectsWritePath() = 0;
	virtual uint32 GetScriptsPathCount() = 0;
	virtual const char * GetScriptsPath(uint32) = 0;
	virtual const char * GetSoundPath() = 0;
	virtual const char * GetDataFolder() = 0;
	virtual const char * GetGameDialog() = 0;
	virtual const char * GetAnimationFolder() = 0;
	virtual uint32 GetParticlesPathCount() = 0 ;
	virtual const char * GetParticlesPath(uint32) = 0;
	virtual BOOL LoadConfigFromFile(const char *szFileName, CParam * params = 0, int  paramCount = 0) = 0;
	virtual BOOL LoadRenderConfig(const char *szProfile) = 0;
	virtual void SaveConfig() = 0;
	virtual CXmlElement *GetConfigXML(void) = 0;
};

class ILogManager
{
public:
	//! Register a log listener 
	virtual void RegisterListener(ILogListener * ) = 0;
	//! Add message to the log 
#ifndef TARGET_OS_FLASH
	virtual void AddToLog(uint32 attr, const char * format, ...) = 0;
#endif
	//!
	virtual void SetLastErrorLogging(bool) = 0;
	//!
	virtual uint32 GetLastErrorCount() = 0;
	//!
	virtual const char * GetLastError(uint32 ) = 0;
	//!
	virtual void ClearLastErrorList() = 0;
	//! 
	virtual void SetLogCallback(pLoggingFunction * ) = 0;
	//! Return last render error
	virtual ERendererError GetLastRenderError() = 0;
	// ! Set last render error
	virtual void SetLastRenderError (ERendererError eLastError) = 0;

};

#ifdef TARGET_OS_FLASH
namespace Engine2
{
  extern void AddToLog(uint32 attr, const char * format, ...);
}
#endif

class ICore
{
public:

	//!//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//!
	//! Common
	//!
	//!//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ICore() {};
	//!
	virtual ~ICore(){};
	//!
	virtual void Close() = 0;
	//! 
	virtual HRESULT ParseConsoleParams(const char * m_szParams) = 0;

	//! TODO:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//#if defined(_WIN32) || defined(_WIN64)
	virtual bool Init(HINSTANCE hInstance, const char *szCaption=0, HICON hIcon=0) = 0;
//#endif    

	virtual bool Init(CXmlElement * init) = 0;
	//!
	virtual int Run() = 0;
	//!
	virtual HRESULT Frame(bool Move = true) = 0;


  //!//////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //!
  //! Windows management
  //!
  //!//////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //! Add a new platform-dependent window
  virtual IWindow * AddWindow() = 0;
  //! Get current window
	virtual IWindow * GetWindow() = 0;
  //! Initial parameters for default window creation
  virtual void SetInitialWindowParameters(int xPos, int yPos, int width ,int height, int bpp, BOOL fullscreen) = 0;
	//! Client code could intercept window creation and change parameters here
	//virtual void SetWindowChangeCallback(pWindowChangesFunction *) = 0;

	//!//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//!
	//! Access to managers
	//!
	//!//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//! Loading profiler manager
	virtual ILoadingProfilerManager * GetLoadingProfiler() = 0;
	//! Performance profiler manager
	virtual IPerformanceProfilerManager * GetPerformanceProfiler() = 0;
	//! Virtual file system manager
	virtual IVFSFileManager *GetVFSManager(void) = 0;
	//! Streaming engine manager
	virtual IStreamEngine * GetStreamingEngine(int num) = 0;
	//! Return config file information
	virtual IConfigFile * GetConfigFile() = 0;
	//! Return debug information manager
	virtual IDebugInformationManager * GetDebugInformationManager() = 0;
	//! Get statistics manager
	virtual IStatisticsManager * GetStatisticsManager() = 0 ;
	//! Get controls manager
	virtual IControlsManager *GetControlsManager(void) = 0;
	//! Get log manager
	virtual ILogManager * GetLogManager() = 0;
  //! Get IInput interface
  virtual IInput * GetInputEngine() = 0;
	//! Get IEntitySystem interface
	virtual IEntitySystem* GetEntitySystem() = 0;



	//!//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//!
	//! Scene management
	//!
	//!//////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//! Get active scene
	virtual IScene *GetScene(void) = 0;
	//! Add new scene
	virtual int AddScene(void) = 0;
	//! Remove scene
	virtual void RemoveScene(int) = 0;
	//! Get active scene id
	virtual int GetActiveSceneID() = 0;
	//! Set active scene
	virtual bool SetActiveScene(int) =0;


	//!//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//!
	//! Stuff
	//!
	//!//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual BOOL SetGameMod(IGameMod *pGameMod) = 0;
	//! получить гейммод
	virtual IGameMod *GetGameMod(void) =0 ;

	//TODO:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//! Need to fix that

	virtual bool RegisterSubscription(IChangesSubscription *) = 0;
	//!
	virtual bool UnregisterSubscription(IChangesSubscription *) = 0;

  virtual BOOL LoadRenderConfig(const char *szProfile) = 0;
};

/*
*@}
*/




#ifdef SWIG
ICore *CreateCore(eStartGameType, const char * pName = 0);
void DeleteCore(ICore * pCore);
// TODO: Problems with generation actually
#define DISABLE_PROFILING
#endif

#if defined(TARGET_OS_IPHONE) || defined(TARGET_OS_ANDROID) || defined(TARGET_OS_FLASH) || defined(TARGET_OS_EMSCRIPTEN) || defined(SWIG)
#ifndef DISABLE_PROFILING
#define DISABLE_PROFILING
#endif
#endif

#ifndef DISABLE_PROFILING
#ifndef ENABLE_PROFILING
#define ENABLE_PROFILING
#endif
#endif


struct AutoProfilerGuard {

	AutoProfilerGuard(const char * section, const char * name, ICore * pCore) 
#ifdef ENABLE_PROFILING
		: m_pCore(pCore) 
#endif
	{
#ifdef ENABLE_PROFILING
		//m_iStackLevel = m_pCore->AddProfilerStackLevel(); 
		m_Id = m_pCore->GetPerformanceProfiler()->StartProfilerInfo(section, name); //, m_iStackLevel);
		if (m_Id >= 0)
			Start = StartProfiling();
#endif
	}

	double GetTime() {
#ifdef ENABLE_PROFILING
		if (m_Id >= 0)
			return EndProfiling(Start);
#endif
		return 0.;
	}

	~AutoProfilerGuard() {
#ifdef ENABLE_PROFILING
		if (m_Id >= 0)
		{
			double renderms = EndProfiling(Start);
			m_pCore->GetPerformanceProfiler()->EndProfilerInfo(m_Id, renderms);
		}
#endif
	}

private:
#ifdef ENABLE_PROFILING
	LARGE_INTEGER Start;
	ICore *m_pCore;
	int m_Id;
#endif
};

struct AutoLoadingSectionGuard {

	AutoLoadingSectionGuard(const char * section, const char * name, ICore * pCore)
#ifdef ENABLE_PROFILING
		: m_pCore(pCore) 
#endif
	{
#ifdef ENABLE_PROFILING
		//m_iStackLevel = m_pCore->AddProfilerStackLevel(); 
		m_Id = m_pCore->GetLoadingProfiler()->StartLoadingSection(section, name); //, m_iStackLevel);
		if (m_Id >= 0)
			Start = StartProfiling();
#endif
	}

	~AutoLoadingSectionGuard() {
#ifdef ENABLE_PROFILING
		if (m_Id >= 0)
		{
			double renderms = EndProfiling(Start);
			m_pCore->GetLoadingProfiler()->EndLoadingSection(m_Id, renderms);
		}
#endif
	}

private:
#ifdef ENABLE_PROFILING
	LARGE_INTEGER Start;
	ICore *m_pCore;
	int m_Id;
#endif
};

struct AutoLoadingProfilerGuard {

	AutoLoadingProfilerGuard(const char * section, const char * name, ICore * pCore) 
#ifdef ENABLE_PROFILING
		: m_pCore(pCore)
#endif
	{
#ifdef ENABLE_PROFILING
		//m_iStackLevel = m_pCore->AddProfilerStackLevel(); 
		m_Id = m_pCore->GetLoadingProfiler()->StartProfilerInfo(section, name); //, m_iStackLevel);

		if (m_Id >= 0)
			Start = StartProfiling();
#endif
	}

	~AutoLoadingProfilerGuard() {
#ifdef ENABLE_PROFILING
		if (m_Id >= 0)
		{
			double renderms = EndProfiling(Start);
			m_pCore->GetLoadingProfiler()->EndProfilerInfo(m_Id, renderms);
		}
#endif
	}

private:
#ifdef ENABLE_PROFILING
	LARGE_INTEGER Start;
	ICore *m_pCore;
	int m_Id;
#endif
};

#ifdef ENABLE_PROFILING
#define FRAME_PROFILER(A, B, C) AutoProfilerGuard tempProfilerGuard(A, B, C); 
#define LOADING_PROFILER(A, B, C) AutoLoadingProfilerGuard tempLoadingProfilerGuard(A, B, C);
#define LOADING_SECTION(A, B, C) AutoLoadingSectionGuard tempLoadingSectionGuard(A, B, C);
#else
#define FRAME_PROFILER(A, B, C)
#define LOADING_PROFILER(A, B, C)
#define LOADING_SECTION(A, B, C)
#endif
