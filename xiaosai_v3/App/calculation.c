#include "common.h"
#include "include.h"
#include "calculation.h"

/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�CCD_init
*  ����˵����CCD��ʼ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void CCD_init1(void)
{
  gpio_init (PTA9 ,GPO,1);
  gpio_init (PTA11 ,GPO,1);
  adc_init(ADC0_SE10) ; 
}
void CCD_init2(void)
{
  gpio_init (PTB1, GPO,1);
  gpio_init (PTA29, GPO,1);
  adc_init(ADC1_SE17) ;
}
void CCD_init3(void)
{
  gpio_init (PTB2, GPO,1);
  gpio_init (PTB3, GPO,1);
  adc_init(ADC1_SE8) ;    //B0
}
/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�StartIntegration
*  ����˵����CCD��������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void StartIntegration1(void) {

    unsigned char i;

    SI_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal();            /* SI  = 0 */
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */
}

void StartIntegration2(void) {

    unsigned char i;

    SI_SetVa2();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVa2();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVa2();            /* SI  = 0 */
    SamplingDelay();
    CLK_ClrVa2();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVa2();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK_ClrVa2();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVa2();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVa2();           /* CLK = 0 */
}

void StartIntegration3(void) {

    unsigned char i;

    SI_SetVa3();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVa3();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVa3();            /* SI  = 0 */
    SamplingDelay();
    CLK_ClrVa3();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVa3();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK_ClrVa3();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVa3();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVa3();           /* CLK = 0 */
}

/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�ImageCapture
*  ����˵����CCD��������
*  ����˵����* ImageData   ��������
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*ImageData =  ad_once(ADC1, AD6a, ADC_8bit);
*************************************************************************/

void ImageCapture1(uint8 * ImageData) {

    unsigned int i;
    extern uint8 AtemP ;

    SI_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i < 300; i++) {                    //����250����CCD��ͼ����ȥ�Ƚ�ƽ����
      SamplingDelay() ;  //200ns                  //�Ѹ�ֵ�Ĵ���߸�С�ﵽ�Լ�����Ľ����
    }

    //Sampling Pixe1 1
    *ImageData =  adc_once (ADC0_SE10 , ADC_8bit);
    ImageData ++ ;
    CLK_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixe1 2~128

        *ImageData =  adc_once(ADC0_SE10, ADC_8bit);
        ImageData ++ ;
        CLK_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */
}

void ImageCapture2(uint8 * ImageData) {

    unsigned int i;
    extern uint8 AtemP ;

    SI_SetVa2();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVa2();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVa2();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i < 300; i++) {                    //����250����CCD��ͼ����ȥ�Ƚ�ƽ����
      SamplingDelay() ;  //200ns                  //�Ѹ�ֵ�Ĵ���߸�С�ﵽ�Լ�����Ľ����
    }

    //Sampling Pixe1 1
    *ImageData =  adc_once (ADC1_SE17, ADC_8bit);
    ImageData ++ ;
    CLK_ClrVa2();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVa2();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixe1 2~128

        *ImageData =  adc_once (ADC1_SE17, ADC_8bit);
        ImageData ++ ;
        CLK_ClrVa2();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVa2();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVa2();           /* CLK = 0 */
}

void ImageCapture3(uint8 * ImageData) {

    unsigned int i;
    extern uint8 AtemP ;

    SI_SetVa3();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVa3();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVa3();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i < 300; i++) {                    //����250����CCD��ͼ����ȥ�Ƚ�ƽ����
      SamplingDelay() ;  //200ns                  //�Ѹ�ֵ�Ĵ���߸�С�ﵽ�Լ�����Ľ����
    }

    //Sampling Pixe1 1
    *ImageData =  adc_once (ADC1_SE8, ADC_8bit);
    ImageData ++ ;
    CLK_ClrVa3();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVa3();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixe1 2~128

        *ImageData =  adc_once (ADC1_SE8, ADC_8bit);
        ImageData ++ ;
        CLK_ClrVa3();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVa3();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVa3();           /* CLK = 0 */
}

