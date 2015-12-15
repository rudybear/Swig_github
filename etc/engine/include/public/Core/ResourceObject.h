#pragma once

enum EResourceType
{
	eResourceType_Model,
	eResourceType_Texture,
	eResourceType_Terrain,
	eResourceType_TerrainPatch,
	eResourceType_Count
};

// Resource name is just a string
typedef Engine2::String ResourceName;

struct IResourceObject
{
	enum ELoadFlags
	{
		eLoadFlag_Blocking = BIT(0)
	};
	virtual void AddRef() = 0;
	virtual void Release() = 0;

	virtual EResourceType GetResourceType() const = 0;
	virtual ResourceName GetResourceName() const = 0;

	//////////////////////////////////////////////////////////////////////////
	// Resource Loading 
	// For flags @see ELoadFlags
	virtual bool StartLoading( uint32 flags ) = 0;
	virtual bool StartLoadingWithOffset( uint32 flags,uint32 nFileOffset,uint32 nMaxDataSize ) = 0;
	virtual void AbortLoading() = 0;

protected:
	virtual ~IResourceObject() {}

	// Callbacks
	virtual void StreamOnAsyncComplete( SStreamingParams &params ) {}
	virtual void StreamOnComplete( SStreamingParams &params ) {};
};

typedef CSmartPtr<IResourceObject> IResourceObjectPtr;

//////////////////////////////////////////////////////////////////////////
// All resources must inherit from this class
//////////////////////////////////////////////////////////////////////////
class DLLIMPORT CResourceObject : public IResourceObject
{
public:
	virtual void AddRef();
	virtual void Release();

	//virtual EResourceType GetType() const = 0;
	virtual ResourceName GetResourceName() const { return m_resourceName; };

	// Initiate loading of the resource.
	// Resources should mostly be loaded asynchronously
	virtual bool StartLoading( uint32 flags );
	virtual bool StartLoadingWithOffset( uint32 flags,uint32 nFileOffset,uint32 nMaxDataSize );
	virtual void AbortLoading();
  virtual bool LoadingComplete( uint32 flags ) { return true; }

protected:
	CResourceObject();
	virtual ~CResourceObject();
	virtual void DeleteThis();

	// Allow associated resources to be freed
	virtual void FreeResource() {};

	friend class CResourceManager;
	virtual void SetResourceName( const ResourceName &name );

protected:
	ResourceName m_resourceName;
	int m_resourceRefCount;
	int m_streamHandle;
	bool m_bStreaming;

protected:
	friend class CStreamingObject;
	void OnStreamAsyncCallback( SStreamingParams &params );
	void OnStreamLoadFinishedCallback( SStreamingParams &params );

private:
	class CStreamingObject *m_pStreamingObject; // Cannot use smart pointer due to forward declaration
};

typedef CSmartPtr<CResourceObject> CResourceObjectPtr;
