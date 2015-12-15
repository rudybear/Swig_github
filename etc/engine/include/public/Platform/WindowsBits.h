#pragma once

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#ifdef _WIN32
# error This header is not supposed to be included on Windows
#endif

typedef unsigned short WORD;

#undef FALSE
#define FALSE   0
#undef TRUE
#define TRUE    1
typedef int BOOL;

typedef void VOID;
typedef unsigned char BYTE;
typedef char TCHAR;
typedef int INT;
typedef unsigned int UINT;
typedef void * LPVOID;

typedef unsigned int       DWORD;
typedef DWORD * LPDWORD;
typedef int HRESULT;
typedef intptr_t HANDLE;
typedef void* HINSTANCE;
typedef void* HICON;

typedef wchar_t WCHAR;

struct POINT {
  int x;
  int y;
};


typedef struct {
  int cx;
  int cy;
} SIZE;

typedef struct tagRECT {
  int left;
  int top;
  int right;
  int bottom;
} RECT, * LPRECT;


typedef struct _OVERLAPPED {
  unsigned int * Internal;
  unsigned int * InternalHigh;
  union {
    struct {
      unsigned int Offset;
      unsigned int OffsetHigh;
    };
    
    void * Pointer;
  };
  
  HANDLE  hEvent;
} OVERLAPPED, *LPOVERLAPPED;

#ifndef __APPLE__
typedef timeval LARGE_INTEGER;
#else
typedef union {
    struct {
        unsigned int LowPart;
        unsigned int HighPart;        
    };
    unsigned long long QuadPart;
} LARGE_INTEGER;
#endif


#define SUCCEEDED(x) (x >= 0)
#define FAILED(hr) (((int)(hr)) < 0)
#define S_OK 0
#define S_FALSE 0x00000001L
#define E_FAIL (int)0x80000008L
#define E_INVALIDARG (int)0x80000003L
#define E_OUTOFMEMORY (int)0x8007000EL


#if defined(_MAC64) || (__x86_64__)
typedef long long INT_PTR, *PINT_PTR;
typedef unsigned long long UINT_PTR, *PUINT_PTR;

typedef long long LONG_PTR, *PLONG_PTR;
typedef unsigned long long ULONG_PTR, *PULONG_PTR;

typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
#else
typedef  int INT_PTR, *PINT_PTR;
typedef  unsigned int UINT_PTR, *PUINT_PTR;

typedef  int LONG_PTR, *PLONG_PTR;
typedef  unsigned int ULONG_PTR, *PULONG_PTR;

typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
#endif
// Candidates for separate header with Windows-types

#undef FALSE
#define FALSE   0
#undef TRUE
#define TRUE    1
typedef int BOOL;

typedef void VOID;
typedef unsigned char BYTE;
typedef char TCHAR;
typedef int INT;
typedef void * LPVOID;

#define WPARAM uint32
#define LPARAM uint32
#define LOWORD(l) (l & 0xffff)  
#define HIWORD(l) ((l>>16) & 0xffff)  
#define HIBYTE(w) (w >> 8)
#define LOBYTE(w) (w && 0xFF)

#if defined(_MAC64) || (__x86_64__)
typedef long long INT_PTR, *PINT_PTR;
typedef unsigned long long UINT_PTR, *PUINT_PTR;

typedef long long LONG_PTR, *PLONG_PTR;
typedef unsigned long long ULONG_PTR, *PULONG_PTR;

typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
#else
typedef  int INT_PTR, *PINT_PTR;
typedef  unsigned int UINT_PTR, *PUINT_PTR;

typedef  int LONG_PTR, *PLONG_PTR;
typedef  unsigned int ULONG_PTR, *PULONG_PTR;

typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
#endif
typedef time_t __time64_t;

#define WIN_HWND intptr_t
#define WIN_HINSTANCE intptr_t

// messages
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

#define WPARAM uint32
#define LPARAM uint32
#define LOWORD(l) (l & 0xffff)  
#define HIWORD(l) ((l>>16) & 0xffff)  
#define HIBYTE(w) (w >> 8)
#define LOBYTE(w) (w && 0xFF)

#define __cdecl 
#ifndef APIENTRY
#define APIENTRY
#endif
#define CALLBACK 
#define WINAPI

inline char* e2_strlwr(char* str)
{
  for (char* p = str; *p; ++p)
    *p = tolower(*p);
  return str;
}
#define _strlwr     e2_strlwr
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
#define _stricmp strcasecmp
#define _strnicmp strncasecmp
#define scanf_s scanf
#define sscanf_s sscanf
#define sprintf_s sprintf
#define _vsnprintf_s vsnprintf_s
#define _itoa_s itoa
#define __va_list va_list
#define _getcwd getcwd
#define _chdir chdir
#define Sleep sleep

inline int strncpy_s(char * output, const char * input, size_t len)
{
    strncpy(output, input, len);
    
    return 0;
}

inline int vsnprintf_s(char *buf,
                            int /*bufSize - not used*/,
                            int size,
                            const char *format,
                            __va_list ap)
{
	int res = vsnprintf(buf, size, format, ap);
	buf[size - 1] = 0;
	return res;
}

