using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;
using System.Diagnostics;
using System.Reflection;
using System.IO;
using System.Security.Permissions;
using EngineCore;

namespace EditorCore
{
    public partial class EditorMainForm : Form
    {

        private FileSystemWatcher watcher;
        Engine engine = null;

        BaseObject selectedObject = null;

        public EditorMainForm()
        {
            InitializeComponent();

            engine = new Engine();

            if (engine.StartEngine("Engine2 Editor", "../../../restest/config.xml?low", this.renderMainWindow.Handle))
            {
                FillObjectsList();
                FillSceneObjects();
                UpdateComponents();
                engine.LoadGame();
                Run();
                IEngineEvents events = (IEngineEvents)engine;
                events.OnPreFrameUpdate += new EventHandler(OnPreUpdate);
            }
        }

        void OnPreUpdate(object sender, EventArgs e)
        {
            try
            {
                engine.RunGame();
            }
            catch 
            {
            };

            if (engine.gameString != null)
            {
                Text = "Engine2 Editor. Game status - " + engine.gameString;
            }
            
        }


        public static Bitmap GetImageByName(string imageName)
        {
            System.Reflection.Assembly asm = System.Reflection.Assembly.GetExecutingAssembly();
            string resourceName = asm.GetName().Name + ".Properties.Resources";
            var rm = new System.Resources.ResourceManager(resourceName, asm);
            return (Bitmap)rm.GetObject(imageName);

        }

        public void FillObjectsList()
        {
            //TreeNode treeNode = new TreeNode("Windows");
            //sceneView.Nodes.Add(treeNode);
            ////
            //// Another node following the first node.
            ////
            //treeNode = new TreeNode("Linux");
            //sceneView.Nodes.Add(treeNode);
            ////
            //// Create two child nodes and put them in an array.
            //// ... Add the third node, and specify these as its children.
            ////
            //TreeNode node2 = new TreeNode("C#");
            //TreeNode node3 = new TreeNode("VB.NET");
            //TreeNode[] array = new TreeNode[] { node2, node3 };
            ////
            //// Final node.
            ////
            //treeNode = new TreeNode("Dot Net Perls", array);
            //sceneView.Nodes.Add(treeNode);

            //string[] arr = new string[4];

            componentsView.View = View.LargeIcon;
            componentsView.GridLines = true;
            componentsView.FullRowSelect = true;
            ImageList ilist = new ImageList();
            ilist.ImageSize = new Size(48, 48);
            ilist.Images.Add(GetImageByName("folder"));

            componentsView.LargeImageList = ilist;

            for (int i = 0; i < engine.GetRegisteredObjects().typeObjects.Count(); ++i)
            {
                ListViewItem item = new ListViewItem(engine.GetRegisteredObjects().typeObjects[i].FullName);
                item.ImageIndex = 0;
                componentsView.Items.Add(item);
            }


            //EngineCore.TestObj testObj = new EngineCore.TestObj();
            //propertyPanel.SelectedObject = testObj;

        }

        Button addComponentButton = null;

        private void SelectObjectProperties(BaseObject baseObj)
        {
            ClearPropertyPanel();

            {
                PropertyGrid propertyGrid = new PropertyGrid();
                propertyGrid.Location = new Point(0, 0);
                propertyGrid.SelectedObject = baseObj;
                propertyGrid.Size = new Size(propertyPanel.ClientSize.Width-2, 200);
                //propertyGrid.AutoSize=true ;//SetAutoSizeMode(AutoSizeMode.GrowAndShrink);
                //propertyGrid.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
                //propertyGrid.Dock = DockStyle.Fill;
                propertyGrid.ExpandAllGridItems();
                propertyPanel.Controls.Add(propertyGrid);
            }

            foreach (BaseComponent component in baseObj.objects)
            {
                PropertyGrid propertyGrid = new PropertyGrid();
                propertyGrid.SelectedObject = component;
                propertyGrid.Size = new Size(propertyPanel.ClientSize.Width-2, 200);
                propertyGrid.Location = new Point(0, 0);
                //propertyGrid.Dock = DockStyle.Fill;
                //propertyGrid.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
                propertyGrid.ExpandAllGridItems();
                propertyPanel.Controls.Add(propertyGrid);
            }

            addComponentButton = new Button();
            addComponentButton.Size = new Size(propertyPanel.ClientSize.Width - 2, 20);
            addComponentButton.Location = new Point((propertyPanel.ClientSize.Width - 80) / 2, 0);
            addComponentButton.Text = "Add Component";
            addComponentButton.Click += new EventHandler(addComponent_Click);
            propertyPanel.Controls.Add(addComponentButton);
            //        button2 = new Button();
            //        
            //        button2.Location = new Point(80, 30);
            //        button2.Text = "Unload code";
            //        this.Controls.Add(button2);
            //        button2.Click += new EventHandler(button2_Click);
        }

