////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __MultiThread_h__
#define __MultiThread_h__

#pragma once
#ifdef _MSC_VER
# pragma warning(disable: 4793) //  '__asm' : causes native code generation for function 'void SpinLock(volatile int *,int,int)'
#endif

#if defined(_WIN32) 
#include <process.h> 
#endif

#include <vector>

FORCEINLINE void SpinLock(volatile int *pLock,int checkVal,int setVal)
{ 
#if defined(_WIN32) && !defined(_WIN64)
	__asm
	{
		mov edx, setVal
		mov ecx, pLock
Spin:
		mov eax, checkVal
		lock cmpxchg [ecx], edx
    pause
		jnz Spin
	}
#else
	// NOTE: The code below will fail on 64bit architectures!
	while(_InterlockedCompareExchange((volatile LONG*)pLock,setVal,checkVal)!=checkVal);
#endif
}

//////////////////////////////////////////////////////////////////////////
FORCEINLINE int InterlockedAdd(volatile int *pVal, int iAdd)
{
	return (int)InterlockedExchangeAdd((volatile LONG*)pVal,iAdd);
}

FORCEINLINE CRITICAL_SECTION * Eng2CreateCriticalSection()
{
#if defined(_WIN32) || defined(_WIN64)    
	CRITICAL_SECTION* pCS = new CRITICAL_SECTION;
	InitializeCriticalSection(pCS);
	return pCS;
#else
#if defined(TARGET_OS_POSIX)
	CRITICAL_SECTION* pCS = new CRITICAL_SECTION;
    pthread_mutexattr_t attr;
    int res = pthread_mutexattr_init(&attr);
    if (res)
    {
        delete pCS;
        pCS = 0;
    }
    
    res = pthread_mutex_init(pCS, &attr);
    if (res)
    {
        delete pCS;
        pCS = 0;
    }
    
    return pCS;
  
#endif       
#endif    
}



#endif
//////////////////////////////////////////////////////////////////////////
FORCEINLINE void  Eng2EnterCriticalSection( void *cs )
{
#if defined(_WIN32) || defined(_WIN64)    
	EnterCriticalSection((CRITICAL_SECTION*)cs);
#else
#if defined(TARGET_OS_POSIX)
    pthread_mutex_lock((CRITICAL_SECTION*)cs);
#endif       
#endif    
    
}

inline void  Eng2DeleteCriticalSection( void *cs )
{
#if defined(_WIN32) || defined(_WIN64)    
    CRITICAL_SECTION *pCS = (CRITICAL_SECTION*)cs;
    DeleteCriticalSection(pCS);
    delete pCS;
#else
#if defined(TARGET_OS_POSIX)
    CRITICAL_SECTION *pCS = (CRITICAL_SECTION*)cs;    
    pthread_mutex_destroy((CRITICAL_SECTION*)pCS);
    delete pCS;
#endif       
#endif    
    
}

//////////////////////////////////////////////////////////////////////////
inline void  Eng2LeaveCriticalSection( void *cs )
{
#if defined(_WIN32) || defined(_WIN64)    
	LeaveCriticalSection((CRITICAL_SECTION*)cs);
#else
#if defined(TARGET_OS_POSIX)
    pthread_mutex_unlock((CRITICAL_SECTION*)cs);
#endif       
#endif
}

//////////////////////////////////////////////////////////////////////////
// Base class for the objects that need thread safe intrusive reference counting
//////////////////////////////////////////////////////////////////////////
class CThreadSafeRefTarget
{
public:
	CThreadSafeRefTarget() : m_refCount(0) {}

	void AddRef()
	{
		InterlockedAdd( &m_refCount,1 );
	}
	void Release()
	{
		int prevCount = InterlockedAdd( &m_refCount,-11 );
		if (prevCount < 2)
		{
			if (prevCount == 1)
			{
				DeleteThis();
			}
			else
			{
				assert( 0 && "Negative Ref Count" );
			}
		}
	}
protected:
	virtual ~CThreadSafeRefTarget() {};
	virtual void DeleteThis() { delete this; }

private:
	volatile int m_refCount;
};

// Definitions for using SHARED_PTR_NAMESPACE::intrusive pointer on CThreadSafeRefTarget
namespace boost
{
	inline void intrusive_ptr_add_ref( CThreadSafeRefTarget *P ) { P->AddRef(); }
	inline void intrusive_ptr_release( CThreadSafeRefTarget *P ) { P->Release(); }
}

//////////////////////////////////////////////////////////////////////////
struct WriteLock
{
	WriteLock(volatile int &rw) { SpinLock(&rw,0,0x10000); prw=&rw; }
	~WriteLock() { InterlockedAdd(prw,-0x10000); }
private:
	volatile int *prw;
};

//////////////////////////////////////////////////////////////////////////
// Start mt namespace
namespace mt
{

//////////////////////////////////////////////////////////////////////////
class CMutex
{
public:
	CMutex() : m_pCritSection(Eng2CreateCriticalSection())
	{}

	~CMutex()
	{
		Eng2DeleteCriticalSection(m_pCritSection);
	}

