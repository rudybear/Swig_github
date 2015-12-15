#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>

//#define UIKit_IPHONE_KEYBOARD 1
#define IPHONE_MULTIPLE_MICE 1

#if IPHONE_MULTIPLE_MICE
#define MAX_SIMULTANEOUS_TOUCHES 4
#else
#define MAX_SIMULTANEOUS_TOUCHES 1
#endif

typedef struct IPhoneMouse IPhoneMouse;
struct IPhoneMouse
{
  int id;
  UITouch *data;
};

/* *INDENT-OFF* */
@interface UIKitView : UIView<UITextFieldDelegate, UIGestureRecognizerDelegate, UIAccelerometerDelegate> {

  IPhoneMouse mice[MAX_SIMULTANEOUS_TOUCHES];

  float _accelerationX, _accelerationY, _accelerationZ;
  float _accelYaw;
  float _accelRoll;
  float _accelPitch;
  int _gameActive;

  float _orientation;
  
  CMMotionManager *motionManager;

  UITapGestureRecognizer * tapRecognizers[10];
  UISwipeGestureRecognizer *swipeLeft;
  UISwipeGestureRecognizer *swipeUp;
  UISwipeGestureRecognizer *swipeRight;
  UISwipeGestureRecognizer *swipeDown;
  
  //CMAttitude *referenceAttitude;
  
#if UIKit_IPHONE_KEYBOARD
  UITextField *textField;
  BOOL keyboardVisible;
#endif	

}
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration;
- (void)createTapRecognizer:(int)num;
- (void)deleteTapRecognizer:(int)num;

#if UIKit_IPHONE_KEYBOARD
- (void)showKeyboard;
- (void)hideKeyboard;
- (void)initializeKeyboard;
@property (readonly) BOOL keyboardVisible;
#endif 

@end
/* *INDENT-ON* */
