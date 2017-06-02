#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"
#include "define.h"

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
#include  "MK60_dma.h"

#include  "VCAN_LED.H"          //LED
#include  "VCAN_KEY.H"          //KEY

#include "IIC.h"            //L3G4200D��MMA845X
#include "calculation.h"    //CCD������
#include "upper monitor.h"  //������ʾ��λ��������
#include "math.h"           //�ߵ���ѧ.h
#include "oled.h"           //OLED����
#include "ccdwork.h"        //CCDȡ�ߡ������
#include "math.h"

#include  "VCAN_camera.h"       //����ͷ��ͷ�ļ�
#include  "Startline_Ren_Block.h"
#include  "Process.h"
#include  "SmallS_Cross.h"
#include "VCAN_OV7725_Eagle.h"


//ͼ��
#define Process_Hang 240
#define Lie 320
#define WHITE 0
#define BLACK 1
#define CENTER 160
#define Stand_Time 3000

/*************************************************************************
*  ģ�����ƣ��ṹ��ͱ���ģ��
*  ����˵����Include �û��Զ���Ľṹ��ͱ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14
*************************************************************************/
struct CarAngle
{
    //���ٶȲŵõ�ֵ��a_sinΪ����z����ٶȣ���sinֵ
    float a_sin;
    float a_cos;
    //�����ǲɼ��Ľ��ٶ�ֵ
    float Gyro;   			
    float speed;
    //����ĽǶȣ�m_angleΪmma845x��õĽǶȣ�G_angleΪ�����ǻ��ֳ����ĽǶ�
    float m_angle;
    float G_angle;
    float OFFSET;//OFFSET_angleΪ��ֹʱ�ĽǶ�important    				
    //ƽ�ⲿ��PIDֵ
    float P;
    float D;   			
    float PWM;    			
};
struct CarSpeed
{
    //��λ
    unsigned char Mode;
    //�ٶȲ��֣���������ٶ�
    int L_5ms;
    int R_5ms;
    int L_100ms;
    int R_100ms;
    float Car;
    float Goal;
    float Goal_init;
    //�ٶȲ��֣�pid����
    float P;              //�ٶȿ���P����
    float I;              //�ٶȿ���I����
    float PWM_Per;  	//�ٶ�ÿ������ֵ
    float I_Error_Start;
    float I_Limit_PWM_max;
    float I_Limit_PWM_min;
    float PWM_Integral;	//�ٶȸ���PWM��ֵ���洢�Ļ���
    float PWM;        	//�ٶȸ���PWM��ֵ    			
};
struct CarDirection
{
    //���������ǵ�ֵ
    float Gyro;
    //pid����
    float P;  //*****************dir����P����**********************
    float D;	 //*****************dir����D����**********************	
    float PWM_Per;  		//����ÿ������ֵ
    float PWM;
    unsigned char output_enable;
};
struct CarStartLine
{
    unsigned char enable;//ʹ��
    unsigned char flag; //�����߱�־
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
    unsigned char flag; //�����߱�־
    unsigned int Loaction;//�������
    int Strength;
    float Angle_OFFSET[2];
};
struct CarBlock
{ 
    unsigned char enable;
    unsigned char flag;//�ϰ��ı�־
    int time;
    int delaytime;
    int Offset;
    int Offset_Init;
};


/*************************************************************************
*  ģ�����ƣ�û������
*  ����˵����Include �û��Զ����ȫ�ֱ�������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14
*************************************************************************/
extern struct CarAngle Angle;
extern struct CarSpeed Speed;
extern struct CarDirection Direction;
extern struct CarStartLine StartLine;
extern struct CarRen Ren;
extern struct CarBlock Block;
extern long int Time_1ms;

   
   
#endif  //__INCLUDE_H__
