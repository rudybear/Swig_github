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

#include "Public/Core/ICore.h"

class IRender;

enum eSoundVolumeType {
	e_All,
	e_Sound,
	e_Music
};


enum eSoundDriver {
	e_DirectSound,
	e_EAX4,
	e_Null
};

// Флаги для описания звукового буфера

#define S_PRIMARYBUFFER       0x00000001
#define S_STATIC              0x00000002
#define S_LOCHARDWARE         0x00000004
#define S_LOCSOFTWARE         0x00000008
#define S_CTRL3D              0x00000010
#define S_CTRLFREQUENCY       0x00000020
#define S_CTRLPAN             0x00000040
#define S_CTRLVOLUME          0x00000080
#define S_CTRLPOSITIONNOTIFY  0x00000100
#define S_CTRLFX              0x00000200
#define S_STICKYFOCUS         0x00004000
#define S_GLOBALFOCUS         0x00008000
#define S_GETCURRENTPOSITION2 0x00010000
#define S_MUTE3DATMAXDISTANCE 0x00020000
#define S_LOCDEFER            0x00040000
#define S_EAX				  0x00080000

// Качество 3D звука
#define S_NO3D					0x00
#define S_3DQUALITY_LOW			0x01
#define S_3DQUALITY_MEDIUM		0x02
#define S_3DQUALITY_HIGH		0x04
#define S_3DQUALITY_AUTO		0x05

// Режим обсчета 3d-параметров звука
#define S_PROCESSING_MODE_NORMAL		0x00000000
#define S_PROCESSING_MODE_HEADRELATIVE	0x00000001
#define S_PROCESSING_MODE_DISABLE		0x00000002

#define S_PLAY_LOOPED					0x00000001

//! Абстрактный класс звука
//! Есть один тонкий момент. Звук может быть статическим и динамическим
//! Сам звук физически существует в единственном экземпляре, а остальные только дублируют его данные
//! При запросе звука выдается указатель на свободный буфер. Свободный - это нестатический и непроигрываемый в текущий момент
//! Если звук используется постоянно, то необходимо его делать статическим!
//! Статический звук получается при его блокировке!


class ISound
{
public:
	ISound() {;};
	virtual ~ISound() {;};
	
	//! Проиграть звук 
	virtual HRESULT Play(DWORD dwPriority = 0, DWORD flags = 0) = 0; 
	//! Остановить звук 
	virtual HRESULT Stop() = 0;
	//! Установить громкость
	virtual HRESULT SetVolume(long volume) = 0;
	//! Установить панораму
	virtual HRESULT SetPan(long pan) = 0;
	//! Установить частоту
	virtual HRESULT SetFreq(DWORD freq) = 0;


	// Методы для 3D - звуков
	//! Установить базовые параметры звука - минимальную и максимальную дистанции и режим 
	virtual void SetSoundParams(float fMinDistance, float fMaxDistance, DWORD dwMode) = 0;
	//! Установить 3D параметры звука - позицию звука и скорость 
	virtual void SetSound3DParams(CVec3* vPos, CVec3* vVel) = 0;
	//! Установить параметры распростанения звука - внутренний угол, внешний угол, ориентация конуса и громкость вне конуса
	virtual void SetSoundConeParams(DWORD dwInsideConeAngle, DWORD dwOutsideConeAngle, CVec3* vConeOrientation, LONG lConeOutsideVolume) = 0;
	//! Обновить параметры
	virtual HRESULT UpdateSoundParams() = 0;

	//! Звук играется?
	virtual BOOL IsSoundPlaying() = 0;

	//! Получить громкость звука
	virtual HRESULT GetVolume(LONG &volume) const = 0;

	//! Получить длительность звука в секундах
	virtual HRESULT GetLength(float &length) const = 0;

	//! Разрешить\запретить изменение скорости проигрывания звука библиотекой
	virtual void SetPlaybackSpeedAffectableFlag(bool flag) = 0;
};


class ISoundLib
{
public:
//	HMODULE m_pModule;
	ISoundLib() {};

#if defined(_WIN32) || defined(_WIN64)
	HMODULE m_pModule;
#endif

	virtual void SetApplication(ICore *) = 0;
	virtual int LoadStreamingSound(const char * FileName) = 0;
	virtual ~ISoundLib() {};
    
#if defined(_WIN32) || defined(_WIN64)    
	virtual HRESULT Init(HWND) = 0;
#endif    
    
	virtual HRESULT Init() = 0;

	virtual ISound* LoadSound(const char *FileName, DWORD Flags = S_CTRLVOLUME | S_CTRL3D, DWORD Quality = S_3DQUALITY_AUTO) = 0;
  virtual ISound* LoadSoundFromMemory(const char * buf, size_t size, const char *FileName, DWORD Flags = S_CTRLVOLUME | S_CTRL3D, DWORD Quality = S_3DQUALITY_AUTO) = 0;
	virtual HRESULT ReleaseSound(const char *FileName, DWORD Flags) = 0;
	virtual HRESULT ReleaseSound(ISound *sound) = 0;
	virtual BOOL IsStreamSoundPlaying() = 0;

	virtual void Close() = 0;
	virtual HRESULT PlayStreamSound( BOOL bLooped ) = 0;
	virtual void StopStreamSound() = 0; 
	virtual HRESULT GetStreamingSoundVolume(LONG *plVolume) = 0;
	virtual HRESULT SetStreamingSoundVolume(LONG lVolume) = 0;
	virtual HRESULT SetVolume(float, eSoundVolumeType) = 0;
	virtual float GetVolume(eSoundVolumeType) = 0;
	virtual HRESULT CreateListener() = 0;
	virtual void SetListenerParams(FLOAT fDistance, FLOAT fRolloff, FLOAT fDoppler) = 0;
	virtual void SetListener3DParams(CVec3 * vPos, CVec3 * vVel, CVec3 * vFront, CVec3 * vTop) = 0;
	virtual HRESULT UpdateListenerParams() = 0;
	virtual eSoundDriver GetType() = 0;

#if defined (USE_EAX)
	virtual BOOL SetSourceEAXProperty(int SourceIndex, GUID guid, unsigned long ulProperty, void *pData, unsigned long ulDataSize) = 0;
	virtual BOOL GetSourceEAXProperty(int SourceIndex, GUID guid, unsigned long ulProperty, void *pData, unsigned long ulDataSize) = 0;
	virtual void StoreSourceProperty(int SourceIndex, unsigned long ulProperty, void *pData, unsigned long ulDataLength) = 0;
	virtual BOOL SetGlobalEAXProperty(GUID guid, unsigned long ulProperty, void *pData, unsigned long ulDataSize) = 0;
	virtual BOOL GetGlobalEAXProperty(GUID guid, unsigned long ulProperty, void *pData, unsigned long ulDataSize) = 0;
#endif
	virtual void Clear() = 0;
	virtual void PrintStatistics(IRender *render) = 0;
	virtual void SetMixingMode(bool hw_or_sw) = 0;
	virtual bool GetMixingMode() = 0;

	virtual void SetFrequencyFactor(float fFactor, bool override = false) = 0;

	virtual void PauseAllSounds() = 0;
	virtual void ResumeAllSounds() = 0;
};
