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
#define REND_OK 1
#define REND_ERROR 2
#define REND_CANTINIT 4
#define REND_MAX_LIGHTS 4
#define NUM_TMU 8

#define MAX_TEXTURES 8
#define MAX_LIGHTS   4


struct CVec2;
struct CVec3;
struct CVec4;



enum APPMSGTYPE { MSG_NONE, MSGERR_APPMUSTEXIT, MSGWARN_SWITCHEDTOREF };

#define D3DAPPERR_NODIRECT3D 0x82000001
#define D3DAPPERR_NOWINDOW 0x82000002
#define D3DAPPERR_NOCOMPATIBLEDEVICES 0x82000003
#define D3DAPPERR_NOWINDOWABLEDEVICES 0x82000004
#define D3DAPPERR_NOHARDWAREDEVICE 0x82000005
#define D3DAPPERR_HALNOTCOMPATIBLE 0x82000006
#define D3DAPPERR_NOWINDOWEDHAL 0x82000007
#define D3DAPPERR_NODESKTOPHAL 0x82000008
#define D3DAPPERR_NOHALTHISMODE 0x82000009
#define D3DAPPERR_NONZEROREFCOUNT 0x8200000a
#define D3DAPPERR_MEDIANOTFOUND 0x8200000b
#define D3DAPPERR_RESIZEFAILED 0x8200000c

// Все typedef'ы - банальный copy-paste из d3dtypes. Решение спорное, но должно помочь 
typedef enum _eBLEND {
  BLEND_ZERO               = 1,
  BLEND_ONE                = 2,
  BLEND_SRCCOLOR           = 3,
  BLEND_INVSRCCOLOR        = 4,
  BLEND_SRCALPHA           = 5,
  BLEND_INVSRCALPHA        = 6,
  BLEND_DESTALPHA          = 7,
  BLEND_INVDESTALPHA       = 8,
  BLEND_DESTCOLOR          = 9,
  BLEND_INVDESTCOLOR       = 10,
  BLEND_SRCALPHASAT        = 11,
  BLEND_BOTHSRCALPHA       = 12,
  BLEND_BOTHINVSRCALPHA    = 13,
  BLEND_FORCE_DWORD        = 0x7fffffff, /* force 32-bit size enum */
} eBLEND;

typedef enum _eBLENDOP {
  BLENDOP_ADD              = 1,
  BLENDOP_SUBTRACT         = 2,
  BLENDOP_REVSUBTRACT      = 3,
  BLENDOP_MIN              = 4,
  BLENDOP_MAX              = 5,
  BLENDOP_FORCE_DWORD      = 0x7fffffff, /* force 32-bit size enum */
} eBLENDOP;


typedef enum _eCULL {
  CULL_Unknown             = 0,
  CULL_NONE                = 1,
  CULL_CW                  = 2,
  CULL_CCW                 = 3,
  CULL_FORCE_DWORD         = 0x7fffffff, /* force 32-bit size enum */
} eCULL;

typedef enum _eCMPFUNC {
  CMP_NEVER                = 1,
  CMP_LESS                 = 2,
  CMP_EQUAL                = 3,
  CMP_LESSEQUAL            = 4,
  CMP_GREATER              = 5,
  CMP_NOTEQUAL             = 6,
  CMP_GREATEREQUAL         = 7,
  CMP_ALWAYS               = 8,
  CMP_FORCE_DWORD          = 0x7fffffff, /* force 32-bit size enum */
} eCMPFUNC;

typedef enum _eDEPTHSTATE {
  DEPTH_ZZWDISABLE = -1,
  DEPTH_ZZWENABLE = 0,
  DEPTH_ZENABLEZWDISABLE = 1,
} eDEPTHSTATE;

