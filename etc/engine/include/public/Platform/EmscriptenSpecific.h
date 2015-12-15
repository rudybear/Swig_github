#pragma once
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include <SDL/SDL_keycode.h>
#include <unistd.h>
#include <stdlib.h>

typedef int errno_t;

#define __cdecl 
#ifndef APIENTRY
#define APIENTRY
#endif

#define WIN_HWND int
#define WIN_HINSTANCE int

struct POINT
{
  int x;
  int y;
};

#define WM_MOUSEMOVE 1
#define WM_LBUTTONDOWN 2
#define WM_LBUTTONUP 3
#define WM_RBUTTONDOWN 4
#define WM_RBUTTONUP 5
#define WM_MBUTTONDOWN 6
#define WM_MBUTTONUP 7
#define WM_CHAR 8 
#define WM_KEYDOWN 9
#define WM_KEYUP 10
#define WM_MOUSEWHEEL 11
#define WM_MOUSEACTIVATE 12
#define WM_MOUSELEAVE 13

#define VK_RETURN SDLK_RETURN
#define VK_ESCAPE SDLK_ESCAPE
#define VK_BACK SDLK_BACKSPACE
#define VK_TAB SDLK_TAB
#define VK_SPACE SDLK_SPACE
#define VK_INSERT SDLK_INSERT
#define VK_DELETE SDLK_DELETE
#define VK_PRIOR SDLK_PAGEUP
#define VK_NEXT SDLK_PAGEDOWN
#define VK_HOME SDLK_HOME
#define VK_END SDLK_END
#define VK_F1 SDLK_F1
#define VK_F2 SDLK_F2
#define VK_F3 SDLK_F3
#define VK_F4 SDLK_F4
#define VK_F5 SDLK_F5
#define VK_F6 SDLK_F6
#define VK_F7 SDLK_F7
#define VK_F8 SDLK_F8
#define VK_F9 SDLK_F9
#define VK_F10 SDLK_F10
#define VK_F11 SDLK_F11
#define VK_F12 SDLK_F12
#define VK_1 SDLK_1
#define VK_2 SDLK_2
#define VK_3 SDLK_3
#define VK_4 SDLK_4
#define VK_5 SDLK_5
#define VK_6 SDLK_6
#define VK_7 SDLK_7
#define VK_8 SDLK_8
#define VK_9 SDLK_9
#define VK_0 SDLK_0
#define VK_LEFT SDLK_LEFT
#define VK_RIGHT SDLK_RIGHT
#define VK_UP SDLK_UP
#define VK_DOWN SDLK_DOWN
#define VK_SHIFT SDLK_LSHIFT
#define VK_LSHIFT SDLK_LSHIFT
#define VK_RSHIFT SDLK_RSHIFT
#define VK_MENU SDLK_LALT
#define VK_LMENU SDLK_LALT
#define VK_RMENU SDLK_RALT
#define VK_CONTROL SDLK_LCTRL
#define VK_LCONTROL SDLK_LCTRL
#define VK_RCONTROL SDLK_RCTRL
#define VK_LBUTTON (SDLK_LAST+1)
#define VK_RBUTTON (SDLK_LAST+2)
#define VK_MBUTTON (SDLK_LAST+3)

FORCEINLINE bool _isnan( float value ) 
{
    return ((*(unsigned int*)&value) & 0x7fffffff) > 0x7f800000; 
} 


// TODO: make template version to handle string length
//FORCEINLINE int fopen_s(FILE ** file, const char * name, const char * mode)
//{
//    
//    *file = fopen(name, mode);
//    return *file == 0 ? -1 : 0; 
//}

FORCEINLINE int strncpy_s(char * output, const char * input, size_t len)
{
    strncpy(output, input, len);
    
    return 0;
}


#define _stricmp strcasecmp
#define scanf_s scanf
#define sscanf_s sscanf
#define sprintf_s sprintf
#define _itoa_s itoa

FORCEINLINE int vsnprintf_s(char *buf,
                            int /*bufSize - not used*/,
                            int size,
                            const char *format,
                            va_list ap)
{
	int res = vsnprintf(buf, size, format, ap);
	buf[size - 1] = 0;
	return res;
}

FORCEINLINE long _InterlockedDecrement(int volatile* value)
{
	return --*value;
}

FORCEINLINE long _InterlockedIncrement(int volatile* value)
{
	return ++*value;
    
}

