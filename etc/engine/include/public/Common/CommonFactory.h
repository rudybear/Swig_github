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
#include <map>
#include <string>

#ifdef __GNUC__
//#include <ext/hash_map>

namespace std
{
    using namespace __gnu_cxx;
}
#endif


template<class T>
class CCommonFactory
{
public:
	typedef T * (*CreateMeshCallback)();
private:
	typedef typename std::map<stlstring, CreateMeshCallback> CallbackMap;
	typedef typename std::map<stlstring, CreateMeshCallback>::iterator CallbackMapIterator;     
public:
	CCommonFactory() {};
	bool Register(stlstring Name, CreateMeshCallback CreateFn)
	{
		return callbacks_.insert(make_pair(Name, CreateFn)).second;
	}

	bool Unregister(stlstring Name)
	{
		return callbacks_.erase(Name) == 1;
	}

	T * Create(stlstring Name)
	{
		CallbackMapIterator i = callbacks_.find(Name);
		if (i == callbacks_.end())
		{
			return NULL;
		}
		return (i->second)();
	}

private:
	CallbackMap callbacks_;

};


