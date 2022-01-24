using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using System.Xml;
using ZedGraph;
namespace GUI_BTL
{
    public partial class Form1 : Form
    {
        delegate void SetTextCallback(byte[] text);
        byte[] bSTX = { 0x02 };
        byte[] bSPID = { 0x53, 0x50, 0x49, 0x44 }; //ASCII {SPID}
        byte[] bGPID = { 0x47, 0x50, 0x49, 0x44 }; //ASCII {GPID}    
        byte[] bVTUN = { 0x56, 0x54, 0x55, 0x4E }; //ASCII {VTUN}
        byte[] bCRUN = { 0x43, 0x52, 0x55, 0x4E }; //ASCII {CRUN}
        byte[] bSVEL = { 0x53, 0x56, 0x45, 0x4C }; //ASCII {SVEL}
        byte[] bSTOP = { 0x53, 0x54, 0x4F, 0x50 }; //ASCII {STOP}
        byte[] bOPT = { 0x00, 0x00, 0x00 };
        byte[] bDATA = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        byte[] bSYNC = { 0x16 };
        byte[] bACK = { 0x06 };
        byte[] bETX = { 0x03 };
        byte[] bProtocolBuffer = new byte[20];
        byte[] bProtocolData = new byte[10];
        byte[] bProtocolOption = new byte[3];
        double[] dPIDVelPlotData = new double[1000];
        double[] dPIDPlotTime = new double[1000];
        
        //int tickStart = 0;
        double t = 0;
        double dVel1;
        public Form1()
        {
            InitializeComponent();
             
        }

       
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                status.Text = "Disconnected";
                status.ForeColor = Color.Red;

            }
            else if (serialPort1.IsOpen)
            {
                status.Text = "Connected";
                status.ForeColor = Color.Green;

            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            byte[] bRECData = new byte[20];
            serialPort1.Read(bRECData, 0, 20);
            
            if (bRECData != Array.Empty<byte>())
            {
                SetText(bRECData);
            }


            StringBuilder strCmd = new StringBuilder();
            int nIndex = 0;
            int nVelocity = 0;
            for (uint i = 0; i < 20; i++)
            {
                bProtocolBuffer[i] = bRECData[i];
            }
            for (uint i = 1; i <= 4; i++)
            {
                strCmd.AppendFormat("{0:X2}", bProtocolBuffer[i]);
            }
            for (uint i = 5; i < 8; i++)
            {
                bProtocolOption[i - 5] = bProtocolBuffer[i];
            }
            for (uint i = 8; i <= 17; i++)
            {
                bProtocolData[i - 8] = bProtocolBuffer[i];
            }

            string cmd = strCmd.ToString();

            

            if (cmd.CompareTo("4352554E") == 0) //CRUN
            {
                double dVel = double.Parse(tbx_velocity.Text);
                nIndex = 0;
                for (int i=0; i < 5;i++)
                {
                    t = t + 0.01;
                    nVelocity = (bProtocolData[2*i] << 8) + bProtocolData[2*i+1];
                    dPIDVelPlotData[nIndex] = nVelocity;
                    DrawPIDVelGraph(nIndex,t, dVel1);
                    nIndex++;

                }    
                //nLenGraphPIDVel = (bProtocolData[0] << 8) + bProtocolData[1];
                //nIndex = (bProtocolData[2] << 8) + bProtocolData[3];
                //nVelocity = (bProtocolData[6] << 8) + bProtocolData[7];
                //dPIDVelPlotData[nIndex] = nVelocity;
                //DrawPIDVelGraph(nIndex);
            }
            //if (cmd.CompareTo("53544F50") == 0)
            //{
            //    serialPort1.Close();
            //}    


        }
        private void SetText(byte[] text)
        {
            if (this.tbx_screen.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                StringBuilder Str = new StringBuilder();
                byte[] DataReceive = text;
                string RxBuffer = Serial.ConvertArraytoString(DataReceive);
                tbx_screen.Text = Environment.NewLine + tbx_screen.Text.Insert(0, RxBuffer);
                Str.Append("REC :");
                string REC = Str.ToString();
                tbx_screen.Text = Environment.NewLine + tbx_screen.Text.Insert(0, REC);

            }
        }
        private void btn_get_Click(object sender, EventArgs e)
        {
            Combo_name.DataSource = SerialPort.GetPortNames();
        }