FORCEINLINE long _InterlockedDecrement(long volatile* value)
{
	return --*value;
}

FORCEINLINE long _InterlockedIncrement(long volatile* value)
{
	return ++*value;
}

#define  InterlockedIncrement _InterlockedIncrement
#define  InterlockedDecrement _InterlockedDecrement

FORCEINLINE long _InterlockedExchangeAdd(int volatile* value , int inc)
{
	int oldValue = *value;
	*value += inc;
	return oldValue;
}

FORCEINLINE long _InterlockedExchangeAdd(long volatile* value , long inc)
{
	int oldValue = *value;
	*value += inc;
	return oldValue;
	
}


FORCEINLINE long _InterlockedCompareExchange(long volatile* destination , long exchange, long comparand)
{
	int dest = (int)*destination;
	if (*destination == comparand)
		*destination = exchange;
	return dest;
}


#define InterlockedExchangeAdd _InterlockedExchangeAdd

#include <pthread.h>
typedef pthread_mutex_t CRITICAL_SECTION;

FORCEINLINE void _debugbreak()
{   
}

typedef void ( *LPOVERLAPPED_COMPLETION_ROUTINE )( 
                                                  unsigned long dwErrorCode,
                                                  unsigned long dwNumberOfBytesTransfered,
                                                  void * lpOverlapped);


typedef enum {INVALID_HANDLE_VALUE = -1l}INVALID_HANDLE_VALUE_ENUM;
//for compatibility reason we got to create a class which actually contains an int rather than a void* and make sure it does not get mistreated
template <class T, T U>//U is default type for invalid handle value, T the encapsulated handle type to be used instead of void* (as under windows and never linux)
class CHandle
{
public:
	typedef T			HandleType;
	typedef void* PointerType;	//for compatibility reason to encapsulate a void* as an int
    
	static const HandleType sciInvalidHandleValue = U;
    
	CHandle(const CHandle<T,U>& cHandle) : m_Value(cHandle.m_Value){}
	CHandle(const HandleType cHandle = U) : m_Value(cHandle){}
	CHandle(const PointerType cpHandle) : m_Value(reinterpret_cast<HandleType>(cpHandle)){}
	CHandle(INVALID_HANDLE_VALUE_ENUM) : m_Value(U){}//to be able to use a common value for all InvalidHandle - types
#if defined(LINUX64)
	//treat __null tyope also as invalid handle type
	CHandle(typeof(__null)) : m_Value(U){}//to be able to use a common value for all InvalidHandle - types
#endif
	operator HandleType(){return m_Value;}
	bool operator!() const{return m_Value == sciInvalidHandleValue;}
	const CHandle& operator =(const CHandle& crHandle){m_Value = crHandle.m_Value;return *this;}
	const CHandle& operator =(const PointerType cpHandle){m_Value = reinterpret_cast<HandleType>(cpHandle);return *this;}
	const bool operator ==(const CHandle& crHandle)		const{return m_Value == crHandle.m_Value;}
	const bool operator ==(const HandleType cHandle)	const{return m_Value == cHandle;}
	const bool operator ==(const PointerType cpHandle)const{return m_Value == reinterpret_cast<HandleType>(cpHandle);}
	const bool operator !=(const HandleType cHandle)	const{return m_Value != cHandle;}
	const bool operator !=(const CHandle& crHandle)		const{return m_Value != crHandle.m_Value;}
	const bool operator !=(const PointerType cpHandle)const{return m_Value != reinterpret_cast<HandleType>(cpHandle);}
	const bool operator <	(const CHandle& crHandle)		const{return m_Value < crHandle.m_Value;}
	HandleType Handle()const{return m_Value;}
    
private:
	HandleType m_Value;	//the actual value, remember that file descriptors are ints under linux
    
	typedef void	ReferenceType;//for compatibility reason to encapsulate a void* as an int
	//forbid these function which would actually not work on an int
	PointerType operator->();
	PointerType operator->() const;
	ReferenceType operator*();
	ReferenceType operator*() const;
	operator PointerType();
};

typedef CHandle<int, (int)-1l> HANDLE;

