#include "common.h"
#include "include.h"



uint8 Pixe3[128];

int zhijiao=0;              
int Into_zhijiao_right=0;
int Into_zhijiao_left=0;
int zhijiaoqian=0;
//int guanbizhijiao=0;
int d=0;
int shutdown_zhijiao=0;
int shutdown_zhijiao2=0;
int zhijiao_bai=0;

int danxian_check_sum=0;
int danxian=0;
int danxian_zhi=0;         //���ε��ߵ�ֵ
int danxian_zhi2[2]={'0'};        //�ϴε��ߵ�ֵ

int danxian_ccd2=0;        //CCD2�������ߵ�ֵ
int danxian_get=0;         //CCD2�Ƿ��⵽���߱�־λ
int danxian_get1=0;    
/******************** ֱ��     ***************************/

int zhijiao_allow = 1;    //������⣬������
int zhijiao_hei=0;
int zhijiao_line_left=0;
int zhijiao_line_right=0;
int zhijiao_turning=0;
int zhijiao_CCD3_chu=0;
int zhijiao_chu=0;
int zhijiao_chu_time=0;
extern int zhijiao_hei_time;
int targe_error3=15; 
int zhijiao_chu_shu=0;
int zhijiao_turning_time=2;
int zhijiao_heheda=0;
int zhijiao_hei_error=25;
int po=0;

/**********************��ֵ��*****************************/
int targe_error2=15; 
int16 targe_error=40;                    //�½��ط�ֵ
int danxian_error=35;                    //�����½��ط�ֵ
int32 ccd_sum=0,ccd_avg=0;               //CCD��ֵ�ĺ͡�ƽ��ֵ
uint8 ccd_max=0,ccd_min=0;               //CCD���ֵ����Сֵ
int16 ccd_target;                        //�ϴ����Һ��ߵ��м�ֵ�����е�
int16 ccd_target1; 
int Ccd_getline_flag=0;
int Turning1=0;
uint8 B_flog=0,H_flog=0;                 //ȫ�ױ�־λ����ʮ��
int16 line_right[3]={90};                //�Һ���λ�ô�����飬���3�ε�
int16 line_left[3]={30};                //�����λ�ô�����飬���3�ε�
int line_right1=90;                    //����һ�ε��Һ���λ��
int line_left1=30;                    //����һ�ε��Һ���λ��
int line_right2=90;                    //����һ�ε��Һ���λ��
int line_left2=30;                    //����һ�ε��Һ���λ��


/*********************    �ϰ�    **********************/
int zhangai_hei=0;
int zhangai_hei_zuo=0;
int zhangai_hei_you=0;
int zhangai_time=0;
int zhangai_time1=7;
int B_flog_wangxing=0;

int Coner=1;
/*********************    ccd2    **********************/


void ccd_deal(uint8 ch[])      //������ch����ccd��ƽ��ֵ�����ֵ����Сֵ
{
//  uint8 i;
//  int8 max=1,min=1;
//  for(i=5;i<123;i++)
//  {
//    if(ch[max]<ch[i]) max=i;
//    if(ch[min]>ch[i]) min=i;
//    ccd_sum+=ch[i];
//  }
//  ccd_max=max;
//  ccd_min=min;
//  ccd_avg=ccd_sum/118;
//  ccd_sum=0;//����û����ƽ��ֵ����𡣡���
}

void ccd3_work()
{
//  int i=0;
//
///*****************   ������    ****************************/
//  
//  Coner=1;
//  for(i=30;i<90;i++)
//  {
//    if(Pixe3[i]-Pixe3[i+4]>targe_error3) 
//    {
//      Coner=0;
//      
//      break;
//    }
  }
  
