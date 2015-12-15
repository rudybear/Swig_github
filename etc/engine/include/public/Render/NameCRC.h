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

//////////////////////////////////////////////////////////////////////////
// CNameCRC
//////////////////////////////////////////////////////////////////////////
#include <assert.h>
#include "Public/Common/OurTypes.h"
#include "Public/Core/Crc32.h"

#ifndef stlstring
#include <string>
#endif

class	CNameCRC
{
public:
  CNameCRC();
  CNameCRC(const CNameCRC& n);
  CNameCRC(const char *s);
  ~CNameCRC() { m_nID = 0; }

  CNameCRC& operator=(const CNameCRC& n);
  CNameCRC& operator=(const char *s);

  bool	operator==(const CNameCRC &n) const;
  bool	operator!=(const CNameCRC &n) const;

  bool	operator==(const char *s) const;
  bool	operator!=(const char *s) const;

  bool	operator<(const CNameCRC &n) const;
  bool	operator>(const CNameCRC &n) const;

  bool	isEmpty() const { return m_nID == 0;}
  void	reset()	{	m_nID = 0; }

private:

  uint32 m_nID;
};

inline CNameCRC::CNameCRC()
{
  m_nID = 0;
}

//////////////////////////////////////////////////////////////////////////
inline CNameCRC::CNameCRC(const CNameCRC& n)
{
  m_nID = n.m_nID;
}

//////////////////////////////////////////////////////////////////////////
inline CNameCRC::CNameCRC(const char *s)
{
  m_nID = 0;
  *this = s;
}

//////////////////////////////////////////////////////////////////////////
inline CNameCRC&	CNameCRC::operator=(const CNameCRC &n)
{
  m_nID = n.m_nID;
  return *this;
}

//////////////////////////////////////////////////////////////////////////
inline CNameCRC&	CNameCRC::operator=(const char *s)
{
  assert(s);
  if (*s) // if not empty
  {
    Crc32Gen Gen;
    m_nID = Gen.GetCRC32Lowercase(s);
  }
  return *this;
}


//////////////////////////////////////////////////////////////////////////
inline bool	CNameCRC::operator==(const CNameCRC &n) const {
  return m_nID == n.m_nID;
}

inline bool	CNameCRC::operator!=(const CNameCRC &n) const {
  return !(*this == n);
}

inline bool	CNameCRC::operator==(const char* str) const
{
  assert(str);
  if (*str) // if not empty
  {
    Crc32Gen Gen;
    uint32 nID = Gen.GetCRC32Lowercase(str);
    return m_nID == nID;
  }
  return m_nID == 0;
}

inline bool	CNameCRC::operator!=(const char* str) const {
  if (!m_nID)
    return true;
  if (*str) // if not empty
  {
    Crc32Gen Gen;
    uint32 nID = Gen.GetCRC32Lowercase(str);
    return m_nID != nID;
  }
  return false;
}

inline bool	CNameCRC::operator<(const CNameCRC &n) const {
  return m_nID < n.m_nID;
}

inline bool	CNameCRC::operator>(const CNameCRC &n) const {
  return m_nID > n.m_nID;
}


#ifdef stlstring
inline bool	operator==(const stlstring &s,const CNameCRC &n) {
  return n == s.c_str();
}
inline bool	operator!=(const stlstring &s,const CNameCRC &n) {
  return n != s.c_str();
}
#else
inline bool	operator==(const std::string &s,const CNameCRC &n) {
  return n == s.c_str();
}
inline bool	operator!=(const std::string &s,const CNameCRC &n) {
  return n != s.c_str();
}
#endif

inline bool	operator==(const char *s,const CNameCRC &n) {
  return n == s;
}
inline bool	operator!=(const char *s,const CNameCRC &n) {
  return n != s;
}
