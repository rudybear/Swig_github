using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EngineCore
{
    public class RegisteredComponents
    {
        public List<Type> typeObjects = null;

        public RegisteredComponents()
        {
            typeObjects = new List<Type>();
        }
    }


}
