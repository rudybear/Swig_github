#include "Engine2.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Engine2", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Engine2", __VA_ARGS__))


#include <jni.h>
//#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android/log.h>
#include "android_native_app_glue.h"

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


#define ANDROID_NDK

#include "Public/Common/Common.h"
#include "Public/Common/STLAllocator.h"
#include "Public/Common/Mathlib.h"
#include "Public/Core/ICore.h"

#include "Public/Core/IScene.h"
#include "Public/Core/IAnimatedMesh.h"
#include "Public/Render/IRender.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))


enum {
	// Numbering matters here, as we use >/< for state hierarchy
	NV_UNINITIALIZED = 0,
	NV_INITIALIZED = 1,
	NV_HAS_SURFACE = 2,
	NV_IS_BOUND = 3
};

enum {
	// the clock timing mode
	NV_TIME_MODE_INIT,
	NV_TIME_MODE_SYSTEM,
	NV_TIME_MODE_EGL
};

#ifndef EGL_NV_system_time
#define EGL_NV_system_time 1
typedef khronos_uint64_t EGLuint64NV;
#ifdef EGL_EGLEXT_PROTOTYPES
EGLAPI EGLuint64NV EGLAPIENTRY eglGetSystemTimeFrequencyNV(void);
EGLAPI EGLuint64NV EGLAPIENTRY eglGetSystemTimeNV(void);
#endif
typedef EGLuint64NV(EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC)(void);
typedef EGLuint64NV(EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC)(void);
#endif

struct saved_state {
	float angle;
	int32_t x;
	int32_t y;
};


unsigned int m_status;

long m_lastQueriedTime;
long m_accumulatedTime;
PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC m_eglGetSystemTimeFrequencyNVProc;
PFNEGLGETSYSTEMTIMENVPROC m_eglGetSystemTimeNVProc;
EGLuint64NV m_eglSystemTimeFrequency;
struct timeval m_startTime;
bool m_nvTimeExtensionQueried;
int m_timeMode;

struct engine {
	struct android_app* app;

	ASensorManager* sensorManager;
	const ASensor* accelerometerSensor;
	ASensorEventQueue* sensorEventQueue;

	int animating;
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	int32_t width;
	int32_t height;
	struct saved_state state;
};

engine *  g_engine = 0;

WIN_HWND getWIN_HWND()
{
	return (WIN_HWND)g_engine->app->window;
}


/**
* Initialize an EGL context for the current display.
*/
static int engine_init_display(struct engine* engine) {

#if EMPTY_TEST
	//return 0;
	// initialize OpenGL ES and EGL

	/*
	* Here specify the attributes of the desired configuration.
	* Below, we select an EGLConfig with at least 8 bits per color
	* component compatible with on-screen windows
	*/
	LOGI("engine_init_display");
	const EGLint attribs[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		//EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
		//EGL_BLUE_SIZE, 8,
		//EGL_GREEN_SIZE, 8,
		//EGL_RED_SIZE, 8,
		//            EGL_CONFIG_CAVEAT, EGL_SLOW_CONFIG,
		//EGL_CONFIG_CAVEAT, EGL_NON_CONFORMANT_CONFIG,
		EGL_NONE
	};
	EGLint w, h, dummy, format;
	EGLint numConfigs;
	EGLConfig config[32];
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	EGLBoolean bRes = eglInitialize(display, 0, 0);

	/* Here, the application chooses the configuration it desires. In this
	* sample, we have a very simplified selection process, where we pick
	* the first EGLConfig that matches our criteria */
	bRes = eglChooseConfig(display, attribs, config, 32, &numConfigs);

	/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
	* guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
	* As soon as we picked a EGLConfig, we can safely reconfigure the
	* ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */

	int finalConfig = -1;
	for (int i = 0; i < numConfigs; ++i)
	{
		bRes = eglGetConfigAttrib(display, config[i], EGL_NATIVE_VISUAL_ID, &format);

		if (format == 1)
		{
			finalConfig = i;
			break;
		}

	}


	if (finalConfig == -1)
	{
		LOGW("Unable to find a proper config");
		return -1;
	}

	int iRes = ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config[finalConfig], engine->app->window, NULL);

	context = eglCreateContext(display, config[finalConfig], NULL, NULL);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
		LOGW("Unable to eglMakeCurrent");
		return -1;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	engine->display = display;
	engine->context = context;
	engine->surface = surface;
	engine->width = w;
	engine->height = h;
	engine->state.angle = 0;

	// Initialize GL state.
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glEnable(GL_CULL_FACE);
	//glShadeModel(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);

	LOGI("engine_init_display done");
