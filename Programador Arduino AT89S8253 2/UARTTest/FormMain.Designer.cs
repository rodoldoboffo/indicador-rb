namespace UARTTest
{
    partial class FormMain
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
            this.comboBoxSerialPorts = new System.Windows.Forms.ComboBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.buttonDisconnect = new System.Windows.Forms.Button();
            this.groupBoxConnection = new System.Windows.Forms.GroupBox();
            this.groupBoxProgrammer = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.buttonDumpDataMemory = new System.Windows.Forms.Button();
            this.buttonGenerateBin = new System.Windows.Forms.Button();
            this.dumpButton = new System.Windows.Forms.Button();
            this.buttonRun = new System.Windows.Forms.Button();
            this.buttonStartProgramProtocol = new System.Windows.Forms.Button();
            this.buttonLoadProgram = new System.Windows.Forms.Button();
            this.buttonBurn = new System.Windows.Forms.Button();
            this.textBoxProgram = new System.Windows.Forms.TextBox();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabelProgramSize = new System.Windows.Forms.ToolStripStatusLabel();
            this.groupBoxConnection.SuspendLayout();
            this.groupBoxProgrammer.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBoxSerialPorts
            // 
            this.comboBoxSerialPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSerialPorts.FormattingEnabled = true;
            this.comboBoxSerialPorts.Location = new System.Drawing.Point(6, 19);
            this.comboBoxSerialPorts.Name = "comboBoxSerialPorts";
            this.comboBoxSerialPorts.Size = new System.Drawing.Size(122, 21);
            this.comboBoxSerialPorts.TabIndex = 0;
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(134, 17);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 1;
            this.buttonConnect.Text = "Conectar";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // buttonDisconnect
            // 
            this.buttonDisconnect.Location = new System.Drawing.Point(215, 17);
            this.buttonDisconnect.Name = "buttonDisconnect";
            this.buttonDisconnect.Size = new System.Drawing.Size(75, 23);
            this.buttonDisconnect.TabIndex = 2;
            this.buttonDisconnect.Text = "Disconectar";
            this.buttonDisconnect.UseVisualStyleBackColor = true;
            this.buttonDisconnect.Click += new System.EventHandler(this.buttonDisconnect_Click);
            // 
            // groupBoxConnection
            // 
            this.groupBoxConnection.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxConnection.Controls.Add(this.comboBoxSerialPorts);
            this.groupBoxConnection.Controls.Add(this.buttonConnect);
            this.groupBoxConnection.Controls.Add(this.buttonDisconnect);
            this.groupBoxConnection.Location = new System.Drawing.Point(7, 3);
            this.groupBoxConnection.Name = "groupBoxConnection";
            this.groupBoxConnection.Size = new System.Drawing.Size(483, 46);
            this.groupBoxConnection.TabIndex = 13;
            this.groupBoxConnection.TabStop = false;
            this.groupBoxConnection.Text = "Conexão";
            // 
            // groupBoxProgrammer
            // 
            this.groupBoxProgrammer.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxProgrammer.Controls.Add(this.button1);
            this.groupBoxProgrammer.Controls.Add(this.buttonDumpDataMemory);
            this.groupBoxProgrammer.Controls.Add(this.buttonGenerateBin);
            this.groupBoxProgrammer.Controls.Add(this.dumpButton);
            this.groupBoxProgrammer.Controls.Add(this.buttonRun);
            this.groupBoxProgrammer.Controls.Add(this.buttonStartProgramProtocol);
            this.groupBoxProgrammer.Controls.Add(this.buttonLoadProgram);
            this.groupBoxProgrammer.Controls.Add(this.buttonBurn);
            this.groupBoxProgrammer.Controls.Add(this.textBoxProgram);
            this.groupBoxProgrammer.Location = new System.Drawing.Point(7, 55);
            this.groupBoxProgrammer.Name = "groupBoxProgrammer";
            this.groupBoxProgrammer.Size = new System.Drawing.Size(483, 513);
            this.groupBoxProgrammer.TabIndex = 14;
            this.groupBoxProgrammer.TabStop = false;
            this.groupBoxProgrammer.Text = "Programa";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(402, 135);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 9;
            this.button1.Text = "Erase";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // buttonDumpDataMemory
            // 
            this.buttonDumpDataMemory.Location = new System.Drawing.Point(402, 252);
            this.buttonDumpDataMemory.Name = "buttonDumpDataMemory";
            this.buttonDumpDataMemory.Size = new System.Drawing.Size(75, 23);
            this.buttonDumpDataMemory.TabIndex = 8;
            this.buttonDumpDataMemory.Text = "Dump Data";
            this.buttonDumpDataMemory.UseVisualStyleBackColor = true;
            this.buttonDumpDataMemory.Click += new System.EventHandler(this.buttonDumpDataMemory_Click);
            // 
            // buttonGenerateBin
            // 
            this.buttonGenerateBin.Location = new System.Drawing.Point(402, 48);
            this.buttonGenerateBin.Name = "buttonGenerateBin";
            this.buttonGenerateBin.Size = new System.Drawing.Size(75, 23);
            this.buttonGenerateBin.TabIndex = 7;
            this.buttonGenerateBin.Text = "Binary";
            this.buttonGenerateBin.UseVisualStyleBackColor = true;
            this.buttonGenerateBin.Click += new System.EventHandler(this.buttonGenerateBin_Click);
            // 
            // dumpButton
            // 
            this.dumpButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.dumpButton.Location = new System.Drawing.Point(402, 106);
            this.dumpButton.Name = "dumpButton";
            this.dumpButton.Size = new System.Drawing.Size(75, 23);
            this.dumpButton.TabIndex = 6;
            this.dumpButton.Text = "Dump";
            this.dumpButton.UseVisualStyleBackColor = true;
            this.dumpButton.Click += new System.EventHandler(this.dumpButton_Click);
            // 
            // buttonRun
            // 
            this.buttonRun.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonRun.Location = new System.Drawing.Point(402, 193);
            this.buttonRun.Name = "buttonRun";
            this.buttonRun.Size = new System.Drawing.Size(75, 23);
            this.buttonRun.TabIndex = 5;
            this.buttonRun.Text = "Run";
            this.buttonRun.UseVisualStyleBackColor = true;
            this.buttonRun.Click += new System.EventHandler(this.buttonRun_Click);
            // 
            // buttonStartProgramProtocol
            // 
            this.buttonStartProgramProtocol.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonStartProgramProtocol.Location = new System.Drawing.Point(402, 77);
            this.buttonStartProgramProtocol.Name = "buttonStartProgramProtocol";
            this.buttonStartProgramProtocol.Size = new System.Drawing.Size(75, 23);
            this.buttonStartProgramProtocol.TabIndex = 3;
            this.buttonStartProgramProtocol.Text = "Start Protocol";
            this.buttonStartProgramProtocol.UseVisualStyleBackColor = true;
            this.buttonStartProgramProtocol.Click += new System.EventHandler(this.buttonStartProgramProtocol_Click);
            // 
            // buttonLoadProgram
            // 
            this.buttonLoadProgram.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonLoadProgram.Location = new System.Drawing.Point(402, 19);
            this.buttonLoadProgram.Name = "buttonLoadProgram";
            this.buttonLoadProgram.Size = new System.Drawing.Size(75, 23);
            this.buttonLoadProgram.TabIndex = 2;
            this.buttonLoadProgram.Text = "Browse";
            this.buttonLoadProgram.UseVisualStyleBackColor = true;
            this.buttonLoadProgram.Click += new System.EventHandler(this.buttonLoadProgram_Click);
            // 
            // buttonBurn
            // 
            this.buttonBurn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonBurn.Location = new System.Drawing.Point(402, 164);
            this.buttonBurn.Name = "buttonBurn";
            this.buttonBurn.Size = new System.Drawing.Size(75, 23);
            this.buttonBurn.TabIndex = 1;
            this.buttonBurn.Text = "Burn";
            this.buttonBurn.UseVisualStyleBackColor = true;
            this.buttonBurn.Click += new System.EventHandler(this.buttonBurn_Click);
            // 
            // textBoxProgram
            // 
            this.textBoxProgram.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxProgram.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxProgram.Location = new System.Drawing.Point(6, 19);
            this.textBoxProgram.Multiline = true;
            this.textBoxProgram.Name = "textBoxProgram";
            this.textBoxProgram.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxProgram.Size = new System.Drawing.Size(390, 487);
            this.textBoxProgram.TabIndex = 0;
            this.textBoxProgram.WordWrap = false;
            this.textBoxProgram.TextChanged += new System.EventHandler(this.textBoxProgram_TextChanged);
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabelProgramSize});
            this.statusStrip.Location = new System.Drawing.Point(0, 571);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(496, 22);
            this.statusStrip.TabIndex = 15;
            this.statusStrip.Text = "statusStrip1";
            // 
            // toolStripStatusLabelProgramSize
            // 
            this.toolStripStatusLabelProgramSize.Name = "toolStripStatusLabelProgramSize";
            this.toolStripStatusLabelProgramSize.Size = new System.Drawing.Size(0, 17);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(496, 593);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.groupBoxProgrammer);
            this.Controls.Add(this.groupBoxConnection);
            this.Name = "FormMain";
            this.Text = "UART Test";
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.groupBoxConnection.ResumeLayout(false);
            this.groupBoxProgrammer.ResumeLayout(false);
            this.groupBoxProgrammer.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBoxSerialPorts;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.Button buttonDisconnect;
        private System.Windows.Forms.GroupBox groupBoxConnection;
        private System.Windows.Forms.GroupBox groupBoxProgrammer;
        private System.Windows.Forms.TextBox textBoxProgram;
        private System.Windows.Forms.Button buttonBurn;
        private System.Windows.Forms.Button buttonLoadProgram;
        private System.Windows.Forms.Button buttonStartProgramProtocol;
        private System.Windows.Forms.Button buttonRun;
        private System.Windows.Forms.Button dumpButton;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelProgramSize;
        private System.Windows.Forms.Button buttonGenerateBin;
        private System.Windows.Forms.Button buttonDumpDataMemory;
        private System.Windows.Forms.Button button1;
    }
}

