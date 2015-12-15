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
#include <vector>
#include <string>
#ifndef MAX_EXPORT
#include "Public/Common/Strings.h"
#include "Public/Common/STLAllocator.h"
#else
typedef std::string stlstring;
#endif
#include <math.h>

// Class for basic common IO operations


struct MyMatrix
{
  union {
    float mat[4][4];
    float f[16];
  };

  bool operator == (const MyMatrix& a) {
    for (int i = 0; i < 16; ++i) {
      if (fabsf(a.f[i] - f[i]) > 0.0000001f)
        return false;
    }

    return true;
  }
};

struct MyQuat
{
  MyQuat():x(0),y(0),z(0),w(0) {}
  bool operator == (const MyQuat& v) { return fabsf(v.x - x) < 1e-6f && fabsf(v.y - y) < 1e-6f && fabsf(v.z - z) < 1e-6f && fabsf(v.w - w) < 1e-6f;}
  MyQuat(const float * f): x(f[0]), y(f[1]), z(f[2]), w(f[3]){}

  float x,y,z,w;
};

struct MyVec3
{
  MyVec3():x(0),y(0),z(0) {};
  MyVec3(const float * f): x(f[0]), y(f[1]), z(f[2]){}
  MyVec3(float _x, float _y, float _z): x(_x), y(_y), z(_z){}

  bool operator == (const MyVec3& v) { return fabsf(v.x - x) < 1e-6f && fabsf(v.y - y) < 1e-6f && fabsf(v.z - z) < 1e-6f;};
  float x,y,z;

  MyVec3& operator += (const MyVec3& a) { 
		x += a.x;
		y += a.y;
		z += a.z;
	  return *this;
  }

  MyVec3& operator - () { 
	  x = -x;
	  y = -y;
	  z = -z;
	  return *this;
  }

  MyVec3& operator -= (const MyVec3& a) { 
		x -= a.x;
		y -= a.y;
		z -= a.z;

	  return *this;
  }

  MyVec3& operator /= (const float a) { 
	  x /= a;
	  y /= a;
	  z /= a;
	  return *this;
  }

  MyVec3& operator *= (const float a) { 
		x *= a;
		y *= a;
		z *= a;

	  return *this;
  }

	MyVec3 Cross(const MyVec3& v) const
	{
		return MyVec3((y * v.z) - (z * v.y),
		              (z * v.x) - (x * v.z),
		              (x * v.y) - (y * v.x));
	}

	float Dot(const MyVec3& v) const 
	{
		return x*v.x + y*v.y + z*v.z;
	}

	MyVec3& Normalize()
	{
		if( const float len = this->Dot(*this) ) *this /= sqrtf(len);

		return *this;
	}
};

