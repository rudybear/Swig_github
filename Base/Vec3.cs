using System;
using System.Runtime.InteropServices;

namespace EngineCore.Base
{
    [StructLayout(LayoutKind.Sequential)]
    [Serializable()]
    public struct Vec3
    {
        public float x;
        public float y;
        public float z;

        public Vec3(float _x, float _y, float _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }

        public CVec3 ToCVec3()
        {
            return new CVec3(x, y, z);
        }

        public void FromCVec3(CVec3 v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
        }

#if false
        public float X
        {
            get { return x; }
            set { x = value; }
        }

        public float Y
        {
            get { return y; }
            set { y = value; }
        }

        public float Z
        {
            get { return z; }
            set { z = value; }
        }
#endif
    }
}
