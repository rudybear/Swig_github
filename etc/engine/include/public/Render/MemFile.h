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

struct SMemFile
{
  SMemFile() {
    m_pFileData = NULL;
    m_nCurSeek = 0;
    m_nSize = 0;
  }
  ~SMemFile() {
    Destruct();
  }

  // this object must be constructed before usage
  void Construct(char* pFileData, size_t nSize) {
    m_pFileData = pFileData;
    m_nSize = nSize;
    m_nCurSeek = 0;
  }

  // this object needs to be freed manually when the CryPak shuts down..
  void Destruct() {
    m_pFileData = NULL;
  }

  char* GetFile() { return m_pFileData; }

  size_t FTell() { return m_nCurSeek;}

  size_t GetFileSize() { return m_nSize; }

  size_t FSeek (size_t nOffset, int nMode) {
    if (!m_pFileData)
      return -1;

    switch (nMode)
    {
    case SEEK_SET:
      m_nCurSeek = nOffset;
      break;
    case SEEK_CUR:
      m_nCurSeek += nOffset;
      break;
    case SEEK_END:
      m_nCurSeek = GetFileSize() - nOffset;
      break;
    default:
      assert(0);
      return -1;
    }
    return 0;
  }

  size_t FRead (void* pDest, size_t nSize, size_t nCount) {
    if (!GetFile())
      return 0;

    size_t nTotal = nSize * nCount;
    if (!nTotal || m_nCurSeek >= GetFileSize())
      return 0;

    if (nTotal + m_nCurSeek > GetFileSize())
    {
      nTotal = GetFileSize() - m_nCurSeek;
      if (nTotal < nSize)
        return 0;
      nTotal -= nTotal % nSize;
    }

    char *pSrc = m_pFileData;
    if (!pSrc)
      return 0;
    pSrc += m_nCurSeek;

    memcpy(pDest, pSrc, nTotal);
    m_nCurSeek += nTotal;

    return nTotal / nSize;
  }
  size_t FEof() {
    return m_nCurSeek >= GetFileSize();
  }

protected:
  size_t m_nCurSeek;
  char *m_pFileData;
  size_t m_nSize;
};
