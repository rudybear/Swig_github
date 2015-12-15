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

#include <map>
#include "Public/Common/Vector.h"
#include "Public/Common/Strings.h"
#include "Public/Render/NameCRC.h"
#include "Public/Render/ResFile.h"

enum ETarget
{
  eTG_Unknown,
  eTG_D3D9,
  eTG_D3D10,
  eTG_OGL,
  eTG_OGL_ES,
  eTG_FLASH, // Agal assembler
  eTG_MAX,
};

#pragma pack(push, 4)

//======================================================================================================

// SHADER MASK
// 
#define LIGHT_TYPE_MASK     		0x0000000000000FFFLL
#define SKINNING_MASK       		0x0000000000001000LL
#define ALPHA_GRADIENT_MASK     0x0000000000002000LL
#define UNDERWATER_MASK     		0x0000000000004000LL
#define BLEND_ONE_SRCA_MASK  		0x0000000000008000LL
#define INSTANCING_MASK     		0x0000000000010000LL
#define SHADOWS_MASK						0x0000000000020000LL
#define SSAO_MASK								0x0000000000040000LL
#define FOG_MASK								0x0000000000080000LL
#define DECAL_DIFFUSE_MASK			0x0000000000100000LL //  - наличие обычной текстуры
#define BUMP_DIFFUSE_MASK	  		0x0000000000200000LL //  - наличие бамп текстуры
#define TANGENT_BASIS_MASK			0x0000000000400000LL //  - наличие тангентов
#define VERTEX_COLOR_MASK 			0x0000000000800000LL //  - наличие вертекс колора
#define SPECULAR_MASK    				0x0000000001000000LL //  - наличие блеска
#define TEX_ANIMATED_MASK   		0x0000000002000000LL //  - наличие анимационной текстуры
#define SECONDARY_DIFFUSE_MASK  0x0000000004000000LL //  - наличие второй диффуз текстуры, которая будет смешиваться по вертекс колору
#define LIGHTMAP_MASK						0x0000000008000000LL //  - наличие лайтмапа
#define ENVMAP_MASK							0x0000000010000000LL //  - наличие кубмапа отражений


#define PROFILES_MASK						0x00000000E0000000LL //  - маска профилей
#define PROFILE_LOWEST_MASK			0x0000000000000000LL 
#define PROFILE_LOW_MASK				0x0000000020000000LL 
#define PROFILE_MED_MASK				0x0000000040000000LL 
#define PROFILE_HIGH_MASK				0x0000000080000000LL 
#define PROFILE_ULTRA_MASK			0x00000000E0000000LL 
#define PROFILES_SHIFT					29

#define TEX_TRANSFORM_MASK   		0x0000000100000000LL //  - наличие текстурной трансформации

#define FRESNEL_MASK						0x0000000200000000LL //  - влияние коэффициента Френеля
//#define NVIDIA_GPU_MASK   			0x0000000200000000 //  - наличие nVidia GPU

#define BENDING_MASK   					0x0000001C00000000LL //  - общая маска вертексных деформаций
#define BEND_TREE_MASK   				0x0000000400000000LL //  - деформация деревьев
#define BEND_LOCAL_MASK   			0x0000000800000000LL //  - локальная деформация 
#define BEND_GRASS_MASK   			0x0000001000000000LL //  - деформация травы

#define OPACITY_TEXTURE_MASK    0x0000002000000000LL //  - OPACITY texture
#define OPACITY_TRACK_MASK			0x0000004000000000LL //  - OPACITY track

#define SHADOW_VARIANCE_MASK		0x0000008000000000LL //  - Variance shadow maps used for terrain

#define DEBUG_MASK              0x0000030000000000LL //  - Debug shader modes
#define DEBUG_SHIFT             40										
#define DEBUG_FILLRATE_MASK     0x0000010000000000LL //  - Fill rate measuring
#define DEBUG_ALPHA_USAGE_MASK  0x0000020000000000LL //  - Texture mapping density
#define SPECIAL_BLEND_MASK	    0x0000040000000000LL //  - Racers road blend

