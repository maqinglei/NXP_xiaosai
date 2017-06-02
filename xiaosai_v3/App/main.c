/*
---------------------���Ŷ���-----------------------
PTB20 PTB21 PTB22 PTB23            �ϲ�����ϵ�4��LED
#define MOTOR1_IO   PTD15       //����ǰ��          PTC10
#define MOTOR2_IO   PTA19       //���ֺ���
#define MOTOR3_IO   PTA5        //����ǰ��          PTC11
#define MOTOR4_IO   PTA24       //���ֺ���

#define MOTOR_FTM   FTM0
#define MOTOR1_PWM  FTM_CH3  
#define MOTOR2_PWM  FTM_CH4
#define MOTOR3_PWM  FTM_CH5
#define MOTOR4_PWM  FTM_CH6

#define MOTOR1_PWM_IO  FTM0_CH3
#define MOTOR2_PWM_IO  FTM0_CH4
#define MOTOR3_PWM_IO  FTM0_CH5
#define MOTOR4_PWM_IO  FTM0_CH6

*/

#include "common.h"
#include "include.h"



#define MOTOR1_IO   PTD15       //����ǰ��          PTC10�����ֲ��ٵı�����
#define MOTOR2_IO   PTA19       //���ֺ���
#define MOTOR3_IO   PTA5        //����ǰ��          PTC11�����ֲ��ٵı�����
#define MOTOR4_IO   PTA24       //���ֺ���

#define DIR_L MOTOR3_IO
#define DIR_R MOTOR1_IO
#define DIR_L_Forward      gpio_init (MOTOR3_IO,GPO,LOW);
#define DIR_L_Backward     gpio_init (MOTOR3_IO,GPO,HIGH);
#define DIR_R_Forward      gpio_init (MOTOR1_IO,GPO,LOW);
#define DIR_R_Backward    gpio_init (MOTOR1_IO,GPO,HIGH);

#define L_DeCoder  PTA12//PTC11
#define R_DeCoder  PTA10//PTC10

#define MOTOR_FTM   FTM0
#define MOTOR1_PWM  FTM_CH3
#define MOTOR2_PWM  FTM_CH4
#define MOTOR3_PWM  FTM_CH5
#define MOTOR4_PWM  FTM_CH6

#define MOTOR1_PWM_IO  FTM0_CH3
#define MOTOR2_PWM_IO  FTM0_CH4
#define MOTOR3_PWM_IO  FTM0_CH5
#define MOTOR4_PWM_IO  FTM0_CH6

#define MOTOR_HZ    (20*1000)

#define XOUT    ADC1_DM0
#define YOUT    ADC0_SE16
#define ZOUT    ADC0_SE17

#define Gyro1   ADC1_SE16
#define Gyro2   ADC1_DP0
#define Angle0     ADC0_SE18

#define UINT8   unsigned char
#define UINT16  unsigned short int
#define UINT32  unsigned int 

#define INT8    char   
#define INT16   short int 
#define INT32   int 


void Measure_speed();
void Measure_Acc();
void Angle_control();
void Speed_control();
void Direction_control();
void Direction_control_with_Ren();
void Motor_Control();




unsigned char imgbuff[CAMERA_H+1][CAMERA_DMA_NUM];                             //����洢����ͼ�������
//uint8 img[CAMERA_H][CAMERA_W];
void PORTA_IRQHandler();
void DMA0_IRQHandler();


/*************************************************************************
*  ģ�����ƣ�û������
*  ����˵��������ȫ�ֱ����Ķ����Լ���ʼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14
*************************************************************************/
struct CarAngle Angle = {0,0,0,0,0,0,0,0,0,0};
struct CarSpeed Speed = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
struct CarDirection Direction = {0,0,0,0,0,0};
struct CarStartLine StartLine = {0,0,0,0};
struct CarRen Ren = {0,0,0,0,0,0,0,0,{0,0}};
struct CarBlock Block = {0,0,0,0};
long int Time_1ms=0;


//��Ҫ����λ�������Ĳ�����
//ֱ��PD 50 0.27
float Zhili_P=50.0;
float Zhili_D=0.28;//10times

int test = 0;