#endif
	return 0;
}

extern int FM_updateframe(int nFlags);

/**
* Just the current frame in the display.
*/


static void startEngine()
{
#if EMPTY_TEST
	return;
#endif
	LOGI("startEngine");
	if (g_engine && g_engine->app && g_engine->app->activity && g_engine->app->activity->vm)
	{

		JNIEnv *pEnv = g_engine->app->activity->env;
		jint res = g_engine->app->activity->vm->AttachCurrentThread(&pEnv, NULL);

		LOGI("startEngine 1");
		//JNIEnv *pEnv = 0;
		//jint res = g_engine->app->activity->vm->GetEnv((void**)&pEnv, JNI_VERSION_1_2);
		//if (res == JNI_EDETACHED)
		//{
		//	pEnv = 0;
		//	res = g_engine->app->activity->vm->AttachCurrentThread(&pEnv, 0);
		//	if (res == 0) { pEnv = 0; }
		//}
		LOGI("startEngine 2");
		if (res == JNI_OK && pEnv)
		{
			LOGI("startEngine 3");
			jobject activityObject = g_engine->app->activity->clazz;
			jclass  activityClass = pEnv->GetObjectClass(activityObject);

			jmethodID senEnable = pEnv->GetMethodID(activityClass, "StartEngine", "()V");
			pEnv->CallVoidMethod(activityObject, senEnable);
			LOGI("startEngine 4");
			pEnv->DeleteLocalRef(activityClass);

			g_engine->app->activity->vm->DetachCurrentThread();
		}
	}
}


static void engine_draw_frame(struct engine* engine) {

	//FM_updateframe(1);

	//LOGI("engine_draw_frame");
#if !EMPTY_TEST
	if (g_engine && g_engine->app && g_engine->app->activity && g_engine->app->activity->vm)
	{
		static jmethodID senEnable = 0;
		if (!senEnable)
		{
			JNIEnv *pEnv = g_engine->app->activity->env;
			jint res = g_engine->app->activity->vm->AttachCurrentThread(&pEnv, NULL);

			//LOGI("engine_draw_frame 1");
			if (res == JNI_OK && pEnv)
			{
				//LOGI("engine_draw_frame 3");
				jobject activityObject = g_engine->app->activity->clazz;
				jclass  activityClass = pEnv->GetObjectClass(activityObject);

				jmethodID senEnable = pEnv->GetMethodID(activityClass, "FrameEngine", "()V");
				pEnv->CallVoidMethod(activityObject, senEnable);
				//LOGI("engine_draw_frame 4");
				pEnv->DeleteLocalRef(activityClass);

				//g_engine->app->activity->vm->DetachCurrentThread();
			}

		}
		else
		{
			JNIEnv *pEnv = g_engine->app->activity->env;
			jobject activityObject = g_engine->app->activity->clazz;
			pEnv->CallVoidMethod(activityObject, senEnable);
		}
	}

	return;
#else

	//LOGI("Frametime:%d", getSystemTime());
	//g_pCore->Frame(TRUE);
	if (engine->display == NULL) {
	//    // No display.
	    return;
	}

	//// Just fill the screen with a color.
	glClearColor(((float)engine->state.x)/engine->width, engine->state.angle,
	        ((float)engine->state.y)/engine->height, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	eglSwapBuffers(engine->display, engine->surface);
#endif
}

/**
* Tear down the EGL context currently associated with the display.
*/
static void engine_term_display(struct engine* engine) {

	LOGI("engine_term_display");
	//if (engine->display != EGL_NO_DISPLAY) {
	//	eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	//	if (engine->context != EGL_NO_CONTEXT) {
	//		eglDestroyContext(engine->display, engine->context);
	//	}
	//	if (engine->surface != EGL_NO_SURFACE) {
	//		eglDestroySurface(engine->display, engine->surface);
	//	}
	//	eglTerminate(engine->display);
	//}
	//engine->animating = 0;
	//engine->display = EGL_NO_DISPLAY;
	//engine->context = EGL_NO_CONTEXT;
	//engine->surface = EGL_NO_SURFACE;
}

/**
* Process the next input event.
*/
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
	struct engine* engine = (struct engine*)app->userData;
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		engine->animating = 1;
		engine->state.x = AMotionEvent_getX(event, 0);
		engine->state.y = AMotionEvent_getY(event, 0);
		return 1;
	}
	return 0;
}

