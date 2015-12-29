using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Collections;
using System.Diagnostics;
#if WIN
using System.Drawing;
#endif
using System.Reflection;
using System.IO;
using System.Security.Permissions;
using Android.Util;

namespace EngineCore
{
    //public class BaseComponent
    //{
    //    private int hash;
    //    static int currentHash = 0;

    //    public BaseComponent()
    //    {
    //        hash = currentHash;
    //        currentHash++;
    //    }

    //    int GetHash() 
    //    {
    //        return hash;
    //    }

    //}

    //public class TestComponent : BaseComponent
    //{
    //    public void Update()
    //    {
    //        Console.WriteLine("Update!");
    //    }

    //    public void Start()
    //    {
    //        Console.WriteLine("Start!");
    //    }
    //}

    [Serializable()]
    public class NameComponent : BaseComponent
    {

        public string name = "Name";
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
    }

    [Serializable()]
    public class UILabel : BaseObject
    {
        public int posX = 0;
        public int PosX
        {
            get { return posX;  }
            set { posX = value; }
        }

        public int posY = 0;
        public int PosY
        {
            get { return posY; }
            set { posY = value; }
        }

#if WIN
        public Color color = -1;
        public Color Color
        {
            get { return color; }
            set { color = value; }
        }

#else
        public Int32 color = -1;
        public Int32 Color
        {
            get { return color; }
            set { color = value; }
        }

#endif

        public string text = "empty";
        public string Text
        {
            get { return text; }
            set { text = value; }
        }

        public override void Render()
        {
            if (core.GetScene() != null && core.GetScene().GetRender() != null)
            {
#if WIN
                int colorRGBA = Engine2.Color_RGBA(color.R, color.G, color.B, color.A, ERenderer.eRN_D3D9);
#else
                int colorRGBA = color;// Engine2.Color_RGBA(color.R, color.G, color.B, color.A, ERenderer.eRN_D3D9);
#endif
                core.GetScene().GetRender().CreateGUIObject().DrawText(0, posX, posY, colorRGBA, text);
                core.GetScene().GetRender().CreateGUIObject().DrawTextScaled(0, posX, posY, 10.0f, 10.0f, colorRGBA, text);
            }
        }
    }

    //public class BaseObject
    //{

    //    private List<BaseComponent> objects = null;

    //    public BaseObject()
    //    {
    //        objects = new List<BaseComponent>();
    //    }

    //    public T GetComponent<T>() where T : BaseComponent
    //    {
    //        Type cmp = typeof(T);

    //        foreach (T obj in objects)
    //        {
    //            if (obj.GetType() == cmp)
    //            {
    //                return obj;
    //            }
    //        }

    //        return null;
    //    }

    //    public void AddComponent(BaseComponent component)
    //    {
    //        objects.Add(component);
    //    }
    //}


    public interface IEngineEvents
    {
        event EventHandler OnPreFrameUpdate;
        event EventHandler OnPostFrameUpdate;
    }

    public class Engine : IEngineEvents
    {
        private ICore core = null;
        private Scene scene = null;
        private RegisteredObjects registeredObjects;
        private RegisteredComponents componentsObjects;

        event EventHandler PreUpdateEvent;
        event EventHandler PostUpdateEvent;
        object objectLock = new Object();

        public Assembly dll = null;
        public string gameString = null;

        event EventHandler IEngineEvents.OnPreFrameUpdate
        {
            add
            {
                lock (objectLock)
                {
                    PreUpdateEvent += value;
                }
            }
            remove
            {
                lock (objectLock)
                {
                    PreUpdateEvent -= value;
                }
            }
        }

        event EventHandler IEngineEvents.OnPostFrameUpdate
        {
            add
            {
                lock (objectLock)
                {
                    PostUpdateEvent += value;
                }
            }
            remove
            {
                lock (objectLock)
                {
                    PostUpdateEvent -= value;
                }
            }
        }

        public ICore GetCore()
        {
            return core;
        }

        public Scene GetScene()
        {
            return scene;
        }

        public  RegisteredObjects GetRegisteredObjects()
        {
            return registeredObjects;
        }

        public BaseObject AddObject(string type)
        {
            //objects.Add(obj);
            BaseObject gameObj = (BaseObject)Activator.CreateInstance(Type.GetType(type), null);
            scene.AddObject(gameObj);
            gameObj.core = core;
            //gameObj.AddComponent(new NameComponent());
            return gameObj;
            //                MethodInfo mi = type.GetMethod("Run");
        }


