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

//#include <string>
#include "public\core\ICore.h"
#include "public\gamemod\gamedefs.h"
#include "public\gamemod\iPhysObject.h"

class IBody;

enum PhysObjectTypes {
	eTypeRigidBody,
	eTypeSensor,
	eTypeJoint,
	eTypeCharacter,
	eTypeExplosion,
	eTypeCar,
	eTypeTerrain
};

enum PhysInertia {
	eInertiaAuto,
	eInertiaInfinite
};

enum SensorStates {
	eSensorOn,
	eSensorOff
};

enum PhysJointType {
	eJointBall,
	eJointHinge,
	eJointFixed,
	eJointDependent,
	eJointOrientation,
	eJointSliding,
	eJointPrismatic,
	eLimitLinear,
	eLimitAngular
};

struct PhysMaterial {
	float m_fStaticFriction;
	float m_fDynamicFriction;
	float m_fRestitution;
	PhysMaterial(float fStFriction, float fDyFriction, float fRestitution): m_fStaticFriction(fStFriction), m_fDynamicFriction(fDyFriction), m_fRestitution(fRestitution) {};
};

struct PhysRBParams
{
	CVec3 vecPos;
	CMatrix4 matRot;
	CVec3 vecVelocity;
	CVec3 vecAngularVelocity;
	CVec3 vecAcceleration;
	CVec3 vecAngularAcceleration;
	bool bDynamic;
	bool bActive;
	float fMass;
	int nCurrentType;
	int nRealType;
	CMatrix4 matInertia;
	int nInertiaType;
};

struct PhysCarParams
{
	float fScaleWidth;
	float fScaleHeight;
	float fScaleLength;
	float fWheelMn;
	float fSpringStiffness;
	float fSpringDamping;
	float fNominalSpringLength;
	float fRearAxis;
	float fFrontAxis;
	float fRearWheelDist;
	float fFrontWheelDist;
};

struct InteractionData {
	int nFlags;
	CVec3 vecPoint;
	CVec3 vecNormal;
	void * pData1;
	void * pData2;
};

struct TraceData {
	IBody * pBody;
	CVec3 vecPoint;
	CVec3 vecNormal;
};

//some globals 
#define plMinTime			0.02f


enum KEY_STATE
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_STOP,
	KEY_PASSIVESTOP,
	KEY_TURNLEFT,
	KEY_TURNRIGHT,
};

class IPhysEntity
{
public: 
	IPhysEntity(){};
	virtual ~IPhysEntity(){};
	virtual HRESULT PreFrameMove(float fDeltaT) = 0;
	virtual HRESULT Move(float fDeltaT) = 0;
	virtual HRESULT PostFrameMove(float fDeltaT) = 0;
	virtual int GetEntityType(void) = 0;

public:
	Engine2::String m_Name;
};

typedef void (*InteractionCallback)(const InteractionData& interation);

class IPhysRigidBody : public IPhysEntity
{
public:
	IPhysRigidBody(){};
	virtual ~IPhysRigidBody(){};
	virtual CVec3 GetVelocity() = 0;
	virtual void SetVelocity(const CVec3& vecVelocity) = 0;
	virtual void SetVelocityEx(const CVec3& vecVelocity) = 0;
	virtual CVec3 GetAcceleration() = 0;
	virtual void SetAcceleration(const CVec3& vecAcceleration) = 0;
	virtual void SetAngularVelocity(const CVec3& vecVelocity) = 0;
	virtual CVec3 GetAngularVelocity() = 0;
	virtual void SetDirection(const CVec3& vecDirection) = 0;
	virtual void ApplySelfForce(const CVec3& vecForce) = 0;
	virtual void ApplyForce(const CVec3& vecForce) = 0;
	virtual void ApplyImpulse(const CVec3& vecForce) = 0;
	virtual void ApplyForcePoint(const CVec3& vecForce, const CVec3& vecPoint) = 0;
	virtual void ApplyImpulsePoint(const CVec3& vecForce, const CVec3& vecPoint) = 0;
	virtual CVec3 GetPosition() = 0;
	virtual void SetPosition(const CVec3& vecPosition) = 0;
	virtual void SetRotation(const CMatrix4& matRot) = 0;
	virtual void SetTerrainRotation(const CMatrix4& matRot) = 0;
	virtual CMatrix4 GetRotation() = 0;
	virtual CMatrix4 GetTerrainRotation() = 0;
	virtual void SetType(int nType) = 0;
	virtual int GetType() = 0;
	virtual void* GetData() = 0;
	virtual float GetMass() = 0;
	virtual void SetMass(float) = 0;
	virtual void SetActiveEx(bool bActive, bool bAddRemove) = 0;
	virtual void SetActive(bool bActive) = 0;
	virtual bool GetActive() = 0;
	virtual void SetDynamic(bool bDynamic) = 0;
	virtual bool GetDynamic() = 0;
	virtual void SetInertia(int nInertia) = 0;
	virtual void SetInteractionCallback(InteractionCallback interaction) = 0;
	virtual bool EnableCheckMaterial(const char * pName) = 0;
	virtual void SetActorClip(const char * pName) = 0;
	virtual void SetActorSkip(const char * pName) = 0;
	virtual void SetActorStop(const char * pName) = 0;
	virtual bool EnableContactHandler(bool bCheckContacts) = 0;
	virtual bool IsMaterialContact(IBody*& pBody) = 0;
	virtual bool IsJoined() = 0;
	virtual CVec3 GetContactPoint() = 0;
	virtual CVec3 GetContactNormal() = 0;
	virtual CAABBox GetAABB() = 0;
	virtual void EnableGravity(bool bGravity) = 0;
	virtual void SetData(IBody * pData) = 0;
	virtual void SetMaterialProperties(float fStaticFriction, float fDynamicFriction, float fRestitution) = 0;
	virtual bool CanJump() = 0;

