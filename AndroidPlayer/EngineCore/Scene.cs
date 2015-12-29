using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
//using System.Runtime.Serialization.Formatters.Js;
//using System.Xml.Serialization;
//using System.Runtime.Serialization.Formatters.;
using Newtonsoft.Json;
using Newtonsoft.Json.Utilities;
using Newtonsoft.Json.Serialization;

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
            core = engineCore;
            mainCamera = new Camera();
            mainCamera.core = core;

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

        //public void Save(string path)
        //{
        //    try
        //    {
        //        //var ser = new XmlSerializer(objects.GetType());
        //        //using (var stream = new FileStream(path+".xml", FileMode.Create))
        //        //    ser.Serialize(stream, this);

        //        using (Stream stream = File.Open(path, FileMode.Create))
        //        {
        //            BinaryFormatter bin = new BinaryFormatter();
        //            bin.Serialize(stream, objects);
        //        }
        //    }
        //    catch (IOException)
        //    {
        //    }
        //}

        //public void Load(string path)
        //{
        //    try
        //    {
        //        using (Stream stream = File.Open(path, FileMode.Open))
        //        {
        //            BinaryFormatter bin = new BinaryFormatter();

        //            objects = (List<BaseObject>)bin.Deserialize(stream);

        //            foreach (BaseObject obj in objects)
        //            {
        //                obj.core = core;
        //                obj.PostLoad();
        //            }
        //        }
        //    }
        //    catch (IOException)
        //    {
        //    }
        //}

        public void Save(string path)
        {
            try
            {
#if false
                using (Stream stream = File.Open(path, FileMode.Create))
                {
                    BinaryFormatter bin = new BinaryFormatter();
                    bin.Serialize(stream, objects);
                }
#endif

                var jsonSerializerSettings = new JsonSerializerSettings()
                {
                    PreserveReferencesHandling = PreserveReferencesHandling.Objects,
                    MissingMemberHandling = MissingMemberHandling.Error,
                    TypeNameHandling = TypeNameHandling.All
                };

                string json = JsonConvert.SerializeObject(objects, Formatting.Indented, jsonSerializerSettings);
                File.WriteAllText(path, json);
            }
            catch (IOException)
            {
            }
        }

        public void Load(string path)
        {
            try
            {
#if false
                using (Stream stream = File.Open(path, FileMode.Open))
                {
                    BinaryFormatter bin = new BinaryFormatter();
                    objects = (List<BaseObject>)bin.Deserialize(stream);
                    foreach (BaseObject obj in objects)
                    {
                        obj.core = core;
                        obj.PostLoad();
                    }
                }
#endif
                List<string> errors = new List<string>();
                ITraceWriter traceWriter = new MemoryTraceWriter();

                var jsonSerializerSettings = new JsonSerializerSettings()
                {
                    // TraceWriter = traceWriter,
                    PreserveReferencesHandling = PreserveReferencesHandling.Objects,
                    //Error = delegate(object sender, ErrorEventArgs args)
                    //{
                    //    errors.Add(args.ErrorContext.Error.Message);
                    //    args.ErrorContext.Handled = true;
                    //},
                    MissingMemberHandling = MissingMemberHandling.Error,
                    TypeNameHandling = TypeNameHandling.All
                };

                objects = JsonConvert.DeserializeObject<List<BaseObject>>(File.ReadAllText(path), jsonSerializerSettings);
                //Console.WriteLine(traceWriter);

                foreach (BaseObject obj in objects)
                {
                    obj.core = core;
                    obj.PostLoad();
                }
            }
            catch (IOException)
            {
            }
        }
    }
}
