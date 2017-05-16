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
//�ӿ�˵��:�ýӿ�ΪHalcon�������Ӿ����ýӿ�                                       
//_V_Comm_InitCtrl:��ʼ����ʾ���� nCtrlImageWidth/nCtrlImageHeight:��ʾ�ؼ��Ŀ�/�� lWindowID:��ʾ�ؼ����
//                 nImageWidth/nImageHeight:��ʾͼ��Ŀ�/�� hWindowID:��ʼ���ɹ������ID
//
//_V_Comm_HObjectIsEmpty:�ж�Obj�Ƿ�Ϊ�� Empty---1 or 0
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

