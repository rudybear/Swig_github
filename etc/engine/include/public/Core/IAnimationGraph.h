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

// Redundant list of states. Its just simple case, obviously that could be a char * state parameter as well
// This is point for discussion, but in WOW there is not too much different states. Its easy to optimise
enum EAnimState{
  eIdle,
  eWalk,
  eRun, 
  eStance,
  eAttack,
  eCastSpell
  // etc.. All major states 

  
};


// The main and general animation structure
struct AnimState {

  //! Requested/current state
  EAnimState m_eState;

  // General movement states

  //! Approximate distance for animation
  float m_fDistance;
  //! Direction of motion ( in 3D space, normalized)
  CVec3 m_vDir;
  //! Target point
  CVec3 m_vDesiredPoint;
  //! Desired transfer speed 
  float m_fSpeed;
  //! Priority
  int m_iPriority; // Weight?
  //! Drop all from stack?
  bool m_bOverridePrevious;

    //! Additional parameters?
  // AnimState * m_pLeader; // Leader following?
  //float m_fReflectionRadius; // Path seeking? Obstacles?

};


class IAnimMeshInfo;

// Return current state 
class IAnimState {

  virtual ~IAnimState() {}
  // Set target mesh info
  virtual void SetAnimMeshInfo(IAnimMeshInfo * pInfo) = 0;
  // Add new requested state to stack
  virtual void AddAnimState(AnimState * pState) = 0;

  virtual int GetCurrentStatesNum() const = 0;

  virtual const AnimState * GetState(int ) const = 0;

};



class IAnimGraph {

  //! Load .xml graph 
  virtual bool LoadGraph(const char *) = 0;
  //! Add IAnimState to the graph trace stack
  virtual void GuideMesh(IAnimState * ) = 0;
  //! Remove IAnimState from graph
  virtual void DetachMesh(IAnimState * ) = 0;
};


struct AnimationParam;

struct DesiredAnimation {
  AnimationParam * m_pParams;
  int m_iAnimation;
};

class IAnimGraph2 {

  //! Load .xml graph 
  virtual bool LoadGraph(const char *) = 0;
  //! Add IAnimState to the graph trace stack
  virtual void GuideMesh(IAnimState * pState, Engine2::Vector<DesiredAnimation*>& result) = 0;
  //! Remove IAnimState from graph
  virtual void DetachMesh(IAnimState * ) = 0;
};
