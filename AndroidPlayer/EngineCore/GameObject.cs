using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EngineCore.Base;

namespace EngineCore
{
    [Serializable()]
    public class GameObject : BaseObject
    {
        public Matrix44 matrix;
        public Vec3 position;
        public Vec3 rotation;
        public Vec3 scale;


        public GameObject()
        {
            matrix = new Matrix44();

            position = new Vec3();
            //position.Set(0,0,0);

            rotation = new Vec3();
            //rotation.Set(0,0,0);

            scale = new Vec3();
            //scale.Set(1,1,1);
        }

        private void SyncMatrix()
        {
            //CMatrix44 matRot = new CMatrix44(0);
            //matRot.FromYPR(rotation.x, rotation.y, rotation.z);
            //matrix.FromPosRotScale(position, matRot, scale);
        }

        private void SyncMatrixTranslation()
        {
            //matrix.SetTranslation(position);
        }

        public void SetPosition(CVec3 position)
        {
            //matrix.SetTranslation(position);
        }

        CVec3 GetPosition()
        {
            return new CVec3();// matrix.GetTranslation();
        }

        public float PosX
        {
            get { return position.x;  }
            set { position.x = value; SyncMatrixTranslation(); }
        }

        public float PosY
        {
            get { return position.y;  }
            set { position.y = value; SyncMatrixTranslation(); }
        }

        public float PosZ
        {
            get { return position.z;  }
            set { position.z = value; SyncMatrixTranslation(); }
        }

    }

}
