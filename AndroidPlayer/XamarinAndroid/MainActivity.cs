using System;
using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;
using Android.Content.PM;
using System.Collections.Generic;
using EngineCore;
using EngineCore.Base;
using Android.Util;
using Java.Interop;

namespace XamarinAndroid
{

    struct Point
    {
        public int X;
        public int Y;
    };

    [Activity(Label = "XamarinAndroid",
        MainLauncher = true,
        Icon = "@drawable/icon",
        ConfigurationChanges = ConfigChanges.Orientation | ConfigChanges.KeyboardHidden,
        ScreenOrientation = ScreenOrientation.Landscape,
        Theme = "@android:style/Theme.Black.NoTitleBar.Fullscreen"
#if __ANDROID_11__
        , HardwareAccelerated=false
#endif
        )]
    [MetaData("android.app.lib_name", Value = "Engine2")]
    public class MainActivity : NativeActivity
    {
        //GLView1 view;
        static Engine engine = null;
        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            Log.Verbose("Engine2 Android player - java", "OnCreate");
            //engine = new Engine();

            //if (engine.StartEngine("Engine2 Player", "sdcard/Fish/config_mobile.xml?low", this.Handle))
            //{
            //    engine.LoadGame();
            //    engine.GetScene().Load("scene.bin");
            //    engine.RunGame();
            //    //IEngineEvents events = (IEngineEvents)engine;
            //    //events.OnPreFrameUpdate += new EventHandler(OnPreUpdate);
            //}

            // Create our OpenGL view, and display it
            //view = new GLView1(this);
            //SetContentView(view);
        }

        //[Export]
        public static String META_DATA_LIB_NAME = "android.app.lib_name";

        [Export]
        public void StartEngine()
        {
            Log.Verbose("Engine2 Android player", "Start Engine");
            engine = new Engine();

            if (engine.StartEngine("Engine2 Player", "mnt/sdcard/Fish/config_mobile.xml?low", this.Handle))
            {
                Log.Verbose("Engine2 Android player", "Start Engine completed!");
                // engine.GetCore().GetScene().GetRender().ReCreateScreen(0, 0, 0, 0);
                //engine.GetScene().Load("mnt/sdcard/Fish/scenes/scene.bin");
                this.CreateScene();
            }

        }

        [Export]
        public void FrameEngine()
        {
            OnPreUpdate(this, new EventArgs());
            engine.ApplicationFrame();
        }
        protected override void OnPause()
        {
            base.OnPause();
            //view.Pause();
        }

        protected override void OnResume()
        {
            base.OnResume();
            //view.Resume();
        }


        Camera camera = null;
        List<BaseMesh> backgrounds;


        float ToRad(float deg)
        {
            return deg * (float)Math.PI / 180.0f;
        }

        float cameraYaw = -100.0f;
        float cameraPitch = 3.0f;

        float defCameraYaw = -100.0f;
        float defCameraPitch = 3.0f;

        private void SetupCamera(float yaw, float pitch)
        {
            CMatrix44 mat = new CMatrix44();
            mat.FromYPR(ToRad(yaw), ToRad(pitch), 0);
            CVec3 dir = new CVec3();
            dir.x = 0.0f;
            dir.y = 0.0f;
            dir.z = 1.0f;

            dir = dir.TransformNormal(mat);

            camera.RotX = dir.x;
            camera.RotY = dir.y;
            camera.RotZ = dir.z;
        }

        private void CreateCamera()
        {
            camera = (Camera)engine.AddObject("EngineCore.Camera");
            camera.position = new EngineCore.Base.Vec3(0, -13, 0);

            //camera.Fov = 1.57f;

            SetupCamera(cameraYaw, cameraPitch);

        }

        private BaseMesh CreateModel(string name)
        {
            BaseMesh model = (BaseMesh)engine.AddObject("EngineCore.BaseMesh");
            model.MeshName = name;
            return model;
        }

