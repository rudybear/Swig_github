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

#include "Public/Common/Common.h"
#include "Public/Common/Strings.h"
#include "Public/Common/Autoref.h"

class CFileInfo : public CRefSmartPtr
{
	friend class CVFSFileManager;
public:
	CFileInfo()
	{
		clear();
	};
	~CFileInfo(){};
 
	const char *GetFileName(void)
	{
		if(!m_bInitialized)
			return NULL;
		return m_szFileName.c_str();
	}
	const char *GetRelFileName(void)
	{
		if(!m_bInitialized)
			return NULL;
		return m_szRelFileName.c_str();
	}

	const char *GetFullFileName(void)
	{
		if(!m_bInitialized)
			return NULL;
		return m_szFullFileName.c_str();
	}

	BOOL IsFolder(void)
	{
		return m_bIsFolder;
	}
	void clear(void)
	{
		m_bInitialized = FALSE;
		m_bIsFolder = FALSE;
	}

  int64 GetModificationTime() const
  {
    return m_iModificationTime;
  }
private:

public:
	Engine2::String m_szFileName;
	Engine2::String m_szRelFileName;
	Engine2::String m_szFullFileName;
  int64 m_iModificationTime;
	BOOL m_bInitialized;
	BOOL m_bIsFolder;
};


typedef Engine2::Vector<CFileInfo *> FileInfosList;


class IReadFileStream : public CRefSmartPtr
{
public:
  virtual size_t Size() = 0;
  virtual int Seek(int offset, int origin) = 0;
  virtual int Read(char * buf, int count) = 0;
protected:
	virtual ~IReadFileStream(){};
};

class IVFSFileManager;

class IFSObject : public CRefSmartPtr
{
public:
	virtual ~IFSObject(){};
	virtual size_t FindFile(FileInfosList *pListToFill,const char* szFileSearchMask,const char *szFolderName) = 0;
	virtual BOOL GetReadFileStream(const char* szFileName, IReadFileStream *&pStream) = 0;
	virtual size_t GetFileData(const char* szFileName, char *&szBuffer, IVFSFileManager * pManager) = 0;
	virtual CFileInfo *GetFileInfo(const char* szFileName) = 0;
	virtual const char * GetName() = 0;
  // Not optimal. Need to refactor!!!
  virtual size_t GetFileSize(const char * szFileName) = 0;
  // szBuffer should be allocated!!!
  virtual size_t GetFileDataWithOffset(const char * szFileName, char *szBuffer, size_t offset, size_t count ) = 0;
  virtual const char *GetWorkingFolder() { return ""; }

  // Free buffer and return true if processed!
  virtual bool FreeMemoryBuffer(char *) { return false; }
};