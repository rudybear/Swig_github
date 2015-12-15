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
#include "Public/Common/Mathlib.h"
#include "Public/Common/Param.h"
#include "IControls.h"

class ICore;

enum {
	eP_NOTHING = 0, 
	eP_PRESSED,
	eP_HOLD,
	eP_RELEASED
};

enum GameDevicesEnum
{
	eDevice_NONE,			// dummy
	eDevice_JOYSTICK,		// all game controllers
	eDevice_KB,				// all keyboards
	eDevice_MOUSE,			// all pointers
};

struct IDirectInputHandler
{
#if defined(_WIN32) || defined(_WIN64)
	HMODULE m_pModule;
#endif

	virtual ~IDirectInputHandler(void){};
	virtual void Reset(void) = 0;

	BOOL m_bActive;
	CParam m_bExclusiveMouse;


	virtual int KeyState(int Key) = 0;
	virtual int MouseButtonState(int Key)=0;
	virtual int JoystickButtonState(int Key)=0;
    //FIXME:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if defined (_WIN32) || defined (_WIN64)
	virtual HRESULT Init(HINSTANCE hInstance,HWND ParentHWND, ICore * pCore)=0;
#endif    
	virtual HRESULT Init(ICore * pCore)=0;
	virtual HRESULT Focus(BOOL) = 0;
	virtual void GetData(void) = 0; //used to Ask data for device called from GameMod once per frame

	virtual int GetButtonState(unsigned int nDeviceType, unsigned int nDeviceNum, unsigned int nButton) = 0;
	virtual float GetAxisState(unsigned int nDeviceType, unsigned int nDeviceNum, unsigned int nAxis) = 0;

	virtual const char * GetKeyName(int nOffset) = 0;

	virtual float IsAxisStateChanged(int &nDeviceType,int &nDeviceNum,int &nAxis) = 0; 
	virtual BOOL IsButtonStateChanged(int &nDeviceType,int &nDeviceNum,int &nButton) = 0; 
	virtual void SetKeyboardCallback(TKeyboardCallback callback) = 0;

	virtual int MousePosX() = 0;
	virtual int MousePosY() = 0;
};