        private void addComponent_Click(object sender, EventArgs e)
        {
            if (engine.dll != null)
            {

                ContextMenu buttonMenu = new ContextMenu();

                Module m = engine.GetType().Module;

                foreach (Type type in m.GetTypes())
                {
                    if (type.IsSubclassOf(typeof(EngineCore.BaseComponent)))
                    {
                        MenuItem menuItem = new MenuItem(type.FullName);
                        menuItem.Tag = type.FullName;
                        menuItem.Click += new EventHandler(componentMenu_Click);
                        buttonMenu.MenuItems.Add(menuItem);
                    }
                    //Console.WriteLine(type.FullName);
                }

                buttonMenu.MenuItems.Add("-");

                foreach (Type type in engine.dll.GetTypes())
                {
                    if (type.IsSubclassOf(typeof(EngineCore.BaseComponent)))
                    {
                        MenuItem menuItem = new MenuItem(type.FullName);
                        menuItem.Tag = type.FullName;
                        menuItem.Click += new EventHandler(customComponentMenu_Click);
                        buttonMenu.MenuItems.Add(menuItem);
                    }
                    //Console.WriteLine(type.FullName);
                }

                buttonMenu.Show(addComponentButton, new System.Drawing.Point(20, 20));
            }
            //
            //Declare the menu items and the shortcut menu.
        //    MenuItem[] menuItems = new MenuItem[]{new MenuItem("Some Button Info"), 
        //new MenuItem("Some Other Button Info"), new MenuItem("Exit")};

        }

        private void componentMenu_Click(object sender, EventArgs e)
        {
            engine.AddComponent(selectedObject, (string)((MenuItem)sender).Tag);
            SelectObjectProperties(selectedObject);
        }

        private void customComponentMenu_Click(object sender, EventArgs e)
        {
            engine.AddCustomComponent(selectedObject, (string)((MenuItem)sender).Tag);
            SelectObjectProperties(selectedObject);
        }

        private void ClearPropertyPanel()
        {
            List<Control> listControls = propertyPanel.Controls.Cast<Control>().ToList();

            foreach (Control control in listControls)
            {
                propertyPanel.Controls.Remove(control);
                control.Dispose();
            }

            addComponentButton = null;
        }

        public void AddSceneObject(string name, string type)
        {
            TreeNode treeNode = new TreeNode(name);
            BaseObject baseObj = engine.AddObject(type);
            treeNode.Tag = baseObj;
            sceneView.Nodes.Add(treeNode);
        }

        public void FillSceneObjects()
        {
            ClearSceneView();

            foreach(BaseObject obj in engine.GetScene().objects)
            {
                TreeNode treeNode = new TreeNode(obj.ObjectName);
                treeNode.Tag = obj;
                sceneView.Nodes.Add(treeNode);
            }
        }

        private void ClearSceneView()
        {
            //List<Control> listControls = sceneView.Controls.Cast<Control>().ToList();

            //foreach (Control control in listControls)
            //{
            //    sceneView.Controls.Remove(control);
            //    control.Dispose();
            //}
            sceneView.Nodes.Clear();
        }

        public void UpdateComponents()
        {

        }

        private void AddObject_Click(object sender, EventArgs e)
        {
            string productName = null;
            productName = componentsView.SelectedItems[0].SubItems[0].Text;
            AddSceneObject(componentsView.SelectedItems[0].SubItems[0].Text, componentsView.SelectedItems[0].SubItems[0].Text);
            //MessageBox.Show(productName);

        }


        [PermissionSet(SecurityAction.Demand, Name = "FullTrust")]
        public void Run()
        {
            // Create a new FileSystemWatcher and set its properties.
            watcher = new FileSystemWatcher();
            watcher.Path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            /* Watch for changes in LastAccess and LastWrite times, and
               the renaming of files or directories. */
            watcher.NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite
               | NotifyFilters.FileName | NotifyFilters.DirectoryName;
            // Only watch text files.
            watcher.Filter = "*.dll";

            // Add event handlers.
            watcher.Changed += new FileSystemEventHandler(OnChanged);
            watcher.Created += new FileSystemEventHandler(OnCreated);
            watcher.Deleted += new FileSystemEventHandler(OnDeleted);
            watcher.Renamed += new RenamedEventHandler(OnRenamed);

            // Begin watching.
            watcher.EnableRaisingEvents = true;
        }

        // Define the event handlers.
        private void OnChanged(object source, FileSystemEventArgs e)
        {
            // Specify what is done when a file is changed, created, or deleted.
            //Console.WriteLine("File: " + e.FullPath + " " + e.ChangeType);
            engine.LoadGame();
        }

        private void OnCreated(object source, FileSystemEventArgs e)
        {
            // Specify what is done when a file is changed, created, or deleted.
            //Console.WriteLine("File: " + e.FullPath + " " + e.ChangeType);
        }

        private void OnDeleted(object source, FileSystemEventArgs e)
        {
            // Specify what is done when a file is changed, created, or deleted.
            //Console.WriteLine("File: " + e.FullPath + " " + e.ChangeType);
            engine.UnloadGame();
        }

        private void OnRenamed(object source, RenamedEventArgs e)
        {
            // Specify what is done when a file is renamed.
            //Console.WriteLine("File: {0} renamed to {1}", e.OldFullPath, e.FullPath);
        }

        private void sceneView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            SelectObjectProperties((BaseObject)e.Node.Tag);
            selectedObject = (BaseObject)e.Node.Tag;
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //
            engine.GetScene().Save("scene.bin");
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            engine.GetScene().Load("scene.bin");
            FillSceneObjects();
        }
    }
}
