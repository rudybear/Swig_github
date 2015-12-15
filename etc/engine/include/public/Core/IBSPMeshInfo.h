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

#include "IMeshInfo.h"
//#include "public\Render\IBSPShader.h"
/*!
*	IBSPMeshInfo - интерфейс BSP меша. 
*/
class IVisibilityEntity;
class CXmlElement;

class IBSPMeshInfo : public IMeshInfo
{
public:
	//! Добавляет меш в bsp, для более эффективного определения видимости. Возвращает номер кластера
	virtual int AddMeshToBSP(IMeshInfo * mesh, CVec3 * pos) = 0; 
	virtual void DeleteMesh(IMeshInfo * mesh) = 0;

	//! May be need create a new interface for this functions?
	virtual bool RegistryEntity(IVisibilityEntity*) = 0; //при регистрации чекается видимость первый раз
	virtual bool UnRegistryEntity(IVisibilityEntity*) = 0;


	//! получить из BSP информацию о Entityes, которые в нём хранятся.
	virtual CXmlElement * GetEnityesXML(void) = 0;

	//! получить из BSP информацию о BSP модели связаной с энтити
	virtual CAABBox * GetBrushModelBBox(int nBrushModelID) = 0;

	//! Что-то подобное и для трассировки приделаем
//	virtual HRESULT AddDecal(CVec3 vecOrigin, CVec3 vecDirection, float fRadius) = 0;
	virtual int AddDecal(CVec3 vecOrigin, CVec3 vecDirection, float fRadius,const char * name) = 0;
	virtual int AddDecal(CVec3 vecOrigin, CVec3 vecDirection, float fRadius, int ) = 0;

	virtual const char *TraceShader(CVec3 vecOrigin, CVec3 vecDirection, CVec3 * vecPosition, CVec3 * vecNormal, bool bOnlySolid = true) = 0;

	virtual void AddLight(ILight *) = 0;
	virtual void DeleteLight(ILight *) = 0;

};