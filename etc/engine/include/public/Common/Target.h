///////////////////////////////////////////////////////////////////////////////
//
// You MUST supply one of the following defines:
//		__FORWINDOWS__		- For Windows
//		__FORDOS__			- For DOS
//		__FOROS2__			- For OS/2
//		__FORUNIX__			- For unix
//		__FORLINUX__		- For Linux-environment
//      __FORMACOS__        - For Mac OS envinronment
//
// If your target platform is DOS or WINDOWS, then you can simply define
//		__FORDOS__
//		__FORWINDOWS__
// Then this file will try to determine what word size and processor is
// used.
//
// You may also specify your processor platform:
//		__FORx86__			- Intel 80x86
//		__FORSPARC__		- Sun SPARC
//		__FORRx000__		- MIPS Rx000
//		__FORPPC__			- Power PC
//		__FORALPHA__		- DEC Alpha
// Note that the processor is detected automatically when compiling for
// Windows or DOS. (The later one must be an Intel !)
//
// Often it is helpfull to know about the byte-ordering. Here you can
// define:
//		__LSBFIRST__		- Like Intel,MIPS
//		__MSBFIRST__		- Like SPARC, Motorola
//
// You may also need the floating point format:
//		__FPIEEE__			- Like Intel
//		__FPIBM__			- For IBM workstations
//		__FPVAX__
//		__FPCRAY__
//
// And your compiler:
//		__FORBORLAND__		- Borland C++
//		__FORVISUAL__		- Microsoft Visual C++
//		__FORGNU__			- GNU C++
//		__FORWATCOM__		- Watcom Compiler
//
// UNIX-Options are:
//		__FORX11__			- For unix with X-Windows
//
// One important note for Windows users: If you want to write a portable
// program using void main(void), then you should not define __WINMAIN__,
// but if your program contains an own WinMain function, you MUST define
// __WINMAIN__, so GApplication will not define its own WinMain function !
//
// Notes for usage of threads: Threads will only be available, if the symbol
// __THREADS__ is defined (this is done automatically by Gomez depending on
// you compiling environment). If you use the Borland or Microsoft compiler,
// I suggest to enable the thread library.
//


#ifndef __TARGETSYSTEM_H
#define __TARGETSYSTEM_H

//#define max(a,b)    (((a) > (b)) ? (a) : (b))
//#define min(a,b)    (((a) < (b)) ? (a) : (b))

// Autodetect Borland compiler
# if defined(__BORLANDC__)
#	define __FORBORLAND__
#	if (defined(_Windows) || defined(_WINDOWS) || defined(WIN32))
#		define __FORWINDOWS__
#	else
#		define __FORDOS__
#	endif
# endif

// Autodetect MS-C
# if defined(_MSC_VER)
#	define __FORVISUAL__
#	if (defined(_Windows) || defined(_WINDOWS) || defined(WIN32))
#		define __FORWINDOWS__
#	else
#		define __FORDOS__
#	endif
# endif

// Autodetect GNUC
# ifdef __GNUC__
#	define __FORGNU__
# endif

// Autodetect iPhone
#if !defined(__MAC_OS_X_VERSION_MAX_ALLOWED) &&  defined(__GNUC__) && ( defined(__APPLE_CPP__) || defined(__APPLE_CC__) || defined(__MACOS_CLASSIC__) )
#          define __FORIPHONE__
#endif


#if defined(__MAC_OS_X_VERSION_MAX_ALLOWED)
#define __FORMACOS__
#endif

// Autodetect Linux
# ifdef __linux__
#	define __FORLINUX__
# endif

#ifdef EMSCRIPTEN
#define __FOREMSCRIPTEN__
#endif

// Enable UNIX if X11 or MOTIF selected
# if defined(__FORX11__) && !defined(__FORUNIX__)
#	define __FORUNIX__
# endif


// Enable UNIX if Linux
# if defined(__FORLINUX__) && !defined(__FORUNIX__)
#	define __FORUNIX__
# endif

// Enable UNIX and X11 if IRIX
# if defined(__FORIRIX__) && !defined(__FORUNIX__)
#	define __FORUNIX__
# endif
# if defined(__FORIRIX__) && !defined(__FORX11__)
#	define __FORX11__
# endif


