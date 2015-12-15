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

#include "Common.h"

#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#define NOT_USE_TRACE_STL

#if defined(_WIN32)

#if !defined(__APPLE__)
#include <xmemory>
  #ifdef NOT_USE_TRACE_STL
    #define NOT_TRACE_STL
  #endif
#else
#define NOT_TRACE_STL
#endif
#include <limits>



#ifndef NOT_TRACE_STL
namespace Engine2
{
  template<typename T>
  class ObjectTraits {
  public : 
    //    convert an ObjectTraits<T> to ObjectTraits<U>

    template<typename U>
    struct rebind {
      typedef ObjectTraits<U> other;
    };

  public : 
    inline explicit ObjectTraits() {}
    inline ~ObjectTraits() {}
    template <typename U>
    inline explicit ObjectTraits(ObjectTraits<U> const&) {}

    //    address

    inline T* address(T& r) { return &r; }
    inline T const* address(T const& r) { return &r; }

    inline void construct(T* p, const T& t) { new(p) T(t); }
    inline void destroy(T* p) { p->~T(); }
  };

  template<typename T>
  class StandardAllocPolicy {
  public : 
    //    typedefs

    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

  public : 
    template<typename U>
    struct rebind {
      typedef StandardAllocPolicy<U> other;
    };

  public : 
    inline explicit StandardAllocPolicy() {}
    inline ~StandardAllocPolicy() {}
    inline explicit StandardAllocPolicy(StandardAllocPolicy const&) {}
    template <typename U>
    inline explicit StandardAllocPolicy(StandardAllocPolicy<U> const&) {}

    //    memory allocation

    inline pointer allocate(size_type cnt, 
      typename std::allocator<void>::const_pointer = 0) { 
        return reinterpret_cast<pointer>(::operator 
          new(cnt * sizeof (T))); 
    }
    inline void deallocate(pointer p, size_type) 
    { ::operator delete(p); }

    inline size_type max_size() const { 
      return -1;//std::numeric_limits<size_type>::max(); 
    }
  };    //    end of class StandardAllocPolicy

  template<typename T, typename T2>
  inline bool operator==(StandardAllocPolicy<T> const&, 
    StandardAllocPolicy<T2> const&) { 
      return true;
  }
  template<typename T, typename OtherAllocator>
  inline bool operator==(StandardAllocPolicy<T> const&, 
    OtherAllocator const&) { 
      return false; 
  }

	template<typename T, typename Policy = StandardAllocPolicy<T> >
	class TrackAllocPolicy : public Policy {
	private : 
		typedef Policy AllocationPolicy;

	public : 
		//    convert an TrackAllocPolicy<T> to TrackAllocPolicy<U>

		template<typename U>
		struct rebind {
			typedef TrackAllocPolicy<U, 
				typename AllocationPolicy::template rebind<U>::other> other;
		};

	public : 
		inline explicit TrackAllocPolicy():total_(0), current_(0), peak_(0) {}
		inline ~TrackAllocPolicy() {}
		inline explicit 
			TrackAllocPolicy(TrackAllocPolicy const& rhs):Policy(rhs), 
			total_(rhs.total_), current_(rhs.current_), peak_(rhs.peak_) {}
		template <typename U>
		inline explicit 
			TrackAllocPolicy(TrackAllocPolicy<U> const& rhs):Policy(rhs), 
			total_(0), current_(0), peak_(0) {}

		//    memory allocation

		typename AllocationPolicy::pointer 
			allocate(typename AllocationPolicy::size_type cnt, 
			typename std::allocator<void>::const_pointer hint = 0) { 
				typename AllocationPolicy::pointer p = 
					AllocationPolicy::allocate(cnt, hint);

				RegisterAllocation(typeid(T).name(), cnt*sizeof(T));
				this->total_ += cnt;
				this->current_ += cnt;
				if ( this->current_ > this->peak_ ) {
					this->peak_ = this->current_;
				}
				return p;
		}
		inline void deallocate(typename AllocationPolicy::pointer p, 
			typename AllocationPolicy::size_type cnt) { 
				RegisterDeallocation(typeid(T).name(), cnt*sizeof(T));
				AllocationPolicy::deallocate(p, cnt);
				this->current_ -= cnt;
		}

		// get stats

		inline typename AllocationPolicy::size_type 
			TotalAllocations() { return this->total_; }
		inline typename AllocationPolicy::size_type 
			CurrentAllocations() { return this->current_; }
		inline typename AllocationPolicy::size_type 
			PeakAllocations() { return this->peak_; }

	private : 
		//    total allocations

		typename AllocationPolicy::size_type total_;    
		//    current allocations

		typename AllocationPolicy::size_type current_; 
		//    peak allocations   

		typename AllocationPolicy::size_type peak_;    
	};    //    end of class TrackAllocPolicy


	// determines if memory from another

	// allocator can be deallocated from this one

	template<typename T, typename Policy, typename T2, typename Policy2>
	inline bool operator==(TrackAllocPolicy<T, Policy> const& lhs, 
		TrackAllocPolicy<T2, Policy2> const& rhs) { 
			return operator==(static_cast<const Policy&>(lhs), 
				static_cast<const Policy&>(rhs)); 
	}
	template<typename T, typename Policy, typename OtherAllocator>
	inline bool operator==(TrackAllocPolicy<T, 
		Policy> const& lhs, OtherAllocator const& rhs) { 
			return operator==(static_cast<const Policy&>(lhs), rhs); 
	}


  template<typename T, typename Policy = 
    /*StandardAllocPolicy<T>*/TrackAllocPolicy<T>, typename Traits = ObjectTraits<T> >
  class Allocator : public Policy, public Traits {
  private : 
    typedef Policy AllocationPolicy;
    typedef Traits TTraits;

