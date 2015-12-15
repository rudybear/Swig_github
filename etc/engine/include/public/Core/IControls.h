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

/*! \addtogroup Engine_related
*@{
*/

//! Controls Virtual Axis Interface

class IGameAxis
{
public:
	IGameAxis(){};
	virtual ~IGameAxis(){};

	virtual /*stlstring*/ const char * GetName() = 0;

	virtual float GetValue(void) = 0;

	virtual void SetLinkAxis(int nDeviceType,int nDeviceNum,int nAxis) = 0;
	virtual void SetIncButtonLink(int nDeviceType,int nDeviceNum,int nButton) = 0;
	virtual void SetDecButtonLink(int nDeviceType,int nDeviceNum,int nButton) = 0;

	virtual void SetIncreaseSpeed(float fSpeed) = 0;

	virtual void SetSpeedMultiply(float fSpeed) = 0;
	virtual float GetSpeedMultiply(void) = 0;

	virtual BOOL IsInverted(void) = 0;
	virtual void SetInverted(BOOL bState) = 0;

	virtual float GetDeadZone(void) = 0;
	virtual void SetDeadZone(float fValue) = 0;

};
//! Controls Virtual Button Interface

class IGameButton
{
public:
	IGameButton(){};
	virtual ~IGameButton(){};

	virtual int GetValue(void) = 0;
	virtual const char *GetName(void) = 0;

	virtual void GetLinkDevice(int &nDeviceType,int &nDeviceNum,int &nButton) = 0;
	virtual void SetLinkDevice(int nDeviceType,int nDeviceNum,int nButton) = 0;

	virtual void SetDeveloperMode(BOOL bEnabled) = 0; //if TRUE - will be accessed only internaly not seen in config
	virtual BOOL GetDeveloperMode(void) = 0; //if TRUE - will be accessed only internaly not seen in config
};

//! Controls Manager Interface

typedef void (*TKeyboardCallback)(unsigned int nID, int nButton, BOOL bValue); 

class CXmlElement;

class IControlsManager
{
public:
	IControlsManager(){};

	virtual ~IControlsManager(){};

	virtual IGameButton *GetButtonByName(const  char * szName) = 0;

	virtual IGameAxis *GetAxisByName(const  char * sszName) = 0;

	virtual size_t GetNumButtons(void) = 0;

	virtual IGameButton *GetButton(size_t nNum) = 0;

	virtual size_t GetNumAxises(void) = 0;

	virtual IGameAxis *GetAxis(size_t nNum) = 0;

	virtual BOOL LoadConfigFromXML(CXmlElement *pConfigDataXML) = 0;

	virtual CXmlElement *GetControlsSettings(void) = 0;

	virtual float IsAxisStateChanged(int &nDeviceType,int &nDeviceNum,int &nAxis) = 0;

	virtual BOOL IsButtonStateChanged(int &nDeviceType,int &nDeviceNum,int &nButton) = 0;

	virtual BOOL GetButtonDesc(Engine2::String& szPlace, int nDeviceType, int nDeviceNum, int nButton) = 0;

	virtual BOOL GetAxisDesc(Engine2::String& szPlace, int nDeviceType, int nDeviceNum, int nAxis) = 0;
	
	virtual IGameAxis* DetermineAxisLink(const  char * szName) = 0;

	virtual IGameButton* DetermineButtonLink(const  char * szName) = 0;

	virtual IGameAxis * DetermineButtonAxisLink(const  char * szAxisName, const  char * szButtonName) = 0;

	virtual IGameAxis *CreateNewAxis(const char * szName) = 0;

	virtual IGameButton *CreateNewButton(const char * szName) = 0;

	virtual bool ResetButtons(int nDeviceType,int nDeviceNum,int nButton) = 0;

  virtual void ResetBinds()  = 0;

	virtual void Update(float fDeltaT) = 0;

	virtual void SetKeyboardCallback(TKeyboardCallback callback) = 0;

	virtual void SetMouseLock() = 0;

	virtual void SetMouseUnlock() = 0;

	virtual bool GetMouseLockStatus() = 0;

	virtual bool IsInFocus() = 0;

};
/*
*@}
*/