# if defined (__FORDOS__)
#	define __CONSOLE__
#	define __32BIT__
#	define __THREADS__
#	if defined(_M_IX86)
#		define __FORx86__				// Intel 80x86
#	elif defined(_M_MRX000)
#		define __FORRx000__			// MIPS Rx000
#	elif defined(_M_ALPHA)
#		define __FORALPHA__			// DEC Alpha
#	elif defined(_M_PPC)
#		define __FORPPC__				// Power PC
#	else
#		define __FORx86__				// Intel 80x86
#	endif
# elif defined (__FORWINDOWS__)		// For Windows NT
#	define __32BIT__
#	define __LONGLONG__
#	define __THREADS__
#	if (defined(_DEBUG) || defined(_Debug))
#		define __FORDEBUG__
#	endif
#	if defined(_M_IX86)
#		define __FORx86__				// Intel 80x86
#	elif defined(_M_MRX000)
#		define __FORRx000__			// MIPS Rx000
#	elif defined(_M_ALPHA)
#		define __FORALPHA__			// DEC Alpha
#	elif defined(_M_PPC)
#		define __FORPPC__				// Power PC
#	else
#		define __FORx86__				// Intel 80x86
#	endif
# elif defined (__FOROS2__)     		// OS/2
#	define __32BIT__
#	define __FORx86__
#	define __THREADS__
# elif defined (__FORLINUX__) 		// Linux
#	define __THREADS__
#	define __LONGLONG__
#	define __NATIVETLS__
# elif defined (__FOREMSCRIPTEN__)
#	define __32BIT__
#	define __LONGLONG__
# elif defined (__FORUNIX__) 		// UNIX
#	define __32BIT__
#	define __THREADS__
# elif defined (__FORIPHONE__) 		// IPHONE
#	define __32BIT__
#	define __THREADS__
#	if (defined(_DEBUG) || defined(_Debug))
#		define __FORDEBUG__
#	endif
#elif defined(__FORMACOS__)
#	define __32BIT__
#	define __THREADS__
#else
#	error You must define __FOR???__ for your target platform !
#endif


// Check Byte ordering
# if defined (__FORx86__)
#	define __LSBFIRST__
#	define __FPIEEE__
# elif defined (__FORRx000__)
#	define __LSBFIRST__
# elif defined (__FORSPARC__)
#	define __MSBFIRST__
# endif

// Check for native TLS support in compiler
# if defined(__FORVISUAL__)
#	define __NATIVETLS__
# endif


# if defined(__FORWINDOWS__)
#   ifdef STRICT
#    undef STRICT
#   endif
#	define STRICT 1
#	define WIN32_LEAN_AND_MEAN
#	ifndef WINVER
#		define WINVER 0x0500
#	endif
#	ifndef _WIN32_WINDOWS
#		define _WIN32_WINDOWS 0x0410	// Windows 98
#	endif
#	ifndef _WIN32_WINNT
#		define _WIN32_WINNT 0x500		// Windows NT 4.0
#	endif
#	define _WINSOCKAPI_				// Prevents inclusion of Winsock 1.0 API
#	define NOSERVICE
#	define NOMCX
#	define NOSOUND
#	define NOMETAFILE
#	define NONLS 
#	define NOMINMAX
#	include <windows.h>
# endif

// Some compilers just take our inline definitions not serious enough
#if defined(__FORVISUAL__)
//#	pragma inline_depth(64)
//#	pragma inline_recursion(on)
#if _MSC_VER < 1700 
#	define inline __forceinline
#endif
#
#	pragma warning(disable:4100)	// Unreferenced formal parameter
#	pragma warning(disable:4127)	// conditional expression is constant
#	pragma warning(disable:4284)	// return type for 'identifier::operator ñ>' is not a UDT or reference to a UDT.
#	pragma warning(disable:4355)	// 'this' : used in base member initializer list
#	pragma warning(disable:4505)	// unreferenced local function has been removed
#	pragma warning(disable:4510)	// default constructor could not be generated
#	pragma warning(disable:4511)	// copy constructor could not be generated
#	pragma warning(disable:4512)	// assignment operator could not be generated
#	pragma warning(disable:4610)	// object 'class' can never be instantiated 
#	pragma warning(disable:4714)	// function marked as __forceinline not inlined
#	pragma warning(disable:4786)	// identifier was truncated to 'number' characters in the debug information
#
//#   define _CRT_SECURE_NO_DEPRECATE
#   pragma warning(disable:4996)	// Function is deprecated
#endif


#define __FOROPENGL__		13

#if defined (__FORIPHONE__) || defined (__FORWINDOWS__)
//#include "SDL.h"
//#define HAVE_SDL 1
#endif

#ifdef __FORWINDOWS__
#define strcasecmp stricmp
#define strncasecmp strnicmp
#endif

#define STRIP_CLASS_INFO 1

#if defined(__FORIPHONE__)
#define __declspec(x)
#define __stdcall
#define __cdecl

#define WINDOW_NOTHREADS 1
#define STRIP_CLASS_INFO 1

#include <string.h>
#include <alloca.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/types.h>

struct FILETIME
{
  unsigned int dwLowDateTime;
  unsigned int dwHighDateTime;
};

#ifdef __cplusplus
//extern "C" int UIKit_main(int argc, char **argv);
//extern "C" int UIKit_initapp(int argc, char **argv);
//extern "C" int UIKit_updateframe(int nFlags);
extern "C" int WinMain(int, int, char *, int); 
#endif

#endif

#ifdef __cplusplus
//extern "C" int WinMain(int, int, char *, int); 
//extern "C" void UIKit_setOrientation(float fOrientation);
//extern "C" void UIKit_gameState(int nState);
#endif


#endif
