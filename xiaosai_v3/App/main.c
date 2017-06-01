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

float Ang_Set=82;//�Ƕȱ���
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
int CCD_Time=0;//ccd�ɼ�ʱ��������
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
/*!
 *  @brief      main����
 */   //�³�
void main()
{
    unsigned int i=0,en=0;//loop
    uint8 send_data_cnt=0;//ccd��λ�����ͼ��ʱ�����
    
    
//    //��ʼ��OLEDģ��
//    OLED_Init();    
//    OLED_Refresh_Gram();//������ʾ
    
    //��ʼ�����ٶȼƺ�������
//    Init_L3G4200D();    
//    MMA845x_init();
//
//    //��ʼ������CCD
//    //CCD_init1() ;   
//    CCD_init2() ;   
//    CCD_init3() ;   

    //��ʼ����·pwmȥ���
    FTM_PWM_init(FTM0, FTM_CH0, 8000, 0);                  
    FTM_PWM_init(FTM0, FTM_CH1, 8000, 0);
    FTM_PWM_init(FTM0, FTM_CH2, 8000, 0);
    FTM_PWM_init(FTM0, FTM_CH3, 8000, 0);
    
    //GPIO�ǵĳ�ʼ��
    gpio_init  (PTC10, GPI, 0);//��ʼ�� PTB10(��һ·���ٷ���λ)
    gpio_init  (PTC11, GPI, 0);//��ʼ�� PTB11(�ڶ�·���ٷ���λ)
    gpio_init  (MOTOR1_IO,GPO,LOW);
    gpio_init  (MOTOR3_IO,GPO,LOW);//���ʹ��
    
    //gpio_init  (PTC5, GPI, 0);//��ʼ��
    
    port_init(PTC5, ALT1 | IRQ_FALLING);          
    set_vector_handler(PORTC_VECTORn ,PORTC_IRQHandler);    
    enable_irq (PORTC_IRQn);                                
   
    gpio_init  (PTC6, GPI, 0);//��ʼ��
    gpio_init  (PTC0 , GPO, 0);//��ʼ��������
//    gpio_init  (PTD12, GPI, 0);//��ʼ�� �������� ��ʱʹ�ð����ӿ�
//    gpio_init  (PTD13, GPI, 0);//��ʼ�� �������� ��ʱʹ�ð����ӿ�                             
    
//    gpio_init  (PTB4, GPI, 0);//��ʼ�� ����
//    gpio_init  (PTB5, GPI, 0);//��ʼ�� 
    
    //��ʼ�����벶׽�ж���
    FTM_Input_init(FTM1, FTM_CH0, FTM_Falling,FTM_PS_1);              //��ʼ��FTM���벶׽ģʽ�����ڵ�һ·���٣�
    port_init_NoALT(FTM1_CH0 ,PULLUP);

    set_vector_handler(FTM1_VECTORn ,FTM1_INPUT_IRQHandler);//����FTM1���жϷ�����Ϊ FTM1_INPUT_IRQHandler
    enable_irq (FTM1_IRQn);

    FTM_Input_init(FTM2, FTM_CH0, FTM_Falling,FTM_PS_1);              //��ʼ��FTM���벶׽ģʽ�����ڵڶ�·���٣�
    port_init_NoALT(FTM2_CH0 ,PULLUP);

    set_vector_handler(FTM2_VECTORn ,FTM2_INPUT_IRQHandler);//����FTM2���жϷ�����Ϊ FTM1_INPUT_IRQHandler
    enable_irq (FTM2_IRQn);  
    
    //��ʼ��6������
//    key_init(KEY_U);
//    key_init(KEY_D);
//    key_init(KEY_L);
//    key_init(KEY_R);
//    key_init(KEY_A);
//    key_init(KEY_B);
    
    //�趨��ʱ��0 1ms�ж�
    pit_init_ms(PIT0, 1);                                //��ʼ��PIT0����ʱʱ��Ϊ�� 1ms
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϷ�����Ϊ PIT0_IRQHandler
    enable_irq (PIT0_IRQn);
    
    //zheng
    /*
    //��ʼ��flash
    flash_init();
    //�������һ������������4k
    flash_erase_sector(FLASH_SECTOR_NUM-1);
    //д�����ݵ�������ƫ�Ƶ�ַΪ0������һ��д��4�ֽ�
    if( 1 == flash_write(FLASH_SECTOR_NUM-1, 0, 123456) )   
    {
        data32 =    flash_read(FLASH_SECTOR_NUM-1, 0, uint32);  //��ȡ4�ֽ�
    }
    */

    while(1)
    {      
      //gpio_set   (PTC0,   1); 
        en++;
        yanshi++;
        if(dengta_yanshi<=10 && dengta1==1)
        {
          dengta1=0;
          dengta_num1++;
          if(dengta<=3) dengta_num++;
          dengta=0;
          if(dengta_num1>=3 )
          {
            if(dengta_num>=3 ) qipao=1;
            else qipao=0;
            dengta_num1=0;
            dengta_num=0;            
          }
        }
        
        if(dengta_yanshi>=5000 && dengta1==1)
        {
          dengta_yanshi=5100;
          dengta1=0;
          dengta_num1++;
          if(dengta<=3) dengta_num++;
          dengta=0;
          if(dengta_num1>=3 )
          {
            if(dengta_num>=2 ) 
            {
              dengta_end_wu=1;
              //dengta_end_you=0;
            }else 
            {
              dengta_end_you++;
              dengta_end_wu=0;
            }
            dengta_num1=0;
            dengta_num=0;            
          }
        }
        if(heheda==0 && dengta_end_you>=2 && dengta_end_wu==1) pao_end=1;
        
       // gpio_set   (PTC0,   1); 
        if(test == 1)
        {
            if(yanshi > 300)//�滻�˴�����Ϊ���ܼ�⼴��
            {
              qipaoyanshi++;
              
              if(qipaoyanshi>=3000) qipaoyanshi=3100;
              
               if(Speed_Set<=40)
               {
                 Speed_Set+=20;
               }
               
               if(Speed_Set<=47 && Speed_Set>40)
               {
                 Speed_Set+=1;
               }
               
               if(Ang_Set>37)
               {
                 Ang_Set=37;
               }
               
               if(dang == 1)
               {
                   if(Sudu_P<30.0)
                   {
                      Sudu_P+=10.0;
             
                      Sudu_I=1.3;
                   }
               }
               else
               {
                    if(Sudu_P<30.0)
                   {
                      Sudu_P+=10.0;
             
                      Sudu_I=1.3;
                   }
               }

            }
            else
            {
              Ang_Cha=0;
            }
        }
        else
        {
            if(qipao==1 && en>100)//�滻�˴�����Ϊ���ܼ�⼴��
            {
                            qipaoyanshi++;
              
              if(qipaoyanshi>=3000) qipaoyanshi=3100;
              
               if(Speed_Set<=40)
               {
                 Speed_Set+=20;
               }
               
               if(Speed_Set<=47 && Speed_Set>40)
               {
                 Speed_Set+=1;
               }
               
               if(Ang_Set>37)
               {
                 Ang_Set=37;
               }
               
               if(dang == 1)
               {
                   if(Sudu_P<30.0)
                   {
                      Sudu_P+=10.0;
             
                      Sudu_I=1.3;
                   }
               }
               else
               {
                    if(Sudu_P<30.0)
                   {
                      Sudu_P+=10.0;
             
                      Sudu_I=1.3;
                   }
               }

            }
            else
            {
              Ang_Cha=0;
            }
        }

        
                  //���̵���һЩ��Ҫ�Ĳ���
          //        if(key_check(KEY_U) == KEY_DOWN) Ang_Set+=1;
          //        else if(key_check(KEY_D) == KEY_DOWN)Ang_Set-=1;
          //        
          //        if(key_check(KEY_L) == KEY_DOWN) Parameter2++;
          //        else if(key_check(KEY_R) == KEY_DOWN)Parameter2--;
          //        
          //        if(key_check(KEY_A) == KEY_DOWN)Parameter3++;
          //        else if(key_check(KEY_B) == KEY_DOWN)Parameter3--;                                    
          //  
        OLED_Clear();//���RAM
        if(gpio_get(PTB4))
        {      
            if(key_check(KEY_D) == KEY_DOWN) Parameter2++;
            else if(key_check(KEY_U) == KEY_DOWN)Parameter4++;         
        }
        else
        {
          OLED_ShowString(64,0,"Change");
          if(key_check(KEY_D) == KEY_DOWN) Parameter3+=1;
          else if(key_check(KEY_U) == KEY_DOWN)Parameter3-=1;         
        }
        
        if(key_check(KEY_L) == KEY_DOWN) Parameter1++;
        
        if(Parameter1 >= 15)
        {
          Parameter1 = 0;
        }
        
        if(Parameter4>=15)
        {
          Parameter4=0;
        }
         
         if(Parameter2>=0 && Parameter2<5)
         {
           OLED_ShowString(4,0,"hh");
           gear=1;
         }
         else if(Parameter2>=5 && Parameter2<10)
         {
           OLED_ShowString(4,0,"Standard");
           gear=1;
         }
         else if(Parameter2>=10 && Parameter2<15)
         {
           OLED_ShowString(4,0,"Turtle");
           gear=2;
         }

         
         if(Parameter2 >= 15)
         {
           Parameter2=0;
         }
         if(Parameter2 <0)
         {
           Parameter2=15;
         }

         if(gpio_get(PTB5))
         {
           OLED_ShowString(4,42,"final");
           dang=1;
           test=0;
         }
         else
         {
           OLED_ShowString(4,42,"test");
           dang=1;
           test=1;
         }
          //OLED��ʾ3������
         
         if(qipao == 1)
         {
           OLED_ShowString(4,14,"Set Off!!!");
         }
         else
         {
           OLED_ShowString(4,14,"Waiting...");
         }
         OLED_ShowString(4,28,"Angel:");
          //LCD_Display(3,0,GYRO_Y);
          //LCD_Display(63,28,gpio_get(PTD11));
          //LCD_Display(33,14,gpio_get(PTC5));
          LCD_Display(53,28,zhangaijifen);//Ang_IGyro
          LCD_Display(93,28,Parameter3);
          //LCD_Display(3,42,zhijiao);

          
          //serial scoper��λ���������
          
           
          //CCD��λ���������
          send_data_cnt++;
          if(send_data_cnt >= 1) 
          {
            //SendImageData(Pixe2);  //�������ݵ���λ��
            send_data_cnt = 0;
          }
          if(send_data_cnt >= 4) 
          {
            //SendImageData(Pixe2);  //�������ݵ���λ��
            send_data_cnt = 0;
          }
          
          //��ʾ��ccd
          if(Parameter1>=5 && Parameter1<10)
          {
              for(i=0; i<128; i++)
              {
                OLED_DrawPoint(i,64-Pixe3[i]/4,1);
              }

              for(i=0; i<128; i++)
              {
                OLED_DrawPoint(i,25,1);
              }
              
              for(i=0; i<128; i++)
              {
                OLED_DrawPoint(i,37,1);
              }
          }
          else if(Parameter1>=10 && Parameter1<15)
          {
              LCD_Display(53,42,gpio_get(PTD12));
              
          }
          
          if(Parameter4 > 5 && Parameter4<10)
          {
            OLED_ShowString(53,42,"Shut_All");
            heheda=1;
            yanshiqipao=0;
          }
          else if(Parameter4>10)
          {
            heheda=0;            
            yanshiqipao=0;
          }
          else
          { 
            yanshiqipao=1;
          }
          
    //        //��ʾ��ccd
    //        for(i=0; i<64; i++)
    //        {
    //          OLED_DrawPoint(Pixe2[i]/2,i,1);
    //        }

          OLED_Refresh_Gram();//������ʾ
          OutPut_Data();
    }
}



