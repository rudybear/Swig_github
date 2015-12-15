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

struct SRenderGraph
{
  const char *m_szName;
  DWORD m_dwColor;
  double *m_pValue;
};

#define FS_PERFRAME_ONLY 1
#define FS_PERFRAME_PROFILE_ONLY 2

struct SRenderStatistics : public SCoreStatistics{
  
  const sHardwareConfig * m_pVideoHardwareConfig;

  float m_iFps; // current fps
  int  m_lFrameNum; // current frame number
  int m_lTrianglesPerFrame; // current rendered polygons
  int m_iBatchesPerFrame; // current number of batches
  int m_iBatchGroupsPerFrame; // current number of batches
  int m_lTrisPerSec; /// current tris per sec
  float m_fElapsedTime; // last frame time
  int m_iShadersPerFrame; // number of active shaders
  uint32 m_iUsedTexMemory; // Used texture memory
  uint32 m_iTotalMaterials; // Total number of materials
  uint32 m_iBonesPerFrame; // total bones updated per frame
  uint32 m_iTotalObjects; // Total objects
  uint32 m_iTotalInstances; // Total instances - render instances
  uint32 m_iTotalObjectsInstances; // Total instances of objects 
  uint32 m_iVisibleObjectsPerFrame; // Visible objects per frame

  uint32 m_nStatsChanges;
  uint32 m_nTexturesChanges;
  uint32 m_nShadersChanges;
  uint32 m_nShaderParams;

  float m_fProfScene;
  float m_fProfDoBatch;
  float m_fProfPresent;
  float m_fProfSamplers;
  float m_fProfShader;
  float m_fProfShaderParams;
  float m_fProfShaderParamsPI;
  float m_fProfStreams;
  float m_fProfDIPs;

  SRenderStatistics() {
    m_fProfScene = 0;
    m_fProfDoBatch = 0;
    m_fProfPresent = 0;
    m_nStatsChanges = 0;
    m_nTexturesChanges = 0;
    m_nShadersChanges = 0;
    m_nShaderParams = 0;

    m_pVideoHardwareConfig = 0;
    m_iFps = 0.0f;
    m_lFrameNum = 0;
    m_lTrianglesPerFrame = 0;
    m_iBatchesPerFrame = 0;
    m_lTrisPerSec = 0;
    m_fElapsedTime = 0.0f;
    m_iShadersPerFrame = 0;
    m_iUsedTexMemory = 0;
    m_iTotalMaterials = 0;
    m_iTotalObjects = 0;
    m_iTotalInstances = 0;
    m_iVisibleObjectsPerFrame = 0;
    m_iTotalObjectsInstances = 0;
  }
};