//�ٶ�PID
float Sudu_P=0.0;
float Sudu_I=0.0;
float Sudu_D=0.0;

//����PD
float Fangxiang_P_R=21.0;//left
float Fangxiang_D_R=0.1;
float Fangxiang_P_L=21.0;//right
float Fangxiang_D_L=0.1;

float Ang_Set=82;//�Ƕ�ƫ��
float zhijiao_Power=0;


float Ang_Cha=0; //��ֱ���ٶȳ������ʱ����µ��ϼ����õĽǶ�ƫ����
float Ang_Podao=0;
int Expose_Time=5;//�ع�ʱ��

int qipaoyanshi=500;//������ʱʱ���ڵ�������֮ǰ

//Ԥ������
//uint32 data32=0;//����������ȡ���Ա���

//��������CCD��ֵ���ⲿ����
unsigned char Pixe1[128]={1,1,1,1,1,1,1,1,1};
unsigned char Pixe2[128]={1,1,1,1,1,1,1,1,1};
extern int16 line_left[3];//�����λ�ô�����飬���3�ε�
extern int16 line_right[3];//�Һ���λ�ô�����飬���3�ε�

//���ڶ�ʱ����չʱ��
//int CCD_Time=0;//ccd�ɼ�ʱ��������
int Speed_Time=0;//��һ���ٶȵļ��ʱ�����
int DSpeed_Time=0;
int D2Speed_Time=0;
int Speed_Con=0;//�ٶȿ���ʱ��

//������ٶ�ֵ
int GYRO_X=0;
int GYRO_Y=0;
int GYRO_Z=0;

//������ٶ�ֵ
double ACC_X=1.1;
double ACC_Y=1.1;
double ACC_Z=1.1;

//�����˲��������Ƕ�
float Ang_Acc=1.1;//���ٶȼ�atan���ýǶ�
float Ang_IGyro=1.1;//���ٶȻ������ýǶ�

float Ang_Error=1.1;//�����˲���ƫ��

float Ang=1.1;//����Ҫ�õ�PID�ĽǶ�

float OutData[4];//4·��λ����ʾ

//����
int LeftWheel_Count=0;//���������ۻ�
int RightWheel_Count=0;//���������ۻ�
int Check_Speed=0;//���������õ����ٶȣ�512�ߣ�
int D_Check_Speed=0;//�ٶ�΢��
int D2_Check_Speed=0;
int I_Check_Speed=0;    //�ٶȻ���
int Speed_Set=0;        //�ٶ��趨ֵ
int Speed_Error=0;      //�ٶ����ֵ
int Check_Speed_Last=0; //���ڼ����ٶ�D
int Check_Speed_Last2=0;//���ڼ����ٶ�D2
extern int zhijiao_hei;
//ת��
int Turning=0;
int guanche=0;

int dengta_yanshi=0;
int dengta=0;
int dengta1=0;
int dengta_end_you=0;
int dengta_end_wu=0;
int dengta_num=0;
int dengta_num1=0;
int qipao=0;
int pao_end_qian=0;
int pao_end=0;
int heheda=0;

//�ٶȿ��Ʊ���������
float Speed_Final_Out=0;//���յ��ٶȿ������
float Speed_Last=0;
float SpeedAverOut=0;//�ٶ�ƽ�����
float SpeedQueue[5]={0};
float Speed_Int=0;
float Speed_Rate=0;
float Speed_Down=0;

int Parameter2=0;
int Parameter1=0;
float Parameter3=0;
int Parameter4=0;

int dang=0;
int gear=0;
int yanshiqipao=0;
int yanshi = 0;


