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

#include "Public/Common/Param.h"
#include "Public/Common/Autoref.h"
#include "Public/Render/RenderCommon.h"

class IPostProcessingContainer;
class IPostProcessingEffect : public CRefSmartPtr
{
friend class IPostProcessingContainer;
public:

	IPostProcessingEffect(void) {;};
	virtual ~IPostProcessingEffect(void) {;};

	virtual HRESULT Init() = 0;// По идее этот метод проводит валидацию, возможен ли этот эффект вообще в этой системе
	virtual HRESULT Preprocess() = 0; //метод подгтовки эффекта. Etc, рендер в текстуру...
	virtual HRESULT Postprocess() = 0; // метод вывода эффекта. Etc, рендер самой текстуры...
	virtual HRESULT Close() = 0;
	virtual HRESULT Restore() = 0;
	virtual HRESULT Invalidate() = 0;
	virtual const char* GetName() = 0;
	virtual void SetParam(CParam *) = 0;
//	virtual void SetParam(const char*, void *) = 0;
	virtual bool GetParam(CParam *&, const char *) = 0;
	virtual void SetActive(eActiveType val) = 0;
	virtual BOOL GetActive() = 0;
	virtual BOOL GetRendered() = 0;
	//! Возвращает TRUE, если постэффект присутствует в единственном экземпляре
	virtual BOOL IsStatic() = 0; 
	//! Проверяет параметры на возможность использования
	virtual BOOL Validate(const Engine2::Vector<CParam>* params) = 0;

	virtual HRESULT     PostPostprocess(void)=0;
	virtual void SuperMethod() = 0;

};

class IPostProcessingContainer
{
	void DeleteEffect(IPostProcessingEffect * p)
	{
		delete p;
	}
};

typedef CSmartPtr<IPostProcessingEffect> PostProcessingEffectPtr;
