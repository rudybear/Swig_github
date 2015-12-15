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

// flags applicable to the IStats (retrieved via getFlags() method)
//
enum EStatsFlags
{
	// if this flag is set, during getStats(), the subsystem must count all the objects
	// it uses in the other subsystems also
	CSF_RecurseSubsystems = 1 << 0,

	CSF_Reserved1 = 1 << 1,
	CSF_Reserved2 = 1 << 2
};


enum EStatsType
{
  eST_Unknown,
  eST_BatchesGPU,
  eST_BatchesCPU,
  eST_Max
};

enum EStatsAlign
{
  eSA_Left,
  eSA_Right,
  eSA_Center,
  eSA_Under,
};

//////////////////////////////////////////////////////////////////////////
// interface IStats
// USAGE
//
//   void X::getStats (IStats* pStats)
//   {
//     STATS_SECTION_NAME(pStats, X);
//     if (!pStats->AddObject (this))
//       return;
//     pStats->AddStat (this, "Stats 1", 21);
//     pSizer->AddStat (this, "Stats 2", 15.4f);
//     m_pSubobject->getStats (pStats);
//   }
//
//   The Add* functions return bool. If they return true, then the object has been added
//   to the set for the first time, and you should go on recursively adding all its children.
//   If it returns false, then you can spare time and rather not go on into recursion;
//   however it doesn't reflect on the results: an object that's added more than once is
//   counted only once.
//
class IStats
{
public:
	// this class is used to push/pop the name to/from the stack automatically
	// (to exclude stack overruns or underruns at runtime)
	friend class CStatsSectionNameHelper;

	virtual void Release() = 0;

  virtual EStatsType GetType() = 0;
  virtual bool IsNeedUpdate() = 0;
  virtual void Clear() = 0;

	// adds an object identified by the unique pointer (it needs not be
	// the actual object position in the memory, though it would be nice,
	// but it must be unique throughout the system and unchanging for this object)
	// nCount parameter is only used for counting number of objects, it doesnt affect the size of the object.
	// RETURNS: true if the object has actually been added (for the first time)
	//          and calculated
	virtual bool AddObject(const char *szName,...) = 0;
  virtual void PushSection(EStatsAlign eAlign, float fSize, uint32 nColor, const char *szName) = 0;


	// returns the flags
	unsigned GetFlags() const { return m_nFlags; }

protected:

	unsigned m_nFlags;
};

