/**************************************************************
 * Copyright (c) 2018-2020,Hangzhou Rokid Tech. Co., Ltd.
 * All rights reserved.
 *
 * FileName: SystemInfo.h
 * Description: Gets the header file for information such as CPU memory Flash
 *
 * Date  :	2018.09.18
 * Author:  zhouyu
 * Modification: add file
 *
 **************************************************************/

#ifndef ROKID_SYSTEMINFO_H_
#define ROKID_SYSTEMINFO_H_

namespace ROKID_SYSTEM
{
#include <stdint.h>

#define WEAKNETFLAG 10.0
#define SLEEPTIME 1000*500
#define PINGHOST "www.baidu.com"
#define NETINTERFACE "ens33"

	//网络状态枚举
	enum ENETSTATE
	{
		//网络未连接
		ENETUNCONNECT = 0,
		//weak network
		EWEAKNETWORK = 1,
		//正常网络
		ENORMALNET = 2
	};

	class CSysInfo
	{
	public:
	    typedef struct CPUINFO
	    {
	        char name[20];
	        unsigned int user;
	        unsigned int nice;
	        unsigned int sys;
	        unsigned int idle;
	        unsigned int iowait;
	        unsigned int irq;
	        unsigned int softirq;
	    }cpu_info_s;

	    typedef struct MEMInfo
	    {
	        char nameTotal[20];
	        unsigned long total;
	        char nameFree[20];
	        unsigned long free;
	        char nameAvailable[20];
	        unsigned long available;
	    }memory_info_s;

	    typedef struct FlashInfo
	    {
	    	float FlashTotal;
	    	float FlashUnsed;
	    	float Flashused;
	    }flash_info_s;

	public:
	    /*******************************************************
	    * Function name ：CSysInfo
	    * Description: econstructor function
	    * Parameter：
	    *   @
	    * Return ：
	    **********************************************************/
	    CSysInfo();

	    /*******************************************************
	    * Function name ：~CSysInfo
	    * Description: destructor function
	    * Parameter：
	    *   @
	    * Return ：
	    **********************************************************/
	    ~CSysInfo();

	    /*******************************************************
	    * Function name ：GetCPUinfo
	    * Description: Capture CPU utilization
	    * Parameter：
	    *   @fCpuUsage	:CPU usage
	    * Return ：0 success, other fail
	    **********************************************************/
	    int GetCPUinfo(float &fCpuUsage);

	    /*******************************************************
	    * Function name ：GetMeninfo
	    * Description: Get memory information
	    * Parameter：
	    *   @fMemUsage	:memory usage
	    *   @u64Used	:Used  size
	    *   @u64Unused	:unUsed size
	    * Return ：0 success, other fail
	    **********************************************************/
	    int GetMeninfo(float &fMemUsage, uint64_t &u64Used, uint64_t &u64Unused);

	    /*******************************************************
	    * Function name ：GetFlashinfo
	    * Description: Get Flash information
	    * Parameter：
	    *   @fFlashUsage	:Flash usage
	    *   @u64Used		:Used  size
	    *   @u64Unused		:unUsed size
	    * Return ：0 success, other fail
	    **********************************************************/
	    int GetFlashinfo(float &fFlashUsage, float &u64Used, float &u64Unused);

	    /*******************************************************
	    * Function name ：GetNetinfo
	    * Description: Get network status
	    * Parameter：
	    *   @nNetstate	:network status :network disconnect -1, Normal network 0, weak network 1
	    * Return ：0 success, other fail
	    **********************************************************/
	    int GetNetinfo(int &nNetstate);

	private:
	    /*******************************************************
	    * Function name ：GetCpuCurState
	    * Description: Get cpu current status
	    * Parameter：
	    *   @cpust	: cpu info struct
	    * Return ：0 success, other fail
	    **********************************************************/
	    int GetCpuCurState(cpu_info_s *cpust);

	    /*******************************************************
	    * Function name ：CalCpuUsage
	    * Description: calculate cpu usage
	    * Parameter：
	    *   @poldtime	:previous time
	    *   @pnewtime	:latter time
	    *   @CpuUage	:cpu usage
	    * Return ：0 success, other fail
	    **********************************************************/
	    int CalCpuUsage(cpu_info_s *poldtime, cpu_info_s *pnewtime, float &CpuUage);

	    /*******************************************************
	    * Function name ：GetMemInfo
	    * Description: Get memory information
	    * Parameter：
	    *   @poldtime	:previous time
	    *   @pnewtime	:latter time
	    *   @CpuUage	:cpu usage
	    * Return ：0 success, other fail
	    **********************************************************/
	    int GetMemInfo(memory_info_s *mem);

	    /*******************************************************
	    * Function name ：GetFlashInfo
	    * Description: Get flash information
	    * Parameter：
	    *   @pFlashinfo	:flash info
	    * Return ：0 success, other fail
	    **********************************************************/
	    int GetFlashInfo(flash_info_s* pFlashinfo);

	    /*******************************************************
	    * Function name ：ping_check
	    * Description: Detect network connectivity
	    * Parameter：
	    *   @hostaddr	:ping addr
	    * Return ：0 success, other fail
	    **********************************************************/
	    int ping_check(char *hostaddr);

	    /*******************************************************
	    * Function name ：NetDetect
	    * Description: calculate cpu usage
	    * Parameter：
	    *   @net_name	:network card name
	    *   @bNetUp		:network card status
	    * Return ：0 success, other fail
	    **********************************************************/
	    int NetDetect(char* net_name, bool &bNetUp);

	    /*******************************************************
	    * Function name ：current_net_speed
	    * Description: get current net speed
	    * Parameter：
	    *   @u64RecvBite	:get bite
	    *   @u64SendBite	:send bite
	    * Return ：0 success, other fail
	    **********************************************************/
	    int current_net_speed(uint64_t &u64RecvBite, uint64_t &u64SendBite);

	    /*******************************************************
	    * Function name ：IsWeakNetwork
	    * Description: check is weak network
	    * Parameter：
	    *   @bweakNet	:weak network status
	    * Return ：0 success, other fail
	    **********************************************************/
	    int IsWeakNetwork(bool &bweakNet);
	};
}

#endif /* ROKID_SYSTEMINFO_H_ */