typedef enum _eVertexTypes {
  eVERTEX_PDT2 = 0,
  eVERTEX_PDT1 = 1,
  eVERTEX_PT2 = 2,
  eVERTEX_PT1 = 3,
  eVERTEX_PNT1 = 4,
  eVERTEX_PNT2 = 5,
  eVERTEX_PNT1TB = 6,
  eVERTEX_PNT2TB = 7,
  eVERTEX_PT3 = 8,
  eVERTEX_PNDT1TB = 9,
  eVERTEX_PNDT1 = 10,
  eVERTEX_PNT2TB_1 = 11,
  eVERTEX_PNT34 = 12,
  eVERTEX_PNDT2 = 13,
  eVERTEX_PNDT4 = 14,
  eVERTEX_PNDT2TB = 15,
  eVERTEX_PT1_3 = 16,
  // Add new vertex type here, change _LAST value
  eVERTEX_LAST = 17,

  eVERTEX_PDT2_INST,
  eVERTEX_PDT1_INST,
  eVERTEX_PT2_INST,
  eVERTEX_PT1_INST,
  eVERTEX_PNT1_INST,
  eVERTEX_PNT2_INST,
  eVERTEX_PNT1TB_INST,
  eVERTEX_PNT2TB_INST,
  eVERTEX_PT3_INST,
  eVERTEX_PNDT1TB_INST,
  eVERTEX_PNDT1_INST,
  eVERTEX_PNT2TB_1_INST,
  eVERTEX_PNT34_INST,
  eVERTEX_PNDT2_INST,
  eVERTEX_PNDT4_INST,
  eVERTEX_PNDT2TB_INST,
  eVERTEX_PT1_3_INST,
  eVERTEX_LAST_INST,

} eVertexTypes;

typedef enum _eVertexAttribute {
  eVA_POSITION,
  eVA_TEXCOORD0,
  eVA_TEXCOORD1,
  eVA_COLOR0,
  eVA_COLOR1,
  eVA_NORMAL,
  eVA_BINORMAL,
  eVA_TANGENT,
  eVA_BLENDWEIGHT,
  eVA_BLENDINDICES,
  eVA_NUM,
} eVertexAttribute;

enum eMaterialType {
  eMeshShader,
  eMeshShader_Transp,
  eMeshShader_Terrain,
  eWaterShader,
  ePlainReflectionShader,
  eCMReflectShader,
  eNoInstancingShader,
};
typedef enum _eShaderType {
  eBase = 0,
  eShaderVS = 1,
  eShaderPS = 2,
  eShaderVSPS = 3,
  eEffect = 4
} eShaderType;

enum eRenderType {
  eFrame = 0,
  eReflection = 1,
  eRefraction = 2,
  eShadow = 3,
  eAfterShadow = 4,
  eGlow = 5,
  eShadowBlur = 6, //  
  eMotionBlurFrame = 7, // Проход для фрейма после MotionBlur
  eImmediate = 8,
  eToon = 9,
  eZPrepass = 10,
  eSSShadow = 11,
  eSSAO = 12,
  eTransparent = 13,
  eRenderToTexture = 14,
  eShadowStatic = 15,
  eShadowDynamic = 16,
  eShadowTerrain = 17,
  eFogPass = 18,
  eAfterGui = 19,
  eSilhouette = 20,
  eLast = 21
};


typedef uint32 TRenderTypeMask;
// Return 1 if eRenderType exists in the mask
inline int IsRenderTypeInMask(TRenderTypeMask mask, eRenderType type) {
  return (mask >> (int)type) & 1;
}

typedef/* unsigned*/ int TEXNUM; 

inline const char * GetRenderTypeDesc(eRenderType type)
{
  switch(type)
  {
  case eFrame:
    return "Frame";

  case eReflection:
    return "Reflection";

  case eRefraction:
    return "Refraction";

  case eShadow:
    return "Shadow";

  case eAfterShadow:
    return "AfterShadow";

  case eGlow:
    return "Glow";
  case eFogPass:
    return "FogPass";

  case eShadowBlur:
    return "ShadowBlur"; // Проход для сцены MotionBlur

  case eMotionBlurFrame:
    return "MotionBlurFrame"; // Проход для фрейма после MotionBlur

  case eImmediate:
    return "Immediate"; 
  case eToon:
    return "Toon";
  case eZPrepass:
    return "ZPrepass";
  case eTransparent:
    return "Transparent";
  case eSSAO:
    return "SSAO";
  default:
    return "Undefined";
          
  }

  return "Undefined";
};

