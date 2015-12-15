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

#include "Public/Render/pAPI.h"

using namespace PAPI;


enum eParticleType {
	eParticle_SimpleGravity,
	eParticle_SimpleAnimated,
  eParticle_Lib,
  eParticle_LibFromXML,
	eParticle_UserDefined,
};

struct ParticleAnimationParam
{
  bool loop;
};


// Just base class
class IParticleEmitter
{
protected:

    float m_fDistanceMult;
  public:

    CMatrix44 * m_pMatrix;
  	virtual eParticleType GetParticleType() const = 0;
    virtual ~IParticleEmitter() {}
    virtual void Update(float fDelta) = 0;
    virtual void DrawParticle() = 0;

    virtual void SetMaterialName(const char *) = 0;
    virtual const char * GetMaterialName() = 0;
    virtual void SetMeshMatrix(CMatrix44* pMat) 
    {
      m_pMatrix = pMat;
    }

    virtual void StartAnimation(ParticleAnimationParam& params) = 0;
    virtual void StopAnimation() = 0;

    virtual void SetVisibleState(bool) = 0;
    virtual void SetTranslation(const CVec3&) = 0;
    virtual void SetBBox(const CAABBox&) = 0;

	virtual void SetEmit(bool bEmit) {}
	virtual int GetParticleCount() const { return -1; }

    // DOESN'T WORK YET!
    void SetDistanceMultiplier(float fMult) {m_fDistanceMult = fMult; };
    float GetDistanceMultiplier() { return m_fDistanceMult; };

    // PER-EMITTER DISTANCE FACTOR FOR VISIBILITY/ INITIAL SETTINGS COMING FROM SCRIPT!
    virtual void SetVisibleDistanceMultiplier(float fDist) = 0;
    virtual float GetVisibleDistanceMultiplier() = 0;

    virtual void SetVisibleDistance(float fDist) = 0;
    virtual float GetVisibleDistance() = 0;

};




class IParticleLibEmitter; 

class IParticleUpdaterCallback {
public:
  virtual void Update(IParticleLibEmitter* context) = 0;

};


class IParticleLibEmitter : public IParticleEmitter {
public:
  virtual eParticleType GetParticleType() const {
    return eParticle_Lib;
  }
  //! 

  virtual void SetVisibleMaterialTexture(uint32 stage, const char * nexTex) = 0;
  virtual bool Create(const char * Material, IParticleUpdaterCallback*, int numParticles) = 0;
  virtual void Color(const pVec &color, const float alpha = 1.0f) = 0;
  virtual void Color(const float red, const float green, const float blue, const float alpha = 1.0f) = 0;
  virtual void Color(const pDomain &cdom) = 0;
  virtual void Color(const pDomain &cdom, ///< The color domain.
    const pDomain &adom ///< The X dimension of the alpha domain is used for alpha.
    ) = 0;
  virtual void Size(const pVec &size) = 0;
  virtual void Size(const pDomain &dom) = 0;
  virtual void Mass(const float mass) = 0;
  virtual void RotVelocity(const pVec &v) = 0;
  virtual void RotVelocity(const pDomain &dom) = 0;
  virtual void StartingAge(const float age, ///< mean starting age of particles
    const float sigma = 0.0f ///< standard deviation of particle starting age
    ) = 0;
  virtual void UpVec(const pVec &v) = 0;
  virtual void UpVec(const pDomain &dom) = 0;
  virtual void Velocity(const pVec &vel) = 0;
  virtual void Velocity(const pDomain &dom) = 0;
  virtual void VertexB(const pVec &v) = 0;
  virtual void VertexB(const pDomain &dom) = 0;
  virtual void VertexBTracks(const bool track_vertex = true) = 0;
  virtual void ResetSourceState() = 0;
  virtual void Seed(const unsigned int seed) = 0;
  virtual void TimeStep(const float new_dt) = 0;
  virtual void CallActionList(const int action_list_num) = 0;
  virtual void DeleteActionLists(const int action_list_num, ///< The handle of the first action list to delete
    const int action_list_count = 1 ///< How many action lists to delete
    ) = 0;
  virtual void EndActionList() = 0;

