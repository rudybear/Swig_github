#pragma once

struct IEntityPropertySet;

struct IEntityPropertyMetadata
{
	virtual void SetName( const char *name ) = 0;
	virtual const char* GetName() const = 0;

	virtual void SetDisplayName( const char *name ) = 0;
	virtual const char* GetDisplayName() const = 0;

	virtual void SetDescription( const char *str ) = 0;
	virtual const char* GetDescription() const = 0;

	virtual void SetLimits( float fMin,float fMax ) = 0;
	virtual void GetLimits( float &fMin,float &fMax ) = 0;

	virtual void SetUIType( const char *sUIType ) = 0;
	virtual const char* GetUIType() const = 0;
};

// Possible property types
enum EPropertyType
{
	ePropertyTypeUnknown,
	ePropertyTypeInt,
	ePropertyTypeBoolean,
	ePropertyTypeFloat,
	ePropertyTypeVec3,
	ePropertyTypeQuat,
	ePropertyTypeString,
	ePropertyTypeEntity, // EntityID
	ePropertyTypeArray   // This property is an array of sub properties
};

class CPropertyVariant
{
private:
	EPropertyType type;
	union
	{
		int i;
		bool b;
		float f;
		float v[4];
		const char* str;
		EntityID eid;
	};

public:

	CPropertyVariant() : type(ePropertyTypeUnknown) {};
	CPropertyVariant( int value ) : type(ePropertyTypeInt),i(value) {};
	CPropertyVariant( bool value ) : type(ePropertyTypeBoolean),b(value) {};
	CPropertyVariant( float value ) : type(ePropertyTypeFloat),f(value) {};
	CPropertyVariant( const CVec3 &value ) : type(ePropertyTypeVec3) { v[0] = value.x; v[1] = value.y; v[2] = value.z; v[3] = 0; };
	CPropertyVariant( const CQuat &value ) : type(ePropertyTypeQuat) { v[0] = value.x; v[1] = value.y; v[2] = value.z; v[3] = value.w; };
	CPropertyVariant( const EntityID &value ) : type(ePropertyTypeEntity),eid(value) {};
	CPropertyVariant( const char *value ) : type(ePropertyTypeString),str(value) {};
	CPropertyVariant( const Engine2::String &value ) : type(ePropertyTypeString),str(value.c_str()) {};

	bool IsType( EPropertyType t ) const { return type == t; }

	template <class T>
	bool ToType( T &value )
	{
		// Unsupported type.
		return false;
	}
	bool ToType( int &value ) const
	{
		switch (type)
		{
		case ePropertyTypeInt:     value = (int)i; return true;
		case ePropertyTypeBoolean: value = (int)b; return true;
		case ePropertyTypeFloat:   value = (int)f; return true;
		case ePropertyTypeEntity:  value = (int)eid; return true;
      default:
        value = 0;
        return false;        
		}
	}
	bool ToType( bool &value ) const
	{
		switch (type)
		{
		case ePropertyTypeInt:     value = i != 0; return true;
		case ePropertyTypeBoolean: value = (bool)b; return true;
		case ePropertyTypeFloat:   value = f != 0; return true;
		case ePropertyTypeEntity:  value = false;  return true;
      default:
        value = false;
        return false;
		}
	}
	bool ToType( float &value ) const
	{
		switch (type)
		{
		case ePropertyTypeInt:     value = (float)i; return true;
		case ePropertyTypeBoolean: value = (float)b; return true;
		case ePropertyTypeFloat:   value = f;        return true;
      default:        
        value = 0.0f;
        return false;
        
		}
	}
	bool ToType( CVec3 &value ) const
	{
		switch (type)
		{
		case ePropertyTypeVec3: value.x = v[0]; value.y = v[1]; value.z =  v[2]; return true;
      default:        
        value.Set(0,0,0);
        return false;
        
		}
	}
	bool ToType( CQuat &value ) const
	{
		switch (type)
		{
		case ePropertyTypeQuat: value.x = v[0]; value.y = v[1]; value.z =  v[2]; value.w = v[3]; return true;
      default:                
        value.SetIdentity();
        return false;
        
		}
	}
	bool ToType( const char *value ) const
	{
		switch (type)
		{
		case ePropertyTypeString: value = str; return true;
      default:                
        value = "";
        return false;
        
		}
	}
	bool ToType( Engine2::String &value ) const
	{
		switch (type)
		{
		case ePropertyTypeString: value = str; return true;
      default:                
        value = "";
        return false;
        
		}
	}
	bool ToType( EntityID value ) const
	{
		switch (type)
		{
		case ePropertyTypeInt:    value = (EntityID)i; return true;
		case ePropertyTypeEntity: value = eid; return true;
      default:                
        value = 0;
        return false;
        
		}
	}

};

//////////////////////////////////////////////////////////////////////////
// Variable Property used by entities.
//////////////////////////////////////////////////////////////////////////
struct IEntityProperty
{
	virtual const char* GetName() const = 0;
	virtual	EPropertyType	GetType() const = 0;
	virtual	int		GetSize() const = 0;

	virtual IEntityPropertyMetadata* GetMetadata() = 0;

	virtual void Set( CPropertyVariant variant ) = 0;
	virtual CPropertyVariant Get() const = 0;

	// Access to child properties of the property.
	virtual IEntityPropertySet* GetChildProperties() = 0;
};

//////////////////////////////////////////////////////////////////////////
// Represent a set of properties.
//////////////////////////////////////////////////////////////////////////
struct IEntityPropertySet
{
public:
	virtual void AddProperty( IEntityProperty *pProperty ) = 0;
	virtual void DeleteProperty( IEntityProperty *pProperty ) = 0;

	virtual IEntityProperty* FindProperty( const char *sName,bool bRecursive=true ) const = 0;

	virtual IEntityProperty* BindProperty( const char *sPropertyName,int    *memberVariable ) = 0;
	virtual IEntityProperty* BindProperty( const char *sPropertyName,bool   *memberVariable ) = 0;
	virtual IEntityProperty* BindProperty( const char *sPropertyName,float  *memberVariable ) = 0;
	virtual IEntityProperty* BindProperty( const char *sPropertyName,CVec3   *memberVariable ) = 0;
	virtual IEntityProperty* BindProperty( const char *sPropertyName,CQuat   *memberVariable ) = 0;
	virtual IEntityProperty* BindProperty( const char *sPropertyName,Engine2::String *memberVariable ) = 0;
	virtual IEntityProperty* BindProperty( const char *sPropertyName,EntityID *memberVariable ) = 0;
};