void main()
{
    uint16 x,y,z,gyro1,gyro2,ang;                           //����ADCת�����
    unsigned int i=0,en=0;//loop
    uint8 send_data_cnt=0;//ccd��λ�����ͼ��ʱ�����
    
    
    //��ʼ�����ٶȼƺ�������
      adc_init(XOUT);
      adc_init(YOUT);
      adc_init(ZOUT);
      adc_init(Gyro2);         //�Ǽ��ٶ�  Angular2
      adc_init(Gyro1);         //�Ǽ��ٶ�  Angular1
      adc_init(Angle0);
       x = adc_once(XOUT,ADC_8bit);
       y = adc_once(YOUT,ADC_8bit);
       z = adc_once(ZOUT,ADC_8bit);
       gyro1 = adc_once(Gyro1,ADC_8bit);
       gyro2 = adc_once(Gyro2,ADC_8bit);
       ang = adc_once(Angle0,ADC_8bit);

       
    //OV7725����ͷ��ʼ��
    camera_init(imgbuff);
    //�����жϷ�����
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //���� PORTA ���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //���� DMA0 ���жϷ�����Ϊ PORTA_IRQHandler

             
    //��ʼ����·pwmȥ���
    FTM_PWM_init(FTM0, MOTOR1_PWM, MOTOR_HZ, 0);                  
    FTM_PWM_init(FTM0, MOTOR2_PWM, MOTOR_HZ, 0);
    FTM_PWM_init(FTM0, MOTOR4_PWM, MOTOR_HZ, 0);
    FTM_PWM_init(FTM0, MOTOR3_PWM, MOTOR_HZ, 0);
    gpio_init  (MOTOR1_IO,GPO,LOW);
    gpio_init  (MOTOR3_IO,GPO,LOW);//���ʹ��
    
    //GPIO�ǵĳ�ʼ��
    gpio_init  (R_DeCoder, GPI, 0);//��ʼ�� PTB10(��һ·���ٷ���λ)
    gpio_init  (L_DeCoder, GPI, 0);//��ʼ�� PTB11(�ڶ�·���ٷ���λ)

    
    //gpio_init  (PTC5, GPI, 0);//��ʼ��
    
    port_init(PTC5, ALT1 | IRQ_FALLING);          
    set_vector_handler(PORTC_VECTORn ,PORTC_IRQHandler);    
    enable_irq (PORTC_IRQn);          
    
    //�趨��ʱ��0 1ms�ж�
    pit_init_ms(PIT0, 1);                                  //��ʼ��PIT0����ʱʱ��Ϊ�� 1ms
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϷ�����Ϊ PIT0_IRQHandler
    enable_irq (PIT0_IRQn);
    
    
    //��ʼ�����벶׽�ж���
    FTM_Input_init(FTM1, FTM_CH0, FTM_Falling,FTM_PS_1);              //��ʼ��FTM���벶׽ģʽ�����ڵ�һ·���٣�
    port_init_NoALT(FTM1_CH0 ,PULLUP);

    set_vector_handler(FTM1_VECTORn ,FTM1_INPUT_IRQHandler);//����FTM1���жϷ�����Ϊ FTM1_INPUT_IRQHandler
    enable_irq (FTM1_IRQn);

    FTM_Input_init(FTM2, FTM_CH0, FTM_Falling,FTM_PS_1);              //��ʼ��FTM���벶׽ģʽ�����ڵڶ�·���٣�
    port_init_NoALT(FTM2_CH0 ,PULLUP);

    set_vector_handler(FTM2_VECTORn ,FTM2_INPUT_IRQHandler);//����FTM2���жϷ�����Ϊ FTM1_INPUT_IRQHandler
    enable_irq (FTM2_IRQn);  
    


    while(1)
    {
          camera_get_img();                                   //����ͷ��ȡͼ��
          Process_Image();
        
    }
}


