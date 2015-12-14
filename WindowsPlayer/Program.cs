using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;
using EngineCore;

namespace WindowsPlayer
{
    class Program
    {

        public partial class PlayerForm : Form
        {

            static Engine engine = null;

            public PlayerForm()
            {

                engine = new Engine();
                this.Size = new Size(1024, 768);

                if (engine.StartEngine("Engine2 Player", "../../../data/config_mobile.xml?low", this.Handle))
                {
                    engine.LoadGame();
                    engine.GetScene().Load("scene.bin");
                    engine.RunGame();
                    //IEngineEvents events = (IEngineEvents)engine;
                    //events.OnPreFrameUpdate += new EventHandler(OnPreUpdate);
                }
            }
        }

        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new PlayerForm());
        }
    }
}
