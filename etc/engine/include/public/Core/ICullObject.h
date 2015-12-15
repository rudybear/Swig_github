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
//#include <tchar.h>
#include "Public/Common/Autoref.h"
#include "Public/Render/RenderCommon.h"
#include "Public/Common/Strings.h"
#include "IStreaming.h"
#include "CoreEnums.h"

class CLightArray;
class IPostProcessingEffect;
class CParam;
class CXmlElement;
class IMeshInfo;

class IStreamedResource;

class StreamCompleteNotifier {
public:
  virtual void StreamIsComplete(IStreamedResource * pSource, eAsyncState state) = 0;
};


class IStreamedStated {
public:
  virtual eAsyncState GetState() {
    return eReady;
  }

};


struct UserDefinedInfo {

  struct UserInfoDataHeader{
    int m_iChunksCount;
  };

  UserDefinedInfo() : m_pData(0), m_iSize(0) {}

  ~UserDefinedInfo() {
    ClearData();
  }

  static const int ChunkNameLength = 10;

  struct UserInfoDataChunk{
    char m_strChunk[ChunkNameLength]; // Chunk type
    int m_iChunkSize;  // Chunk size
  };


  void AddUserInfo(const char name[ChunkNameLength], size_t size, const void * pData) {
    size_t oldSize = 0;
    if (m_pData) {
      oldSize = m_iSize;
      m_pData = (char*)realloc(m_pData, oldSize + sizeof(UserInfoDataChunk) + size);
      m_iSize = oldSize + sizeof(UserInfoDataChunk) + size;
    } else {
      m_pData = (char*)malloc(sizeof(UserInfoDataChunk) + sizeof(UserInfoDataHeader) + size);
      oldSize += sizeof(UserInfoDataHeader);
      ((UserInfoDataHeader*)(m_pData))->m_iChunksCount = 0;
      m_iSize = sizeof(UserInfoDataChunk) + sizeof(UserInfoDataHeader) + size;
    }

    UserInfoDataChunk newChunk;
    strncpy(newChunk.m_strChunk, name, ChunkNameLength);
	newChunk.m_iChunkSize = (int)size;
    memcpy(m_pData + oldSize, &newChunk, sizeof(UserInfoDataChunk));
    memcpy(m_pData + oldSize + sizeof(UserInfoDataChunk), pData, size);

    ((UserInfoDataHeader*)(m_pData))->m_iChunksCount++;
  }

  int GetUserInfoChuncksCount() const {
    return m_pData ? ((UserInfoDataHeader*)m_pData)->m_iChunksCount : 0;
  }

  const void * GetChunk(const int num) const {
    char * pOffset = 0;
    if (num < GetUserInfoChuncksCount()) {

      pOffset = m_pData + sizeof(UserInfoDataHeader);
      size_t newSize = 0;
      for (int i = 0 ; i <= num; ++i) {
        pOffset += newSize;
        newSize = UnalignedRead<int>(&((UserInfoDataChunk*)pOffset)->m_iChunkSize) +  sizeof(UserInfoDataChunk);
      }
    }

    return pOffset + sizeof(UserInfoDataChunk);
  }

  template<class T>
  static T UnalignedRead(const void* address)
  {
#ifdef EMSCRIPTEN
	  T result;
	  memcpy(&result, address, sizeof(result));
	  return result;
#else
	  return *((T*)address);
#endif
  }

  const char * GetChunkName(const int num) const {
    char * pOffset = 0;
    if (num < GetUserInfoChuncksCount()) {

      pOffset = m_pData + sizeof(UserInfoDataHeader);
      size_t newSize = 0;
      for (int i = 0 ; i <= num; ++i) {
        pOffset += newSize;
        newSize = UnalignedRead<int>(&((UserInfoDataChunk*)pOffset)->m_iChunkSize) +  sizeof(UserInfoDataChunk);
      }
    }

    return pOffset;// + sizeof(UserInfoDataChunk);
  }

  size_t GetChunkSize(const int num) const {
    char * pOffset = 0;
    size_t newSize = 0;
    if (num < GetUserInfoChuncksCount()) {
      pOffset = m_pData + sizeof(UserInfoDataHeader);
      for (int i = 0 ; i <= num; ++i) {
        newSize= UnalignedRead<int>(&((UserInfoDataChunk*)pOffset)->m_iChunkSize);
        pOffset += newSize + sizeof(UserInfoDataChunk);
      }
    }

    return newSize;
  }

