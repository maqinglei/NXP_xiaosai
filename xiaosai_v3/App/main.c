/*
---------------------引脚定义-----------------------
PTB20 PTB21 PTB22 PTB23            上层板子上的4个LED
#define MOTOR1_IO   PTD15       //右轮前进          PTC10
#define MOTOR2_IO   PTA19       //右轮后退
#define MOTOR3_IO   PTA5        //左轮前进          PTC11
#define MOTOR4_IO   PTA24       //左轮后退

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



#define MOTOR1_IO   PTD15       //右轮前进          PTC10是右轮测速的编码器
#define MOTOR2_IO   PTA19       //右轮后退
#define MOTOR3_IO   PTA5        //左轮前进          PTC11是左轮测速的编码器
#define MOTOR4_IO   PTA24       //左轮后退

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




unsigned char imgbuff[CAMERA_H+1][CAMERA_DMA_NUM];                             //定义存储接收图像的数组
//uint8 img[CAMERA_H][CAMERA_W];
void PORTA_IRQHandler();
void DMA0_IRQHandler();


/*************************************************************************
*  模块名称：没有名称
*  功能说明：各种全局变量的定义以及初始化
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14
*************************************************************************/
struct CarAngle Angle = {0,0,0,0,0,0,0,0,0,0};
struct CarSpeed Speed = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
struct CarDirection Direction = {0,0,0,0,0,0};
struct CarStartLine StartLine = {0,0,0,0};
struct CarRen Ren = {0,0,0,0,0,0,0,0,{0,0}};
struct CarBlock Block = {0,0,0,0};
long int Time_1ms=0;


//需要用上位机调整的参数们
//直立PD 50 0.27
float Zhili_P=50.0;
float Zhili_D=0.28;//10times

int test = 0;

//速度PID
float Sudu_P=0.0;
float Sudu_I=0.0;
float Sudu_D=0.0;

//方向PD
float Fangxiang_P_R=21.0;//left
float Fangxiang_D_R=0.1;
float Fangxiang_P_L=21.0;//right
float Fangxiang_D_L=0.1;

float Ang_Set=82;//角度偏移
float zhijiao_Power=0;


float Ang_Cha=0; //在直线速度冲刺起来时候和坡道上减速用的角度偏移量
float Ang_Podao=0;
int Expose_Time=5;//曝光时间

int qipaoyanshi=500;//起跑延时时间在灯塔出现之前

//预留变量
//uint32 data32=0;//用于扇区读取测试变量

//储存两个CCD的值，外部变量
unsigned char Pixe1[128]={1,1,1,1,1,1,1,1,1};
unsigned char Pixe2[128]={1,1,1,1,1,1,1,1,1};
extern int16 line_left[3];//左黑线位置存放数组，最近3次的
extern int16 line_right[3];//右黑线位置存放数组，最近3次的

//用于定时器扩展时间
//int CCD_Time=0;//ccd采集时间间隔变量
int Speed_Time=0;//测一次速度的间隔时间变量
int DSpeed_Time=0;
int D2Speed_Time=0;
int Speed_Con=0;//速度控制时间

//储存角速度值
int GYRO_X=0;
int GYRO_Y=0;
int GYRO_Z=0;

//储存加速度值
double ACC_X=1.1;
double ACC_Y=1.1;
double ACC_Z=1.1;

//互补滤波的两个角度
float Ang_Acc=1.1;//加速度计atan所得角度
float Ang_IGyro=1.1;//角速度积分所得角度

float Ang_Error=1.1;//互补滤波的偏差

float Ang=1.1;//最终要用到PID的角度

float OutData[4];//4路上位机显示

//测速
int LeftWheel_Count=0;//左轮脉冲累积
int RightWheel_Count=0;//右轮脉冲累积
int Check_Speed=0;//编码器检测得到的速度（512线）
int D_Check_Speed=0;//速度微分
int D2_Check_Speed=0;
int I_Check_Speed=0;    //速度积分
int Speed_Set=0;        //速度设定值
int Speed_Error=0;      //速度误差值
int Check_Speed_Last=0; //用于计算速度D
int Check_Speed_Last2=0;//用于计算速度D2
extern int zhijiao_hei;
//转弯
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

