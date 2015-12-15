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

struct sHardwareConfig
{
    UINT    AdapterOrdinal;
    DWORD   MaxTextureWidth, MaxTextureHeight;
    DWORD   MaxVolumeExtent;
    DWORD   MaxTextureRepeat;
    DWORD   MaxTextureAspectRatio;
    DWORD   MaxAnisotropy;
    float   MaxVertexW;
//    DWORD   StencilCaps;
    DWORD   MaxTextureBlendStages;
    DWORD   MaxSimultaneousTextures;
    DWORD   MaxActiveLights;
    DWORD   MaxUserClipPlanes;
    DWORD   MaxVertexBlendMatrices;
    DWORD   MaxVertexBlendMatrixIndex;
    float   MaxPointSize;
    DWORD   MaxPrimitiveCount;          // max number of primitives per DrawPrimitive call
    DWORD   MaxVertexIndex;
    DWORD   MaxStreams;
    DWORD   MaxStreamStride;            // max stride for SetStreamSource
    DWORD   VertexShaderVersion;
    DWORD   MaxVertexShaderConst;       // number of vertex shader constant registers
    DWORD   PixelShaderVersion;
    float   PixelShader1xMaxValue;      // max value storable in registers of ps.1.x shaders
    float   MaxNpatchTessellationLevel;
    DWORD   MaxVShaderInstructionsExecuted; // maximum number of vertex shader instructions that can be executed
    DWORD   MaxPShaderInstructionsExecuted; // maximum number of pixel shader instructions that can be executed
    DWORD   MaxVertexShader30InstructionSlots; 
    DWORD   MaxPixelShader30InstructionSlots;
    bool    SupportsVertexFetch;
    bool    SupportsAutogenMips;
    bool    SupportsDepthTexture; // requires extensions on WebGL
    bool    SupportsTextureLod; // requires extensions on WebGL

    DWORD   VendorID;
    DWORD   DeviceID;

    Engine2::String m_sDeviceName;
    Engine2::String m_sDeviceString;
    Engine2::String m_sBigIDLine;
    Engine2::String m_sCPU;

	sHardwareConfig()
    : AdapterOrdinal()
    , MaxTextureWidth()
	, MaxTextureHeight()
    , MaxVolumeExtent()
    , MaxTextureRepeat()
    , MaxTextureAspectRatio()
    , MaxAnisotropy()
    , MaxVertexW()
    , MaxTextureBlendStages()
    , MaxSimultaneousTextures()
    , MaxActiveLights()
    , MaxUserClipPlanes()
    , MaxVertexBlendMatrices()
    , MaxVertexBlendMatrixIndex()
    , MaxPointSize()
    , MaxPrimitiveCount()
    , MaxVertexIndex()
    , MaxStreams()
    , MaxStreamStride()
    , VertexShaderVersion()
    , MaxVertexShaderConst()
    , PixelShaderVersion()
    , PixelShader1xMaxValue()
    , MaxNpatchTessellationLevel()
    , MaxVShaderInstructionsExecuted()
    , MaxPShaderInstructionsExecuted()
    , MaxVertexShader30InstructionSlots()
    , MaxPixelShader30InstructionSlots()
    , SupportsVertexFetch()
    , SupportsAutogenMips()
    , SupportsDepthTexture()
    , SupportsTextureLod()
    , VendorID()
    , DeviceID()
	{
	}
};
