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


class CFile;

class CGeneralFSObject : public IFSObject
{
public:
	CGeneralFSObject(void);
	virtual ~CGeneralFSObject(void);

	//overrided IFSObject methods
	virtual size_t FindFile(FileInfosList *pListToFill,const char* szFileSearchMask,const char *szFolderName);
	virtual BOOL GetReadFileStream(const char* szFileName, IReadFileStream*& pStream);
	virtual size_t GetFileData(const char* szFileName, char *&szBuffer, IVFSFileManager * pManager);
	virtual CFileInfo *GetFileInfo(const char* szFileName);
	virtual const char * GetName() { return "CGeneralFSObject"; }
  // Not optimal. Need to refactor!!!
  virtual size_t GetFileSize(const char * szFileName);
  // szBuffer should be allocated!!!
  virtual size_t GetFileDataWithOffset(const char * szFileName, char *szBuffer, size_t offset, size_t count );
  virtual const char *GetWorkingFolder() { return m_szWorkingFolder; }

public:
	//own methods
	void Init(const char *szWorkingFolder);
private:
	Engine2::String CutToRelativeFileName(const char *szFullFileName,const char* szCutPath);
	Engine2::String CutToFileName(const char *szFullFileName);

  CFile * OpenReadFile(const char * name);


private:

	BOOL m_bInitialized;
  Engine2::String m_szWorkingFolder;
  Engine2::String m_szExeFolder;
};
