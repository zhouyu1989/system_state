/*
 *  test.cpp
 *	作用：测试文件
 *  Created on: 2018年9月18日
 *  Author: 周喻
 */

#include <iostream>
#include <stdio.h>
#include "../src/SystemStatus.h"
#include "../include/rk_sys_status.h"

using namespace std;
using namespace ROKID_SYSTEM;

int main()
{

	int ret =0;
	float cpu_used=0;
	float CPU_used1=0;
	float mem_used=0;
	uint64_t u64Used=0;
	uint64_t u64Unused=0;
	float FlashUsed=0;
	float flash_Used=0;
	float flash_Unused=0;
	int Net_state=0;
//	class CSystemState cSystem_Status;

	if((ret=CpuState(cpu_used))<0)
	{
		printf("get cpu used failed\n");
		return -1;
	}
	printf("cpu usage:%f\n",cpu_used);

	if((ret=Memorystate(mem_used,u64Used,u64Unused))<0)
	{
		printf("get cpu used failed\n");
		return -1;
	}
	printf("memory usage:%f used:%llu unused:%llu\n",mem_used, u64Used, u64Unused);

	if((ret=FlashState(FlashUsed,flash_Used,flash_Unused))<0)
	{
		printf("get cpu used failed\n");
		return -1;
	}
	printf("flash usage:%f flash_used:%f flash_unused:%f\n",FlashUsed,flash_Used,flash_Unused);

	if((ret=NetState(Net_state))<0)
	{
		printf("get cpu used failed\n");
		return -1;
	}
	printf("net stat:%d",Net_state);

	return 0;
}
