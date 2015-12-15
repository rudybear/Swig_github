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
#include "Public/Common/Vector.h"
#include "Public/Common/Strings.h"
#include <algorithm>


DLLIMPORT void ChangeSlash(stlstring& str);
DLLIMPORT void AddBackSlash(stlstring& str);
DLLIMPORT stlstring RemoveBackslash( const stlstring &path );
DLLIMPORT void ReplaceStr(stlstring& str, const stlstring& searchStr, const stlstring& ins );
DLLIMPORT stlstring GetExtension(const stlstring& str);
DLLIMPORT stlstring GetName(stlstring& str);
DLLIMPORT stlstring GetPath(stlstring& str);
DLLIMPORT void GetParamsList(const char * str, char  br, stlvector(stlstring) & list, bool bForceLowerCase);
DLLIMPORT void GetParamsList(const char * str, char  br, Engine2::Vector<Engine2::String> & list, bool bForceLowerCase);
DLLIMPORT stlstring EraseExtension(const stlstring& str);

inline void StringToLower(stlstring& str)
{
    for (stlstring::iterator it = str.begin(), end = str.end(); it != end; ++it)
        *it = tolower(*it);
}
DLLIMPORT void ChangeExtension(stlstring& str, const stlstring& ext);
DLLIMPORT stlstring  EraseAftermark(const stlstring& str, int ch);

namespace EngString
{
    DLLIMPORT bool IsEqual(const stlstring& str1, const stlstring& str2); // Сравнивает строки без учета регистра. Возвращает true, если равны
};


