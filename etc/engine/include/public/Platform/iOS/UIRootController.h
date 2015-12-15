#import <UIKit/UIKit.h>
#import "UIKitOpenglView.h"

@interface UIRootController : UIViewController<UIGestureRecognizerDelegate> 
{
  UIKitOpenglView *glView;
  UILabel         *myLabel;
}

-(void)doModal : (BOOL)bModal  hiddenGL:(BOOL)hiddenGL;

@property(nonatomic,retain) UIKitOpenglView* glView;
@property(nonatomic,retain) UILabel *myLabel;

@end
