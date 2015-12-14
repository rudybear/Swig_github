using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace EngineCore
{

    public class Scene
    {
        // fixme
        public List<BaseObject> objects = null;

        private ICore core = null;
        public Camera mainCamera = null;

        public Scene(ICore engineCore)
        {
            objects = new List<BaseObject>();
            mainCamera = new Camera();
            core =  engineCore;

            AddObject(mainCamera);
        }

        public void AddObject(BaseObject obj)
        {
            objects.Add(obj);
        }

        public void DeleteObject(BaseObject obj)
        {
            objects.Remove(obj);
        }

        public void Update()
        {
            foreach (var obj in objects)
            {
                obj.Update();
            }
        }

        public void Render()
        {
            foreach (var obj in objects)
            {
                obj.Render();
            }
        }

        public void Save(string path)
        {
            try
            {
                using (Stream stream = File.Open(path, FileMode.Create))
                {
                    BinaryFormatter bin = new BinaryFormatter();
                    bin.Serialize(stream, objects);
                }
            }
            catch (IOException)
            {
            }
        }

        public void Load(string path)
        {
            try
            {
                using (Stream stream = File.Open(path, FileMode.Open))
                {
                    BinaryFormatter bin = new BinaryFormatter();

                    objects = (List<BaseObject>)bin.Deserialize(stream);

                    foreach (BaseObject obj in objects)
                    {
                        obj.core = core;
                    }
                }
            }
            catch (IOException)
            {
            }
        }
    }
}