        static Random rnd = new Random();
        private float Random_Float(float min, float max)
        {
            return (float)rnd.NextDouble() * (max - min) + min;
        }
        private void CreateModel(string name, float scale, int count, bool faceCamera, Vec3 xyz, float cr1, float cr2)
        {
            for (int i = 0; i < count; ++i)
            {
                BaseMesh model = CreateModel(name);


                float angle = Random_Float(0, (float)Math.PI * 2.0f);
                float radius = Random_Float(cr1, cr2);

                model.PosX = xyz.x + (float)Math.Cos(angle) * radius;
                model.PosY = xyz.y;
                model.PosZ = xyz.z + (float)Math.Sin(angle) * radius;

                model.scale = new Vec3(scale, scale, scale);

                float dx = model.PosX - camera.PosX;
                float dz = model.PosZ - camera.PosZ;
                float camAngle = 270.0f * 3.14f / 180.0f + (float)Math.Atan2(dz, dx);// * 180.0f / 3.14f;

                model.RotX = camAngle;

            }
        }

        private void CreateBackground()
        {
            backgrounds = new List<BaseMesh>();

            BaseMesh back = CreateModel("scenes\\ff_back_scene01.echr");

            CreateModel("objects\\ff_weed01_01.schr", 0.75f, 5, true, new Vec3(0, -22, 0), 20, 80);
            CreateModel("objects\\ff_weed01_02.schr", 0.75f, 5, true, new Vec3(0, -22, 0), 20, 80);
            CreateModel("objects\\ff_weed01_03.schr", 0.75f, 5, true, new Vec3(0, -22, 0), 20, 80);
            CreateModel("objects\\ff_weed01a_01.schr", 0.75f, 5, true, new Vec3(0, -22, 0), 20, 80);
            CreateModel("objects\\ff_weed01a_02.schr", 0.75f, 5, true, new Vec3(0, -22, 0), 20, 80);
            CreateModel("objects\\ff_weed01a_03.schr", 0.75f, 5, true, new Vec3(0, -22, 0), 20, 80);

            unchecked
            {
                int col = (int)4279009217;
                engine.GetCore().GetScene().GetRender().SetupFog(col, col, (int)3724541951, 0.0f, 0.0f, 0.0156862754f, 0.901960790f);
                engine.GetCore().GetScene().GetRender().EnableFog(1);
            }
        }


        #region FISH


        public struct SPlacement
        {
            public SPlacement(int a, int b, int c)
            {
                m_radiusIndex = a;
                m_levelIndex = b;
                m_phaseIndex = c;
            }
            public int m_radiusIndex;
            public int m_levelIndex;
            public int m_phaseIndex;
        };

        public class Fish
        {
            public BaseMesh m_shadowModel;
            public AnimationMesh m_model;
            public SPlacement m_place;
            public int m_phaseMod;
        }

        List<Fish> fishes;

        private AnimationMesh CreateFishModel(string name)
        {
            AnimationMesh model = (AnimationMesh)engine.AddObject("EngineCore.AnimationMesh");
            model.MeshName = name;

            return model;
        }

