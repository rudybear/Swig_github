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

template <class _CharT, class _Traits, class _Alloc>
std::size_t
string_hash(const std::basic_string<_CharT,_Traits,_Alloc>& __s) 
{
	unsigned int __h = 0;
	typedef typename std::basic_string<_CharT,_Traits,_Alloc>::const_pointer const_ptr;
	size_t __len = __s.size();
	const _CharT* __data = __s.data();

	for ( size_t __i = 0; __i < __len; ++__i)
	{
		int nVal = tolower(__data[__i]);
		__h = 5*__h + nVal;
	}
	return size_t(__h);
} 


template <
	class _CharT,
	class _Traits = std::char_traits<_CharT>,
	class _Alloc = std::allocator<_CharT>,
	class _Pr = std::less< std::basic_string<_CharT, _Traits, _Alloc> >
>
class bshc
{    // traits class for hash containers
public:
	typedef std::basic_string<_CharT, _Traits, _Alloc> _Kty;

	enum
	{    // parameters for hash table
		bucket_size = 4,    // 0 < bucket_size
		min_buckets = 8
	};    // min_buckets = 2 ^^ N, 0 < N

	bshc()
		: comp()
	{    // construct with default comparator
	}

	bshc(_Pr _Pred)
		: comp(_Pred)
	{    // construct with _Pred comparator
	}

	size_t operator()(const _Kty& _Keyval) const
	{    // hash _Keyval to size_t value
		return string_hash(_Keyval);
	}

	bool operator()(const _Kty& _Keyval1, const _Kty& _Keyval2) const
	{    // test if _Keyval1 ordered before _Keyval2
		return (comp(_Keyval1, _Keyval2));
	}

private:
	_Pr comp;    // the comparator object
};

#ifndef NOT_TRACE_STL
typedef bshc<char, std::char_traits<char>, Engine2::Allocator<char> > string_hash_compare;
#else

	#if _MSC_VER < 1700 
		typedef bshc<char> string_hash_compare;
	#else //_MSC_VER < 1700 
		typedef stdext::hash_compare<std::string, std::less<std::string> > string_hash_compare;
	#endif //_MSC_VER < 1700 

#endif