typedef int errno_t;
namespace Engine2
{
  namespace Platform
  {
    inline errno_t  fopen_s( FILE ** _File,  const char * _Filename,  const char * _Mode)
    {
      *_File = fopen(/*tmpbuf*/_Filename, _Mode);
      return *_File == 0 ? -1 : 0; 
    }
    
  }
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
#define _MAX_PATH 4096
#ifdef __APPLE__
# define MAX_PATH _MAX_PATH
#else
# define MAX_PATH PATH_MAX
#endif

#define GENERIC_READ    (0x80000000L)
#define GENERIC_WRITE   (0x40000000L)
#define GENERIC_EXECUTE (0x20000000L)
#define GENERIC_ALL     (0x10000000L)

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
#define INVALID_HANDLE_VALUE (-1)

inline HANDLE CreateFile(
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
    
	char adjustedFilename[MAX_PATH];
	strcpy(adjustedFilename, lpFileName);
    
	bool failOpen = false;
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
		FS_OPEN(adjustedFilename, flags, fd, 0, errno);		
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
inline BOOL CloseHandle( HANDLE hObject )
{
	int fd = (int)hObject;
    
	if (fd != -1)
	{
		close(fd);
	}
	return TRUE;
}

inline DWORD GetFileSize(HANDLE hFile,DWORD *lpFileSizeHigh )
{
	FS_ERRNO_TYPE err = 0;
	FS_STAT_TYPE st;
	int fd = (int)hFile;
	DWORD r;
    
	FS_FSTAT(fd, st, err);
	if (err != 0)
		return INVALID_FILE_SIZE;
	if (lpFileSizeHigh)
		*lpFileSizeHigh = (DWORD)(st.st_size >> 32);
	r = (DWORD)st.st_size;
	return r;
}

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
typedef void ( *LPOVERLAPPED_COMPLETION_ROUTINE )( 
                                                  unsigned int dwErrorCode,
                                                  unsigned int dwNumberOfBytesTransfered,
                                                  void * lpOverlapped);

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

template<class A, class B>
A min(A a, B b) { return a < b ? a : b; }

enum { _A_SUBDIR = 1 };

struct _finddata_t
{
  int attrib;
  char name[128];

  DIR* dir;
  dirent entry;
  dirent* result;
	char mask[128];
};

inline intptr_t _findnext(intptr_t handle, _finddata_t* fd)
{
	if (!fd->dir)
		return 0;

	const char* n;
	do {
		if (readdir_r(fd->dir, &fd->entry, &fd->result) != 0)
			return 0;
		if (fd->result == 0)
			return 0;
		n = fd->entry.d_name;;
	}
	while ((n[0] == '.' && n[1] == '\0') ||
				 (n[0] == '.' && n[1] == '.' && n[2] == '\0') ||
				 fnmatch(fd->mask, n, FNM_NOESCAPE) == FNM_NOMATCH);

	strcpy(fd->name, fd->entry.d_name);

	fd->attrib = 0;
	if (fd->entry.d_type == DT_DIR)
		fd->attrib = _A_SUBDIR;

  return (intptr_t)fd;
}

inline intptr_t _findfirst(const char* filter, _finddata_t* fd)
{
  const char* last_sep = strrchr(filter, '/');
	const char* mask;
	const char* folder;
  if (last_sep) {
		char* f = (char*)alloca(last_sep - filter + 1);
		strncpy(f, filter, last_sep - filter);
		f[last_sep - filter] = '\0';
		folder = f;
		mask = last_sep + 1;
	}
	else {
		mask = filter;
		folder = ".";
	}

	strcpy(fd->mask, mask);
  fd->dir = opendir(folder);
  if (!fd->dir)
    return 0;
  return _findnext((intptr_t)fd, fd);
}


inline void _findclose(intptr_t handle)
{
	if (!handle)
		return;
  _finddata_t* fd = (_finddata_t*)handle;
  closedir(fd->dir);
  fd->dir = 0;
}

inline void _splitpath(const char* szSrcFile, char* out_drive, char* out_dir, char* out_filename, char* out_ext)
{
  const char* last_sep = strrchr(szSrcFile, '/');
  const char* filename;
  if (!last_sep) {
    filename = szSrcFile;
    last_sep = filename;
  }
  else {
    filename = last_sep + 1;
  }
  const char* ext = strrchr(last_sep, '.');
  if (!ext)
    ext = szSrcFile + strlen(szSrcFile);

  if (out_drive)
    strcpy(out_drive, "");
  if (out_dir) {
    strncpy(out_dir, szSrcFile, last_sep - szSrcFile);
		out_dir[last_sep-szSrcFile] = '/';
		out_dir[last_sep-szSrcFile+1] = '\0';
	}
  if (out_filename) {
    strncpy(out_filename, filename, ext - filename);
		out_filename[ext - filename] = '\0';
	}
  if (out_ext) {
    strcpy(out_ext, ext);
	}
}