        private void btn_open_Click(object sender, EventArgs e)
        {
            if (Combo_name.DataSource == null)
            {
                MessageBox.Show("Please get port!");
            }
            else if (Combo_baud.Text == "")
            {
                MessageBox.Show("Please get baud !");
            }
            else if (Combo_name.DataSource != null && Combo_baud.Text != null)
            {
                if (!serialPort1.IsOpen)
                { 
                        serialPort1.PortName = Combo_name.Text;
                        serialPort1.BaudRate = Convert.ToInt32(Combo_baud.Text);
                    try
                    {
                        serialPort1.Open();
                        btn_open.Text = "Close";
                        
                    }
                    catch
                    {
                        MessageBox.Show("Can not open " + serialPort1.PortName, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }

                }

                else
                {
                    serialPort1.Close();
                    btn_open.Text = "Open";
                }
            }
        }

        private void btn_send_Click(object sender, EventArgs e)
        {
            Array.Clear(bDATA, 0, 10);
            double dKp = double.Parse(tbx_Kp.Text);
            double dKi = double.Parse(tbx_Ki.Text);
            double dKd = double.Parse(tbx_Kd.Text);
            double dfPMW = double.Parse(tbx_fPMW.Text);
            byte[] bProtocol = new byte[50];
            byte[] bKp = new byte[2];
            byte[] bKi = new byte[2];
            byte[] bKd = new byte[3];
            byte[] bfPMW = new byte[4];
            byte nLengTithes;
            SplitData.FloatToByteArray(dKp, ref bKp, out nLengTithes);
            bDATA[0] = bKp[0];
            bDATA[1] = bKp[1];
            SplitData.FloatToByteArray(dKi, ref bKi, out nLengTithes);
            bDATA[2] = bKi[0];
            bDATA[3] = bKi[1];
            SplitData.FloatToByteArrayWithNipes(dKd, bKd, out nLengTithes);
            bKd[2] = nLengTithes;
            bDATA[4] = bKd[0];
            bDATA[5] = bKd[1];
            bDATA[6] = bKd[2];
            SplitData.TransformVelocity(dfPMW, ref bfPMW);
            bDATA[7] = bfPMW[0];
            bDATA[8] = bfPMW[1];
            bDATA[9] = bfPMW[2];
            bProtocol = Serial.CreatedFrame(bSPID, bDATA);
            if (serialPort1.IsOpen)
            {
                tbx_screen.Text = ""; String TxBuffer = "";
                serialPort1.Write(bProtocol, 0, 20);
                TxBuffer = Serial.ConvertArraytoString(bProtocol);
                tbx_screen.Text = Environment.NewLine + "SPID:" + Environment.NewLine + TxBuffer;
            }

            else tbx_screen.Text = "Process sending fail" + Environment.NewLine;
        }

        private void btn_tunning_Click(object sender, EventArgs e)
        {
            Array.Clear(bDATA, 0, 10);
            byte[] bProtocol = new byte[50];
            bProtocol = Serial.CreatedFrame(bCRUN, bDATA);
            if (serialPort1.IsOpen)
            {
                String TxBuffer = "";
                serialPort1.Write(bProtocol, 0, 20);
                TxBuffer = Serial.ConvertArraytoString(bProtocol);

                tbx_screen.Text = Environment.NewLine + "CRUN:" + Environment.NewLine + TxBuffer + Environment.NewLine + tbx_screen.Text;
            }
            else tbx_screen.Text = "Process tuning fail" + Environment.NewLine + tbx_screen.Text;
        }

        private void btn_stop_Click(object sender, EventArgs e)
        {
            //PID_graph_clearing();
            //timer1.Enabled = false;
            byte[] bProtocol = new byte[50];
            Array.Clear(bDATA, 0, 10);
            bProtocol = Serial.CreatedFrame(bSTOP, bDATA);

            if (serialPort1.IsOpen)
            {
                String TxBuffer = "";
                serialPort1.Write(bProtocol, 0, 20);
                TxBuffer = Serial.ConvertArraytoString(bProtocol);
                tbx_screen.Text = Environment.NewLine + "STOP:" + Environment.NewLine + TxBuffer + Environment.NewLine + tbx_screen.Text;
            }
            else tbx_screen.Text = "Process requesting data fail" + Environment.NewLine + tbx_screen.Text;
           
        }
        private void btn_svel_Click(object sender, EventArgs e)
        {
            Array.Clear(bDATA, 0, 10);
            double dVel = double.Parse(tbx_velocity.Text);
            dVel1 = dVel;
            byte[] bVel = new byte[3];
           
            SplitData.TransformVelocity(dVel1, ref bVel);
            bDATA[0] = bVel[0];
            bDATA[1] = bVel[1];
            bDATA[2] = bVel[2];
            byte[] bProtocol = new byte [50];
            bProtocol = Serial.CreatedFrame(bSVEL, bDATA);
            if (serialPort1.IsOpen)
            {
                String TxBuffer = "";
                serialPort1.Write(bProtocol, 0, 20);
                TxBuffer = Serial.ConvertArraytoString(bProtocol);

                tbx_screen.Text = Environment.NewLine + "SVEL:" + Environment.NewLine + TxBuffer + Environment.NewLine + tbx_screen.Text;
            }
            else tbx_screen.Text = "Process tuning fail" + Environment.NewLine + tbx_screen.Text;
        }
        private void PID_Graph_Initialization()
        {
            GraphPane myPane = zedGraphControl_PID.GraphPane;
            myPane.Title.Text = "Graph of Velocity";
            myPane.XAxis.Title.Text = "Time";
            myPane.YAxis.Title.Text = "Velocity";
            RollingPointPairList list1 = new RollingPointPairList(5000);
            RollingPointPairList list2 = new RollingPointPairList(5000);
            LineItem curve1 = myPane.AddCurve("CmdVelocity", list1, Color.Red, SymbolType.None);
            LineItem curve2 = myPane.AddCurve("ActVelocity", list2, Color.Blue, SymbolType.None);

             timer1.Interval = 10;

            myPane.XAxis.Scale.Min = 0;
            myPane.XAxis.Scale.Max = 5;
            myPane.XAxis.Scale.MinorStep = 0.1;
            myPane.XAxis.Scale.MajorStep = 0.5;
            myPane.YAxis.Scale.Min = 0;
            myPane.YAxis.Scale.Max = 50;
            myPane.YAxis.Scale.MinorStep = 1;
            myPane.YAxis.Scale.MajorStep = 5;
            myPane.AxisChange();
            //tickStart = Environment.TickCount;
            
            //for (int i = 0; i < 1000; i++)
            //{
            //    if (i == 0)
            //    {
            //        dPIDPlotTime[i] = 0.01;
            //    }
            //    else dPIDPlotTime[i] = dPIDPlotTime[i - 1] + 0.01;
            //}

        }

        private void PID_graph_clearing()
        {
            zedGraphControl_PID.GraphPane.CurveList.Clear(); // Xóa đường
            zedGraphControl_PID.GraphPane.GraphObjList.Clear(); // Xóa đối tượng

            zedGraphControl_PID.AxisChange();
            zedGraphControl_PID.Invalidate();

            GraphPane myPane = zedGraphControl_PID.GraphPane;
            myPane.Title.Text = "Graph of Velocity";
            myPane.XAxis.Title.Text = "Time";
            myPane.YAxis.Title.Text = "Velocity";

            RollingPointPairList list1 = new RollingPointPairList(5000);
            RollingPointPairList list2 = new RollingPointPairList(5000);
            LineItem curve1 = myPane.AddCurve("CmdVeloity", list1, Color.Red, SymbolType.None);
            LineItem curve2 = myPane.AddCurve("ActVelocity", list2, Color.Blue, SymbolType.None);
            myPane.XAxis.Scale.Min = 0;
            myPane.XAxis.Scale.Max = 5;
            myPane.XAxis.Scale.MinorStep = 0.1;
            myPane.XAxis.Scale.MajorStep = 0.5;
            myPane.YAxis.Scale.Min = 0;
            myPane.YAxis.Scale.Max = 50;
            myPane.YAxis.Scale.MinorStep = 1;
            myPane.YAxis.Scale.MajorStep = 5;
            myPane.AxisChange();
           //tickStart = Environment.TickCount;
        }
        private void DrawPIDVelGraph(int index, double t,double dVel)
        {
            if (zedGraphControl_PID.GraphPane.CurveList.Count <= 0)
                return;
            LineItem curve1 = zedGraphControl_PID.GraphPane.CurveList[0] as LineItem;
            LineItem curve2 = zedGraphControl_PID.GraphPane.CurveList[1] as LineItem;
            curve1.Line.Width = 3;
            curve2.Line.Width = 3;
            IPointListEdit list1 = curve1.Points as IPointListEdit;
            IPointListEdit list2 = curve2.Points as IPointListEdit;
            //double time = (Environment.TickCount - tickStart) / 1000.0;
            list1.Add(t, dVel);
            list2.Add(t, dPIDVelPlotData[index]);
            //list1.Add(dPIDPlotTime[index], dVel * 4 * 11 * 34 / 100 / 60);
            //list2.Add(dPIDPlotTime[index], dPIDVelPlotData[index]);

            Scale xScale = zedGraphControl_PID.GraphPane.XAxis.Scale;
            Scale yScale = zedGraphControl_PID.GraphPane.YAxis.Scale;
            if (t > xScale.Max - xScale.MajorStep)
            {
                xScale.Max = t + xScale.MajorStep;
                xScale.Min = xScale.Max - 5;
            }

            // Tự động Scale theo trục y
            if (dPIDVelPlotData[index] > yScale.Max - yScale.MajorStep)
            {
                yScale.Max = dPIDVelPlotData[index] + yScale.MajorStep;
            }
            else if (dPIDVelPlotData[index] < yScale.Min + yScale.MajorStep)
            {
                yScale.Min = dPIDVelPlotData[index] - yScale.MajorStep;
            }

            zedGraphControl_PID.AxisChange();
            zedGraphControl_PID.Invalidate();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            PID_Graph_Initialization();
            
        }

        
    }
}