/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�CalculateIntegrationTime
*  ����˵���������ع�ʱ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/

/* �ع�ʱ�䣬��λms */
uint8 IntegrationTime = 10;
void CalculateIntegrationTime(void) {
extern uint8 Pixe1[128];
/* 128�����ص��ƽ��ADֵ */
uint8 PixelAverageValue;
/* 128�����ص��ƽ����ѹֵ��10�� */
uint8 PixelAverageVoltage;
/* �趨Ŀ��ƽ����ѹֵ��ʵ�ʵ�ѹ��10�� */
int16 TargetPixelAverageVoltage = 25;
/* �趨Ŀ��ƽ����ѹֵ��ʵ��ֵ��ƫ�ʵ�ʵ�ѹ��10�� */
int16 PixelAverageVoltageError = 0;
/* �趨Ŀ��ƽ����ѹֵ�����ƫ�ʵ�ʵ�ѹ��10�� */
int16 TargetPixelAverageVoltageAllowError = 2;

    /* ����128�����ص��ƽ��ADֵ */
    PixelAverageValue = PixelAverage(128,Pixe1);
    /* ����128�����ص��ƽ����ѹֵ,ʵ��ֵ��10�� */
    PixelAverageVoltage = (unsigned char)((int)PixelAverageValue * 25 / 194);

    PixelAverageVoltageError = TargetPixelAverageVoltage - PixelAverageVoltage;
    if(PixelAverageVoltageError < -TargetPixelAverageVoltageAllowError)
    {
      PixelAverageVoltageError = 0- PixelAverageVoltageError ;
      PixelAverageVoltageError /= 2;
      if(PixelAverageVoltageError > 5 )
         PixelAverageVoltageError = 5 ;     //ÿ�α仯�ع�ʱ��
      IntegrationTime -= PixelAverageVoltageError;
    }
    if(PixelAverageVoltageError > TargetPixelAverageVoltageAllowError)
    { 
      PixelAverageVoltageError /= 2;
      if(PixelAverageVoltageError > 5 )
         PixelAverageVoltageError = 5 ;     //ÿ�α仯�ع�ʱ��
      IntegrationTime += PixelAverageVoltageError;
    }

    if(IntegrationTime <= 1)
        IntegrationTime = 1;
    if(IntegrationTime >= 100)
        IntegrationTime = 100;
}


/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�PixelAverage
*  ����˵����������ľ�ֵ����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
uint8 PixelAverage(uint8 len, uint8 *data) {
  unsigned char i;
  unsigned int sum = 0;
  for(i = 0; i<len; i++) {
    sum = sum + *data++;
  }
  return ((unsigned char)(sum/len));
}
/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�SendHex
*  ����˵�����ɼ���������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void SendHex(unsigned char hex) {
  unsigned char temp;
  temp = hex >> 4;
  if(temp < 10) {
    uart_putchar(UART3,temp + '0');
  } else {
    uart_putchar(UART3,temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if(temp < 10) {
    uart_putchar(UART3,temp + '0');
  } else {
   uart_putchar(UART3,temp - 10 + 'A');
  }
}
/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�SendImageData
*  ����˵����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void SendImageData(unsigned char * ImageData) {

    unsigned char i;
    unsigned char crc = 0;

    /* Send Data */
    uart_putchar(UART3,'*');
    uart_putchar(UART3,'L');
    uart_putchar(UART3,'D');

    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);

    for(i=0; i<128; i++) {
      SendHex(*ImageData++);
    }

    SendHex(crc);
    uart_putchar(UART3,'#');
}
/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�SamplingDelay
*  ����˵����CCD��ʱ���� 200ns
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
 void SamplingDelay(void){
  /* volatile uint8 i ;
   for(i=0;i<2;i++) {
    asm("nop");
    asm("nop");
    asm("nop");
   }*/
   systick_delay_ns(200);
   
   
   
}