	class CLock
	{
	public:
		CLock( CMutex& mtx ) : m_pCritSection(mtx.m_pCritSection)
		{
			Eng2EnterCriticalSection(m_pCritSection);
		}
		~CLock()
		{
			Eng2LeaveCriticalSection(m_pCritSection);
		}

	private:
		CLock( const CLock& );
		CLock& operator=( const CLock& );

		void *m_pCritSection;
	};

private:
	CMutex( const CMutex& );
	CMutex& operator=( const CMutex& );

	CRITICAL_SECTION* m_pCritSection;
};

//////////////////////////////////////////////////////////////////////////
class CEvent
{
public:

#ifdef WIN32
	explicit CEvent( bool bInitiallyOwn = false, bool bManualReset = false )
	{
		m_handle = (void*)::CreateEvent(NULL, (bManualReset)?TRUE:FALSE, (bInitiallyOwn)?TRUE:FALSE, NULL);
	}
	virtual ~CEvent() { ::CloseHandle(m_handle); };
	bool SetEvent() { return ::SetEvent(m_handle) != FALSE; };
	bool PulseEvent() { return ::PulseEvent(m_handle) != FALSE; };
	bool ResetEvent() { return ::ResetEvent(m_handle) != FALSE; };
	
	// Wait for event.
	// When time negative waits without timeout
	bool Wait( int timeoutInMs=-1 ) const
	{
		if (timeoutInMs < 0)
			timeoutInMs = INFINITE;
		if (::WaitForSingleObject(m_handle, timeoutInMs) == WAIT_TIMEOUT)
			return false;
		return true;
	}
#else //WIN32
	explicit CEvent( bool bInitiallyOwn = false, bool bManualReset = false ) {(void)m_handle;}
	virtual ~CEvent() {};
	bool SetEvent() { return true; };
	bool PulseEvent() { return true; };
	bool ResetEvent() { return true; };
	bool Wait( int timeoutInMs=-1 ) const { return true; };
#endif //WIN32

private:
	void *m_handle;
};

//////////////////////////////////////////////////////////////////////////
class DLLIMPORT CThread : public CThreadSafeRefTarget
{
public:
	CThread() : m_handle(0), m_bStarted(false), m_bRunning(false) {};

	static void SetName( const char * name );

	void Start();
	
	// Terminate thread
	// Override and implement it to properly exit Run method.
	virtual void Terminate() {}

protected:
	virtual ~CThread();

	// Must be overriden by derived class
	virtual void Run() = 0;
	// Called before thread terminates.
	virtual void OnTerminate() {};

protected:
	CThread( const CThread& );
	CThread& operator=( const CThread& );

	THREAD_HANDLE m_handle;
	volatile bool m_bStarted;
	volatile bool m_bRunning;

private:
#if defined(TARGET_OS_POSIX)  
	static void* __cdecl ThreadFuncThis( void *pThisPtr )
#else
  static void __cdecl ThreadFuncThis( void *pThisPtr )
#endif
	{
		// Assign Unhandled exception handler for this thread here.
		CThread *pThis = (CThread*)pThisPtr;
		pThis->m_bStarted = true;
		pThis->m_bRunning = true;
		pThis->Run();
		pThis->m_bRunning = false;
		pThis->OnTerminate();
#if defined(TARGET_OS_POSIX)      
    return 0;
#endif
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Threads implementation. For static linking it must be declared inline otherwise creating multiple symbols
////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void CThread::Start()
{
#if defined (_WIN32) || defined(_WIN64)    
	m_handle = (THREAD_HANDLE) _beginthread(ThreadFuncThis, 0, this);
#else
	#if defined(TARGET_OS_POSIX)    
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_t * pt = (pthread_t*)m_handle;
		/*int res =*/ pthread_create(pt, &attr, ThreadFuncThis, this);

		pthread_attr_destroy(&attr);
	#endif    
#endif        
}

//////////////////////////////////////////////////////////////////////////
inline CThread::~CThread()
{
#if defined (_WIN32) || defined(_WIN64)
	if (m_handle != 0)
	{
		Terminate();
		::WaitForSingleObject( m_handle, INFINITE );
	}
#else    
#if defined(TARGET_OS_POSIX)    
	pthread_exit(0);
#endif    
#endif
}

//////////////////////////////////////////////////////////////////////////
inline void CThread::SetName( const char * name )
{
#if defined (_WIN32) || defined(_WIN64)    
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; // must be 0x1000
		const char *szName; // pointer to name (in user addr space)
		DWORD dwThreadID; // thread ID (-1=caller thread)
		DWORD dwFlags; // reserved for future use, must be zero
	} THREADNAME_INFO;

	THREADNAME_INFO info;
	{
		info.dwType = 0x1000;
		info.szName = name;
		info.dwThreadID = DWORD(-1);
		info.dwFlags = 0;
	}
	__try
	{
#ifndef _WIN64
		RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info );
#else
    RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (const ULONG_PTR*)&info );
#endif
	}
	__except (EXCEPTION_CONTINUE_EXECUTION)
	{
	}
#endif
}

