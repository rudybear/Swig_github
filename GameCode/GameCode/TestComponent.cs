using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using EngineCore;

namespace GameCode
{
    [Serializable()]
    class TestComponent : BaseComponent
    {
        public string hello = "hello, world";
        public string Hello
        { get; set; }

        public override void Update()
        {
            UILabel label = (UILabel)parent;//. GetComponent<UILabel>();

            NameComponent nameComp = parent.GetComponent<NameComponent>();
            if (nameComp != null)
            {
                nameComp.Name = "Fuck this name!";
            }
            

            if (label != null)
            {
                Random r = new Random();
                int rInt = r.Next(0, 255); //for ints
#if WIN
                label.Color = Color.FromArgb(255, rInt, 1, 1);
#endif
            }
            
        }
    }
}
