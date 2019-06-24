
#pragma once
#ifndef _ZMQRECEIVELIB_H_
#define _ZMQRECEIVELIB_H_

#include "Nolo_DeviceType.h"
//Disable 不兼容UDT的C类型
#pragma warning(disable:4190)

namespace NOLOVR
{

extern "C"
{
	/*************************************************
	功能描述: 启动NoloServer
	参数列表:
			  @ StrServerPath 【输入】 指定 NoloServer.exe 路径，如果没有指定路径，
			  默认到NoloClientLib.dll 同级目录的NoloServer目录下查找
	返 回 值: 如果启动Server成功，返回true,否则返回false
	其它说明: 无
	*************************************************/
	NOLO_API bool __cdecl StartNoloServer(const wchar_t *StrServerPath = L"");

	/*************************************************
	功能描述: 设置事件监听接口类指针,C++ 语言调用
	参数列表:
			  @ Listener  【输入】 从接口INOLOZQMEvent派生的类 实例指针
	返 回 值: void
	其它说明: 无
	*************************************************/
	NOLO_API void __cdecl SetEventListener(INOLOZMQEvent *Listener);

	/*************************************************
	功能描述: 设置是否使用悬挂模式，
	参数列表:
		  @ bCellingMode  【输入】 true 为 悬挂模式， false 为平放模式
	返 回 值: void
	其它说明: 此函数必须要ZMQ建立连接后，调用才会生效，推荐在回调函数OnZMQConnected()中调用
			  通常情况下，不建议客户使用悬挂模式，推荐C++开发下使用本接口
	*************************************************/
	NOLO_API void __cdecl SetBCellingMode(bool bCellingMode);

	/*************************************************
	功能描述: 设置回调 与SetEventListener,二者选一,不可混用
	参数列表:
			  @ callBackType  【输入】 回调类型
			  @ pCallBackFun  【输入】 函数指针
	返 回 值: void
	其它说明: 推荐C#使用本接口
	*************************************************/
	NOLO_API void __cdecl RegisterCallBack(EClientCallBackTypes callBackType, void *pCallBackFun);

	/*************************************************
	功能描述: 头盔旋转中心转换设置
	参数列表:
			  @ hmdCenter 【输入】 从 [双眼中点] 到 [头盔定位器] 的位移向量值
	返 回 值: void
	其它说明: 当需要使用头部位置时，应该设置该值进行头部位置转换，
			  向量坐标系：x正方向: 右， y正方向: 上，z正方向：前
			  示例值： (0.00f,0.08f,0.08f)
	*************************************************/
	NOLO_API void __cdecl SetHmdCenter(const NVector3 &hmdCenter);

	/*************************************************
	功能描述: 打开ZMQ监听
	参数列表: 无
	返 回 值: 打开成功返回 true,失败则返回 false
	其它说明: 必须调用此函数，SDK才会接收Nolo数据，前提是NoloServer
			  或者 NOLOHOME 已经打开
	*************************************************/
	NOLO_API bool __cdecl OpenNoloZeroMQ();

	/*************************************************
	功能描述: 关闭ZMQ监听
	参数列表: 无
	返 回 值: void
	其它说明: 无
	*************************************************/
	NOLO_API void __cdecl CloseNoloZeroMQ();

	/*************************************************
	功能描述: 向NOLO手柄发送震动命令
	参数列表:
			  @ deviceType 【输入】 手柄类型，有效值为：eLeftController,eRightController
			  @ intensity  【输入】 震动强度，从弱到强： 50 - 100
	返 回 值: 无
	其它说明: 一次调用震动一帧的时长，约16ms 。
	*************************************************/
	NOLO_API void __cdecl TriggerHapticPulse(ENoloDeviceType deviceType, int intensity);

	/*************************************************
	功能描述: 获取最新的NOLO左手柄数据
	参数列表: 无
	返 回 值: @ Controller
	其它说明: 无
	*************************************************/
	NOLO_API Controller __cdecl GetLeftControllerData();

	/*************************************************
	功能描述: 获取最新的NOLO右手柄数据
	参数列表: 无
	返 回 值: @ Controller
	其它说明: 无
	*************************************************/
	NOLO_API Controller __cdecl GetRightControllerData();

	/*************************************************
	功能描述: 获取最新的NOLO头盔定位器数据
	参数列表: 无
	返 回 值: @ HMD
	其它说明: 无
	*************************************************/
	NOLO_API HMD        __cdecl GetHMDData();

	/*************************************************
	功能描述: 获取最新的NOLO头盔定位器数据
	参数列表: 无
	返 回 值: @ NOLOData
	其它说明: 无
	*************************************************/
	NOLO_API NOLOData   __cdecl GetNoloData();

	/*************************************************
	功能描述: 向Server端发送命令
	参数列表: @CmdContent 是一个json字符串，如 "{Type:\"ShowPsvr\",Msg:\"OK\"}"，内容与客户端商定
				最大字符串数目 60
	返 回 值: @ NOLOData
	其它说明: 无
	*************************************************/
	NOLO_API void   __cdecl SendUIComand(const char *strCmdContent);

}

}
#endif // !_ZMQRECEIVELIB_H_