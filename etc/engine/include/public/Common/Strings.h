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

#include <string.h>
#include <wchar.h>
#include <limits.h>
#include <stdarg.h>
#include <ctype.h>
#include "Allocator.h"
#include "Common.h"

#ifdef SWIG
#undef DLLIMPORT
#define DLLIMPORT
#endif

namespace Engine2 
{

	//////////////////////////////////////////////////////////////////////////
	// String_template class.
	//////////////////////////////////////////////////////////////////////////
	template <class T, class A = Engine2::StandardAllocator>
	class DLLIMPORT String_template 
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		// Types compatible with STL string.
		//////////////////////////////////////////////////////////////////////////
		typedef String_template<T, A> _Self;
		typedef size_t size_type;
		typedef T value_type;
		typedef const value_type* const_str;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef pointer iterator;
		typedef const_pointer const_iterator;

		static const size_type npos = ~(size_type)0;

		//////////////////////////////////////////////////////////////////////////
		// Constructors
		//////////////////////////////////////////////////////////////////////////
		String_template();

	public:

		String_template( const _Self& str );
		String_template( const _Self& str,size_type nOff,size_type nCount );
		explicit String_template( value_type ch, size_type nRepeat = 1 );
		String_template( const_str str );
		String_template( const_str str, size_type nLength );
		String_template( const_iterator _First,const_iterator _Last );
		virtual ~String_template();

		size_type length() const;
		size_type size() const;
		bool empty() const;
		void clear();  // free up the data

		//! Returns the storage currently allocated to hold the string, a value at least as large as length().
		size_type capacity() const;

		// Sets the capacity of the string to a number at least as great as a specified number.
		// nCount = 0 is shrinking string to fit number of characters in it.
		void reserve( size_type nCount=0 );

		_Self& append( const value_type* _Ptr );
		_Self& append( const value_type* _Ptr,size_type nCount );
		_Self& append( const _Self& _Str,size_type nOff,size_type nCount );
		_Self& append( const _Self& _Str );
		_Self& append( size_type nCount,value_type _Ch );
		_Self& append( const_iterator _First,const_iterator _Last );

		_Self& assign( const_str _Ptr );
		_Self& assign( const_str _Ptr, size_type nCount );
		_Self& assign( const _Self& _Str, size_type off, size_type nCount );
		_Self& assign( const _Self& _Str );
		_Self& assign( size_type nCount, value_type _Ch );
		_Self& assign( const_iterator _First,const_iterator _Last );

		value_type  at( size_type index ) const;
		//value_type& at( size_type index );

		const_iterator begin() const { return m_str; };
		const_iterator end() const { return m_str+length(); };

		iterator begin() { return m_str; };
		iterator end() { return m_str+length(); };

		//! cast to C string operator.
		operator const_str() const { return m_str; }

		//! cast to C string.
		const value_type *c_str() const { return m_str; }
		const value_type *data() const { return m_str; };

		int compare( const _Self& _Str ) const;
		int compare( size_type _Pos1,size_type _Num1,const _Self& _Str ) const;
		int compare( size_type _Pos1,size_type _Num1,const _Self& _Str,size_type nOff,size_type nCount ) const;
		int compare( const value_type* _Ptr	) const;
		int compare( size_type _Pos1,size_type _Num1,const value_type* _Ptr	) const;
		int compareWithPos( size_type _Pos1,size_type _Num1,const value_type* _Ptr,size_type _Num2 = npos	) const;
		int compareNoCase( const _Self& _Str ) const;
		int compareNoCase( size_type _Pos1,size_type _Num1,const _Self& _Str ) const;
		int compareNoCase( size_type _Pos1,size_type _Num1,const _Self& _Str,size_type nOff,size_type nCount ) const;
		int compareNoCase( const value_type* _Ptr	) const;
		int compareNoCase( size_type _Pos1,size_type _Num1,const value_type* _Ptr	) const;
		int compareNoCaseWithPos( size_type _Pos1,size_type _Num1,const value_type* _Ptr,size_type _Num2 = npos	) const;

		// Copies at most a specified number of characters from an indexed position in a source string to a target character array.
		size_type copy( value_type* _Ptr, size_type nCount,	size_type nOff = 0 ) const;

		void push_back( value_type _Ch ) { _ConcatenateInPlace( &_Ch, 1 ); }
		void resize( size_type nCount,value_type _Ch=' ');

		//! simple sub-string extraction
		_Self substr( size_type pos, size_type count=npos ) const;

		// replace part of string.
		_Self& replace( value_type chOld, value_type chNew );
		_Self& replace( const_str strOld, const_str strNew );
		_Self& replace( size_type pos,size_type count,const_str strNew );
		_Self& replace( size_type pos,size_type count,const_str strNew,size_type count2 );
		_Self& replace( size_type pos,size_type count,size_type nNumChars,value_type chNew);

		_Self& insert(size_type nIndex,value_type ch);
		_Self& insert(size_type nIndex,size_type nCount, value_type ch);
		_Self& insert(size_type nIndex,const_str pstr);
		_Self& insert(size_type nIndex,const_str pstr,size_type nCount );

		_Self& erase( size_type nIndex,size_type count=npos );

		size_type find( value_type ch,size_type pos = 0 ) const;
		size_type find( const_str subs,size_type pos = 0 ) const;
		size_type rfind( value_type ch,size_type pos = npos ) const; 

    size_type find_last_of( value_type _Ch,size_type nOff = 0 ) const;

		size_type find_first_of( value_type _Ch,size_type nOff = 0 ) const;
		size_type find_first_of( const_str charSet,size_type nOff = 0 ) const;
		//size_type find_first_of( const value_type* _Ptr,size_type _Off,size_type _Count ) const;
		size_type find_first_of( const _Self& _Str, size_type _Off = 0 ) const;

		size_type find_first_not_of( value_type _Ch,size_type _Off=0 ) const;
		size_type find_first_not_of( const value_type* _Ptr,size_type _Off=0 ) const;
		size_type find_first_not_of( const value_type* _Ptr,size_type _Off,size_type _Count ) const;
		size_type find_first_not_of( const _Self& _Str,size_type _Off = 0 ) const;

		void swap( _Self& _Str );

		_Self& operator=( const _Self& str );
		_Self& operator=( value_type ch );
		_Self& operator=( const_str str );

