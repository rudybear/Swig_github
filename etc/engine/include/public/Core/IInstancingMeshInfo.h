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
/*


*/
#include "IMeshInfo.h"
/*!
* IInstancingMeshInfo - mesh info для вывода с помощью метода instancing
*	test.m_Params.SetParam("Mesh","cube.x");
*	test.m_Params.SetParam("Type", "instancingmesh");
*	test.m_Params.SetParam("Material", "DefaultInstance");
*	test.m_Params.SetParam("Count", "100");
*
*
*/

class IInstancingMeshInfo : public IMeshInfo
{

public:
	IInstancingMeshInfo() {};
	//! XYZ + rotation
	virtual void SetPosition(int num, CVec4& Pos) = 0;
	//! Get maximum amout of meshes in one batch
	virtual int GetMaxMeshesInBatch() = 0;
	//! Doesn't work now!
	virtual void SetColor(int num, CVec4& Pos) = 0;
	
	//! Set amount of visible objects on current frame
	virtual void SetVisibleObjects(int) = 0;
	//! Get amount of visible object on current frame
	virtual int GetVisibleObjects(void) = 0;
};
