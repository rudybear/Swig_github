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

class ISamplerState
{
public:
	virtual ~ISamplerState(void) {;};

	virtual void SetSamplerState(unsigned int num, int type) = 0;
	virtual void GetSamplerState(unsigned int num, int *type) = 0;

	virtual int GetNumStages() = 0;

protected:
	ISamplerState() {};
};