/*****************    ��ֱ�Ǽ��     *************************/
  zhijiao_CCD3_chu=0;
  if(zhijiao_line_right==1 || zhijiao_line_left==1)  
  {
    zhijiao_CCD3_chu=1;
    for(i=10;i<65;i++)
    {
      if(Pixe3[i]-Pixe3[i+4]>targe_error3) 
      {
        zhijiao_CCD3_chu=0;
        break;
      }
    }
  }
  
}
void ccd2_work()
{
//  uint8 i=0;
//
////  int16 error;                                      //error=Pixe2[i]-Pixe2[i-4]�������ж��Ƿ���ڷ�ֵ
//  //uint8 no_left_line=0,no_right_line=0;             //�Ƿ�Ѱ�������ߵı�־λ
////  if(danxian==1)        //���뵥�ߣ�CCD2��ʼ�ѵ���
////  {
////    danxian_get=0;      //��־λ��0
////    for(i=10; i<=117; i++)
////    {
////      if(Pixe2[i-5]-Pixe2[i]>targe_error2 && Pixe2[i+5]-Pixe2[i]>targe_error2)
////      {//CCD2��ⵥ��
////        danxian_ccd2=i;  //�������ڵĵ�
////        danxian_get=1;   //��⵽���߱�־λ
////        break;
////        
////      }
////    }
///*******************************************************************
//    
//    ��������CCD2�����Һ���
//    
//********************************************************************/    
//  
//   // if(danxian_ccd2<1) danxian_ccd2=1;       //����м�ֵС��1����Ĭ��Ϊ0
//   // if(danxian_ccd2>126) danxian_ccd2=126;   //����м�ֵ����126����Ĭ��Ϊ126
//   //����Ϊ���ߵ�����ֵ
//
////    if(danxian_get==0)
////    {
////      danxian=0;
////      danxian_ccd2=0;
////      zhijiao_allow = 1;
////      zhijiao_hei=0;
////    }      
////  }
}

