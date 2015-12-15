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


#include "Public/Common/Autoref.h"

typedef void *EVENT_HANDLE;
typedef void *THREAD_HANDLE;

struct StreamEngineParams;
class IStreamCallback;
class IReadStreamProxy;

enum
{
	ERROR_UNKNOWN_ERROR          = 0xF0000000,
	ERROR_UNEXPECTED_DESTRUCTION = 0xF0000001,
	ERROR_INVALID_CALL           = 0xF0000002,
	ERROR_CANT_OPEN_FILE         = 0xF0000003,
	ERROR_REFSTREAM_ERROR        = 0xF0000004,
	ERROR_OFFSET_OUT_OF_RANGE    = 0xF0000005,
	ERROR_REGION_OUT_OF_RANGE    = 0xF0000006,
	ERROR_SIZE_OUT_OF_RANGE      = 0xF0000007,
	ERROR_CANT_START_READING     = 0xF0000008,
	ERROR_OUT_OF_MEMORY          = 0xF0000009,
	ERROR_ABORTED_ON_SHUTDOWN    = 0xF000000A,
	ERROR_OUT_OF_MEMORY_QUOTA    = 0xF000000B,
	ERROR_ZIP_CACHE_FAILURE      = 0xF000000C,
	ERROR_USER_ABORT             = 0xF000000D
};



enum StreamReadParamsFlagEnum
{
	// Set this flag if you want using Callback function
	SRP_FLAGS_ASYNC_CALLBACK = 1,
	SRP_FLAGS_MAKE_PERMANENT = 1 << 2,
	SRP_FLAGS_MAKE_TRANSIENT = 1 << 3,
	SRP_FLAGS_ASYNC_PROGRESS = 1 << 4,
	SRP_QUICK_STARTREAD = 1 << 5
};

struct StreamReadParams
{
	StreamReadParams (
		DWORD * _dwUserData = 0,
		int _nPriority = 0,
		unsigned _nLoadTime = 0,
		unsigned _nMaxLoadTime = 0,
		unsigned _nOffset = 0,
		unsigned _nSize = 0,
		void* _pBuffer = NULL,
		unsigned _nFlags = 0,
    unsigned short _nIDSOurce = 0
	):
		dwUserData (_dwUserData),
		nPriority(_nPriority),
		nLoadTime(_nLoadTime),
		nMaxLoadTime(_nMaxLoadTime),
		pBuffer (_pBuffer),
		nOffset (_nOffset),
		nSize (_nSize),
		nFlags (_nFlags),
    nIDSource(_nIDSOurce)
	{
	}

	DWORD *  dwUserData;

	int nPriority;
	unsigned nLoadTime;
	unsigned nMaxLoadTime;
	void* pBuffer;
	unsigned nOffset;
	unsigned nSize;
	unsigned nFlags;
  unsigned short nIDSource;
};

class IReadStream;

//TYPEDEF_AUTOPTR(IReadStream);
typedef CSmartPtr<IReadStreamProxy> IReadStreamProxy_AutoPtr;
typedef CSmartPtr<IReadStreamProxy> IReadStreamProxyPtr;
//typedef IReadStream * IReadStreamPtr;
class IStreamEngine;

class IReadStream {
public:

  virtual ~IReadStream() {};
  virtual void AddRef() = 0;
  virtual void Release() = 0;

  virtual const char * GetFileName() const = 0;
  virtual int GetSource() const = 0;
  virtual void SetSource(int nSource) = 0;
  virtual bool Activate() = 0;
  virtual unsigned GetFileSize() const = 0;
  virtual void Register (IReadStreamProxy* pProxy) = 0;
  virtual void Unregister (IReadStreamProxy* pProxy) = 0;
  virtual bool IsError()  = 0;
  // request to abort comes from the proxy. This doesn't means immediate deallocation.
  virtual void Abort(IReadStreamProxy* pProxy) = 0;
  // Client (through the given Proxy) has requested priority rise
  virtual void OnRaisePriority (IReadStreamProxy* pProxy, unsigned nPriority) = 0;
  virtual DWORD ReadDataOverlapped(char *pData, uint32 size, OVERLAPPED *overlapped, LPOVERLAPPED_COMPLETION_ROUTINE callback) = 0;

  virtual bool isOverlapped() const = 0;
  virtual HANDLE GetFile () = 0;
  virtual IStreamEngine* GetEngine() = 0;
  virtual void* GetFileData(uint32 offset, uint32 size) = 0;
  virtual unsigned GetArchiveOffset()const = 0;
  virtual void OnIOExecuted(IReadStreamProxy* pProxy) = 0;
  virtual void FreeBuffer() = 0;
};

class IStreamFactory {
public:
  // Probably we need override proxy too
  //virtual IReadStream * CreateStreamProxy(const char* szSource, class IReadStream* pStream, IStreamCallback* pCallback, StreamReadParams* pParams) = 0;
  virtual IReadStream* CreateStream(const char * strFileName, IStreamEngine* pEngine) = 0;
  virtual void UpdateStream(IReadStream*) {};
  virtual const char * GetStreamName() const = 0;
};

class IStreamEngine
{
public:
	enum
	{
		FLAGS_DISABLE_CALLBACK_TIME_QUOTA = 1
	};
  //! registers a new stream (added to the system: queued)
  virtual void Register (IReadStream*)= 0;
  //! unregisters: happens upon release of all resources
  virtual void Unregister (IReadStream*)= 0;

  // support overlapping
  virtual bool isOverlappedIoEnabled()= 0;