//速度控制变量新增：
float Speed_Final_Out=0;//最终的速度控制输出
float Speed_Last=0;
float SpeedAverOut=0;//速度平滑输出
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
    uint16 x,y,z,gyro1,gyro2,ang;                           //保存ADC转换结果
    unsigned int i=0,en=0;//loop
    uint8 send_data_cnt=0;//ccd上位机发送间隔时间变量
    
    
    //初始化加速度计和陀螺仪
      adc_init(XOUT);
      adc_init(YOUT);
      adc_init(ZOUT);
      adc_init(Gyro2);         //角加速度  Angular2
      adc_init(Gyro1);         //角加速度  Angular1
      adc_init(Angle0);
       x = adc_once(XOUT,ADC_8bit);
       y = adc_once(YOUT,ADC_8bit);
       z = adc_once(ZOUT,ADC_8bit);
       gyro1 = adc_once(Gyro1,ADC_8bit);
       gyro2 = adc_once(Gyro2,ADC_8bit);
       ang = adc_once(Angle0,ADC_8bit);

       
    //OV7725摄像头初始化
    camera_init(imgbuff);
    //配置中断服务函数
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //设置 PORTA 的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //设置 DMA0 的中断服务函数为 PORTA_IRQHandler

             
    //初始化四路pwm去电机
    FTM_PWM_init(FTM0, MOTOR1_PWM, MOTOR_HZ, 0);                  
    FTM_PWM_init(FTM0, MOTOR2_PWM, MOTOR_HZ, 0);
    FTM_PWM_init(FTM0, MOTOR4_PWM, MOTOR_HZ, 0);
    FTM_PWM_init(FTM0, MOTOR3_PWM, MOTOR_HZ, 0);
    gpio_init  (MOTOR1_IO,GPO,LOW);
    gpio_init  (MOTOR3_IO,GPO,LOW);//电机使能
    
    //GPIO们的初始化
    gpio_init  (R_DeCoder, GPI, 0);//初始化 PTB10(第一路测速方向位)
    gpio_init  (L_DeCoder, GPI, 0);//初始化 PTB11(第二路测速方向位)

    
    //gpio_init  (PTC5, GPI, 0);//初始化
    
    port_init(PTC5, ALT1 | IRQ_FALLING);          
    set_vector_handler(PORTC_VECTORn ,PORTC_IRQHandler);    
    enable_irq (PORTC_IRQn);          
    
    //设定定时器0 1ms中断
    pit_init_ms(PIT0, 1);                                  //初始化PIT0，定时时间为： 1ms
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //设置PIT0的中断服务函数为 PIT0_IRQHandler
    enable_irq (PIT0_IRQn);
    
    
    //初始化输入捕捉中断们
    FTM_Input_init(FTM1, FTM_CH0, FTM_Falling,FTM_PS_1);              //初始化FTM输入捕捉模式（用于第一路测速）
    port_init_NoALT(FTM1_CH0 ,PULLUP);

    set_vector_handler(FTM1_VECTORn ,FTM1_INPUT_IRQHandler);//设置FTM1的中断服务函数为 FTM1_INPUT_IRQHandler
    enable_irq (FTM1_IRQn);

    FTM_Input_init(FTM2, FTM_CH0, FTM_Falling,FTM_PS_1);              //初始化FTM输入捕捉模式（用于第二路测速）
    port_init_NoALT(FTM2_CH0 ,PULLUP);

    set_vector_handler(FTM2_VECTORn ,FTM2_INPUT_IRQHandler);//设置FTM2的中断服务函数为 FTM1_INPUT_IRQHandler
    enable_irq (FTM2_IRQn);  
    


    while(1)
    {
          camera_get_img();                                   //摄像头获取图像
          Process_Image();
        
    }
}


