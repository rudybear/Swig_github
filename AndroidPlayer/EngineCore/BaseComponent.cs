using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

namespace EngineCore
{
    [Serializable()]
    public class BaseComponent //: ISerializable
    {
        private int hash;
        static int currentHash = 0;
        public BaseObject parent = null;

        public virtual string ComponentName
        {
            get { return GetType().FullName; }
        }

        public BaseComponent()
        {
            hash = currentHash;
            currentHash++;
        }

        int GetHash()
        {
            return hash;
        }


        public virtual void Update()
        {

        }
    }


    //public class BaseObj
    //{
    //    public string name;
    //    public string Name
    //    {
    //        get { return name; }
    //        set { name = value; }
    //    }
    //}

    //public class TestObj
    //{

    //    public string text;
    //    public string Text
    //    {
    //        get { return text; }
    //        set { text = value; }
    //    }

    //    List<BaseObj> objects; // I want to show this dynamically in property grid

    //    public BaseObj baseObj;
    //    public BaseObj BaseObject
    //    {
    //        get { return baseObj; }
    //        set { baseObj = value; }
    //    }

    //    public TestObj() 
    //    { 
    //        baseObj = new BaseObj();
    //    }
    //}
}