/*!
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 29;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //ʹ�����ж�
    n = 28;
    if(flag & (1 << n))                                 //PTA28�����ж�
    {
        camera_href();
    }
#endif


}




/*************************************************************************
*  �������ƣ�VSYNC_IRQ
*  ����˵����PORTD�˿��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-1-25    �Ѳ���
*  ��    ע�����ź���Ҫ�Լ���ʼ�������
*************************************************************************/
void VSYNC_IRQ(void)
{    
    static UINT16 czd=0;
    static u32 flag;
    //Clear Interrupt flag
    flag = PORTD_ISFR;
    PORTD_ISFR = flag;
    czd++;
    if(ov7725_eagle_img_flag == IMG_START)	//��Ҫ��ʼ�ɼ�ͼ��
    {
        //DMA_PORTx2BUFF_Init(CAMERA_DMA_CH, (void *)&PTB_BYTE2_IN, (void *)ov7725_eagle_img_buff, PTE27, DMA_BYTE1, CAMERA_SIZE , DMA_falling);
        //DMAͨ��0��ʼ����PTA27����Դ(Ĭ��������)��Դ��ַΪPTB_B0_IN��Ŀ�ĵ�ַΪ��IMG_BUFF��ÿ�δ���1Byte
        dma_portx2buff_init(CAMERA_DMA_CH, (void *)&PTB_B0_IN, (void *)ov7725_eagle_img_buff, PTA27, DMA_BYTE1, CAMERA_DMA_NUM, DADDR_KEEPON);

        DMA_EN(CAMERA_DMA_CH);            		//ʹ��ͨ��CHn Ӳ������
        DMA_DADDR(CAMERA_DMA_CH) = (u32)ov7725_eagle_img_buff; //�ָ���ַ
        ov7725_eagle_img_flag = IMG_GATHER;		        //���ͼ��ɼ���
        disable_irq(90);  
    }
    else					//ͼ��ɼ�����
    {
        disable_irq(90); 			//�ر�PTA���ж�
        ov7725_eagle_img_flag = IMG_FAIL;		//���ͼ��ɼ�ʧ��
    }
}




/*************************************************************************
*  �������ƣ�DMA0_IRQHandler
*  ����˵����DMA0
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-1-25    �Ѳ���
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸�
*************************************************************************/
void DMA0_IRQHandler()
{
  
//    DMA_DIS(CAMERA_DMA_CH);            	//�ر�ͨ��CHn Ӳ������
//    DMA_IRQ_CLEAN(CAMERA_DMA_CH);           //���ͨ�������жϱ�־λ
//    ov7725_eagle_img_flag = IMG_FINISH ;  
   camera_dma();
}
///*!
// *  @brief      DMA0�жϷ�����
// *  @since      v5.0
// */
//void DMA0_IRQHandler()
//{
//    camera_dma();
//}





/*************************************************************************
*  �������ƣ�PIT0_IRQHandler
*  ����˵����PIT0 ��ʱ�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѳ���
*  ��    ע��
*************************************************************************/
void PIT0_IRQHandler(void)
{
    static unsigned char TimeCnt_20ms = 0;	  //20msʱ�������
    static unsigned char flag = 0;                //5ms�ķ�ʱ��־
    PIT_Flag_Clear(PIT0);
    Time_1ms++; 
  //  _LED1 = (Time_1ms/500)%2;
    TimeCnt_20ms++;
    if(TimeCnt_20ms >= 20)
    {TimeCnt_20ms = 0;}
    flag = TimeCnt_20ms%5;
    //����ΪֹT=0.5us
    /**************************************************************/
    /*********************Own code*********************************/
    /**************************************************************/   

    
    //�ٶȿ��� Tmax=8.5us
    if(flag==0 && Time_1ms>Stand_Time)
    {
        Measure_speed();
        Speed_control();
    }
    //����angle_Out������ֱ������ T=449us IICʱ�䳤
    else if(flag==1)
    {
        Measure_Acc();//T=340us
        Angle_control();//T=100us
        Motor_Control();//T=9us
    }
    else if(Ren.flag==1 && flag==2)//�����ֵķ������
    {
        Direction_control_with_Ren();//T=58us
        Motor_Control();
    }
    //�������
    if(Ren.flag==0 && Direction.output_enable==1)
    {
        Direction_control();//T=54us
        Motor_Control();
        Direction.output_enable = 0;
    }
    
    
    //���ٽ׶� T=3us��ֱ�Ӿʹﵽ�趨ֵ
    if(Time_1ms > Stand_Time && Speed.Goal < Speed.Goal_init)
    { 
        Speed.Goal = Speed.Goal_init + 1;
 //       buzzer = 1;
    }
    else
    {
//        if(Ren.flag==1 || Cross_flag==1 || Slope_flag==1 || Time_1ms < Block.time + 1000 || smallS_flag==1)
////            buzzer = 1;
//        else
//            buzzer = 0;
    }
    
    //LED��ˮ�ƣ�֤���ڽ���ʱ���ж�
    //Water_LEDs();
    /*********************************************************************/
    /**************************Own code end*******************************/
    /*********************************************************************/
    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
}