        public void AddComponent(BaseObject obj, string type)
        {
            Type compType = Type.GetType(type);
            BaseComponent gameComponent = (BaseComponent)Activator.CreateInstance(compType, null);
            obj.AddComponent(gameComponent);
        }

        public void AddCustomComponent(BaseObject obj, string type)
        {
            Type compType = dll.GetType(type);
            BaseComponent gameComponent = (BaseComponent)Activator.CreateInstance(compType, null);
            obj.AddComponent(gameComponent);
        }

        public bool StartEngine(string name, string config, IntPtr windowHandle)
        {
            Log.Verbose("Engine2 Android player", "Create Core");
            core = Engine2.CreateCore(eStartGameType.eNoCrashHandling, name);
            Log.Verbose("Engine2 Android player", "Load config");
            if (core.GetConfigFile().LoadConfigFromFile(config) == 0)
            {
                Log.Verbose("Engine2 Android player", "Load config failed");
            }
            else
            {
                Log.Verbose("Engine2 Android player", "Load config successful!");
                Log.Verbose("Engine2 Android player", core.GetConfigFile().GetEffectsWritePath());
            }

#if false
            if (windowHandle.ToInt64() != 0)
            {
                IWindow wnd = core.AddWindow();
                IntPtr hPtr = System.Runtime.InteropServices.Marshal.AllocHGlobal(windowHandle);
                System.Runtime.InteropServices.Marshal.WriteIntPtr(hPtr, windowHandle);

                SWIGTYPE_p_WIN_HWND hWNd = new SWIGTYPE_p_WIN_HWND(hPtr, true);
                wnd.RegisterHWND(hWNd);
            }
            else 
            {
                // TODO
                core.SetInitialWindowParameters(0, 0, 1024, 768, 32, 0);
            }
#endif

            //core.ParseConsoleParams("-render render_ogl.dll");
            IntPtr ptrToNull = System.Runtime.InteropServices.Marshal.AllocHGlobal(sizeof(int));
            SWIGTYPE_p_HINSTANCE hInst = new SWIGTYPE_p_HINSTANCE(ptrToNull, true);
            SWIGTYPE_p_HICON hIcon = new SWIGTYPE_p_HICON(ptrToNull, true);
            core.Init(hInst, name, hIcon);
#if WIN
            Application.Idle += new EventHandler(Application_Idle);
#endif
            scene = new Scene(core);

            registeredObjects = new RegisteredObjects();
            componentsObjects = new RegisteredComponents();

            registeredObjects.typeObjects.Add(Type.GetType("EngineCore.UILabel"));//new Type(EngineCore.UILabel));

            //scene = new BaseObject();
            EngineCore.UILabel label = new EngineCore.UILabel();
            scene.AddObject(label);

            label.text = " Hello, World";
            label.core = core;

            core.GetScene().GetRender().SetShowFPS(true);
            core.GetScene().GetRender().SetAmbientLight(unchecked((int)0xff777777));
            core.GetScene().ProjParams(60.0f, 0.1f, 1000.0f);

            return true;
        }

        private void Application_Idle(Object sender, EventArgs e)
        {
            ApplicationFrame();
        }

        public void ApplicationFrame()
        {
            //scene.GetComponent<LabelComponent>().Render();
            EventHandler handler = PreUpdateEvent;
            if (handler != null)
            {
                handler(this, new EventArgs());
            }
            scene.Update();
            scene.Render();
            core.Frame();

            handler = PostUpdateEvent;
            if (handler != null)
            {
                handler(this, new EventArgs());
            }
        }

        public void UnloadGame()
        {
            if (dll != null)
            {
                //AppDomain.Unload(domain);
                dll = null;
                gameString = "Game unloaded";
            }
        }

        public void LoadGame()
        {
            if (dll != null)
            {
                UnloadGame();
            }

            string dllPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\GameCode.dll";
            //string dllPath = "GameCode.dll";
            dll = Assembly.Load(File.ReadAllBytes(dllPath));
        }

        public void RunGame()
        {
            if (dll != null)
            {
                Type type = dll.GetType("GameCode.GameCodeRoot");
                if (type != null)
                {
                    object gameObj = Activator.CreateInstance(type, null);
                    MethodInfo mi = type.GetMethod("Run");
                    if (mi != null)
                    {
                        gameString = (string)mi.Invoke(gameObj, null);
                    }

                }
            }
        }

    }


    //public class Form1 : Form
    //{

    //    private ICore core = null;
    //    public Button button1;
    //    public Button button2;
    //    public Button button3;

    //    public BaseObject scene = null;
    //    public PropertyGrid propertyGrid = null;
    //    public Panel panel = null;