/*!
 *  @brief      PORTA中断服务函数
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //清中断标志位

    n = 29;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //使用行中断
    n = 28;
    if(flag & (1 << n))                                 //PTA28触发中断
    {
        camera_href();
    }
#endif


}




/*************************************************************************
*  函数名称：VSYNC_IRQ
*  功能说明：PORTD端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要自己初始化来清除
*************************************************************************/
void VSYNC_IRQ(void)
{    
    static UINT16 czd=0;
    static u32 flag;
    //Clear Interrupt flag
    flag = PORTD_ISFR;
    PORTD_ISFR = flag;
    czd++;
    if(ov7725_eagle_img_flag == IMG_START)	//需要开始采集图像
    {
        //DMA_PORTx2BUFF_Init(CAMERA_DMA_CH, (void *)&PTB_BYTE2_IN, (void *)ov7725_eagle_img_buff, PTE27, DMA_BYTE1, CAMERA_SIZE , DMA_falling);
        //DMA通道0初始化，PTA27触发源(默认上升沿)，源地址为PTB_B0_IN，目的地址为：IMG_BUFF，每次传输1Byte
        dma_portx2buff_init(CAMERA_DMA_CH, (void *)&PTB_B0_IN, (void *)ov7725_eagle_img_buff, PTA27, DMA_BYTE1, CAMERA_DMA_NUM, DADDR_KEEPON);

        DMA_EN(CAMERA_DMA_CH);            		//使能通道CHn 硬件请求
        DMA_DADDR(CAMERA_DMA_CH) = (u32)ov7725_eagle_img_buff; //恢复地址
        ov7725_eagle_img_flag = IMG_GATHER;		        //标记图像采集中
        disable_irq(90);  
    }
    else					//图像采集错误
    {
        disable_irq(90); 			//关闭PTA的中断
        ov7725_eagle_img_flag = IMG_FAIL;		//标记图像采集失败
    }
}




/*************************************************************************
*  函数名称：DMA0_IRQHandler
*  功能说明：DMA0
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要根据自己初始化来修改
*************************************************************************/
void DMA0_IRQHandler()
{
  
//    DMA_DIS(CAMERA_DMA_CH);            	//关闭通道CHn 硬件请求
//    DMA_IRQ_CLEAN(CAMERA_DMA_CH);           //清除通道传输中断标志位
//    ov7725_eagle_img_flag = IMG_FINISH ;  
   camera_dma();
}
///*!
// *  @brief      DMA0中断服务函数
// *  @since      v5.0
// */
//void DMA0_IRQHandler()
//{
//    camera_dma();
//}





/*************************************************************************
*  函数名称：PIT0_IRQHandler
*  功能说明：PIT0 定时中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014-1-14    已测试
*  备    注：
*************************************************************************/
void PIT0_IRQHandler(void)
{
    static unsigned char TimeCnt_20ms = 0;	  //20ms时间计数器
    static unsigned char flag = 0;                //5ms的分时标志
    PIT_Flag_Clear(PIT0);
    Time_1ms++; 
  //  _LED1 = (Time_1ms/500)%2;
    TimeCnt_20ms++;
    if(TimeCnt_20ms >= 20)
    {TimeCnt_20ms = 0;}
    flag = TimeCnt_20ms%5;
    //到此为止T=0.5us
    /**************************************************************/
    /*********************Own code*********************************/
    /**************************************************************/   

    
    //速度控制 Tmax=8.5us
    if(flag==0 && Time_1ms>Stand_Time)
    {
        Measure_speed();
        Speed_control();
    }
    //计算angle_Out，并且直立控制 T=449us IIC时间长
    else if(flag==1)
    {
        Measure_Acc();//T=340us
        Angle_control();//T=100us
        Motor_Control();//T=9us
    }
    else if(Ren.flag==1 && flag==2)//有人字的方向输出
    {
        Direction_control_with_Ren();//T=58us
        Motor_Control();
    }
    //方向输出
    if(Ren.flag==0 && Direction.output_enable==1)
    {
        Direction_control();//T=54us
        Motor_Control();
        Direction.output_enable = 0;
    }
    
    
    //加速阶段 T=3us，直接就达到设定值
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
    
    //LED流水灯，证明在进定时器中断
    //Water_LEDs();
    /*********************************************************************/
    /**************************Own code end*******************************/
    /*********************************************************************/
    PIT_Flag_Clear(PIT0);       //清中断标志位
}







/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：USART3_IRQHandler
*  功能说明：串口3 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014-1-14    已测试
*  备    注：
*************************************************************************/
void USART3_IRQHandler(void)
{

}




/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：SysTick_Handler
*  功能说明：系统滴答定时器中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-18    已测试
*  备    注：ucos里用得到
*************************************************************************/
void SysTick_Handler(void)
{
    //    OSIntEnter();
    //    OSTimeTick();
    //    OSIntExit();
}