/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�USART3_IRQHandler
*  ����˵��������3 �ж� ���� ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѳ���
*  ��    ע��
*************************************************************************/
void USART3_IRQHandler(void)
{

}




/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�SysTick_Handler
*  ����˵����ϵͳ�δ�ʱ���жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-18    �Ѳ���
*  ��    ע��ucos���õõ�
*************************************************************************/
void SysTick_Handler(void)
{
    //    OSIntEnter();
    //    OSTimeTick();
    //    OSIntExit();
}





/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�HardFault_Handler
*  ����˵����Ӳ���Ϸ��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-4    �Ѳ���
*  ��    ע��������LED��˸��ָʾ������Ӳ���Ϸ�
*************************************************************************/
void HardFault_Handler(void)
{
    while (1)
    {
        printf("\n****Ӳ���Ϸô���!!!*****\r\n\n");
    }
}




/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�PendSV_Handler
*  ����˵����PendSV��������ϵͳ���ã��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-15    �Ѳ���
*  ��    ע��uC/OS�����л�����
*************************************************************************/
void PendSV_Handler(void)
{
}





/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�FTM0_IRQHandler
*  ����˵����FTM0���벶׽�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-25
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸ģ��ο����еĴ�������Լ��Ĺ���
*************************************************************************/
void FTM0_IRQHandler()
{
}




/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�FTM1_IRQHandler
*  ����˵����FTM1���벶׽�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-25
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸ģ��ο����еĴ�������Լ��Ĺ���
*************************************************************************/
void FTM1_IRQHandler()
{
}



/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��ISR_fun.c
 * ����         ���߶˰������жϷ��������Ӻ���������ISR.c
 * ʵ��ƽ̨     ������ӡ�󿪷���
 * ��汾       ������Ұ���
 * Ƕ��ϵͳ     ��
 * ����         ��xuxu
**********************************************************************************/



/*************************************************************************
*  �������ƣ�Measure_speed
*  ����˵���������ٶ�
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*************************************************************************/
void Measure_speed()
{
    static unsigned char SpeedDirection_L;
    static unsigned char SpeedDirection_R;
    SpeedDirection_L = (FTM1_QDCTRL & FTM_QDCTRL_QUADIR_MASK);
    SpeedDirection_R = (FTM2_QDCTRL & FTM_QDCTRL_QUADIR_MASK);
    //���ֲ���
    if(SpeedDirection_L==0)	//��ת
    {
        if(10000 - FTM1_CNT < 5000)//��ֹbug
          Speed.L_5ms = 10000 - FTM1_CNT;
    }
    else                        //��ת
    {
        if(FTM1_CNT < 5000)//��ֹbug
          Speed.L_5ms = 0 - FTM1_CNT;
    }
    //���ֲ���
    if(SpeedDirection_R==0)	//��ת
    {
        if(10001 - FTM2_CNT < 5000)//��ֹbug
          Speed.R_5ms = 0 - (10000-FTM2_CNT);
    }
    else                         //��ת
    {
        if(FTM2_CNT < 5000)//��ֹbug
          Speed.R_5ms = FTM2_CNT;
    }
    #define ratio 1.953125//��������С�������������256�ߣ�ԭ���õ�500��
    Speed.L_5ms = (int)(Speed.L_5ms*ratio);
    Speed.R_5ms = (int)(Speed.R_5ms*ratio);
    //clear
    FTM1_CNT = 0;
    FTM2_CNT = 0;
}


/*************************************************************************
*  �������ƣ�Measure_Acc
*  ����˵�����������ٶȼ�ֵ
*  ����˵������
*  �������أ��ޣ�������ȫ�ֱ���a_sin��a_cos��
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*************************************************************************/
void Measure_Acc()
{
    static float a_sin_new=0,a_sin[3];
    static float a_cos_new=0,a_cos[3];
    
    for(int i = 0;i < 3;i++)
        a_sin[i] = Get_mma8451_once('Z');
    a_sin_new = (a_sin[0] + a_sin[1] + a_sin[2])/3.0;
    
    for(int i = 0;i < 3;i++)
        a_cos[i] = Get_mma8451_once('X');
    a_cos_new = (a_cos[0] + a_cos[1] + a_cos[2])/3.0;
    
    //��ͨ�˲�
    Angle.a_sin = Angle.a_sin*0.5 + a_sin_new*0.5;//��90��-90��sinֵ 1��0��-1�仯,��Ϊ��
    Angle.a_cos = Angle.a_cos*0.5 + a_cos_new*0.5;//��90��-90) cosֵ 0��-1��0�仯,��Ϊ��
}