  public : 
    typedef typename AllocationPolicy::size_type size_type;
    typedef typename AllocationPolicy::difference_type difference_type;
    typedef typename AllocationPolicy::pointer pointer;
    typedef typename AllocationPolicy::const_pointer const_pointer;
    typedef typename AllocationPolicy::reference reference;
    typedef typename AllocationPolicy::const_reference const_reference;
    typedef typename AllocationPolicy::value_type value_type;

  public : 
    template<typename U>
    struct rebind {
      typedef Allocator<U, typename AllocationPolicy::template rebind<U>::other, 
        typename TTraits::template rebind<U>::other > other;
    };

  public : 
    inline explicit Allocator() {}
    inline ~Allocator() {}
    inline Allocator(Allocator const& rhs):Traits(rhs), Policy(rhs) {}
    template <typename U>
    inline Allocator(Allocator<U> const&) {}
    template <typename U, typename P, typename T2>
    inline Allocator(Allocator<U, P, 
      T2> const& rhs):Traits(rhs), Policy(rhs) {}
  };    //    end of class Allocator


  // determines if memory from another

  // allocator can be deallocated from this one

  template<typename T, typename P, typename Tr>
  inline bool operator==(Allocator<T, P, 
    Tr> const& lhs, Allocator<T, 
    P, Tr> const& rhs) { 
      return operator==(static_cast<const P&>(lhs), 
        static_cast<const P&>(rhs)); 
  }
  template<typename T, typename P, typename Tr, 
    typename T2, typename P2, typename Tr2>
    inline bool operator==(Allocator<T, P, 
    Tr> const& lhs, Allocator<T2, P2, Tr2> const& rhs) { 
      return operator==(static_cast<const P&>(lhs), 
        static_cast<const P2&>(rhs)); 
  }
  template<typename T, typename P, typename Tr, typename OtherAllocator>
  inline bool operator==(Allocator<T, P, 
    Tr> const& lhs, OtherAllocator const& rhs) { 
      return operator==(static_cast<P&>(lhs), rhs); 
  }
  template<typename T, typename P, typename Tr>
  inline bool operator!=(Allocator<T, P, Tr> const& lhs, 
    Allocator<T, P, Tr> const& rhs) { 
      return !operator==(lhs, rhs); 
  }
  template<typename T, typename P, typename Tr, 
    typename T2, typename P2, typename Tr2>
    inline bool operator!=(Allocator<T, P, Tr> const& lhs, 
    Allocator<T2, P2, Tr2> const& rhs) { 
      return !operator==(lhs, rhs); 
  }
  template<typename T, typename P, typename Tr, 
    typename OtherAllocator>
    inline bool operator!=(Allocator<T, P, 
    Tr> const& lhs, OtherAllocator const& rhs) { 
      return !operator==(lhs, rhs); 
  }

	template<class T, size_t alignment>
	struct AlignedAllocator : std::allocator<T>
	{
		template<class U>
		struct rebind { typedef AlignedAllocator<U, alignment> other; };

		typedef std::allocator<T> base;

		typedef typename base::pointer pointer;
		typedef typename base::size_type size_type;

		pointer allocate(size_type n)
		{
			if(pointer p = (pointer)_aligned_malloc(n, alignment))
				return p;
			throw std::bad_alloc("aligned_allocator");
		}

		pointer allocate(size_type n, void const*)
		{
			return this->allocate(n);
		}

		void deallocate(pointer p, size_type)
		{
			_aligned_free(p);
		}
	};
};
#endif
#else
#define NOT_TRACE_STL
#endif

#ifndef NOT_TRACE_STL

template<typename T> struct AllocationStrategy { typedef Engine2::Allocator<T> Allocator; };

#define STLLIST(x) std::list< x, Engine2::Allocator< x > >
#define STLSET(x) std::set< x, std::less< x >, Engine2::Allocator< x > >
#define STLSTRING std::basic_string<char, std::char_traits<char>, Engine2::Allocator<char> >
#define STLMAP(x, y) std::map< x, y, std::less< x >, Engine2::Allocator< std::pair< const x, y > > >
#define STLVECTOR_WITH_TYPEDEF(x, y) typedef STLVECTOR(x) y; y

#define stlvector(x) STLVECTOR(x) 
#define stllist(x) STLLIST(x) 
#define stlset(x) STLSET(x) 
#define stlstring STLSTRING 
#define stlmap(x,y) STLMAP(x,y) 
#define stlvector_with_typedef(x, y) STLVECTOR_WITH_TYPEDEF(x, y) 

#define stlvector_with_pair(x, y) std::vector< std::pair<x,y>, Engine2::Allocator< std::pair<x,y> > >

#define STLVECTOR(x) std::vector<x, typename AllocationStrategy<x>::Allocator >

#else

template<typename T> struct AllocationStrategy { typedef std::allocator<T> Allocator; };

#define STLLIST(x) std::list<x>
#define STLSET(x) std::set<x>
#define STLSTRING std::string
#define STLMAP(x,y) std::map<x,y> 
#define STLVECTOR_WITH_TYPEDEF(x, y) typedef STLVECTOR(x) y; y

#define stlvector(x) STLVECTOR(x) 
#define stllist(x) STLLIST(x) 
#define stlset(x) STLSET(x) 
#define stlstring STLSTRING 
#define stlmap(x,y) STLMAP(x,y) 
#define stlvector_with_typedef(x, y) STLVECTOR_WITH_TYPEDEF(x, y) 
#define stlvector_with_pair(x, y) std::vector< std::pair<x,y> >

#define STLVECTOR(x) std::vector<x>
#endif

template<class T>
size_t GetVectorSize(STLVECTOR(T)& vec)
{
  return vec.capacity() * sizeof(T);
}