    //    private Assembly dll = null;
    //    //private AppDomain domain;

    //    private string gameString = null;
    //    private FileSystemWatcher watcher;



    //    public Form1()
    //    {
    //        this.Size = new Size(1024, 768);

    //        button1 = new Button();
    //        button1.Size = new Size(40, 40);
    //        button1.Location = new Point(30, 30);
    //        button1.Text = "Load code";
    //        this.Controls.Add(button1);
    //        button1.Click += new EventHandler(button1_Click);

    //        button2 = new Button();
    //        button2.Size = new Size(40, 40);
    //        button2.Location = new Point(80, 30);
    //        button2.Text = "Unload code";
    //        this.Controls.Add(button2);
    //        button2.Click += new EventHandler(button2_Click);

    //        button3 = new Button();
    //        button3.Size = new Size(40, 40);
    //        button3.Location = new Point(120, 30);
    //        button3.Text = "Exec code";
    //        this.Controls.Add(button3);
    //        button3.Click += new EventHandler(button3_Click);


    //        propertyGrid = new PropertyGrid();
    //        propertyGrid.Size = new Size(200, 768);
    //        propertyGrid.Location = new Point(1024 - 200, 0);
    //        this.Controls.Add(propertyGrid);

    //        panel = new Panel();
    //        panel.Size = new Size(1024 - 200, 768);
    //        this.Controls.Add(panel);

    //        core = Engine2.CreateCore(eStartGameType.eNoCrashHandling, "Hello SWIG and CSharp!");
    //        core.GetConfigFile().LoadConfigFromFile("../../../data/config_mobile.xml?low");

    //        //int val = 1;
    //        IntPtr falsePtr = System.Runtime.InteropServices.Marshal.AllocHGlobal(sizeof(int));
    //        System.Runtime.InteropServices.Marshal.WriteInt32(falsePtr, 0);

    //        //System.IntPtr falsePtr = new System.IntPtr(intPointer);
    //        //SWIGTYPE_p_BOOL boolFalse = new SWIGTYPE_p_BOOL(falsePtr, true);

    //        IWindow wnd = core.AddWindow();
    //        IntPtr hPtr = System.Runtime.InteropServices.Marshal.AllocHGlobal(this.Handle);
    //        System.Runtime.InteropServices.Marshal.WriteIntPtr(hPtr, panel.Handle);

    //        SWIGTYPE_p_WIN_HWND hWNd = new SWIGTYPE_p_WIN_HWND(hPtr, true);
    //        wnd.RegisterHWND(hWNd);

    //        //core.SetInitialWindowParameters(0, 0, 1440, 920, 32, boolFalse);

    //        //IntPtr hInstance = GetModuleHandle(null);

    //        //IntPtr hInstPtr = System.Runtime.InteropServices.Marshal.AllocHGlobal(sizeof(int));
    //        //System.Runtime.InteropServices.Marshal.WriteInt32(falsePtr, hInstPtr);
    //        //IntPtr hInstPtr = System.Runtime.InteropServices.Marshal.GetHINSTANCE(System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0]);
    //        SWIGTYPE_p_HINSTANCE hInst = new SWIGTYPE_p_HINSTANCE(falsePtr, true);
    //        SWIGTYPE_p_HICON hIcon = new SWIGTYPE_p_HICON(falsePtr, true);
    //        core.Init(hInst, "SWIG", hIcon);
    //        Application.Idle += new EventHandler(Application_Idle);

    //        scene = new BaseObject();
    //        LabelComponent label = new LabelComponent();
    //        scene.AddComponent(label);

    //        label.text = " Hello, World";
    //        label.core = core;

    //        //BaseObject obj = new BaseObject();
    //        //TestComponent component = new TestComponent();
    //        //obj.AddComponent(component);
    //        //obj.GetComponent<TestComponent>().Update();
    //        //obj.GetComponent<TestComponent>().Start();

    //        propertyGrid.SelectedObject = label;

    //        string exePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
    //        Directory.SetCurrentDirectory(exePath);

    //        Run();
    //        LoadGame();
    //        RunGame();
    //        //domain = AppDomain.CreateDomain("GameCode");
    //    }

    //    private void Application_Idle(Object sender, EventArgs e)
    //    {
    //        if (gameString != null)
    //            scene.GetComponent<LabelComponent>().Text = gameString;
    //        else
    //            scene.GetComponent<LabelComponent>().Text = "No string";