        private SPlacement SelectPlacement(int levelMin, int levelMax)
        {
            if (m_freePlacements.Count == 0)
            {
                return new SPlacement(-1, -1, -1);
            }

            List<int> variants = new List<int>();

            for (int i = 0; i < m_freePlacements.Count - 1; ++i)
            {
                if (m_freePlacements[i].m_levelIndex >= levelMin && m_freePlacements[i].m_levelIndex <= levelMax)
                    variants.Add(i);
            }

            if (variants.Count == 0)
                return new SPlacement(-1, -1, -1);

            int index = rnd.Next(0, variants.Count - 1);

            SPlacement ret = m_freePlacements[variants[index]];
            m_freePlacements.RemoveAt(variants[index]);

            return ret;
        }
        private void CreateFish(string name, int count, int levelMin = -1, int levelMax = -1)
        {
            for (int i = 0; i < count; ++i)
            {
                Fish fish = new Fish();

                fish.m_model = CreateFishModel(name);


                fish.m_model.scale = new Vec3(3.54f, 3.54f, 3.54f);
                fish.m_model.PosX = 5.0f;
                fish.m_model.PosY = -22.0f;
                fish.m_model.PosZ = -5.0f;

                fish.m_place = SelectPlacement(levelMin, levelMax);
                fish.m_phaseMod = rnd.Next(-15, 15);

                fish.m_shadowModel = CreateModel("fx/fx_decal_shadow01.schr");
                fish.m_shadowModel.scale = new Vec3(3.54f, 3.54f, 3.54f);

                fishes.Add(fish);
            }
        }
        private void CreateFishes()
        {
            fishes = new List<Fish>();

            CreateFish("fishes/oceanheart01_lo.achr", 10, 0, 1);
            CreateFish("fishes/oceanheart01_md.achr", 10, 2, 3);
            CreateFish("fishes/oceanheart01_hi.achr", 10, 4, 5);
            CreateFish("fishes/oceanheart02_lo.achr", 10, 0, 1);
            CreateFish("fishes/oceanheart02_md.achr", 10, 2, 3);
            CreateFish("fishes/oceanheart02_hi.achr", 10, 4, 5);


            CreateFish("fishes/atlanticshark01_lo.achr", 10, 0, 1);
            CreateFish("fishes/atlanticshark01_md.achr", 10, 2, 3);
            CreateFish("fishes/atlanticshark01_hi.achr", 10, 4, 5);
            CreateFish("fishes/atlanticshark02_lo.achr", 10, 0, 1);
            CreateFish("fishes/atlanticshark02_md.achr", 10, 2, 3);
            CreateFish("fishes/atlanticshark02_hi.achr", 10, 4, 5);

        }

        #endregion

        public const int MAX_RADIUS = 2;
        public const int MAX_LEVELS = 6;
        public const int MAX_PHASES = 10;

        public float[] m_radiuses;
        public float[] m_levels;
        public int[] m_phases;

        public int m_timer;
        public const int TIME = 70000;

        List<SPlacement> m_freePlacements;
        public void CreateData()
        {
            m_timer = 0;

            m_radiuses = new float[MAX_RADIUS];
            for (int i = 0; i < MAX_RADIUS; ++i)
                m_radiuses[i] = 34.0f + i * 2.0f;

            m_levels = new float[MAX_LEVELS];
            for (int i = 0; i < MAX_LEVELS; ++i)
                m_levels[i] = -18.0f + i * 2.0f;

            m_phases = new int[MAX_PHASES];
            for (int i = 0; i < MAX_PHASES; ++i)
                m_phases[i] = 360 * i / MAX_PHASES;

            m_freePlacements = new List<SPlacement>();
            for (int i = 0; i < MAX_RADIUS; ++i)
            {
                for (int j = 0; j < MAX_LEVELS; ++j)
                {
                    for (int k = 0; k < MAX_PHASES; ++k)
                    {
                        SPlacement p = new SPlacement();
                        p.m_levelIndex = j;
                        p.m_radiusIndex = i;
                        p.m_phaseIndex = k;
                        m_freePlacements.Add(p);
                    }
                }
            }

        }
        private void CreateScene()
        {

            //
            IDebugInformationManager dbManager = engine.GetCore().GetDebugInformationManager();
            dbManager.SetDebugParamInt("UseSun", 1);

            CreateData();
            CreateCamera();
            CreateBackground();
            CreateFishes();

        }

        bool needInit = true;
        private bool mouseDown = false;
        private Point mouseCapturedPos;
        private Point mouseCurrentPos;
        private Point curDistances;

