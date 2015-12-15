//
//#pragma once
//
//class CHARhash_compare
//{
//
//public:
//	enum
//	{    // parameters for hash table
//		bucket_size = 4,    // 0 < bucket_size
//		min_buckets = 8
//	}; 
//
//	CHARhash_compare( )
//	{
//	}
//
//	size_t operator( )( const stlstring& Str)const
//	{
//		const char* ptr = Str.data();
//		size_t hashVal = 0;
//		while(*ptr)
//		{
//			hashVal = 5*hashVal + tolower(*ptr);
//			ptr++;
//		}
//		return hashVal;
//	}
//
//	bool operator( )( 
//		const stlstring& _Key1,
//		const stlstring& _Key2
//	)const
//	{
//		size_t n1 = 0;
//		size_t n2 = 0;
//
//		const char* ptr = _Key1.data();
//		while(*ptr)
//		{
//			n1 = 5*n1 + tolower(*ptr);
//			ptr++;
//		}
//
//
//		ptr = _Key2.data();
//		while(*ptr)
//		{
//			n2 = 5*n2 + tolower(*ptr);
//			ptr++;
//		}
//		return n1>n2;
//	}
//};
