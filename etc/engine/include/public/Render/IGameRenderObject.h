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

#include "Public/Common/Mathlib.h"
/*#include "Render.h"
#include "RenderObject.h"
*/

// Obsolete class. Use only for debug purposes!

struct GAMERENDERVERTEX
{
	CVec3 v;
	int color;
	CVec2 t1;
};

struct RENDER2DVERTEXBase
{

};

struct RENDER2DVERTEX : public RENDER2DVERTEXBase
{
  CVec4 v;
	DWORD color; 
	CVec2 t1;
};

struct RENDER2DVERTEX1 : public RENDER2DVERTEXBase
{
  CVec4 v;
  DWORD color; 
  CVec2 t1;
  CVec2 t2;
};


class IGameRenderObject
{

public:
	IGameRenderObject(void){}
	virtual ~IGameRenderObject(void){}

	virtual void BeginScene()=0;
	virtual void EndScene()=0;
  virtual HRESULT SetTexture(int, int SrcBlend, int DstBlend)=0;
	virtual HRESULT SetTexture(int, int Blend = -1)=0;
	virtual HRESULT SetTexture2D(int, int Blend = -1, int depth = 1)=0;
  virtual HRESULT SetTexture2D(int, int SrcBlend, int DstBlend, int Depth)=0;
	virtual void SetTransform2D(const CMatrix44& transform)=0;
  virtual HRESULT SetScissor(int nX=0, int nY=0, int nW=0, int nH=0)=0; // Scissor disabled if nW or nH <= 0
  virtual HRESULT SetScissor2D(int nX=0, int nY=0, int nW=0, int nH=0)=0; // Scissor disabled if nW or nH <= 0
	virtual HRESULT SetDepthFunc(int DF)=0;
	virtual HRESULT SetCullFunc(int CF) = 0;
	virtual HRESULT SetFillMode(int FM) = 0;
	virtual HRESULT SetAlphaFunc(int AF, int AV = 0)=0;
  virtual HRESULT SetAlphaFunc2D(int AF, int AV = 0)=0;
	virtual void DrawTriangle(GAMERENDERVERTEX *)=0;
	virtual void DrawTriangleList(GAMERENDERVERTEX *, int)=0;
	virtual void DrawLine(GAMERENDERVERTEX *)=0;
	virtual void DrawLineList(GAMERENDERVERTEX *, int)=0;
	virtual void DrawTriangle2D(RENDER2DVERTEX *) = 0;
	virtual void DrawTriangle2DList(RENDER2DVERTEX *, int)=0; // второй параметр - количество треугольников!!!!
	virtual void DrawLine2D(RENDER2DVERTEX *) = 0;
	virtual void DrawLine2DList(RENDER2DVERTEX *, int)=0; // второй параметр - количество треугольников!!!!
	virtual void DrawAABB(const CAABBox& box, int color) = 0;
  virtual void DrawImage2D(float x, float y, float width, float height, int ntexture) = 0;



	//	void ClearPool();

};

class CCamera;

class IGUIRenderObject;
class IMeshInfo;
// Special interface for render to texture
class IRenderToTextureObject  {
public:
	// gui render object

  virtual void SetUserViewport(bool ) = 0;
	virtual IGUIRenderObject * GetGUIRenderObject() = 0;
	virtual IGameRenderObject * GetGameRenderObject() = 0;
  virtual int GetTexture() = 0;

  virtual void AddRenderMesh(IMeshInfo * pInfo) = 0;

  virtual void SetCamera(CCamera * cam) = 0;
  virtual void SetActiveWeather(size_t ) = 0;

	// start rendering to texture
	// return false if we have got problems with destination texture or another internal render problems
	// destination texture should exist! You can draw this texture inside
	virtual bool BeginRender(int tex, BOOL nErase, DWORD color, BOOL bDrawDirectToTex=FALSE) = 0;
	virtual bool EndRender(int nUpdate = 1) = 0;
	virtual void UseZ(bool bUseZ) = 0;

	virtual void Clear() = 0;


};
