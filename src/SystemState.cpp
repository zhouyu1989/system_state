/**************************************************************
 * Copyright (c) 2018-2020,Hangzhou Rokid Tech. Co., Ltd.
 * All rights reserved.
 *
 * FileName: SystemState.cpp
 * Description: Gets information about the device's CPU, memory, and so on
 *
 * Date  :	2018.09.18
 * Author:  zhouyu
 * Modification: add file
 *
 **************************************************************/

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "SystemStatus.h"

using namespace std;
using namespace ROKID_SYSTEM;

/*******************************************************
* Function name ：CSystemState
* Description: econstructor function
* Parameter：
*   @
* Return ：0 success, other fail
**********************************************************/
CSystemState::CSystemState()
: m_fCpuUsage(0),
  m_u64MemUsed(0),
  m_u64MenUnused(0),
  m_u64FlashUsed(0),
  m_u64FlashUnused(0),
  m_fFlashUsage(0),
  m_nNetStatus(0)
{

}

/*******************************************************
* Function name ：~CSystemState
* Description: destructor function
* Parameter：
*   @
* Return ：0 success, other fail
**********************************************************/
CSystemState::~CSystemState()
{

}

/*******************************************************
* Function name ：CpuState
* Description: Capture CPU utilization
* Parameter：
*   @fCpuUsed	:CPU usage
* Return ：0 success, other fail
**********************************************************/
int CSystemState::CpuState(float &fCpuUsed)
{
	int ret=0;
	ret=m_cSysinfo.GetCPUinfo(fCpuUsed);
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
int CSystemState::Memorystate(float &fMemUsed, uint64_t &u64Used, uint64_t &u64Unused)
{
	int ret=0;
	ret=m_cSysinfo.GetMeninfo(fMemUsed, u64Used, u64Unused);
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
int CSystemState::FlashState(float &fFlashUsed, float &u64Used, float &u64Unused)
{
	int ret=0;
	ret=m_cSysinfo.GetFlashinfo(fFlashUsed, u64Used, u64Unused);
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
int CSystemState::NetState(int &nNetstate)
{
	int ret=0;
	ret=m_cSysinfo.GetNetinfo(nNetstate);
	if(ret < 0)
	{
		return -1;
	}

	return 0;
}