#define MAKE_RETURN(x,y) \
  if (!_stricmp(v, x)) \
  return y;

inline eRenderType GetRenderTypeVal(const char * v)
{
  MAKE_RETURN("Frame", eFrame);
  MAKE_RETURN("Reflection", eReflection);
  MAKE_RETURN("Refraction", eRefraction);
  MAKE_RETURN("Shadow", eShadow);
  MAKE_RETURN("AfterShadow", eAfterShadow);
  MAKE_RETURN("AfterGui", eAfterGui);
  MAKE_RETURN("Glow", eGlow);
  MAKE_RETURN("Silhouette", eSilhouette);
  MAKE_RETURN("FogPass", eFogPass);
  MAKE_RETURN("ShadowBlur", eShadowBlur);
  MAKE_RETURN("Immediate", eImmediate);
  MAKE_RETURN("Toon", eToon);
  MAKE_RETURN("ZPrepass", eZPrepass);
  MAKE_RETURN("Transparent", eTransparent);
  MAKE_RETURN("SSAO", eSSAO);
  return eFrame;//FIXME
}

enum eActiveType {
  e_Disable,
  e_Always,
  e_NextFrame// специальный режим рисования по требованию
};

typedef enum _TRANSFORMSTATETYPE {
  TS_VIEW          = 2,
  TS_PROJECTION    = 3,
  TS_TEXTURE0      = 16,
  TS_TEXTURE1      = 17,
  TS_TEXTURE2      = 18,
  TS_TEXTURE3      = 19,
  TS_TEXTURE4      = 20,
  TS_TEXTURE5      = 21,
  TS_TEXTURE6      = 22,
  TS_TEXTURE7      = 23,
  TS_FORCE_DWORD     = 0x7fffffff, /* force 32-bit size enum */
} TRANSFORMSTATETYPE;

#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
  ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |       \
  ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))
#endif /* defined(MAKEFOURCC) */