/**
* Process the next main command.
*/
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
	struct engine* engine = (struct engine*)app->userData;
	switch (cmd) {
	case APP_CMD_SAVE_STATE:
		// The system has asked us to save our current state.  Do so.
		engine->app->savedState = malloc(sizeof(struct saved_state));
		*((struct saved_state*)engine->app->savedState) = engine->state;
		engine->app->savedStateSize = sizeof(struct saved_state);
		break;
	case APP_CMD_INIT_WINDOW:
		// The window is being shown, get it ready.
		if (engine->app->window != NULL) {
			engine_init_display(engine);
// INITIALIZE C# code here
			startEngine();
			engine_draw_frame(engine);
			engine->animating = 1;
		}
		break;
	case APP_CMD_TERM_WINDOW:
		// The window is being hidden or closed, clean it up.
		engine_term_display(engine);
		break;
	case APP_CMD_GAINED_FOCUS:
		// When our app gains focus, we start monitoring the accelerometer.
		if (engine->accelerometerSensor != NULL) {
			ASensorEventQueue_enableSensor(engine->sensorEventQueue,
				engine->accelerometerSensor);
			// We'd like to get 60 events per second (in us).
			ASensorEventQueue_setEventRate(engine->sensorEventQueue,
				engine->accelerometerSensor, (1000L / 60) * 1000);
		}
		break;
	case APP_CMD_LOST_FOCUS:
		// When our app loses focus, we stop monitoring the accelerometer.
		// This is to avoid consuming battery while not being used.
		if (engine->accelerometerSensor != NULL) {
			ASensorEventQueue_disableSensor(engine->sensorEventQueue,
				engine->accelerometerSensor);
		}
		// Also stop animating.
		engine->animating = 0;
		//            engine_draw_frame(engine);
		break;
	}
}



/**
* This is the main entry point of a native application that is using
* android_native_app_glue.  It runs in its own thread, with its own
* event loop for receiving input events and doing other things.
*/
void android_main(struct android_app* state) {
	struct engine engine;

	LOGI("engine2: android_main");

	LOGI("DAta internal path:%s", state->activity->internalDataPath);
	LOGI("DAta external path:%s", state->activity->externalDataPath);

	m_lastQueriedTime = 0;
	m_accumulatedTime = 0;
	gettimeofday(&m_startTime, 0);
	m_eglGetSystemTimeFrequencyNVProc = NULL;
	m_eglGetSystemTimeNVProc = NULL;
	m_eglSystemTimeFrequency = 0;
	m_nvTimeExtensionQueried = false;
	m_timeMode = NV_TIME_MODE_INIT;



	//6sleep(10000);
	g_engine = &engine;

	// Make sure glue isn't stripped.
	//app_dummy();

	memset(&engine, 0, sizeof(engine));
	state->userData = &engine;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input;
	engine.app = state;
	engine.animating = 0;

	// Prepare to monitor accelerometer
	engine.sensorManager = ASensorManager_getInstance();
	engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
		ASENSOR_TYPE_ACCELEROMETER);
	engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
		state->looper, LOOPER_ID_USER, NULL, NULL);

	if (state->savedState != NULL) {
		// We are starting with a previous saved state; restore from it.
		engine.state = *(struct saved_state*)state->savedState;
	}



	// loop waiting for stuff to do.

	while (1) {
		// Read all pending events.
		int ident;
		int events;
		struct android_poll_source* source;

		// If not animating, we will block forever waiting for events.
		// If animating, we loop until all events are read, then continue
		// to draw the next frame of animation.
		while ((ident = ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
			(void**)&source)) >= 0) {

			// Process this event.
			if (source != NULL) {
				source->process(state, source);
			}

			// If a sensor has data, process it now.
			if (ident == LOOPER_ID_USER) {
				if (engine.accelerometerSensor != NULL) {
					ASensorEvent event;
					while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
						&event, 1) > 0) {
						//                        LOGI("accelerometer: x=%f y=%f z=%f",
						//                                event.acceleration.x, event.acceleration.y,
						//                                event.acceleration.z);
					}
				}
			}

			// Check if we are exiting.
			if (state->destroyRequested != 0) {
				engine_term_display(&engine);
				return;
			}
		}

		if (engine.animating) {
			// Done with events; draw next animation frame.
			engine.state.angle += .01f;
			if (engine.state.angle > 1) {
				engine.state.angle = 0;
			}

			// Drawing is throttled to the screen update rate, so there
			// is no need to do timing here.
			engine_draw_frame(&engine);
		}
	}
}
