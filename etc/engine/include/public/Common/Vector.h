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

#include "Allocator.h"
#include "Common.h"

namespace Engine2
{
	// Vector class 
	template<class T, class A = StandardAllocator>
	class DLLIMPORT Vector
	{
	public:

		typedef Vector<T, A>	 self_type;
		typedef T              value_type;
		typedef T*             iterator;
		typedef const T*       const_iterator;
		typedef T&             reference;
		typedef const T&       const_reference;
		typedef size_t			   size_type;


		Vector(size_type size) : m_data(0), m_capacity(0), m_size(0) { resize(size); }
		Vector(void) : m_data(0), m_capacity(0), m_size(0)   { }

		Vector(const self_type& v): m_data(0), m_capacity(0), m_size(0) {
			resize_raw(v.size());
			//assign(v);
			init(begin(), end(), v.begin());
		}

		template <class T1> Vector(const Vector<T1>& v): m_data(0), m_capacity(0), m_size(0) {
			resize_raw(v.size());
			assign(v);
		}

		~Vector(void) {	clear_destroy();}

		inline iterator begin() { return m_data; }
		inline const_iterator begin() const { return m_data; }
		inline iterator end() { return m_data + m_size;}
		inline const_iterator end() const { return m_data + m_size;}

		inline reference front() { return m_data[0]; }
		inline const_reference front() const {	return m_data[0];	}
		inline reference back() { 	return m_data[m_size-1]; }
		inline const_reference back() const { return m_data[m_size-1]; }

		inline size_type size() const { return m_size; }
		inline bool empty() const { return m_size == 0; }

		inline const_iterator  data() { return m_data; }

		inline self_type& operator = (const self_type& v) {
			if (&v != this) {
				resize_raw(v.size());
				init(begin(), end(), v.begin());
			}
			return *this;
		}

		inline reference operator[](size_type i) { 
			assert(i < m_size);
			return m_data[i];
		}

		iterator insert(iterator at)
		{
			iterator it = insert_raw(at);
			return new(it) T;
		}
		iterator insert(iterator at, T const& val)
		{
			iterator it = insert_raw(at);
			return new(it) T(val);
		}

		inline const_reference operator[](size_type i) const 
		{     
			assert(i < m_size);
			return m_data[i]; 
		}

		//inline reference operator[](size_type i)
		//{     
		//	assert(i >= 0 && i < size);
		//	return m_data[i]; 
		//}

		inline void clear() {
			resize(0);
		}

		inline void clear_destroy() {
			//_asm
			//{
			//	int 3
			//}
			destroy(begin(), end());

			if (m_data)
				A::deallocate(m_data, m_size * sizeof(T));
			m_size = m_capacity = 0;
		}

		inline void resize(size_type nCount)
		{
      if (nCount != m_size)
      {
			  size_type nOld = m_size;
			  destroy(begin()+nCount, end());
			  resize_raw(nCount);
			  init(begin()+nOld, end());
      }
		}

		inline void resize(size_type nCount, const T& value)
		{
      if (nCount != m_size)
      {
  			size_type nOld = m_size;
			  destroy(begin()+nCount, end());
			  resize_raw(nCount);
			  init(begin()+nOld, end(), value);
      }
		}

		inline void reserve(size_type nCount)
		{
			if (nCount > m_capacity) {
				// allocate the new one and copy
				iterator p =  static_cast<iterator>(A::allocate(nCount * sizeof(T)));
				memmove(p, m_data, m_size);
				A::deallocate(m_data, m_capacity* sizeof(T));
				m_data = p;
				m_capacity = nCount;
			}
		}

		inline iterator push_back()									
		{ 
			resize_raw(size()+1);
			return ::new(end()-1) T;
		}
		inline iterator push_back(T const& val)
		{ 
			resize_raw(size()+1);
			return ::new(end()-1) T(val);
		}

		inline void pop_back()
		{
			if (!empty())
			{
				erase( m_data + m_size - 1);
			}
		}

		template <class T1>
		void swap(Vector<T1>& v)
		{
			Engine2::swap(m_data, v.m_data);
			Engine2::swap(m_capacity, v.m_capacity);
			Engine2::swap(m_size, v.m_size);
		}

		int erase( T const& val )
		{
			int count = 0;
			for (iterator it = end()-1; it >= begin(); --it)
			{
				if (*it == val)
				{
					it = erase(it, it+1);
					count++;
				}
			}
			return count;
		}

		iterator erase(iterator first, iterator final)
		{
			ptrdiff_t pos = first-begin();
			ptrdiff_t count = final-first;

			// Destroy, then delete elems.
			destroy(first, final);
			move(first, end() - count, final);

			// Resize mem.
			resize_raw(size() - count);
			return begin()+pos;
		}

		iterator erase(iterator it)
		{
			return erase(it, it+1);
		}

		size_type erase(size_type i)
		{
			assert(i < size());
			erase(begin() + i);
			return i-1;
		}

	private:
		T *				m_data;
		size_type	m_capacity;
		size_type	m_size;

		iterator insert_raw(iterator at)
		{
			size_t pos = at-begin();

			// Realloc, then move elements.
			resize_raw(size()+1);
			move(begin()+pos+1, end(), begin()+pos);
			return begin()+pos;
		}

		inline void init(T* b, T* e) {
			for (; b < e; b++)
				new(b) T;
		}

		inline void init(iterator b, iterator e, const_reference value){
			for (; b < e; b++)
				new(b) T(value);
		}

		inline void init(iterator b, iterator e, const_iterator value){
			for (; b < e; b++)
				new(b) T(*value++);
		}

		inline void destroy(T* first, T* final)
		{
			for (; first < final; first++)
				first->~T();
		}

		inline void move(T* first, T* final, T const* src)
		{
			memmove(first, src, (size_t)final-(size_t)first);
		}

		inline void resize_raw(const size_type s) {

			if (m_capacity == 0 && s) {
				m_data = static_cast<iterator>( A::allocate(s* sizeof(T)));
				m_size = m_capacity = s;
			}
			else if (s > m_capacity)
			{
				// Grow if needed, to next power-of-two.
				size_type nCap = 4; //-V112
				while (nCap < s)
					nCap <<= 1;
				m_size = s;
				m_capacity = nCap;
				m_data = static_cast<iterator>( A::reallocate(m_data, nCap* sizeof(T)));
			}
			else
			{
				m_size = s;
			}
		}
	};
}

