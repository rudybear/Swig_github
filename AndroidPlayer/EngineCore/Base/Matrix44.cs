using System;
using System.Runtime.InteropServices;

namespace EngineCore.Base
{
    [StructLayout(LayoutKind.Sequential)]
    [Serializable()]
    public struct Matrix44
    {
        public float _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44;

        [NonSerialized()]
        public CMatrix44 cMat44;
        public CMatrix44 ToCMatrix44()
        {
            if (cMat44 == null)
            {
                cMat44 = new CMatrix44(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44);
            }

            return cMat44;
        }


        public void SetIdentity()
        {
            _11 = 1.0f;
            _12 = 0.0f;
            _13 = 0.0f;
            _14 = 0.0f;
            _21 = 0.0f;
            _22 = 1.0f;
            _23 = 0.0f;
            _24 = 0.0f;
            _31 = 0.0f;
            _32 = 0.0f;
            _33 = 1.0f;
            _34 = 0.0f;
            _41 = 0.0f;
            _42 = 0.0f;
            _43 = 0.0f;
            _44 = 1.0f;
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
