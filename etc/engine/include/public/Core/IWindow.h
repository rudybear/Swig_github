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


class IWindowListener
{
public:

  //!
  virtual void			OnCreate(void) = 0;
  //!
  virtual void			OnDestroy(void) = 0;
  //!
  virtual void			OnRequestClose(void) = 0;
  //! It's analogue of applicationDidBecomeActive
  virtual void			OnActivate(void) = 0;
  //! applicationDidEnterBackground
  virtual void			OnDeactivate(void) = 0;
  //! applicationWillEnterForeground
  virtual void			OnPreActivate(void) = 0;
  //! applicationWillResignActive
  virtual void			OnPreDeactivate(void) = 0;  
  //!
  virtual void			OnMove(const int x, const int y) = 0;
  //!
  virtual void			OnResize(const int width, const int height) = 0;
  //!
  virtual void			OnChangeStyle(unsigned int) = 0;
  //! 
  virtual void			OnMemoryWarning() = 0;
};

class IWindow
{
public:

  enum Style {
    Resizeable		= 0x00000001,
    Topmost			  = 0x00000002,
    Border			  = 0x00000004,
    ClientBorder	= 0x00000008,
    TitleBar		  = 0x00000010,
    Popup			    = 0x00000020,
		MinMaxBox			= 0x00000040,
    DefaultStyle	= Resizeable | ClientBorder | TitleBar,
  };
  //!
  IWindow() {}
  //!
  virtual ~IWindow() {}
  //!
  virtual bool Create(int x, int y, int width, int height, bool bFullScreen) = 0;
  //!
  virtual void SetName(const Engine2::String& name) = 0;
  //!
  //! TODO:
  //virtual void SetNameUnicode(Engine2::String& name) = 0;
  ////!
  virtual const Engine2::String& GetName() const = 0;
  //!
  virtual bool IsActive() const = 0;
  //!
  virtual void SetFocus() = 0;
  //!
  virtual void Show(bool) = 0;
  //!
  virtual bool IsInFocus() const = 0;
  //!
  virtual void SetSize(int width, int height, bool bFullscreen) = 0;
	//!
	virtual bool IsFullscreen() const = 0;
  //!
  virtual void SetPosition(int x, int y) = 0;
  //!
  virtual bool SetStyle(unsigned int style) = 0;
  //!
  virtual unsigned int GetStyle() const = 0;
  //!
  virtual RECT GetWindowRect() const = 0;
  //!
  virtual RECT GetClientRect() const = 0;
  //!
  virtual void RegisterListener(IWindowListener * ) = 0;
  //!
  virtual void UnRegisterListener(IWindowListener * ) = 0;
  //!
  virtual void Invalidate(const RECT *) = 0;
  //!
  virtual void Close() = 0;
  //! 
  virtual WIN_HWND GetWindowHandle() const {
        return 0;
  };
  //!
  virtual void RegisterHWND(WIN_HWND hWnd) {

  };

  // Use this method to notify engine when RegisterHWND is used
  virtual void NotifyMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
  {

  }

#ifdef TARGET_OS_WIN
  virtual void SetIcon(HICON icon) = 0;
  //!

  //!
  virtual HDC	GetDeviceHandle() const = 0; 

	
#endif

#ifdef __APPLE__

#endif
};