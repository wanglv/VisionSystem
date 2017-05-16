#pragma once
#include <Windows.h>
#include "halconcpp.h"
using namespace HalconCpp;

enum _V_COMM_BACK_CODE
{
	_V_COMM_THROW = -1,
	_V_COMM_OK = 0 ,
	_V_COMM_NG ,
};


////////////////////////////////////////////////////////////////////////////////////////////////////////
//Author:William
//CopyRight:William
//接口说明:该接口为Halcon开发的视觉常用接口                                       
//_V_Comm_InitCtrl:初始化显示窗口 nCtrlImageWidth/nCtrlImageHeight:显示控件的宽/高 lWindowID:显示控件句柄
//                 nImageWidth/nImageHeight:显示图像的宽/高 hWindowID:初始化成功输出的ID
//
//_V_Comm_HObjectIsEmpty:判断Obj是否为空 Empty---1 or 0
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////


class CVisionCommBase
{
public:
	virtual int _V_Comm_InitCtrl(int nCtrlImageWidth,int nCtrlImageHeight,long lWindowID,int nImageWidth,\
		int nImageHeight,HTuple* hWindowID) = 0 ;

	virtual bool _V_Comm_HObjectIsEmpty(HObject& hObj) = 0 ;
};

