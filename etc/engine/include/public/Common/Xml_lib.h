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

#include "Common.h"
#include "Strings.h"
#include "Vector.h"

typedef int BOOL;


#ifdef SWIG

#undef DLLIMPORT
#define DLLIMPORT

#endif

/*! \addtogroup XMLReading
*@{
*/

namespace xml 
{
  class TiXmlNode;
};


//! Param-Value 
class DLLIMPORT CXmlParam //param wich can be assigned to one of elements;
{
public:
	CXmlParam(){};
	CXmlParam(const Engine2::String &szName,const Engine2::String &szValue)
	{
		ParamName = szName;
		ParamValue = szValue;
	};
	~CXmlParam(){};

	Engine2::String ParamName;
	Engine2::String ParamValue;
};



typedef Engine2::Vector<CXmlParam> XmlParamList;

class /*DLLIMPORT*/  IXmlParams
{
protected:
	virtual void				AddParam(const Engine2::String& ParamName, const Engine2::String& ParamValue)=0;
public:
	virtual ~IXmlParams()  {};
	virtual const CXmlParam*	GetParam(int) const =0;
	virtual int					GetNumParams(void) const =0;
	virtual CXmlParam*			GetParamByName(Engine2::String szName)=0;
	virtual const char*			GetValueByName(const Engine2::String&) const=0;
	virtual void				SetParam(const Engine2::String&, const Engine2::String&)=0;
};

class DLLIMPORT CXmlParams:public IXmlParams
{
public:
	CXmlParams();
	~CXmlParams();

	const CXmlParam *GetParam(int i) const;
	CXmlParam* GetParamByName(Engine2::String szName);
protected:
	void AddParam(const Engine2::String& ParamName, const Engine2::String& ParamValue);
public:
	int GetNumParams(void) const; 
	const char* GetValueByName(const Engine2::String& KeyName) const;
	void SetParam(const Engine2::String& KeyName, const Engine2::String& NewParamName);
public: //data
	XmlParamList m_Contents;
};

class CXmlElement;

typedef Engine2::Vector<CXmlElement> XmlElementsList;



class DLLIMPORT CXmlVector
{
public:
	CXmlVector(void){m_Contents.clear();};
	~CXmlVector(void);
public:
	BOOL Serialize(FILE *to, int level);
	BOOL SerializeBuffer(Engine2::String& buffer, int level);
	int Deserialize(const Engine2::String& buffer, int );
	CXmlElement *FindElementByName(const Engine2::String& ElementName);
	const CXmlElement *FindElementByName(const Engine2::String& ElementName) const;
	const CXmlElement *FindElementByNameConst(const Engine2::String& ElementName) const;
	CXmlElement*  AddElement(const CXmlElement *element);
	void SwapElements(size_t E1, size_t E2);
	void RemoveElement(size_t nNum);
public:
	XmlElementsList m_Contents;
};

class DLLIMPORT CXmlElement
{
public:
	CXmlElement(void);
	~CXmlElement(void);

public:
	BOOL Serialize(const Engine2::String& FileName);
	BOOL SerializeThroughAPI(const char *szFileName);
	BOOL Serialize(FILE *to, int level);
	BOOL SerializeBuffer(Engine2::String& buffer, int level);
	void SetName(const Engine2::String& pName);
	BOOL LoadFromXml(const Engine2::String& szFileName);
	BOOL LoadFromXml(const char * szFileName);
	BOOL LoadFromStr(const Engine2::String& szString);
	BOOL LoadFromStr(const char * szString, size_t strLen);
	const char *GetParamValueByName(const Engine2::String &szName) const;
	CXmlElement *GetElementByName(const Engine2::String &szName);

	BOOL Deserialize(const Engine2::String& FileName);
	int Deserialize(const Engine2::String& buffer, int offset);

	void ClearContents(void);
	CXmlElement *Clone(void) const;
	BOOL ProcessXmlNode(xml::TiXmlNode *pNode, CXmlElement *pElement);

	CXmlElement operator = (const CXmlElement &xml);
	void  CopyFrom (const CXmlElement *xml);

  const char * GetName() {
    return m_szName.c_str();
  }

public://Data
	CXmlParams m_Params;
	CXmlVector m_Elements;
	Engine2::String m_szName;

	BOOL AppendXML(CXmlElement *pXmlToAdd);
};

class IVFSFileManager;

DLLIMPORT BOOL XMLAddInt(CXmlElement *pXml, const Engine2::String& szName, int nValue);
DLLIMPORT int XMLGetInt(const CXmlElement *pXml, const Engine2::String& szName, int nDefaultValue, BOOL &bResult);
DLLIMPORT BOOL XMLAddFloat(CXmlElement *pXml, const Engine2::String& szName, float fValue);
DLLIMPORT float XMLGetFloat(const CXmlElement *pXml, const Engine2::String& szName, float fDefaultValue, BOOL &bResult);
DLLIMPORT BOOL XMLGetBOOL(const CXmlElement *pXml, const Engine2::String& szName);
DLLIMPORT BOOL GetXmlFileDataFromStream(IVFSFileManager *pFileManager,CXmlElement *pXmlContainer,const char * szFileName,BOOL bAbsFilePath = 0);
