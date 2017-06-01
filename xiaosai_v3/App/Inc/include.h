#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include �û��Զ����ͷ�ļ�
 */
#include  "MK60_wdog.h"
#include  "MK60_it.H"
#include  "MK60_gpio.H"     //IO�ڲ���
#include  "MK60_uart.h"     //����
#include  "MK60_SysTick.h"
#include  "MK60_lptmr.h"    //�͹��Ķ�ʱ��(��ʱ)
#include  "MK60_pit.h"      //PIT
#include  "MK60_FLASH.h"    //FLASH
#include  "MK60_adc.h"
#include  "MK60_FTM.h"

#include  "VCAN_LED.H"          //LED
#include  "VCAN_KEY.H"          //KEY

#include "IIC.h"            //L3G4200D��MMA845X
#include "calculation.h"    //CCD������
#include "upper monitor.h"  //������ʾ��λ��������
#include "math.h"           //�ߵ���ѧ.h
#include "oled.h"           //OLED����
#include "ccdwork.h"        //CCDȡ�ߡ������



#endif  //__INCLUDE_H__