/*************************************************************************
*  �������ƣ�Angle_control
*  ����˵�����Ƕ��ںϣ�������Ƕȣ�����Ƕ�pwm���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*************************************************************************/
#define Gyro_OFFSET (-4)
void Angle_control()
{
    //ֱ��
    #define k_Gyro 0.07   //���ٶȷŴ���
    #define dt 0.005
    #define tg 2         //**����ʱ��:1~4
    static float mG_delta=0;      //��angle_speedһ������
    static float Angle_Gyro_old=0;
    
    //���ĸ����Ǻ�����������ô��װ��ʵ�����Ű�װ��asin��
    /*if(Angle.a_cos <= 0)
    {
        if(Angle.a_cos==0)
            Angle.m_angle = asin(Angle.a_sin)*57.295779513;  	//180/pi=57.295779513
        else
            Angle.m_angle = atan(Angle.a_sin/(0 - Angle.a_cos))*57.295779513;
    }
    else
    {
        Angle.m_angle = atan(Angle.a_sin/Angle.a_cos)*57.295779513;
        Angle.m_angle = 180 - Angle.m_angle;
    }*/
    Angle.m_angle = asin(Angle.a_sin)*57.295779513;
    if(Angle.m_angle > 90)
        Angle.m_angle = 90;
    else if(Angle.m_angle < -90)
        Angle.m_angle = -90;
   
    
    //�õ�Angle.G_angle
    Angle_Gyro_old = Angle.Gyro;
    Angle.Gyro = (float)(Get_Gyro(1,'X') - Gyro_OFFSET);
    Angle.speed = 0 - k_Gyro *(Angle_Gyro_old + Angle.Gyro)/2.0;
    mG_delta = (Angle.m_angle - Angle.G_angle) / tg;
    Angle.G_angle += (Angle.speed + mG_delta) * dt;
        
    //�õ�Angle.PWM
    if(Ren.flag == 0)//���������
    {
        Angle.PWM = (Angle.OFFSET - Angle.G_angle)*Angle.P
                      - Angle.speed * Angle.D;
    }
    else//���������
    {
        Angle.PWM = (Angle.OFFSET - Angle.G_angle)*(Angle.P +0)
                      - Angle.speed * (Angle.D + 0);
    }
}




