using System;
using System.Runtime.InteropServices;

namespace EngineCore.Base
{
    [StructLayout(LayoutKind.Sequential)]
    [Serializable()]
    public struct Matrix44
    {
        public float _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44;

        public CMatrix44 ToCMatrix44()
        {
            return new CMatrix44(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44);
        }

        public void FromCMatrix44(CMatrix44 mat)
        {
            _11 = mat._11;
            _12 = mat._12;
            _13 = mat._13;
            _14 = mat._14;
            _21 = mat._21;
            _22 = mat._22;
            _23 = mat._23;
            _24 = mat._24;
            _31 = mat._31;
            _32 = mat._32;
            _33 = mat._33;
            _34 = mat._34;
            _41 = mat._41;
            _42 = mat._42;
            _43 = mat._43;
            _44 = mat._44;
        }
    }
}
