#ifndef _uikitwindow_h
#define _uikitwindow_h

#import "UIKitOpenglView.h"

typedef struct IPhoneWindow IPhoneWindow;

struct IPhoneWindow
{
  
  enum DeviceOrientation{
    DeviceOrientationUnknown,
    DeviceOrientationPortrait,            // Device oriented vertically, home button on the bottom
    DeviceOrientationPortraitUpsideDown,  // Device oriented vertically, home button on the top
    DeviceOrientationLandscapeLeft,       // Device oriented horizontally, home button on the right
    DeviceOrientationLandscapeRight,      // Device oriented horizontally, home button on the left
    DeviceOrientationFaceUp,              // Device oriented flat, face up
    DeviceOrientationFaceDown             // Device oriented flat, face down
  };
  
  UIWindow *uiwindow;
  UIKitOpenglView *uiview;
  int m_iWidth;
  int m_iHeight;
  int m_iLandscapeMode;
  enum DeviceOrientation m_eOrientation;
  
};

extern IPhoneWindow *g_IWindow;

#endif /* _uikitwindow_h */

