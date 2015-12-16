﻿using System;
using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;
using Android.Content.PM;
using EngineCore;
using Android.Util;
using Java.Interop;

namespace XamarinAndroid
{
    [Activity(Label = "XamarinAndroid",
        MainLauncher = true,
        Icon = "@drawable/icon",
        ConfigurationChanges = ConfigChanges.Orientation | ConfigChanges.KeyboardHidden
#if __ANDROID_11__
		,HardwareAccelerated=false
#endif
        )]
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

        [Export]
        public void StartEngine()
        {
            Log.Verbose("Engine2 Android player", "Start Engine");
            engine = new Engine();

            if (engine.StartEngine("Engine2 Player", "sdcard/Fish/config_mobile.xml?low", this.Handle))
            {
                Log.Verbose("Engine2 Android player", "Start Engine completed!");
            }

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
    }
}
