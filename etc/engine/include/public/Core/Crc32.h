
#ifndef __crc32_h__
#define __crc32_h__

#if _MSC_VER > 1000
#pragma once
#endif

#include <stdlib.h>
#include <string.h>

#ifndef HAS_CRC32
#define HAS_CRC32 1
#endif

class Crc32Table
{
public:
	static Crc32Table& GetCrc32Table();

	static unsigned int crc32_table[256];  //!< Lookup table array
	static void init_CRC32_Table();  //!< Builds lookup table array 
private:
	static bool m_bInit;
	static unsigned int reflect( unsigned int ref, char ch); //!< Reflects CRC bits in the lookup table 
};

class Crc32Gen 
{
public:
	Crc32Gen();
	//! Creates a CRC from a text string 
	unsigned int GetCRC32( const char *text ) const;
	unsigned int GetCRC32( const char *data,int size,unsigned int ulCRC ) const;

	unsigned int GetCRC32Lowercase( const char *text ) const;
	unsigned int GetCRC32Lowercase( const char *data,int size,unsigned int ulCRC ) const;

protected:

	unsigned int get_CRC32( const char *data,int size,unsigned int ulCRC ) const;
	unsigned int get_CRC32Lowercase( const char *data,int size,unsigned int ulCRC ) const;
};

inline unsigned int Crc32Gen::GetCRC32( const char *text ) const
{
	int len = (int)strlen(text);
	return GetCRC32( text,len,-1 );
}

inline unsigned int Crc32Gen::GetCRC32( const char *data, int size, unsigned int ulCRC ) const
{
	return get_CRC32( data,size,ulCRC );
}

inline unsigned int Crc32Gen::GetCRC32Lowercase( const char *text ) const
{
	int len = (int)strlen(text);
	return GetCRC32Lowercase( text,len,-1 );
}

inline unsigned int Crc32Gen::GetCRC32Lowercase( const char *data, int size, unsigned int ulCRC ) const
{
	return get_CRC32Lowercase( data,size,ulCRC );
}

#define _ascii_tolower(c)     ( (((c) >= L'A') && ((c) <= L'Z')) ? ((c) - L'A' + L'a') : (c) )

inline unsigned int Crc32Gen::get_CRC32Lowercase( const char *data,int size,unsigned int ulCRC ) const
{	
	int len; 
	unsigned char* buffer;

	// Get the length. 
	len = size; 

	// Save the text in the buffer. 
	buffer = (unsigned char*)data; 
	// Perform the algorithm on each character in the string, using the lookup table values. 

	Crc32Table& table = Crc32Table::GetCrc32Table();
	while(len--) 
  {
    unsigned char c = *buffer++;
	  ulCRC = (ulCRC >> 8) ^ table.crc32_table[(ulCRC & 0xFF) ^ _ascii_tolower(c)]; 
  }
	// Exclusive OR the result with the beginning value. 
	return ulCRC ^ (unsigned int)-1; 
} 


unsigned int CRC32(const char *szStr);

inline unsigned int CRC32Lower(const char *szStr)
{
	Crc32Gen gen;
	unsigned int nHash = gen.GetCRC32Lowercase(szStr, (int)strlen(szStr), -1);
	return nHash;
}

#endif // __crc32_h__
