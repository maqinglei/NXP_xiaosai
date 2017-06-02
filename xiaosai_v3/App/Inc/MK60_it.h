///*!
// *     COPYRIGHT NOTICE
// *     Copyright (c) 2013,ɽ��Ƽ�
// *     All rights reserved.
// *     �������ۣ�ɽ���ѧ��̳ http://www.vcan123.com
// *
// *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
// *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
// *
// * @file       MK60_it.h
// * @brief      ɽ��K60 ƽ̨�жϸ�λ�ض���ͷ�ļ�
// * @author     ɽ��Ƽ�
// * @version    v5.0
// * @date       2013-06-26
// */
//
//
//#ifndef __MK60_IT_H__
//#define __MK60_IT_H__
//
//#define L_DeCoder  PTA12//PTC11
//#define R_DeCoder  PTA10//PTC10
//
//#define MOTOR_FTM   FTM0
//#define MOTOR1_PWM  FTM_CH3
//#define MOTOR2_PWM  FTM_CH4
//#define MOTOR3_PWM  FTM_CH5
//#define MOTOR4_PWM  FTM_CH6
//
//#define MOTOR1_PWM_IO  FTM0_CH3
//#define MOTOR2_PWM_IO  FTM0_CH4
//#define MOTOR3_PWM_IO  FTM0_CH5
//#define MOTOR4_PWM_IO  FTM0_CH6
//
//extern unsigned char Pixe1[128];
//extern unsigned char Pixe2[128];
//extern long int ccd_avg;
//extern int zhijiao;
//extern int po;
//extern int Into_zhijiao_right;
//extern int Into_zhijiao_left;
//extern int guanbizhijiao;
//extern int zhijiaoqian;
//extern int Parameter1;
//extern int Parameter2;
//extern int zhangaijifen;
//extern float Parameter3;
//extern int SUM;
//extern float zhijiao_Power;
//extern int Speed_Con;
//extern int zhangail;
//extern int zhangair;
//extern int d;
//extern int gear;
//extern float Ang_Cha;
//extern int DSpeed_Time;
//extern int D2Speed_Time;
//extern int Coner;
//extern int Speed_Change;
//extern int qipao;
//extern int Stright_Count;
//extern float Turning_Out_L;
//extern float Turning_Out_R;
//extern float Turning_Out_L_Lo;
//extern float Turning_Out_R_Lo;
//extern float Dynamic_P_L;
//extern int D2_Check_Speed;
//extern float Dynamic_P_R;
//extern float qianzhan;
////��Ҫ����λ�������Ĳ�����
//extern float Zhili_P;
//extern float Zhili_D;
//extern int dang;
//extern int Parameter4;
//extern float Sudu_P;
//extern float Sudu_I;
//extern float Sudu_D;
//extern float Fangxiang_P_R;
//extern float Fangxiang_D_R;
//extern float Fangxiang_P_L;
//extern float Fangxiang_D_L;
//extern int Expose_Time;//�ع�ʱ��
//extern int qipaoyanshi;
//extern float Speed_Int;
//extern float Speed_Rate;
//extern float Speed_Down;
//extern int danxian_check_sum;
//extern int danxian;
//extern int Min_Hor[2][4];
//extern float SpeedQueue[5];
//extern int CCD_Time;//���ڶ�ʱ����չʱ��
//extern int Speed_Time;//���ڲ��ٵ�ʱ��
//extern int zhijiao_chu_shu;
////������ٶ�ֵ
//extern int GYRO_X;
//extern int GYRO_Y;
//extern int GYRO_Z;
//
////������ٶ�ֵ
//extern double ACC_X;
//extern double ACC_Y;
//extern double ACC_Z;
//
////�����˲��������Ƕ�
//extern float Ang_Acc;//���ٶȼ�atan���ýǶ�
//extern float Ang_IGyro;//���ٶȻ������ýǶ�
//
//extern float Ang_Error;//�����˲���ƫ��
//
//extern float Ang;//����Ҫ�õ�PID�ĽǶ�
//extern float Ang_Set;
//extern int podao;
//extern float Ang_Podao;
//extern int LeftWheel_Count;
//extern int RightWheel_Count;           
//extern int Check_Speed;                  //���������õ����ٶȣ�512�ߣ�
//extern int D_Check_Speed;             //�����ٶȲ���ֵ΢��
//extern int I_Check_Speed;             //�����ٶȲ���ֵ����
//extern int Speed_Set;                      //�ٶ��趨ֵ
//extern int Check_Speed_Last;
//extern int dengta;
//extern int dengta1;
//extern int dengta_yanshi;
//extern int pao_end;
//extern int Corner_Count;
//extern int Turning;
//extern int Check_Speed_Last2;//���ڼ����ٶ�D
//extern int danxian;
//extern int guanche;
//extern int duiguan_time;
//extern int duiguan_guanbi;
//extern int Shut_Hill;
//extern int zhijiao_line_left;
//extern int zhijiao_line_right;
//extern float Speed_Control_Out;//�ٶȿ����������ֱ�Ӹ����������
//extern int Speed_Error;
//extern float Speed_Final_Out;//���յ��ٶȿ������
//extern float Speed_Last;
//extern float SpeedAverOut;//�ٶ�ƽ�����
///*                          ���¶����ж�������
// *  ��ȡ��Ĭ�ϵ��ж�����Ԫ�غ궨��        #undef  VECTOR_xxx
// *  �����¶��嵽�Լ���д���жϺ���      #define VECTOR_xxx    xxx_IRQHandler
// *  ���磺
// *       #undef  VECTOR_003                         ��ȡ��ӳ�䵽�ж�����������жϺ�����ַ�궨��
// *       #define VECTOR_003    HardFault_Handler    ���¶���Ӳ���Ϸ��жϷ�����
// */
//   
//extern void PIT0_IRQHandler(void);
//void FTM1_INPUT_IRQHandler(void);
//void FTM2_INPUT_IRQHandler(void);
//void Go(float Speed); //���µ�����������ת��ֵ���ٶ�ֵ
//void PORTC_IRQHandler(void);
//
//
//
//
//#endif  //__MK60_IT_H__
