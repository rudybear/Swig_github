using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EngineCore;
using EngineCore.Base;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

//using System;
//using System.ComponentModel;
//using System.Windows.Forms;

namespace EngineCore
{


    //public class SaveFileNameEditor : UITypeEditor
    //{
    //    public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context)
    //    {
    //        return UITypeEditorEditStyle.Modal;
    //    }

    //    public override object EditValue(ITypeDescriptorContext context, IServiceProvider provider, object value)
    //    {
    //        if (context == null || context.Instance == null || provider == null)
    //        {
    //            return base.EditValue(context, provider, value);
    //        }

    //        using (SaveFileDialog saveFileDialog = new SaveFileDialog())
    //        {
    //            if (value != null)
    //            {
    //                saveFileDialog.FileName = value.ToString();
    //            }

    //            saveFileDialog.Title = context.PropertyDescriptor.DisplayName;
    //            saveFileDialog.Filter = "All files (*.*)|*.*";
    //            if (saveFileDialog.ShowDialog() == DialogResult.OK)
    //            {
    //                value = saveFileDialog.FileName;
    //            }
    //        }

    //        return value;
    //    }
    //}

    [Serializable()] 
    public class BaseMesh : GameObject
    {
        public string meshName;

        //[Category("File")]
        //[Description("Mesh file")]
        //[EditorAttribute(typeof(System.Windows.Forms.Design.FileNameEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public string MeshName
        {
            get { return meshName; }
            set { meshName = value; LoadMesh(meshName); }
        }

        public BaseMesh()
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


            node.m_Params.SetParam(new Engine2String("Mesh"), new Engine2String(name));
            node.m_Params.SetParam(new Engine2String("Type"), new Engine2String("basemesh"));
            node.m_Params.SetParam(new Engine2String("MaterialsFromFile"), new Engine2String("1"));
           

            IMeshInfo info = core.GetScene().AddCreateMesh(node, 0);

            IntPtr ptr = IMeshInfo.getCPtr(info).Handle;
            mesh = new IBaseMeshInfo(ptr, false);

            mesh.RebuildMesh();
            mesh.SetLodDistance(0, 1000000);

            if (ptr != null)
            {
                string animName = name;
                int dot = animName.LastIndexOf('.');
                animName = animName.Substring(0, dot) + ".uvanim";

                uint num = mesh.LoadUVAnimation(animName);
                if (num != 0XFFFFFFFF)
                {
                    UVAnimationParam anim = new UVAnimationParam();
                    anim.m_bLooped = true;
                    mesh.StartUVAnimation((uint)num, anim);
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
        private IBaseMeshInfo mesh;

    }
}
