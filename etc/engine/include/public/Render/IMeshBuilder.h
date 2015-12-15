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

#include "RenderCommon.h"


enum eAttribute {
  POSITION=0x00001,
  NORMAL=0x00002,
  TEX0=0x00004,
  TEX1=0x00008,
  TEX2=0x00010,
  TEX3=0x00020,
  TEX4=0x00040,
  TEX5=0x00040,
  TEX6=0x00040,
  TEX7=0x00080,
  TANGENT=0x00100,
  BINORMAL=0x00200,
  BLENDWEIGHT=0x00400,
  BLENDINDICES=0x00800,
  POINTSIZE=0x01000,
  FOG=0x02000,
  DEPTH=0x04000,
  SPECULAR=0x08000,
  DIFFUSE=0x10000
};

typedef enum eDECLTYPE
{
    eFLOAT1    =  0,  // 1D float expanded to (value, 0., 0., 1.)
    eFLOAT2    =  1,  // 2D float expanded to (value, value, 0., 1.)
    eFLOAT3    =  2,  // 3D float expanded to (value, value, value, 1.)
    eFLOAT4    =  3,  // 4D float
    eD3DCOLOR  =  4,  // 4D packed unsigned bytes mapped to 0. to 1. range
                                 // Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
    eUBYTE4    =  5,  // 4D unsigned byte
    eSHORT2    =  6,  // 2D signed short expanded to (value, value, 0., 1.)
    eSHORT4    =  7,  // 4D signed short

// The following types are valid only with vertex shaders >= 2.0


    eUBYTE4N   =  8,  // Each of 4 bytes is normalized by dividing to 255.0
    eSHORT2N   =  9,  // 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
    eSHORT4N   = 10,  // 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
    eUSHORT2N  = 11,  // 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)
    eUSHORT4N  = 12,  // 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)
    eUDEC3     = 13,  // 3D unsigned 10 10 10 format expanded to (value, value, value, 1)
    eDEC3N     = 14,  // 3D signed 10 10 10 format normalized and expanded to (v[0]/511.0, v[1]/511.0, v[2]/511.0, 1)
    eFLOAT16_2 = 15,  // Two 16-bit floating point values, expanded to (value, value, 0, 1)
    eFLOAT16_4 = 16,  // Four 16-bit floating point values
    eUNUSED    = 17,  // When the type field in a decl is unused.
} DECLTYPE;



typedef enum eDECLUSAGE
{
    ePOSITION = 0,
    eBLENDWEIGHT,   // 1
    eBLENDINDICES,  // 2
    eNORMAL,        // 3
    ePSIZE,         // 4
    eTEXCOORD,      // 5
    eTANGENT,       // 6
    eBINORMAL,      // 7
    eTESSFACTOR,    // 8
    ePOSITIONT,     // 9
    eCOLOR,         // 10
    eFOG,           // 11
    eDEPTH,         // 12
    eSAMPLE,        // 13
} DECLUSAGE;


struct sDeclaration{
	WORD Stream;
	BYTE Type;
	BYTE Usage;
	BYTE Index;
}; 

#define sDECL_END() {0xFF,eUNUSED,0,0}

class IMeshBuilder
{

public:

	virtual ~IMeshBuilder(void) {};

	virtual void Clear() = 0;

	virtual HRESULT CreateDeclaration(sDeclaration *) = 0; // Создаем 
	virtual HRESULT CreateDeclaration(eVertexTypes) = 0; // Создаем 
	//HRESULT Create(DWORD); // Создать вертекс-буфер с заданными флагами
	virtual DWORD GetDescrition() = 0;
	virtual BOOL  isPosition() = 0;
	virtual BOOL  isNormal() = 0;
	virtual BOOL  isDiffuse() = 0;
	virtual BOOL  isSpecular()  = 0;
	virtual int   isTex(int) = 0;
	virtual BOOL  isTangent() = 0;
	virtual BOOL  isBinormal()  = 0;
	virtual BOOL  isBlendweight() = 0;
	virtual BOOL  isBlendindices() = 0;
	virtual BOOL  isPsize() = 0;
	virtual BOOL  isFog() = 0;
	virtual BOOL  isDepth() = 0;

