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

#include "Mathlib.h"
#include "Strings.h"
#include "EngineTypes.h"
//#include <string>
#include <vector>
#include <stdio.h>

#if defined(STATIC_LIB) || defined(__APPLE__) || defined (ANDROID_NDK) || defined(EMSCRIPTEN)
#include "Public/Core/Crc32.h"
  #if defined (ANDROID_NDK) && !defined(HAS_CRC32)
	#if !defined(HAS_CRC32)
		#define HAS_CRC32
	#endif
  #endif
#endif

typedef Engine2::Vector<CMatrix44> MatrixArray;
typedef Engine2::Vector<CVec4> VectorArray;
typedef Engine2::Vector<CQuatTS> QuatTArray;

class CParam
{
private:
	eParamType m_Type;
	char m_Data[sizeof(CMatrix44)]; // biggest size here

	Engine2::String m_String;
	Engine2::String m_Name;
  MatrixArray m_MatrixArray;
  VectorArray m_VectorArray;
  QuatTArray m_QuatTArray;

  uint32 m_NameHash;

	void Clean();

public:

  CParam() : m_MatrixArray(), m_VectorArray(), m_QuatTArray()
			{
				m_Type = e_None;
				pOnParamChange = NULL;
        memset(m_Data, 0, sizeof(m_Data));
			}

			void SetName(const char *);

			CParam(const CParam& p)
			{
				m_Type = e_None;
				operator=(p);
			}

			CParam(const char * name)  : m_MatrixArray(), m_VectorArray(), m_QuatTArray()
			{
				m_Type = e_None;
				m_Name = name;
				pOnParamChange = NULL;
        MakeHash();
        memset(m_Data, 0, sizeof(m_Data));
			}

			~CParam(void);

			// Info
			eParamType GetType() const { return m_Type;};
			const char * GetTypeAsString() const
			{
				switch (m_Type)
				{
				case e_None:
					return "none";
				case e_Float:
					return "float";
				case e_String:
					return "string";
				case e_Integer:
					return "integer";
				case e_Vector2:
					return "vector2";
				case e_Vector3:
					return "vector3";
				case e_Vector4:
					return "vector4";
				case e_Pointer:
					return "pointer";
				case e_MatrixArray:
					return "matrixarray";
				case e_VectorArray:
					return "vectorarray";
				default:
					return "unknown";
				}
			}

			void SetType(eParamType e)
			{
				m_Type = e;
			}
			void SetFromString(const char * str);

      inline uint32 GetHash() const {
#if !defined(ANDROID_NDK) && !defined(FLASH)
        assert(m_NameHash != 0);
#endif
        return m_NameHash;
      };

			const char * GetName() const
			{ 
				if (m_Name.empty())
					return "";
				else
					return m_Name.c_str();
			}
			// float
			void SetFloat(float a)
			{
        float * vFloat = ((float*)m_Data);
				const bool bNeedUpdate = pOnParamChange != NULL && m_Type == e_Float && *vFloat != a;
				Clean();

				//m_Float = a;
        *vFloat = a;

				m_Type = e_Float;
				if (bNeedUpdate)
					pOnParamChange();
			};

      FORCEINLINE void FastSetFloat(float a)
      {
        float * vFloat = ((float*)m_Data);
        *vFloat = a;
      };

			float GetFloat() const;

			// integer
			void SetInt(int a)
			{
        int * vInt = ((int*)m_Data);

				const bool bNeedUpdate = pOnParamChange != NULL && m_Type == e_Integer && *vInt != a;
				Clean();
        *vInt = a;
				//m_Integer = a;
				m_Type = e_Integer;
				if (bNeedUpdate)
					pOnParamChange();
			};

			inline int GetInt() const
			{
        return *((int*)m_Data);
			}

			// string
			void SetString(const char *);
			const char * GetString () const;

			//  vec4
			inline void SetVector4(const CVec4& a)
			{
        CVec4 * vVec4 = ((CVec4*)m_Data);
				const bool bNeedUpdate = pOnParamChange != NULL && m_Type == e_Vector4 && *vVec4 != a;
				Clean();
        *vVec4 = a;
				//m_Vector4 = a;
				m_Type = e_Vector4;
				if (bNeedUpdate)
					pOnParamChange();
			}

			const CVec4& GetVector4() const;