void ccd_getline()                                 //��CCD�����Һ���
{
//  uint8 i=0;
//  int16 error;                                      //error=Pixe2[i]-Pixe2[i-4]�������ж��Ƿ���ڷ�ֵ
//  uint8 no_left_line=0,no_right_line=0;             //�Ƿ�Ѱ�������ߵı�־λ
//  ccd_deal(Pixe2);                                  //������Pixe1����ccd1��ƽ��ֵ�����ֵ����Сֵ
//  
//  Ccd_getline_flag=0;
//  if(danxian==0)            //�ж��뵥�ߵ��㷨
//  {
//    for(i=20; i<=107; i++)  
//    {
//      if(Pixe2[i-4]-Pixe2[i]>danxian_error && Pixe2[i+4]-Pixe2[i]>danxian_error)
//      {   //��i�������Ҹ�6�������½��أ��жϵ���
//        if((i-line_left[0]>5)&&(line_right[0]-i>5))
//        {   //�жϵ����Ƿ�������˫�ߵ��м�
//          danxian=1;       //�뵥�߱�־λ
//          danxian_zhi=i;   //��ʼ�����μ��ϴεĵ���ֵ
//          danxian_zhi2[1]=danxian_zhi;
//          danxian_zhi2[0]=danxian_zhi;
//          danxian_get1=1;
//          zhijiao_allow = 0;    
//          zhijiao_hei=0;
//          Ccd_getline_flag=1;
//          break;
//        }
//      }
//    }
//  }else 
//  {
//    zhijiao_allow = 0;
//    danxian_get1=0;
//    for(i=20; i<=106; i++)
//    {
//
//      if(Pixe2[i-3]-Pixe2[i]>targe_error && Pixe2[i+3]-Pixe2[i]>targe_error)
//      {//��i�������Ҹ�6�������½��أ��жϵ���
//        danxian_zhi=i;
//        danxian=1;
//        
//        if(danxian_zhi>=danxian_zhi2[0])
//        {
//          if(danxian_zhi-danxian_zhi2[0]<10)
//          {//���ε����Ƿ����ϴε��ߵ�����15����֮��
//            danxian_zhi2[1]=danxian_zhi2[0];
//            danxian_zhi2[0]=danxian_zhi;
//            danxian_get1=1;
//            Ccd_getline_flag=1;
//            break;
//          }
//        }else if(danxian_zhi<danxian_zhi2[0])
//        {
//          if(danxian_zhi2[0]-danxian_zhi<10)
//          {
//            danxian_zhi2[1]=danxian_zhi2[0];
//            danxian_zhi2[0]=danxian_zhi;
//            danxian_get1=1;
//            Ccd_getline_flag=1;
//            break;
//          }
//        } 
//      }
//    }
//    if(danxian_get1==0) 
//    {
//      danxian_zhi2[1]=danxian_zhi2[0];
//      danxian_zhi2[0]=danxian_zhi2[0]+(int)(1.0*(danxian_zhi2[0]-danxian_zhi2[1]));
//      Ccd_getline_flag=1;
//    }
//  }
//  
//  if(danxian == 0)  
//    ccd_target=(line_left[0]+line_right[0])/2;       //�ϴ����Һ��ߵ��м�ֵ
//  else ccd_target=danxian_zhi2[0];
//  if(ccd_target<1) ccd_target=1;                    //����м�ֵС��1����Ĭ��Ϊ0
//  if(ccd_target>126) ccd_target=126;                //����м�ֵ����126����Ĭ��Ϊ126
//  
///****************   ���ߴ��ϴε��м� ����Ѱ��    ********************/  
////  if(zhijiao_hei>=1) zhijiao_hei_error=30;
////  else zhijiao_hei_error=15;
//  no_left_line=1;                                   //��ûѰ������
//  if(ccd_target>121) ccd_target1=126;
//  else ccd_target1=ccd_target+5;
//  for(i=ccd_target1;i>10;i--)                         //���������л��䣬�ӵ�5��֮����Ч
//  {
//    error=Pixe2[i]-Pixe2[i-5];        //            //4��֮����½����������ķ�ֵ�ж�
//    if(error>targe_error && Pixe2[i-5]<100 ) {
//        no_left_line=0;                             //�ҵ�����
//        line_left1=i-2;
//        break;
//    }
//  }
///****************    ���ߴ��ϴε��м� ����Ѱ��   ********************/
//  no_right_line=1;                                  //��ûѰ������
//  if(ccd_target<6) ccd_target1=1;
//  else ccd_target1=ccd_target-5;
//  for(i=ccd_target1;i<118;i++)                       //���������л��䣬�ӵ�118��֮ǰ��Ч   
//  {                                                 
//    error=Pixe2[i]-Pixe2[i+5]; //                   //4��֮����½����������ķ�ֵ�ж� 
//    if(error>targe_error && Pixe2[i+5]<100 )  {
//        no_right_line=0;                            //�ҵ�����
//        line_right1=i+2;
//        break;
//    }
//  } 
///*******************   ���۶������   ****************************/
// // gpio_set   (PTC0,   0);
//  if((no_right_line==1)&&(no_left_line==0))        //no_right_line=1��˵��������
//  {
//    //gpio_set   (PTC0,   1);// 
//    //if( line_right[0]<114) gpio_set   (PTC0,   1);//
//    if(danxian==0 && zhijiao_hei>=1 && line_right[0]<98) {//���ұߣ�ֱ�ǣ�šһ��
//      zhijiao_hei=0;
//      zhijiao_line_right=1;//����ֱ��׼����ת
//    }else 
//    {
//      Ccd_getline_flag=1;
//      line_left[2]=line_left[1];
//      line_left[1]=line_left[0];
//      line_left[0]=line_left1;                     //�������飬�����µ�����
//      line_right[2]=line_right[1];
//      line_right[1]=line_right[0];
//      line_right[0]=line_right[0]+(line_left[0]-line_left[1])*10/10;//��һ�ߵ��ߣ�����һ�ߵ�ƫ����
//    }
//  } else if((no_right_line==0)&&(no_left_line==1))        //no_left_line=1��˵��������
//  {
//    //gpio_set   (PTC0,   1);// 
//    //if(line_left[0]>14 ) gpio_set   (PTC0,   1);//
//    if(danxian==0 && zhijiao_hei>=1 && line_left[0]>30) {
//      zhijiao_hei=0;
//      zhijiao_line_left=1;//����ֱ��׼����ת
//    }else
//    {
//      Ccd_getline_flag=1;
//      line_right[2]=line_right[1];
//      line_right[1]=line_right[0];
//      line_right[0]=line_right1;                    //�������飬�����µ�������
//      line_left[2]=line_left[1];
//      line_left[1]=line_left[0];
//      line_left[0]=line_left[0]+(line_right[0]-line_right[1])*10/10;  //��һ�ߵ��ߣ�����һ�ߵ�ƫ����
//    }
//  }else if((no_right_line==1)&&(no_left_line==1))        //�����ߣ�ȫ�׻�ȫ��
//  {
//    B_flog=0;  
//    if(ccd_avg>100) 
//    {
//      B_flog=1;                       //ccdƽ��ֵ���ڷ�ֵ��ȫ����ʮ�֣������ǿ���߶���     
//      Ccd_getline_flag=1;
//    }
//  }else if((no_right_line==0)&&(no_left_line==0))        //������&&(line_right1-line_left1)>30
//  {
//    if(zhijiao_CCD3_chu==1)
//    {
//      zhijiao_line_left=0;
//      zhijiao_line_right=0;
//      zhijiao_CCD3_chu=0;
//      zhijiao_turning=0;  
//      zhijiao_hei=0;
//      zhijiao_chu_shu=1;
//      zhijiao_heheda=1;
//      //gpio_set   (PTC0,   1);
//    }else if(danxian==1 && danxian_get1==0 && line_right1-danxian_zhi2[0]>8 && danxian_zhi2[0]-line_left1>8)
//    {
//      danxian=0;
//      zhijiao_allow = 1;
//      zhijiao_hei=0;
//    }else if(zhijiao_heheda>=30 && B_flog_wangxing==0 && danxian==0&& line_left1-line_left[0]>12 && line_right[0]-line_right1<3)
//    {
//      zhangai_hei_zuo=1; 
//      //zhangai_time1=4+(zhangai_time1-4)/Speed_Rate;
//
//    }else if(zhijiao_heheda>=30 && B_flog_wangxing==0 && danxian==0 && line_right[0]-line_right1>12 && line_left1-line_left[0]<3)
//    {
//      zhangai_hei_you=1;   
//      //zhangai_time1=4+(zhangai_time1-4)/Speed_Rate;
//    } 
//    
//    
//    if(zhijiao_line_right==0 && zhijiao_line_left==0)
//    {
//      Ccd_getline_flag=1;
//      //if(line_right1-line_left1>30)
//      //{
//        
//        line_right[2]=line_right[1];
//        line_right[1]=line_right[0];
//        line_right[0]=line_right1;                     //�������飬�����µ�������
//        line_left[2]=line_left[1];
//        line_left[1]=line_left[0];
//        line_left[0]=line_left1; 
//      //}
//    }
//  }
//  
///*********      ����Turning    ***************************/
//  if(Ccd_getline_flag==0) 
//  {
//    Turning1=Turning;
//    Turning=Turning+(Turning-Turning1);
//  }else 
//  {
//    Turning1=Turning;
//    Turning=64-(line_left[0]+line_right[0])/2;
//  }
//  
///*********   ֱ�Ǻ��ϰ��ĸ���ʱ�䴦��     *******************/
//  if(zhijiao_line_right == 1 || zhijiao_line_left == 1)
//  {
//    zhijiao_turning++;    //����ֱ�Ǻ���ʱת
//  }else zhijiao_turning=0;
//  
////  if(zhangai_hei_zuo == 1 || zhangai_hei_you == 1)
////  {
////    zhangai_time++;
////  }else zhangai_time=0;
////  if(zhangai_time>=zhangai_time1)
////  {
////     zhangai_time=0;
////     zhangai_hei_zuo=0;
////     zhangai_hei_you=0;
////     zhangai_time1=8;
////  }
//  if(B_flog==1 ) B_flog_wangxing=1;
//  if(B_flog_wangxing>=1) B_flog_wangxing++;
//  if(B_flog_wangxing>=20) B_flog_wangxing=0;
///*****************    ���⴦��      **************************/
//  //gpio_set   (PTC0,   0); 
//  if(danxian==1) 
//  {     
//    Turning = (int)(1*(64-danxian_zhi2[0]));
//    //gpio_set   (PTC0,   1); 
//  }else if(zhijiao_turning>=zhijiao_turning_time && zhijiao_line_right == 1)
//  {
//    zhijiao_turning=zhijiao_turning_time;
//    //gpio_set   (PTC0,   1); 
//  }else if(zhijiao_turning>=zhijiao_turning_time && zhijiao_line_left == 1)
//  {
//    zhijiao_turning=zhijiao_turning_time;
//    //gpio_set   (PTC0,   1);  
//  }else if(zhangaijifen <= 1500 && zhangai_hei_zuo == 1) //zhangai_time
//  {
//    //Turning = Turning-20;
//    //gpio_set   (PTC0,   1);
//  }else if(zhangaijifen <= 1500 && zhangai_hei_you == 1) 
//  {
//    //Turning = Turning+20;
//    //gpio_set   (PTC0,   1);
//  }else if(B_flog==1) 
//  {
//    Turning = 0;//ʮ��
//    B_flog=0;
//    gpio_set   (PTC0,   1); 
//  }

}

void Delay(uint32 a)
{
  uint32 b=900000,c=900000;
  for(;a>0;a--)
    for(;b>0;b--)
      for(;c>0;) c--;
        
}


