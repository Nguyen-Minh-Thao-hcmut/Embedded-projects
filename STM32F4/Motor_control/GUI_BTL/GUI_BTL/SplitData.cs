using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_BTL
{
    class SplitData
    {
		public static void FloatToByteArray(double dNumber, ref byte[] bOut, out byte nLengthTithes)
		{
			byte nCountTithes = 0;
			bOut[0] = (byte)dNumber;
			float nTithes = (float)(dNumber - bOut[0]);
			do
			{
				nTithes *= 10;
				if ((nCountTithes++ >> 3) == 1) break;
			} while (nTithes <= 1);
			nLengthTithes = nCountTithes;
			bOut[1] = (byte)nTithes;
		}
		public static void FloatToByteArrayWithNipes(double fNumber, byte[] bOut, out byte nLengthTithes)
		{
			byte nCountTithes = 5;
			bOut[0] = (byte)fNumber;
			double nTithes = (double)(fNumber - bOut[0]);
			nTithes = nTithes * Math.Pow(10, nCountTithes);
			while (nTithes > 255)
			{
				nTithes /= 10;
				nCountTithes--;
			}
			nLengthTithes = nCountTithes;
			bOut[1] = (byte)nTithes;
		}

		public static double BinarytoDecimal(string b)
		{
			int binary = int.Parse(b);
			double dec = 0, i = 0, d;
			while (binary != 0)
			{
				d = binary % 10;
				dec = dec + d * Math.Pow(2, i); // su dung ham trong C#
				binary = binary / 10;
				i++;
			}
			return dec;
		}

		public static void TransformVelocity(double dVel, ref byte[] bOut)
        {
			int bVel = 0;
			bVel = (int)dVel;
			double nTithes = (double)(dVel - bVel);
			bOut[2] = (byte)(nTithes * 10);
			bOut[0] = (byte)(bVel / 100);
			bOut[1] = (byte)(bVel % 100);



		}
	}
}
