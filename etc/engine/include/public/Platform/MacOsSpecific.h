////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <mach/mach_time.h>
#include <libkern/OSAtomic.h>
#include "WindowsBits.h"

typedef int errno_t;
//#define FORCEINLINE inline

FORCEINLINE bool _isnan( float value ) 
{
    return ((*(unsigned int*)&value) & 0x7fffffff) > 0x7f800000; 
} 

#include <pthread.h>
#include <libkern/OSAtomic.h>

FORCEINLINE LONG _InterlockedDecrement(LONG volatile* value)
{
    return OSAtomicDecrement32((int volatile*)value);
    
}

FORCEINLINE LONG _InterlockedIncrement(LONG volatile* value)
{
    return OSAtomicIncrement32((int volatile*)value);
    
}

#define  InterlockedIncrement _InterlockedIncrement
#define  InterlockedDecrement _InterlockedDecrement

////////////////////////////////////////////////////////////////////////////
//inline UINT_PTR GetCurrentThreadId()
//{
//    pthread_t id = pthread_self();
//    return (UINT_PTR)id;
//}


FORCEINLINE LONG _InterlockedExchangeAdd(LONG volatile* value , LONG inc)
{
    // FIXME:!!!!!!!!!!!!!!!!!! OSCompareAndSwap
	int oldValue = (int)*value;
	//bool res = 
    OSAtomicCompareAndSwap32(oldValue, oldValue + (int)inc, (int volatile*)value);
	
	return oldValue;//
	
}


FORCEINLINE LONG _InterlockedCompareExchange(LONG volatile* destination , LONG exchange, LONG comparand)
{
	int dest = (int)*destination;
	//bool res = 
    OSAtomicCompareAndSwap32(comparand, exchange, (int*)destination );
    return dest;//res ? dest : -oldValue;//
}

#define InterlockedExchangeAdd _InterlockedExchangeAdd

typedef pthread_mutex_t CRITICAL_SECTION;

//#define _debugbreak __debugbreak
FORCEINLINE void _debugbreak()
{

}




#include <malloc/malloc.h>

FORCEINLINE size_t _msize(void * ptr)
{
    return malloc_size(ptr);
}

typedef unsigned int UINT;

typedef wchar_t WCHAR;

#ifndef FLT_EPSILON
#define FLT_EPSILON   1.192092896e-07F 
#endif

typedef time_t __time64_t;

//#define LOG //

//FIXME:!!!!!
FORCEINLINE double timeGetTime()
{
    return 0.0f;
}


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

extern int errno;

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


FORCEINLINE bool _BitScanForward(DWORD * out, DWORD value)
{
    if (value) {
        *out = ffsl(value);
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
#undef ASSERT
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



// FIXME:!!!!!!!!!!!!!!!!!!!!!!!!!!!!
inline BOOL QueryPerformanceCounter(LARGE_INTEGER * count)
{
  count->QuadPart =  mach_absolute_time();
  return TRUE;
}

// FIXME:!!!!!!!!!!!!!!!!!!!!!!!!!!!!
inline BOOL QueryPerformanceFrequency(LARGE_INTEGER * count)
{
  mach_timebase_info_data_t info;
  kern_return_t err = mach_timebase_info( &info );

  double conversion = 0.0;

  if( err == 0  )
    conversion = 1e-9 * (double) info.numer / (double) info.denom;

  count->QuadPart = (long long)((double)(1.0/conversion));

  return TRUE;
}

// FIXME:!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#ifdef __cplusplus
#define C_LINKAGE	"C"
#else
#define C_LINKAGE
#endif /* __cplusplus */

        
extern C_LINKAGE bool FixPathForPlatform(char * buf, int sizebuf, const char * srcPath, const char * _Mode);
        

FORCEINLINE void OutputDebugString( char const * str)
{
    printf("%s", str);
}