/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：HardFault_Handler
*  功能说明：硬件上访中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-4    已测试
*  备    注：可以用LED闪烁来指示发生了硬件上访
*************************************************************************/
void HardFault_Handler(void)
{
    while (1)
    {
        printf("\n****硬件上访错误!!!*****\r\n\n");
    }
}




/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：PendSV_Handler
*  功能说明：PendSV（可悬起系统调用）中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-15    已测试
*  备    注：uC/OS用来切换任务
*************************************************************************/
void PendSV_Handler(void)
{
}





/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：FTM0_IRQHandler
*  功能说明：FTM0输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-25
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/
void FTM0_IRQHandler()
{
}




/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：FTM1_IRQHandler
*  功能说明：FTM1输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-25
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/
void FTM1_IRQHandler()
{
}



/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：ISR_fun.c
 * 描述         ：高端霸气的中断服务函数的子函数，供给ISR.c
 * 实验平台     ：凌立印象开发板
 * 库版本       ：基于野火库
 * 嵌入系统     ：
 * 作者         ：xuxu
**********************************************************************************/



/*************************************************************************
*  函数名称：Measure_speed
*  功能说明：测量速度
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/
void Measure_speed()
{
    static unsigned char SpeedDirection_L;
    static unsigned char SpeedDirection_R;
    SpeedDirection_L = (FTM1_QDCTRL & FTM_QDCTRL_QUADIR_MASK);
    SpeedDirection_R = (FTM2_QDCTRL & FTM_QDCTRL_QUADIR_MASK);
    //左轮测速
    if(SpeedDirection_L==0)	//正转
    {
        if(10000 - FTM1_CNT < 5000)//防止bug
          Speed.L_5ms = 10000 - FTM1_CNT;
    }
    else                        //反转
    {
        if(FTM1_CNT < 5000)//防止bug
          Speed.L_5ms = 0 - FTM1_CNT;
    }
    //右轮测速
    if(SpeedDirection_R==0)	//正转
    {
        if(10001 - FTM2_CNT < 5000)//防止bug
          Speed.R_5ms = 0 - (10000-FTM2_CNT);
    }
    else                         //反转
    {
        if(FTM2_CNT < 5000)//防止bug
          Speed.R_5ms = FTM2_CNT;
    }
    #define ratio 1.953125//后来换了小的龙丘编码器，256线，原来用的500线
    Speed.L_5ms = (int)(Speed.L_5ms*ratio);
    Speed.R_5ms = (int)(Speed.R_5ms*ratio);
    //clear
    FTM1_CNT = 0;
    FTM2_CNT = 0;
}


/*************************************************************************
*  函数名称：Measure_Acc
*  功能说明：测量加速度计值
*  参数说明：无
*  函数返回：无（但包含全局变量a_sin和a_cos）
*  修改时间：2012-2-14    已测试
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
    
    //低通滤波
    Angle.a_sin = Angle.a_sin*0.5 + a_sin_new*0.5;//（90至-90）sin值 1到0到-1变化,左为正
    Angle.a_cos = Angle.a_cos*0.5 + a_cos_new*0.5;//（90至-90) cos值 0到-1到0变化,上为负
}



/*************************************************************************
*  函数名称：Angle_control
*  功能说明：角度融合，计算出角度，计算角度pwm输出
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/
#define Gyro_OFFSET (-4)
void Angle_control()
{
    //直立
    #define k_Gyro 0.07   //角速度放大倍数
    #define dt 0.005
    #define tg 2         //**跟踪时间:1~4
    static float mG_delta=0;      //和angle_speed一个级别
    static float Angle_Gyro_old=0;
    
    //用哪个三角函数决定于怎么安装，实测竖着安装用asin好
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
   
    
    //得到Angle.G_angle
    Angle_Gyro_old = Angle.Gyro;
    Angle.Gyro = (float)(Get_Gyro(1,'X') - Gyro_OFFSET);
    Angle.speed = 0 - k_Gyro *(Angle_Gyro_old + Angle.Gyro)/2.0;
    mG_delta = (Angle.m_angle - Angle.G_angle) / tg;
    Angle.G_angle += (Angle.speed + mG_delta) * dt;
        
    //得到Angle.PWM
    if(Ren.flag == 0)//正常情况下
    {
        Angle.PWM = (Angle.OFFSET - Angle.G_angle)*Angle.P
                      - Angle.speed * Angle.D;
    }
    else//有人字情况
    {
        Angle.PWM = (Angle.OFFSET - Angle.G_angle)*(Angle.P +0)
                      - Angle.speed * (Angle.D + 0);
    }
}




/*************************************************************************
*  函数名称：Speed_control
*  功能说明：计算速度pwm输出
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/
void Speed_control()
{
    static unsigned char speed_Period=0;//速度控制周期变量
    #define speed_Period_Constant 20 //速度控制周期
    static float speed_Delta=0;
    static float Tmp_Speed_P;
    static int temp_L_100ms=0,temp_R_100ms=0;
    
    speed_Period++;
    temp_L_100ms += Speed.L_5ms;
    temp_R_100ms += Speed.R_5ms;
    if(speed_Period >= 20)//速度PID反馈调试。100ms一次计算
    {
        speed_Period = 0;
        Speed.L_100ms = temp_L_100ms;
        Speed.R_100ms = temp_R_100ms;
        Speed.Car = (float)((Speed.L_100ms + Speed.R_100ms)/2.0);
        temp_L_100ms = 0;
        temp_R_100ms = 0;
        
        //速度控制
        speed_Delta = Speed.Goal - Speed.Car;
        
        //IIIIIIIIIIIIIIIIIIIII积分IIIIIIIIIIIIIIIIIII
        #define SPEEDUP_TIME 1500
        if(Time_1ms < Stand_Time + SPEEDUP_TIME)//站立之后的两秒之内：使劲跟随
        {
            if(Speed.Mode==3)
                Speed.PWM_Integral = 1000 + 3000*(Stand_Time + SPEEDUP_TIME - Time_1ms)/SPEEDUP_TIME;
            if(Speed.Mode==4)
                Speed.PWM_Integral = 0 + 3500*(Stand_Time + SPEEDUP_TIME - Time_1ms)/SPEEDUP_TIME;
            else
                Speed.PWM_Integral = 1000 + 3000*(Stand_Time + SPEEDUP_TIME - Time_1ms)/SPEEDUP_TIME;
        }
        else//站立之后的两秒之后
        {
            Speed.PWM_Integral += speed_Delta * Speed.I;
            //PWM_Integral限幅
            if(Speed.PWM_Integral > Speed.I_Limit_PWM_max)//限幅啊
                Speed.PWM_Integral = Speed.I_Limit_PWM_max;
            else if(Speed.PWM_Integral <= Speed.I_Limit_PWM_min)
                Speed.PWM_Integral = Speed.I_Limit_PWM_min;
        }
        
        //PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
        //并不是普通限幅，用于还没快的时候
        if(speed_Delta> 0 - Speed.I_Error_Start && speed_Delta < Speed.I_Error_Start)
            Tmp_Speed_P = Speed.P * speed_Delta;
        else if(speed_Delta< 0 - Speed.I_Error_Start)
            Tmp_Speed_P = Speed.P * (0 - Speed.I_Error_Start);
        else if(speed_Delta > Speed.I_Error_Start)
            Tmp_Speed_P = Speed.P * Speed.I_Error_Start;
        
        //输出
        Speed.PWM_Per = ( Tmp_Speed_P
                         + Speed.PWM_Integral
                             - Speed.PWM)  /  speed_Period_Constant;
    }
    Speed.PWM += Speed.PWM_Per;
}




/*************************************************************************
*  函数名称：Direction_control和Direction_control_with_Ren
*  功能说明：计算方向pwm输出（包含和不包含人字）
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/
#define Dir_Gyro_OFFSET 10
void Direction_control()
{
    Direction.Gyro = (float)(Get_Gyro(1,'Y') - Dir_Gyro_OFFSET); //向右为负
    if(Block.flag==0)//有黑砖头障碍情况
    {
        Direction.PWM_Per = Direction.P * (black_centre - CENTER )	//输出
            + Direction.D * Direction.Gyro
                - Direction.PWM;
    }
    else//没有黑砖头障碍情况
    {
        if(Time_1ms < Block.time + Block.delaytime)
            Direction.PWM_Per = Direction.P * (black_centre + Block.Offset - CENTER )	//输出
                         + Direction.D * Direction.Gyro
                           - Direction.PWM;
        else
            Block.flag = 0;
    }
    Direction.PWM += Direction.PWM_Per;
}

void Direction_control_with_Ren()//???人字时候是否需要方向的D值？
{
    if(Time_1ms > Ren.record_time + Ren.Delaytime1)//看见了但是延时打角
    {
        Direction.Gyro = (float)(Get_Gyro(1,'Y') - Dir_Gyro_OFFSET); //向右为负
        if(Ren.Loaction > CENTER)//右拐
        {
            black_centre = 160 + Ren.Strength;
        }
        else//左拐
        {
            if(Speed.Mode==3)//摄像头歪了，3档位打左拐补丁
            {
                if(Multiple_line_enable==1)
                    black_centre = 160 - Ren.Strength - 27;
                else
                    black_centre = 160 - Ren.Strength - 22;
            }
            else if(Speed.Mode==4 || Speed.Mode==5)//摄像头歪了，4,5档位打左拐补丁
            {
                if(Multiple_line_enable==1)
                    black_centre = 160 - Ren.Strength - 33;
                else
                    black_centre = 160 - Ren.Strength - 30;
            }
            else//摄像头歪了，其它档位左拐和右拐正常
            {
                black_centre = 160 - Ren.Strength;
            }
        }
        
        //时间计数
        if(Time_1ms > Ren.record_time + Ren.Delaytime1 + Ren.Delaytime2)
        {
            Ren.flag = 0;
        }
        
        //输出
        Direction.PWM_Per=(Direction.P * (black_centre - CENTER)	//输出
                           + Direction.D * Direction.Gyro
                               - Direction.PWM);
        Direction.PWM += Direction.PWM_Per;
    }
}



/*************************************************************************
*  函数名称：Motor_Control
*  功能说明：pwm输出
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/

void Motor_Control()
{	
    static float pwm_Dead_L = 100;
    static float pwm_Dead_R = 100;
    static float all_PWM_L = 0;
    static float all_PWM_R = 0;
    
    //电机pwm输出    //300  400  500  600  700  800  900  1000 1100
    //测得的速度     //1130 2000 2750 3600 4350 5150 5870 6650 7450
    
    
    //计算总的输出
    if(Slope_flag == 0)//无坡道
    {
        all_PWM_L = Angle.PWM - Speed.PWM - Direction.PWM;
        all_PWM_R = Angle.PWM - Speed.PWM + Direction.PWM;
    }
    else//有坡道
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
    
    
    //倒地保护和终点线停车
    if(Angle.G_angle < -25 ||  Angle.G_angle > 40 || StartLine.flag==1)
    {
        if(Time_1ms > StartLine.time_record + StartLine.Delaytime)
        {
            all_PWM_L = 0;
            all_PWM_R = 0;
        }
    }
    
    //空转测速和磨轮胎
    //all_PWM_L = all_PWM_R=1000;
    
    
    //防止跳轮左右限幅:低速不用(国赛再调)
    //结果国赛也没调。。。慎用。。。
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
    
    
    //1.左面控制PWM
    if(all_PWM_L >= 0)
    {
        all_PWM_L += pwm_Dead_L;//加死区
        if(all_PWM_L >= 3990)   //限幅
            all_PWM_L = 3990;
        FTM_PWM_Duty(FTM0, MOTOR3_PWM , ((unsigned int)(all_PWM_L)) );//输出
        DIR_L_Forward;
    }
    else
    {
        all_PWM_L -= pwm_Dead_L;//加死区
        if(all_PWM_L <= -3990)  //限幅
            all_PWM_L = -3990;
        FTM_PWM_Duty(FTM0, MOTOR3_PWM , (unsigned int)(4000u + all_PWM_L));//输出
        DIR_L_Backward;
    }
    //2.右面控制PWM					
    if(all_PWM_R >= 0)
    {
        all_PWM_R += pwm_Dead_R;//加死区
        if(all_PWM_R >= 3990)   //限幅
            all_PWM_R = 3990;
        FTM_PWM_Duty(FTM0, MOTOR1_PWM ,  ((unsigned int)(all_PWM_R)));//输出
        DIR_R_Forward;
    }
    else
    {
        all_PWM_R -= pwm_Dead_R;//加死区
        if(all_PWM_R <= -3990)  //限幅
            all_PWM_R = -3990;
        FTM_PWM_Duty(FTM0, MOTOR1_PWM , (unsigned int)(4000 +  all_PWM_R)  );//输出
        DIR_R_Backward;
    }
}