#define LIGHTMAP_PLANAR_MASK		0x0000080000000000LL //  - наличие террейн окклюжн-мапа
#define STATIC_LIGHTING_MASK		0x0000100000000000LL //  - наличие террейн окклюжн-мапа
#define GLOW_MASK								0x0000200000000000LL //  - наличие свечения в альфа-канале диффуз текстуры
#define BLEND_ALPHA_MASK				0x0000400000000000LL //  - alpha blending
#define BLEND_ADD_MASK					0x0000800000000000LL //  - additive blending
#define RENDER_TO_TEXTURE_MASK	0x0001000000000000LL //  - means we render into the texture with simplified shading (impostors, sprites, clouds, light maps etc....)
#define LIGHTMAP_CUSTOM_MASK		0x0002000000000000LL //  - наличие custom lightmap

#define POINT_SHADOWMAP     		0x0004000000000000LL //  - для затенения тени в радиусе для теней не от солнца
#define ALPHA_TEST_MASK					0x0008000000000000LL //  - alpha test state
#define IGNORE_BRIGHTNESS_MASK	0x0010000000000000LL //  - Used for slot only
#define BLEND_MULTI_MASK				0x0020000000000000LL //  - multiplicative blending
#define FOG_LIT_MASK            0x0040000000000000LL //  - lit fog
#define TOON_MASK               0x0080000000000000LL //  - Cell shading
#define DISABLE_RTLIGHTING_MASK 0x0100000000000000LL //  - Disable RT lighting
#define MACRO_AND_MICRO_MASK    0x0200000000000000LL //  - Using macro texture + micro texture with separate texture coordinates
#define GLOSS_IN_DIFFUSEALPHA_MASK 0x0400000000000000LL //  - Gloss map - from diffuse texture alpha channel
#define BUILDING_MASK           0x0800000000000000LL //  - Building shader (2 env. cubemaps with lerp)
#define SPECULAR_IN_DIFFUSEALPHA_MASK 0x1000000000000000LL //  - Specular map - from diffuse texture alpha channel
#define GLASS_MASK              0x2000000000000000LL //  - Building shader (2 env. cubemaps with lerp)
#define DEFERRED_MASK           0x4000000000000000LL //  - Deferred shading mask
#define TEST_MASK               0x8000000000000000LL //  - Deferred shading mask

#define MAX_MASK								0x7FFFFFFFFFFFFFFFLL


typedef int64 TShaderMask;


//======================================================================================================

enum EEffectLibErrors
{
  eEL_OK = 0,
  eEL_InvalidParam,
  eEL_SrcFileNotFound,
  eEL_DstFileNotFound,
  eEL_CRCFileNotFound,
  eEL_CompilationFailed,
  eEL_VersionMismatch,
  eEL_ParsingFailed,
};

enum EShaderCombinationUsage 
{
  eSC_NotInCache,
  eSC_NotInFile,
  eSC_CRCMismatch,
  eSC_InCache,
  eSC_InPakCache,
  eSC_PreUploaded,
  eSC_SkippedCache,
  eSC_Empty
};
struct SShaderCombination
{
  Engine2::String m_Name;  // Name without extension
  uint64 m_nMask;
  uint32 m_nCRC;
  EShaderCombinationUsage m_eUsage;
};
struct SShaderFlag
{
  const char *m_szName;  // Name without extension
  uint64 m_nMask;
};

struct SFileCRC
{
  CNameCRC m_Name;  // Name with extension
  uint32 m_nCRC;
};

#define EFFECT_LIST_VERSION  3        // shaderslist.txt file
#define EFFECT_CACHE_VERSION 2        // fxc file
#define EFFECT_CACHE_REMAP_VERSION 1  // fxcm file

