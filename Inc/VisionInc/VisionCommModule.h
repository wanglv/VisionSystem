#ifndef __VISION_COMM_MODULE_H__
#define __VISION_COMM_MODULE_H__

#pragma once
#include "VisionCommBase.h"

CVisionCommBase*  __stdcall CreateInterface() ;
void          __stdcall ReleaseInterface(CVisionCommBase* pInterface) ;

#endif
