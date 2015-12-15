#pragma once

typedef unsigned int EntityID;
typedef unsigned int EntitySectorID;

#include "Public/Common/Autoref.h"
#include "IEntityProperty.h"

struct IEntity;
struct IEntityComponent;
struct IEntitySystem;

#define MAX_ENTITY_TAGS 32

#define BIT(x) (1<<(x))

enum EEntityEvent
{
	eEntityEventDestroy       = 0, // Sent when entity is destroyed
	eEntityEventUpdate,            // Sent when entity is updated, every frame
	eEntityEventTransform,         // Sent when entity is changing transform
};

struct SEntityEvent
{
	EEntityEvent event;
	//CVec3 v;
};

struct IEntityComponent : public CAutoRef
{
	// Component Types
	enum EType
	{
		eTypeTransform = 0, // Transform must always be first with value 0 (for optimization)
		eTypeRender,
		eTypeGeometry,
		eTypePhysics,
		eTypeAnimation,
		eTypeCamera,
		eTypeLight,
		eTypeUser = 100, // User types start from this.
	};
	
	// Get name of the component.
	virtual const char* GetName() const = 0;
	
	// Get type of the component.
	EType GetType() const { return m_type; };

	// Get Host entity
	virtual IEntity* GetEntity() const = 0;

	// Get access to component property set.
	virtual IEntityPropertySet* Props() = 0;

	virtual void OnEvent( SEntityEvent &event ) = 0;

public:
	//////////////////////////////////////////////////////////////////////////
	IEntityComponent() : m_eventMask(0),m_type(eTypeUser) {};
	void HandleEntityEvent( EEntityEvent event ) { m_eventMask |= 1 << ((int)event); }

	// Mask for entity events handled for this component
	unsigned int m_eventMask;
	// Type of the component.
	EType m_type;
};

// BOOST and STL is forbidden in interfaces!!!!
typedef CSmartPtr<IEntityComponent> IEntityComponentPtr;

struct IEntityClass : public CRefTarget
{
	virtual const char* GetName() const = 0;

	// Creates components for this entity class.
	virtual void CreateComponents( IEntity *pEntity ) = 0;
};

//////////////////////////////////////////////////////////////////////////
// Prefab is a collection of pre-configured entities
//////////////////////////////////////////////////////////////////////////
struct IEntityPrefab
{

};

struct IEntityLayer
{

};

// Sector in which entity is located.
struct IEntitySector
{
	
};

struct IEntity
{
	enum ETransformFlags
	{
		eTransformPosition   = BIT(0), // Position changed
		eTransformRotation   = BIT(1), // Rotation changed
		eTransformScale      = BIT(2), // Scale changed
		eTransformInherited  = BIT(3), // Inherited change from parent entity
		eTransformEditor     = BIT(4), // When editor transform entity
	};
	enum EFlags
	{
		eFlagDeleted         = BIT(0), // Entity is deleted
	};

	//////////////////////////////////////////////////////////////////////////
	virtual EntityID GetID() const = 0;
	virtual IEntityClass* GetClass() const = 0;

	virtual IEntityPrefab* GetPrefab() const  = 0;

	// Access to the entity properties.
	virtual IEntityPropertySet* Props() = 0;

	//////////////////////////////////////////////////////////////////////////
	// Components
	//////////////////////////////////////////////////////////////////////////
	virtual IEntityComponentPtr GetComponent( IEntityComponent::EType eComponentType ) = 0;
	virtual IEntityComponentPtr CreateComponent( IEntityComponent::EType eComponentType ) = 0;
	virtual void AddComponent( IEntityComponentPtr pComponent ) = 0;
	virtual void RemoveComponent( IEntityComponent::EType eComponentType ) = 0;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Entity location in the world.
	//////////////////////////////////////////////////////////////////////////
	virtual IEntitySector* GetSector() const = 0;
	virtual void GetTransform( CVec3 &p,CQuat &q,CVec3 &s ) = 0;
	virtual void SetTransform( const CVec3 &p,const CQuat &q,const CVec3 &s,int nTransformFlags=0 ) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual IEntity* GetParent() const = 0;
	virtual void AttachChild( IEntity *pChild,bool bKeepWorldTransform=false ) = 0;
	virtual void DetachChild( IEntity *pChild,bool bKeepWorldTransform=false ) = 0;
	virtual void DetachThis( bool bKeepWorldTransform=false ) = 0;

	//virtual void SerializeXml( C)
	// Send event to entity and all its components registered to handle it.
	virtual void SendEvent( SEntityEvent &event ) = 0;
};

struct SEntitySpawnParams
{
	EntityID id;
	CVec3 pos;
	CVec3 scale;
	CQuat rotation;
	const char *sName;
	const char *sClassName;
	IEntityPrefab* pPrefab;
	IEntitySector* pSector;

	SEntitySpawnParams() : id(0),pos(0,0,0),scale(1,1,1),sName(NULL),sClassName(NULL),pPrefab(NULL),pSector(NULL) { rotation.SetIdentity(); }
};

struct IEntitySystemListener;

struct IEntitySystem : public CRefTarget
{
	virtual IEntity* SpawnEntity( const SEntitySpawnParams &params ) = 0;
	virtual IEntity* GetEntity( EntityID entityId ) = 0;
	virtual void DeleteEntity( EntityID entityId ) = 0;

	virtual void Subscribe(IEntitySystemListener* pListener) = 0;
	virtual void Unsubscribe(IEntitySystemListener* pListener) = 0;
	
	//////////////////////////////////////////////////////////////////////////
	// Entity Classes
	//////////////////////////////////////////////////////////////////////////
	virtual void RegisterClass( IEntityClass* pClass ) = 0;
	virtual IEntityClass* FindClass( const char *sClassName ) = 0;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Entity tags
	//////////////////////////////////////////////////////////////////////////
	virtual void SetTag( unsigned char nIndex,const char *sTag ) = 0;
	virtual const char* GetTag( unsigned char nIndex ) const = 0;
	//////////////////////////////////////////////////////////////////////////

	// Called every frame to update entity system.
	virtual void Update() = 0;
};


struct IEntitySystemListener
{
	virtual void OnEntityAdded(EntityID id, IEntity* entity) {}
	virtual void OnEntityRemoved(EntityID id) {}
};

IEntitySystem* CreateEntitySystem(); // TODO: get rid of this declaration as soon as project converted into DLL
