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

class IBSPGeometry
{
public:
	virtual int GetFaces() = 0;
	virtual int GetTris(int nFace) = 0;
	virtual BOOL GetTriangle(int iFace, int iTriangle, CTriangle* out) = 0;
};