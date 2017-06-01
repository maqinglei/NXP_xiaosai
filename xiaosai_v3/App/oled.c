#include "include.h"
#include "stdlib.h"
#include "oledfont.h"  	 
//#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//imodule	
//////////////////////////////////////////////////////////////////////////////////	

//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
unsigned short     int OLED_GRAM[132][8];	 

//�����Դ浽LCD		 
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<131;n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}

//��SSD1306д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_RS_Set();
	else 
	  OLED_RS_Clr();		  

	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  

	OLED_RS_Set();   	  
} 

	  	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)
          for(n=0;n<130;n++)
            OLED_GRAM[n][i]=0X00;  
	
}

//���һ��RAM  
void OLED_Clear_Line(u8 Line)  
{  
	u8 n;  
        for(n=0;n<130;n++)
          OLED_GRAM[n][Line]=0X00;  
	
}

//���� 
//x:0~127
//y:0~63
//t:1 ��� 0,���				   
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>131||y>63)return;//������Χ��.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}
//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,���;1,���	  
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	//OLED_Refresh_Gram();//������ʾ
}





//x1,y1,x2,y2 ��������
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,���;1,���	 
void OLED_Cube(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)
{
	u8 x,y; 
	
	for(y=y1;y<=y2;y++)
	{
		OLED_DrawPoint(x1,y,dot);
		OLED_DrawPoint(x2,y,dot);
	}
	
	for(x=x1+1;x<=x2-1;x++)
	{
		OLED_DrawPoint(x,y1,dot);
		OLED_DrawPoint(x,y2,dot);
	}
}

void OLED_SelBar(unsigned char col)
{
	switch (col)
		{
			case 0:				
				OLED_Cube(2,14,129,28,0);
				OLED_Cube(2,28,129,42,0);
				OLED_Cube(2,42,129,56,0);
				OLED_Cube(2,0,129,14,1);
				break;
			case 1:
				OLED_Cube(2,0,129,14,0);				
				OLED_Cube(2,28,129,42,0);
				OLED_Cube(2,42,129,56,0);
				OLED_Cube(2,14,129,28,1);
				break;
			case 2:
				OLED_Cube(2,0,129,14,0);
				OLED_Cube(2,14,129,28,0);				
				OLED_Cube(2,42,129,56,0);
				OLED_Cube(2,28,129,42,1);
				break;
			case 3:
				OLED_Cube(2,0,129,14,0);
				OLED_Cube(2,14,129,28,0);
				OLED_Cube(2,28,129,42,0);
				OLED_Cube(2,42,129,56,1);
				break;
			
			default:
				break;
		}
}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	chr=chr-' ';//�õ�ƫ�ƺ��ֵ				   
    for(t=0;t<size;t++)
    {   
		if(size==12)temp=oled_asc2_1206[chr][t];  //����1206����
		else temp=oled_asc2_1608[chr][t];		 //����1608���� 	                          
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}
//m^n����
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
	}
} 
//��ʾ�ַ���
//x,y:�������  
//*p:�ַ�����ʼ��ַ
//��16����
void OLED_ShowString(u8 x,u8 y,const u8 *p)
{
// #define MAX_CHAR_POSX 122
 #define MAX_CHAR_POSX 126
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*p,12,1);	 
        x+=8;
        p++;
    }  
}	   
//��ʼ��SSD1306					    
void OLED_Init(void)
{ 	
        unsigned int delay=0xfee;
        
        gpio_init(PTB8, GPO, 1);
        gpio_init(PTB9, GPO, 1);
        gpio_init(PTB10, GPO, 1);
        gpio_init(PTB11, GPO, 1);
  							  
	OLED_RST_Clr();
	for(; delay != 0; delay--);
        for(; delay != 0; delay--);
        for(; delay != 0; delay--);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD); //�ر���ʾ
	OLED_WR_Byte(0xD5,OLED_CMD); //����ʱ�ӷ�Ƶ����,��Ƶ��
	OLED_WR_Byte(80,OLED_CMD);   //[3:0],��Ƶ����;[7:4],��Ƶ��
	OLED_WR_Byte(0xA8,OLED_CMD); //��������·��
	OLED_WR_Byte(0X3F,OLED_CMD); //Ĭ��0X3F(1/64) 
	OLED_WR_Byte(0xD3,OLED_CMD); //������ʾƫ��
	OLED_WR_Byte(0X00,OLED_CMD); //Ĭ��Ϊ0

	OLED_WR_Byte(0x40,OLED_CMD); //������ʾ��ʼ�� [5:0],����.
													    
	OLED_WR_Byte(0x8D,OLED_CMD); //��ɱ�����
	OLED_WR_Byte(0x14,OLED_CMD); //bit2������/�ر�
	OLED_WR_Byte(0x20,OLED_CMD); //�����ڴ��ַģʽ
	OLED_WR_Byte(0x02,OLED_CMD); //[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	OLED_WR_Byte(0xA1,OLED_CMD); //���ض�������,bit0:0,0->0;1,0->127;
	OLED_WR_Byte(0xC0,OLED_CMD); //����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	OLED_WR_Byte(0xDA,OLED_CMD); //����COMӲ����������
	OLED_WR_Byte(0x12,OLED_CMD); //[5:4]����
		 
	OLED_WR_Byte(0x81,OLED_CMD); //�Աȶ�����
	OLED_WR_Byte(0xEF,OLED_CMD); //1~255;Ĭ��0X7F (��������,Խ��Խ��)
	OLED_WR_Byte(0xD9,OLED_CMD); //����Ԥ�������
	OLED_WR_Byte(0xf1,OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WR_Byte(0xDB,OLED_CMD); //����VCOMH ��ѹ����
	OLED_WR_Byte(0x30,OLED_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WR_Byte(0xA4,OLED_CMD); //ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	OLED_WR_Byte(0xA6,OLED_CMD); //������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ	    						   
	OLED_WR_Byte(0xAF,OLED_CMD); //������ʾ	 
	OLED_Clear();
}  


void LCD_Display(unsigned char x,unsigned char y,long int num)//��ʾ����
{
//	unsigned char disp[]={0,0,0,0,0,0,0,0,0};
	unsigned char disp[15];
	sprintf(disp,"%d",num);
	OLED_ShowString(x,y,&disp[0]);  
}
void LCD_Display_float(unsigned char x,unsigned char y,float num)
{
	unsigned char buffer[15];
	sprintf(buffer,"%.2f",num);
	OLED_ShowString(x,y,&buffer[0]);  	
}

void Display_CCD(void)
{
        int i;
        
        for(i=0;i<ccd_avg;i++)
        {
            if(Pixe1[i]>0x88)
            {
              OLED_DrawPoint(i,63,1);
              OLED_DrawPoint(i,62,1);
              OLED_DrawPoint(i,61,1);
            }
            else
            {
              OLED_DrawPoint(i,63,0);
              OLED_DrawPoint(i,62,0);
              OLED_DrawPoint(i,61,0);
            }
        }
        
        for(i=0;i<128;i++)
        {
            if(Pixe2[i]>0x88)
            {
              OLED_DrawPoint(i,58,1);
              OLED_DrawPoint(i,57,1);
              OLED_DrawPoint(i,56,1);
            }
            else
            {
              OLED_DrawPoint(i,58,0);
              OLED_DrawPoint(i,57,0);
              OLED_DrawPoint(i,56,0);
            }
        }
        OLED_Refresh_Gram();//������ʾ
}