/*************************************************************************
*  �������ƣ�Speed_control
*  ����˵���������ٶ�pwm���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*************************************************************************/
void Speed_control()
{
    static unsigned char speed_Period=0;//�ٶȿ������ڱ���
    #define speed_Period_Constant 20 //�ٶȿ�������
    static float speed_Delta=0;
    static float Tmp_Speed_P;
    static int temp_L_100ms=0,temp_R_100ms=0;
    
    speed_Period++;
    temp_L_100ms += Speed.L_5ms;
    temp_R_100ms += Speed.R_5ms;
    if(speed_Period >= 20)//�ٶ�PID�������ԡ�100msһ�μ���
    {
        speed_Period = 0;
        Speed.L_100ms = temp_L_100ms;
        Speed.R_100ms = temp_R_100ms;
        Speed.Car = (float)((Speed.L_100ms + Speed.R_100ms)/2.0);
        temp_L_100ms = 0;
        temp_R_100ms = 0;
        
        //�ٶȿ���
        speed_Delta = Speed.Goal - Speed.Car;
        
        //IIIIIIIIIIIIIIIIIIIII����IIIIIIIIIIIIIIIIIII
        #define SPEEDUP_TIME 1500
        if(Time_1ms < Stand_Time + SPEEDUP_TIME)//վ��֮�������֮�ڣ�ʹ������
        {
            if(Speed.Mode==3)
                Speed.PWM_Integral = 1000 + 3000*(Stand_Time + SPEEDUP_TIME - Time_1ms)/SPEEDUP_TIME;
            if(Speed.Mode==4)
                Speed.PWM_Integral = 0 + 3500*(Stand_Time + SPEEDUP_TIME - Time_1ms)/SPEEDUP_TIME;
            else
                Speed.PWM_Integral = 1000 + 3000*(Stand_Time + SPEEDUP_TIME - Time_1ms)/SPEEDUP_TIME;
        }
        else//վ��֮�������֮��
        {
            Speed.PWM_Integral += speed_Delta * Speed.I;
            //PWM_Integral�޷�
            if(Speed.PWM_Integral > Speed.I_Limit_PWM_max)//�޷���
                Speed.PWM_Integral = Speed.I_Limit_PWM_max;
            else if(Speed.PWM_Integral <= Speed.I_Limit_PWM_min)
                Speed.PWM_Integral = Speed.I_Limit_PWM_min;
        }
        
        //PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
        //��������ͨ�޷������ڻ�û���ʱ��
        if(speed_Delta> 0 - Speed.I_Error_Start && speed_Delta < Speed.I_Error_Start)
            Tmp_Speed_P = Speed.P * speed_Delta;
        else if(speed_Delta< 0 - Speed.I_Error_Start)
            Tmp_Speed_P = Speed.P * (0 - Speed.I_Error_Start);
        else if(speed_Delta > Speed.I_Error_Start)
            Tmp_Speed_P = Speed.P * Speed.I_Error_Start;
        
        //���
        Speed.PWM_Per = ( Tmp_Speed_P
                         + Speed.PWM_Integral
                             - Speed.PWM)  /  speed_Period_Constant;
    }
    Speed.PWM += Speed.PWM_Per;
}




/*************************************************************************
*  �������ƣ�Direction_control��Direction_control_with_Ren
*  ����˵�������㷽��pwm����������Ͳ��������֣�
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*************************************************************************/
#define Dir_Gyro_OFFSET 10
void Direction_control()
{
    Direction.Gyro = (float)(Get_Gyro(1,'Y') - Dir_Gyro_OFFSET); //����Ϊ��
    if(Block.flag==0)//�к�שͷ�ϰ����
    {
        Direction.PWM_Per = Direction.P * (black_centre - CENTER )	//���
            + Direction.D * Direction.Gyro
                - Direction.PWM;
    }
    else//û�к�שͷ�ϰ����
    {
        if(Time_1ms < Block.time + Block.delaytime)
            Direction.PWM_Per = Direction.P * (black_centre + Block.Offset - CENTER )	//���
                         + Direction.D * Direction.Gyro
                           - Direction.PWM;
        else
            Block.flag = 0;
    }
    Direction.PWM += Direction.PWM_Per;
}

void Direction_control_with_Ren()//???����ʱ���Ƿ���Ҫ�����Dֵ��
{
    if(Time_1ms > Ren.record_time + Ren.Delaytime1)//�����˵�����ʱ���
    {
        Direction.Gyro = (float)(Get_Gyro(1,'Y') - Dir_Gyro_OFFSET); //����Ϊ��
        if(Ren.Loaction > CENTER)//�ҹ�
        {
            black_centre = 160 + Ren.Strength;
        }
        else//���
        {
            if(Speed.Mode==3)//����ͷ���ˣ�3��λ����ղ���
            {
                if(Multiple_line_enable==1)
                    black_centre = 160 - Ren.Strength - 27;
                else
                    black_centre = 160 - Ren.Strength - 22;
            }
            else if(Speed.Mode==4 || Speed.Mode==5)//����ͷ���ˣ�4,5��λ����ղ���
            {
                if(Multiple_line_enable==1)
                    black_centre = 160 - Ren.Strength - 33;
                else
                    black_centre = 160 - Ren.Strength - 30;
            }
            else//����ͷ���ˣ�������λ��պ��ҹ�����
            {
                black_centre = 160 - Ren.Strength;
            }
        }
        
        //ʱ�����
        if(Time_1ms > Ren.record_time + Ren.Delaytime1 + Ren.Delaytime2)
        {
            Ren.flag = 0;
        }
        
        //���
        Direction.PWM_Per=(Direction.P * (black_centre - CENTER)	//���
                           + Direction.D * Direction.Gyro
                               - Direction.PWM);
        Direction.PWM += Direction.PWM_Per;
    }
}



