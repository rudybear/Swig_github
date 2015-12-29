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

        private bool needUpdate;


        public GameObject()
        {
            matrix = new Matrix44();
            matrix.SetIdentity();

            position = new Vec3();
            //position.Set(0,0,0);

            rotation = new Vec3();
            //rotation.Set(0,0,0);

            scale = new Vec3();
            scale.x = scale.y = scale.z = 1.0f;

            needUpdate = false;
            //scale.Set(1,1,1);
        }

        public bool IsMatrixNeedUpdate()
        {
            return needUpdate;
        }

        public void MarkMatrixAsUpdated()
        {
            needUpdate = false;
        }

        private void SyncMatrix()
        {
            //CMatrix44 mat = ;

            //CMatrix44 matRot = new CMatrix44(0);
            //matRot.FromYPR(rotation.x, rotation.y, rotation.z);
            //matrix.FromPosRotScale(position, matRot, scale);
        }

        private void SyncMatrixRotation()
        {
            needUpdate = true;
            CMatrix44 matRot = new CMatrix44();
            matRot.FromYPR(rotation.x, rotation.y, rotation.z);

            CMatrix44 mat = matrix.ToCMatrix44();
            mat.FromPosRot(position.ToCVec3(), matRot);
            matrix.FromCMatrix44(mat);
        }

        private void SyncMatrixTranslation()
        {
            needUpdate = true;
            CMatrix44 mat = matrix.ToCMatrix44();
            mat.SetTranslation(position.ToCVec3());
            matrix.FromCMatrix44(mat);
            //matrix.SetTranslation(position);
            //matrix.
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
            get { return position.x; }
            set { position.x = value; SyncMatrixTranslation(); }
        }

        public float PosY
        {
            get { return position.y; }
            set { position.y = value; SyncMatrixTranslation(); }
        }

        public float PosZ
        {
            get { return position.z; }
            set { position.z = value; SyncMatrixTranslation(); }
        }

        public float RotX
        {
            get { return rotation.x; }
            set { rotation.x = value; SyncMatrixRotation(); }
        }

        public float RotY
        {
            get { return rotation.y; }
            set { rotation.y = value; SyncMatrixRotation(); }
        }

        public float RotZ
        {
            get { return rotation.z; }
            set { rotation.z = value; SyncMatrixRotation(); }
        }

    }

}
