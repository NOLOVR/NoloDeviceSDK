using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace NoloClientCSharp
{
    public enum ENoloDeviceType
    {
        eHmd = 0,
        eLeftController,
        eRightController,
        eBaseStation
    };

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct NVector2
    {
        public float x;
        public float y;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct NVector3
    {
        public float x;
        public float y;
        public float z;
        public override string ToString()
        {
            return "V:(" + x + "," + y + "," + z + ")";
        }
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct NQuaternion
    {
        public float x;
        public float y;
        public float z;
        public float w;
        public override string ToString()
        {
            return "Q:(" + w + "," + x + "," + y + "," + z + ")";
        }
    }

    //Types
    public enum EControlerButtonType
    {
        ePadBtn = 0x01,
        eTriggerBtn = 0x02,
        eMenuBtn = 0x04,
        eSystemBtn = 0x08,
        eGripBtn = 0x10,
        ePadTouch = 0x20
    };
    
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Controller
    {
        public int VersionID;
        public NVector3 Position;
        public NQuaternion Rotation;
        public uint Buttons;
        public int Touched;
        public NVector2 TouchAxis;
        public int Battery;
        public int State;
    };

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct HMD
    {
        public int HMDVersionID;
        public NVector3 HMDPosition;
        public NVector3 HMDInitPostion;
        public uint HMDTwoPointDriftAngle;
        public NQuaternion HMDRotation;
        public int HMDState;
    };


    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct BaseStation
    {
        public int BaseStationVersionID;
        public int BaseStationPower;
    };

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct NoloSensorData
    {
        NVector3 vecLVelocity;
        NVector3 vecLAngularVelocity;
        NVector3 vecRVelocity;
        NVector3 vecRAngularVelocity;
        NVector3 vecHVelocity;
        NVector3 vecHAngularVelocity;
    };

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct NOLOData
    {
        public Controller leftData;
        public Controller rightData;
        public HMD hmdData;
        public BaseStation bsData;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] expandData;
        public NoloSensorData NoloSensorData;
        public byte leftPackNumber;
        public byte rightPackNumber;
        public NVector3 FixedEyePosition;
    };

}