		_Self& operator+=( const _Self& str );
		_Self& operator+=( value_type ch );
		_Self& operator+=( const_str str );


    _Self& FixPathToUnix();

		_Self& Format( const value_type* format,... );
		//// This is _fast_ version
		_Self& MakeLower();
		//// This is correct version
		_Self& MakeLowerLocale();
		_Self& MakeUpper();

		// public utilities.
		static size_type _strlen( const_str str );
		static const_str _strchr( const_str str, value_type c);
		static value_type* _strstr( value_type* str, const_str strSearch);
		static bool _IsValidString( const_str str );

	public:
		//////////////////////////////////////////////////////////////////////////
		// Only used for debugging statistics.
		//////////////////////////////////////////////////////////////////////////
		static int _usedMemory( int size )
		{
			static int s_used_memory = 0;
			s_used_memory += size;
			return s_used_memory;
		}

	private:
		value_type* m_str; // pointer to ref counted string data

		// String header, immediately after this header in memory starts actual string data.
		struct StrHeader
		{
			// Reference count of this string.
			int nRefCount;
			// Current length of string.
			size_t nLength;
			// Size of memory allocated at the end of this class.
			int nAllocSize;
			// Here in memory starts character buffer of size nAllocSize.
			//value_type data[nAllocSize]

			value_type* GetChars() { return (value_type*)(this+1); }
			void  AddRef() { nRefCount++; /*InterlockedIncrement(&_header()->nRefCount);*/};
			int   Release() { return --nRefCount; };
		};
		static StrHeader* _emptyHeader()
		{
			static int sEmptyStringBuffer[sizeof(StrHeader) / sizeof(int) + 1] = { -1 /* the rest is initialized with zeros */ };
			return (StrHeader*)(&sEmptyStringBuffer);
		}

		// implementation helpers
		StrHeader* _header() const;

		void _AllocData( size_type nLen );
		static void _FreeData( StrHeader* pData );
		void _Free();
		void _Initialize();

		void _Concatenate( const_str sStr1,size_type nLen1,const_str sStr2,size_type nLen2 );
		void _ConcatenateInPlace( const_str sStr,size_type nLen );
		void _Assign( const_str sStr,size_type nLen );
		void _MakeUnique();