/*************************************************************************
*  �������ƣ�Motor_Control
*  ����˵����pwm���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*************************************************************************/

void Motor_Control()
{	
    static float pwm_Dead_L = 100;
    static float pwm_Dead_R = 100;
    static float all_PWM_L = 0;
    static float all_PWM_R = 0;
    
    //���pwm���    //300  400  500  600  700  800  900  1000 1100
    //��õ��ٶ�     //1130 2000 2750 3600 4350 5150 5870 6650 7450
    
    
    //�����ܵ����
    if(Slope_flag == 0)//���µ�
    {
        all_PWM_L = Angle.PWM - Speed.PWM - Direction.PWM;
        all_PWM_R = Angle.PWM - Speed.PWM + Direction.PWM;
    }
    else//���µ�
    {
        if(Speed.Mode==1)
        {
            all_PWM_L = Angle.PWM - Speed.PWM*0.5 - Direction.PWM;
            all_PWM_R = Angle.PWM - Speed.PWM*0.5 + Direction.PWM;
        }
        else if(Speed.Mode==2)
        {
            all_PWM_L = Angle.PWM - Direction.PWM;
            all_PWM_R = Angle.PWM + Direction.PWM;
        }
        else if(Speed.Mode==3 || Speed.Mode==4 || Speed.Mode==5)
        {
            all_PWM_L = Angle.PWM + 2000 - Direction.PWM;
            all_PWM_R = Angle.PWM + 2000 + Direction.PWM;
        }
    }
    
    
    //���ر������յ���ͣ��
    if(Angle.G_angle < -25 ||  Angle.G_angle > 40 || StartLine.flag==1)
    {
        if(Time_1ms > StartLine.time_record + StartLine.Delaytime)
        {
            all_PWM_L = 0;
            all_PWM_R = 0;
        }
    }
    
    //��ת���ٺ�ĥ��̥
    //all_PWM_L = all_PWM_R=1000;
    
    
    //��ֹ���������޷�:���ٲ���(�����ٵ�)
    //�������Ҳû�����������á�����
    if(Speed.Mode==1 || Speed.Mode==2 || Speed.Mode==3 || Speed.Mode==4)
    {
    }
    else if(Speed.Car > 5500)
    {
        if(all_PWM_L > 800 && all_PWM_R < 0)
            all_PWM_R = 0;
        else if(all_PWM_L < 0 && all_PWM_R > 800)
            all_PWM_L = 0;
    }
    
    
    //1.�������PWM
    if(all_PWM_L >= 0)
    {
        all_PWM_L += pwm_Dead_L;//������
        if(all_PWM_L >= 3990)   //�޷�
            all_PWM_L = 3990;
        FTM_PWM_Duty(FTM0, MOTOR3_PWM , ((unsigned int)(all_PWM_L)) );//���
        DIR_L_Forward;
    }
    else
    {
        all_PWM_L -= pwm_Dead_L;//������
        if(all_PWM_L <= -3990)  //�޷�
            all_PWM_L = -3990;
        FTM_PWM_Duty(FTM0, MOTOR3_PWM , (unsigned int)(4000u + all_PWM_L));//���
        DIR_L_Backward;
    }
    //2.�������PWM					
    if(all_PWM_R >= 0)
    {
        all_PWM_R += pwm_Dead_R;//������
        if(all_PWM_R >= 3990)   //�޷�
            all_PWM_R = 3990;
        FTM_PWM_Duty(FTM0, MOTOR1_PWM ,  ((unsigned int)(all_PWM_R)));//���
        DIR_R_Forward;
    }
    else
    {
        all_PWM_R -= pwm_Dead_R;//������
        if(all_PWM_R <= -3990)  //�޷�
            all_PWM_R = -3990;
        FTM_PWM_Duty(FTM0, MOTOR1_PWM , (unsigned int)(4000 +  all_PWM_R)  );//���
        DIR_R_Backward;
    }
}


