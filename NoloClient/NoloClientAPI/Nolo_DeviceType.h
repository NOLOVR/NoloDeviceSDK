#pragma once
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <cwchar>
#include "Nolo_Math.h"

namespace NOLOVR
{

enum ENoloDeviceType
{
	eHmd = 0,
	eLeftController,
	eRightController,
	eBaseStation
};

enum EControlerButtonType {
	ePadBtn     = 0x01,
	eTriggerBtn = 0x02,
	eMenuBtn    = 0x04,
	eSystemBtn  = 0x08,
	eGripBtn    = 0x10,
	ePadTouch   = 0x20
};

enum ERotationType {
	eNoloRotation = 0x01,
	eHmdRotation
};
#pragma pack(push,1)

struct Controller
{   // 4+12+16+4+4+8+4+4 = 56
	int VersionID;
	NVector3 Position;
	NQuaternion Rotation;
	UINT Buttons;
	int Touched;
	NVector2 TouchAxis;
	int Battery;
	int State;
};

struct HMD
{ // 4+12+12+4+16+4 = 52
	int HMDVersionID;
	NVector3 HMDPosition;
	NVector3 HMDInitPostion;//
	UINT HMDTwoPointDriftAngle;//已弃用
	NQuaternion HMDRotation;
	int HMDState;
};

struct BaseStation
{// 8
	int BaseStationVersionID;
	int BaseStationPower;
};

struct NoloSensorData
{//12*6 = 72
	NVector3 vecLVelocity;
	NVector3 vecLAngularVelocity;
	NVector3 vecRVelocity;
	NVector3 vecRAngularVelocity;
	NVector3 vecHVelocity;
	NVector3 vecHAngularVelocity;
};

struct NOLOData
{
	Controller leftData;  
	Controller rightData;
	HMD hmdData;
	BaseStation bsData;
	byte expandData[64];
	NoloSensorData NoloSensorData;
	UCHAR leftPackNumber;
	UCHAR rightPackNumber;
	NVector3 FixedEyePosition;
};

#pragma pack(pop)

//CStyle FunPotinters
typedef void(__cdecl *pfnKeyEvent)(ENoloDeviceType DevType, UCHAR Keys);
typedef void(__cdecl *pfnKeyUpDownEvent)(ENoloDeviceType DevType, EControlerButtonType type);
typedef void(__cdecl *pfnVoidCallBack)();
typedef void(__cdecl *pfnDataCallBack)(const NOLOData &noloData);
typedef void(__cdecl *pfnVoidIntCallBack)(int Versions);

enum EClientCallBackTypes
{
	eOnZMQConnected = 0,  
	eOnZMQDisConnected,       
	eOnButtonDoubleClicked, 
	eOnKeyPressEvent,
	eOnKeyReleaseEvent,
	eOnNewData,        // pfnDataCallBack
	eOnNoloDevVersion, // pfnVoidIntCallBack
	eCallBackCount
};


//不要在派生类中阻塞任何回调函数，以及处理耗时的工作
class INOLOZMQEvent
{
public:
	//已经与服务端建立连接
	virtual void OnZMQConnected() = 0;
	//已经与服务端断开连接
	virtual void OnZMQDisConnected() = 0;
	//DevType存在的某个按键被双击了 
	//通过判断 （Keys & EControlerButtonType::XX）来判断该按钮是否被双击了
	virtual void OnKeyDoubleClicked(ENoloDeviceType DevType, UCHAR Keys) {};
	//存在按钮被按下
	virtual void OnButtonPressed(ENoloDeviceType device, EControlerButtonType type) {};
	//存在按钮被抬起
	virtual void OnButtonRelease(ENoloDeviceType device, EControlerButtonType type) {};
	//新数据
	virtual void OnNewData(const NOLOData &_noloData) {};
	//判断Nolo设备是否需要更新
	virtual void OnNoloDevNeedUpdate(int Versions) {};

};

}