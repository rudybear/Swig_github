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

//! This is for internal debug purposes only!!!!!
//! DO NOT USE THIS FOR REAL STUFF!!!
class CAutoRef
{
private:
  int m_iRefcounter;
public:
  CAutoRef() : m_iRefcounter(0) {;};

  virtual ~CAutoRef() {;};

  void AddRef() { ++m_iRefcounter;};
  void Release() { --m_iRefcounter;};

  int  GetReferences() { return m_iRefcounter;};
};


template <class _I> class CSmartPtr 
{
private:
  _I* p;
public:
  CSmartPtr() : p(NULL) {}
#if defined(LINUX64)
  CSmartPtr(typeof(__null)) : p(NULL) {}
#endif
  CSmartPtr(int Null) : p(NULL) {}
  CSmartPtr(_I* p_)
  {
    p = p_;
    if (p)
      p->AddRef();
  }

  CSmartPtr(const CSmartPtr &p_)
  {
    p = p_.p;
    if (p)
      p->AddRef();
  }
  ~CSmartPtr()
  {
    if (p)
      p->Release();
  }
  _I* get() const { return p; }

  void reset( _I * t = 0) { operator=(t); }

  size_t use_count() const { return p->use_count(); }
  operator _I*() const { return p; } 
  operator const _I*() const { return p; }
  _I& operator*() const { return *p; }
  _I* operator->(void) const { return p; }
  CSmartPtr&  operator=(_I* newp)
  {
    if (newp)
      newp->AddRef();
    if (p)
      p->Release();
    p = newp;
    return *this;
  }
  CSmartPtr&  operator=(const CSmartPtr &newp)
  {
    if (newp.p)
      newp.p->AddRef();
    if (p)
      p->Release();
    p = newp.p;
    return *this;
  }
  operator bool() const 
  {
    return p != NULL;
  };
  bool operator !() const 
  {
    return p == NULL;
  };
  bool  operator ==(const _I* p2) const 
  {
    return p == p2;
  };
  bool  operator ==(_I* p2) const 
  {
    return p == p2;
  };
  bool  operator ==(const CSmartPtr<_I>& rhs) const
  {
    return p == rhs.p;
  }
  bool  operator !=(const _I* p2) const 
  {
    return p != p2;
  };
  bool  operator !=(_I* p2) const 
  {
    return p != p2;
  };
  bool  operator !=(const CSmartPtr &p2) const 
  {
    return p != p2.p;
  };
  bool  operator <(const _I* p2) const 
  {
    return p < p2;
  };
  bool  operator >(const _I* p2) const 
  {
    return p > p2;
  };
  // set our contained pointer to null, but don't call Release()
  // useful for when we want to do that ourselves, or when we know that
  // the contained pointer is invalid
  friend _I* ReleaseOwnership( CSmartPtr<_I>& ptr )
  {
    _I * ret = ptr.p;
    ptr.p = 0;
    return ret;
  }

};

template <class _I>
inline bool operator ==(const CSmartPtr<_I> &p1, int null)	
{
  assert(!null);
  return !(bool)p1;	
}
template <class _I>
inline bool operator !=(const CSmartPtr<_I> &p1, int null)
{
  assert(!null);
  return (bool)p1;	
}
template <class _I>
inline bool operator ==(int null, const CSmartPtr<_I> &p1)
{
  assert(!null);
  return !(bool)p1;	
}
template <class _I>
inline bool operator !=(int null, const CSmartPtr<_I> &p1)
{
  assert(!null);
  return (bool)p1;	
}

#include "MultiThread.h"

class IRefSmartPtr
{
public:
  virtual ~IRefSmartPtr() {};
  virtual void AddRef() = 0;
  virtual void Release() = 0;
  virtual int NumRefs() const = 0;
  virtual int  GetReferences() = 0;
};

class CRefSmartPtr
{
public:
	CRefSmartPtr():
			m_nRefCounter (0)
			{
			}

			virtual ~CRefSmartPtr()
			{
				//assert (!m_nRefCounter);
			}

			void AddRef()
			{
				//	++m_nRefCounter;
				InterlockedAdd(&m_nRefCounter, 1);
			}


			void Release()
			{
				InterlockedAdd(&m_nRefCounter, -1);
				if (m_nRefCounter == 0)
					DeleteThis();
				else if(m_nRefCounter < 0)
				{
					assert( 0 && "Negative Ref Count" );
					_debugbreak();
				}
			}
			// Warning: use for debugging/statistics purposes only!
			int NumRefs() const
			{
				return m_nRefCounter;
			}

			int  GetReferences() { return m_nRefCounter;};

			int use_count() const 
			{
				return m_nRefCounter;
			}
protected:
	virtual void DeleteThis()
	{
		delete this;
	}

	volatile int m_nRefCounter;
};

// Definitions for using SHARED_PTR_NAMESPACE::intrusive pointer on CRefSmartPtr
namespace boost
{
	inline void intrusive_ptr_add_ref( CRefSmartPtr *P ) { P->AddRef(); }
	inline void intrusive_ptr_release( CRefSmartPtr *P ) { P->Release(); }
}
