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

class IFFShader
{
public:

	virtual ~IFFShader(void) {};
	virtual void SetColorStage(unsigned  int, int, int, int) = 0; // устанавливаем параметры для Color Stage 
	virtual void SetAlphaStage(unsigned int, int, int, int) = 0; // устанавливаем параметры для Alpha Stage 

	virtual void GetColorStage(unsigned int, int *, int *, int*) = 0;
	virtual void GetAlphaStage(unsigned int, int *, int *, int*) = 0;

	virtual int GetNumStages() = 0;

	virtual void SetShader() = 0; // Для использованием рендером!
protected:
	IFFShader(void) {};
};
