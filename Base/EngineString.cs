using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EngineCore.Base
{
    class EngineString
    {
        //private string str;
        SWIGTYPE_p_Engine2__String engineStr;

        public EngineString(string str)
        {
            SetString(str);
        }

        private void Clear()
        {
            if (engineStr == null)
            {
                System.Runtime.InteropServices.Marshal.FreeHGlobal(SWIGTYPE_p_Engine2__String.getCPtr(engineStr).Handle);
                engineStr = null;
            }
        }

        public void SetString(string str)
        {
            int len = str.Length;
            IntPtr ptrToNull = System.Runtime.InteropServices.Marshal.AllocHGlobal(len);
            byte[] array = Encoding.ASCII.GetBytes(str);
            System.Runtime.InteropServices.Marshal.Copy(array, 0, ptrToNull, len);
            engineStr = new SWIGTYPE_p_Engine2__String(ptrToNull, true);
            //SWIGTYPE_p_HINSTANCE hInst = new SWIGTYPE_p_HINSTANCE(ptrToNull, true);
        }

        public SWIGTYPE_p_Engine2__String ToEngineString()
        {
            return engineStr;
        }
    }
}
