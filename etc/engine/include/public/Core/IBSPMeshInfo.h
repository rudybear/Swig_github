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
*	IBSPMeshInfo - ��������� BSP ����. 
*/
class IVisibilityEntity;
class CXmlElement;

class IBSPMeshInfo : public IMeshInfo
{
public:
	//! ��������� ��� � bsp, ��� ����� ������������ ����������� ���������. ���������� ����� ��������
	virtual int AddMeshToBSP(IMeshInfo * mesh, CVec3 * pos) = 0; 
	virtual void DeleteMesh(IMeshInfo * mesh) = 0;

	//! May be need create a new interface for this functions?
	virtual bool RegistryEntity(IVisibilityEntity*) = 0; //��� ����������� �������� ��������� ������ ���
	virtual bool UnRegistryEntity(IVisibilityEntity*) = 0;


	//! �������� �� BSP ���������� � Entityes, ������� � �� ��������.
	virtual CXmlElement * GetEnityesXML(void) = 0;

	//! �������� �� BSP ���������� � BSP ������ �������� � ������
	virtual CAABBox * GetBrushModelBBox(int nBrushModelID) = 0;

	//! ���-�� �������� � ��� ����������� ���������
//	virtual HRESULT AddDecal(CVec3 vecOrigin, CVec3 vecDirection, float fRadius) = 0;
	virtual int AddDecal(CVec3 vecOrigin, CVec3 vecDirection, float fRadius,const char * name) = 0;
	virtual int AddDecal(CVec3 vecOrigin, CVec3 vecDirection, float fRadius, int ) = 0;

	virtual const char *TraceShader(CVec3 vecOrigin, CVec3 vecDirection, CVec3 * vecPosition, CVec3 * vecNormal, bool bOnlySolid = true) = 0;

	virtual void AddLight(ILight *) = 0;
	virtual void DeleteLight(ILight *) = 0;

};