			//  vec3
			inline void SetVector3(const CVec3& a)
			{
        CVec3 * vVec3 = ((CVec3*)m_Data);
				const bool bNeedUpdate = pOnParamChange != NULL && m_Type == e_Vector3 && *vVec3 != a;
				Clean();
        *vVec3 = a;
				//m_Vector3 = a;
				m_Type = e_Vector3;
				if (bNeedUpdate)
					pOnParamChange();
			};

			const CVec3& GetVector3() const;

			//  vec2
			void SetVector2(CVec2& a)
			{
        CVec2 * vVec2 = ((CVec2*)m_Data);
				const bool bNeedUpdate = pOnParamChange != NULL && m_Type == e_Vector2 && *vVec2 != a;
				Clean();
        *vVec2 = a;
				//m_Vector2 = a;
				m_Type = e_Vector2;
				if (bNeedUpdate)
					pOnParamChange();
			};

			const CVec2& GetVector2() const;

			//  matrix
			inline void SetMatrix(const CMatrix44& a)
			{
        CMatrix44 * vMat = ((CMatrix44*)m_Data);
				Clean();
        *vMat = a;
//				m_Matrix = a;
				m_Type = e_Matrix;
				if (pOnParamChange)
					pOnParamChange();
			}

			const CMatrix44& GetMatrix() const;

			void SetMatrixArray(MatrixArray&);
			MatrixArray& GetMatrixArray() { return m_MatrixArray;};
			const MatrixArray& GetMatrixArray() const { return m_MatrixArray;};

			void SetQuatTArray(QuatTArray&);
			QuatTArray& GetQuatTArray() { return m_QuatTArray;};
			const QuatTArray& GetQuatTArray() const { return m_QuatTArray;};

			void SetVectorArray(VectorArray&);
			VectorArray& GetVectorArray() { return m_VectorArray;};
			const VectorArray& GetVectorArray() const { return m_VectorArray;};

			// pointer
			//void SetPointer(void *);
			//const void * GetPointer() const;

			CParam& operator  = (const CParam& );
			CParam& operator  = (float);
			CParam& operator  = (int);
			CParam& operator  = (char *);
			CParam& operator  = (CVec2&);
			CParam& operator  = (CVec3&);
			CParam& operator  = (CVec4&);
			CParam& operator  = (CMatrix44&);
			bool operator == (const CParam& a);
			bool operator != (const CParam& a);

      void MakeHash();

			//	operator const float() const;
			operator float();
			operator int();
			operator const char * ();
			operator const CVec2&();	
			operator const CVec3&();
			operator const CVec4&();
			operator const CMatrix44&();

			//notify
			void (*pOnParamChange)(void);
};

inline void CParam::SetName(const char * name)
{
	m_Name = name;
  MakeHash();
}

inline CParam::~CParam(void)
{
	Clean();
}


inline CParam& CParam::operator=(const CParam& p)
{
  if (&p != this) {
    Clean();
    //memset(this, 0, sizeof(CParam));

    m_Type = p.m_Type;
    m_Name = p.m_Name;
    m_String = p.m_String;
    //m_sHandle = p.m_sHandle;
    m_NameHash = p.m_NameHash;
    pOnParamChange = p.pOnParamChange;
    
    switch (m_Type)
    {
      /*
    case e_Float:
      m_Float = p.m_Float;
      break;
    case e_String:
      m_String = p.m_String;
      break;
    case e_Integer:
      m_Integer = p.m_Integer;
      break;
    case e_Vector2:
      m_Vector2 = p.m_Vector2;
      break;
    case e_Vector3:
      m_Vector3 = p.m_Vector3;
      break;
    case e_Vector4:
      m_Vector4 = p.m_Vector4;
      break;
    case e_Matrix:
      m_Matrix = p.m_Matrix;
      break;
    case e_Pointer:
      m_Pointer = p.m_Pointer;
      break;
      */
    case e_MatrixArray:
      m_MatrixArray = p.m_MatrixArray;
      break;
    case e_VectorArray:
      m_VectorArray = p.m_VectorArray;
      break;
    case e_QuatTArray:
      m_QuatTArray = p.m_QuatTArray;
      break;
    default:
      memcpy(m_Data, p.m_Data, sizeof(p.m_Data));
      ;
    }
    
    
  }
  return *this;
}

