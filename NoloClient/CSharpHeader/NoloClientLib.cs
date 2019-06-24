
using System;
using System.Runtime.InteropServices;
using System.Text;

namespace NoloClientCSharp
{
    //delegate Must be CDecl type
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void pfnKeyEvent(ENoloDeviceType DevType, byte Keys);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void pfnVoidCallBack();
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void pfnDataCallBack(ref NOLOData noloData);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void pfnVoidIntCallBack(int version);


    public enum ECallBackTypes
    {
        eOnZMQConnected = 0,     //pfnVoidCallBack
        eOnZMQDisConnected,      //pfnVoidCallBack
        eOnButtonDoubleClicked,  //pfnKeyEvent
        eOnKeyPressEvent,        //pfnKeyEvent
        eOnKeyReleaseEvent,      //pfnKeyEvent
        eOnNewData,              //pfnDataCallBack
        eOnNoloDevVersion,       //pfnVoidIntCallBack
        eCallBackCount
    };

    public class NoloClientLib
    {
        [DllImport("NoloClientLib",CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool StartNoloServer(string strName);

        [DllImport("NoloClientLib",CallingConvention = CallingConvention.Cdecl)]
        public static extern void RegisterCallBack(ECallBackTypes callBackType, IntPtr pCallBackFun);

        [DllImport("NoloClientLib", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetHmdCenter(ref NVector3 hmdCenter);

        [DllImport("NoloClientLib", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetBCellingMode(bool bCellingMode);

        [DllImport("NoloClientLib", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool OpenNoloZeroMQ();

        [DllImport("NoloClientLib", CallingConvention = CallingConvention.Cdecl)]
        public static extern void CloseNoloZeroMQ();

        [DllImport("NoloClientLib", CallingConvention = CallingConvention.Cdecl)]
        public static extern void TriggerHapticPulse(ENoloDeviceType deviceType, int intensity);

        [DllImport("NoloClientLib", CallingConvention = CallingConvention.Cdecl)]
        public static extern Controller GetLeftControllerData();

        [DllImport("NoloClientLib", CallingConvention = CallingConvention.Cdecl)]
        public static extern Controller GetRightControllerData();

        [DllImport("NoloClientLib", CallingConvention = CallingConvention.Cdecl)]
        public static extern HMD GetHMDData();

        [DllImport("NoloClientLib", CallingConvention = CallingConvention.Cdecl)]
        public static extern NOLOData GetNoloData();

    }
}
