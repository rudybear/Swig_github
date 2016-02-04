using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EngineCore;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using EngineCore.Base;

namespace EngineCore
{
    [Serializable()]
    public class Camera : GameObject
    {

        [NonSerialized()]
        private CCamera camera;

        public float fov;
        public float Fov
        {
            get { return fov; }
            set { fov = value;  SetProjParams(); }
        }

        public float near;
        public float ZNear
        {
            get { return near; }
            set { near = value; SetProjParams(); }
        }

        public float far;
        public float ZFar
        {
            get { return far; }
            set { far = value; SetProjParams(); }
        }

        public float aspect;

        public float Aspect
        {
            get { return aspect; }
            set { aspect = value; SetProjParams(); }
        }

        private void SetProjParams()
        {
            core.GetScene().ProjParams(fov, near, far);
        }
        public Camera()
        {
            onCreated();
        }

        public override void PostLoad()
        {

        }

        public void onCreated()
        {
            camera = new CCamera();
            position.z = 5.0f;
            aspect = 1.0f;
            near = 0.1f;
            far = 20000.0f;
            fov = 60.0f;
            rotation.z = -1.0f;
        }

        [OnDeserializing]
        private void OnDeserializing(StreamingContext c)
        {
            onCreated();
        }

        public override void Update()
        {
            // eye, look, up
            //Vec3 eye = new Vec3(0, 0, 5);
            float dist = 10.0f;
            Vec3 look = new Vec3(position.x + rotation.x* dist, position.y + rotation.y* dist, position.z + rotation.z* dist);
            Vec3 up = new Vec3(0, 1, 0);

            camera.SetViewParams(position.ToCVec3(), look.ToCVec3(), up.ToCVec3());
            core.GetScene().SetCamera(camera);

            //core.GetScene().GetRender().SetTransform(2,  core.GetScene().GetCamera().GetViewMatrix());//(CMatrix44*)&m_Camera->GetViewMatrix());
        }

    }
}
