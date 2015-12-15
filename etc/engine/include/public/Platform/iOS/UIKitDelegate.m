#import "UIKitDelegate.h"
#import "UIKitOpenglView.h"

#import "UIKitWindow.h"
#import "UIRootController.h"

#include "Public/Core/UIKit.h"

static int forward_argc;
static char **forward_argv;

int main(int argc, char **argv) {

  if (pUIKIT_Main)
  {
    pUIKIT_Main();    
  }
  else
  {
    int i;
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  
    /* store arguments */
    forward_argc = argc;
    forward_argv = (char **)malloc(argc * sizeof(char *));
    for (i=0; i<argc; i++) {
      forward_argv[i] = malloc( (strlen(argv[i])+1) * sizeof(char));
      strcpy(forward_argv[i], argv[i]);
    }

    /* Give over control to run loop, UIKitDelegate will handle most things from here */
    UIApplicationMain(argc, argv, NULL, @"UIKitDelegate");
    
    [[UIKitDelegate sharedAppDelegate] Main];
    
    [pool release];
  }
}

@implementation UIKitDelegate


@synthesize window, rootViewController;

/* convenience method */
+(UIKitDelegate *)sharedAppDelegate {
  /* the delegate is set in UIApplicationMain(), which is garaunteed to be called before this method */
  return (UIKitDelegate *)[[UIApplication sharedApplication] delegate];
}
static bool bAppActive  = false;

- (id)init
{
  self = [super init];
  window = nil;
  return self;
}

#ifdef IPHONE_USE_THREADS 
- (void)_runMainLoop:(UIApplication *)application
{
  /* run the user's application, passing argc and argv */
  int exit_status = UIKit_main(forward_argc, forward_argv);
  
  /* free the memory we used to hold copies of argc and argv */
  int i;
  for (i=0; i<forward_argc; i++) {
    free(forward_argv[i]);
  }
  free(forward_argv);	
    
  /* exit, passing the return status from the user's application */
  exit(exit_status);
}
#else
- (void)_runFrame:(NSTimer *)timer
{
   if (bAppActive)
   {
     UIKit_updateframe();
   }
}
#endif // IPHONE_USE_THREADS



- (void)Main
{
  
  [[NSFileManager defaultManager] changeCurrentDirectoryPath: [[NSBundle mainBundle] resourcePath]];
  
  UIWindow *uiwindow = [UIKitDelegate sharedAppDelegate].window;
  if (!uiwindow)
  {
    uiwindow = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    [UIKitDelegate sharedAppDelegate].window = uiwindow;    
  }

  UIImage * img;

  if ([[UIScreen mainScreen] bounds].size.width == 1024 || [[UIScreen mainScreen] bounds].size.height == 1024)
  {
    img = [UIImage imageNamed:@"Default-Portrait~ipad"];
  }
  else
    if ([[UIScreen mainScreen] bounds].size.width == 568 || [[UIScreen mainScreen] bounds].size.height == 568)
    {
      img = [UIImage imageNamed:@"Default-568h"];
    }
    else
    
  {
    img = [UIImage imageNamed:@"Default"];
  }
  
  splashImageView = [[UIImageView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
  splashImageView.image = img;
  splashImageView.contentMode = UIViewContentModeScaleToFill;//UIViewContentModeTopLeft;
  
  [self.window addSubview:splashImageView];
  [self.window makeKeyAndVisible];

  NSTimer * startEngine = [NSTimer timerWithTimeInterval:1 target:self selector:@selector(Main1) userInfo:nil repeats:false];
  [[NSRunLoop mainRunLoop] addTimer:startEngine forMode:NSRunLoopCommonModes];
}

- (void)Main1
{
#ifdef IPHONE_USE_THREADS	
  // Start rendering thread
  [NSThread detachNewThreadSelector:@selector(_runMainLoop:) toTarget:self withObject:nil]; 
#else

  [splashImageView removeFromSuperview];
  self.window = nil;
  
  WinMain(0, 0, forward_argv, forward_argc);
  bAppActive = true;

  //[Alexey] Reverted back to 30 fps, because higher timer fire causes serious lags in input! DO NOT CHANGE!
  [NSTimer scheduledTimerWithTimeInterval: 1.0f/30.0f
                                   target:self
                                 selector:@selector(_runFrame:)
                                 userInfo:nil
                                  repeats:YES];
  
#endif
  

  //[splashImageView release];
  //[window makeKeyAndVisible];		
}



- (void)applicationDidFinishLaunching:(UIApplication *)application
 {
   
   //[self performSelector:@selector(Main) withObject:nil afterDelay:0.0]; 
   [self performSelectorOnMainThread:@selector(Main) withObject:nil waitUntilDone:true];//:@selector(Main) withObject:nil afterDelay:0.0]; 
   
 }

- (void)applicationWillTerminate:(UIApplication *)application {
  
  //UIKit_SendQuit();
  
}

- (void)applicationWillResignActive:(UIApplication *)application
{
  UIKit_ApplicationWillResignActive();
  bAppActive = false;
}

- (void)applicationDidEnterBackground:(UIApplication *)application 
{
  UIKit_ApplicationDidEnterBackground();
  bAppActive = false;
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
  UIKit_ApplicationDidBecomeActive();
  bAppActive = true;
}

- (void)applicationWillEnterForeground:(UIApplication *)application 
{
  UIKit_ApplicationWillEnterForeground();
  bAppActive = true;
}

-(void)applicationDidReceiveMemoryWarning:(UIApplication *)application
{
  UIKit_ApplicationMemoryWarning();
}

-(void)dealloc
{
  [rootViewController release];
  [window release];
  [super dealloc];
}

-(void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
  NSDictionary * dict = [[NSDictionary alloc] initWithObjectsAndKeys:deviceToken, @"Data", nil];
  [[NSNotificationCenter defaultCenter] postNotificationName:@"didRegisterForRemoteNotificationsWithDeviceToken" object:application userInfo:dict];
}

-(void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
  NSDictionary * dict = [[NSDictionary alloc] initWithObjectsAndKeys:error, @"Error", nil];
  [[NSNotificationCenter defaultCenter] postNotificationName:@"didFailToRegisterForRemoteNotificationsWithError" object:application userInfo:dict];
}

-(void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
  [[NSNotificationCenter defaultCenter] postNotificationName:@"didReceiveRemoteNotification" object:application userInfo:userInfo];
}

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
  if(pApplicationhandleOpenURL)
    return (BOOL)pApplicationhandleOpenURL(url);
  
  return TRUE;//[super application:application handleOpenURL:url];
}

//
//- (BOOL)application:(UIApplication *)application willFinishLaunchingWithOptions:(NSDictionary *)launchOptions
//{
//  return TRUE;
//}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  BOOL bStart = TRUE;
  
  if (pUIKit_ApplicationdidFinishLaunchingWithOptions)
    bStart = pUIKit_ApplicationdidFinishLaunchingWithOptions(launchOptions);

  if (bStart)
     [self performSelectorOnMainThread:@selector(Main) withObject:nil waitUntilDone:true];
  
  return bStart;}

static void UIKit_ReadSettingsPreferences()
{
}

static void UIKit_SaveSettingsPreferences()
{
}


lpUIKIT_Main pUIKIT_Main = 0;

@end