inline MyVec3 operator + (const MyVec3& a, const MyVec3& b ) { 
	return MyVec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline MyVec3 operator - (const MyVec3& a, const MyVec3& b ) { 
	return MyVec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

struct MyVec2
{
  MyVec2():x(0),y(0) {};
  MyVec2(const float * f): x(f[0]), y(f[1]){}
  bool operator == (const MyVec2& v) { return fabsf(v.x - x) < 1e-6f && fabsf(v.y - y) < 1e-6f;};
  float x,y;

};

struct MyVec4
{
  MyVec4():x(0),y(0),z(0),w(0) {};
  MyVec4(const float * f): x(f[0]), y(f[1]), z(f[2]), w(f[3]) {}
  bool operator == (const MyVec4& v) { return fabsf(v.x - x) < 1e-6f && fabsf(v.y - y) < 1e-6f && fabsf(v.z - z) < 1e-6f && fabsf(v.w - w) < 1e-6f;};
  float x,y,z,w;
};

struct CUVAnimationFrame
{
    int frame;
    float utile;
    float vtile;
    float uoffset;
    float voffset;
    float angle;
};


struct SkinInfo
{
  SkinInfo()
  {
    m_BoneID[0] = 0;
    m_BoneID[1] = 0;
    m_BoneID[2] = 0;
    m_BoneID[3] = 0;

    m_Weight[0] = 0.0f;
    m_Weight[1] = 0.0f;
    m_Weight[2] = 0.0f;
    m_Weight[3] = 0.0f;
  }
  int m_BoneID[4];
  float m_Weight[4];
};

struct SkinInfo2
{
  unsigned char m_BoneID[4];
  unsigned char m_Weight[4];
};

struct SkinInfo3
{
  unsigned int m_BoneID[4];
  unsigned char m_Weight[4];
};

struct TangentSpace
{
  MyVec3 m_Tangent;
  MyVec3 m_Binormal;
};
// full vertex
#ifndef MAX_EXPORT
struct Face
#else
struct MyFace
#endif
{
  int m_iInd[3];
  //	int m_i1;
  //	int m_i2;
  int m_iMatId;

  int m_NormalId0;
  int m_NormalId1;
  int m_NormalId2;
  int m_TexId0;
  int m_TexId1;
  int m_TexId2;
};


struct MyVertex 
{
  MyVec3 m_Pos;
  MyVec3 m_Normal;
};

namespace Engine2
{

#define TYPE_SKELETON								0x10
#define TYPE_ANIMATION_CONTROLLER		0x11
#define TYPE_MESH										0x12
#define TYPE_MATERIAL								0x13
#define TYPE_LIGHT  								0x14
#define TYPE_INDOOR 								0x15
#define TYPE_USER  									0x16
#define TYPE_XREF  									0x17
#define TYPE_ANIMMESH               0x18
#define TYPE_CUSTOMSTREAM           0x18
#define TYPE_UVANIMATION            0x19
#define TYPE_VERTEXDATA             0x20
#define TYPE_INDEXDATA              0x21
#define TYPE_COMPILED_RO            0x22
#define TYPE_TIMESTAMP              0x23

	const char Engine2tag[] = "Engine2";
	// Common header for engine2 files
	struct Header
	{
		char m_Tag[8];
		int m_iNumChunks;
		int m_iChunksOffset;
	};

	struct ChunkInfo
	{
		int m_iOffset;
		int m_iSize;
		int m_iVersion;
		int m_iType;
	};

	// File structure looks : Header|Chunks data|Chunks list
	
	class CChunkFile
	{
	private:
		std::vector<ChunkInfo> m_Chunks;
		std::vector<char> m_Data;

		Header * GetHeader()
		{
			return (Header *)&m_Data[0];
		}


	public:

		// IO routine
		bool SaveChunks(const char *);
		size_t SaveChunks(void *, size_t);
		bool LoadChunks(const char *);
		bool LoadChunks(char *, size_t);

		// Chunks API
		void AddChunk(int version, int type, void * pData, int size);

		int GetNumChunks();
		int GetChunkVersion(int);
		int GetChunkType(int);
		int GetChunkSize(int);
		void * GetChunkData(int);

		CChunkFile(void);
		~CChunkFile(void);

    template<class T>
    static void SimpleGet(char ** data, T& value)
    {
      memcpy(&value, *data, sizeof(T));
      *data += sizeof(T);
    }
        template<class T>
    static void SimpleGetArray(char ** data, T& value)
    {
        int cc;
        memcpy(&cc, *data, sizeof(int));
        *data += sizeof(int);
        if (cc) {
            value.resize(cc);
            memcpy(&value[0], *data, sizeof(typename T::value_type) * cc);
            *data += sizeof(typename T::value_type) * cc;
        }
    }

#if !defined(__GNUC__)    
		template<>
		static void SimpleGet<stlstring>(char ** data, stlstring& value)
		{
			short int len;
			memcpy(&len, *data, sizeof(short int));
			*data += sizeof(short int);
			value.resize(len);
			memcpy(&value[0], *data, len);
			*data += len;
		}

#ifndef MAX_EXPORT
		template<>
		static void SimpleGet<Engine2::String>(char ** data, Engine2::String& value)
		{
			short int len;
			memcpy(&len, *data, sizeof(short int));
			*data += sizeof(short int);
			value.resize(len);
			memcpy(value.begin(), *data, len);
			*data += len;
		}
#endif
#endif    


	};
#if defined(__GNUC__)    
    template<>
    FORCEINLINE void CChunkFile::SimpleGet<stlstring>(char ** data, stlstring& value)
    {
        short int len;
        memcpy(&len, *data, sizeof(short int));
        *data += sizeof(short int);
        value.resize(len);
        memcpy(&value[0], *data, len);
        *data += len;
    }

#ifndef MAX_EXPORT
    template<>
    FORCEINLINE void CChunkFile::SimpleGet<Engine2::String>(char ** data, Engine2::String& value)
    {
        short int len;
        memcpy(&len, *data, sizeof(short int));
        *data += sizeof(short int);
        value.resize(len);
        memcpy(value.begin(), *data, len);
        *data += len;
    }
#endif
#endif    

	template<class T>
	inline void SimplePut(std::vector<char>& data, T& value)
	{
		size_t last = data.size();
		data.resize(last + sizeof(T));
		memcpy(&data[last], &value, sizeof(T));
	}

	template<>
	inline void SimplePut<stlstring>(std::vector<char>& data, stlstring& value)
	{
		size_t last = data.size();
		data.resize(last + value.length() + sizeof(short int));
		short int len = (short int)value.length();
		memcpy(&data[last], &len, sizeof(short int));
		if (len)
			memcpy(&data[last + sizeof(short int)], value.c_str(), len);
	}

	template<class T>
	inline void SimplePutArray(std::vector<char>& data, T& value, size_t count)
	{
		size_t last = data.size();
		data.resize(last + sizeof(T::value_type) * count + sizeof(int));
		int cc = (int)count;
		memcpy(&data[last], &cc, sizeof(int));
		if (cc)
			memcpy(&data[last + sizeof(int)], &value[0], sizeof(T::value_type) * count);
	}

	template<class T>
	inline void SimplePutArray(std::vector<char>& data, T& value)
	{
		SimplePutArray(data, value, value.size())	;
	}

}