  virtual int GenActionLists(const int action_list_count = 1 ///< How many action lists to create
    ) = 0;
  virtual void NewActionList(const int action_list_num) = 0;
  virtual void CopyGroup(const int p_src_group_num, ///< group number of the source particle group
    const size_t index = 0, ///< index of the first particle in the source list to copy
    const size_t copy_count = P_MAXINT ///< copy at most this many particles
    ) = 0;
  virtual void CurrentGroup(const int p_group_num) = 0;
  virtual void DeleteParticleGroups(const int p_group_num, ///< handle of the first particle group to delete
    const int p_group_count = 1 ///< delete this many groups
    ) = 0;
  virtual int GenParticleGroups(const int p_group_count = 1, ///< generate this many groups
    const size_t max_particles = 0 ///< each created group can have this many particles
    ) = 0;
  virtual size_t GetGroupCount() = 0;
  virtual size_t GetMaxParticles() = 0;
  virtual size_t GetParticles(const size_t index, ///< index of the first particle to return
    const size_t count, ///< max number of particles to return
    float *position = NULL, ///< location to store 3 floats per particle for position
    float *color = NULL, ///< location to store 4 floats per particle for color and alpha
    float *vel = NULL, ///< location to store 3 floats per particle for velocity
    float *size = NULL, ///< location to store 3 floats per particle for size
    float *age = NULL ///< location to store 1 float per particle for age
    ) = 0;
  virtual size_t GetParticlePointer(float *&ptr, ///< the returned pointer to the particle data
    size_t &stride, ///< the number of floats from one particle's value to the next particle's value
    size_t &pos3Ofs, ///< the number of floats from returned ptr to the first particle's position parameter
    size_t &posB3Ofs, ///< the number of floats from returned ptr to the first particle's positionB parameter
    size_t &size3Ofs, ///< the number of floats from returned ptr to the first particle's size parameter
    size_t &vel3Ofs, ///< the number of floats from returned ptr to the first particle's velocity parameter
    size_t &velB3Ofs, ///< the number of floats from returned ptr to the first particle's velocityB parameter
    size_t &color3Ofs, ///< the number of floats from returned ptr to the first particle's color parameter
    size_t &alpha1Ofs, ///< the number of floats from returned ptr to the first particle's alpha parameter
    size_t &age1Ofs, ///< the number of floats from returned ptr to the first particle's age parameter
    size_t &up3Ofs, ///< the number of floats from returned ptr to the first particle's up parameter
    size_t &rvel3Ofs, ///< the number of floats from returned ptr to the first particle's rvel parameter
    size_t &upB3Ofs, ///< the number of floats from returned ptr to the first particle's upB parameter
    size_t &mass1Ofs, ///< the number of floats from returned ptr to the first particle's mass parameter
    size_t &data1Ofs ///< the number of floats from returned ptr to the first particle's data parameter, which is a 32-bit integer, not a float
    ) = 0;
  virtual void SetMaxParticles(const size_t max_count) = 0;
  virtual void BirthCallback(P_PARTICLE_CALLBACK callback, ///< Pointer to function of yours to call
    void *data = NULL ///< Pointer to arbitrary data of yours to pass into your function
    ) = 0;
  virtual void DeathCallback(P_PARTICLE_CALLBACK callback, ///< Pointer to function of yours to call
    void *data = NULL ///< Pointer to arbitrary data of yours to pass into your function
    ) = 0;
  virtual void SetWorkingSetSize(const int set_size_bytes) = 0;

