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

#include "Public/Core/IFSObject.h"

  /*! \addtogroup Engine_related
  *@{
   */

class IVFSFileManager
{
public:
	IVFSFileManager(){};
	virtual ~IVFSFileManager(void) {}
	virtual void AddFSObject(IFSObject *pObject) = 0;

	virtual void DeleteFSObject(IFSObject *pObject) = 0;
	virtual void SetPriority(IFSObject *pObject, int place) = 0;
	virtual uint32 GetFSObjectsCount() = 0; 
	virtual IFSObject * GetFSObject(int num) = 0;


  virtual size_t GetFileSize(const char * szFileName) = 0;
  // szBuffer should be allocated!!!
  virtual size_t GetFileDataWithOffset(const char * szFileName, char *szBuffer, size_t offset, size_t count ) = 0;
	virtual BOOL GetReadFileStream(const char * szFileName, IReadFileStream *&pStream,BOOL bUnused = FALSE) = 0;
	virtual size_t GetFileData(const char * szFileName, char *&szBuffer,BOOL bUnused = FALSE) = 0;
	virtual BOOL CloseReadFileStream( IReadFileStream *pStream) = 0;
	virtual CFileInfo *GetFileInfo(const char *szFileName) = 0;
	virtual FileInfosList *FindFile(const char* szFileSearchMask,const char *szFolderName = NULL) = 0;
  virtual void AllocateTextBuffer(char *&szTextBuffer, size_t) = 0;
	virtual void ClearTextBuffer(char *&szTextBuffer) = 0;
	virtual void ClearFoundFiles(void) = 0;
  virtual const char* GetWorkingFolder(void) = 0;
};

