%module Engine2
%{
#include "public/Core/ICore.h"
#include "Public/Core/IGameMod.h"
#include "Public/Render/IRender.h"
#include "public/Common/Strings.h"
%}

%include "public/Common/Strings.h"

%template(Engine2String) Engine2::String_template<char, Engine2::StandardAllocator>;

typedef int BOOL;
typedef int DWORD;
typedef float FLOAT;
typedef float CFLOAT;
typedef unsigned int uint32;
typedef int int32;

%include "public/Core/ICore.h"
%include "Public/Core/IGameMod.h"
%include "Public/Core/IWindow.h"
%include "Public/Core/IScene.h"
%include "Public/Render/IRender.h"
%include "Public/Render/IGUIRenderObject.h"
%include "public/Core/IMeshInfo.h"
%include "public/Core/IAnimatedMesh.h"
%include "public/Core/IWeatherSystem.h"
%include "public/Render/ILight.h"

%rename(add_assign) CVec2::operator+=;
%rename(add_assign) CVec3::operator+=;
%rename(add_assign) CVec4::operator+=;

%rename(sub_assign) CVec2::operator-=;
%rename(sub_assign) CVec3::operator-=;
%rename(sub_assign) CVec4::operator-=;

%rename(mul_assign) CVec2::operator*=;
%rename(mul_assign) CVec3::operator*=;
%rename(mul_assign) CVec4::operator*=;

%rename(div_assign) CVec2::operator/=;
%rename(div_assign) CVec3::operator/=;
%rename(div_assign) CVec4::operator/=;

%rename(equal) CVec2::operator==;
%rename(equal) CVec3::operator==;
%rename(equal) CVec4::operator==;

%rename(not_equal) CVec2::operator!=;
%rename(not_equal) CVec3::operator!=;
%rename(not_equal) CVec4::operator!=;

%rename(add) CVec2::operator+;
%rename(add) CVec3::operator+;
%rename(add) CVec4::operator+;

%rename(sub) CVec2::operator-;
%rename(sub) CVec3::operator-;
%rename(sub) CVec4::operator-;

%rename(mul) CVec2::operator*;
%rename(mul) CVec3::operator*;
%rename(mul) CVec4::operator*;

%rename(div) CVec2::operator/;
%rename(div) CVec3::operator/;
%rename(div) CVec4::operator/;

%rename(assign) CVec2::operator=;
%rename(assign) CVec3::operator=;
%rename(assign) CVec4::operator=;

%rename(mul_float) operator*( FLOAT, const CVec3& );
%rename(mul_float) operator*( FLOAT, const CVec4& );

%rename(cast) CVec3::operator FLOAT*;
%rename(const_cast) CVec3::operator const FLOAT*;

%rename(cast) CVec4::operator FLOAT*;
%rename(const_cast) CVec4::operator const FLOAT*;

%rename(less) operator < (const CVec3& lhs, const CVec3& rhs);
%rename(less) operator < (const CVec4& lhs, const CVec4& rhs);

%rename(great) operator > (const CVec3& lhs, const CVec3& rhs);
%rename(great) operator > (const CVec4& lhs, const CVec4& rhs);

%rename(quat_vec_mult) operator * (const CQuaternion &q, const CVec3 &v);
%rename(vec_quat_mult) operator * (const CVec3 &v, const CQuaternion &q);
 
%rename(not_equal) CMatrix44::operator!=;
%rename(assign) CMatrix44::operator=; 
%rename(mul) CMatrix44::operator*;

%rename(get_val) CMatrix44::operator[];
%rename(get_val_row_col) CMatrix44::operator();


%include "public/Common/MathVector.h"
%include "public/Common/MathMatrix.h"
%include "public/Common/Camera.h"
%include "public/Common/Xml_lib.h"

 
