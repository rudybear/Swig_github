using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EngineCore;
using EngineCore.Base;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

namespace EngineCore
{
    [Serializable()]
    public class AnimationMesh :  GameObject
    {
        public string meshName;
        public string MeshName
        {
            get { return meshName; }
            set { meshName = value; LoadMesh(meshName); }
        }

        public AnimationMesh()
        {

        }

        [OnDeserialized]
        private void OnDeserialized(StreamingContext c)
        {
        }


        public override void PostLoad()
        {
            if (meshName != null)
            {
                LoadMesh(meshName);
            }
        }

        public bool LoadMesh(string name)
        {
            CXmlElement node = new CXmlElement();

            //name = "chars\\hmn_m\\hmn_m.achr";
            node.m_Params.SetParam(new Engine2String("Mesh"), new Engine2String(name));
            node.m_Params.SetParam(new Engine2String("Type"), new Engine2String("animatedmesh"));
            node.m_Params.SetParam(new Engine2String("MaterialsFromFile"), new Engine2String("1"));
           
            
            IMeshInfo info = core.GetScene().AddCreateMesh(node, 0);

            IntPtr ptr = IMeshInfo.getCPtr(info).Handle;
            mesh = new IAnimMeshInfo(ptr, false);
            if (ptr != null)
            {
                mesh.RebuildMesh();
                string animName = name;
                int dot = animName.LastIndexOf('.');
                animName = animName.Substring(0, dot) + ".anim";

                int num = mesh.LoadAnimation(animName);
                if (num != -1)
                {
                    AnimationParam anim = new AnimationParam();
                    anim.m_bLooped = true;
                    mesh.StartAnimation((uint)num, anim);
                }
            }

            return mesh != null;
        }

        public override void Update()
        {
            if (mesh != null)
            {
                if (IsMatrixNeedUpdate())
                {
                    mesh.SetMatrix(matrix.ToCMatrix44());
                    MarkMatrixAsUpdated();
                }
                
                //LoadMesh("test");
            }
        }

        [NonSerialized()]
        private IAnimMeshInfo mesh;

    }
}