	virtual bool SetParams(const PhysRBParams& pParams) = 0;
	virtual bool GetParams(PhysRBParams& pParams) = 0;

	//FLy
	virtual void SetHeight(float fHeight) = 0;
	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;
	virtual float GetLiftingConstant() = 0;
	virtual void SetEngineCoeff(float f) = 0;

	
};

class IPhysJoint : public IPhysEntity
{
public:
	IPhysJoint(){};
	virtual ~IPhysJoint(){};
	virtual IPhysRigidBody * GetBody1() = 0;
	virtual IPhysRigidBody * GetBody2() = 0;
	virtual void SetData(void * pData) = 0;
	virtual void SetPosition(const CVec3& vecPosition) = 0;
	virtual void SetDirection(const CVec3& vecDirection) = 0;
	virtual BOOL IsBroken() = 0;
};


#define BONE_PREFIX "Meqbone "
#define BONE_POSTFIX "_meq"

class IPhysCharacter : public IPhysEntity
{
public:
	IPhysCharacter(){};
	virtual ~IPhysCharacter(){};

	virtual void ResetCharacter() = 0;
	virtual void Deactivate() = 0;

	virtual void SetType(int nType) = 0;
	virtual int GetType(void) = 0;
	virtual void SetActive(bool bActive) = 0;
	virtual bool GetActive() = 0;

	virtual CAABBox GetAABB() = 0;

//	virtual void* GetData() = 0;
	virtual void SetData(void * pData) = 0;

	virtual BOOL GetBoneMatrix(const char * szBoneName, CMatrix4& matBone) = 0;
	virtual BOOL SetBoneMatrix(const char * szBoneName, const CMatrix4& matBone) = 0;

	virtual void ApplyForce(const CVec3& vecForce) = 0;
	virtual void ApplyForcePoint(const CVec3& vecForce, const CVec3& vecPoint) = 0;

	//! test
	virtual void Translate(const CVec3& vecOffset) = 0;
	virtual void Rotate(const CMatrix4& vecOffset) = 0;
	virtual void Scale(float fScale) = 0;

	//! не пользоваться этими функциями без особой надобности - они работают с проходом по мапу с соответствующей скоростью
	virtual int GetBonesCount() = 0;
	virtual const char * GetBoneName(int nBoneID) = 0;

};

class IPhysSensor : public IPhysEntity
{
public:
	IPhysSensor(){};
	virtual ~IPhysSensor(){};
	virtual void SetPosition(const CVec3& vecPosition) = 0;
	virtual int GetSensorState() = 0;
	virtual void * GetSensorData() = 0;
	virtual void SetType(int nType) = 0;
	virtual int GetType() = 0;
	virtual void SetInteractionCallback(InteractionCallback interaction) = 0;
	virtual void SetData(void * pData) = 0;
};

class IPhysLib
{
public:
	virtual void Init(float fWorldScale) = 0;
	virtual void Destroy() = 0;
	virtual void Clear() = 0;
	virtual void Move(float fDeltaT) = 0;
	virtual IPhysEntity * CreatePhysEntity(const CXmlElement * pParams, bool bIsClonable) = 0;
	virtual bool DestroyPhysEntity(IPhysEntity * pObject) = 0;
	virtual void EnableInteraction(int nType1, int nType2) = 0;
	virtual void DisableInteraction(int nType1, int nType2) = 0;
	virtual void SetCore(ICore *pCore) = 0;
	virtual void SetScale(float fWorldScale) = 0;

