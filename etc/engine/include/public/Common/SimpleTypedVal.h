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

class ISimpliestTypedVal
{
public:
	ISimpliestTypedVal(){};
	virtual ~ISimpliestTypedVal(){};

	virtual int GetType(void)=0;
};


template < typename ValueType,class ClassType> 
class SimpleTypedVal : public ISimpliestTypedVal
{
public:
	SimpleTypedVal(ValueType ClassType::*pPtr)
	{
		m_nPtr = pPtr;
	};

	~SimpleTypedVal(){};

	void SetValue(ClassType *pObject, const ValueType &nVal)
	{
		pObject->*m_nPtr = nVal;
	};
	const ValueType &GetValue(const ClassType *pObject)
	{
		return pObject->*m_nPtr;
	};


	virtual int GetType(void){return 1;};

protected:
	ValueType ClassType::*m_nPtr;
};

