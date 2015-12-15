////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _IWEATHER
#define _IWEATHER

#pragma once

// Interface for the weather system. 

class ISun;
class IAtmosphere;
class IWind;
class IOcean;

// Various Atmosphere parameters.
typedef enum {
	eAtmBetaRayMultiplier,
	eAtmBetaMieMultiplier,
	eAtmInscatteringMultiplier,
	eAtmExtinctionMultiplier,
	eAtmHGg,
} EAtmosphereParams;

class IWeather
{
public:
	virtual ~IWeather() {};

	virtual ISun * GetSun() = 0;
	virtual IAtmosphere * GetAtmosphere() = 0;
	virtual IWind * GetWind() = 0;
  virtual IOcean * GetOcean() = 0;
	
	virtual void  SetSSAOAmount(const float fAmount) = 0;
	virtual float GetSSAOAmount() const = 0;
};

class ISun
{
public:
	virtual CVec3 GetDirection() = 0;
	virtual CVec3 GetPosition() = 0;
	virtual float GetIntensity() = 0;
	virtual CVec4 GetColor() = 0;
	virtual CVec4 GetColorAndIntensity() = 0;
	virtual CVec4 GetColorWithIntensity() = 0;

  virtual const CMatrix44& GetLMMatrix() = 0;
  virtual void SetLMMatrix(const CMatrix44& mxLM) = 0;

	virtual void SetSunIntensity(float fIntensity) = 0;
	virtual void SetSunThetaPhi(float fTheta, float fPhi) = 0;
  virtual float GetSunTheta() = 0;
	virtual float GetSunPhi() = 0;

	virtual void SetLight(class ILight *pSun) = 0;
	virtual class ILight * GetLight() = 0;

protected:
	virtual ~ISun() {};
};

class IAtmosphere
{
public:
	virtual void SetParam(EAtmosphereParams param, float fValue) = 0;
	virtual float GetParam(EAtmosphereParams param) = 0;

	virtual CVec3 GetBetaRayleigh() = 0;
	virtual CVec3 GetBetaDashRayleigh() = 0;

	virtual CVec3 GetBetaMie() = 0;
	virtual CVec3 GetBetaDashMie() = 0;

protected:
	virtual  ~IAtmosphere()  {};
};

class IWind
{
public:
	virtual CVec3 GetDirection() = 0;
	virtual float GetSpeed() = 0;
	virtual void SetDirection(CVec3& v) = 0;
	virtual void SetSpeed(float f) = 0;

protected:
	virtual ~IWind() {};
};

class IOcean
{
public:
  virtual float GetWaveDirection() = 0;
  virtual float GetWavesSpeed() = 0;
  virtual float GetWavesSize() = 0;
  virtual float GetWavesAmount() = 0;
  virtual float GetLevel() = 0;
  virtual const CVec4& GetFogColor() = 0;
  virtual void SetWaveDirection(float f) = 0;
  virtual void SetWavesSpeed(float f) = 0;
  virtual void SetWavesSize(float f) = 0;
  virtual void SetWavesAmount(float f) = 0;
  virtual void SetLevel(float f) = 0;
  virtual void SetFogColor(const CVec4& fogColor) = 0;
  virtual const char *GetMaterialName() = 0;
  virtual void SetMaterialName(const char *szMatName) = 0;
  virtual void SetReflectionTexName(const char *szTexName) = 0;
  virtual const char *GetReflectionTexName() = 0;

protected:
  virtual ~IOcean() {};
};

#endif