// namespace mt.
}

/////////////////////////////////////////////////////////////////////////////////////
// Safe critical section robot: when constructing, it's locking the section, when
//  destructing, it's unlocking it
/////////////////////////////////////////////////////////////////////////////////////
template <class T>
class CAutoLock
{
	T& m_csThis; // the critical section that is to be locked on construction and unlocked on destruction
public:
	// on construction, we lock the critical section
	CAutoLock(T& csThis):
			m_csThis(csThis)
			{
				csThis.Lock();
			}
  
	CAutoLock(const T& csThis):
  m_csThis(csThis)
  {
    csThis.Lock();
  }
  
			// on destruction, we unlock it
			~CAutoLock()
			{
				m_csThis.Unlock();
			}
};

template <class T>
class CAutoUnlock
{
	T& m_csThis; // the critical section that is to be locked on construction and unlocked on destruction
public:
	// on construction, we lock the critical section
	CAutoUnlock (T& csThis):
			m_csThis(csThis)
			{
				csThis.Unlock();
			}
			// on destruction, we unlock it
			~CAutoUnlock()
			{
				m_csThis.Lock();
			}
};


/////////////////////////////////////////////////////////////////////////////////////
// Abstraction of critical section synchronization object. Auto-constructs/destructs
// the embedded critical section
/////////////////////////////////////////////////////////////////////////////////////
class CCritSection
{
  //this is a mutex implementation under linux too since semaphores provide additional functionality not provided by the windows compendent
  void *csThis;
public:

  CCritSection()
  {
    csThis = 0;
    csThis = Eng2CreateCriticalSection();
  }
  ~CCritSection()
  {
    Eng2DeleteCriticalSection(csThis);
  }
  void Lock ()
  {
    Eng2EnterCriticalSection(csThis);
  }
  bool Try()
  {
    //return CryTryCriticalSection(csThis);
      return false;
  }
    
  void Unlock ()
  {
    Eng2LeaveCriticalSection(csThis);
  }

  // the lock and unlock facilities are disabled for explicit use,
  // the client functions should use auto-lockers and auto-unlockers
private:
  CCritSection (const CCritSection &);

  friend class CAutoLock<CCritSection>;
  friend class CAutoUnlock<CCritSection>;
};

#define AUTO_LOCK(csLock) CAutoLock<CCritSection> __AL__##csLock(csLock)
#define AUTO_LOCK_THIS() CAutoLock<CCritSection> __AL__this(*this)
#define AUTO_UNLOCK(csUnlock) CAutoUnlock<CCritSection> __AUl__##csUnlock(csUnlock)
#define AUTO_UNLOCK_THIS() CAutoUnlock<CCritSection> __AUl__##thisUnlock(*this)

// Include Thread Safe containers
#include "MultiThreadSTL.h"

struct NaiveJob
{
  virtual int execute() = 0;
  virtual ~NaiveJob() {}
};

extern int volatile g_TreadsLock;

struct NaiveJobManager
{

private:
  static void RunIfAvailable() {
    //TaskContainer::iterator it = std::find(tasks.begin(), tasks.end(), pTask);
    if (iThreadsAvailable && !tasks.empty()) {
      NaiveJob * pTask = tasks.back();
      tasks.pop_back();
#    if defined (_WIN32) || defined(_WIN64)    
        //m_handle = (THREAD_HANDLE) _beginthread(func, 0, p);
        _beginthread(NaiveJobManager::RunTask, 0, pTask);
        
#else
#if defined(TARGET_OS_POSIX)    
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        
        pthread_t  pt;// = (pthread_t*)m_handle;
        /*int res =*/ pthread_create(&pt, &attr, NaiveJobManager::RunTask, pTask);
        
        pthread_attr_destroy(&attr);
#endif    
#endif        

      --iThreadsAvailable;
    }
  }
    
#    if defined (_WIN32) || defined(_WIN64)    
  static void RunTask(void  *pData)
#else
#if defined(TARGET_OS_POSIX)   
  static void* RunTask(void  *pData)
#endif
#endif
  {

    NaiveJob * pTask = (NaiveJob*)pData;
    pTask->execute();
#if defined(TARGET_OS_POSIX)    
      return 0;
#endif
  }

public:

  typedef Engine2::Vector< NaiveJob * > TaskContainer;
  static TaskContainer tasks;
  static int iThreadsAvailable;

  NaiveJob * pJob;

  NaiveJobManager(NaiveJob * job  ) {
    pJob = job;
  }
  // guard
  ~NaiveJobManager()
  {
    RemoveTask(pJob);
  }


  static void StartTask(NaiveJob * pTask) 
  {

    WriteLock lock(g_TreadsLock);
    {
      tasks.insert(tasks.begin(), pTask);
      RunIfAvailable();
    }
  }

  static void RemoveTask(NaiveJob * pTask) 
  {
    delete pTask;
    {
      WriteLock lock(g_TreadsLock);
      ++iThreadsAvailable;
      RunIfAvailable();
    }
  }
};


//#endif // __MultiThread_h__
