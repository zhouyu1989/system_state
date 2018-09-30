/**************************************************************
 * Copyright (c) 2018-2020,Hangzhou Rokid Tech. Co., Ltd.
 * All rights reserved.
 *
 * FileName: SystemInfo.cpp
 * Description: Gets information about the device's CPU, memory, and so on
 *
 * Date  :	2018.09.18
 * Author:  zhouyu
 * Modification: add file
 *
 **************************************************************/

//#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include "SystemInfo.h"

//using namespace std;
using namespace ROKID_SYSTEM;

/*******************************************************
* Function name ：CSysInfo
* Description: econstructor function
* Parameter：
*   @
* Return ：0 success, other fail
**********************************************************/
CSysInfo::CSysInfo()
{

}

/*******************************************************
* Function name ：~CSysInfo
* Description: destructor function
* Parameter：
*   @
* Return ：0 success, other fail
**********************************************************/
CSysInfo::~CSysInfo()
{

}

/*******************************************************
* Function name ：GetCPUinfo
* Description: Capture CPU utilization
* Parameter：
*   @fCpuUsage	:CPU usage
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::GetCPUinfo(float &fCpuUsage)
{
	cpu_info_s oldtime;
	cpu_info_s newtime;
	memset(&oldtime, 0 , sizeof(cpu_info_s));
	memset(&newtime, 0 , sizeof(cpu_info_s));

	//first data collection
	if(GetCpuCurState(&oldtime) < 0)
	{
		fCpuUsage = 0.0;
		return -1;
	}

	usleep(SLEEPTIME);
	//second data collection
	if(GetCpuCurState(&newtime) < 0)
	{
		fCpuUsage = 0.0;
		return -1;
	}

	//calculate usage
	CalCpuUsage(&oldtime, &newtime,fCpuUsage);

	return 0;
}

/*******************************************************
* Function name ：GetMeninfo
* Description: Get memory information
* Parameter：
*   @fMemUsage	:memory usage
*   @u64Used	:Used  size
*   @u64Unused	:unUsed size
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::GetMeninfo(float &fMemUsage, uint64_t &u64Used, uint64_t &u64Unused)
{
	memory_info_s meminfo;
	memset(&meminfo, 0 , sizeof(meminfo));
	if(GetMemInfo(&meminfo)<0)
	{
		fMemUsage=0;
		return -1;
	}

	fMemUsage=(1-((float)meminfo.available/meminfo.total))*100.0;
	u64Unused=meminfo.available;
	u64Used=meminfo.total-meminfo.available;

	return 0;
}

/*******************************************************
* Function name ：GetFlashinfo
* Description: Get Flash information
* Parameter：
*   @fFlashUsage	:Flash usage
*   @u64Used		:Used  size
*   @u64Unused		:unUsed size
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::GetFlashinfo(float &fFlashUsage, float &u64Used, float &u64Unused)
{
	int nRet=0;
	flash_info_s flashdate;
	memset(&flashdate,0,sizeof(flashdate));

	if((nRet=GetFlashInfo(&flashdate))<0)
	{
		return -1;
	}

	u64Used=flashdate.Flashused;
	u64Unused=flashdate.FlashUnsed;
	fFlashUsage=flashdate.Flashused/flashdate.FlashTotal;

	return 0;
}

/*******************************************************
* Function name ：GetNetinfo
* Description: Get network status
* Parameter：
*   @nNetstate	:network status
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::GetNetinfo(int &nNetstate)
{
	int nRet=0;
	bool bNetStatus=false;

	//check network is open
	if((nRet=NetDetect(NETINTERFACE,bNetStatus))!=0)
	{
		return -1;
	}

	if(false==bNetStatus)
	{
		nNetstate=-1;
		return 0;
	}

	//check network is connected
	nRet=ping_check(PINGHOST);
	if(nRet==1)
	{
		nNetstate=1;
		return 0;
	}
	else if(nRet==-1)
	{
		nNetstate=-1;
		return 0;
	}

	//check weak network stat
	nRet=IsWeakNetwork(bNetStatus);
	if((0==nRet)&&true==bNetStatus)
	{
		nNetstate=1;
	}
	else if((0==nRet)&&false==bNetStatus)
	{
		nNetstate=0;
	}
	else if(nRet<0)
	{
		printf("check weak net failed\n");
	}

	return 0;
}

/*******************************************************
* Function name ：GetCpuCurState
* Description: Get cpu current status
* Parameter：
*   @cpust	: cpu info struct
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::GetCpuCurState(cpu_info_s *cpust)
{
	FILE *fd;
	char buff[256];
	char *pstatus;
	cpu_info_s *cpu_occupy;
	cpu_occupy=cpust;

	fd = fopen("/proc/stat", "r");
	if(fd == NULL)
		return -1;

	pstatus =fgets(buff, sizeof(buff), fd);
	if(pstatus == NULL)
	{
		fclose(fd);
		return -1;
	}

	if(sscanf(buff, "%s %u %u %u %u %u %u %u", cpu_occupy->name
				,&cpu_occupy->user, &cpu_occupy->nice,&cpu_occupy->sys, &cpu_occupy->idle
				,&cpu_occupy->iowait, &cpu_occupy->irq,&cpu_occupy->softirq) != 8)
	{
		fclose(fd);
		return -1;

	}
	fclose(fd);

	return 0;
}

/*******************************************************
* Function name ：CalCpuUsage
* Description: calculate cpu usage
* Parameter：
*   @poldtime	:previous time
*   @pnewtime	:latter time
*   @CpuUage	:cpu usage
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::CalCpuUsage(cpu_info_s *poldtime, cpu_info_s *pnewtime, float &CpuUage)
{
	unsigned long oldtotal=0;
	unsigned long newtotal=0;
//	unsigned long usertotal=0;
//	unsigned long systotal=0;
	float idleTotal=0;

	oldtotal = poldtime->user + poldtime->nice + poldtime->sys + poldtime->idle + poldtime->iowait + poldtime->irq + poldtime->softirq;
	newtotal = pnewtime->user + pnewtime->nice + pnewtime->sys + pnewtime->idle + pnewtime->iowait + pnewtime->irq + pnewtime->softirq;

//	usertotal = pnewtime->user - poldtime->user;
//	systotal = pnewtime->sys - poldtime->sys;
	idleTotal = pnewtime->idle - poldtime->idle;

	if ((newtotal-oldtotal) != 0)
	{
		CpuUage = (1-(idleTotal / (newtotal-oldtotal)))*100;
	}
	else
	{
		CpuUage = 0;
	}

	return 0;
}

/*******************************************************
* Function name ：GetMemInfo
* Description: Get memory information
* Parameter：
*   @poldtime	:previous time
*   @pnewtime	:latter time
*   @CpuUage	:cpu usage
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::GetMemInfo(memory_info_s *pmeminfo)
{
	FILE *pf;
	char buff[256];
	char temp[20];

	pf = fopen ("/proc/meminfo", "r");
	if(pf == NULL)
		return -1;

	char *pstatus = NULL;
	pstatus = fgets (buff, sizeof(buff), pf);
	if( pstatus == NULL )
	{
		fclose(pf);
		return -1;
	}

	if(sscanf(buff, "%s %lu %s", pmeminfo->nameTotal, &pmeminfo->total, temp) != 3)
	{
		fclose(pf);
		return -1;
	}

	pstatus = fgets (buff, sizeof(buff), pf);
	if( pstatus == NULL )
	{
		fclose(pf);
		return -1;
	}

	if(sscanf(buff, "%s %lu %s", pmeminfo->nameFree, &pmeminfo->free, temp) != 3)
	{
		fclose(pf);
		return -1;
	}

	pstatus = fgets (buff, sizeof(buff), pf);
	if( pstatus == NULL )
	{
		fclose(pf);
		return -1;
	}

	if(sscanf (buff, "%s %lu %s", pmeminfo->nameAvailable, &pmeminfo->available, temp) !=3)
	{
		fclose(pf);
		return -1;
	}

	fclose(pf);

	return 0;
}

/*******************************************************
* Function name ：GetFlashInfo
* Description: Get flash information
* Parameter：
*   @pFlashinfo	:flash info
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::GetFlashInfo(flash_info_s* pFlashinfo)
{
	FILE * fp=NULL;
	char a[80],e[80],f[80],buf[256];
	double tmp_total=0;
	double tmp_used=0;
	double tmp_unused=0;
	double dev_total=0,dev_used=0;

	if(pFlashinfo==NULL)
	{
		return -1;
	}

	fp=popen("df","r");
	if(fp<0)
	{
		return -2;
	}
	fgets(buf,256,fp);

	while(6==fscanf(fp,"%s %lf %lf %lf %s %s", a, &tmp_total, &tmp_used, &tmp_unused, e, f))
	{
			dev_total+=tmp_total;
			dev_used+=tmp_used;
	}
	pFlashinfo->FlashTotal=dev_total/(1024*1024);
	pFlashinfo->Flashused=dev_used/(1024*1024);
	pFlashinfo->FlashUnsed=pFlashinfo->FlashTotal-pFlashinfo->Flashused;

	pclose(fp);

	return 0;
}

/*******************************************************
* Function name ：ping_check
* Description: Detect network connectivity
* Parameter：
*   @hostaddr	:ping addr
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::ping_check(char *hostaddr)
{
	FILE *fp;
	size_t len = 0;
	char *pos;
	int nRet=0;
	int ret=0;
	int percent = 100;
	char* line = NULL;
	char szcmd[80]={0};

	sprintf(szcmd, "ping -c 1 -q -n %s",hostaddr);
	fp=popen(szcmd,"r");
	if(fp<0)
	{
		return -1;
	}

	nRet=getline(&line, &len, fp);
	if(nRet==-1)
	{
		printf("network error\n");
		pclose(fp);
		free(line);
		return -1;
	}
	while (getline (&line, &len, fp) != -1)
	{
		if (strncmp ("packets transmitted", line + 2, 19) != 0)
		{
		    continue;
		}
		pos = strchr (line, '%');
		if (pos == 0) {
			ret=1;
		}
		while (*pos != ' ')
		{
		  pos--;
		}
		sscanf (pos, " %d%% loss", &percent);
		printf("ping_check->pos -- %s\n", pos);
		printf("ping_check->percent -- %d \n", percent);
		if (percent == 0)
		{
		    printf("ping_check:OK\n");
		    ret=0;
		}
		else
		{
			ret=1;
		    printf("ping_check: lost package \n");
		}
	}
	pclose(fp);
	free(line);

	return ret;
}

/*******************************************************
* Function name ：NetDetect
* Description: calculate cpu usage
* Parameter：
*   @net_name	:network card name
*   @bNetUp		:network card status
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::NetDetect(char* net_name, bool &bNetUp)
{
	int skfd = 0;
	struct ifreq ifr;

	if(NULL==net_name)
	{
		return -1;
	}

	skfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(skfd < 0)
	{
		printf("%s:%d Open socket error!\n", __FILE__, __LINE__);
		return -1;
	}

	strcpy(ifr.ifr_name, net_name);

	if(ioctl(skfd, SIOCGIFFLAGS, &ifr) <0 )
	{
		printf("%s:%d IOCTL error!\n", __FILE__, __LINE__);
		printf("Maybe ethernet inferface %s is not valid!\n", ifr.ifr_name);
		close(skfd);
		return -1;
	}

	if(ifr.ifr_flags & IFF_RUNNING)
	{
		close(skfd);
		bNetUp=true;
	}
	else
	{
		close(skfd);
		bNetUp=false;
	}

	return 0;
}

/*******************************************************
* Function name ：current_net_speed
* Description: get current net speed
* Parameter：
*   @u64RecvBite	:get bite
*   @u64SendBite	:send bite
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::current_net_speed(uint64_t &u64RecvBite, uint64_t &u64SendBite)
{

	int nRet=0;
	size_t nDatalen=0;
	FILE *fp;
	unsigned int a,b,c,d,e,f,g,h,i,j,k,l,m,n;
	char* buff = NULL;
	char szcmd[32]={0};
	char sztmp[12]={0};

	sprintf(szcmd, "cat /proc/net/dev|grep %s",NETINTERFACE);
	fp=popen(szcmd,"r");
	if(fp<0)
	{
		return -1;
	}

	nRet=getline(&buff, &nDatalen, fp);
	if(-1 == nDatalen)
	{
		return -1;
	}
	if(17!=(nRet=sscanf(buff,"%s %llu %u %u %u %u %u %u %u %llu %u %u %u %u %u %u %u",
			sztmp,&u64RecvBite,&a,&b,&c,&d,&e,&f,&g,&u64SendBite,&h,&i,&j,&k,&l,&m,&n)))
	{
		printf("Analytical net parameters failed\n");
		free(buff);
		buff=NULL;
		return -1;
	}

	if(NULL!=buff)
	{
		free(buff);
		buff=NULL;
	}

	return 0;
}

/*******************************************************
* Function name ：IsWeakNetwork
* Description: check is weak network
* Parameter：
*   @bweakNet	:weak network status
* Return ：0 success, other fail
**********************************************************/
int CSysInfo::IsWeakNetwork(bool &bweakNet)
{
	int ret=0;
	uint64_t old_recv_bite=0;
	uint64_t old_rend_bite=0;
	uint64_t new_recv_bite=0;
	uint64_t new_rend_bite=0;
	float upspeed=0;
	float downspeed=0;

	if((ret=current_net_speed(old_recv_bite, old_rend_bite))<0)
	{
		return -1;
	}

	sleep(5);

	if((ret=current_net_speed(new_recv_bite, new_rend_bite))<0)
	{
		return -1;
	}

	upspeed=(new_recv_bite-old_recv_bite)/5;

	downspeed=(new_rend_bite-old_recv_bite)/5;

	if(((uint64_t)upspeed - WEAKNETFLAG < 0) || (uint64_t)downspeed - WEAKNETFLAG < 0)
	{
		bweakNet=true;
	}
	else
	{
		bweakNet=false;
	}

	return 0;
}