		static void _copy( value_type *dest,const value_type *src,size_type count );
		static void _move( value_type *dest,const value_type *src,size_type count );
		static void _set( value_type *dest,value_type ch,size_type count );
	};


	/////////////////////////////////////////////////////////////////////////////
	// String_template<T, A> Implementation
	//////////////////////////////////////////////////////////////////////////

	template <class T, class A>
	inline typename String_template<T, A>::StrHeader* String_template<T, A>::_header() const
	{
		assert(m_str != NULL); return ((StrHeader*)m_str)-1;
	}

	template <class T, class A>
	inline typename String_template<T, A>::size_type String_template<T, A>::_strlen( const_str str )
	{
		return (str == NULL) ? 0 : (size_type)::strlen(str);
	}

	template <>
	inline String_template<wchar_t>::size_type String_template<wchar_t>::_strlen( const_str str )
	{
		return (str == NULL) ? 0 : (size_type)::wcslen(str);
	}

	template <class T, class A>
	inline typename String_template<T, A>::const_str String_template<T, A>::_strchr( const_str str,value_type c )
	{
		return (str == NULL) ? 0 : ::strchr(str, c);
	}

	template <>
	inline String_template<wchar_t>::const_str String_template<wchar_t>::_strchr( const_str str,value_type c )
	{
		return (str == NULL) ? 0 : ::wcschr(str, c);
	}

	template <class T, class A>
	inline typename String_template<T, A>::value_type* String_template<T, A>::_strstr( value_type* str,const_str strSearch )
	{
		return (str == NULL) ? 0 : ::strstr(str, strSearch);
	}

	template <>
	inline String_template<wchar_t>::value_type* String_template<wchar_t>::_strstr( value_type* str,const_str strSearch )
	{
		return (str == NULL) ? 0 : ::wcsstr(str, strSearch);
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::_copy( value_type *dest,const value_type *src,size_type count )
	{
		memcpy( dest,src,count*sizeof(value_type) );
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::_move( value_type *dest,const value_type *src,size_type count )
	{
		memmove( dest,src,count*sizeof(value_type) );
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::_set( value_type *dest,value_type ch,size_type count )
	{
		memset( dest,ch,count*sizeof(value_type) );
	}

	//////////////////////////////////////////////////////////////////////////
	template <>
	inline void String_template<wchar_t>::_set( value_type *dest,value_type ch,size_type count )
	{
		wmemset( dest,ch,count );
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline bool String_template<T, A>::_IsValidString( const_str  )
	{
		/*
		if (str == NULL)
		return false;
		int nLength = _strlen(str);
		return !::IsBadStringPtrA(str, nLength);
		*/
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::_Assign( const_str sStr,size_type nLen )
	{
		// Check if this string is shared (reference count greater then 1) or not enough capacity to store new string.
		// Then allocate new string buffer.
		if (_header()->nRefCount > 1 || nLen > capacity())
		{
			_Free();
			_AllocData(nLen);
		}
		// Copy characters from new string to this buffer.
		_copy( m_str,sStr,nLen );
		
		// Set new length.
		_header()->nLength = nLen;
		// Make null terminated string.
		m_str[nLen] = 0;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::_Concatenate( const_str sStr1,size_type nLen1,const_str sStr2,size_type nLen2 )
	{
		size_type nLen = nLen1 + nLen2;
		if (nLen1 * 2 > nLen)
			nLen = nLen1 * 2;
		if (nLen != 0)
		{
			if (nLen < 8)
				nLen = 8;
			_AllocData(nLen);
			_copy( m_str,sStr1,nLen1 );
			_copy( m_str+nLen1, sStr2,nLen2 );
			_header()->nLength = nLen1 + nLen2;
			m_str[nLen1 + nLen2] = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::_ConcatenateInPlace( const_str sStr,size_type nLen )
	{
		if (nLen != 0)
		{
			// Check if this string is shared (reference count greater then 1) or not enough capacity to store new string.
			// Then allocate new string buffer.
			if (_header()->nRefCount > 1 || length()+nLen > capacity())
			{
				StrHeader* pOldData = _header();
				_Concatenate( m_str,length(),sStr,nLen );
				_FreeData(pOldData);
			}
			else
			{
				_copy( m_str+length(), sStr, nLen );
				_header()->nLength += nLen;
				m_str[_header()->nLength] = 0; // Make null terminated string.
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::_MakeUnique()
	{
		if (_header()->nRefCount > 1)
		{
			// If string is shared, make a copy of string buffer.
			StrHeader *pOldData = _header();
			// This will not free header because reference count is greater then 1.
			_Free();
			// Allocate a new string buffer.
			_AllocData( pOldData->nLength );
			// Full copy of null terminated string.
			_copy( m_str,pOldData->GetChars(),pOldData->nLength+1 );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::_Initialize()
	{
		m_str = _emptyHeader()->GetChars();
	}

	// always allocate one extra character for '\0' termination
	// assumes [optimistically] that data length will equal allocation length
	template <class T, class A>
	inline void String_template<T, A>::_AllocData( size_type nLen )
	{
		assert(nLen <= INT_MAX-1);    // max size (enough room for 1 extra)

		if (nLen == 0)
			_Initialize();
		else
		{
			int allocLen = int(sizeof(StrHeader) + (nLen+1)*sizeof(value_type));
			StrHeader* pData = (StrHeader*)A::allocate( allocLen );

			_usedMemory( allocLen ); // For statistics.

			pData->nRefCount = 1;
			m_str = pData->GetChars();
			pData->nLength = nLen;
			pData->nAllocSize = (int)nLen;
			m_str[nLen] = 0; // null terminated string.
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::_Free()
	{
		if (_header()->nRefCount >= 0) // Not empty string.
		{
			_FreeData( _header() );
			_Initialize();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::_FreeData( StrHeader* pData )
	{
		if (pData->nRefCount >= 0) // Not empty string.
		{
			assert(pData->nRefCount != 0);
			if (pData->Release() <= 0)
			{
				int allocLen = int(sizeof(StrHeader) + sizeof(value_type)*size_t(pData->nAllocSize+1));
				_usedMemory( -allocLen ); // For statistics.

				A::deallocate((void*)pData,allocLen);
        pData = 0;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>::String_template() : m_str(0)
	{
		_Initialize();
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>::String_template( const String_template<T, A>& str ): m_str(0)
	{
		if (str.m_str) {
		 assert(str._header()->nRefCount != 0);
		 if (str._header()->nRefCount >= 0)
		 {
		 	m_str = str.m_str;
		 	_header()->AddRef();
		 }
		 else
		 {
		 	_Initialize();
		 }
	 }
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>::String_template( const String_template<T, A>& str,size_type nOff,size_type nCount ): m_str(0)
	{
		_Initialize();
		assign( str,nOff,nCount );
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>::String_template( const_str str ): m_str(0)
	{
		_Initialize();
		// Make a copy of C string.
		size_type nLen = _strlen(str);
		if (nLen != 0)
		{
			_AllocData(nLen);
			_copy( m_str,str,nLen );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>::String_template( const_str str,size_type nLength ): m_str(0)
	{
		_Initialize();
		if (nLength > 0)
		{
			_AllocData(nLength);
			_copy( m_str,str,nLength );
		}
	}


	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>::String_template( value_type ch,size_type nRepeat ): m_str(0)
	{
		_Initialize();
		if (nRepeat > 0)
		{
			_AllocData( nRepeat );
			_set( m_str,ch,nRepeat );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>::String_template( const_iterator _First,const_iterator _Last ): m_str(0)
	{
		_Initialize();
		size_type nLength = (size_type)(_Last-_First);
		if (nLength > 0)
		{
			_AllocData(nLength);
			_copy( m_str,_First,nLength );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>::~String_template()
	{
		if (m_str)
			_FreeData( _header() );
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline typename String_template<T, A>::size_type String_template<T, A>::length() const
	{
		return _header()->nLength;
	}
	template <class T, class A>
	inline typename String_template<T, A>::size_type String_template<T, A>::size() const
	{
		return _header()->nLength;
	}
	template <class T, class A>
	inline typename String_template<T, A>::size_type String_template<T, A>::capacity() const
	{
		return _header()->nAllocSize;
	}

	template <class T, class A>
	inline bool String_template<T, A>::empty() const
	{
		return length() == 0;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::clear()
	{
		if (length() == 0)
			return;
		if (_header()->nRefCount >= 0)
			_Free();
		else
			*this = "";
		assert( length() == 0);
		assert(_header()->nRefCount < 0 || capacity() == 0);
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::reserve( size_type nCount )
	{
		// Reserve of 0 is shrinking container to fit number of characters in it..
		if (nCount > capacity())
		{
			StrHeader* pOldData = _header();
			_AllocData( nCount );
			_copy( m_str,pOldData->GetChars(),pOldData->nLength );
			_header()->nLength = pOldData->nLength;
			m_str[pOldData->nLength] = 0;
			_FreeData(pOldData);
		} else if (nCount == 0)
		{
			if (length() != capacity())
			{
				StrHeader* pOldData = _header();
				_AllocData(length());
				_copy( m_str,pOldData->GetChars(),pOldData->nLength );
				_FreeData(pOldData);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::append( const_str _Ptr )
	{
		*this += _Ptr;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::append( const_str _Ptr, size_type nCount )
	{
		_ConcatenateInPlace( _Ptr,nCount );
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::append( const String_template<T, A>& _Str, size_type off, size_type nCount )
	{
		size_type len = _Str.length();
		if (off > len)
			return *this;
		if (off+nCount > len)
			nCount = len - off;
		_ConcatenateInPlace( _Str.m_str+off,nCount );
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::append( const String_template<T, A>& _Str )
	{
		*this += _Str;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::append( size_type nCount, value_type _Ch )
	{
		if (nCount > 0)
		{
			if (length()+nCount >= capacity())
			{
				StrHeader* pOldData = _header();
				_AllocData( length()+nCount );
				_copy( m_str, pOldData->GetChars(), pOldData->nLength );
				_set( m_str+pOldData->nLength,_Ch,nCount );
				_FreeData(pOldData);
			}
			else
			{
				size_type nOldLength = length();
				_set( m_str+nOldLength,_Ch,nCount );
				_header()->nLength = nOldLength + nCount;
				m_str[length()] = 0; // Make null terminated string.
			}
		}
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::append(  const_iterator _First,const_iterator _Last )
	{
		append( _First,(size_type)(_Last-_First) );
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::assign( const_str _Ptr )
	{
		*this = _Ptr;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::assign( const_str _Ptr, size_type nCount )
	{
		size_type len = _strlen(_Ptr);
		_Assign( _Ptr,(nCount<len)?nCount:len );
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::assign( const String_template<T, A>& _Str, size_type off, size_type nCount )
	{
		size_type len = _Str.length();
		if (off > len)
			return *this;
		if (off+nCount > len)
			nCount = len - off;
		_Assign( _Str.m_str+off,nCount );
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::assign( const String_template<T, A>& _Str )
	{
		*this = _Str;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::assign( size_type nCount, value_type _Ch )
	{
		if (nCount >= 1)
		{
			_AllocData( nCount );
			_set( m_str,_Ch,nCount );
		}
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A>& String_template<T, A>::assign( const_iterator _First,const_iterator _Last )
	{
		assign( _First,(size_type)(_Last-_First) );
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline typename String_template<T, A>::value_type String_template<T, A>::at( size_type index ) const
	{
		assert( index < length() );
		return m_str[index];
	}

	/*
	inline value_type& String_template<T, A>::at( size_type index )
	{
	// same as GetAt
	assert( index >= 0 && index < length() );
	return m_str[index];
	}
	*/

	/*
	inline String_template<T, A>::value_type String_template<T, A>::operator[]( size_type index ) const
	{
	assert( index >= 0 && index < length() );
	return m_str[index];
	}
	*/

	/*
	inline value_type& String_template<T, A>::operator[]( size_type index )
	{
	// same as GetAt
	assert( index >= 0 && index < length() );
	return m_str[index];
	}
	*/


	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline int String_template<T, A>::compare( const String_template<T, A>& _Str ) const
	{
		return strcmp( m_str,_Str.m_str );
	}

	template <class T, class A>
	inline int String_template<T, A>::compare( size_type _Pos1,size_type _Num1,const String_template<T, A>& _Str ) const
	{
		return compareWithPos(_Pos1, _Num1, _Str.m_str, npos);
	}


	template <class T, class A>
	inline int String_template<T, A>::compare( size_type _Pos1,size_type _Num1,const String_template<T, A>& _Str,size_type nOff,size_type nCount ) const
	{
		assert( nOff < _Str.length() );
		return compareWithPos(_Pos1, _Num1, _Str.m_str + nOff, nCount);
	}


	template <class T, class A>
	inline int String_template<T, A>::compare( const value_type* _Ptr	) const
	{
		return strcmp( m_str,_Ptr );
	}

	template <class T, class A>
	inline int String_template<T, A>::compare( size_type _Pos1,size_type _Num1,const value_type* _Ptr	) const
	{
		return compareWithPos(_Pos1, _Num1, _Ptr, npos);
	}

	template <class T, class A>
	inline int String_template<T, A>::compareWithPos( size_type _Pos1,size_type _Num1,const value_type* _Ptr,size_type _Num2 ) const
	{
		assert( _Pos1 < length() );
		if (length() - _Pos1 < _Num1)
			_Num1 = length() - _Pos1; // trim to size

		int res = _Num1 == 0 ? 0 : strncmp( m_str+_Pos1,_Ptr,(_Num1 < _Num2)?_Num1:_Num2);
		return (res != 0 ? res : _Num1 < _Num2 ? -1 : _Num1 == _Num2 ? 0 : +1);
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline int String_template<T, A>::compareNoCase( const String_template<T, A>& _Str ) const
	{
		return _stricmp( m_str,_Str.m_str );
	}

	template <class T, class A>
	inline int String_template<T, A>::compareNoCase( size_type _Pos1,size_type _Num1,const String_template<T, A>& _Str ) const
	{
		return compareNoCaseWithPos(_Pos1, _Num1, _Str.m_str, npos);
	}

	template <class T, class A>
	inline int String_template<T, A>::compareNoCase( size_type _Pos1,size_type _Num1,const String_template<T, A>& _Str,size_type nOff,size_type nCount ) const
	{
		assert( nOff < _Str.length() );
		return compareNoCaseWithPos(_Pos1, _Num1, _Str.m_str + nOff, nCount);
	}

	template <class T, class A>
	inline int String_template<T, A>::compareNoCase( const value_type* _Ptr	) const
	{
#ifndef SWIG
		return stricmp( m_str,_Ptr );
#else
		return _stricmp(m_str, _Ptr);
#endif
	}

	template <class T, class A>
	inline int String_template<T, A>::compareNoCase( size_type _Pos1,size_type _Num1,const value_type* _Ptr	) const
	{
		return compareNoCaseWithPos(_Pos1, _Num1, _Ptr, npos);
	}

	template <class T, class A>
	inline int String_template<T, A>::compareNoCaseWithPos( size_type _Pos1,size_type _Num1,const value_type* _Ptr,size_type _Num2 ) const
	{
		assert( _Pos1 < length() );
		if (length() - _Pos1 < _Num1)
			_Num1 = length() - _Pos1; // trim to size
#ifndef SWIG
		int res = _Num1 == 0 ? 0 : strnicmp(m_str + _Pos1, _Ptr, (_Num1 < _Num2) ? _Num1 : _Num2);
#else
	#ifndef ANDROID
			int res = _Num1 == 0 ? 0 : _strnicmp(m_str + _Pos1, _Ptr, (_Num1 < _Num2) ? _Num1 : _Num2);
	#else
			int res = _Num1 == 0 ? 0 : strncasecmp(m_str + _Pos1, _Ptr, (_Num1 < _Num2) ? _Num1 : _Num2);
	#endif
#endif
		return (res != 0 ? res : _Num1 < _Num2 ? -1 : _Num1 == _Num2 ? 0 : +1);
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline typename String_template<T, A>::size_type String_template<T, A>::copy( value_type* _Ptr, size_type nCount,size_type nOff ) const
	{
		assert(nOff < length());
		if (nOff+nCount > length()) // trim to offset.
			nCount = length() - nOff;

		_copy( _Ptr,m_str+nOff,nCount );
		return nCount;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline void String_template<T, A>::resize( size_type nCount,value_type _Ch )
	{
		_MakeUnique();
		if (nCount > length())
		{
			size_type numToAdd = nCount - length();
			append(numToAdd,_Ch);
		}
		else if (nCount < length())
		{
			_header()->nLength = nCount;
			m_str[length()] = 0; // Make null terminated string.

		}
	}

	//////////////////////////////////////////////////////////////////////////
	//! compare helpers
	template <class T, class A> inline bool operator==(const String_template<T, A>& s1, const String_template<T, A>& s2)
	{ return s1.compare(s2) == 0; }
	template <class T, class A> inline bool operator==(const String_template<T, A>& s1, const typename String_template<T, A>::value_type* s2)
	{ return s1.compare(s2) == 0; }
	template <class T, class A> inline bool operator==(const typename String_template<T, A>::value_type* s1, const String_template<T, A>& s2)
	{ return s2.compare(s1) == 0; }
	template <class T, class A> inline bool operator!=(const String_template<T, A>& s1, const String_template<T, A>& s2)
	{ return s1.compare(s2) != 0; }
	template <class T, class A> inline bool operator!=(const String_template<T, A>& s1, const typename String_template<T, A>::value_type* s2)
	{ return s1.compare(s2) != 0; }
	template <class T, class A> inline bool operator!=(const typename String_template<T, A>::value_type* s1, const String_template<T, A>& s2)
	{ return s2.compare(s1) != 0; }
	template <class T, class A> inline bool operator<(const String_template<T, A>& s1, const String_template<T, A>& s2)
	{ return s1.compare(s2) < 0; }
	template <class T, class A> inline bool operator<(const String_template<T, A>& s1, const typename String_template<T, A>::value_type* s2)
	{ return s1.compare(s2) < 0; }
	template <class T, class A> inline bool operator<(const typename String_template<T, A>::value_type* s1, const String_template<T, A>& s2)
	{ return s2.compare(s1) > 0; }
	template <class T, class A> inline bool operator>(const String_template<T, A>& s1, const String_template<T, A>& s2)
	{ return s1.compare(s2) > 0; }
	template <class T, class A> inline bool operator>(const String_template<T, A>& s1, const typename String_template<T, A>::value_type* s2)
	{ return s1.compare(s2) > 0; }
	template <class T, class A> inline bool operator>(const typename String_template<T, A>::value_type* s1, const String_template<T, A>& s2)
	{ return s2.compare(s1) < 0; }
	template <class T, class A> inline bool operator<=(const String_template<T, A>& s1, const String_template<T, A>& s2)
	{ return s1.compare(s2) <= 0; }
	template <class T, class A> inline bool operator<=(const String_template<T, A>& s1, const typename String_template<T, A>::value_type* s2)
	{ return s1.compare(s2) <= 0; }
	template <class T, class A> inline bool operator<=(const typename String_template<T, A>::value_type* s1, const String_template<T, A>& s2)
	{ return s2.compare(s1) >= 0; }
	template <class T, class A> inline bool operator>=(const String_template<T, A>& s1, const String_template<T, A>& s2)
	{ return s1.compare(s2) >= 0; }
	template <class T, class A> inline bool operator>=(const String_template<T, A>& s1, const typename String_template<T, A>::value_type* s2)
	{ return s1.compare(s2) >= 0; }
	template <class T, class A> inline bool operator>=(const typename String_template<T, A>::value_type* s1, const String_template<T, A>& s2)
	{ return s2.compare(s1) <= 0; }

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::operator=( value_type ch )
	{
		_Assign( &ch,1 );
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A> operator+( const String_template<T, A>& string1,typename String_template<T, A>::value_type ch )
	{
		String_template<T, A> s(string1);
		s.append(1,ch);
		return s;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A> operator+( typename String_template<T, A>::value_type ch, const String_template<T, A>& str )
	{
		String_template<T, A> s;
		s.reserve(str.size()+1);
		s.append(1,ch);
		s.append(str);
		return s;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A>
	inline String_template<T, A> operator+( const String_template<T, A>& string1, const String_template<T, A>& string2 )
	{
		String_template<T, A> s(string1);
		s.append( string2 );
		return s;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A> operator+( const String_template<T, A>& str1, const typename String_template<T, A>::value_type* str2 )
	{
		String_template<T, A> s(str1);
		s.append( str2 );
		return s;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A> operator+( const typename String_template<T, A>::value_type* str1, const String_template<T, A>& str2 )
	{
		//		assert(str1 == NULL || String_template<T, A>::_IsValidString(str1));
		String_template<T, A> s;
		s.reserve( String_template<T, A>::_strlen(str1) + str2.size() );
		s.append(str1);
		s.append(str2);
		return s;
	}

	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::operator=(const String_template<T, A>& str)
	{
		if (m_str != str.m_str)
		{

//			_Assign(str.c_str(), str.length());
			if (_header()->nRefCount < 0)
			{
				// Empty string.
				//			_Assign( str.m_str,str.length() );
				if (str._header()->nRefCount < 0)
					; // two empty strings...
				else
				{
					m_str = str.m_str;
					_header()->AddRef();
				}
			}
			else if (str._header()->nRefCount < 0)
			{
				// If source string is empty.
				_Free();
				m_str = str.m_str;
			}
			else
			{
				// Copy string reference.
				_Free();
				m_str = str.m_str;
				_header()->AddRef();
			}
		}
		return *this;
	}

	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::operator=( const_str str )
	{
		assert(str == NULL || _IsValidString(str));
		_Assign( str,_strlen(str) ) ;
		return *this;
	}

	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::operator+=( const_str str )
	{
		assert(str == NULL || _IsValidString(str));
		_ConcatenateInPlace( str,_strlen(str) );
		return *this;
	}

	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::operator+=( value_type ch )
	{
		_ConcatenateInPlace( &ch,1 );
		return *this;
	}

	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::operator+=( const String_template<T, A>& str )
	{
		_ConcatenateInPlace( str.m_str,str.length() );
		return *this;
	}

	//! find first single character
	template <class T, class A> 
	inline typename String_template<T, A>::size_type String_template<T, A>::find( value_type ch,size_type pos ) const
	{
		if (!( pos <= length()) )
			return (typename String_template<T, A>::size_type)npos;
		const_str str = _strchr( m_str+pos,ch );
		// return npos if not found and index otherwise
		return (str == NULL) ? npos : (size_type)(str - m_str);
	}

	//! find a sub-string (like strstr)
	template <class T, class A> 
	inline typename String_template<T, A>::size_type String_template<T, A>::find( const_str subs,size_type pos ) const
	{
		assert( _IsValidString(subs) );
		if ( pos > length() )
			return npos;

		// find first matching substring
		const_str str = _strstr( m_str+pos,subs );

		// return npos for not found, distance from beginning otherwise
		return (str == NULL) ? npos : (size_type)(str - m_str);

	}

	//! find last single character
	template <class T, class A> 
	inline typename String_template<T, A>::size_type String_template<T, A>::rfind( value_type ch,size_type pos ) const
	{
		const_str str;
		if (pos == npos) {
			// find last single character
			str = strrchr( m_str,ch );
			// return -1 if not found, distance from beginning otherwise
			return (str == NULL) ? -1 : (size_type)(str - m_str);
		} else {
			if ( pos > length() )
				return npos;

			value_type tmp = m_str[pos+1];
			m_str[pos+1] = 0;
			str = strrchr( m_str,ch );
			m_str[pos+1] = tmp;
		}
		// return -1 if not found, distance from beginning otherwise
		return (str == NULL) ? -1 : (size_type)(str - m_str);
	}

  //////////////////////////////////////////////////////////////////////////
  template <class T, class A> 
  inline typename String_template<T, A>::size_type String_template<T, A>::find_last_of(value_type _Ch, size_type nOff) const
  {
    size_t len = length(); 
    if (len <= nOff)
      return -1;

    char *pos = m_str + len - 1;
    for (size_t i=len-nOff; i>0; i--)
    {
      if (*pos == _Ch)
        return (size_t)(pos - m_str);
      pos--;
    }

    return -1;
  }

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline typename String_template<T, A>::size_type String_template<T, A>::find_first_of( const String_template<T, A>& _Str, size_type _Off ) const
	{
		return find_first_of( _Str.m_str,_Off );
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline typename String_template<T, A>::size_type String_template<T, A>::find_first_of( value_type _Ch,size_type nOff ) const
	{
		if ( nOff > length() )
			return npos;
		value_type charSet[2] = { _Ch,0 };
		const_str str = strpbrk( m_str+nOff,charSet );
		return (str == NULL) ? -1 : (size_type)(str - m_str);
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline typename String_template<T, A>::size_type String_template<T, A>::find_first_of( const_str charSet,size_type nOff ) const
	{
		assert(_IsValidString(charSet));
		if ( nOff > length() )
			return npos;
		const_str str = strpbrk( m_str+nOff,charSet );
		return (str == NULL) ? -1 : (size_type)(str - m_str);
	}

	//size_type find_first_not_of(const _Self& __s, size_type __pos = 0) const 
	//{ return find_first_not_of(__s._M_start, __pos, __s.size()); }

	//size_type find_first_not_of(const _CharT* __s, size_type __pos = 0) const 
	//{ _STLP_FIX_LITERAL_BUG(__s) return find_first_not_of(__s, __pos, _Traits::length(__s)); }

	//size_type find_first_not_of(const _CharT* __s, size_type __pos,	size_type __n) const;

	//size_type find_first_not_of(_CharT __c, size_type __pos = 0) const;


	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline typename String_template<T, A>::size_type String_template<T, A>::find_first_not_of( const value_type* _Ptr,size_type _Off ) const
	{ return find_first_not_of( _Ptr,_Off,_strlen(_Ptr) ); }

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline typename String_template<T, A>::size_type String_template<T, A>::find_first_not_of( const String_template<T, A>& _Str,size_type _Off ) const
	{ return find_first_not_of( _Str.m_str,_Off ); }

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline typename String_template<T, A>::size_type String_template<T, A>::find_first_not_of( value_type _Ch,size_type _Off ) const
	{
		if (_Off > length())
			return npos;
		else {
			for (const value_type *str = begin()+_Off; str != end(); ++str)
				if (*str != _Ch)
					return size_type(str - begin()); // Character found!
			return npos;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline typename String_template<T, A>::size_type String_template<T, A>::find_first_not_of( const value_type* _Ptr,size_type _Off,size_type _Count ) const
	{
		if (_Off > length())
			return npos;
		else {
			const value_type *charsFirst = _Ptr,*charsLast = _Ptr+_Count;
			for (const value_type *str = begin()+_Off; str != end(); ++str)
			{
				const value_type *c;
				for (c = charsFirst; c != charsLast; ++c)
				{
					if (*c == *str)
						break;
				}
				if (c == charsLast)
					return size_type(str - begin());// Current character not in char set.
			}
			return npos;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A> String_template<T, A>::substr( size_type pos, size_type count ) const
	{
		if (pos >= length())
			return String_template<T, A>();
		if (count == npos)
		{
			count = length() - pos;
		}
		if (pos + count > length())
			count = length() - pos;
		return String_template<T, A>( m_str+pos,count );
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::erase( size_type nIndex,size_type nCount )
	{
		if (nCount + nIndex > length())
			nCount = length() - nIndex;
		if (nIndex < length())
		{
			_MakeUnique();
			size_type nNumToCopy = length() - (nIndex + nCount) + 1;
			_move( m_str+nIndex,m_str+nIndex+nCount,nNumToCopy );
			_header()->nLength = length() - nCount;
		}

		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::insert( size_type nIndex, value_type ch )
	{
		return insert(nIndex,1,ch);
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::insert( size_type nIndex,size_type nCount,value_type ch )
	{
		_MakeUnique();

		size_type nNewLength = length();
		if (nIndex > nNewLength)
			nIndex = nNewLength;
		nNewLength += nCount;

		if (capacity() < nNewLength)
		{
			StrHeader* pOldData = _header();
			const_str pstr = m_str;
			_AllocData(nNewLength);
			_copy( m_str,pstr,pOldData->nLength+1 );
			_FreeData(pOldData);
		}

		_move( m_str+nIndex+nCount, m_str+nIndex, (nNewLength-nIndex) );
		_set( m_str+nIndex,ch,nCount );
		_header()->nLength = nNewLength;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::insert( size_type nIndex,const_str pstr,size_type nCount )
	{
		size_type nInsertLength = nCount;
		size_type nNewLength = length();
		if (nInsertLength > 0)
		{
			_MakeUnique();
			if (nIndex > nNewLength)
				nIndex = nNewLength;
			nNewLength += nInsertLength;

			if (capacity() < nNewLength)
			{
				StrHeader* pOldData = _header();
				const_str pstr = m_str;
				_AllocData(nNewLength);
				_copy( m_str, pstr,(pOldData->nLength+1) );
				_FreeData(pOldData);
			}

			_move( m_str + nIndex + nInsertLength, m_str + nIndex, (nNewLength-nIndex-nInsertLength+1) );
			_copy( m_str + nIndex, pstr, nInsertLength );
			_header()->nLength = nNewLength;
			m_str[length()] = 0;
		}
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::insert( size_type nIndex,const_str pstr )
	{
		return insert( nIndex,pstr,_strlen(pstr) );
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::replace( size_type pos,size_type count,const_str strNew )
	{
		return replace( pos,count,strNew,_strlen(strNew) );
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::replace( size_type pos,size_type count,const_str strNew,size_type count2 )
	{
		erase( pos,count );
		insert( pos,strNew,count2 );
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::replace( size_type pos,size_type count,size_type nNumChars,value_type chNew )
	{
		erase( pos,count );
		insert( pos,nNumChars,chNew );
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::replace( value_type chOld,value_type chNew )
	{
		if (chOld != chNew)
		{
			_MakeUnique();
			value_type* strend = m_str + length();
			for (value_type* str = m_str; str != strend; ++str)
			{
				if (*str == chOld)
				{
					*str = chNew;
				}
			}
		}
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::replace( const_str strOld,const_str strNew )
	{
		size_type nSourceLen = _strlen(strOld);
		if (nSourceLen == 0)
			return *this;
		size_type nReplacementLen = _strlen(strNew);

		size_type nCount = 0;
		value_type* strStart = m_str;
		value_type* strEnd = m_str + length();
		value_type* strTarget;
		while (strStart < strEnd)
		{
			while ((strTarget = _strstr(strStart, strOld)) != NULL)
			{
				nCount++;
				strStart = strTarget + nSourceLen;
			}
			strStart += _strlen(strStart) + 1;
		}

		if (nCount > 0)
		{
			_MakeUnique();

			size_type nOldLength = length();
			size_type nNewLength =  nOldLength + (nReplacementLen-nSourceLen)*nCount;
			if (capacity() < nNewLength || _header()->nRefCount > 1)
			{
				StrHeader* pOldData = _header();
				const_str pstr = m_str;
				_AllocData(nNewLength);
				_copy( m_str, pstr, pOldData->nLength );
				_FreeData(pOldData);
			}
			strStart = m_str;
			strEnd = m_str + length();

			while (strStart < strEnd)
			{
				while ( (strTarget = _strstr(strStart, strOld)) != NULL)
				{
					size_type nBalance = nOldLength - ((size_type)( strTarget - m_str) + nSourceLen);
					_move( strTarget + nReplacementLen, strTarget + nSourceLen, nBalance );
					_copy( strTarget, strNew, nReplacementLen );
					strStart = strTarget + nReplacementLen;
					strStart[nBalance] = 0;
					nOldLength += (nReplacementLen - nSourceLen);
				}
				strStart += _strlen(strStart) + 1;
			}
			_header()->nLength = nNewLength;
		}
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline void String_template<T, A>::swap( String_template<T, A>& _Str )
	{
		value_type *temp = _Str.m_str;
		_Str.m_str = m_str;
		m_str = temp;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::Format( const_str format,... )
	{
		assert(_IsValidString(format));

		value_type temp[4096]; // Limited to 4096 characters!
		va_list argList;
		va_start(argList, format );
		vsnprintf_s(temp, 4096, 4096, format, argList); 
		temp[4095] = '\0';
		va_end(argList);
		*this = temp;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
#define __ascii_tolower(c)      ( (((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c) )
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::MakeLower()
	{
		_MakeUnique();
		for (value_type *s = m_str; *s != 0; s++)
		{
			*s = __ascii_tolower(*s);
		}
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::MakeLowerLocale()
	{
		_MakeUnique();
		for (value_type *s = m_str; *s != 0; s++)
		{
			*s = ::tolower(*s);
		}
		return *this;
	}

  //////////////////////////////////////////////////////////////////////////
  template <class T, class A> 
  inline String_template<T, A>& String_template<T, A>::FixPathToUnix()
  {
    _MakeUnique();
    for (value_type *s = m_str; *s != 0; s++)
    {
      if (*s == '\\')
        *s='/';
    }
    return *this;
  }

	//////////////////////////////////////////////////////////////////////////
	template <class T, class A> 
	inline String_template<T, A>& String_template<T, A>::MakeUpper()
	{
		_MakeUnique();
		for (value_type *s = m_str; *s != 0; s++)
		{
			*s = ::toupper(*s);
		}
		return *this;
	}

	typedef String_template<char> String;
	typedef String_template<wchar_t> StringW;

	// Variant of String_template<T, A> which does not share memory with other strings.
#ifndef SWIG
	class StringLocal: public String_template<char>
	{
	public:
		typedef String_template<char> String;
		StringLocal() 
		{}
		StringLocal( const StringLocal& str )
			: String(str.c_str())
		{}
		StringLocal( const String& str )
			: String(str.c_str())
		{}
		StringLocal( const_str str )
			: String(str)
		{}

		StringLocal& operator=( const StringLocal& str )
		{
			String::operator=(str.c_str());
			return *this;
		}
		StringLocal& operator=( const String& str )
		{
			String::operator=(str.c_str());
			return *this;
		}
		StringLocal& operator=( const_str str )
		{
			String::operator=(str);
			return *this;
		}
	};
#endif

	// Not using THCAR type anymore. Only c-style string support
	template< int MAX_STR_LEN >
	class CFixedString
	{
	public:
		// constructs empty CFixedString
		CFixedString()
		{
			Empty();
		}
		// from a single character
		CFixedString(char ch)
		{
			m_szBuffer[0] = ch;
			m_szBuffer[1] = 0;
		}
		// from an ANSI string (converts to TCHAR)
		CFixedString(const char * lpsz)
		{      
#if defined(_WIN32) || defined(_WIN64)
			assert(!::IsBadStringPtr(lpsz,-1));
#endif
			assert(strlen(lpsz) <= MAX_STR_LEN);

			if( strlen(lpsz)<MAX_STR_LEN ) 
				strcpy_s(m_szBuffer,lpsz); 
			else 
				Empty();
		}

		// Attributes

		char m_szBuffer[MAX_STR_LEN+1];  // Allocate string space + 0-char

		// Methods

		const char* c_str() const 
		{
			return m_szBuffer;
		}
		// get data length
		size_t GetLength() const 
		{
			return strlen(m_szBuffer); 
		};
		// TRUE if zero length
		bool IsEmpty() const 
		{ 
			return m_szBuffer[0] == 0; 
		};
		// clear contents to empty
		void Empty() 
		{ 
			m_szBuffer[0] = 0;
		};
		// return single character at zero-based index
		char GetAt(int nIndex) const
		{
			assert( nIndex>=0 && nIndex<=MAX_STR_LEN );
			return m_szBuffer[nIndex];
		}

		char operator[] (int nIndex) const 
		{ 
			assert( nIndex>=0 && nIndex<=MAX_STR_LEN );
			return m_szBuffer[nIndex];
		}
		// set a single character at zero-based index
		void SetAt(int nIndex, char ch)
		{
			assert( nIndex>=0 && nIndex<=MAX_STR_LEN );
			m_szBuffer[nIndex] = ch;
		}
		// return pointer to const string
		operator const char *() const 
		{ 
			return m_szBuffer; 
		};

		// Overloaded assignment

		// set string content to single character
		const CFixedString& operator=(char ch)
		{
			m_szBuffer[0] = ch;
			m_szBuffer[1] = 0;
			return *this;
		}
		// copy string content from ANSI string (converts to TCHAR)
		const CFixedString& operator=(const char * lpsz)
		{      
#if defined(_WIN32) || defined(_WIN64)
			assert(!::IsBadStringPtr(lpsz,-1));
#endif
			if( strlen(lpsz)<=MAX_STR_LEN ) 
				strcpy_s(m_szBuffer,lpsz); 
			else 
				Empty();

			return *this;
		}

		// String concatenation

		// concatenate a single character
		const CFixedString& operator += (char ch)
		{      
			if( GetLength() <= MAX_STR_LEN-1 ) {
				char szTmp[2] = {ch,0};
				strcat_s(m_szBuffer,szTmp);
			}
			return *this;
		}
		// concatenate a UNICODE character after converting it to TCHAR
		CFixedString operator+(const char * str)
		{
#if defined(_WIN32) || defined(_WIN64)
			assert(!::IsBadStringPtr(lpsz,-1));
#endif
			if( strlen(m_szBuffer) + strlen(str) <= MAX_STR_LEN) 
				strcat_s( m_szBuffer, str );
		}
		const CFixedString& operator+=(const char * lpsz)
		{      
#if defined(_WIN32) || defined(_WIN64)
			assert(!::IsBadStringPtr(lpsz,-1));
#endif
			if( GetLength() + strlen(lpsz) <= MAX_STR_LEN ) 
				strcat_s(m_szBuffer,lpsz);
			return *this;
		}

		// string comparison
		bool operator == (const char * str) const { return (Compare(str) == 0); };
		bool operator != (const char * str) const { return (Compare(str) != 0); };
		bool operator <= (const char * str) const { return (Compare(str) <= 0); };
		bool operator <  (const char * str) const { return (Compare(str) <  0); };
		bool operator >= (const char * str) const { return (Compare(str) >= 0); };
		bool operator >  (const char * str) const { return (Compare(str) >  0); };

		// straight character comparison
		int Compare(const char * lpsz) const { return strcmp(m_szBuffer,lpsz); };
		// compare ignoring case
		int CompareNoCase(const char * lpsz) const { return strcmp(m_szBuffer,lpsz); };

		// Upper/lower/reverse conversion

		// NLS aware conversion to uppercase
		void MakeUpper() { strupr(m_szBuffer); };
		// NLS aware conversion to lowercase
		void MakeLower() { strlwr(m_szBuffer); };

		// String manipulation

		CFixedString Left(int len) 
		{
			CFixedString<MAX_STR_LEN> dest;
			if( len>GetLength() ) len = GetLength();
			strncpy_s( dest.m_szBuffer, m_szBuffer, len );
			dest.m_szBuffer[len] = 0;
			return dest;
		}
		CFixedString Mid(int pos,int len=-1) 
		{
			CFixedString<MAX_STR_LEN> dest;
			if( len<0 ) len = GetLength()-pos;
			if( pos+len>GetLength() ) len = GetLength() - pos;
			if( len<=0 ) return dest;
			strncpy_s( dest.m_szBuffer, &m_szBuffer[pos], len );
			dest.m_szBuffer[len] = 0;
			return dest;
		}
		CFixedString Right(int len) 
		{
			CFixedString<MAX_STR_LEN> dest;
			int pos = GetLength()-len;
			if( pos<0 ) {
				pos = 0;
				len = GetLength();
			}
			strncpy_s( dest.m_szBuffer, &m_szBuffer[pos], len );
			dest.m_szBuffer[len] = 0;
			return dest;
		}

		// Searching

		// find character starting at left, -1 if not found
		int Find(char ch) const
		{
			const char * p = strchr(m_szBuffer, ch);
			if(p==NULL) 
				return -1;
			return p - m_szBuffer;
		}
		// find character starting at right
		int ReverseFind(char ch) const
		{
			const char * p = strrchr(m_szBuffer, ch);
			if(p==NULL) 
				return -1;
			return p - m_szBuffer;
		}
		// find first instance of substring
		int Find(const char * lpszSub) const
		{
#if defined(_WIN32) || defined(_WIN64)            
			assert(!::IsBadStringPtr(lpszSub,-1));
#endif            
			const char * p = strstr(m_szBuffer, lpszSub);
			if(p==NULL) 
				return -1;
			return p - m_szBuffer;
		}

	};
}

