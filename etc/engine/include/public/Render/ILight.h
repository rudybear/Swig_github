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

#define LIGHT_POINT          1
#define LIGHT_SPOT           2
#define LIGHT_DIRECTIONAL    3
#define LIGHT_PROJECTION	 4
#define LIGHT_SHADOW		 0x8	
#define LIGHT_AMBIENT		 0x10	

struct CVec3;

class IShadowFrustrum
{
	friend class CLight;
protected:
	IShadowFrustrum() {}
	~IShadowFrustrum() {}
public:
	virtual int GetShadowMap() const = 0;

	virtual int GetShadowMapSize() const = 0;

	virtual void SetViewProjMatrices(const CMatrix44& mxView, const CMatrix44& mxProj) = 0;
  virtual void SetNearFar(float fNear, float fFar) = 0;
  virtual void GetNearFar(float& fNear, float& fFar) = 0;

  virtual void SetBiasScale(float fBiasScale) = 0;

	virtual const CMatrix44 & GetViewMatrix(void) const = 0;
	virtual const CMatrix44 & GetProjMatrix(void) const = 0;
	virtual const CMatrix44 & GetViewProjMatrix(void) const = 0;

	virtual class ILight* GetParent(void) = 0;
};

class ILight
{
protected:
	ILight(void){};
	virtual ~ILight(void){};
public:

	virtual void InitLight( int ltType, float x, float y, float z ) = 0;

	virtual void SetPos(const CVec3 &vecPos) = 0;
	virtual void SetDirection(const CVec3 &vecDirection) = 0;
	virtual void SetType(int nType) = 0;

	virtual void SetAmbient(CVec3 &vecColor) = 0;
	virtual void SetAmbient(float r,float g,float b) = 0;

	virtual void SetSpecular(CVec3 &vecColor) = 0;
	virtual void SetSpecular(float r,float g,float b) = 0;

	virtual void SetDiffuse(CVec3 &vecColor) = 0;
	virtual void SetDiffuse(float r,float g,float b) = 0;

	virtual void SetRange(float fRange) = 0;

	virtual void SetTheta(float f) = 0;
	virtual void SetPhi(float f) = 0;
	virtual void SetFalloff(float f) = 0;

	virtual float GetRange() const = 0;
	virtual float GetTheta() = 0;
	virtual float GetPhi() const = 0;
	virtual float GetFalloff() = 0;

	virtual void SetAttenuationAll(float fAttenuation0,float fAttenuation1,float fAttenuation2) = 0;

	virtual const CVec3& GetPos() const = 0;
	virtual const CVec3& GetDirection() const = 0;

	virtual int GetType() const  = 0;

	virtual void GetAmbient(CVec3 &vecColor) = 0;
	virtual void GetAmbient(float& r,float& g,float& b) = 0;

	virtual void GetSpecular(CVec3 &vecColor) const = 0;
	virtual void GetSpecular(float& r,float& g,float& b) const = 0;

	virtual void GetDiffuse(CVec4 &vecColor) const = 0;
	virtual void GetDiffuse(float& r,float& g,float& b) const = 0;

	virtual void GetRange(float& fRange) const = 0;

	virtual void GetTheta(float& f) = 0;
	virtual void GetPhi(float& f) const = 0;
	virtual void GetFalloff(float& f) = 0;

	virtual void GetAttenuationAll(float& fAttenuation0,float& fAttenuation1,float& fAttenuation2) = 0;

	virtual int GetTexture() const = 0;
	virtual void SetTexture(int) = 0;

	virtual void Update() = 0;

	virtual float GetShadowsFadeDistance(void) const = 0;
	virtual void SetShadowsFadeDistance(float f) = 0;

	virtual void SetNumShadowmapCascades(int nCascades) = 0;
	virtual void SetShadowmapSize(int nSize) = 0;

  virtual void CastShadowsState(bool bEnableShadow) = 0; // works only if LIGHT_SHADOW is set
	virtual bool GetMakeShadow() const = 0;

	virtual IShadowFrustrum* AddShadowFrustrum(bool bVariance=false) = 0;
	virtual size_t GetNumShadowFrustrums() const = 0;
	virtual IShadowFrustrum* GetShadowFrustrum(int nFrustrum) const = 0;
	virtual void RemoveShadowFrustrum(int nFrustrum) = 0;

	virtual void SetCurrentFrustrum(int nFrustrum) = 0;
	virtual IShadowFrustrum* GetCurrentFrustrum() = 0;

  virtual void SetVisibility(bool) = 0;
  virtual bool GetVisibility() = 0;

	// returns the light intensity by object's world position
	virtual float GetRelativeIntesity(const CVec3& rObjPos) const = 0;

  virtual void AddFlare(const char *szTexName, float fSize, float fPos, uint32 nColor=-1) = 0;
  virtual void ResetFlares() = 0;
};