  size_t GetSize() const {
    size_t size = 0;
    if (m_pData) {
      int num = GetUserInfoChuncksCount();
      size += sizeof(UserInfoDataHeader);
      char * pOffset = m_pData + sizeof(UserInfoDataHeader);
      for (int i = 0 ; i < num; ++i) {
        size_t newSize = UnalignedRead<int>(&((UserInfoDataChunk*)pOffset)->m_iChunkSize);
        pOffset += newSize + sizeof(UserInfoDataChunk);
        size +=newSize + sizeof(UserInfoDataChunk);
      }
    }

    return size;
  }

  const char * GetData() const {
    return m_pData;
  }

  void ClearData() {
    if (m_pData)
      free(m_pData);
  }

  void AddRawData(void * pData, size_t size) {
    if (m_pData)
      free(m_pData);

    m_pData = (char*)malloc(size);
    m_iSize = size;
    memcpy(m_pData, pData, size);
  }

private:
  char * m_pData;
  size_t m_iSize;
};

class IStreamedResource : public IStreamedStated
{
/*protected:*/
  
public:
  StreamCompleteNotifier * m_pNotifier;
  bool m_bAsyncCallback;
  // This is common syncro state
  IStreamedResource() : m_pNotifier(0), m_bAsyncCallback(false) {}
  virtual ~IStreamedResource() {}
  // nothing to do
  virtual void Abort() {

  }


  virtual void ClearUserDefinedData() {

  }

  virtual const UserDefinedInfo* GetUserDefinedData() {
    return 0;
  }

  virtual eMeshType GetMeshType() const  = 0;

  void SetStreamCompleteNotifier( StreamCompleteNotifier * pNotifier, bool bAsyncCallback = false) {
    m_bAsyncCallback = bAsyncCallback;
    m_pNotifier = pNotifier;
  }
};


class ICullObject : public CRefSmartPtr, public IStreamedResource
{
protected:
	IReadStreamProxy * m_pStream;
	eRenderType  m_eRenderType;
	bool m_bVisible;
	/*stlstring*/ Engine2::String m_strFileName;
public:
	ICullObject(void) : m_pStream(0), m_bVisible(TRUE), m_fRadius(0), m_abBox(0)  { /*for (int i = 0; i < MAXRENDERTYPE; ++i) {m_bVisibleType[i] = FALSE;*/ memset(m_bVisibleType, 0, sizeof(m_bVisibleType)); }
	virtual ~ICullObject(void) {
    if (m_pStream) {
      m_pStream->Abort();
      m_pStream = 0;

    }
  }

	virtual HRESULT Init(const CXmlElement *) {return -1;};
	virtual HRESULT SetParam(CParam *) {return -1;};
	virtual HRESULT DeleteParam(CParam *) {return -1;};
	virtual BOOL Validate(const CXmlElement *) { return TRUE;};
	virtual BOOL Equal(const ICullObject *) const { return FALSE;};
	virtual void Draw(CMatrix44 * mat, eRenderType){};
	virtual HRESULT CreateNewMesh(const CXmlElement *) = 0;
	virtual BOOL ReloadMesh() { return FALSE; }
	virtual BOOL ValidateType(const CXmlElement *) { return TRUE;}; 
	virtual HRESULT Restore()= 0;// { return E_FAIL;};
	virtual HRESULT Invalidate() { return S_OK;};
	virtual void Clone(ICullObject *) = 0;
	virtual BOOL IsVisible(eRenderType type) {return m_bVisible && m_bVisibleType[type];};
	virtual void SetLightArray(CLightArray *) = 0;
	virtual void PrepareShadowLights() {};
  virtual void SuperMethod() {};
  virtual bool IsVisibleInObject(IMeshInfo *) const { return false; }
// absolete..	unsigned int m_numReferences;
	void SetName(const char * name) {m_strFileName = name;};
	const char * GetName() { return m_strFileName.c_str(); };
	float m_fRadius;
  virtual size_t GetSize() { return 0; }
	virtual size_t GetCommonSize() { return 0; }
	ICullObject * m_pParent;
	CAABBox m_abBox;
	bool m_bVisibleType[eLast]; 
};