  //
  virtual void SortIOJobs() = 0;

  //
  virtual void OnIOJobExecuted (IReadStreamProxy* pJobProxy) = 0;
  virtual void RemoveProxy(IReadStreamProxy* pJobProxy) = 0; 

  virtual unsigned UpdateAndWait (unsigned nMilliseconds, unsigned nFlags) = 0;

	virtual IReadStreamProxyPtr StartRead (const char* szFile, IStreamCallback* pCallback = NULL, StreamReadParams* pParams = NULL) = 0;
	virtual unsigned GetFileSize (const char* szFile) = 0;
	virtual void Update (unsigned nFlags = 0) = 0;
	virtual unsigned Wait(unsigned nMilliseconds, unsigned nFlags = 0) = 0;
	virtual void SuspendCallbackTimeQuota(){}
	virtual void ResumeCallbackTimeQuota(){}

  // return source number 
  virtual int RegisterStreamFactory(IStreamFactory * ) = 0;
  // unregister source
  virtual bool UnRegisterStreamFactory(IStreamFactory * ) = 0;
  //! Set main stream factory. 0 is default, means just disk operations.
  virtual void SetPrimaryStreamFactory(int num) = 0;

  virtual void SetAutobalance(int lengthQueue, int desiredFrameRate) = 0;

	virtual ~IStreamEngine() {}
};


class AutoSuspendTimeQuota
{
public:
	AutoSuspendTimeQuota(IStreamEngine* pStreamEngine)
	{
		m_pStreamEngine = pStreamEngine;
		pStreamEngine->SuspendCallbackTimeQuota();
	}

	~AutoSuspendTimeQuota()
	{
		m_pStreamEngine->ResumeCallbackTimeQuota();
	}
protected:
	IStreamEngine* m_pStreamEngine;
};

class IReadStreamProxy
{
public:
	virtual void AddRef() = 0;
	virtual void Release() = 0;
	virtual bool IsError() = 0;
	virtual bool IsFinished() = 0;
	virtual unsigned int GetBytesRead(bool bWait=false) = 0;
	virtual const void* GetBuffer () = 0;
	virtual void Abort() {}
	virtual void RaisePriority (unsigned int nPriority) {}
	virtual DWORD * GetUserData() = 0;
  virtual void Wait() = 0;
  virtual const StreamReadParams& GetParams() const = 0;
  virtual void FinalizeIO() = 0;
  virtual void OnFinishRead(unsigned nError) = 0;
  virtual	bool StartRead (unsigned nMemQuota = 0x7FFFFFFF) = 0;
  virtual bool IsIOExecuted() = 0;
  virtual Engine2::String Dump() = 0;
  virtual size_t GetSize() = 0;
  virtual uint32 GetIOError() const = 0;
protected:

	virtual ~IReadStreamProxy() {}
};


class IStreamCallback
{
public:
	// For some applications, even partially loaded data can be useful.
  virtual void AddReference() {};
  virtual void ReleaseReference() {};
	virtual void StreamOnProgress (IReadStreamProxy* pStream) {}
	virtual void StreamOnComplete (IReadStreamProxy* pStream, unsigned nError) = 0;
};



enum StreamingStrategy
{
	SS_FIFO,
	SS_FAST,
	SS_PRIORITIZED,
	SS_MULTISTREAM
};


struct StreamEngineParams
{
	StreamingStrategy nStrategy;
	unsigned nMaxBytesPerSecond;
	unsigned nMaxCallbackTicksPerSecond;
	unsigned nMaxStreams;
};

typedef CSmartPtr<IReadStream> IReadStream_AutoPtr;

//////////////////////////////////////////////////////////////////////////
struct IMemoryBuffer : public CRefSmartPtr
{
	// Resizes internal memory buffer
	virtual void Resize( size_t newSize ) = 0;
	// Return size of internal memory buffer
	virtual size_t GetSize() const = 0;
	// Get pointer to memory buffer. 
	virtual uint8* GetBuffer() const = 0;
};
typedef CSmartPtr<IMemoryBuffer> IMemoryBufferPtr;

//////////////////////////////////////////////////////////////////////////
class DLLIMPORT CMemoryBuffer : public IMemoryBuffer
{
public:
	CMemoryBuffer() : m_nSize(0), m_pBuffer(0) {};

	//////////////////////////////////////////////////////////////////////////
	virtual void Resize( size_t newSize )
	{
		FreeBuffer();
		m_pBuffer = (uint8*)malloc(newSize);
	}
	size_t GetSize() const { return m_nSize; };
	virtual uint8* GetBuffer() const { return m_pBuffer; }
	//////////////////////////////////////////////////////////////////////////

protected:
	virtual ~CMemoryBuffer() { FreeBuffer(); };
	void FreeBuffer()
	{
		if (m_pBuffer)
		{
			free(m_pBuffer);
		}
	}

private:
	size_t m_nSize;
	uint8 *m_pBuffer;
};

// Priority for this streaming object
enum EStreamingPriority
{
	eStreamingPriority_Low,
	eStreamingPriority_Normal,
	eStreamingPriority_High,
};

//////////////////////////////////////////////////////////////////////////
struct SStreamingParams
{
public:
	SStreamingParams() {};

	Engine2::String filename;

	// ResourceObject who owns this streaming params
	class CResourceObject* pResourceObject;

	// Priority for this object
	EStreamingPriority ePriority;

	uint32 flags;

	// Loaded data buffer.
	IMemoryBufferPtr pDataBuffer;
};
