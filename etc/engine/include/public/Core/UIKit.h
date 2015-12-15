#ifndef _uikit_h
#define _uikit_h

typedef struct IPhoneGLConfig IPhoneGLConfig;
struct IPhoneGLConfig
{
  int red_size;
  int green_size;
  int blue_size;
  int alpha_size;
  int depth_size;
  int retained_backing;
};

#ifdef __cplusplus
#define C_LINKAGE	"C"
#else
#define C_LINKAGE
#endif /* __cplusplus */

extern C_LINKAGE int UIKit_GL_MakeCurrent(int nSet);
extern C_LINKAGE void UIKit_GL_SwapBuffer();
extern C_LINKAGE int UIKit_GL_CreateContext(IPhoneGLConfig *pConfig);
extern C_LINKAGE void UIKit_GL_DeleteContext();

//===================================================================================

#define WINDOW_BORDERLESS 1
#define WINDOW_LANDSCAPE 2
#define WINDOW_FULLSCREEN 3

extern C_LINKAGE int  UIKit_CreateWindow(int nFlags);
extern C_LINKAGE void UIKit_DestroyWindow();
extern C_LINKAGE void UIKit_ShowWindow(bool bShow);
extern C_LINKAGE void UIKit_UpdateResolution(int* width, int* height);
extern C_LINKAGE void UIKit_GL_SwapBuffer(); 

//===================================================================================

#define MOUSE_BUTTON_LEFT  1
#define MOUSE_BUTTON_RIGHT 2

#define MOUSE_PRESSED      1
#define MOUSE_DOUBLE_PRESSED 2
#define MOUSE_RELEASED     3

extern C_LINKAGE void UIKit_SendMouseMotion(int Id, int relative, int x, int y);
extern C_LINKAGE void UIKit_SendMouseButton(int Id, int x, int y, int state, int button); 
extern C_LINKAGE void UIKit_SendJoystickMotion(int pitch, int roll, int yaw);
extern C_LINKAGE void UIKit_SendAccelerometerMotion(float yaw, float pitch, float roll);
extern C_LINKAGE void UIKit_SendAttitudeAngles(float x, float y, float z);
extern C_LINKAGE void UIKit_SendSwipeMotion(int type, int distance);
//extern C_LINKAGE void UIKit_SendQuit(); 
extern C_LINKAGE void	UIKit_SetDesiredFPS(float fFPS);
extern C_LINKAGE void	UIKit_SetError(const char *szError);
extern C_LINKAGE bool FixPathForPlatform(char * buf, int sizebuf, const char * srcPath, const char * Mode);  
extern C_LINKAGE void	UIKit_CreateTapRecognizer(int numFingers, int numTaps);
extern C_LINKAGE void	UIKit_DeleteTapRecognizer(int numFingers, int numTaps);
extern C_LINKAGE void	UIKit_DeleteGestureRecognizer();
extern C_LINKAGE void	UIKit_CreateGestureRecognizer();
extern C_LINKAGE void	UIKit_SendTap(int i, int x, int y);
extern C_LINKAGE void UIKit_ApplicationDidEnterBackground();
extern C_LINKAGE void UIKit_ApplicationWillResignActive();
extern C_LINKAGE void UIKit_ApplicationDidBecomeActive();
extern C_LINKAGE void UIKit_ApplicationWillEnterForeground();
extern C_LINKAGE void UIKit_ApplicationMemoryWarning();
extern C_LINKAGE bool UIKit_ApplicationReady();

//extern C_LINKAGE int UIKit_main(int argc, char **argv);

typedef void(*lpUIKITExternalUpdate)(void);
extern lpUIKITExternalUpdate pUIKITExternalUpdate;
typedef bool(*lpUIKit_ApplicationhandleOpenURL)(void *); // I hate this. Type is NSURL!
extern lpUIKit_ApplicationhandleOpenURL pApplicationhandleOpenURL;
typedef bool(*lpUIKit_ApplicationdidFinishLaunchingWithOptions)(void *); // Type is NSDictionary
extern lpUIKit_ApplicationdidFinishLaunchingWithOptions pUIKit_ApplicationdidFinishLaunchingWithOptions;

extern C_LINKAGE void UIKit_updateframe(); 

typedef void(*lpUIKIT_Main)(void);
extern lpUIKIT_Main pUIKIT_Main;


#ifdef TARGET_OS_IPHONE
extern C_LINKAGE int WinMain(int, int, char *, int); 
#endif

#endif /* _uikit_h */