struct SCacheHeader
{
  uint32 m_nVersion;
  uint32 m_nSizeSelf;
  SCacheHeader()
  {
    m_nVersion = EFFECT_CACHE_VERSION;
    m_nSizeSelf = sizeof(SCacheHeader);
  }
};

typedef Engine2::Vector<SShaderCombination> TShaderCombinations;

//================================================================================

#define IDEFFHEADER		(('C'<<24)+('F'<<16)+('F'<<8)+'E')
#define EFF_VERSION 2

struct SEFFECT_DESC
{
  uint32 nRefSize;
  uint32 Magic;
  uint32 Version;
  uint32 Parameters;                  // Number of parameters
  uint32 Techniques;                  // Number of techniques
  uint32 Passes;                      // Number of passes
  uint32 States;                      // Number of states
  TShaderMask AffectMask;             // Global FX Affect Mask
  uint32 nCRC;

  SEFFECT_DESC()
  {
    Magic = IDEFFHEADER;
    Version = EFF_VERSION;
    Parameters = 0;
    Techniques = 0;
    Passes = 0;
    States = 0;
    AffectMask = -1;
  }
};
struct STECHNIQUE_DESC
{
  uint32 nRefSize;
  char Name[128];                       // Technique name
  uint32 Passes;                        // Number of passes
  int32 PassesOffs;                    // Number of passes
  uint32 Annotations;                   // Number of annotations
  STECHNIQUE_DESC()
  {
    memset(this, 0, sizeof(*this));
    PassesOffs = -1;
  }
};

enum EBLEND {
  EBLEND_ZERO               = 1,
  EBLEND_ONE                = 2,
  EBLEND_SRCCOLOR           = 3,
  EBLEND_INVSRCCOLOR        = 4,
  EBLEND_SRCALPHA           = 5,
  EBLEND_INVSRCALPHA        = 6,
  EBLEND_DESTALPHA          = 7,
  EBLEND_INVDESTALPHA       = 8,
  EBLEND_DESTCOLOR          = 9,
  EBLEND_INVDESTCOLOR       = 10,
  EBLEND_SRCALPHASAT        = 11,
  EBLEND_BOTHSRCALPHA       = 12,
  EBLEND_BOTHINVSRCALPHA    = 13,
  EBLEND_BLENDFACTOR        = 14, /* Only supported if D3DPBLENDCAPS_BLENDFACTOR is on */
  EBLEND_INVBLENDFACTOR     = 15, /* Only supported if D3DPBLENDCAPS_BLENDFACTOR is on */

  EBLEND_FORCE_DWORD        = 0x7fffffff, /* force 32-bit size enum */
};

