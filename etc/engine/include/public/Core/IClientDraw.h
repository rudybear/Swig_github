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

#include <list>
#include <map>
#include "Public/Render/IGameRenderObject.h"
#include "Public/Core/IMeshBuildermeshInfo.h"

class IGameRenderObject;
class IClientDraw
{
public:
	IClientDraw()
	{
		m_bClientDrawDeleteOnFrameEnd = FALSE;
		m_bDrawAlready = false;
		m_nDrawTextureID = -1;
		m_bFreed = TRUE;
	};

	BOOL m_bFreed;
	~IClientDraw()
	{
		assert(m_bFreed);
		if(!m_bFreed)
		{
		}
	};

	virtual HRESULT Draw(void) = 0;
	virtual HRESULT Draw2D(void) = 0;
	BOOL m_bClientDrawDeleteOnFrameEnd;

	int m_nDrawTextureID; // used to Draw in CBaseMod
	bool m_bDrawAlready; // -1 - means multiple textures

public:
	IGameRenderObject * m_pClientRenderObject;
	int m_nTextureID;
};


class ClientDrawersHashEntry
{
public:
	ClientDrawersHashEntry(){
		m_nClientDrawerTextureID = -2;
		m_nBlendFuncID = -1;
		m_nDepthFuncID = -1;
	};
	ClientDrawersHashEntry(int ID,int nBlendID,int nDepth){
		m_nClientDrawerTextureID = ID;
		m_nBlendFuncID = nBlendID;
		m_nDepthFuncID = nDepth;
	};

	~ClientDrawersHashEntry(){};


	//	CClientDrawersList m_DrawersPointersList;
	std::map<long long,IClientDraw*> m_ClientDrawersLinked;
	std::map<long long,IClientDraw*>::iterator m_ClientDrawersLinkedI;
	int m_nClientDrawerTextureID;
	int m_nBlendFuncID;
	int m_nDepthFuncID;
};


class CMeshBuilderDrawer : public ICallbackDrawer
{
protected:
	BOOL m_bClientDrawDeleteOnFrameEnd;

public:


};


