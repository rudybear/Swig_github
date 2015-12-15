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

struct SZipDirFileHeader;


class CFileManager
{
private:
	enum EDecompressionBufferSize
	{
		DECOMP_BUF_SIZE = 16384
	};

	typedef stdext::hash_map<stlstring,  SZipDirFileHeader*, string_hash_compare> IndexMap;

	unsigned char* m_pucArchive;

	unsigned int m_uiSizeOfArchive;

	IndexMap m_colArchiveIndex;
	bool ReadDirectory();
	bool FindDirectoryHeader( unsigned char*& pucDirHeader ) const;

	HANDLE m_hFile;

public:

	typedef std::list< stlstring > ArchiveList;

	CFileManager(void);
	~CFileManager(void);

	BOOL LoadFromArchive(const stlstring& strPathName);


	void GetArchiveList( ArchiveList& kArchiveList ) const;
	BOOL DecompressFile( const stlstring& strPathName, 
		stlvector< unsigned char >& colUncompressedData ) const;




};

