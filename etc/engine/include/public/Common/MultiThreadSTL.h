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

// Thread safe containers
#include <algorithm>

namespace mt
{
	template <typename T>
	class vector
	{
	public:
		typedef	T	value_type;
		typedef size_t size_type;

	public:
		vector() {}
		vector( const vector<T> &rOther )
		{		
			AUTO_LOCK(cs); 
      CCritSection& otherCS = rOther.cs; 
      AUTO_LOCK(otherCS); 
			v = rOther.v;
		}
		vector& operator=( const vector<T> &rOther )
		{		
      CCritSection& otherCS = rOther.cs;
			AUTO_LOCK(cs); 
			AUTO_LOCK(otherCS); 
			v = rOther.v;
			return *this;
		}

		bool   empty() const { AUTO_LOCK(cs); return v.empty(); }
		void   clear() { AUTO_LOCK(cs); v.clear(); }

		size_type size() const { AUTO_LOCK(cs); return v.size(); }
		size_type capacity() const { AUTO_LOCK(cs); return v.size(); }
		void resize( size_type sz ) { AUTO_LOCK(cs); v.resize( sz ); }
		void reserve( size_type sz ) { AUTO_LOCK(cs); v.reserve( sz ); }

		T&       operator[]( size_type index ) { AUTO_LOCK(cs); return v[index]; }
		const T& operator[]( size_type index ) const { AUTO_LOCK(cs); return v[index]; }
		const T& front() const { AUTO_LOCK(cs); return v.front(); }
		const T& back() const { AUTO_LOCK(cs); return v.back(); }
		T&       back() { AUTO_LOCK(cs); return v.back(); }

		void push_back( const T& val ) { AUTO_LOCK(cs); return v.push_back(val); }
		void pop_back() { AUTO_LOCK(cs); return v.pop_back(); }

		void swap( std::vector<T> &rOther ) { AUTO_LOCK(cs); v.swap(rOther); }

		template <class CompareFunc>
		void sort( const CompareFunc &func ) { AUTO_LOCK(cs); std::sort( v.begin(),v.end(),func ); }

		//////////////////////////////////////////////////////////////////////////
		bool try_pop_front( T& outval )
		{
			AUTO_LOCK(cs); 
			if (!v.empty())
			{
				outval = v.front();
				v.erase(v.begin());
				return true;
			}
			return false;
		};
		//////////////////////////////////////////////////////////////////////////
		bool try_pop_back( T& outval )
		{
			AUTO_LOCK(cs); 
			if (!v.empty())
			{
				outval = v.back();
				v.pop_back();
				return true;
			}
			return false;
		};

		//////////////////////////////////////////////////////////////////////////
		bool try_remove( const T& value )
		{
			AUTO_LOCK(cs);
			if(!v.empty())
			{
				typename std::vector<T>::iterator it = std::find(v.begin(), v.end(), value);
				if (it != v.end())
				{
					v.erase(it);
					return true;
				}
			}
			return false;
		};

	public:
		CCritSection& get_lock() const { return cs; }

	private:
		std::vector<T> v;
		mutable	CCritSection cs;
	};

	//////////////////////////////////////////////////////////////////////////
	// templates container
	//////////////////////////////////////////////////////////////////////////
	template<class T, class cont_t = std::vector<T> >
	class container
	{
	private:
		mutable CCritSection m_lock;
		cont_t m_queue;
	public:
		void push_back(const T& v) { AUTO_LOCK(m_lock); m_queue.push_back(v); }
		bool try_pop_back(T& v) { AUTO_LOCK(m_lock); if(!m_queue.empty()) { v = m_queue.back(); m_queue.pop_back(); return true; } return false; }
		inline bool empty() const { return m_queue.empty(); }
	};
}
