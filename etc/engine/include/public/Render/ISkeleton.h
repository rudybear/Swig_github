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

#include "Public/Common/Mathlib.h"

// Interface for Skeleton
class IMeshInfo;


struct CJoint
{
public:
  CJoint(void) : m_iParent(-1), m_iVisible(1)	{	}

public:
  CQuatT m_AbsJointNoRoot;
  CQuatT m_AbsJoint;
  CQuatT m_RelJoint;
	int			m_iParent: 31;
	int			m_iVisible: 1;
};

// For storing default data
struct CExtendedJoint : public CJoint
{
  uint32 m_crcName;
  char   n_sName[32]; 
  CQuatT m_AbsInvJoint;
};

//! Matrix joint info with non-uniform scale
struct CMatrixJoint {
  CMatrix44 m_AbsJoint;
  CMatrix44 m_RelJoint;
  int			m_iParent;
  float m_Visibility;
};

//! Extended joint info with non-uniform scale
struct CExtendedMatrixJoint : public CMatrixJoint
{
  char   n_sName[32]; 
  CMatrix44 m_AbsInvJoint;
  CVec3  m_reScale;
};

// Give access to the base transformations
class IBaseSkeleton {
public:
  virtual ~IBaseSkeleton() {}

  virtual size_t GetExtendedJointNum() const = 0;
  virtual const CExtendedJoint* GetExtendedJoint(size_t num) const = 0;
  virtual const CExtendedMatrixJoint* GetExtendedMatrixJoint(size_t num) const = 0;
};


class ISkeleton
{
public:
    virtual ~ISkeleton() {};
	// Get the number of bones
	virtual uint32 GetNumBones() = 0;

	// Get id for desired bone by name
	virtual uint32 GetBoneIDFromName(const char *) = 0;

	// Get id for desired bone by ID
	virtual const char * GetBoneNameFromID(uint32) = 0;

	// Get  absolute matrix by ID
	virtual const CQuatT *  GetBoneAbsMatrix(uint32) = 0;

	// Get the relative matrix by ID
	virtual const CQuatT *  GetBoneRelMatrix(uint32) = 0;

	// Get the absolute matrix in default pose by ID
	virtual const CQuatT *  GetBoneDefaultMatrix(uint32) = 0;

  virtual const CJoint *GetJoint(uint32 num) = 0;

	// Add attachment 
	virtual void AddAttachment(IMeshInfo * pObject, uint32, CMatrix44& initTM) = 0;
	virtual void RemoveAttachment(IMeshInfo * pObject) = 0;


  // Get  absolute matrix by ID
  virtual const CMatrix44 *  GetBoneAbsMatrixAsMatrix(uint32) = 0;

  // Get the relative matrix by ID
  virtual const CMatrix44 *  GetBoneRelMatrixAsMatrix(uint32) = 0;

  // Get the absolute matrix in default pose by ID
  virtual const CMatrix44 *  GetBoneDefaultMatrixAsMatrix(uint32) = 0;


};