enum ERENDERSTATETYPE {
  ERS_UNKNOWN                   = 0,
  ERS_ZENABLE                   = 7,    /* D3DZBUFFERTYPE (or TRUE/FALSE for legacy) */
  ERS_FILLMODE                  = 8,    /* D3DFILLMODE */
  ERS_SHADEMODE                 = 9,    /* D3DSHADEMODE */
  ERS_ZWRITEENABLE              = 14,   /* TRUE to enable z writes */
  ERS_ALPHATESTENABLE           = 15,   /* TRUE to enable alpha tests */
  ERS_LASTPIXEL                 = 16,   /* TRUE for last-pixel on lines */
  ERS_SRCBLEND                  = 19,   /* D3DBLEND */
  ERS_DESTBLEND                 = 20,   /* D3DBLEND */
  ERS_CULLMODE                  = 22,   /* D3DCULL */
  ERS_ZFUNC                     = 23,   /* D3DCMPFUNC */
  ERS_ALPHAREF                  = 24,   /* D3DFIXED */
  ERS_ALPHAFUNC                 = 25,   /* D3DCMPFUNC */
  ERS_DITHERENABLE              = 26,   /* TRUE to enable dithering */
  ERS_ALPHABLENDENABLE          = 27,   /* TRUE to enable alpha blending */
  ERS_FOGENABLE                 = 28,   /* TRUE to enable fog blending */
  ERS_SPECULARENABLE            = 29,   /* TRUE to enable specular */
  ERS_FOGCOLOR                  = 34,   /* D3DCOLOR */
  ERS_FOGTABLEMODE              = 35,   /* D3DFOGMODE */
  ERS_FOGSTART                  = 36,   /* Fog start (for both vertex and pixel fog) */
  ERS_FOGEND                    = 37,   /* Fog end      */
  ERS_FOGDENSITY                = 38,   /* Fog density  */
  ERS_RANGEFOGENABLE            = 48,   /* Enables range-based fog */
  ERS_STENCILENABLE             = 52,   /* BOOL enable/disable stenciling */
  ERS_STENCILFAIL               = 53,   /* D3DSTENCILOP to do if stencil test fails */
  ERS_STENCILZFAIL              = 54,   /* D3DSTENCILOP to do if stencil test passes and Z test fails */
  ERS_STENCILPASS               = 55,   /* D3DSTENCILOP to do if both stencil and Z tests pass */
  ERS_STENCILFUNC               = 56,   /* D3DCMPFUNC fn.  Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
  ERS_STENCILREF                = 57,   /* Reference value used in stencil test */
  ERS_STENCILMASK               = 58,   /* Mask value used in stencil test */
  ERS_STENCILWRITEMASK          = 59,   /* Write mask applied to values written to stencil buffer */
  ERS_TEXTUREFACTOR             = 60,   /* D3DCOLOR used for multi-texture blend */
  ERS_WRAP0                     = 128,  /* wrap for 1st texture coord. set */
  ERS_WRAP1                     = 129,  /* wrap for 2nd texture coord. set */
  ERS_WRAP2                     = 130,  /* wrap for 3rd texture coord. set */
  ERS_WRAP3                     = 131,  /* wrap for 4th texture coord. set */
  ERS_WRAP4                     = 132,  /* wrap for 5th texture coord. set */
  ERS_WRAP5                     = 133,  /* wrap for 6th texture coord. set */
  ERS_WRAP6                     = 134,  /* wrap for 7th texture coord. set */
  ERS_WRAP7                     = 135,  /* wrap for 8th texture coord. set */
  ERS_CLIPPING                  = 136,
  ERS_LIGHTING                  = 137,
  ERS_AMBIENT                   = 139,
  ERS_FOGVERTEXMODE             = 140,
  ERS_COLORVERTEX               = 141,
  ERS_LOCALVIEWER               = 142,
  ERS_NORMALIZENORMALS          = 143,
  ERS_DIFFUSEMATERIALSOURCE     = 145,
  ERS_SPECULARMATERIALSOURCE    = 146,
  ERS_AMBIENTMATERIALSOURCE     = 147,
  ERS_EMISSIVEMATERIALSOURCE    = 148,
  ERS_VERTEXBLEND               = 151,
  ERS_CLIPPLANEENABLE           = 152,
  ERS_POINTSIZE                 = 154,   /* float point size */
  ERS_POINTSIZE_MIN             = 155,   /* float point size min threshold */
  ERS_POINTSPRITEENABLE         = 156,   /* BOOL point texture coord control */
  ERS_POINTSCALEENABLE          = 157,   /* BOOL point size scale enable */
  ERS_POINTSCALE_A              = 158,   /* float point attenuation A value */
  ERS_POINTSCALE_B              = 159,   /* float point attenuation B value */
  ERS_POINTSCALE_C              = 160,   /* float point attenuation C value */
  ERS_MULTISAMPLEANTIALIAS      = 161,  // BOOL - set to do FSAA with multisample buffer
  ERS_MULTISAMPLEMASK           = 162,  // DWORD - per-sample enable/disable
  ERS_PATCHEDGESTYLE            = 163,  // Sets whether patch edges will use float style tessellation
  ERS_DEBUGMONITORTOKEN         = 165,  // DEBUG ONLY - token to debug monitor
  ERS_POINTSIZE_MAX             = 166,   /* float point size max threshold */
  ERS_INDEXEDVERTEXBLENDENABLE  = 167,
  ERS_COLORWRITEENABLE          = 168,  // per-channel write enable
  ERS_TWEENFACTOR               = 170,   // float tween factor
  ERS_BLENDOP                   = 171,   // D3DBLENDOP setting
  ERS_POSITIONDEGREE            = 172,   // NPatch position interpolation degree. D3DDEGREE_LINEAR or D3DDEGREE_CUBIC (default)
  ERS_NORMALDEGREE              = 173,   // NPatch normal interpolation degree. D3DDEGREE_LINEAR (default) or D3DDEGREE_QUADRATIC
  ERS_SCISSORTESTENABLE         = 174,
  ERS_SLOPESCALEDEPTHBIAS       = 175,
  ERS_ANTIALIASEDLINEENABLE     = 176,
  ERS_MINTESSELLATIONLEVEL      = 178,
  ERS_MAXTESSELLATIONLEVEL      = 179,
  ERS_ADAPTIVETESS_X            = 180,
  ERS_ADAPTIVETESS_Y            = 181,
  ERS_ADAPTIVETESS_Z            = 182,
  ERS_ADAPTIVETESS_W            = 183,
  ERS_ENABLEADAPTIVETESSELLATION = 184,
  ERS_TWOSIDEDSTENCILMODE       = 185,   /* BOOL enable/disable 2 sided stenciling */
  ERS_CCW_STENCILFAIL           = 186,   /* D3DSTENCILOP to do if ccw stencil test fails */
  ERS_CCW_STENCILZFAIL          = 187,   /* D3DSTENCILOP to do if ccw stencil test passes and Z test fails */
  ERS_CCW_STENCILPASS           = 188,   /* D3DSTENCILOP to do if both ccw stencil and Z tests pass */
  ERS_CCW_STENCILFUNC           = 189,   /* D3DCMPFUNC fn.  ccw Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
  ERS_COLORWRITEENABLE1         = 190,   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
  ERS_COLORWRITEENABLE2         = 191,   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
  ERS_COLORWRITEENABLE3         = 192,   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
  ERS_BLENDFACTOR               = 193,   /* D3DCOLOR used for a constant blend factor during alpha blending for devices that support D3DPBLENDCAPS_BLENDFACTOR */
  ERS_SRGBWRITEENABLE           = 194,   /* Enable rendertarget writes to be DE-linearized to SRGB (for formats that expose D3DUSAGE_QUERY_SRGBWRITE) */
  ERS_DEPTHBIAS                 = 195,
  ERS_WRAP8                     = 198,   /* Additional wrap states for vs_3_0+ attributes with ERGS_TEXCOORD */
  ERS_WRAP9                     = 199,
  ERS_WRAP10                    = 200,
  ERS_WRAP11                    = 201,
  ERS_WRAP12                    = 202,
  ERS_WRAP13                    = 203,
  ERS_WRAP14                    = 204,
  ERS_WRAP15                    = 205,
  ERS_SEPARATEALPHABLENDENABLE  = 206,  /* TRUE to enable a separate blending function for the alpha channel */
  ERS_SRCBLENDALPHA             = 207,  /* SRC blend factor for the alpha channel when ERS_SEPARATEDESTALPHAENABLE is TRUE */
  ERS_DESTBLENDALPHA            = 208,  /* DST blend factor for the alpha channel when ERS_SEPARATEDESTALPHAENABLE is TRUE */
  ERS_BLENDOPALPHA              = 209,  /* Blending operation for the alpha channel when ERS_SEPARATEDESTALPHAENABLE is TRUE */

