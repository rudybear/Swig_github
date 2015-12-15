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

#include "Public/Render/IGameRenderObject.h"
#define GUI_DEPTH_DISABLED  0x000 
#define GUI_DEPTH_ENABLED   0x100
#define GUI_DEPTH_MASK      0xF00

#define GUI_SAMPLING_LINWRAP     0x00
#define GUI_SAMPLING_LINCLAMP    0x1000
#define GUI_SAMPLING_POINTWRAP   0x10
#define GUI_SAMPLING_BILINWRAP   0x20
#define GUI_SAMPLING_BILINCLAMP  0x40
#define GUI_SAMPLING_POINTCLAMP  0x80
#define GUI_SAMPLING_MASK        0xF0F0

#define GUI_BLEND_NONE      1
#define GUI_BLEND_ALPHA     0
#define GUI_BLEND_ONE       3
#define GUI_BLEND_MASK		  0xF

class IGUIRenderObject 
{
public:

  virtual ~IGUIRenderObject(void) {}

  virtual void SetTexture(int num, int blend = -1) =0 ;
  virtual void SetEffect(int num, int Texture) = 0;
  virtual void SetTextureNew(int num,int blend = -1)=0;
  virtual void SetLineMode() = 0; // Set it up AFTER SetTexture
  virtual void DrawTriangle2DList(RENDER2DVERTEX *, int, int nFlags=0) = 0; // второй параметр - количество треугольников!!!!
  virtual void DrawText(int font,float posx, float posy , DWORD color , const char * text) = 0;
  virtual void DrawTextScaled(int,float, float ,float, float, DWORD, const char *) = 0;

protected:
  IGUIRenderObject(void)  {}
};

struct IMaterial;
class I2DRenderObject 
{
public:

  virtual ~I2DRenderObject(void) {}

  //! Complex 
  virtual void SetMaterial(const IMaterial * material) =0;

  //! Simple texture interface
  virtual void SetDefaultMaterial() = 0;
  virtual void SetTexture(int num) = 0;
  virtual void SetBlendState(bool) = 0;
  virtual void SetBlendOperation(eBLENDOP) = 0;
  virtual void SetSrcBlend(eBLEND) = 0;
  virtual void SetDstBlend(eBLEND) = 0;
  //! Cull states
  virtual void SetCullFunc(eCULL) = 0;
  //! Depth states
  virtual void SetDepthFunc(eDEPTHSTATE)=0;
  virtual void SetFillMode(int FM) = 0;
  virtual void SetAlphaFunc(eCMPFUNC AF, int AV = 0)=0;

  //! Rendering interface
  virtual void DrawTriangle2DList(RENDER2DVERTEX *, int triangleCount) = 0; 
  virtual void DrawText(int font,float posx, float posy , DWORD color , const char * text) = 0;
  virtual void DrawTextScaled(int,float, float ,float, float, DWORD, const char *) = 0;

  virtual void BeginScene() = 0;
  virtual void EndScene() = 0;

protected:
  I2DRenderObject(void)  {}
};
