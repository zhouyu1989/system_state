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

#ifndef ROKID_RK_SYS_STATUS_H_
#define ROKID_RK_SYS_STATUS_H_

#include <stdint.h>
#include "../src/SystemStatus.h"

#ifdef __cplusplus
extern "C" {
#endif

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


#ifdef __cplusplus
}
#endif

#endif /* ROKID_RK_SYS_STATUS_H_ */
