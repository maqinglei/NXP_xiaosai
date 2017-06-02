//#include "include.h"
//#include "math.h"
////void Water_LEDs();
//void Measure_speed();
//void Measure_Acc();
//void Angle_control();
//void Speed_control();
//void Direction_control();
//void Direction_control_with_Ren();
//void Motor_Control();
//
///*************************************************************************
//*  �������ƣ�VSYNC_IRQ
//*  ����˵����PORTD�˿��жϷ�����
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-1-25    �Ѳ���
//*  ��    ע�����ź���Ҫ�Լ���ʼ�������
//*************************************************************************/
//void VSYNC_IRQ(void)
//{    
//    static u16 czd=0;
//    static u32 flag;
//    //Clear Interrupt flag
//    flag = PORTD_ISFR;
//    PORTD_ISFR = flag;
//    czd++;
//    if(img_flag == IMG_START)	//��Ҫ��ʼ�ɼ�ͼ��
//    {
//        DMA_PORTx2BUFF_Init(CAMERA_DMA_CH, (void *)&PTB_BYTE2_IN, (void *)Image_fire, PTE27, DMA_BYTE1, CAMERA_SIZE , DMA_falling);
//        DMA_EN(CAMERA_DMA_CH);            		//ʹ��ͨ��CHn Ӳ������
//        DMA_DADDR(CAMERA_DMA_CH) = (u32)Image_fire; //�ָ���ַ
//        img_flag = IMG_GATHER;		        //���ͼ��ɼ���
//        disable_irq(90);  
//    }
//    else					//ͼ��ɼ�����
//    {
//        disable_irq(90); 			//�ر�PTA���ж�
//        img_flag = IMG_FAIL;		//���ͼ��ɼ�ʧ��
//    }
//}
//
//
//
//
///*************************************************************************
//*  �������ƣ�DMA0_IRQHandler
//*  ����˵����DMA0
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-1-25    �Ѳ���
//*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸�
//*************************************************************************/
//void DMA0_IRQHandler()
//{
//    DMA_DIS(CAMERA_DMA_CH);            	//�ر�ͨ��CHn Ӳ������
//    DMA_IRQ_CLEAN(CAMERA_DMA_CH);           //���ͨ�������жϱ�־λ
//    img_flag = IMG_FINISH ;  
//}
//
//
//
//
//
//
///*************************************************************************
//*  �������ƣ�PIT0_IRQHandler
//*  ����˵����PIT0 ��ʱ�жϷ�����
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2014-1-14    �Ѳ���
//*  ��    ע��
//*************************************************************************/
//void PIT0_IRQHandler(void)
//{
//    static unsigned char TimeCnt_20ms = 0;	  //20msʱ�������
//    static unsigned char flag = 0;                //5ms�ķ�ʱ��־
//    PIT_Flag_Clear(PIT0);
//    Time_1ms++; 
//    _LED1 = (Time_1ms/500)%2;
//    TimeCnt_20ms++;
//    if(TimeCnt_20ms >= 20)
//    {TimeCnt_20ms = 0;}
//    flag = TimeCnt_20ms%5;
//    //����ΪֹT=0.5us
//    /**************************************************************/
//    /*********************Own code*********************************/
//    /**************************************************************/   
//
//    
//    //�ٶȿ��� Tmax=8.5us
//    if(flag==0 && Time_1ms>Stand_Time)
//    {
//        Measure_speed();
//        Speed_control();
//    }
//    //����angle_Out������ֱ������ T=449us IICʱ�䳤
//    else if(flag==1)
//    {
//        Measure_Acc();//T=340us
//        Angle_control();//T=100us
//        Motor_Control();//T=9us
//    }
//    else if(Ren.flag==1 && flag==2)//�����ֵķ������
//    {
//        Direction_control_with_Ren();//T=58us
//        Motor_Control();
//    }
//    //�������
//    if(Ren.flag==0 && Direction.output_enable==1)
//    {
//        Direction_control();//T=54us
//        Motor_Control();
//        Direction.output_enable = 0;
//    }
//    
//    
//    //���ٽ׶� T=3us��ֱ�Ӿʹﵽ�趨ֵ
//    if(Time_1ms > Stand_Time && Speed.Goal < Speed.Goal_init)
//    { 
//        Speed.Goal = Speed.Goal_init + 1;
//        buzzer = 1;
//    }
//    else
//    {
//        if(Ren.flag==1 || Cross_flag==1 || Slope_flag==1 || Time_1ms < Block.time + 1000 || smallS_flag==1)
//            buzzer = 1;
//        else
//            buzzer = 0;
//    }
//    
//    //LED��ˮ�ƣ�֤���ڽ���ʱ���ж�
//    //Water_LEDs();
//    /*********************************************************************/
//    /**************************Own code end*******************************/
//    /*********************************************************************/
//    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
//}
//
//
//
//
//
//
//
///*************************************************************************
//*                             Ұ��Ƕ��ʽ����������
//*
//*  �������ƣ�USART3_IRQHandler
//*  ����˵��������3 �ж� ���� ������
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2014-1-14    �Ѳ���
//*  ��    ע��
//*************************************************************************/
//void USART3_IRQHandler(void)
//{
//    unsigned char ch;
//    //����һ���ֽ����ݲ��ط�
//    ch = uart_getchar (UART3);      //���յ�һ������
//    switch(ch)
//    {
////      case 'a':break;
////      case 'b': Angle.P+=10;  printf("angle_P:");SCISendFloat(UART3, Angle.P);break;
////      case 'c': Angle.P-=10;  printf("angle_P:");SCISendFloat(UART3, Angle.P);break;
////      case 'd': Angle.D+=10;  printf("angle_D:");SCISendFloat(UART3, Angle.D);break;
////      case 'e': Angle.D-=10;  printf("angle_D:");SCISendFloat(UART3, Angle.D);break;
////      case 'f': Angle.D+=1;   printf("angle_D:");SCISendFloat(UART3, Angle.D);break;
////      case 'g': Angle.D-=1;   printf("angle_D:");SCISendFloat(UART3, Angle.D);break;
////      case '0': Angle.OFFSET+=1;  printf("OFFSET_angle:");SCISendFloat(UART3, Angle.OFFSET);break;
////      case '1': Angle.OFFSET-=1;  printf("OFFSET_angle:");SCISendFloat(UART3, Angle.OFFSET);break;
////      case '2': Angle.OFFSET+=0.1;printf("OFFSET_angle:");SCISendFloat(UART3, Angle.OFFSET);break;
////      case '3': Angle.OFFSET-=0.1;printf("OFFSET_angle:");SCISendFloat(UART3, Angle.OFFSET);break;
////      //case '4':tg+=1;printf("tg:");SCISendFloat(UART3,tg);break;
//      //case '5':tg-=1;printf("tg:");SCISendFloat(UART3,tg);break;
//      //������ӵġ���
//      case 'a':Speed.P+=0.2; printf("speed_P:");SCISendFloat(UART3,Speed.P);break;
//      case 'b':Speed.P-=0.2; printf("speed_P:");SCISendFloat(UART3,Speed.P);break;
//      case 'e':Speed.I+=0.1;  printf("speed_I:");SCISendFloat(UART3,Speed.I);break;
//      case 'f':Speed.I-=0.1;  printf("speed_I:");SCISendFloat(UART3,Speed.I);break;
//      case 'g':Speed.I+=0.01;  printf("speed_I:");SCISendFloat(UART3,Speed.I);break;
//      case 'h':Speed.I-=0.01;  printf("speed_I:");SCISendFloat(UART3,Speed.I);break;
//      //case 'j':SD_enable=1;StartLine.flag=1;break;
////      case '6':pwm_Dead_L+=10;printf("pwm_Dead_L:");SCISendFloat(UART3,pwm_Dead_L);break;
////      case '7':pwm_Dead_L-=10;printf("pwm_Dead_L:");SCISendFloat(UART3,pwm_Dead_L);break;
////      case '8':pwm_Dead_R+=10;printf("pwm_Dead_R:");SCISendFloat(UART3,pwm_Dead_R);break;
////      case '9':pwm_Dead_R-=10;printf("pwm_Dead_R:");SCISendFloat(UART3,pwm_Dead_R);break;
//      //default: printf("error");
//    }
//    uart_putchar(UART3,'\n');
//}
//
//
//
//
///*************************************************************************
//*                             Ұ��Ƕ��ʽ����������
//*
//*  �������ƣ�SysTick_Handler
//*  ����˵����ϵͳ�δ�ʱ���жϷ�����
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-18    �Ѳ���
//*  ��    ע��ucos���õõ�
//*************************************************************************/
//void SysTick_Handler(void)
//{
//    //    OSIntEnter();
//    //    OSTimeTick();
//    //    OSIntExit();
//}
//
//
//
//
//
///*************************************************************************
//*                             Ұ��Ƕ��ʽ����������
//*
//*  �������ƣ�HardFault_Handler
//*  ����˵����Ӳ���Ϸ��жϷ�����
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-4    �Ѳ���
//*  ��    ע��������LED��˸��ָʾ������Ӳ���Ϸ�
//*************************************************************************/
//void HardFault_Handler(void)
//{
//    while (1)
//    {
//        printf("\n****Ӳ���Ϸô���!!!*****\r\n\n");
//    }
//}
//
//
//
//
///*************************************************************************
//*                             Ұ��Ƕ��ʽ����������
//*
//*  �������ƣ�PendSV_Handler
//*  ����˵����PendSV��������ϵͳ���ã��жϷ�����
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-15    �Ѳ���
//*  ��    ע��uC/OS�����л�����
//*************************************************************************/
//void PendSV_Handler(void)
//{
//}
//
//
//
//
//
///*************************************************************************
//*                             Ұ��Ƕ��ʽ����������
//*
//*  �������ƣ�FTM0_IRQHandler
//*  ����˵����FTM0���벶׽�жϷ�����
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-25
//*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸ģ��ο����еĴ�������Լ��Ĺ���
//*************************************************************************/
//void FTM0_IRQHandler()
//{
//}
//
//
//
//
///*************************************************************************
//*                             Ұ��Ƕ��ʽ����������
//*
//*  �������ƣ�FTM1_IRQHandler
//*  ����˵����FTM1���벶׽�жϷ�����
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-25
//*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸ģ��ο����еĴ�������Լ��Ĺ���
//*************************************************************************/
//void FTM1_IRQHandler()
//{
//}
//
//
//
///******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
// * �ļ���       ��ISR_fun.c
// * ����         ���߶˰������жϷ��������Ӻ���������ISR.c
// * ʵ��ƽ̨     ������ӡ�󿪷���
// * ��汾       ������Ұ���
// * Ƕ��ϵͳ     ��
// * ����         ��xuxu
//**********************************************************************************/
//
//
//
///*************************************************************************
//*  �������ƣ�Measure_speed
//*  ����˵���������ٶ�
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-14    �Ѳ���
//*************************************************************************/
//void Measure_speed()
//{
//    static unsigned char SpeedDirection_L;
//    static unsigned char SpeedDirection_R;
//    SpeedDirection_L = (FTM1_QDCTRL & FTM_QDCTRL_QUADIR_MASK);
//    SpeedDirection_R = (FTM2_QDCTRL & FTM_QDCTRL_QUADIR_MASK);
//    //���ֲ���
//    if(SpeedDirection_L==0)	//��ת
//    {
//        if(10000 - FTM1_CNT < 5000)//��ֹbug
//          Speed.L_5ms = 10000 - FTM1_CNT;
//    }
//    else                        //��ת
//    {
//        if(FTM1_CNT < 5000)//��ֹbug
//          Speed.L_5ms = 0 - FTM1_CNT;
//    }
//    //���ֲ���
//    if(SpeedDirection_R==0)	//��ת
//    {
//        if(10001 - FTM2_CNT < 5000)//��ֹbug
//          Speed.R_5ms = 0 - (10000-FTM2_CNT);
//    }
//    else                         //��ת
//    {
//        if(FTM2_CNT < 5000)//��ֹbug
//          Speed.R_5ms = FTM2_CNT;
//    }
//    #define ratio 1.953125//��������С�������������256�ߣ�ԭ���õ�500��
//    Speed.L_5ms = (int)(Speed.L_5ms*ratio);
//    Speed.R_5ms = (int)(Speed.R_5ms*ratio);
//    //clear
//    FTM1_CNT = 0;
//    FTM2_CNT = 0;
//}
//
//
///*************************************************************************
//*  �������ƣ�Measure_Acc
//*  ����˵�����������ٶȼ�ֵ
//*  ����˵������
//*  �������أ��ޣ�������ȫ�ֱ���a_sin��a_cos��
//*  �޸�ʱ�䣺2012-2-14    �Ѳ���
//*************************************************************************/
//void Measure_Acc()
//{
//    static float a_sin_new=0,a_sin[3];
//    static float a_cos_new=0,a_cos[3];
//    
//    for(int i = 0;i < 3;i++)
//        a_sin[i] = Get_mma8451_once('Z');
//    a_sin_new = (a_sin[0] + a_sin[1] + a_sin[2])/3.0;
//    
//    for(int i = 0;i < 3;i++)
//        a_cos[i] = Get_mma8451_once('X');
//    a_cos_new = (a_cos[0] + a_cos[1] + a_cos[2])/3.0;
//    
//    //��ͨ�˲�
//    Angle.a_sin = Angle.a_sin*0.5 + a_sin_new*0.5;//��90��-90��sinֵ 1��0��-1�仯,��Ϊ��
//    Angle.a_cos = Angle.a_cos*0.5 + a_cos_new*0.5;//��90��-90) cosֵ 0��-1��0�仯,��Ϊ��
//}
//
//
//
///*************************************************************************
//*  �������ƣ�Angle_control
//*  ����˵�����Ƕ��ںϣ�������Ƕȣ�����Ƕ�pwm���
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-14    �Ѳ���
//*************************************************************************/
//#define Gyro_OFFSET (-4)
//void Angle_control()
//{
//    //ֱ��
//    #define k_Gyro 0.07   //���ٶȷŴ���
//    #define dt 0.005
//    #define tg 2         //**����ʱ��:1~4
//    static float mG_delta=0;      //��angle_speedһ������
//    static float Angle_Gyro_old=0;
//    
//    //���ĸ����Ǻ�����������ô��װ��ʵ�����Ű�װ��asin��
//    /*if(Angle.a_cos <= 0)
//    {
//        if(Angle.a_cos==0)
//            Angle.m_angle = asin(Angle.a_sin)*57.295779513;  	//180/pi=57.295779513
//        else
//            Angle.m_angle = atan(Angle.a_sin/(0 - Angle.a_cos))*57.295779513;
//    }
//    else
//    {
//        Angle.m_angle = atan(Angle.a_sin/Angle.a_cos)*57.295779513;
//        Angle.m_angle = 180 - Angle.m_angle;
//    }*/
//    Angle.m_angle = asin(Angle.a_sin)*57.295779513;
//    if(Angle.m_angle > 90)
//        Angle.m_angle = 90;
//    else if(Angle.m_angle < -90)
//        Angle.m_angle = -90;
//   
//    
//    //�õ�Angle.G_angle
//    Angle_Gyro_old = Angle.Gyro;
//    Angle.Gyro = (float)(Get_Gyro(1,'X') - Gyro_OFFSET);
//    Angle.speed = 0 - k_Gyro *(Angle_Gyro_old + Angle.Gyro)/2.0;
//    mG_delta = (Angle.m_angle - Angle.G_angle) / tg;
//    Angle.G_angle += (Angle.speed + mG_delta) * dt;
//        
//    //�õ�Angle.PWM
//    if(Ren.flag == 0)//���������
//    {
//        Angle.PWM = (Angle.OFFSET - Angle.G_angle)*Angle.P
//                      - Angle.speed * Angle.D;
//    }
//    else//���������
//    {
//        Angle.PWM = (Angle.OFFSET - Angle.G_angle)*(Angle.P +0)
//                      - Angle.speed * (Angle.D + 0);
//    }
//}
//
//
//
//
///*************************************************************************
//*  �������ƣ�Speed_control
//*  ����˵���������ٶ�pwm���
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-14    �Ѳ���
//*************************************************************************/
//void Speed_control()
//{
//    static unsigned char speed_Period=0;//�ٶȿ������ڱ���
//    #define speed_Period_Constant 20 //�ٶȿ�������
//    static float speed_Delta=0;
//    static float Tmp_Speed_P;
//    static int temp_L_100ms=0,temp_R_100ms=0;
//    
//    speed_Period++;
//    temp_L_100ms += Speed.L_5ms;
//    temp_R_100ms += Speed.R_5ms;
//    if(speed_Period >= 20)//�ٶ�PID�������ԡ�100msһ�μ���
//    {
//        speed_Period = 0;
//        Speed.L_100ms = temp_L_100ms;
//        Speed.R_100ms = temp_R_100ms;
//        Speed.Car = (float)((Speed.L_100ms + Speed.R_100ms)/2.0);
//        temp_L_100ms = 0;
//        temp_R_100ms = 0;
//        
//        //�ٶȿ���
//        speed_Delta = Speed.Goal - Speed.Car;
//        
//        //IIIIIIIIIIIIIIIIIIIII����IIIIIIIIIIIIIIIIIII
//        #define SPEEDUP_TIME 1500
//        if(Time_1ms < Stand_Time + SPEEDUP_TIME)//վ��֮�������֮�ڣ�ʹ������
//        {
//            if(Speed.Mode==3)
//                Speed.PWM_Integral = 1000 + 3000*(Stand_Time + SPEEDUP_TIME - Time_1ms)/SPEEDUP_TIME;
//            if(Speed.Mode==4)
//                Speed.PWM_Integral = 0 + 3500*(Stand_Time + SPEEDUP_TIME - Time_1ms)/SPEEDUP_TIME;
//            else
//                Speed.PWM_Integral = 1000 + 3000*(Stand_Time + SPEEDUP_TIME - Time_1ms)/SPEEDUP_TIME;
//        }
//        else//վ��֮�������֮��
//        {
//            Speed.PWM_Integral += speed_Delta * Speed.I;
//            //PWM_Integral�޷�
//            if(Speed.PWM_Integral > Speed.I_Limit_PWM_max)//�޷���
//                Speed.PWM_Integral = Speed.I_Limit_PWM_max;
//            else if(Speed.PWM_Integral <= Speed.I_Limit_PWM_min)
//                Speed.PWM_Integral = Speed.I_Limit_PWM_min;
//        }
//        
//        //PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
//        //��������ͨ�޷������ڻ�û���ʱ��
//        if(speed_Delta> 0 - Speed.I_Error_Start && speed_Delta < Speed.I_Error_Start)
//            Tmp_Speed_P = Speed.P * speed_Delta;
//        else if(speed_Delta< 0 - Speed.I_Error_Start)
//            Tmp_Speed_P = Speed.P * (0 - Speed.I_Error_Start);
//        else if(speed_Delta > Speed.I_Error_Start)
//            Tmp_Speed_P = Speed.P * Speed.I_Error_Start;
//        
//        //���
//        Speed.PWM_Per = ( Tmp_Speed_P
//                         + Speed.PWM_Integral
//                             - Speed.PWM)  /  speed_Period_Constant;
//    }
//    Speed.PWM += Speed.PWM_Per;
//}
//
//
//
//
///*************************************************************************
//*  �������ƣ�Direction_control��Direction_control_with_Ren
//*  ����˵�������㷽��pwm����������Ͳ��������֣�
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-14    �Ѳ���
//*************************************************************************/
//#define Dir_Gyro_OFFSET 10
//void Direction_control()
//{
//    Direction.Gyro = (float)(Get_Gyro(1,'Y') - Dir_Gyro_OFFSET); //����Ϊ��
//    if(Block.flag==0)//�к�שͷ�ϰ����
//    {
//        Direction.PWM_Per = Direction.P * (black_centre - CENTER )	//���
//            + Direction.D * Direction.Gyro
//                - Direction.PWM;
//    }
//    else//û�к�שͷ�ϰ����
//    {
//        if(Time_1ms < Block.time + Block.delaytime)
//            Direction.PWM_Per = Direction.P * (black_centre + Block.Offset - CENTER )	//���
//                         + Direction.D * Direction.Gyro
//                           - Direction.PWM;
//        else
//            Block.flag = 0;
//    }
//    Direction.PWM += Direction.PWM_Per;
//}
//
//void Direction_control_with_Ren()//???����ʱ���Ƿ���Ҫ�����Dֵ��
//{
//    if(Time_1ms > Ren.record_time + Ren.Delaytime1)//�����˵�����ʱ���
//    {
//        Direction.Gyro = (float)(Get_Gyro(1,'Y') - Dir_Gyro_OFFSET); //����Ϊ��
//        if(Ren.Loaction > CENTER)//�ҹ�
//        {
//            black_centre = 160 + Ren.Strength;
//        }
//        else//���
//        {
//            if(Speed.Mode==3)//����ͷ���ˣ�3��λ����ղ���
//            {
//                if(Multiple_line_enable==1)
//                    black_centre = 160 - Ren.Strength - 27;
//                else
//                    black_centre = 160 - Ren.Strength - 22;
//            }
//            else if(Speed.Mode==4 || Speed.Mode==5)//����ͷ���ˣ�4,5��λ����ղ���
//            {
//                if(Multiple_line_enable==1)
//                    black_centre = 160 - Ren.Strength - 33;
//                else
//                    black_centre = 160 - Ren.Strength - 30;
//            }
//            else//����ͷ���ˣ�������λ��պ��ҹ�����
//            {
//                black_centre = 160 - Ren.Strength;
//            }
//        }
//        
//        //ʱ�����
//        if(Time_1ms > Ren.record_time + Ren.Delaytime1 + Ren.Delaytime2)
//        {
//            Ren.flag = 0;
//        }
//        
//        //���
//        Direction.PWM_Per=(Direction.P * (black_centre - CENTER)	//���
//                           + Direction.D * Direction.Gyro
//                               - Direction.PWM);
//        Direction.PWM += Direction.PWM_Per;
//    }
//}
//
//
//
///*************************************************************************
//*  �������ƣ�Motor_Control
//*  ����˵����pwm���
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-14    �Ѳ���
//*************************************************************************/
//
//void Motor_Control()
//{	
//    static float pwm_Dead_L = 100;
//    static float pwm_Dead_R = 100;
//    static float all_PWM_L = 0;
//    static float all_PWM_R = 0;
//    
//    //���pwm���    //300  400  500  600  700  800  900  1000 1100
//    //��õ��ٶ�     //1130 2000 2750 3600 4350 5150 5870 6650 7450
//    
//    
//    //�����ܵ����
//    if(Slope_flag == 0)//���µ�
//    {
//        all_PWM_L = Angle.PWM - Speed.PWM - Direction.PWM;
//        all_PWM_R = Angle.PWM - Speed.PWM + Direction.PWM;
//    }
//    else//���µ�
//    {
//        if(Speed.Mode==1)
//        {
//            all_PWM_L = Angle.PWM - Speed.PWM*0.5 - Direction.PWM;
//            all_PWM_R = Angle.PWM - Speed.PWM*0.5 + Direction.PWM;
//        }
//        else if(Speed.Mode==2)
//        {
//            all_PWM_L = Angle.PWM - Direction.PWM;
//            all_PWM_R = Angle.PWM + Direction.PWM;
//        }
//        else if(Speed.Mode==3 || Speed.Mode==4 || Speed.Mode==5)
//        {
//            all_PWM_L = Angle.PWM + 2000 - Direction.PWM;
//            all_PWM_R = Angle.PWM + 2000 + Direction.PWM;
//        }
//    }
//    
//    
//    //���ر������յ���ͣ��
//    if(Angle.G_angle < -25 ||  Angle.G_angle > 40 || StartLine.flag==1)
//    {
//        if(Time_1ms > StartLine.time_record + StartLine.Delaytime)
//        {
//            all_PWM_L = 0;
//            all_PWM_R = 0;
//        }
//    }
//    
//    //��ת���ٺ�ĥ��̥
//    //all_PWM_L = all_PWM_R=1000;
//    
//    
//    //��ֹ���������޷�:���ٲ���(�����ٵ�)
//    //�������Ҳû�����������á�����
//    if(Speed.Mode==1 || Speed.Mode==2 || Speed.Mode==3 || Speed.Mode==4)
//    {
//    }
//    else if(Speed.Car > 5500)
//    {
//        if(all_PWM_L > 800 && all_PWM_R < 0)
//            all_PWM_R = 0;
//        else if(all_PWM_L < 0 && all_PWM_R > 800)
//            all_PWM_L = 0;
//    }
//    
//    
//    //1.�������PWM
//    if(all_PWM_L >= 0)
//    {
//        all_PWM_L += pwm_Dead_L;//������
//        if(all_PWM_L >= 3990)   //�޷�
//            all_PWM_L = 3990;
//        FTM_PWM_Duty(FTM0, CH2 , ((unsigned int)(all_PWM_L)) );//���
//        DIR_L_Forward;
//    }
//    else
//    {
//        all_PWM_L -= pwm_Dead_L;//������
//        if(all_PWM_L <= -3990)  //�޷�
//            all_PWM_L = -3990;
//        FTM_PWM_Duty(FTM0, CH2 , (unsigned int)(4000u + all_PWM_L));//���
//        DIR_L_Backward;
//    }
//    //2.�������PWM					
//    if(all_PWM_R >= 0)
//    {
//        all_PWM_R += pwm_Dead_R;//������
//        if(all_PWM_R >= 3990)   //�޷�
//            all_PWM_R = 3990;
//        FTM_PWM_Duty(FTM0, CH1 ,  ((unsigned int)(all_PWM_R)));//���
//        DIR_R_Forward;
//    }
//    else
//    {
//        all_PWM_R -= pwm_Dead_R;//������
//        if(all_PWM_R <= -3990)  //�޷�
//            all_PWM_R = -3990;
//        FTM_PWM_Duty(FTM0, CH1 , (unsigned int)(4000 +  all_PWM_R)  );//���
//        DIR_R_Backward;
//    }
//}
//
