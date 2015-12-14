namespace EditorCore
{
    partial class EditorMainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.renderMainWindow = new System.Windows.Forms.Panel();
            this.sceneView = new System.Windows.Forms.TreeView();
            this.componentsView = new System.Windows.Forms.ListView();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openGLRenderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.directXRenderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openGLESRenderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.AddComponent = new System.Windows.Forms.Button();
            this.propertyPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // renderMainWindow
            // 
            this.renderMainWindow.Location = new System.Drawing.Point(2, 27);
            this.renderMainWindow.Name = "renderMainWindow";
            this.renderMainWindow.Size = new System.Drawing.Size(851, 541);
            this.renderMainWindow.TabIndex = 0;
            // 
            // sceneView
            // 
            this.sceneView.Location = new System.Drawing.Point(2, 574);
            this.sceneView.Name = "sceneView";
            this.sceneView.Size = new System.Drawing.Size(460, 195);
            this.sceneView.TabIndex = 2;
            this.sceneView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.sceneView_AfterSelect);
            // 
            // componentsView
            // 
            this.componentsView.Location = new System.Drawing.Point(469, 575);
            this.componentsView.Name = "componentsView";
            this.componentsView.Size = new System.Drawing.Size(384, 194);
            this.componentsView.TabIndex = 3;
            this.componentsView.UseCompatibleStateImageBehavior = false;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem,
            this.viewToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1137, 24);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.loadToolStripMenuItem.Text = "Load";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
            this.editToolStripMenuItem.Text = "Edit";
            // 
            // viewToolStripMenuItem
            // 
            this.viewToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openGLRenderToolStripMenuItem,
            this.directXRenderToolStripMenuItem,
            this.openGLESRenderToolStripMenuItem});
            this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
            this.viewToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.viewToolStripMenuItem.Text = "View";
            // 
            // openGLRenderToolStripMenuItem
            // 
            this.openGLRenderToolStripMenuItem.Name = "openGLRenderToolStripMenuItem";
            this.openGLRenderToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.openGLRenderToolStripMenuItem.Text = "OpenGL Render";
            // 
            // directXRenderToolStripMenuItem
            // 
            this.directXRenderToolStripMenuItem.Name = "directXRenderToolStripMenuItem";
            this.directXRenderToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.directXRenderToolStripMenuItem.Text = "DirectX Render";
            // 
            // openGLESRenderToolStripMenuItem
            // 
            this.openGLESRenderToolStripMenuItem.Name = "openGLESRenderToolStripMenuItem";
            this.openGLESRenderToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.openGLESRenderToolStripMenuItem.Text = "OpenGL ES Render";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // AddComponent
            // 
            this.AddComponent.Location = new System.Drawing.Point(710, 739);
            this.AddComponent.Name = "AddComponent";
            this.AddComponent.Size = new System.Drawing.Size(143, 30);
            this.AddComponent.TabIndex = 5;
            this.AddComponent.Text = "Add Component";
            this.AddComponent.UseVisualStyleBackColor = true;
            this.AddComponent.Click += new System.EventHandler(this.AddObject_Click);
            // 
            // propertyPanel
            // 
            this.propertyPanel.AutoScroll = true;
            this.propertyPanel.AutoSize = true;
            this.propertyPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.propertyPanel.Location = new System.Drawing.Point(853, 27);
            this.propertyPanel.Name = "propertyPanel";
            this.propertyPanel.Size = new System.Drawing.Size(284, 742);
            this.propertyPanel.TabIndex = 6;
            this.propertyPanel.WrapContents = false;
            // 
            // EditorMainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1137, 770);
            this.Controls.Add(this.propertyPanel);
            this.Controls.Add(this.AddComponent);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.componentsView);
            this.Controls.Add(this.sceneView);
            this.Controls.Add(this.renderMainWindow);
            this.Name = "EditorMainForm";
            this.Text = "Engine2";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel renderMainWindow;
        private System.Windows.Forms.TreeView sceneView;
        private System.Windows.Forms.ListView componentsView;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openGLRenderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem directXRenderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openGLESRenderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.Button AddComponent;
        private System.Windows.Forms.FlowLayoutPanel propertyPanel;
    }
}

