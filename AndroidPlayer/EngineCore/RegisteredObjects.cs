using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EngineCore
{
    public class RegisteredObjects
    {
        public List<Type> typeObjects = null;

        public RegisteredObjects()
        {
            typeObjects = new List<Type>();
        }
    }
}