    //        scene.GetComponent<LabelComponent>().Render();
    //        core.Frame();
    //    }
    //    //class X
    //    //http://habrahabr.ru/post/267515/
    //    //{
    //    //    class A
    //    //    {
    //    //        public int f1;
    //    //        public int p1 { get; set; }
    //    //        public int m1(string s, int i) { return (0); }
    //    //    }
    //    //    X()
    //    //    {
    //    //        A a = new A();
    //    //        Type t = a.GetType();

    //    //        FieldInfo fi = t.GetField("f1");
    //    //        object of = fi.GetValue(a);

    //    //        PropertyInfo pi = t.GetProperty("p1");
    //    //        MethodInfo mpi = pi.GetGetMethod();
    //    //        object ompi = mpi.Invoke(a, null);

    //    //        MethodInfo mi = t.GetMethod("m1");
    //    //        object om = mi.Invoke(a, new object[] { "param1", 2 });
    //    //    }
    //    //}

    //    private void UnloadGame()
    //    {
    //        if (dll != null)
    //        {
    //            //AppDomain.Unload(domain);
    //            dll = null;
    //            gameString = "Game unloaded";
    //        }
    //    }

    //    private void button2_Click(object sender, EventArgs e)
    //    {
    //        UnloadGame();
    //    }


    //    private void button1_Click(object sender, EventArgs e)
    //    {
    //        //if (dll != null)
    //        //{
    //        //    AppDomain.Unload(domain);
    //        //    dll = null;
    //        //}

    //        LoadGame();
    //        button3_Click(sender, e);
    //    }

    //    private void LoadGame()
    //    {
    //        if (dll != null)
    //        {
    //            UnloadGame();
    //        }

    //        string dllPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\GameCode.dll";
    //        //string dllPath = "GameCode.dll";
    //        dll = Assembly.Load(File.ReadAllBytes(dllPath));
    //    }

    //    private void button3_Click(object sender, EventArgs e)
    //    {
    //        RunGame();
    //    }

    //    private void RunGame()
    //    {
    //        if (dll != null)
    //        {
    //            Type type = dll.GetType("GameCode.GameCodeRoot");
    //            if (type != null)
    //            {
    //                object gameObj = Activator.CreateInstance(type, null);
    //                MethodInfo mi = type.GetMethod("Run");
    //                if (mi != null)
    //                {
    //                    gameString = (string)mi.Invoke(gameObj, null);
    //                }

    //            }
    //        }
    //    }


    //    [STAThread]
    //    static void Main()
    //    {
    //        Application.EnableVisualStyles();
    //        Application.Run(new Form1());
    //    }

    //    [PermissionSet(SecurityAction.Demand, Name = "FullTrust")]
    //    public void Run()
    //    {
    //        // Create a new FileSystemWatcher and set its properties.
    //        watcher = new FileSystemWatcher();
    //        watcher.Path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
    //        /* Watch for changes in LastAccess and LastWrite times, and
    //           the renaming of files or directories. */
    //        watcher.NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite
    //           | NotifyFilters.FileName | NotifyFilters.DirectoryName;
    //        // Only watch text files.
    //        watcher.Filter = "*.dll";

    //        // Add event handlers.
    //        watcher.Changed += new FileSystemEventHandler(OnChanged);
    //        watcher.Created += new FileSystemEventHandler(OnCreated);
    //        watcher.Deleted += new FileSystemEventHandler(OnDeleted);
    //        watcher.Renamed += new RenamedEventHandler(OnRenamed);

    //        // Begin watching.
    //        watcher.EnableRaisingEvents = true;
    //    }

    //    // Define the event handlers.
    //    private void OnChanged(object source, FileSystemEventArgs e)
    //    {
    //        // Specify what is done when a file is changed, created, or deleted.
    //        //Console.WriteLine("File: " + e.FullPath + " " + e.ChangeType);
    //        LoadGame();
    //        RunGame();
    //    }

    //    private  void OnCreated(object source, FileSystemEventArgs e)
    //    {
    //        // Specify what is done when a file is changed, created, or deleted.
    //        //Console.WriteLine("File: " + e.FullPath + " " + e.ChangeType);
    //    }

    //    private  void OnDeleted(object source, FileSystemEventArgs e)
    //    {
    //        // Specify what is done when a file is changed, created, or deleted.
    //        //Console.WriteLine("File: " + e.FullPath + " " + e.ChangeType);
    //        UnloadGame();
    //    }

    //    private  void OnRenamed(object source, RenamedEventArgs e)
    //    {
    //        // Specify what is done when a file is renamed.
    //        //Console.WriteLine("File: {0} renamed to {1}", e.OldFullPath, e.FullPath);
    //    }
    //}
}