typedef enum _FORMAT
{
  FMT_UNKNOWN              =  0,

  FMT_R8G8B8               = 20,
  FMT_A8R8G8B8             = 21,
  FMT_X8R8G8B8             = 22,
  FMT_R5G6B5               = 23,
  FMT_X1R5G5B5             = 24,
  FMT_A1R5G5B5             = 25,
  FMT_A4R4G4B4             = 26,
  FMT_R3G3B2               = 27,
  FMT_A8                   = 28,
  FMT_A8R3G3B2             = 29,
  FMT_X4R4G4B4             = 30,
  FMT_A2B10G10R10          = 31,
  FMT_A8B8G8R8             = 32,
  FMT_X8B8G8R8             = 33,
  FMT_G16R16               = 34,
  FMT_A2R10G10B10          = 35,
  FMT_A16B16G16R16         = 36,

  FMT_A8P8                 = 40,
  FMT_P8                   = 41,

  FMT_L8                   = 50,
  FMT_A8L8                 = 51,
  FMT_A4L4                 = 52,

  FMT_V8U8                 = 60,
  FMT_L6V5U5               = 61,
  FMT_X8L8V8U8             = 62,
  FMT_Q8W8V8U8             = 63,
  FMT_V16U16               = 64,
  FMT_A2W10V10U10          = 67,

  FMT_UYVY                 = MAKEFOURCC('U', 'Y', 'V', 'Y'),
  FMT_R8G8_B8G8            = MAKEFOURCC('R', 'G', 'B', 'G'),
  FMT_YUY2                 = MAKEFOURCC('Y', 'U', 'Y', '2'),
  FMT_G8R8_G8B8            = MAKEFOURCC('G', 'R', 'G', 'B'),
  FMT_DXT1                 = MAKEFOURCC('D', 'X', 'T', '1'),
  FMT_DXT2                 = MAKEFOURCC('D', 'X', 'T', '2'),
  FMT_DXT3                 = MAKEFOURCC('D', 'X', 'T', '3'),
  FMT_DXT4                 = MAKEFOURCC('D', 'X', 'T', '4'),
  FMT_DXT5                 = MAKEFOURCC('D', 'X', 'T', '5'),
  FMT_3DC                  = MAKEFOURCC('A', 'T', 'I', '2'),
  FMT_PVRTC2               = MAKEFOURCC('P', 'T', 'C', '2'),
  FMT_PVRTC2A              = MAKEFOURCC('P', 'T', 'C', '3'),
  FMT_PVRTC4               = MAKEFOURCC('P', 'T', 'C', '5'),
  FMT_PVRTC4A              = MAKEFOURCC('P', 'T', 'C', '4'),
  FMT_ETC0                 = MAKEFOURCC('E', 'T', 'C', '0'),

  FMT_D16_LOCKABLE         = 70,
  FMT_D32                  = 71,
  FMT_D15S1                = 73,
  FMT_D24S8                = 75,
  FMT_D24X8                = 77,
  FMT_D24X4S4              = 79,
  FMT_D16                  = 80,

  FMT_L16                  = 81,

  FMT_D32F_LOCKABLE        = 82,
  FMT_D24FS8               = 83,

  FMT_D32_LOCKABLE         = 84,
  FMT_S8_LOCKABLE          = 85,

  FMT_VERTEXDATA           =100,
  FMT_INDEX16              =101,
  FMT_INDEX32              =102,

  FMT_Q16W16V16U16         =110,

  FMT_MULTI2_ARGB8         = MAKEFOURCC('M','E','T','1'),

  // Floating point surface formats

  // s10e5 formats (16-bits per channel)
  FMT_R16F                 = 111,
  FMT_G16R16F              = 112,
  FMT_A16B16G16R16F        = 113,

  // IEEE s23e8 formats (32-bits per channel)
  FMT_R32F                 = 114,
  FMT_G32R32F              = 115,
  FMT_A32B32G32R32F        = 116,

  FMT_CxV8U8               = 117,

  FMT_A1                   = 118,
  FMT_R32F_S               = 120,

  FMT_BINARYBUFFER         = 199,

  FMT_FORCE_DWORD          =0x7fffffff
} TEXFORMAT;

typedef enum _POOL {
  POOL_DEFAULT                 = 0,
  POOL_MANAGED                 = 1,
  POOL_SYSTEMMEM               = 2,
  POOL_SCRATCH                 = 3,

  POOL_FORCE_DWORD             = 0x7fffffff
} BUFPOOL;

enum EFOGMODE {
  EFOG_NONE                 = 0,
  EFOG_EXP                  = 1,
  EFOG_EXP2                 = 2,
  EFOG_LINEAR               = 3,
  EFOG_FORCE_DWORD          = 0x7fffffff, /* force 32-bit size enum */
};

#define CLIPPLANE0 (1 << 0)
#define CLIPPLANE1 (1 << 1)
#define CLIPPLANE2 (1 << 2)
#define CLIPPLANE3 (1 << 3)
#define CLIPPLANE4 (1 << 4)
#define CLIPPLANE5 (1 << 5)

enum ETEXTUREFILTERTYPE
{
  ETEXF_NONE            = 0,    // filtering disabled (valid for mip filter only)
  ETEXF_POINT           = 1,    // nearest
  ETEXF_LINEAR          = 2,    // linear interpolation
  ETEXF_ANISOTROPIC     = 3,    // anisotropic
  ETEXF_PYRAMIDALQUAD   = 6,    // 4-sample tent

  ETEXF_FORCE_DWORD     = 0x7fffffff,   // force 32-bit size enum
};