inline void CParam::Clean()
{
	switch (m_Type)
	{
	////case e_None:
	////	return "none";
	////case e_Float:
	////	return "float";
	////case e_String:
	////	break;
	//	//case e_Integer:
	////	return "integer";
	////case e_Vector2:
	////	return "vector2";
	////case e_Vector3:
	////	return "vector3";
	////case e_Vector4:
	////	return "vector4";
	////case e_Pointer:
	////	return "pointer";
	case e_MatrixArray:
		{
			MatrixArray destruct;
			m_MatrixArray.swap(destruct);
		}
		break;
	case e_VectorArray:
		{
			VectorArray destruct;
			m_VectorArray.swap(destruct);
		}
		break;
	case e_QuatTArray:
		{
			QuatTArray destruct;
			m_QuatTArray.swap(destruct);
		}
		break;
	default:
		;
	}

	m_Type = e_None;
  //memset(this, 0, sizeof(CMatrix44) + sizeof(int));	// to avoid destruction
  memset(m_Data, 0, sizeof(m_Data));
}

inline void CParam::MakeHash()
{
#if defined(HAS_CRC32) || defined(STATIC_LIB)
  m_NameHash = CRC32(m_Name.c_str());
#else
  m_NameHash = 0;
#endif
}

inline float CParam::GetFloat() const
{
	if (m_Type == e_Float)
		//return m_Float;
    return *((float*)m_Data);
	return 0.0f;
}

// string
inline void CParam::SetString(const char * a)
{
  //const char ** str = (const char**)m_Data;
	const bool bNeedUpdate = pOnParamChange != NULL && m_Type == e_String && m_String != a;
	Clean();
	m_String = a;
  //*str = a;
	m_Type = e_String;
	if (bNeedUpdate)
		pOnParamChange();
}

inline void CParam::SetFromString(const char * str)
{
	if (m_Type == e_String)
	{
		SetString(str);
		if (pOnParamChange)
			pOnParamChange();

		return; 
	}

	if (m_Type == e_Integer)
	{
		SetInt(atoi(str));
		if (pOnParamChange)
			pOnParamChange();

		return;
	}

	if (m_Type == e_Float)
	{
		SetFloat((float)atof(str));
		if (pOnParamChange)
			pOnParamChange();

		return;
	}

	if (m_Type == e_Vector4)
	{
    CVec4 vec4;
		sscanf_s(str, "%f,%f,%f,%f", &vec4.x,&vec4.y,&vec4.z,&vec4.w);
    SetVector4(vec4);
		if (pOnParamChange)
			pOnParamChange();

		return;

	}


	if (m_Type == e_Vector3)
	{
    CVec3 vec3;
		sscanf_s(str, "%f,%f,%f", &vec3.x,&vec3.y,&vec3.z);
    SetVector3(vec3);
		if (pOnParamChange)
			pOnParamChange();

		return;

	}

	if (m_Type == e_Vector2)
	{
    CVec2 vec2;
		sscanf_s(str, "%f,%f", &vec2.x,&vec2.y);
    SetVector2(vec2);
		if (pOnParamChange)
			pOnParamChange();

		return;

	}
	if (m_Type == e_Matrix)
	{
    CMatrix44 mat;
		sscanf_s(str,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
			&mat._11,&mat._12,&mat._13,&mat._14,
			&mat._21,&mat._22,&mat._23,&mat._24,
			&mat._31,&mat._32,&mat._33,&mat._34,
			&mat._41,&mat._42,&mat._43,&mat._44);
    SetMatrix(mat);
		if (pOnParamChange)
			pOnParamChange();

		return;
	}
}

