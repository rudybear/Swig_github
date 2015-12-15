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

#include "Public/Common/Vector.h"

enum eAsyncState
{
  eMeshCreated,
  eRequested,
  eReady,
  eProcessing,
  eWaitClientResponse,
  eInMemory, // patch ready
  eLODChanged, //patch changed his LOD
  eReleased, // patch is already released
  eNotFound
};

enum eMeshType {
  eBaseMesh,
  eAnimMesh,
  eStaticMeshBuilderMesh,
  eDynamicMeshBuilderMesh,
  eSkydomeMesh,
  eSkyboxMesh,
  eCloudsMesh,
  eDecalMesh,
  eCoronaMesh,
  eBSPMesh,
  eLightShaftMesh,
  eTerrainMesh,
  eIndoorMesh,
  ePatch,
	eParticleMesh,
  eEffectMesh,
  eClientMesh,
  eEngineMesh,
  eRainAreaMesh,
  eOceanMesh,
  eSystem,
  eInstancedMesh,
  eUnknownMesh
};


struct PatchNotification
{
  int m_iPatchX;
  int m_iPatchZ;
  int m_iLOD;
  eAsyncState m_CurrentState;
};

typedef Engine2::Vector<PatchNotification> TPatchNotificationVector;
