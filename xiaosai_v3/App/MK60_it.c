///*!
// * @file       MK60_it.c
// * @brief      ��Ϯ����_�жϷ�����
// * @author     ���� ����
// * @version    v1.2
// * @date       2015-04-06
// */
//
//#include    "MK60_it.h"
//#include    "include.h"
////#define Canshu //������壬��ر��ٶȿ��ƺ��������
//
//
//uint8 CCD_succeed_flag=0;    //ccd�����Ѳɼ���־λ
//int zhangail=0;
//int zhangair=0;
//int zhangaijifen=0;
//
//float Speed_L=0;             //���ڼ�����ٶ�ֵ
//int danxian_kai=0;          //������ʱ
//int duiguan_time=0;
//int duiguan_guanbi=0;
//int Speed_Change=0;
//extern int zhijiao_allow;
//extern int zhijiao_hei;
//extern int zhijiao_chu;
//int zhijiao_allow_time=0;
//int zhijiao_hei_time=0;
//extern int zhijiao_chu_time;
//int Stright_Count=0;//ֱ����ʱ����������㣬��ֱ������
//extern int zhijiao_chu_time;
//extern int zhijiao_turning_time;
//extern int zhijiao_turning;
//extern int zhijiao_heheda;
////int Stright_Count=0;//ֱ����ʱ����������㣬��ֱ������
//int zhijiao_chu_time1=0;
//float Speed_Rate1=0;
//
//float Dynamic_P_L=0;//��̬ת��P�����ʵ�����ǰհ�����ϵͳ��Ӧ�ٶȣ��������������᲻�ȶ�
//float Dynamic_P_R=0;
//
//float Turning_Out_R=0;
//float Turning_Out_L=0;
//float Turning_Out_R_Lo=0;
//float Turning_Out_L_Lo=0;
//int podao=0;//��⵽�µ�����ʱ����
//int Shut_Hill=0;//��⵽�µ���3�벻���µ����
//float qianzhan=0.1;
//
//float Speed_Control_Out=0;//�ٶȿ����������ֱ�Ӹ����������
//
//
//void Go(float Speed) //���µ�����������ת��ֵ���ٶ�ֵ
//{
//#ifndef Canshu  
//  
//  if(gear==1)//һ��
//  {
//    zhijiao_Power=210;
//    Fangxiang_P_R=18.0;//left
//    Fangxiang_D_R=0.1;
//    Fangxiang_P_L=18.0;//right
//    Fangxiang_D_L=0.1;
//  }
//  else if(gear == 2)//����
//  {
//    zhijiao_Power=210;
//    Fangxiang_P_R=18.6;//left
//    Fangxiang_D_R=0.11;
//    Fangxiang_P_L=18.6;//right
//    Fangxiang_D_L=0.11;
//  }
//  
//  if(Turning>0)//��̬P ����Ч��
//  {
//    Dynamic_P_L=Fangxiang_P_L*(1+Speed_Rate*qianzhan*(1-Turning/64));
//    Dynamic_P_R=Fangxiang_P_R*(1+Speed_Rate*qianzhan*(1-Turning/64));
//  }
//  else
//  {
//    Dynamic_P_L=Fangxiang_P_L*(1+Speed_Rate*qianzhan*(1+Turning/64));
//    Dynamic_P_R=Fangxiang_P_R*(1+Speed_Rate*qianzhan*(1-Turning/64));
//  }
//  gpio_set   (PTC0,   0);
//  if(zhijiao_turning>=zhijiao_turning_time && zhijiao_line_right == 1)
//  {    
//    Turning_Out_R = -zhijiao_Power;
//    Turning_Out_L = -zhijiao_Power;
//    //gpio_set   (PTC0,   1);
//  }
//  else if(zhijiao_turning>=zhijiao_turning_time && zhijiao_line_left == 1)
//  {
//    Turning_Out_R = zhijiao_Power;
//    Turning_Out_L = zhijiao_Power;//
//    //gpio_set   (PTC0,   1);
//  }else if(zhangaijifen<1000 && zhangai_hei_zuo == 1 && qipaoyanshi > 550) 
//  {
//    Turning_Out_R = -500;//*Speed_Rate
//    Turning_Out_L = -500;
//    gpio_set   (PTC0,   1);
//  }
//  else if(zhangaijifen<1000 && zhangai_hei_you == 1 && qipaoyanshi > 550) //zhangai_time <= 20 && zhangai_hei_you == 1
//  {
//    Turning_Out_R = 500;
//    Turning_Out_L = 500;
//    gpio_set   (PTC0,   1);
//  }
//  else
//  {
//      Turning_Out_R=Speed_Rate*Dynamic_P_R*Turning+Fangxiang_D_R*GYRO_Y;
//      Turning_Out_L=Speed_Rate*Dynamic_P_L*Turning+Fangxiang_D_L*GYRO_Y;
//      
//      if(qipaoyanshi>=510)//��һ��bug���޸�
//      {
//        if(Turning_Out_R>270) Turning_Out_R=270;
//        if(Turning_Out_R<-270) Turning_Out_R=-270;
//        if(Turning_Out_L>270) Turning_Out_L=270;
//        if(Turning_Out_L<-270) Turning_Out_L=-270;
//        
//      }
//      else
//      {
//        Turning_Out_R=0;
//        Turning_Out_L=0;
//        
//      }
//      
//      if(podao!=0)
//      {
//        if(Turning_Out_R>70) Turning_Out_R=70;
//        if(Turning_Out_R<-70) Turning_Out_R=-70;
//        if(Turning_Out_L>70) Turning_Out_L=70;
//        if(Turning_Out_L<-70) Turning_Out_L=-70;
//      }
//          
//  }
//#endif  
//  
//  if(pao_end==0)
//  {   
//    if( (Speed+Turning_Out_R)>=0 && (Speed+Turning_Out_R)<=990)
//    {
//        FTM_PWM_Duty(FTM0, MOTOR1_PWM, (uint32)(Speed+Turning_Out_R) );//r
//        FTM_PWM_Duty(FTM0, MOTOR2_PWM, 0);
//        //gpio_set   (PTC0,   0); 
//    }else if((Speed+Turning_Out_R) < 0 && (Speed+Turning_Out_R) > (0-990))
//    {
//        FTM_PWM_Duty(FTM0, MOTOR1_PWM, 0);
//        FTM_PWM_Duty(FTM0, MOTOR2_PWM, (uint32)(0-Speed));
//        //gpio_set   (PTC0,   0); 
//    }
//    else
//    {
//      
//      if( Speed+Turning_Out_R>=990)
//      {
//        FTM_PWM_Duty(FTM0, MOTOR1_PWM,990);//r
//        FTM_PWM_Duty(FTM0, MOTOR2_PWM, 0);
//      }
//      if( Speed+Turning_Out_R<=-990)
//      {
//        FTM_PWM_Duty(FTM0, MOTOR1_PWM,0);//r
//        FTM_PWM_Duty(FTM0, MOTOR2_PWM, 990);
//      }
//    }
//    
//    if( (Speed-Turning_Out_L)>=0 && (Speed-Turning_Out_L)<=990)
//    {
//        FTM_PWM_Duty(FTM0, MOTOR3_PWM, (uint32)(Speed-Turning_Out_L) );//��������
//        FTM_PWM_Duty(FTM0, MOTOR4_PWM, 0);
//        //gpio_set   (PTC0,   0); 
//    }
//    else if((Speed-Turning_Out_L) < 0 && (Speed-Turning_Out_L) > (0-990))
//    {
//        FTM_PWM_Duty(FTM0, MOTOR3_PWM, 0);
//        FTM_PWM_Duty(FTM0, MOTOR4_PWM, (uint32)(0-Speed));
//        //gpio_set   (PTC0,   0); 
//    }
//    else
//    {
//      if( Speed-Turning_Out_L>=990 )
//      {
//        FTM_PWM_Duty(FTM0, MOTOR3_PWM,990);//r
//        FTM_PWM_Duty(FTM0, MOTOR4_PWM, 0);
//      }
//      if( Speed-Turning_Out_L<=-990 )
//      {
//        FTM_PWM_Duty(FTM0, MOTOR3_PWM,0);//r
//        FTM_PWM_Duty(FTM0, MOTOR4_PWM, 990);
//      }
//      //gpio_set   (PTC0,   1); 
//    }
//    
//  }
//  else 
//  {
//    FTM_PWM_Duty(FTM0, MOTOR1_PWM, 0);
//    FTM_PWM_Duty(FTM0, MOTOR2_PWM, 0);
//    FTM_PWM_Duty(FTM0, MOTOR4_PWM, 0);
//    FTM_PWM_Duty(FTM0, MOTOR3_PWM, 0);
//  }
//    
//}
//
////��ʱ��0�жϷ���
//void PIT0_IRQHandler(void)/////////////////////////////����������Ҫ�Ŀ��ƺ�����ڣ�
//{
////   CCD_Time++;//�������ع�ʱ
//   Speed_Time++;//��һ���ٶȵļ��ʱ��
//   DSpeed_Time++;
//   Speed_Con++;
//   if(zhijiao_chu_shu==1)  zhijiao_chu_time1++;
//
//   if(qipaoyanshi>=510) dengta_yanshi++;
//   
//   zhangaijifen = (zhangail+zhangair)/2;
//   if(zhangaijifen>=340) 
//   {
//     zhangai_hei_zuo = 0;
//     zhangai_hei_you = 0;
//     zhangaijifen=0;
//     zhangail=0;
//     zhangair=0;
//   }
//   //�ɼ�����������
//   GYRO_X=Get_Gyro(1,'X');//ֱ������������
//   GYRO_Y=Get_Gyro(1,'Y');//�������������
//        
//   //�ɼ����ٶȼ�����
//   ACC_X=Get_mma8451_once('X');//������һ��˶���bug��
//   ACC_Z=Get_mma8451_once('Z');
//   
//   //�Լ��ٶȼ����ݼ���Ƕ�
//   Ang_Acc=Ang_Set+Ang_Cha+Parameter3-186*ACC_Z;
//   //���������ǻ��ֽǶ�+++++�����˲�
//   Ang_IGyro-=(GYRO_X+Ang_Error*3.5)*0.00025;//��ʱ��Ang_IGyro��������ʹ�õĽǶ�
//   //���������Ƕ�֮���ƫ��
//   Ang_Error=Ang_IGyro-Ang_Acc;
//   
//   //ֱ��PID,fixed parameter
//   Speed_L=Ang_IGyro*Zhili_P-GYRO_X*Zhili_D*Zhili_P*0.025;//ֱ��PID
//   
//   if(100 == Speed_Con)
//   {
//     Speed_Con=0;
//     Speed_Last=Speed_Final_Out;
//   }
//   
//   //�����ٶȺ�D�ٶȡ�I�ٶ�
//   if(10==Speed_Time)                //50ms��һ���ٶ�
//   {
//       Speed_Time=0;
//       
//       Check_Speed=(LeftWheel_Count+RightWheel_Count)/2;  //ƽ��һ��,Speed_Changeû�м��� 
//       
//       //�ٶ�
//       SpeedQueue[4]=SpeedQueue[3];
//       SpeedQueue[3]=SpeedQueue[2];
//       SpeedQueue[2]=SpeedQueue[1];
//       SpeedQueue[1]=SpeedQueue[0]; 
//       SpeedQueue[0]=Check_Speed;
//        
//       if(qipaoyanshi >1000)
//       {
//           if( (Check_Speed-SpeedQueue[4])>15 ) Check_Speed=SpeedQueue[4];
//           if( (SpeedQueue[4]-Check_Speed)>15 ) Check_Speed=SpeedQueue[4];
//       }
//       
//       if(qipaoyanshi > 1000)
//       {
//          if(Check_Speed>(Speed_Set-Speed_Down+10)) Check_Speed=Speed_Set-Speed_Down+10;//�ٶȲ����޷�
//          if(Check_Speed<(Speed_Set-Speed_Down-10)) Check_Speed=Speed_Set-Speed_Down-10;
//       }
//       
//       Speed_Rate=(float)(Check_Speed)/Speed_Set;//�ٶ�Ư��
//       
//       Speed_Error=Speed_Set-Speed_Down-Check_Speed;
//       LeftWheel_Count=0;       RightWheel_Count=0;
//
//       if(qipaoyanshi>900)
//       {
//        Speed_Int=Speed_Int+Speed_Error*Sudu_I;
//       }
//       
//       if(Speed_Int>100) Speed_Int=100;
//       if(Speed_Int<-100) Speed_Int=-100;
//       
//       Speed_Control_Out=Sudu_P*(float)Speed_Error+Speed_Int;
//       SpeedAverOut=(Speed_Control_Out-Speed_Last)/100;
//       
//       dengta1=1;
//   }
//   
//   Speed_Final_Out=Speed_Final_Out+SpeedAverOut;
//   
//   //��������޷�
//   if(qipaoyanshi > 1000)
//   {
//       if(Speed_Final_Out>500)      Speed_Final_Out=500;
//       else if(Speed_Final_Out<-500)       Speed_Final_Out=-500;
//   }
//   
//   //�ٶ�PID
//#ifndef Canshu  
//   Speed_L=Speed_L-Speed_Final_Out;
//#endif   
//   
////   //�����ع⣬���Բ��ع�  
////   if(CCD_Time==0)
////   {
////     ////StartIntegration1() ;    //����CCD1,���ع�
////     StartIntegration2() ;   //����CCD2,���ع�
////     StartIntegration3() ;
////   }else if(CCD_Time==5)//�����ع�ʱ��ɼ�����
////   {
////     //ImageCapture1(Pixe1) ;
////   }
////   else if(CCD_Time==7)//�����ع�ʱ��ɼ�����
////   {
////     ImageCapture3(Pixe3) ;
////   }else if(CCD_Time==3)//�����ع�ʱ��ɼ�����
////   {
////     ImageCapture2(Pixe2) ;
////   }
////   else if(CCD_Time>=10)//�����ɼ�ʱ����
////   {
////     CCD_Time=0;
////     CCD_succeed_flag=1;//ccd�����Ѳɼ�
////   }
//   
//   //ccd���ݲɼ�һ�κ󣬼������Һ��ߣ���ֹ�ظ�����
//
//   zhijiao_heheda++;
//   if(zhijiao_allow >= 1) zhijiao_allow++;
//   if(zhijiao_allow >= 200 && zhijiao_heheda>=1000) {
//     zhijiao_allow=300;
//     zhijiao_heheda=1010;
//     if(gpio_get(PTD12)==1)
//     {
//       zhijiao_hei=1;
//       Speed_Rate1=Speed_Rate;
//     }
//   }
//   
//   if(zhijiao_hei>=1) 
//   {
//     zhijiao_hei++;//��⵽���߱�־ 
//   }
//   if(zhijiao_hei>=1000){  //��⵽����һ��ʱ���ڼ�ⶪ��
//    zhijiao_hei=0;       //��ʱ����Ϊ������Ч
//   }
//   if(CCD_succeed_flag==1)
//   {
//     if(qipaoyanshi>520) { //δ����ʱ������������
//       ccd_getline(); 
//       ccd3_work();
//     }
//     
//     CCD_succeed_flag=0;//��������ٴδ򿪲ɼ�
//   }
//   //���µ��
//   Go(Speed_L);//����0���
//   
//   if( ((Turning>=0 && Turning<20) || 
//        (Turning<=0 && Turning>-20)) 
//                                    && qipaoyanshi>720)
//   {
//     Stright_Count++;
//   }
//   else
//   {
//     Stright_Count=0;
//   }
//
//   if(Stright_Count>920 &&Coner)
//   {
//     Ang_Cha=29;
//     Stright_Count=921;
//     
//   }
//   else
//   {
//     Ang_Cha=0;
//    Speed_Down=0;
//   }
//   
//   if(gpio_get(PTD13)==1)
//   {
//      
//   }
//   else if(qipaoyanshi>700 && Shut_Hill == 0)
//   {
//      
//      podao=500;
//      
//   }
//   
//   if(podao!=0)
//   {
//     //gpio_set   (PTC0,   1);
//     podao--;
//     Shut_Hill=1500;
//   }
//   else
//   {
//
//     //gpio_set   (PTC0,   0); 
//     if(Shut_Hill!=0)
//       Shut_Hill--;
//   }
//   
//   
//   
//   
////   if(dang == 1)
////   {
////       if(zhijiao_chu_time1>=140)
////       {
////         if(gear == 1)
////         {
////            Speed_Down=38;
////            Ang_Cha=50;
////            //gpio_set   (PTC0,   1);
////         }
////         else if(gear == 2)
////         {
////            Speed_Down=25;
////            Ang_Cha=80;
////         }
////       }
////       
////       if(zhijiao_chu_time1>=820)
////       {
////         if(gear == 1)
////         {
////           Speed_Down=38;
////           Ang_Cha=-40;
////           //gpio_set   (PTC0,   1);
////         }
////         else if(gear == 2)
////         {
////           Speed_Down=38;
////           Ang_Cha=-50;
////           //gpio_set   (PTC0,   1);
////         }
////       }
////
////       if(zhijiao_chu_time1>=1900) 
////       {
////         if(gear == 1)
////         {
////           Speed_Down=8;
////           Ang_Cha=-3;
////           //zhijiao_chu_shu=0;
////           
////           //gpio_set   (PTC0,0);
////         }
////         else if(gear == 2)
////         {
////           Speed_Down=38;
////           Ang_Cha=-3;
////           //zhijiao_chu_shu=0;
////           
////          // gpio_set   (PTC0,   0);
////         }
////         zhijiao_turning_time=3;
////       }
////   }
//   
//   
//   //������λ���������
//   //OutData[0]=(float)Turning_Out_R;
//   OutData[1]=(float)dengta;
//   //OutData[2]=(float)(Check_Speed-SpeedQueue[4]);
//   //���жϱ�־λ
//   PIT_Flag_Clear(PIT0);       
//}
//
//void FTM1_INPUT_IRQHandler(void)    //��һ·���٣�����
//{
//    uint8 s = FTM1_STATUS;          //��ȡ��׽�ͱȽ�״̬  All CHnF bits can be checked using only one read of STATUS.
//    uint8 CHn;
//
//    FTM1_STATUS = 0x00;             //���жϱ�־λ
//
//    CHn = 0;
//    if( s & (1 << CHn) )
//    {
//      if(gpio_get(R_DeCoder))
//      {
//         RightWheel_Count++;
//      }
//      else
//      {
//         RightWheel_Count--;
//      }
//      
//      if(zhangai_hei_zuo == 1 || zhangai_hei_you == 1)
//      {
//         zhangair++;
//      }
//    }
//
//}
//
//void FTM2_INPUT_IRQHandler(void)    //��һ·���٣�����
//{
//    uint8 s = FTM2_STATUS;          //��ȡ��׽�ͱȽ�״̬  All CHnF bits can be checked using only one read of STATUS.
//    uint8 CHn;
//
//    FTM2_STATUS = 0x00;             //���жϱ�־λ
//
//    CHn = 0;
//    if( s & (1 << CHn) )
//    {
//
//       if(gpio_get(L_DeCoder))             
//       {
//          LeftWheel_Count--;
//       }
//       else
//       {
//          LeftWheel_Count++;
//       };
//       
//       if(zhangai_hei_zuo == 1 || zhangai_hei_you == 1)
//       {
//         zhangail++;
//       }
//        /*********************/
//    }
//}
//
///*!
// *  @brief      PORTC�˿��жϷ�����
// *  @since      v5.0
// */
//void PORTC_IRQHandler(void)
//{
//
//    uint8  n = 0;    //���ź�
//    n = 5;
//    if(PORTC_ISFR & (1 << n))           //PTD7 �����ж�
//    {
//        dengta++;
//      
//        PORTC_ISFR  = (1 << n);        //д1���жϱ�־λ
//
//
//    }
//
//}