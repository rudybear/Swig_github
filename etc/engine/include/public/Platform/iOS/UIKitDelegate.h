#import <UIKit/UIKit.h>
#import "UIKitOpenglView.h"
#import "UIRootController.h"

/* *INDENT-OFF* */
@interface UIKitDelegate : NSObject<UIApplicationDelegate>
{
  IBOutlet UIWindow *window;
  IBOutlet UIRootController *rootViewController;
  UIImageView * splashImageView;
}

- (void)Main;

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) UIRootController *rootViewController;


+(UIKitDelegate *)sharedAppDelegate;

@end
/* *INDENT-ON* */
