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
#include "Public/Common/Xml_lib.h"
#include "Public/Core/IMeshInfo.h"

class IMeshInfo;
class IAnimatedMeshInfo;
class IMeshArray
{
public:
	IMeshArray(){};
	virtual ~IMeshArray(){};

	virtual IMeshInfo *AddCreateMesh(const CXmlElement * paraminfo, BOOL bSelfDraw = FALSE)=0; //Adds created from .X file mesh to Scene->MeshArray
	virtual HRESULT DeleteMesh(IMeshInfo *)=0;
	virtual void Clear() = 0;
	virtual IMeshInfo *SimpleLoadMesh(const char * szModelName,const char *szMat1 = NULL) = 0;
	virtual IAnimatedMeshInfo *SimpleLoadSkinMesh(const char * szModelName,const char *szFirstMaterialOverride = NULL,const char *szSecondMaterialOverride = NULL,const char *szThirdMaterialOverride = NULL) = 0;
	virtual void SetVisibleMesh(IMeshInfo * pInfo, BOOL bVisible) = 0;
	virtual size_t GetNumRegisteredMeshes(void) = 0;
	virtual IMeshInfo *GetMesh(size_t nNum) = 0;
	virtual uint32 GetLastFrameVisibleMeshes() = 0;
};
