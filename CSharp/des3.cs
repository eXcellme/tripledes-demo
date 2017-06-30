using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;

namespace ConsoleApplication4
{
    class Program
    {
       
        public static string Encrypt3DES(string a_strString, string a_strKey)
        {
            TripleDESCryptoServiceProvider DES = new TripleDESCryptoServiceProvider();

            DES.Key = ASCIIEncoding.ASCII.GetBytes(a_strKey);
            DES.Mode = CipherMode.ECB;

            ICryptoTransform DESEncrypt = DES.CreateEncryptor();

            byte[] Buffer = UTF8Encoding.UTF8.GetBytes(a_strString);
            return Convert.ToBase64String(DESEncrypt.TransformFinalBlock(Buffer, 0, Buffer.Length));
        }
        public static string Decrypt3DES(string a_strString, string a_strKey)
        {
            TripleDESCryptoServiceProvider DES = new TripleDESCryptoServiceProvider();

            DES.Key = ASCIIEncoding.ASCII.GetBytes(a_strKey);
            DES.Mode = CipherMode.ECB;
            DES.Padding = System.Security.Cryptography.PaddingMode.PKCS7;

            ICryptoTransform DESDecrypt = DES.CreateDecryptor();

            string result = "";
            try
            {
                byte[] Buffer = Convert.FromBase64String(a_strString);
                byte[] temp = DESDecrypt.TransformFinalBlock(Buffer, 0, Buffer.Length);
                result = UTF8Encoding.UTF8.GetString(temp);
                
            }
            catch (Exception e)
            {
                Console.WriteLine("A Cryptographic error occurred: {0}", e.Message);
                
            }
            return result;
        }
        static void Main()
        {
            // Console.WriteLine("hello world");
            // Console.ReadLine();
            System.Text.Encoding utf8 = System.Text.Encoding.UTF8;
            string sourceTxt = "Hello";
            string appSecert = "123456781234567812345678";

            string result = Encrypt3DES(sourceTxt, appSecert);
            Console.WriteLine(result);
            Console.ReadLine();

            string result2 = Decrypt3DES(result, appSecert);
            Console.WriteLine(result2);
            Console.ReadLine();
        }
    
    }
}
