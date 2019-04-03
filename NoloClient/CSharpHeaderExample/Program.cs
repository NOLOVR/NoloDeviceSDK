
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestClientSharpDemo
{

    class Program
    {

        static void Main(string[] args)
        {
            Console.WriteLine("Test NoloCSharp Client Started!");

            NoloManager m_NoloManager = new NoloManager();
            m_NoloManager.StartNoloDevice();
            
            Console.ReadKey();
        }
    }
}