enum ETEXTUREADDRESS {
  ETADDRESS_WRAP            = 1,
  ETADDRESS_MIRROR          = 2,
  ETADDRESS_CLAMP           = 3,
  ETADDRESS_BORDER          = 4,
  ETADDRESS_MIRRORONCE      = 5,
  ETADDRESS_FORCE_DWORD     = 0x7fffffff, /* force 32-bit size enum */
};

typedef enum _FILLMODE {
  FILL_POINT               = 1,
  FILL_WIREFRAME           = 2,
  FILL_SOLID               = 3,
  FILL_FORCE_DWORD         = 0x7fffffff, /* force 32-bit size enum */
} FILLMODE;


#define VERTEXTEXTURESAMPLER0 257

/* Usages */
#define FUSAGE_RENDERTARGET       (0x00000001L)
#define FUSAGE_DEPTHSTENCIL       (0x00000002L)
#define FUSAGE_DYNAMIC            (0x00000200L)
#define FUSAGE_AUTOGENMIPMAP      (0x00000400L)
#define FUSAGE_CUBEMAP            (0x00010000L)

/* Usages for Vertex/Index buffers */
#define FUSAGE_WRITEONLY          (0x00000008L)


typedef enum _IMAGE_FILEFORMAT
{
  IFF_BMP         = 0,
  IFF_JPG         = 1,
  IFF_TGA         = 2,
  IFF_PNG         = 3,
  IFF_DDS         = 4,
  IFF_PPM         = 5,
  IFF_DIB         = 6,
  IFF_HDR         = 7,       //high dynamic range formats
  IFF_PFM         = 8,       //
  IFF_FORCE_DWORD = 0x7fffffff

} IMAGE_FILEFORMAT;

enum MAXTableSlotMap {
  ID_AM = 0,// - Ambient (value 0)
  ID_DI,// - Diffuse (value 1)
  ID_SP,// - Specular (value 2)
  ID_SH,// - Shininess (value 3). In R3 and later this is called Glossiness.
  ID_SS,// - Shininess strength (value 4). In R3 and later this is called Specular Level.
  ID_SI,// - Self-illumination (value 5)
  ID_OP,// - Opacity (value 6)
  ID_FI,// - Filter color (value 7)
  ID_BU,// - Bump (value 8)
  ID_RL,// - Reflection (value 9)
  ID_RR,// - Refraction (value 10)
  ID_DP // - Displacement (value 11)
};

struct RenderViewport
{
  DWORD       X;
  DWORD       Y;            /* Viewport Top left */
  DWORD       Width;
  DWORD       Height;       /* Viewport Dimensions */
  float       MinZ;         /* Min/max of clip Volume */
  float       MaxZ;

  RenderViewport() {}

  RenderViewport(int inX, int inY, int inWidth, int inHeight)
  {
    X = inX;
    Y = inY;
    Width  = inWidth;
    Height = inHeight;
    MinZ = 0;
    MaxZ = 1;
  }
};

struct LOCKED_RECT
{
  INT                 Pitch;
  void*               pBits;
};
/* Lock flags */

#define LOCK_READONLY           0x00000010L
#define LOCK_DISCARD            0x00002000L
#define LOCK_NOOVERWRITE        0x00001000L
#define LOCK_NOSYSLOCK          0x00000800L
#define LOCK_DONOTWAIT          0x00004000L                  

#define LOCK_NO_DIRTY_UPDATE     0x00008000L


struct RENDVERTEX_ET
{
  CVec3 p;
  DWORD diffuse;
  CVec2 t1;
  CVec2 t2;
};

struct RENDVERTEX 
{
};

struct RENDVERTEX_PDT2: public RENDVERTEX // BSP vertex Position + Diffuse + tex2
{
  CVec3 p;
  DWORD diffuse;
  CVec2 t1;
  CVec2 t2;
};

struct RENDVERTEX_PDT1: public RENDVERTEX // BSP vertex Position + Diffuse + tex2
{
  CVec3 p;
  DWORD diffuse;
  CVec2 t1;
};