  ERS_FORCE_DWORD               = 0x7fffffff, /* force 32-bit size enum */
};
struct SSTATE_DESC
{
  uint32 nRefSize;
  ERENDERSTATETYPE State;
  uint32 Value;
  SSTATE_DESC()
  {
    memset(this, 0, sizeof(*this));
  }
};
struct SPASS_DESC
{
  uint32 nRefSize;
  char Name[64];                 // Pass name
  uint32 Annotations;            // Number of annotations
  int nStatesSize;
  int nStatesOffs;
  int nVertexShaderParamOffs;    
  int nVertexShaderParamSize;    
  int nPixelShaderParamOffs;    
  int nPixelShaderParamSize;    
  int nPixelShaderNameOffs;
  int nVertexShaderNameOffs;    
  int pad00;
  int pad01;  
  TShaderMask nMaskVS;
  TShaderMask nMaskPS;

  
  SPASS_DESC()
  {
    memset(this, 0, sizeof(*this));
    nVertexShaderParamOffs = -1;
    nPixelShaderParamOffs = -1;
    nPixelShaderNameOffs = -1;
    nVertexShaderNameOffs = -1;
    nStatesOffs = -1;
  }
};

enum EREGISTER_SET
{
  ERGS_UNKNOWN,
  ERGS_ATTR0,
  ERGS_ATTR1,
  ERGS_ATTR2,
  ERGS_ATTR3,
  ERGS_ATTR4,
  ERGS_ATTR5,
  ERGS_ATTR6,
  ERGS_ATTR7,
  ERGS_ATTR8,
  ERGS_ATTR9,
  ERGS_ATTR10,
  ERGS_ATTR11,
  ERGS_ATTR12,
  ERGS_ATTR13,
  ERGS_ATTR14,
  ERGS_ATTR15,