  // Lock 0 stream. Old behavior
	virtual HRESULT  Lock(DWORD) = 0;
  // Lock num stream. New behavior
  virtual HRESULT  LockStream(DWORD flags,int stream) = 0;

	virtual void * GetElementPointer(eDECLUSAGE usage, BYTE index) = 0; // Дает указатель на элемент (один!!!)
	virtual int    GetElementIterator(eDECLUSAGE) = 0; // Дает размер для смещения элемента. sizeof()
	virtual void * GetVertexPointer() = 0;// Дает указатель на всю структуру
 	virtual void * GetVertexPointer(int) = 0;// Дает указатель на всю структуру
	virtual int    GetVertexIterator() = 0; // Дает размер для смещения структуры. sizeof()
  virtual int    GetVertexIterator(int) = 0; // Дает размер для смещения структуры. sizeof()

  // Unlock 0 stream, old behavior
	virtual HRESULT   Unlock() = 0; //
  // Unlock 0 stream, old behavior
  virtual HRESULT   UnlockStream(int stream) = 0; //

	virtual unsigned int    GetSize() = 0; // Возвращает размер буфера в элементах
	virtual unsigned int    GetTotalSize() = 0; // Возвращает общий размер буфера
  virtual unsigned int    GetTotalSize(int stream) = 0; // Возвращает общий размер буфера

	//! Продвинутый метод создания MeshBuilder.Создает буфер нужного размера. Size БЕЗ размера структуры!!!
	virtual HRESULT   SetSize(int iSize, DWORD usage, DWORD  pool) = 0; // 
  virtual HRESULT   SetSize(int iSize, DWORD usage, DWORD  pool, int stream) = 0; // 
	//! Простой метод создания MeshBuilder. Создает буфер нужного размера. Size БЕЗ размера структуры!!!
	//! Если bStatic TRUE, то создается статический буфер, с флагами WRITEONLY, MANAGED
	//! Если bStatc FALSE, то создается динамический буфер, с флагами WRITEONLY|DYNAMIC, DEFAULT
	virtual HRESULT   SetSize(int iSize, BOOL bStatic ) = 0; // 
	virtual HRESULT   SetFormat(eVertexTypes) = 0;  // Пересоздает буфер с другими флагами. Содержимое переезжает


	// мега супер/ Автоматический расчет tangent space
	virtual void CalculateTangentBinormal(BOOL, BOOL) = 0;
	virtual void CalculateNormals() = 0;

	// Здесь можно сделать как в _известной игре_
	
	virtual void SetNormal(float, float, float) = 0;
	virtual void SetNormal(const CVec3&) = 0;

	
	virtual void SetColor(BYTE, BYTE, BYTE, BYTE) = 0;
	virtual void SetColorD(DWORD) = 0;

	virtual void SetPosition(const CVec3&) = 0;
	virtual void SetPosition(float, float, float) = 0;

	virtual void SetTexCoord(int, const CVec2&) = 0;
	virtual void SetTexCoord(int, float, float) = 0;
	virtual void SetTexCoord(int, const CVec3&) = 0;
	virtual void SetTexCoord(int, float, float, float) = 0;
	virtual void SetTexCoord(int, const CVec4&) = 0;
    virtual void SetTexCoord(int, float, float, float, float) = 0;


	virtual void NextVertex() = 0;


//	virtual int GetVB() = 0; // Возвращает текущий индекс IB
	//FIXME: Добавить метод рендера
//	virtual void SetDescription(IBaseRenderPrimitive *) = 0;// Устанавливает параметры в RP

	virtual void Invalidate() = 0;
	virtual void Restore() = 0;

protected:
	IMeshBuilder() {};
//	void S
};
