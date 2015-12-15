#pragma once

#include <algorithm>
namespace stl
{
	template <typename Container,class T>
	inline bool find_and_erase( Container &c,const T& item )
	{
    //typedef Container _Type;
		typename Container::iterator it;
    it = std::find( c.begin(),c.end(),item );
		if (it != c.end())
		{
			c.erase(it);
			return true;
		}
		return false;
	}

	template <class Map,class Key,class Value>
	inline Value find_in_map( Map &m,const Key& key,const Value &defaultValue )
	{
		typename Map::const_iterator it = m.find(key);
		if (it != m.end())
		{
			return it->second;
		}
		return defaultValue;
	}
}

namespace boost
{
	class Referencable
	{
		int m_nRefCount;
	protected:
		Referencable() : m_nRefCount(0) {}
		virtual ~Referencable() {}; // Must have virtual destructor.

		virtual void AddRef() { (++m_nRefCount); }
		virtual void Release()
		{
			if((--m_nRefCount) <= 0)
			{
				delete this;
			}
		}

	private:	
		friend void intrusive_ptr_release(Referencable * p);
		friend void intrusive_ptr_add_ref(Referencable * p);
	};

	inline void intrusive_ptr_add_ref(Referencable * p)
	{
		p->AddRef();
	}

	inline void intrusive_ptr_release(Referencable * p)
	{
		p->Release();
	}
}
typedef boost::Referencable CRefTarget;