  ERGS_POSITION,
  ERGS_BLENDWEIGHT,   // 1
  ERGS_BLENDINDICES,  // 2
  ERGS_NORMAL,        // 3
  ERGS_PSIZE,         // 4
  ERGS_TEXCOORD,      // 5
  ERGS_TANGENT,       // 6
  ERGS_BINORMAL,      // 7
  ERGS_TESSFACTOR,    // 8
  ERGS_POSITIONT,     // 9
  ERGS_COLOR,         // 10
  ERGS_FOG,           // 11
  ERGS_DEPTH,         // 12
  ERGS_SAMPLE,        // 13

  ERGS_BOOL,
  ERGS_INT4,
  ERGS_FLOAT4,
  ERGS_MAT4,
  ERGS_SAMPLER,

  // force 32-bit size enum
  ERGS_FORCE_DWORD = 0x7fffffff
};
enum EPARAMETER_CLASS
{
  PC_SCALAR,
  PC_VECTOR,
  PC_MATRIX_ROWS,
  PC_MATRIX_COLUMNS,
  PC_OBJECT,
  PC_STRUCT,
  PC_INPUT,

  // force 32-bit size enum
  PC_FORCE_DWORD = 0x7fffffff
};
enum EPARAMETER_TYPE
{
  PT_VOID,
  PT_BOOL,
  PT_INT,
  PT_FLOAT,
  PT_STRING,
  PT_TEXTURE,
  PT_TEXTURE1D,
  PT_TEXTURE2D,
  PT_TEXTURE3D,
  PT_TEXTURECUBE,
  PT_SAMPLER,
  PT_SAMPLER1D,
  PT_SAMPLER2D,
  PT_SAMPLER3D,
  PT_SAMPLERCUBE,
  PT_PIXELSHADER,
  PT_VERTEXSHADER,
  PT_PIXELFRAGMENT,
  PT_VERTEXFRAGMENT,
  PT_UNSUPPORTED,

  // force 32-bit size enum
  PT_FORCE_DWORD = 0x7fffffff
};
struct SPARAM_DESC
{
  uint32 nRefSize;
  char Name[64];                   // Constant name
  char ResName[64];                // GLSL resource name

  EREGISTER_SET RegisterSet;       // Register set
  uint32 RegisterIndex;            // Register index
  uint32 RegisterCount;            // Number of registers occupied

  EPARAMETER_CLASS Class;           // Class
  EPARAMETER_TYPE Type;             // Component type

