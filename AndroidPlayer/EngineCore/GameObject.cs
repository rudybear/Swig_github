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


        private CMatrix44 matRot;
        private CVec3 cPos;
        private CVec3 cScl;
        private bool needUpdate;


        public GameObject()
        {
            matrix = new Matrix44();
            matrix.SetIdentity();
            matrix.ToCMatrix44();

            matRot = new CMatrix44();

            position = new Vec3();
            cPos = new CVec3();
            //position.Set(0,0,0);

            rotation = new Vec3();
            //rotation.Set(0,0,0);

            scale = new Vec3();
            scale.x = scale.y = scale.z = 1.0f;
            cScl = new CVec3();

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
            
            matRot.FromYPR(rotation.x, rotation.y, rotation.z);

            cPos.Set(position.x, position.y, position.z);
            cScl.Set(scale.x, scale.y, scale.z);


            matrix.cMat44.FromPosRotScale(cPos, matRot, cScl);
            //matrix.FromCMatrix44(mat);
        }

        private void SyncMatrixTranslation()
        {
            needUpdate = true;
            //CMatrix44 mat = matrix.ToCMatrix44();
            cPos.Set(position.x, position.y, position.z);
            matrix.cMat44.SetTranslation(cPos);
            //matrix.FromCMatrix44(mat);
            //matrix.SetTranslation(position);
            //matrix.
        }

        private void SyncMatrixScale()
        {
            needUpdate = true;
            SyncMatrixRotation();
            //CMatrix44 mat = matrix.ToCMatrix44();
            //mat.SetScale(scale.ToCVec3());
            //matrix.FromCMatrix44(mat);
        }


        public void SetYPRPos(float yaw, float pitch, float roll, float x, float y, float z )
        {
            needUpdate = true;
           // CMatrix44 mat = matrix.ToCMatrix44();
            rotation.x = yaw;
            rotation.y = pitch;
            rotation.z = roll;
            position.x = x;
            position.y = y;
            position.z = z;

            SyncMatrixRotation();



            //mat.FromPosRotScale(position.ToCVec3(), matRot, scale.ToCVec3());
            //mat.FromYPR(rotation.x, rotation.y, rotation.z);
            //mat.SetTranslation(position.ToCVec3());
            //matrix.FromCMatrix44(mat);
            //matrix._41 = x;
            //matrix._42 = y;
            //matrix._43 = z;
        }
        //public void SetPosition(CVec3 position)
        //{
        //    //matrix.SetTranslation(position);
        //}

        //CVec3 GetPosition()
        //{
        //    return new CVec3();// matrix.GetTranslation();
        //}

        //public void SetScale(CVec3 scale)
        //{

        //}


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

        public float ScaleX
        {
            get { return scale.x; }
            set { scale.x = value; SyncMatrixScale(); }
        }

        public float ScaleY
        {
            get { return scale.y; }
            set { scale.y = value; SyncMatrixScale(); }
        }

        public float ScaleZ
        {
            get { return scale.z; }
            set { scale.z = value; SyncMatrixScale(); }
        }

    }

}
