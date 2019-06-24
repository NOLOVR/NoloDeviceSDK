#pragma once

#ifndef _NOLO_MATH_H_
#define _NOLO_MATH_H_

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef SDKDLL_EXPORTS
#define NOLO_API __declspec(dllexport)
#else
#define NOLO_API __declspec(dllimport)
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#define NOLO_EC  extern "C"
#define safeDelte(p) if(p!=nullptr){delete p;p=nullptr;}

typedef unsigned int UINT;
typedef unsigned char byte;

namespace NOLOVR
{

struct NOLO_API  NVector2
{
public:
	float x;
	float y;
	float length();
	void  normalize();
};

struct NOLO_API  NVector3
{
public:
	NVector3();
	NVector3(float _x, float _y, float _z);
	void     set(float _x, float _y, float _z);
	NVector3 operator-(const NVector3 &_v1);
	float    operator*(const NVector3 &rhs);
	NVector3 operator*(const float rhs);
	NVector3 operator^(const NVector3 &rhs);
	NVector3 operator+(const NVector3 &rhs);
	NVector3 operator-(const float rhs);
	NVector3 operator/(const float rhs);
	NVector3 operator=(const NVector3 & rhs);
	bool     operator==(const NVector3 & rhs);
	float	 length();
	void	 normalize();
public:
	float x;
	float y;
	float z;
};

struct NOLO_API NQuaternion
{
public:
	NQuaternion();
	NQuaternion(float _x, float _y, float _z, float _w);
	NQuaternion(const NVector3 &xyz, float cw);
	NVector3 GetEulerAngle();
	NVector3 GetEulerAngle(const NQuaternion qa);
	float  length();
	void   normalize();
	static NQuaternion FromAnixAngle(NVector3 anix, float angle);
	NQuaternion operator*(const NQuaternion &qa);
	//通过此四元数旋转一个向量
	NVector3 operator*(NVector3 v)const;
public:
	float x;
	float y;
	float z;
	float w;
};


}

#endif