  uint32 Rows;                      // Number of rows
  uint32 Columns;                   // Number of columns
  uint32 Elements;                  // Number of array elements
  uint32 StructMembers;             // Number of structure member sub-parameters

  uint32 DefaultValueSize;          // Data size, in bytes
  int32  DefaultValueOffs;               // Pointer to default value

  int8  MinFilter;
  int8  MagFilter;
  int8  MipFilter;
  int8  AddressU;
  int8  AddressV;
  int8  AddressW;
  int16 pad00;
  uint32 BorderColor;
  float MaxMipLevel;
  SPARAM_DESC()
  {
    memset(this, 0, sizeof(*this));
    DefaultValueOffs = -1;
    MinFilter = MagFilter = MipFilter = -1;
    AddressU = AddressV = AddressW = -1;
    BorderColor = -1;
  }
};
struct SREMAP_DESC_H
{
  uint32 nRefSize;
  int nVersion;
  uint32 nCRC;
  TShaderMask nAffectMask;
};
struct SREMAP_DESC_ENTRY
{
  char szName[64];
  int nCombinations;
};
struct SREMAP_ITEM
{
  TShaderMask nMask;
  TShaderMask nRefMask;
};

typedef std::map<TShaderMask, Engine2::String> MapShaderFlags;

struct SExclTarget
{
  unsigned short TargetFlags;        // 1<<eTG_ (0x8000 - Force)
  unsigned char ProfileFlags;   // 1<<(Lowest, Low, Medium, High, Highest)
  unsigned char TypeFlags;      // 1:VS, 2:PS, 4:GS, 8:DS, 16:HS;

  SExclTarget()
  {
    TargetFlags = 0;
    ProfileFlags = 0;
    TypeFlags = 0xff; // Exclude all kind of shaders by default
  }
};

struct SShaderProp
{
  char Name[32];
  TShaderMask Mask;
  TShaderMask CurMaskAnd;
  TShaderMask CurMaskOr;
  unsigned int CurTypeMask;  // VS, PS, GS, DS, HS
  Engine2::Vector<SExclTarget> ETargets;
  Engine2::Vector<Engine2::String> ExclShaders;
};

struct SShaderProps
{
  Engine2::Vector<SShaderProp> m_Props;
  Engine2::Vector<Engine2::String> m_BlackLists[eTG_MAX];
  Engine2::Vector<Engine2::String> m_Lighting[3];
  ETarget m_eCurTarget;
  int m_nCurProfile;
  bool m_bUseCG;
  TShaderMask m_CurGlobalMaskAnd;
  TShaderMask m_CurGlobalMaskOr;
  TShaderMask m_CurMaskAnd[2];  // VS, PS
  TShaderMask m_CurMaskOr[2];  // VS, PS

  SShaderProps()
  {
    m_bUseCG = false;
    m_eCurTarget = eTG_Unknown;
    m_nCurProfile = -1;
    m_CurGlobalMaskAnd = -1;
    m_CurGlobalMaskOr = 0;
    m_CurMaskAnd[0] = m_CurMaskAnd[1] = -1;
    m_CurMaskOr[0] = m_CurMaskOr[1] = 0;
  }

  void Clear() { m_Props.clear(); }
  void Add(TShaderMask nMask, const char *szName) {
    SShaderProp Prop;
    strncpy_s(Prop.Name, szName, 32);
    Prop.Mask = nMask;
    Prop.CurMaskAnd = 0;
    Prop.CurMaskOr = 0;
    m_Props.push_back(Prop);
  }
};

struct SZipDirEntry
{
  int nInd;
  int nSize;
  CNameCRC nName;
};

class IEffectsLib
{
protected:
  //MapShaderFlags m_ShaderFlags;
  //Engine2::Vector<SShaderFlag> m_ShaderFlagsArray;
  SShaderProps m_ShaderProps;

