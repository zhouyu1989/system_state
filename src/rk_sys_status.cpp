/**************************************************************
 * Copyright (c) 2018-2020,Hangzhou Rokid Tech. Co., Ltd.
 * All rights reserved.
 *
 * FileName: rk_sys_status.h
 * Description: Dynamic library interface
 *
 * Date  :	2018.09.18
 * Author:  zhouyu
 * Modification: add file
 *
 **************************************************************/

#include "../include/rk_sys_status.h"

using namespace ROKID_SYSTEM;

/*******************************************************
* Function name ：CpuState
* Description: Capture CPU utilization
* Parameter：
*   @fCpuUsed	:CPU usage
* Return ：0 success, other fail
**********************************************************/
int CpuState(float &fCpuUsed)
{
	int ret=0;
	CSystemState system_status;

	ret=system_status.CpuState(fCpuUsed);
	if(ret < 0)
	{
		return -1;
	}

	return 0;
}

/*******************************************************
* Function name ：Memorystate
* Description: Get memory status
* Parameter：
*   @fMemUsed	:memory usage
*   @u64Used	:Used  size
*   @u64Unused	:unUsed size
* Return ：0 success, other fail
**********************************************************/
int Memorystate(float &fMemUsed, uint64_t &u64Used, uint64_t &u64Unused)
{
	int ret=0;
	CSystemState system_status;

	ret=system_status.Memorystate(fMemUsed, u64Used, u64Unused);
	if(ret < 0)
	{
		return -1;
	}

	return 0;
}

/*******************************************************
* Function name ：FlashState
* Description: Get Flash status
* Parameter：
*   @fFlashUsed		:Flash usage
*   @u64Used		:Used  size
*   @u64Unused		:unUsed size
* Return ：0 success, other fail
**********************************************************/
int FlashState(float &fFlashUsed,  float &u64Used, float &u64Unused)
{
	int ret=0;
	CSystemState system_status;

	ret=system_status.FlashState(fFlashUsed, u64Used, u64Unused);
	if(ret < 0)
	{
		return -1;
	}

	return 0;
}

/*******************************************************
* Function name ：NetState
* Description: Get network status
* Parameter：
*   @nNetstate	:network status :network disconnect -1, Normal network 0, weak network 1
* Return ：0 success, other fail
**********************************************************/
int NetState(int &nNetstate)
{
	int ret=0;
	CSystemState system_status;

	ret=system_status.NetState(nNetstate);
	if(ret < 0)
	{
		return -1;
	}

	return 0;
}




