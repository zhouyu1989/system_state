/**************************************************************
 * Copyright (c) 2018-2020,Hangzhou Rokid Tech. Co., Ltd.
 * All rights reserved.
 *
 * FileName: SystemStatus.h
 * Description: Gets the header file for information such as CPU memory Flash
 *
 * Date  :	2018.09.18
 * Author:  zhouyu
 * Modification: add file
 *
 **************************************************************/

#ifndef ROKID_SYSTEMSTATUS_H_
#define ROKID_SYSTEMSTATUS_H_

#include <stdint.h>
#include "SystemInfo.h"

namespace ROKID_SYSTEM
{
	class CSystemState
	{
	public:
		//CPU usage
		float m_fCpuUsage;
		//memory used
		uint64_t m_u64MemUsed;
		//memory unused
		uint64_t m_u64MenUnused;
		//flash used
		uint64_t m_u64FlashUsed;
		//flash unused
		uint64_t m_u64FlashUnused;
		//flash usage
		float m_fFlashUsage;
		//network stat
		int m_nNetStatus;

		CSysInfo m_cSysinfo;

	public:
	    /*******************************************************
	    * Function name ：CSystemState
	    * Description: econstructor function
	    * Parameter：
	    *   @
	    * Return ：
	    **********************************************************/
		CSystemState();

	    /*******************************************************
	    * Function name ：~CSystemState
	    * Description: destructor function
	    * Parameter：
	    *   @
	    * Return ：0 success, other fail
	    **********************************************************/
		~CSystemState();

	    /*******************************************************
	    * Function name ：CpuState
	    * Description: Capture CPU utilization
	    * Parameter：
	    *   @fCpuUsed	:CPU usage
	    * Return ：0 success, other fail
	    **********************************************************/
		int CpuState(float &fCpuUsed);

	    /*******************************************************
	    * Function name ：Memorystate
	    * Description: Get memory status
	    * Parameter：
	    *   @fMemUsed	:memory usage
	    *   @u64Used	:Used  size
	    *   @u64Unused	:unUsed size
	    * Return ：0 success, other fail
	    **********************************************************/
		int Memorystate(float &fMemUsed, uint64_t &u64Used, uint64_t &u64Unused);

	    /*******************************************************
	    * Function name ：FlashState
	    * Description: Get Flash status
	    * Parameter：
	    *   @fFlashUsed		:Flash usage
	    *   @u64Used		:Used  size
	    *   @u64Unused		:unUsed size
	    * Return ：0 success, other fail
	    **********************************************************/
		int FlashState(float &fFlashUsed,  float &u64Used, float &u64Unused);

	    /*******************************************************
	    * Function name ：NetState
	    * Description: Get network status
	    * Parameter：
	    *   @nNetstate	:network status :network disconnect -1, Normal network 0, weak network 1
	    * Return ：0 success, other fail
	    **********************************************************/
		int NetState(int &nNetstate);

		//函数名称：BatteryState
		//函数作用：获取电池信息
		//函数返回值：成功 0 失败非0
		//函数输入：无
		//函数输出：fBatteryUnused		使用率
		//int BatteryState(float &fFlashUnused);
	};
}

#endif /* ROKID_SYSTEMSTATUS_H_ */