  bool UpdateShaderFlags();
  void InitShaderFlags(const char *pXmlShaderProps);
public:
  SShaderProp *GetShaderFlag(const char *szName)
  {
    for (unsigned int i=0; i<m_ShaderProps.m_Props.size(); i++)
    {
      SShaderProp& Prop = m_ShaderProps.m_Props[i];
      if (!strcmp(Prop.Name, szName))
        return &Prop;
    }
    return NULL;
  }
  TShaderMask GetShaderMaskAnd() { return m_ShaderProps.m_CurGlobalMaskAnd; }
  TShaderMask GetShaderMaskOr() { return m_ShaderProps.m_CurGlobalMaskOr; }
  const SShaderProps& GetShaderProps() { return m_ShaderProps; }

public:
  virtual const SShaderProp *GetAllShaderFlags() = 0;
  virtual TShaderMask GetMaskForString(const char *szStr, bool &bError) = 0;
  virtual void FillShaderDefinitions(TShaderMask mask, Engine2::Vector<Engine2::String>& defines, bool bInsertEqual) = 0;
  virtual uint32 GetEffectCRC(const char *effect, const char *path) = 0;
  virtual TShaderMask GetShaderMask(const char* effect, const char *path) = 0;
  virtual EEffectLibErrors UpdateCRC(const Engine2::Vector<Engine2::String>& Files, const char *szDstFile) = 0;
  virtual EEffectLibErrors GetEffectCombinationsForListFile(TShaderCombinations& Combinations, const char *szListFile) = 0;
  virtual EEffectLibErrors GetEffectCombinationsForCachePath(TShaderCombinations& Combinations, const char *szCachePath, const char *szCRCFile) = 0;
  virtual EEffectLibErrors CompileEffects(const TShaderCombinations *pCombinations, const char *szSrcPath, const char *szCRCFile, const char *szDstPath, const char *szListFile, bool bIncremental, bool bRecompileExisting=true, Engine2::String *pErrors=NULL) = 0;
  virtual EEffectLibErrors CompileEffect(const char *szSrcFile, uint64 nMask, const char *szCRCFile, const char *szDstFile, const char *szListFile, uint64 nDate=0) = 0;
  virtual bool CompileEffect(const char *szSrcFile, const char *szDstPath, const Engine2::Vector<Engine2::String>& Defines, char *szError, int nErrSize, bool bDebug, const char *szEntry=NULL, void *ShaderInfo=NULL, uint32 nCRC=0) = 0;
  virtual EEffectLibErrors PackEffects(const char *szSrcPath, const char *szDstPath, const char *szCRCFile) = 0;
  virtual EEffectLibErrors GenerateEffect(const char *szSrcFile, const char *szCRCFile, const char *szDstPath, bool bDebug, char *szError) = 0;
  virtual EEffectLibErrors GenerateEffects(const char *szSrcPath, const char *szDstPath, char *&szError, bool bIncremental) = 0;
  virtual const char *GetPackName(int nType, int nProfile) = 0;
  virtual EEffectLibErrors Decompress(unsigned char *pInData, unsigned char *pOutData, int nCompSize, int nUncompSize) = 0;
  virtual void SetTarget(ETarget eTG) = 0;
  virtual void SetProfile(int nProfile) { m_ShaderProps.m_nCurProfile = nProfile; UpdateShaderFlags(); }
  virtual ETarget GetTarget() = 0;
  virtual bool OpenLog(const char *szName, bool bOverwrite) = 0;
  virtual void CloseLog() = 0;

  virtual int OpenZPak(const char *szPackName) = 0;
  virtual bool CloseZPak(int nHandle) = 0;
  virtual bool GetZPakDir(int nHandle, std::vector<SZipDirEntry>& Dir) = 0;
  virtual bool ReadZPakFile(int nHandle, const SZipDirEntry& de, Engine2::Vector<unsigned char>& Content) = 0;
  virtual bool ZPackShaders(const char *szDstPath, const char *szPakName) = 0;
};

#pragma pack(pop)

extern IEffectsLib *CreateEffectsLib(const char *pXmlShaderProps);