  virtual void Avoid(float magnitude, ///< how drastically the particle velocities are modified to avoid the obstacle at each time step.
    const float epsilon, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
    const float look_ahead, ///< how far forward along the velocity vector to look for the obstacle
    const pDomain &dom ///< the space to avoid
    ) = 0;
  virtual void Bounce(float friction, ///< The tangential component of the outgoing velocity vector is scaled by (1 - friction).
    const float resilience, ///< The normal component of the outgoing velocity vector is scaled by resilience.
    const float cutoff, ///< Only apply friction if the outgoing tangential velocity is greater than cutoff. This can allow particles to glide smoothly along a surface without sticking.
    const pDomain &dom ///< Bounce off the surface of this domain.
    ) = 0;
  virtual void CopyVertexB(const bool copy_pos = true, ///< If true, sets the PositionB of each particle to the current position of that particle. This makes each particle remember this position so it can later return to it using the Restore() action.
    const bool copy_vel = false ///< If true, sets the velocityB of each particle to the current velocity of that particle. This can be useful for computing the orientation of the particle by copying a particle's velocity at the beginning of each time step. Then when drawing a particle, the cross-product velocity and velocityB yields a tangent vector.
    ) = 0;
  virtual void Damping(const pVec &damping, ///< Component-wise multiply this vector by the velocity vector
    const float vlow = 0.0f, const float vhigh = P_MAXFLOAT) = 0;
  virtual void RotDamping(const pVec &damping, ///< Component-wise multiply this vector by the rotational velocity vector
    const float vlow = 0.0f, const float vhigh = P_MAXFLOAT) = 0;
  virtual void Explosion(const pVec &center, ///< center point of shock wave
    const float radius, ///< current radius of wave peak
    const float magnitude, ///< scales the acceleration applied to particles
    const float sigma, ///< standard deviation of the gaussian; the sharpness or broadness of the strength of the wave.
    const float epsilon = P_EPS ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
    ) = 0;
  virtual void Follow(float magnitude = 1.0f, ///< scales each particle's acceleration
    const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
    const float max_radius = P_MAXFLOAT ///< defines the sphere of influence of this action. No particle further than max_radius from its predecessor is affected.
    ) = 0;
  virtual void Fountain() = 0;
  virtual void Gravitate(const float magnitude = 1.0f, ///< scales each particle's acceleration
    const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
    const float max_radius = P_MAXFLOAT ///< defines the sphere of influence of this action. No particle further than max_radius from another particle is affected.
    ) = 0;
  virtual void Gravity(const pVec &dir) = 0;
  virtual void Jet(const pDomain &dom, ///< apply jet to particles in this domain
    const pDomain &acc) = 0; ///< acceleration vector comes from this domain
  virtual void KillOld(const float age_limit,
    const bool kill_less_than = false ///< true to kill particles younger than age_limit
    ) = 0;
  virtual void MatchVelocity(const float magnitude = 1.0f, ///< scales each particle's acceleration
    const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
    const float max_radius = P_MAXFLOAT ///< defines the sphere of influence of this action. No particle further than max_radius from another particle is affected.
    ) = 0;
  virtual void MatchRotVelocity(const float magnitude = 1.0f, ///< scales each particle's acceleration
    const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
    const float max_radius = P_MAXFLOAT ///< defines the sphere of influence of this action. No particle further than max_radius from another particle is affected.
    ) = 0;
  virtual void Move(const bool move_velocity = true, ///< apply velocity to position.
    const bool move_rotational_velocity = true ///< apply rotational velocity to Up vector. This is an optimization.
    ) = 0;
  virtual void OrbitLine(const pVec &p, ///< a point on the line
    const pVec &axis, ///< any vector parallel to the line
    const float magnitude = 1.0f, ///< scales each particle's acceleration
    const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
    const float max_radius = P_MAXFLOAT ///< defines the cylinder of influence of this action. No particle further than max_radius from the line is affected.
    ) = 0;
  virtual void OrbitPoint(const pVec &center, ///< accelerate toward this point
    const float magnitude = 1.0f, ///< scales each particle's acceleration
    const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
    const float max_radius = P_MAXFLOAT ///< defines the sphere of influence of this action. No particle further than max_radius from the center is affected.
    ) = 0;
  virtual void RandomAccel(const pDomain &dom) = 0;
  virtual void RandomDisplace(const pDomain &dom) = 0;
  virtual void RandomVelocity(const pDomain &dom) = 0;
  virtual void RandomRotVelocity(const pDomain &dom) = 0;
  virtual void Restore(const float time, ///< how long more until particles should arrive at target position and orientation
    const bool vel = true, ///< restore positions
    const bool rvel = true ///< restore up vectors
    ) = 0;
  virtual void Sink(const bool kill_inside, ///< true to kill particles inside the domain
    const pDomain &dom) = 0;
  virtual void SinkVelocity(const bool kill_inside, ///< true to kill particles with velocities inside the domain
    const pDomain &dom) = 0;
  virtual void Sort(const pVec &eye,
    const pVec &look,
    const bool front_to_back = false, ///< true to sort in front-to-back order instead of back-to-front
    const bool clamp_negative = false ///< true to set negative dot product values to zero before sorting. This speeds up sorting time. Particles behind the viewer won't be visible so their relative order doesn't matter.
    ) = 0;
  virtual void Source(const float particle_rate, ///< how many particles to add per unit time
    const pDomain &dom ///< particle positions are chosen from this domain
    ) = 0;
  virtual void SourceUniform(const float particle_rate, ///< how many particles to add per unit time
	const float chaos, ///< scatters generation time of particles [0..1]
    const pDomain &dom ///< particle positions are chosen from this domain
    ) = 0;
  virtual void SpeedLimit(const float min_speed, const float max_speed = P_MAXFLOAT) = 0;
  virtual void TargetColor(const pVec &color, ///< target color
    const float alpha, ///< target alpha value
    const float scale, ///< what percent of the way from the current color to the target color to transition in unit time
    bool bAlpha=false
    ) = 0;
  virtual void TargetSize(const pVec &size, ///< target size
    const pVec &scale ///< what percent of the way from the current size to the target size to transition in unit time
    ) = 0;
  virtual void TargetVelocity(const pVec &vel, ///< target velocity
    const float scale ///< what percent of the way from the current velocity to the target velocity to transition in unit time
    ) = 0;
  virtual void TargetRotVelocity(const pVec &rvel, ///< rotational velocity
    const float scale ///< what percent of the way from the current rotational velocity to the target rotational velocity to transition in unit time
    ) = 0;
  virtual void Vertex(const pVec &v, ///< position of particle to create
    long data = 0 ///< application data to be passed to the birth and death callbacks
    ) = 0;
  virtual void Vortex(
    const pVec &center, ///< tip of the vortex
    const pVec &axis, ///< the ray along the center of the vortex
    const float tightnessExponent, ///< like a Phong exponent that gives a curve to the vortex silhouette; 1.0 is a cone; greater than 1.0 curves inward.
    const float max_radius, ///< defines the radius at the top of the vortex and the infinite cylinder of influence. No particle further than max_radius from the axis is affected.
    const float inSpeed, ///< inward acceleration of particles OUTSIDE the vortex
    const float upSpeed, ///< vertical acceleration of particles INSIDE the vortex. Can be negative to apply gravity.
    const float aroundSpeed ///< acceleration around vortex of particles INSIDE the vortex.
    ) = 0;

