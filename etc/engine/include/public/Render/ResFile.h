////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __RESFILE_H__
#define __RESFILE_H__

#include "Public/Common/STLAllocator.h"
#include "Public/Common/OurTypes.h"
#include "Public/Common/Vector.h"
#include "Public/Core/IVFSFileManager.h"
#include "NameCRC.h"
#include "MemFile.h"
#include <map>

#define IDRESHEADER		(('K'<<24)+('C'<<16)+('P'<<8)+'D')
#define RESVERSION_LZSS  4 // LZSS
#define RESVERSION_LZMA  5 // LZMA

//#define RES_LZMA 1


// Resource file flags
#define RF_NOTSAVED 1
#define RF_COMPRESS 2
#define RF_TEMPDATA 4
#define RF_COMPRESSED 8

// Resource header
struct SFileResHeader
{
  uint32 m_Magic;
  uint32  m_nVersion;
  uint32 m_nNumFiles;
  uint32 m_nOfsDir;
};

// File entry descriptor in the resource (12 bytes)
struct SFileDirEntry
{
  uint32 m_nSize;
  uint16 m_nFlags;     // RF_
  int32 m_nOffset;
  CNameCRC m_cName;
  SFileDirEntry()
  {
    m_nSize = 0;
    m_nFlags = 0;
    m_nOffset = 0;
  }
};

typedef std::map<CNameCRC, void *> TFileFlushData;
typedef TFileFlushData::iterator TFileFlushDataItor;

typedef std::vector<SFileDirEntry> TFileDir;
typedef TFileDir::iterator TFileDirItor;

// Resource access types
#define RA_READ   1
#define RA_WRITE  2
#define RA_CREATE 4
#define RA_ENDIANS 8

class CResFile
{
private:
  stlstring m_szName;
  FILE *m_Handle;
  SMemFile m_MemFile;
  TFileDir m_Dir;
  TFileFlushData m_FlushData;
  int m_nResSize;
  int m_nTypeAccess;
  size_t m_nOffsDir;
  bool m_bDirty;
  stlstring m_szError;
  int m_nVersion;
  IVFSFileManager *m_pFM;

  size_t FRead (void* pDest, size_t nSize, size_t nCount) {
    if (m_Handle)
      return fread(pDest, nSize, nCount, m_Handle);
    else
      return m_MemFile.FRead(pDest, nSize, nCount);
  }
  size_t FSeek (size_t nOffset, int nMode) {
    if (m_Handle)
      return fseek(m_Handle, (long)nOffset, nMode);
    else
      return m_MemFile.FSeek(nOffset, nMode);
  }
public:
  CResFile(const char* name, IVFSFileManager *pFM=NULL);
  ~CResFile();

  const char* GetError(void);
  void SetError(const char *er, ...);
  const char *GetFileName() { return m_szName.c_str(); }
  int GetVersion() { return m_nVersion; }

  bool Open(int nType);
  bool Close();
  int Flush();
  int FlushDir(size_t nSeek);

  int GetNumFiles() { return (int)m_Dir.size(); }

  void *FileReadCompressed(SFileDirEntry *de, uint32& nSizeDecomp, uint32& nSizeComp);

  int FileAdd(SFileDirEntry* de, void* data);

  void* FileRead(SFileDirEntry *de, uint32& nSizeDecomp, uint32& nSizeComp);
  void* FileRead(CNameCRC name, uint32& nSizeDecomp, uint32& nSizeComp);

  int FileLength(SFileDirEntry *de);
  int FileLength(CNameCRC name);

  bool IsDirty() { return m_bDirty; }

  bool FileExist(CNameCRC name);

  SFileDirEntry *GetEntry(CNameCRC name);
  std::vector<SFileDirEntry> *GetDirectory();

  FILE *GetHandle() { return m_Handle; }
  int GetResourceSize();
};

#endif //  __RESFILE_H__
