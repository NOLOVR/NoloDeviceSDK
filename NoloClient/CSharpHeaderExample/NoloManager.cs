using System;
using NoloClientCSharp;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace TestClientSharpDemo
{
    class NoloManager
    {

        public NoloManager()
        {
            InitCallBacks();
        }

        public void StartNoloDevice()
        {
            //NoloClientLib.StartNoloServer(@"NoloServer\NoloServer.exe");
            NoloClientLib.OpenNoloZeroMQ(); 
        }

        private static pfnVoidCallBack _OnNoloZqmStart;
        private static pfnVoidCallBack _OnNoloZqmFinished;
        private static pfnDataCallBack _OnNoloData;
        private static pfnKeyEvent     _OnNoloKeyEvent;
        private static pfnVoidIntCallBack _OnNoloDevVersion;

        private void InitCallBacks()
        {
            _OnNoloZqmStart = new pfnVoidCallBack(OnZmqConnected);
            NoloClientLib.RegisterCallBack(ECallBackTypes.eOnZMQConnected,
                Marshal.GetFunctionPointerForDelegate(_OnNoloZqmStart));

            _OnNoloZqmFinished = new pfnVoidCallBack(OnZmqDisConnected);
            NoloClientLib.RegisterCallBack(ECallBackTypes.eOnZMQDisConnected,
                Marshal.GetFunctionPointerForDelegate(_OnNoloZqmFinished));

            _OnNoloData = new pfnDataCallBack(OnNewData);
            NoloClientLib.RegisterCallBack(ECallBackTypes.eOnNewData,
                Marshal.GetFunctionPointerForDelegate(_OnNoloData));

            _OnNoloKeyEvent = new pfnKeyEvent(OnKeyDbClicked);
            NoloClientLib.RegisterCallBack(ECallBackTypes.eOnButtonDoubleClicked,
                Marshal.GetFunctionPointerForDelegate(_OnNoloKeyEvent));

            _OnNoloDevVersion = new pfnVoidIntCallBack(OnNoloDevVersion);
            NoloClientLib.RegisterCallBack(ECallBackTypes.eOnNoloDevVersion,
                Marshal.GetFunctionPointerForDelegate(_OnNoloDevVersion));
        }

        private void OnNoloDevVersion(int version)
        {
            Console.WriteLine("OnNoloDevVersion"+ version);
        }

        private void OnKeyDbClicked(ENoloDeviceType DevType, byte Keys)
        {
            Console.WriteLine(DevType.ToString()+ " DbClick:" + Keys);
        }

        private void OnNewData(ref NOLOData noloData)
        {   
            Console.WriteLine("Data "+ noloData.hmdData.HMDRotation);
            //Console.WriteLine(" lPack:" + noloData.leftPackNumber +"rPack:"+ noloData.rightPackNumber);

        }

        private void OnZmqConnected()
        {
            Console.WriteLine("OnZmqConnected");
        }

        private void OnZmqDisConnected()
        {
            Console.WriteLine("OnZmqDisConnected");
        }

    }
}