	virtual bool CreateExplosion(const CVec3& vecPoint, const float fStrength, const float fRadius, const int nTypes) = 0;
	virtual bool CreateTriangleSplinters(const int nSplintersCount, const float * pData, const float fLifeTime, stlvector<IPhysRigidBody*>& pOut) = 0;
	virtual bool CreatePolygonSplinters(const int nIndexCount, const int * pIndexData, const int nVertexCount, const float * pVertexData, stlvector<IPhysRigidBody*>& pOut) = 0;
	virtual IPhysRigidBody* CreateTerrain(int xResolution, int yResolution, float xSize, float ySize, const float * pData) = 0;
	virtual IPhysJoint* CreateJointFromBodies(int nJointType, IPhysRigidBody* pBody1, IPhysRigidBody* pBody2) = 0;
	virtual IPhysJoint* CreateLimitFromBodies(int nJointType, IPhysRigidBody* pBody1, IPhysRigidBody* pBody2, float fValue) = 0;

	virtual int Trace(const CVec3& vecPos, const CVec3& vecDest, TraceData* out, int nQuantity, int nFlags) = 0;
	virtual int TraceExclude(const CVec3& vecPos, const CVec3& vecDest, TraceData* out, int nQuantity, int nFlags, int nNumExcludeBodies, IPhysRigidBody **pExclude) = 0;
	virtual BOOL TraceMaterial(const CVec3& vecPos, const CVec3& vecDest, TraceData& out, Engine2::String& szMaterial, int nFlags) = 0;

	virtual void SetMaterialInteractionProperties(const Engine2::String& szMaterial1, const Engine2::String& szMaterial2, float fFrictionS, float fFrictionD, float fRestitution) = 0;

	virtual bool Serialize(unsigned char* pBuffer, int& nBufferLength) = 0;
	virtual bool DeSerialize(const unsigned char* pBuffer, int nBufferLength) = 0;

	//TEST METHODS!
	virtual void SetFrameTime(float fFrameTime) = 0;
	virtual float GetFrameTime() = 0;
	virtual void SetFrameFactor(float fFrameFactor) = 0;

	virtual float GetTPS(void) = 0; //Trace per second

	virtual CVec3 getGravity() = 0;
};



class IPhysCar : public IPhysEntity
{
public:
	
	IPhysCar(){};
	virtual ~IPhysCar(){};

	virtual void onKeyDown (int key) = 0;
	virtual void onKeyUp (int key) = 0;

	virtual CVec3 GetPosition() = 0;
	virtual CMatrix4 GetRotation() = 0;
	virtual void GetCarParams(PhysCarParams& nCarParams) = 0;
	virtual void SetCarParams(const PhysCarParams& nCarParams) = 0;
	virtual void UpdateCar()=0;

	virtual CVec3 GetWheelPosition(int iIndex)=0;
	virtual CMatrix4 GetWheelRotation(int iIndex)=0;
	virtual bool HasWheelContact(int iIndex) const = 0;
	virtual float GetWheelAngularVelocity(int iIndex) const = 0;
	virtual float GetWheelMn() = 0;

	virtual CVec3 GetVelocity() = 0;
	virtual int	GetGear() = 0;
	virtual bool isContactGround() = 0;
	virtual CVec3 GetDirection() = 0;

	virtual int getCountWheelOnGroud(void) = 0;

	virtual float GetDriveMagnitude() const = 0;

	virtual void setActive(bool b) = 0;
	virtual bool getActive(void) = 0;
	virtual void setDynamic(bool b) = 0;
	virtual bool getDynamic(void) = 0;

	virtual void SetType(int nType) = 0;
	virtual int getType() = 0;

	virtual void SetData(IBody * pData) = 0;

	virtual float getMass() = 0;
	virtual void SetLimitRotation(float f) = 0 ;

	
	virtual HRESULT ApplyImpulse(const CVec3& vecImpulse) = 0;
	
	virtual void SetActiveEx(bool bActive, bool bAddRemove) = 0;

	virtual float GetRatio() = 0;

	virtual void setDynamicFriction(float f) = 0;
	virtual void setDriveConstant1(float f) = 0;

	virtual void ReSpawn() = 0;
	virtual void ReSpawn(CVec3 vecPos,CMatrix4 matRot) = 0;

	virtual void SetRotation(CMatrix4 matRot) = 0;
	virtual void SetPosition(CVec3 pos) = 0;
};


class IPhysTerrain : public IPhysEntity
{
public:


	IPhysTerrain(){};
	virtual ~IPhysTerrain(){};
	virtual HRESULT PreFrameMove(float fDeltaT) = 0;
	virtual HRESULT Move(float fDeltaT) = 0;
	virtual HRESULT PostFrameMove(float fDeltaT) = 0;

	virtual float* GetHeightMap(int& x,int& z,int& iXResolution,int& iZResolution) = 0;

	virtual void SetType(int nType) = 0;

	virtual void setActive(bool b) = 0;
	virtual void setDynamic(bool b) = 0;

};

IPhysLib * GetPhysLib(bool bReCreate = false);
bool DestroyPhysLib();


