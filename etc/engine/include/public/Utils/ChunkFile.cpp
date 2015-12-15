////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#ifndef MAX_EXPORT
#include "RenderStdAfx.h"
#include "Public/Common/Common.h"
//#endif

void RegisterAllocation(const char *, size_t size );
void RegisterDeallocation(const char *, size_t size );

#include "ChunkFile.h"


namespace Engine2
{

	CChunkFile::CChunkFile(void)
	{
	}

	CChunkFile::~CChunkFile(void)
	{
	}

	// IO routine
	bool CChunkFile::SaveChunks(const char * filename)
	{
		// final preparation

		FILE * f;

    if (Engine2::Platform::fopen_s(&f, filename, "wb") != 0)
			return false;

		Header *h = GetHeader();
		h->m_iChunksOffset = (int)m_Data.size();
		m_Data.resize(m_Data.size() + m_Chunks.size() * sizeof(ChunkInfo));
		memcpy(&m_Data[GetHeader()->m_iChunksOffset], &m_Chunks[0], m_Chunks.size() * sizeof(ChunkInfo));

		bool result = fwrite(&m_Data[0], 1, m_Data.size(), f) == m_Data.size();
		fclose(f);

		return result;
	}

	size_t CChunkFile::SaveChunks(void *data, size_t size)
	{
		Header *h = GetHeader();
		h->m_iChunksOffset = (int)m_Data.size();
		m_Data.resize(m_Data.size() + m_Chunks.size() * sizeof(ChunkInfo));
		memcpy(&m_Data[GetHeader()->m_iChunksOffset], &m_Chunks[0], m_Chunks.size() * sizeof(ChunkInfo));

		if (m_Data.size() > size) return 0;

		memcpy(data, &m_Data[0], m_Data.size());

		return m_Data.size();
	}

	bool CChunkFile::LoadChunks(const char * filename)
	{
		FILE * f;

		if (Engine2::Platform::fopen_s(&f, filename, "rb") != 0)
			return false;

		Header header;

		fread(&header, 1, sizeof(Header),f);

#ifdef WIN32
		_fseeki64(f, 0, SEEK_SET);
#else
		fseek(f, 0, SEEK_SET);
#endif

		if (strncmp(header.m_Tag, Engine2tag, 8) != 0)
			return false;

		m_Data.resize(header.m_iChunksOffset);

		fread(&m_Data[0], 1, header.m_iChunksOffset, f);

		//fseek(f, header.m_iChunksOffset, SEEK_SET);

		for (int i = 0; i < header.m_iNumChunks; ++i)
		{
			ChunkInfo chunk;
			fread(&chunk, 1, sizeof(ChunkInfo), f);
			m_Chunks.push_back(chunk);
		}

		fclose(f);
		return true;
	}

	bool CChunkFile::LoadChunks(char * buf, size_t len)
	{
		Header * pHeader = (Header *)buf;
		char * p = buf;

		if (strncmp(pHeader->m_Tag, Engine2tag, 8) != 0)
			return false;


		m_Data.resize(pHeader->m_iChunksOffset);

		memcpy(&m_Data[0], buf, pHeader->m_iChunksOffset);
		p+= pHeader->m_iChunksOffset;

    m_Chunks.resize(pHeader->m_iNumChunks);
    
    //printf("num chunks = %i chunk size = %i offset = %i size=%i", pHeader->m_iNumChunks, sizeof(ChunkInfo), pHeader->m_iChunksOffset, len);
		for (int i = 0; i < pHeader->m_iNumChunks; ++i)
		{
      memcpy(&m_Chunks[i], p, sizeof(ChunkInfo));  
			p += sizeof(ChunkInfo);     
		}
		return true;
	}


	// Chunks API
	void CChunkFile::AddChunk(int version, int type, void * pData, int size)
	{
		ChunkInfo info;
		if (m_Data.empty())
		{
			// add header
			Header header;
			memset(&header, 0, sizeof(header));
			strncpy_s(header.m_Tag,Engine2tag, 7);
			m_Data.resize(sizeof(Header));
			memcpy(&m_Data[0], &header, sizeof(Header));
		}

		info.m_iOffset = (int)m_Data.size();
		info.m_iSize = size;
		info.m_iType = type;
		info.m_iVersion = version;

		m_Data.resize(m_Data.size() + size);

		memcpy(&m_Data[info.m_iOffset], pData, size);
		GetHeader()->m_iNumChunks += 1;

		m_Chunks.push_back(info);
	}

	int CChunkFile::GetNumChunks()
	{
		return (int)m_Chunks.size();
	}

	int CChunkFile::GetChunkVersion(int i)
	{
		return m_Chunks[i].m_iVersion;
	}

	int CChunkFile::GetChunkType(int i)
	{
		return m_Chunks[i].m_iType;
	}

	int CChunkFile::GetChunkSize(int i )
	{
		return m_Chunks[i].m_iSize;

	}

	void * CChunkFile::GetChunkData(int i)
	{
		return (void*)(&m_Data[0] + m_Chunks[i].m_iOffset);
	}
}

//template<class T>
//void SimpleGet(char ** data, T& value)
//{
//  memcpy(&value, *data, sizeof(T));
//  *data += sizeof(T);
//}
//
//template<>
//void SimpleGet<stlstring>(char ** data, stlstring& value)
//{
//  short int len;
//  memcpy(&len, *data, sizeof(short int));
//  *data += sizeof(short int);
//  value.resize(len);
//  memcpy(&value[0], *data, len);
//  *data += len;
//}
//
//template<class T>
//void SimpleGetArray(char ** data, T& value)
//{
//  int cc;
//  memcpy(&cc, *data, sizeof(int));
//  *data += sizeof(int);
//  if (cc) {
//    value.resize(cc);
//    memcpy(&value[0], *data, sizeof(T::value_type) * cc);
//    *data += sizeof(T::value_type) * cc;
//  }
//}