        private void ProcessCamera(double dt)
        {
            if (mouseDown)
            {
                //int distX = mouseCapturedPos.X - mouseCurrentPos.X;

                cameraYaw += (float)curDistances.X * (float)dt * 15.0f;

                cameraPitch -= (float)curDistances.Y * (float)dt * 5.0f;

                if (cameraPitch < -45.0f)
                    cameraPitch = -45.0f;

                if (cameraPitch > 45.0f)
                    cameraPitch = 45.0f;

                SetupCamera(cameraYaw, cameraPitch);
            }
        }

        void OnPreUpdate(object sender, EventArgs e)
        {

            if (engine != null && engine.GetCore() != null && engine.GetCore().GetScene().GetRender() != null)
            {


                if (needInit && engine.GetCore().GetScene().GetWeatherSystem() != null && engine.GetCore().GetScene().GetWeatherSystem().GetSun() != null)
                {
                    engine.GetCore().GetScene().GetRender().SetAmbientLight(unchecked((int)7113100));

                    ISun sun = engine.GetCore().GetScene().GetWeatherSystem().GetSun();

                    if (sun.GetLight() != null)
                    {
                        sun.GetLight().SetVisibility(true);
                        sun.GetLight().SetDiffuse(0.743529439f, 0.762352943f, 0.693333328f);
                        sun.SetSunThetaPhi(0.197395504f, 0.0f);
                        sun.GetLight().SetDirection(new Vec3(0.196116135f, 0.980580688f, 0.0f).ToCVec3());

                        needInit = false;
                    }
                }


                double dt = engine.GetCore().GetScene().GetRender().GetElapsedTime();

                ProcessCamera(dt);

                m_timer += (int)Math.Round(dt * 1000.0);

                if (m_timer > TIME)
                    m_timer -= TIME;

                float t = m_timer / (float)TIME;

                float defAngle = -110.0f * 3.14f / 180.0f;
                float m_allRot = -0.4f;
                // update fishes
                foreach (Fish fish in fishes)
                {
                    if (fish.m_place.m_radiusIndex < 0 || fish.m_place.m_levelIndex < 0 || fish.m_place.m_phaseIndex < 0)
                        continue;

                    int fishPhase = m_phases[fish.m_place.m_phaseIndex] + fish.m_phaseMod;
                    float phase = 2 * t + fishPhase / 180.0f;

                    float r = m_radiuses[fish.m_place.m_radiusIndex];

                    float x = (float)Math.Cos(phase * 3.14f) * r / 3 + (float)Math.Sin(defAngle) * 42;
                    float z = (float)Math.Sin(phase * 3.14f) * r * 1.5f + (float)Math.Cos(defAngle) * 42;
                    float h = m_levels[fish.m_place.m_levelIndex];

                    float x1 = -(float)Math.Sin(phase * 3.14f) * r / 3.5f;
                    float z1 = (float)Math.Cos(phase * 3.14f) * r * 1.5f;
                    float rotAngle = m_allRot;//-3.14f/6.0f;//( m_camRotDefault.yaw - 90 ) * 3.14f / 180.0f;
                    float bx = x;
                    x = x * (float)Math.Cos(rotAngle) + z * (float)Math.Sin(rotAngle);
                    z = bx * -(float)Math.Sin(rotAngle) + z * (float)Math.Cos(rotAngle);

                    float angle = ((float)Math.Atan2(x1, z1) + rotAngle);// * 180 / 3.14f;

                    fish.m_model.PosX = x;
                    fish.m_model.PosY = h;
                    fish.m_model.PosZ = z;
                    fish.m_model.RotX = angle + 3.1415f;

                    fish.m_shadowModel.PosX = x;
                    fish.m_shadowModel.PosY = -19.90f;
                    fish.m_shadowModel.PosZ = z;

                    fish.m_shadowModel.RotX = angle + 3.1415f;

                    //fish.m_shadowModel.SetPos(x, -19.90f, z);

                    //fish.m_shadowModel.SetRot(180 + angle, 0, 0);
                }

            }
        }

    }
}