typedef struct _OVERLAPPED {
    unsigned long * Internal;
    unsigned long * InternalHigh;
    union {
        struct {
            unsigned long Offset;
            unsigned long OffsetHigh;
        };
        
        void * Pointer;
    };
    
    HANDLE  hEvent;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct tagRECT {
    long left;
    long top;
    long right;
    long bottom;
} RECT, * LPRECT;

typedef long HRESULT;

typedef timeval LARGE_INTEGER;

#include <malloc.h>

FORCEINLINE size_t _msize(void * ptr)
{
   assert (0);
   //return dlmalloc_usable_size(ptr);
   return 0;
}


#define S_OK 0
#define E_FAIL 0x80000008L
#define S_FALSE 0x00000001L
#define E_INVALIDARG 0x80000003L
#define E_OUTOFMEMORY 0x8007000EL


typedef unsigned int UINT;
typedef wchar_t WCHAR;

#ifndef FLT_EPSILON
#define FLT_EPSILON   1.192092896e-07F 
#endif

typedef time_t __time64_t;

#define _getcwd getcwd
#define _chdir chdir


typedef struct {
    int cx;
    int cy;
    
} SIZE;

#define _MAX_PATH 4096
#define MAX_PATH _MAX_PATH
#define CALLBACK 
#define Sleep sleep

#define WINAPI

#define override 

//typedef enum { INVALID_HANDLE_VALUE = -1l } INVALID_HANDLE_VALUE_ENUM;

#define GENERIC_READ    (0x80000000L)
#define GENERIC_WRITE   (0x40000000L)
#define GENERIC_EXECUTE (0x20000000L)
#define GENERIC_ALL     (0x10000000L)


//FIXME:!!!!!
FORCEINLINE double timeGetTime()
{
	timeval tv;
	gettimeofday(&tv, 0 );

	return (double)tv.tv_usec / 1000.0 + (double)tv.tv_sec * 1000;
}


typedef void VOID;
//#define INVALID_HANDLE_VALUE  -1l

FORCEINLINE char *ltoa ( long i , char *a , int radix )
{
	if ( a == NULL ) return NULL ;
	strcpy ( a , "0" ) ;
	if ( i && radix > 1 && radix < 37 ) {
		char buf[35] ;
		unsigned long u = i , p = 34 ;
		buf[p] = 0 ;
		if ( i < 0 && radix == 10 ) u = -i ;
		while ( u ) {
			unsigned long d = u % radix ;
			buf[--p] = d < 10 ? '0' + d : 'a' + d - 10 ;
			u /= radix ;
		}
		if ( i < 0 && radix == 10 ) buf[--p] = '-' ;
		strcpy ( a , buf + p ) ;
	}
	return a ;
}

#define ENOENT 2
#define FS_ERRNO_TYPE int
#define FS_ENOENT ENOENT
#define FS_EINVAL EINVAL
#define FS_EISDIR EISDIR
#define FS_DIRENT_TYPE struct dirent
#define FS_DIR_TYPE DIR *
#define FS_DIR_NULL (NULL)
#define FS_STAT_TYPE struct stat
#define FS_CLOSEDIR(dir, err) \
while (true) \
{ \
if (closedir((dir)) == 0) \
(err) = 0; \
else \
(err) = errno; \
break; \
}
#define FS_CLOSEDIR_NOERR(dir) (closedir((dir)))
#define FS_OPENDIR(dirname, dir, err) \
while (true) \
{ \
if (((dir) = opendir((dirname))) == NULL) \
(err) = errno; \
else \
(err) = 0; \
break; \
}
#define FS_READDIR(dir, ent, entsize, err) \
while (true) \
{ \
struct dirent *pDirent = readdir((dir)); \
if (pDirent == NULL) \
{ \
(entsize) = 0; \
(err) = (errno == ENOENT) ? 0 : errno; \
} \
else \
{ \
(ent) = *pDirent; \
(entsize) = sizeof(struct dirent); \
(err) = 0; \
} \
break; \
}
#define FS_TYPE_DIRECTORY DT_DIR
#define FS_STAT(filename, buffer, err) \
while (true) \
{ \
if (stat((filename), &(buffer)) == -1) \
(err) = errno; \
else \
(err) = 0; \
break; \
}
#define FS_FSTAT(fd, buffer, err) \
while (true) \
{ \
if (fstat((fd), &(buffer)) == -1) \
(err) = errno; \
else \
(err) = 0; \
break; \
}
#define FS_OPEN(filename, flags, fd, mode, err) \
while (true) \
{ \
if (((fd) = open((filename), (flags), (mode))) == -1) \
(err) = errno; \
else \
(err) = 0; \
break; \
}
#define FS_CLOSE(fd, err) \
while (true) \
{ \
if (close((fd)) == -1) \
(err) = errno; \
else \
(err) = 0; \
break; \
}
#define FS_CLOSE_NOERR(fd) (close((fd)))
#define FS_O_RDWR O_RDWR
#define FS_O_RDONLY O_RDONLY
#define FS_O_WRONLY O_WRONLY

#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5

#define FILE_SHARE_READ						0x00000001
#define FILE_SHARE_WRITE					0x00000002
#define OPEN_EXISTING							3
#define FILE_FLAG_OVERLAPPED			0x40000000
#define INVALID_FILE_SIZE					((DWORD)0xFFFFFFFFl)
#define FILE_BEGIN								0
#define FILE_CURRENT							1
#define FILE_END									2
#define ERROR_NO_SYSTEM_RESOURCES 1450L
#define ERROR_INVALID_USER_BUFFER	1784L
#define ERROR_NOT_ENOUGH_MEMORY   8L
#define ERROR_PATH_NOT_FOUND      3L
#define FILE_FLAG_SEQUENTIAL_SCAN 0x08000000

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
FORCEINLINE HANDLE CreateFile(
                              const char* lpFileName,
                              DWORD dwDesiredAccess,
                              DWORD dwShareMode,
                              void* lpSecurityAttributes,
                              DWORD dwCreationDisposition,
                              DWORD dwFlagsAndAttributes,
                              HANDLE hTemplateFile
                              )
{
	int flags = 0;
	int fd = -1;
	FS_ERRNO_TYPE fserr;
	bool create = false;
	HANDLE h;
    //#if !defined(PS3)
	if ((dwDesiredAccess & GENERIC_READ) == GENERIC_READ
		&& (dwDesiredAccess & GENERIC_WRITE) == GENERIC_WRITE)
		flags = O_RDWR;
	else if ((dwDesiredAccess & GENERIC_WRITE) == GENERIC_WRITE)
		flags = O_WRONLY;
	else
	{
		// On Windows files can be opened with no access. We'll map no access
		// to read only.
		flags = O_RDONLY;
	}
	if ((dwDesiredAccess & GENERIC_WRITE) == GENERIC_WRITE)
        //#endif
	{
		switch (dwCreationDisposition)
		{
            case CREATE_ALWAYS:
                flags |= O_CREAT | O_TRUNC;
                create = true;
                break;
            case CREATE_NEW:
                flags |= O_CREAT | O_EXCL;
                create = true;
                break;
            case OPEN_ALWAYS:
                flags |= O_CREAT;
                create = true;
                break;
            case OPEN_EXISTING:
                flags = O_RDONLY;
                break;
            case TRUNCATE_EXISTING:
                flags |= O_TRUNC;
                break;
            default:
                assert(0);
		}
	}
    
    //#if defined(PS3)
    //	char buf[512];
    //	const char *adjustedFilename = ConvertFileName(buf, lpFileName);
    //#else
	char adjustedFilename[MAX_PATH];
	strcpy(adjustedFilename, lpFileName);
	//GetFilenameNoCase(lpFileName, adjustedFilename, create);
    //#endif
    
	bool failOpen = false;
    //#if defined(USE_FILE_MAP)
    //#if defined(LINUX)
    //	const bool skipInitial = false;
    //#else
    //	const bool skipInitial = true;
    //#endif
    //	if (!FileNode::CheckOpen(adjustedFilename, create, skipInitial))
    //		failOpen = true;
    //#endif
	(void)create;
    
#if defined(FILE_MAP_DEBUG)
	fd = open(adjustedFilename, flags, mode);
	if (fd != -1 && failOpen)
	{
		puts("FileNode::CheckOpen error");
		assert(0);
	}
#else
	if (failOpen)
	{
		fd = -1;
		fserr = ENOENT;
	} 
	else
	{
        //#if defined(PS3)
        //		OpenFromFileHandleCacheAsFD(adjustedFilename, flags, fd, 0, errno);
        //#else
		FS_OPEN(adjustedFilename, flags, fd, 0, errno);		
        //#endif
	}
#endif
	(void)fserr;
	if (fd == -1)
	{
		h = INVALID_HANDLE_VALUE;
	} else
	{
		h = (HANDLE)fd;
	}
	return h;
}

//////////////////////////////////////////////////////////////////////////
FORCEINLINE DWORD GetFileSize(HANDLE hFile,DWORD *lpFileSizeHigh )
{
	FS_ERRNO_TYPE err = 0;
	FS_STAT_TYPE st;
	int fd = (int)hFile;
	DWORD r;
    
	FS_FSTAT(fd, st, err);
	if (err != 0)
		return INVALID_FILE_SIZE;
	if (lpFileSizeHigh)
		*lpFileSizeHigh = 0; //(DWORD)(st.st_size >> 32);
	r = (DWORD)st.st_size;
	return r;
}

//////////////////////////////////////////////////////////////////////////
FORCEINLINE BOOL CloseHandle( HANDLE hObject )
{
	int fd = (int)hObject;
    
	if (fd != -1)
	{
		close(fd);
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
FORCEINLINE BOOL CancelIo( HANDLE hFile )
{
	//TODO: implement
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
FORCEINLINE HRESULT GetOverlappedResult( HANDLE hFile,void* lpOverlapped,LPDWORD lpNumberOfBytesTransferred, BOOL bWait )
{
	//TODO: implement
	return 0;
    
}

//////////////////////////////////////////////////////////////////////////
FORCEINLINE BOOL ReadFileEx
(
 HANDLE hFile,
 LPVOID lpBuffer,
 DWORD nNumberOfBytesToRead,
 LPOVERLAPPED lpOverlapped,
 LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
 )
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
FORCEINLINE DWORD SetFilePointer
(
 HANDLE hFile,
 LONG lDistanceToMove,
 PLONG lpDistanceToMoveHigh,
 DWORD dwMoveMethod
 )
{
	//TODO: implement
	return 0;
}

#define FAILED(hr) (((int)(hr)) < 0)

typedef int HINSTANCE;
typedef int HICON;
typedef char TCHAR;
typedef const char *  D3DXHANDLE;

#define _THIS

#define PURE =0

#define D3DXFX_DONOTSAVESTATE         (1 << 0)
#define D3DXFX_DONOTSAVESHADERSTATE   (1 << 1)
#define D3DXFX_DONOTSAVESAMPLERSTATE  (1 << 2)

#define D3DXFX_NOT_CLONEABLE          (1 << 11)
#define D3DXFX_LARGEADDRESSAWARE      (1 << 17)

typedef struct _D3DXMACRO
{
  const char * Name;
  const char * Definition;

} D3DXMACRO, *LPD3DXMACRO;

#define D3DFVF_RESERVED0        0x001
#define D3DFVF_POSITION_MASK    0x400E
#define D3DFVF_XYZ              0x002
#define D3DFVF_XYZRHW           0x004
#define D3DFVF_XYZB1            0x006
#define D3DFVF_XYZB2            0x008
#define D3DFVF_XYZB3            0x00a
#define D3DFVF_XYZB4            0x00c
#define D3DFVF_XYZB5            0x00e
#define D3DFVF_XYZW             0x4002

#define D3DFVF_NORMAL           0x010
#define D3DFVF_PSIZE            0x020
#define D3DFVF_DIFFUSE          0x040
#define D3DFVF_SPECULAR         0x080

#define D3DFVF_TEXCOUNT_MASK    0xf00
#define D3DFVF_TEXCOUNT_SHIFT   8
#define D3DFVF_TEX0             0x000
#define D3DFVF_TEX1             0x100
#define D3DFVF_TEX2             0x200
#define D3DFVF_TEX3             0x300
#define D3DFVF_TEX4             0x400
#define D3DFVF_TEX5             0x500
#define D3DFVF_TEX6             0x600
#define D3DFVF_TEX7             0x700
#define D3DFVF_TEX8             0x800

#define D3DFVF_LASTBETA_UBYTE4   0x1000
#define D3DFVF_LASTBETA_D3DCOLOR 0x8000

#define D3DFVF_RESERVED2         0x6000  // 2 reserved bits

#define D3DFVF_TEXTUREFORMAT2 0         // Two floating point values
#define D3DFVF_TEXTUREFORMAT1 3         // One floating point value
#define D3DFVF_TEXTUREFORMAT3 1         // Three floating point values
#define D3DFVF_TEXTUREFORMAT4 2         // Four floating point values

#define D3DFVF_TEXCOORDSIZE3(CoordIndex) (D3DFVF_TEXTUREFORMAT3 << (CoordIndex*2 + 16))
#define D3DFVF_TEXCOORDSIZE2(CoordIndex) (D3DFVF_TEXTUREFORMAT2)
#define D3DFVF_TEXCOORDSIZE4(CoordIndex) (D3DFVF_TEXTUREFORMAT4 << (CoordIndex*2 + 16))
#define D3DFVF_TEXCOORDSIZE1(CoordIndex) (D3DFVF_TEXTUREFORMAT1 << (CoordIndex*2 + 16))

// emscripten has no ffs implemented
FORCEINLINE bool _BitScanForward(DWORD * out, DWORD value)
{
  if (value) {
	unsigned int v = value;
	unsigned int c;
	if (v & 0x1) 
	  c = 0;
	else
	{
	  c = 1;
	  if ((v & 0xffff) == 0) 
	  {  
		v >>= 16;  
		c += 16;
	  }
	  if ((v & 0xff) == 0) 
	  {  
		v >>= 8;  
		c += 8;
	  }
	  if ((v & 0xf) == 0) 
	  {  
		v >>= 4;
		c += 4;
	  }
	  if ((v & 0x3) == 0) 
	  {  
		v >>= 2;
		c += 2;
	  }
	  c -= v & 0x1;
	}	
	*out = c;
	return true;
  }

  *out = 0;
  return false;
}

typedef enum _D3DPRIMITIVETYPE {
  D3DPT_POINTLIST             = 1,
  D3DPT_LINELIST              = 2,
  D3DPT_LINESTRIP             = 3,
  D3DPT_TRIANGLELIST          = 4,
  D3DPT_TRIANGLESTRIP         = 5,
  D3DPT_TRIANGLEFAN           = 6,
  D3DPT_FORCE_DWORD           = 0x7fffffff, /* force 32-bit size enum */
} D3DPRIMITIVETYPE;

typedef enum _D3DSAMPLERSTATETYPE
{
  D3DSAMP_ADDRESSU       = 1,  /* D3DTEXTUREADDRESS for U coordinate */
  D3DSAMP_ADDRESSV       = 2,  /* D3DTEXTUREADDRESS for V coordinate */
  D3DSAMP_ADDRESSW       = 3,  /* D3DTEXTUREADDRESS for W coordinate */
  D3DSAMP_BORDERCOLOR    = 4,  /* D3DCOLOR */
  D3DSAMP_MAGFILTER      = 5,  /* D3DTEXTUREFILTER filter to use for magnification */
  D3DSAMP_MINFILTER      = 6,  /* D3DTEXTUREFILTER filter to use for minification */
  D3DSAMP_MIPFILTER      = 7,  /* D3DTEXTUREFILTER filter to use between mipmaps during minification */
  D3DSAMP_MIPMAPLODBIAS  = 8,  /* float Mipmap LOD bias */
  D3DSAMP_MAXMIPLEVEL    = 9,  /* DWORD 0..(n-1) LOD index of largest map to use (0 == largest) */
  D3DSAMP_MAXANISOTROPY  = 10, /* DWORD maximum anisotropy */
  D3DSAMP_SRGBTEXTURE    = 11, /* Default = 0 (which means Gamma 1.0,
                               no correction required.) else correct for
                               Gamma = 2.2 */
                               D3DSAMP_ELEMENTINDEX   = 12, /* When multi-element texture is assigned to sampler, this
                                                            indicates which element index to use.  Default = 0.  */
                                                            D3DSAMP_DMAPOFFSET     = 13, /* Offset in vertices in the pre-sampled displacement map.
                                                                                         Only valid for D3DDMAPSAMPLER sampler  */
                                                                                         D3DSAMP_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
} D3DSAMPLERSTATETYPE;

typedef enum _D3DTEXTUREOP
{
    // Control
    D3DTOP_DISABLE              = 1,      // disables stage
    D3DTOP_SELECTARG1           = 2,      // the default
    D3DTOP_SELECTARG2           = 3,

    // Modulate
    D3DTOP_MODULATE             = 4,      // multiply args together
    D3DTOP_MODULATE2X           = 5,      // multiply and  1 bit
    D3DTOP_MODULATE4X           = 6,      // multiply and  2 bits

    // Add
    D3DTOP_ADD                  =  7,   // add arguments together
    D3DTOP_ADDSIGNED            =  8,   // add with -0.5 bias
    D3DTOP_ADDSIGNED2X          =  9,   // as above but left  1 bit
    D3DTOP_SUBTRACT             = 10,   // Arg1 - Arg2, with no saturation
    D3DTOP_ADDSMOOTH            = 11,   // add 2 args, subtract product
                                        // Arg1 + Arg2 - Arg1*Arg2
                                        // = Arg1 + (1-Arg1)*Arg2

    // Linear alpha blend: Arg1*(Alpha) + Arg2*(1-Alpha)
    D3DTOP_BLENDDIFFUSEALPHA    = 12, // iterated alpha
    D3DTOP_BLENDTEXTUREALPHA    = 13, // texture alpha
    D3DTOP_BLENDFACTORALPHA     = 14, // alpha from D3DRS_TEXTUREFACTOR

    // Linear alpha blend with pre-multiplied arg1 input: Arg1 + Arg2*(1-Alpha)
    D3DTOP_BLENDTEXTUREALPHAPM  = 15, // texture alpha
    D3DTOP_BLENDCURRENTALPHA    = 16, // by alpha of current color

    // Specular mapping
    D3DTOP_PREMODULATE            = 17,     // modulate with next texture before use
    D3DTOP_MODULATEALPHA_ADDCOLOR = 18,     // Arg1.RGB + Arg1.A*Arg2.RGB
                                            // COLOROP only
    D3DTOP_MODULATECOLOR_ADDALPHA = 19,     // Arg1.RGB*Arg2.RGB + Arg1.A
                                            // COLOROP only
    D3DTOP_MODULATEINVALPHA_ADDCOLOR = 20,  // (1-Arg1.A)*Arg2.RGB + Arg1.RGB
                                            // COLOROP only
    D3DTOP_MODULATEINVCOLOR_ADDALPHA = 21,  // (1-Arg1.RGB)*Arg2.RGB + Arg1.A
                                            // COLOROP only

    // Bump mapping
    D3DTOP_BUMPENVMAP           = 22, // per pixel env map perturbation
    D3DTOP_BUMPENVMAPLUMINANCE  = 23, // with luminance channel

    // This can do either diffuse or specular bump mapping with correct input.
    // Performs the function (Arg1.R*Arg2.R + Arg1.G*Arg2.G + Arg1.B*Arg2.B)
    // where each component has been scaled and offset to make it signed.
    // The result is replicated into all four (including alpha) channels.
    // This is a valid COLOROP only.
    D3DTOP_DOTPRODUCT3          = 24,

    // Triadic ops
    D3DTOP_MULTIPLYADD          = 25, // Arg0 + Arg1*Arg2
    D3DTOP_LERP                 = 26, // (Arg0)*Arg1 + (1-Arg0)*Arg2

    D3DTOP_FORCE_DWORD = 0x7fffffff,
} D3DTEXTUREOP;

#define D3DTA_SELECTMASK        0x0000000f  // mask for arg selector
#define D3DTA_DIFFUSE           0x00000000  // select diffuse color (read only)
#define D3DTA_CURRENT           0x00000001  // select stage destination register (read/write)
#define D3DTA_TEXTURE           0x00000002  // select texture color (read only)
#define D3DTA_TFACTOR           0x00000003  // select D3DRS_TEXTUREFACTOR (read only)
#define D3DTA_SPECULAR          0x00000004  // select specular color (read only)
#define D3DTA_TEMP              0x00000005  // select temporary register color (read/write)
#define D3DTA_CONSTANT          0x00000006  // select texture stage constant
#define D3DTA_COMPLEMENT        0x00000010  // take 1.0 - x (read modifier)
#define D3DTA_ALPHAREPLICATE    0x00000020  // replicate alpha to color components (read modifier)

typedef enum _D3DTEXTUREADDRESS {
    D3DTADDRESS_WRAP            = 1,
    D3DTADDRESS_MIRROR          = 2,
    D3DTADDRESS_CLAMP           = 3,
    D3DTADDRESS_BORDER          = 4,
    D3DTADDRESS_MIRRORONCE      = 5,
    D3DTADDRESS_FORCE_DWORD     = 0x7fffffff, /* force 32-bit size enum */
} D3DTEXTUREADDRESS;

typedef enum _D3DTEXTUREFILTERTYPE
{
    D3DTEXF_NONE            = 0,    // filtering disabled (valid for mip filter only)
    D3DTEXF_POINT           = 1,    // nearest
    D3DTEXF_LINEAR          = 2,    // linear interpolation
    D3DTEXF_ANISOTROPIC     = 3,    // anisotropic
    D3DTEXF_PYRAMIDALQUAD   = 6,    // 4-sample tent
    D3DTEXF_GAUSSIANQUAD    = 7,    // 4-sample gaussian
    D3DTEXF_FORCE_DWORD     = 0x7fffffff,   // force 32-bit size enum
} D3DTEXTUREFILTERTYPE;

FORCEINLINE void *_aligned_malloc( size_t size, int align )
{
  void *mem = malloc( size + (align-1) + sizeof(void*) );

  char *amem = ((char*)mem) + sizeof(void*);
  amem += align - ((ptrdiff_t)amem & (align - 1));

  ((void**)amem)[-1] = mem;
  return amem;
}

FORCEINLINE void _aligned_free( void *mem )
{
  free( ((void**)mem)[-1] );
}

//FIXME:!!!!!!!!!!!!!!!!!!!!!!
FORCEINLINE uint32 GetCurrentThreadId()
{
    return 0;
}

#ifdef ASSERT
# undef ASSERT
#endif
#define ASSERT(x)


#define D3DXSHADER_DEBUG                          (1 << 0)
#define D3DXSHADER_SKIPVALIDATION                 (1 << 1)
#define D3DXSHADER_SKIPOPTIMIZATION               (1 << 2)
#define D3DXSHADER_PACKMATRIX_ROWMAJOR            (1 << 3)
#define D3DXSHADER_PACKMATRIX_COLUMNMAJOR         (1 << 4)
#define D3DXSHADER_PARTIALPRECISION               (1 << 5)
#define D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT        (1 << 6)
#define D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT        (1 << 7)
#define D3DXSHADER_NO_PRESHADER                   (1 << 8)
#define D3DXSHADER_AVOID_FLOW_CONTROL             (1 << 9)
#define D3DXSHADER_PREFER_FLOW_CONTROL            (1 << 10)
#define D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY (1 << 12)
#define D3DXSHADER_IEEE_STRICTNESS                (1 << 13)
#define D3DXSHADER_USE_LEGACY_D3DX9_31_DLL        (1 << 16)


// optimization level flags
#define D3DXSHADER_OPTIMIZATION_LEVEL0            (1 << 14)
#define D3DXSHADER_OPTIMIZATION_LEVEL1            0
#define D3DXSHADER_OPTIMIZATION_LEVEL2            ((1 << 14) | (1 << 15))
#define D3DXSHADER_OPTIMIZATION_LEVEL3            (1 << 15)

#include <string.h>
#include <ctype.h>

#define _strlwr     strlwr
#define _tcslen     strlen
#define _tcscpy     strcpy
#define _tcscpy_s   strcpy_s
#define _tcsncpy    strncpy
#define _tcsncpy_s  strncpy_s
#define _tcscat     strcat
#define _tcscat_s   strcat_s
#define _tcsupr     strupr
#define _tcsupr_s   strupr_s
#define _tcslwr     strlwr
#define _tcslwr_s   strlwr_s
#define fscanf_s    fscanf
#define fprintf_s   fprintf
#define strcpy_s    strcpy
#define strcat_s    strcat


// FIXME:!!!!!!!!!!!!!!!!!!!!!!!!!!!!
FORCEINLINE BOOL QueryPerformanceCounter(LARGE_INTEGER * count)
{
  assert(0);
    //struct timezone zone;
    ////gettimeofday(count, &zone);
    //struct timeval now;

    //gettimeofday(&now, &zone);

    //double elapsed = now.tv_sec * 1000.0 + now.tv_usec/1000000.0;

    //count->QuadPart = elapsed;

	return TRUE;
}

// FIXME:!!!!!!!!!!!!!!!!!!!!!!!!!!!!
FORCEINLINE BOOL QueryPerformanceFrequency(LARGE_INTEGER * count)
{
  assert(0);
  //count->QuadPart = 1;
	return TRUE;
}

// FIXME:!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define GETTIMESTAMP timeGetTime()

#define SUCCEEDED(x) (x >= 0)

//extern bool FixPathForPlatform(char * buf, int sizebuf, const char * srcPath); 

namespace Engine2
{
  namespace Platform
  {
    FORCEINLINE errno_t  fopen_s( FILE ** _File,  const char * _Filename,  const char * _Mode)
    {
      // FIXME:!!!
      *_File = fopen(/*tmpbuf*/_Filename, _Mode);
      //LOGI("fopen_s:%s res:%s", _Filename, strerror(errno));
      return *_File == 0 ? -1 : 0; 
    }
    
  }
}

void OutputDebugString( char const * str);