struct RENDVERTEX_PT2: public RENDVERTEX // BSP vertex Position + Normal + tex2
{
  CVec3 p;
  CVec2 t1;
  CVec2 t2;
};

struct RENDVERTEX_PT1: public RENDVERTEX // BSP vertex Position + Diffuse + tex1
{
  CVec3 p;
  CVec2 t1;
};

struct RENDVERTEX_PT1_3: public RENDVERTEX // BSP vertex Position + Diffuse + tex1
{
  CVec3 p;
  CVec3 t1;
};

struct RENDVERTEX_PNT1: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  CVec2 t1;
};

struct RENDVERTEX_PNT2: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  CVec2 t1;
  CVec2 t2;
};

struct RENDVERTEX_PNT34: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  CVec4 t1;
  CVec4 t2;
  CVec4 t3;
};

struct RENDVERTEX_PNT2_1: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  CVec2 t1;
  CVec3 t2;
};

struct RENDVERTEX_PNT1TB: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  CVec2 t1;
  CVec3 tangent;
  CVec3 binormal;
};

struct RENDVERTEX_PNDT1TB: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  DWORD diffuse;
  CVec2 t1;
  CVec3 tangent;
  CVec3 binormal;
};

struct RENDVERTEX_PNDT1: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  DWORD diffuse;
  CVec2 t1;
};

struct RENDVERTEX_PNT2TB: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  CVec2 t1;
  CVec2 t2;
  CVec3 tangent;
  CVec3 binormal;
};

struct RENDVERTEX_PNT2TB_1: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  CVec2 t1;
  CVec3 t2;
  CVec3 tangent;
  CVec3 binormal;
};



//struct RENDVERTEX_PNDT1TB: public RENDVERTEX // BSP vertex Position + Normal + tex1
//{
//  CVec3 p;
//  CVec3 n;
//  DWORD diffuse;
//  CVec2 t1;
//  CVec3 tangent;
//  CVec3 binormal;
//};

struct RENDVERTEX_PNDT2: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  DWORD diffuse;
  CVec2 t1;
  CVec2 t2;
};


struct RENDVERTEX_PNDT2TB: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  DWORD diffuse;
  CVec2 t1;
  CVec2 t2;
  CVec3 tangent;
  CVec3 binormal;
};

struct RENDVERTEX_PNDT4: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec3 n;
  DWORD diffuse;
  CVec2 t1;
  CVec3 t2;
  CVec3 t3;
  CVec3 t4;
};

struct RENDVERTEX_PT3: public RENDVERTEX // BSP vertex Position + Normal + tex1
{
  CVec3 p;
  CVec2 t1;
  CVec2 t2;
  CVec2 t3;
};



struct _2DVERTEX
{
  CVec4 p;
  CVec2 t;
};
struct _3DVERTEX
{
  CVec3 p;
  CVec2 t;
};



//
struct RenderStatistics {
  int m_iObjectsDrawed;
  int m_iTrisDrawed;
  int m_iSectorsChecked;
  int m_iSectorsSkipped;
  int m_iSectorsPassed;

  RenderStatistics() : m_iObjectsDrawed(0), m_iTrisDrawed(0), m_iSectorsChecked(0), m_iSectorsSkipped(0), m_iSectorsPassed(0)   {}

  void ClearStatisctics() {
    m_iSectorsChecked = 0;
    m_iSectorsSkipped = 0;
    m_iObjectsDrawed = 0;
    m_iTrisDrawed = 0;
    m_iSectorsPassed = 0;
  }
};



typedef enum _PRIMITIVETYPE {
  RPT_POINTLIST             = 1,
  RPT_LINELIST              = 2,
  RPT_LINESTRIP             = 3,
  RPT_TRIANGLELIST          = 4,
  RPT_TRIANGLESTRIP         = 5,
  RPT_TRIANGLEFAN           = 6,
  RPT_TRIANGLENOVB          = 7,
  RPT_FORCE_DWORD           = 0x7fffffff, /* force 32-bit size enum */
} RENPRIMITIVETYPE;







