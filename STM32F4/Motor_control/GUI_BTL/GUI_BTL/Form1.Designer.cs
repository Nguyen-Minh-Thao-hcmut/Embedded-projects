
namespace GUI_BTL
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.tbx_screen = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.zedGraphControl_PID = new ZedGraph.ZedGraphControl();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.Combo_baud = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.status = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.Combo_name = new System.Windows.Forms.ComboBox();
            this.btn_open = new System.Windows.Forms.Button();
            this.btn_get = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.btn_stop = new System.Windows.Forms.Button();
            this.tbx_velocity = new System.Windows.Forms.TextBox();
            this.btn_tunning = new System.Windows.Forms.Button();
            this.btn_send = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.tbx_Ki = new System.Windows.Forms.TextBox();
            this.tbx_Kd = new System.Windows.Forms.TextBox();
            this.tbx_Kp = new System.Windows.Forms.TextBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.btn_svel = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.tbx_fPMW = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.tbx_screen);
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(897, 202);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Screen";
            // 
            // tbx_screen
            // 
            this.tbx_screen.Location = new System.Drawing.Point(12, 21);
            this.tbx_screen.Multiline = true;
            this.tbx_screen.Name = "tbx_screen";
            this.tbx_screen.ReadOnly = true;
            this.tbx_screen.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbx_screen.Size = new System.Drawing.Size(878, 169);
            this.tbx_screen.TabIndex = 0;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.zedGraphControl_PID);
            this.groupBox2.Controls.Add(this.groupBox4);
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.tbx_Ki);
            this.groupBox2.Controls.Add(this.tbx_Kd);
            this.groupBox2.Controls.Add(this.tbx_Kp);
            this.groupBox2.Location = new System.Drawing.Point(12, 196);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(885, 666);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "PID Controller";
            // 
            // zedGraphControl_PID
            // 
            this.zedGraphControl_PID.Location = new System.Drawing.Point(7, 168);
            this.zedGraphControl_PID.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.zedGraphControl_PID.Name = "zedGraphControl_PID";
            this.zedGraphControl_PID.ScrollGrace = 0D;
            this.zedGraphControl_PID.ScrollMaxX = 0D;
            this.zedGraphControl_PID.ScrollMaxY = 0D;
            this.zedGraphControl_PID.ScrollMaxY2 = 0D;
            this.zedGraphControl_PID.ScrollMinX = 0D;
            this.zedGraphControl_PID.ScrollMinY = 0D;
            this.zedGraphControl_PID.ScrollMinY2 = 0D;
            this.zedGraphControl_PID.Size = new System.Drawing.Size(871, 482);
            this.zedGraphControl_PID.TabIndex = 13;
            this.zedGraphControl_PID.UseExtendedPrintDialog = true;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.Combo_baud);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.status);
            this.groupBox4.Controls.Add(this.label6);
            this.groupBox4.Controls.Add(this.Combo_name);
            this.groupBox4.Controls.Add(this.btn_open);
            this.groupBox4.Controls.Add(this.btn_get);
            this.groupBox4.Location = new System.Drawing.Point(544, 15);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(334, 146);
            this.groupBox4.TabIndex = 12;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Serial";
            // 
            // Combo_baud
            // 
            this.Combo_baud.FormattingEnabled = true;
            this.Combo_baud.Items.AddRange(new object[] {
            "1200",
            "2400",
            "4800",
            "9600",
            "19200",
            "38400",
            "57600",
            "115200"});
            this.Combo_baud.Location = new System.Drawing.Point(97, 69);
            this.Combo_baud.Name = "Combo_baud";
            this.Combo_baud.Size = new System.Drawing.Size(121, 24);
            this.Combo_baud.TabIndex = 15;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(35, 68);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 17);
            this.label7.TabIndex = 14;
            this.label7.Text = "Baud";
            // 
            // status
            // 
            this.status.AutoSize = true;
            this.status.Location = new System.Drawing.Point(119, 109);
            this.status.Name = "status";
            this.status.Size = new System.Drawing.Size(46, 17);
            this.status.TabIndex = 11;
            this.status.Text = "status";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(35, 29);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(45, 17);
            this.label6.TabIndex = 12;
            this.label6.Text = "Name";
            // 
            // Combo_name
            // 
            this.Combo_name.FormattingEnabled = true;
            this.Combo_name.Location = new System.Drawing.Point(97, 26);
            this.Combo_name.Name = "Combo_name";
            this.Combo_name.Size = new System.Drawing.Size(121, 24);
            this.Combo_name.TabIndex = 13;
            // 
            // btn_open
            // 
            this.btn_open.Location = new System.Drawing.Point(237, 79);
            this.btn_open.Name = "btn_open";
            this.btn_open.Size = new System.Drawing.Size(75, 47);
            this.btn_open.TabIndex = 12;
            this.btn_open.Text = "Open";
            this.btn_open.UseVisualStyleBackColor = true;
            this.btn_open.Click += new System.EventHandler(this.btn_open_Click);
            // 
            // btn_get
            // 
            this.btn_get.Location = new System.Drawing.Point(237, 26);
            this.btn_get.Name = "btn_get";
            this.btn_get.Size = new System.Drawing.Size(75, 45);
            this.btn_get.TabIndex = 11;
            this.btn_get.Text = "Get";
            this.btn_get.UseVisualStyleBackColor = true;
            this.btn_get.Click += new System.EventHandler(this.btn_get_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.tbx_fPMW);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.btn_svel);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.btn_stop);
            this.groupBox3.Controls.Add(this.tbx_velocity);
            this.groupBox3.Controls.Add(this.btn_tunning);
            this.groupBox3.Controls.Add(this.btn_send);
            this.groupBox3.Location = new System.Drawing.Point(172, 15);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(366, 146);
            this.groupBox3.TabIndex = 11;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Control Button";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(150, 33);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(38, 17);
            this.label8.TabIndex = 16;
            this.label8.Text = "RPM";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(18, 34);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(57, 17);
            this.label4.TabIndex = 6;
            this.label4.Text = "Velocity";
            // 
            // btn_stop
            // 
            this.btn_stop.Location = new System.Drawing.Point(275, 79);
            this.btn_stop.Name = "btn_stop";
            this.btn_stop.Size = new System.Drawing.Size(75, 47);
            this.btn_stop.TabIndex = 10;
            this.btn_stop.Text = "Stop";
            this.btn_stop.UseVisualStyleBackColor = true;
            this.btn_stop.Click += new System.EventHandler(this.btn_stop_Click);
            // 
            // tbx_velocity
            // 
            this.tbx_velocity.Location = new System.Drawing.Point(86, 27);
            this.tbx_velocity.Multiline = true;
            this.tbx_velocity.Name = "tbx_velocity";
            this.tbx_velocity.Size = new System.Drawing.Size(58, 36);
            this.tbx_velocity.TabIndex = 7;
            // 
            // btn_tunning
            // 
            this.btn_tunning.Location = new System.Drawing.Point(194, 79);
            this.btn_tunning.Name = "btn_tunning";
            this.btn_tunning.Size = new System.Drawing.Size(75, 47);
            this.btn_tunning.TabIndex = 9;
            this.btn_tunning.Text = "Tunning";
            this.btn_tunning.UseVisualStyleBackColor = true;
            this.btn_tunning.Click += new System.EventHandler(this.btn_tunning_Click);
            // 
            // btn_send
            // 
            this.btn_send.Location = new System.Drawing.Point(194, 21);
            this.btn_send.Name = "btn_send";
            this.btn_send.Size = new System.Drawing.Size(75, 42);
            this.btn_send.TabIndex = 8;
            this.btn_send.Text = "Send";
            this.btn_send.UseVisualStyleBackColor = true;
            this.btn_send.Click += new System.EventHandler(this.btn_send_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(17, 137);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(25, 17);
            this.label3.TabIndex = 5;
            this.label3.Text = "Kd";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(17, 87);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(20, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Ki";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(17, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(25, 17);
            this.label1.TabIndex = 3;
            this.label1.Text = "Kp";
            // 
            // tbx_Ki
            // 
            this.tbx_Ki.Location = new System.Drawing.Point(58, 71);
            this.tbx_Ki.Multiline = true;
            this.tbx_Ki.Name = "tbx_Ki";
            this.tbx_Ki.Size = new System.Drawing.Size(85, 44);
            this.tbx_Ki.TabIndex = 2;
            // 
            // tbx_Kd
            // 
            this.tbx_Kd.Location = new System.Drawing.Point(81, 121);
            this.tbx_Kd.Multiline = true;
            this.tbx_Kd.Name = "tbx_Kd";
            this.tbx_Kd.Size = new System.Drawing.Size(85, 40);
            this.tbx_Kd.TabIndex = 1;
            // 
            // tbx_Kp
            // 
            this.tbx_Kp.Location = new System.Drawing.Point(81, 21);
            this.tbx_Kp.Multiline = true;
            this.tbx_Kp.Name = "tbx_Kp";
            this.tbx_Kp.Size = new System.Drawing.Size(85, 44);
            this.tbx_Kp.TabIndex = 0;
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // btn_svel
            // 
            this.btn_svel.Location = new System.Drawing.Point(275, 21);
            this.btn_svel.Name = "btn_svel";
            this.btn_svel.Size = new System.Drawing.Size(75, 42);
            this.btn_svel.TabIndex = 17;
            this.btn_svel.Text = "Svel";
            this.btn_svel.UseVisualStyleBackColor = true;
            this.btn_svel.Click += new System.EventHandler(this.btn_svel_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(18, 99);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(45, 17);
            this.label5.TabIndex = 18;
            this.label5.Text = "fPMW";
            // 
            // tbx_fPMW
            // 
            this.tbx_fPMW.Location = new System.Drawing.Point(86, 87);
            this.tbx_fPMW.Multiline = true;
            this.tbx_fPMW.Name = "tbx_fPMW";
            this.tbx_fPMW.Size = new System.Drawing.Size(58, 36);
            this.tbx_fPMW.TabIndex = 19;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(150, 99);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(27, 17);
            this.label9.TabIndex = 20;
            this.label9.Text = "HZ";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(906, 864);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox tbx_screen;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbx_Ki;
        private System.Windows.Forms.TextBox tbx_Kd;
        private System.Windows.Forms.TextBox tbx_Kp;
        private System.Windows.Forms.Button btn_stop;
        private System.Windows.Forms.Button btn_tunning;
        private System.Windows.Forms.Button btn_send;
        private System.Windows.Forms.TextBox tbx_velocity;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ComboBox Combo_baud;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label status;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox Combo_name;
        private System.Windows.Forms.Button btn_open;
        private System.Windows.Forms.Button btn_get;
        private System.Windows.Forms.Label label8;
        private ZedGraph.ZedGraphControl zedGraphControl_PID;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button btn_svel;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox tbx_fPMW;
        private System.Windows.Forms.Label label5;
    }
}