	virtual float GetUpdateTime() = 0;

};

class ISimpleGravityParticeEmitter : public IParticleEmitter {
  public:
	  virtual eParticleType GetParticleType() const {
  		return eParticle_SimpleGravity;
  	}
    virtual void Create(TEXNUM texID, int maxParticles, int particlesPerSec, float lifeSpan, const CVec3 &v0, float angle, float size) = 0;
};



class IAnimatedParticleEmitter : public IParticleEmitter {
public:
	virtual eParticleType GetParticleType() const {
		return eParticle_SimpleAnimated;
	}

  virtual bool LoadAnimation(const char * name) = 0;
  virtual bool Create(const char *material, const char *texture) = 0;
};


class IParticleXMLEmitter : public IParticleEmitter
{
public:
  virtual eParticleType GetParticleType() const {
    return eParticle_LibFromXML;
  }
  virtual bool Load(const char * name) = 0;
  virtual bool Load(CXmlElement& ) = 0;
};


//! It's not an emitter. It's particles container!!!
class IParticleMeshInfo : public IMeshInfo 
{
public:
	virtual size_t GetEmittersCount() const = 0;
	virtual IParticleEmitter * GetEmitter(size_t num) const = 0;
	virtual int AddEmitter(IParticleEmitter * ) = 0; // For custom type
	virtual void DeleteEmitter(IParticleEmitter * ) = 0;
};

enum eEffectPartEvent {
  eEffectPart_Started,
  eEffectPart_Ended,
  // insert new here
  eEffectPart_Last
};

class IEffectEventListener {
public:
  virtual void EventHappens(const char * effectPart, eEffectPartEvent event) = 0;
};

class IEffectMeshInfo : public IMeshInfo {
public:
  virtual bool Load(const char * name) = 0;
  virtual bool Load(CXmlElement& ) = 0;

  virtual void RegisterListener(IEffectEventListener * ) = 0;
  virtual void UnRegisterListener(IEffectEventListener * ) = 0;

  virtual bool StartEffect() = 0;
  virtual bool StopEffect() = 0;

  // clamped from 0 to 1
  virtual void SetDistanceMultiplier(float fMult) = 0;
  virtual float GetDistanceMultiplier(float fMult) = 0;

  virtual void SetVisibleDistanceMultiplier(float fDist) = 0;
  virtual float GetVisibleDistanceMultiplier() = 0;

  virtual int GetEmittersCount() = 0;
  virtual IParticleEmitter * GetEmitter(int) = 0;
};