inline const char * CParam::GetString () const
{
	static char buf[255]; buf[0] = '\0';
	if (m_Type == e_String)
		return m_String.c_str();

	if (m_Type == e_Integer)
	{
    int vInt = GetInt();
		//_itoa_s(vInt, buf, 10);
        sprintf_s(buf, "%i", vInt);
		return buf;
	}

	if (m_Type == e_Float)
	{
    float vFloat = GetFloat();
		sprintf_s(buf, "%f", vFloat);
		return buf;
	}

	if (m_Type == e_Vector2)
	{
    CVec2 vVec2 = GetVector2();
		sprintf_s(buf, "(%f, %f)", vVec2.x,vVec2.y);
		return buf;
	}

	if (m_Type == e_Vector3)
	{
    CVec3 vVec3 = GetVector3();
		sprintf_s(buf, "(%f, %f, %f)", vVec3.x,vVec3.y,vVec3.z);
		return buf;
	}

	if (m_Type == e_Vector4)
	{
    CVec4 vVec4 = GetVector4();
		sprintf_s(buf, "(%f, %f, %f, %f)", vVec4.x,vVec4.y,vVec4.z,vVec4.w);
		return buf;
	}
	if (m_Type == e_Matrix)
	{
    CMatrix44 vMat = GetMatrix();
		sprintf_s(buf,"(%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f)",
			vMat._11,vMat._12,vMat._13,vMat._14,
			vMat._21,vMat._22,vMat._23,vMat._24,
			vMat._31,vMat._32,vMat._33,vMat._34,
			vMat._41,vMat._42,vMat._43,vMat._44);
		return buf; 
	}
	return buf;
}


inline const CVec4& CParam::GetVector4() const
{
	return *((CVec4*)(m_Data));
}

//  vec3
inline const CVec3& CParam::GetVector3() const
{
	return *((CVec3*)(m_Data));
}

//  vec2
inline const CVec2& CParam::GetVector2() const
{
	return *((CVec2*)(m_Data));
}

//  matrix
inline const CMatrix44& CParam::GetMatrix() const
{

	return *((CMatrix44*)(m_Data));;
}

inline void CParam::SetQuatTArray(QuatTArray& a)
{
	Clean();
  //*((QuatTArray*)(m_Data)) = a;
	m_QuatTArray = a;
	m_Type = e_QuatTArray;

	if (pOnParamChange)
		pOnParamChange();
}

inline void CParam::SetMatrixArray(MatrixArray& a)
{
	Clean();
	m_MatrixArray = a;
  //*((MatrixArray*)(m_Data)) = a;
	m_Type = e_MatrixArray;

	if (pOnParamChange)
		pOnParamChange();
}

inline void CParam::SetVectorArray(VectorArray& a)
{
	Clean();
  //*((VectorArray*)(m_Data)) = a;
	m_VectorArray = a;
	m_Type = e_VectorArray;

	if (pOnParamChange)
		pOnParamChange();
}

inline CParam& CParam::operator  = (float a )
{
	SetFloat(a);
	return *this;
}

inline CParam& CParam::operator  = (int a)
{
	SetInt(a);
	return *this;

}

inline CParam& CParam::operator  = (char * a)
{
	SetString(a);
	return *this;

}

inline CParam& CParam::operator  = (CVec2& a)
{
	SetVector2(a);
	return *this;

}

inline CParam& CParam::operator  = (CVec3& a)
{
	SetVector3(a);
	return *this;
}

inline CParam& CParam::operator  = (CVec4& a)
{
	SetVector4(a);
	return *this;

}

inline CParam& CParam::operator  = (CMatrix44& a)
{
	SetMatrix(a);
	return *this;
}

inline bool CParam::operator != (const CParam& a)
{
	return !(operator==(a));
}

inline bool CParam::operator == (const CParam& a)
{
	if (/*m_Name == a.m_Name && */m_Type == a.m_Type)
	{
		if (m_Type == e_String)
			return m_String == a.m_String;
		else
			if (m_Type == e_Integer)
				return GetInt() == a.GetInt();
			else
				if (m_Type == e_Float)
					return GetFloat() == a.GetFloat();
				else
					if (m_Type == e_Vector2)
						return !(GetVector2() != a.GetVector2());
					else
						if (m_Type == e_Vector3)
							return !(GetVector3() != a.GetVector3());
						else
							if (m_Type == e_Vector4)
								return !(GetVector4() != a.GetVector4());
							else
								if (m_Type == e_Matrix)
									return !(GetMatrix() != a.GetMatrix());
	}
	return false;
}


inline CParam::operator float()
{
	return GetFloat();
}

inline CParam::operator int()
{
	return GetInt();
}

inline CParam::operator const char * ()
{
	return (char *)GetString();
}

inline CParam::operator const CVec2&()
{
	return GetVector2();
}

inline CParam::operator const CVec3&()
{
	return GetVector3();
}

inline CParam::operator const CVec4&()
{
	return GetVector4();
}

inline CParam::operator const CMatrix44&()
{
	return GetMatrix();
}

