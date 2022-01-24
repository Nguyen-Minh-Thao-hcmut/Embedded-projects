using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_BTL
{
    class Serial
    {
        static byte[] bOPT = { 0x0, 0x0, 0x00 };
        //DATA
        //byte[] bDATA = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        //SYNC/ACK
        static byte[] bSYNC = { 0x16 };
        static byte[] bACK = { 0x06 };
        //ETX
        static byte[] bETX = { 0x03 };
        static byte[] bSTX = { 0x02 };


        public static string ConvertArraytoString(byte[] bProtocol)
        {
            StringBuilder Str = new StringBuilder();
            for (int i = 0; i < 20; i++)
            {
                Str.AppendFormat("{0:X2} ", bProtocol[i]);

            }
            return Str.ToString();

        }
        public static byte[] CreatedFrame(byte[] bCommand, byte[] bData)
        {
            byte[] bProtocol = new byte[50];
            int index = 0;
            bSTX.CopyTo(bProtocol, index);
            index += bSTX.Length;
            bCommand.CopyTo(bProtocol, index);
            index += bCommand.Length;
            bOPT.CopyTo(bProtocol, index);
            index += bOPT.Length;
            bData.CopyTo(bProtocol, index);
            index += bData.Length;
            bSYNC.CopyTo(bProtocol, index);
            index += bSYNC.Length;
            bETX.CopyTo(bProtocol, index);
            index += bETX.Length;
            return bProtocol;
        }
    }
}
