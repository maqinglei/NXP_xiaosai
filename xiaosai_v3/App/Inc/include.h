#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"
#include "define.h"

/*
 * Include 用户自定义的头文件
 */
#include  "MK60_wdog.h"
#include  "MK60_it.H"
#include  "MK60_gpio.H"     //IO口操作
#include  "MK60_uart.h"     //串口
#include  "MK60_SysTick.h"
#include  "MK60_lptmr.h"    //低功耗定时器(延时)
#include  "MK60_pit.h"      //PIT
#include  "MK60_FLASH.h"    //FLASH
#include  "MK60_adc.h"
#include  "MK60_FTM.h"
#include  "MK60_dma.h"

#include  "VCAN_LED.H"          //LED
#include  "VCAN_KEY.H"          //KEY

#include "IIC.h"            //L3G4200D和MMA845X
#include "calculation.h"    //CCD的驱动
#include "upper monitor.h"  //波形显示上位机的驱动
#include "math.h"           //高等数学.h
#include "oled.h"           //OLED驱动
#include "ccdwork.h"        //CCD取线、计算等
#include "math.h"

#include  "VCAN_camera.h"       //摄像头总头文件
#include  "Startline_Ren_Block.h"
#include  "Process.h"
#include  "SmallS_Cross.h"
#include "VCAN_OV7725_Eagle.h"


//图像
#define Process_Hang 240
#define Lie 320
#define WHITE 0
#define BLACK 1
#define CENTER 160
#define Stand_Time 3000

/*************************************************************************
*  模块名称：结构体和变量模块
*  功能说明：Include 用户自定义的结构体和变量
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14
*************************************************************************/
struct CarAngle
{
    //加速度才得的值，a_sin为车的z轴加速度，即sin值
    float a_sin;
    float a_cos;
    //陀螺仪采集的角速度值
    float Gyro;   			
    float speed;
    //算出的角度：m_angle为mma845x测得的角度，G_angle为陀螺仪积分出来的角度
    float m_angle;
    float G_angle;
    float OFFSET;//OFFSET_angle为静止时的角度important    				
    //平衡部分PID值
    float P;
    float D;   			
    float PWM;    			
};
struct CarSpeed
{
    //档位
    unsigned char Mode;
    //速度部分：定义各种速度
    int L_5ms;
    int R_5ms;
    int L_100ms;
    int R_100ms;
    float Car;
    float Goal;
    float Goal_init;
    //速度部分：pid控制
    float P;              //速度控制P参数
    float I;              //速度控制I参数
    float PWM_Per;  	//速度每次增量值
    float I_Error_Start;
    float I_Limit_PWM_max;
    float I_Limit_PWM_min;
    float PWM_Integral;	//速度赋给PWM的值，存储的积分
    float PWM;        	//速度赋给PWM的值    			
};
struct CarDirection
{
    //方向陀螺仪的值
    float Gyro;
    //pid部分
    float P;  //*****************dir控制P参数**********************
    float D;	 //*****************dir控制D参数**********************	
    float PWM_Per;  		//方向每次增量值
    float PWM;
    unsigned char output_enable;
};
struct CarStartLine
{
    unsigned char enable;//使能
    unsigned char flag; //起跑线标志
    unsigned int time_record; 
    unsigned int Delaytime;
};
struct CarRen
{
    unsigned char enable;
    unsigned char Multiple_enable;
    int record_time;
    int Delaytime1;
    int Delaytime2;
    unsigned char flag; //起跑线标志
    unsigned int Loaction;//左或者右
    int Strength;
    float Angle_OFFSET[2];
};
struct CarBlock
{ 
    unsigned char enable;
    unsigned char flag;//障碍的标志
    int time;
    int delaytime;
    int Offset;
    int Offset_Init;
};


/*************************************************************************
*  模块名称：没有名称
*  功能说明：Include 用户自定义的全局变量声明
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14
*************************************************************************/
extern struct CarAngle Angle;
extern struct CarSpeed Speed;
extern struct CarDirection Direction;
extern struct CarStartLine StartLine;
extern struct CarRen Ren;
extern struct CarBlock Block;
extern long int Time_1ms;

   
   
#endif  //__INCLUDE_H__
