#include "include.h"


/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
* 文件名       ：Process.c
* 描述         ：最高端霸气的图像处理代码
* 实验平台     ：凌立印象开发板
* 库版本       ：基于野火库
* 嵌入系统     ：
* 作者         ：xuxu
**********************************************************************************/
#define ov7725_eagle_img_buff2Image(row,col) ((ov7725_eagle_img_buff[row][col/8]>>(7-col%8))&0x01)

//坡道标志
unsigned char Slope_Check_enable=0;
unsigned char Slope_flag=0;


void Judge_startline_by_camera();
void Judge_Ren();
void Block_judge();
void get_black_line_correct(unsigned char *ImageData_in,int hang);
void Slope_Check();


//真实输出
int black_centre=CENTER;
int H=120;
unsigned char Multiple_line_enable=0;
//坐标
int centre[Process_Hang+2]={0};
int black_L[Process_Hang+2]={0};
int black_R[Process_Hang+2]={0};
int halfwidth[Process_Hang+2]={0};
unsigned char getLeft_flag[Process_Hang+2]={0};
unsigned char getRight_flag[Process_Hang+2]={0};
//坐标
int centre_oth[Process_Hang+2]={0};
int black_L_oth[Process_Hang+2]={0};
int black_R_oth[Process_Hang+2]={0};
int halfwidth_oth[Process_Hang+2]={0};
unsigned char getLeft_flag_oth[Process_Hang+2]={0};
unsigned char getRight_flag_oth[Process_Hang+2]={0};
//加权平均
int centre_ratio_step=0;
int valid_farthest=180;
int near_hang=180;
int far_hang=70;
int _halfwidth_min[Process_Hang]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,32,33,33,34,34,35,35,36,37,37,38,38,39,39,40,40,41,41,42,42,43,43,44,44,45,46,46,46,47,48,48,49,49,50,50,51,52,52,52,53,54,54,55,55,56,56,57,57,58,58,59,59,60,60,61,61,62,62,63,63,64,64,65,65,66,67,67,67,68,68,69,69,69,70,71,71,71,72,72,73,73,74,74,74,75,75,76,76,77,77,78,78,79,79,80,80,81,81,82,82,83,83,84,84,84,85,85,86,86,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int _halfwidth_max[Process_Hang]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,88,88,89,89,89,90,90,91,91,92,92,92,93,93,94,94,94,95,96,96,96,97,97,98,98,98,99,99,100,100,100,101,101,101,102,102,103,103,103,104,104,105,105,105,106,106,107,107,107,108,108,109,109,109,109,110,110,111,111,111,112,112,112,113,113,114,114,114,115,115,116,116,116,116,116,117,117,118,118,118,118,118,119,119,119,120,120,120,120,121,121,121,121,122,122,122,123,123,123,123,123,124,124,124,124,125,125,125,125,125,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float centre_ratio[Process_Hang]={132.4,132.0,131.6,131.2,130.8,130.4,130.0,129.6,129.2,128.8,128.4,128.0,127.6,127.2,126.8,126.4,126.0,125.6,125.2,124.8,124.4,124.0,123.6,123.2,122.8,122.4,122.0,121.6,121.2,120.8,120.4,120.0,119.6,119.2,118.8,118.4,118.0,117.6,117.2,116.8,116.4,116.0,115.6,115.2,114.8,114.4,114.0,113.6,113.2,112.8,112.4,112.0,111.6,111.2,110.8,110.4,110.0,109.6,109.2,108.8,108.4,108.0,107.6,107.2,106.8,106.4,106.0,105.6,105.2,104.8,104.4,104.0,103.6,103.2,102.8,102.4,102.0,101.6,101.2,100.8,100.4,100.0,99.6,99.2,98.8,98.4,98.0,97.6,97.2,96.8,96.4,96.0,95.6,95.2,94.8,94.4,94.0,93.6,93.2,92.8,92.4,92.0,91.6,91.2,90.8,90.4,90.0,89.6,89.2,88.8,88.4,88.0,87.6,87.2,86.8,86.4,86.0,85.6,85.2,84.8,84.4,84.0,83.6,83.2,82.8,82.4,82.0,81.6,81.2,80.8,80.4,80.0,79.6,79.2,78.8,78.4,78.0,77.6,77.2,76.8,76.4,76.0,75.6,75.2,74.8,74.4,74.0,73.6,73.2,72.8,72.4,72.0,71.6,71.2,70.8,70.4,70.0,69.6,69.2,68.8,68.4,68.0,67.6,67.2,66.8,66.4,66.0,65.6,65.2,64.8,64.4,64.0,63.6,63.2,62.8,62.4,62.0,61.6,61.2,60.8,60.4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float centre_ratio_1[Process_Hang]={1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,10.9,11.1,11.3,11.4,11.6,11.7,11.9,12.1,12.2,12.4,12.5,12.7,12.9,13.0,13.2,13.3,13.5,13.6,13.7,13.9,14.0,14.2,14.3,14.4,14.5,14.7,14.8,14.9,15.0,15.1,15.2,15.3,15.4,15.5,15.6,15.7,15.8,15.9,16.0,16.0,16.1,16.2,16.2,16.3,16.3,16.4,16.4,16.5,16.5,16.5,16.6,16.6,16.6,16.6,16.6,16.6,16.6,16.6,16.6,16.6,16.6,16.5,16.5,16.5,16.4,16.4,16.3,16.3,16.2,16.2,16.1,16.0,16.0,15.9,15.8,15.7,15.6,15.5,15.4,15.3,15.2,15.1,15.0,14.9,14.8,14.7,14.5,14.4,14.3,14.2,14.0,13.9,13.7,13.6,13.5,13.3,13.2,13.0,12.9,12.7,12.5,12.4,12.2,12.1,11.9,11.7,11.6,11.4,11.3,11.1,10.9,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
float centre_ratio_2[Process_Hang]={1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,10.9,11.1,11.3,11.4,11.6,11.7,11.9,12.1,12.2,12.4,12.5,12.7,12.9,13.0,13.2,13.3,13.5,13.6,13.7,13.9,14.0,14.2,14.3,14.4,14.5,14.7,14.8,14.9,15.0,15.1,15.2,15.3,15.4,15.5,15.6,15.7,15.8,15.9,16.0,16.0,16.1,16.2,16.2,16.3,16.3,16.4,16.4,16.5,16.5,16.5,16.6,16.6,16.6,16.6,16.6,16.6,16.6,16.6,16.6,16.6,16.6,16.5,16.5,16.5,16.4,16.4,16.3,16.3,16.2,16.2,16.1,16.0,16.0,15.9,15.8,15.7,15.6,15.5,15.4,15.3,15.2,15.1,15.0,14.9,14.8,14.7,14.5,14.4,14.3,14.2,14.0,13.9,13.7,13.6,13.5,13.3,13.2,13.0,12.9,12.7,12.5,12.4,12.2,12.1,11.9,11.7,11.6,11.4,11.3,11.1,10.9,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
float centre_ratio_new[111]={0.3,0.4,0.5,0.5,0.7,0.8,0.9,1.1,1.3,1.5,1.8,2.1,2.4,2.8,3.2,3.7,4.2,4.8,5.5,6.2,7.0,7.9,8.9,10.0,11.1,12.4,13.7,15.1,16.6,18.2,19.9,21.7,23.5,25.4,27.4,29.4,31.4,33.5,35.6,37.7,39.8,41.8,43.8,45.7,47.6,49.3,51.0,52.5,53.9,55.1,56.2,57.1,57.8,58.3,58.6,58.7,58.7,58.6,58.4,58.3,58.0,57.8,57.4,57.1,56.7,56.2,55.7,55.2,54.6,53.9,53.3,52.6,51.9,51.1,50.3,49.5,48.7,47.9,47.0,46.1,45.2,44.3,43.4,42.5,41.6,40.6,39.7,38.8,37.9,36.9,36.0,35.1,34.2,33.4,32.5,31.7,30.8,30.0,29.2,28.4,27.7,27.0,26.2,25.6,24.9,24.2,23.6,23.0,22.4,21.9,21.3};
//历史值
int His_centre[30]={0};
int His_black_L[30]={0};
int His_black_R[30]={0};
int His_halfwidth[30]={0};
unsigned char His_Left_flag[30]={0};
unsigned char His_Right_flag[30]={0};


void Store_History();
void Cross_judge();
int sum_OneRow(unsigned int hang);
int sum_OneCol(unsigned int lie);
unsigned char Judge_smallS();


/*************************************************************************
*  函数名称：Capture_Process_Image
*  功能说明：处理图像信息，算出中线值，并且算出偏差来量
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*  运行时间：?ms,在200M情况下
*************************************************************************/
void Process_Image()
{
    int i;
    int centre_sum = 0;

    //起跑线检测
    if(StartLine.enable==1 && Time_1ms > 15000 && StartLine.flag==0)
        Judge_startline_by_camera();


    //采集中线
    if(Speed.Mode==1 || Speed.Mode==6 || Speed.Mode==7)//1档，4700
    {
        H = 150;
        black_centre = (int)(get_black_line_oth(ov7725_eagle_img_buff[H],H));
        Store_History();
        if(Multiple_line_enable==1)//加权平均才运行
        {
            for(i=near_hang;i>far_hang;i--)
                get_black_line(ov7725_eagle_img_buff[i],i);
            valid_farthest = find_valid_farthest();
            if(valid_farthest==-1 || valid_farthest>130)
            {       
            }
            else
            {
                centre_sum = 0;
                float sum_ratio=0;
                for(i=near_hang;i>valid_farthest;i--)
                {
                    centre_sum += centre[i]*centre_ratio[i];
                    sum_ratio += centre_ratio[i];
                }
                black_centre = (int)(centre_sum/sum_ratio);
            } 
        }
    }
    else if(Speed.Mode==2)//2档，5300
    {
        H = 137;
        black_centre = (int)(get_black_line_oth(ov7725_eagle_img_buff[H],H));
        Store_History();
        if(Multiple_line_enable==1)//加权平均才运行
        {
            for(i=near_hang;i>far_hang;i--)
            {
                get_black_line(ov7725_eagle_img_buff[i],i);
            }
            valid_farthest = find_valid_farthest();
            if(valid_farthest == -1 || valid_farthest > 120)
            {          
            }
            else
            {
                centre_sum = 0;
                float sum_ratio=0;
                for(i=near_hang;i>valid_farthest;i--)
                {
                    centre_sum += centre[i]*centre_ratio[i];
                    sum_ratio += centre_ratio[i];
                }
                if(valid_farthest>95)
                {
                    for(i=valid_farthest;i>95;i--)
                    {
                        centre_sum += centre[valid_farthest+1]*centre_ratio[i];
                        sum_ratio += centre_ratio[i];
                    }
                }
                black_centre = (int)(centre_sum/sum_ratio);
            }
        }
    }
    else if(Speed.Mode==3)//3档，5800
    {
        H = 125;
        black_centre = (int)(get_black_line_oth(ov7725_eagle_img_buff[H],H));
        Store_History();
        if(Multiple_line_enable==1)//加权平均才运行
        {
            for(i=near_hang;i>far_hang;i--)
                get_black_line(ov7725_eagle_img_buff[i],i);
            valid_farthest = find_valid_farthest();
            if(valid_farthest == -1)
            {       
            }
            else
            {
                centre_sum = 0;
                float sum_ratio=0;
                for(i=190;i>valid_farthest;i--)
                {
                    if(i>175)
                        centre_ratio_step = 0;        //8       
                    else if(i>160) 
                        centre_ratio_step = 9;        //10
                    else if(i>145)
                        centre_ratio_step = 9;       //13
                    else if(i>130) 
                        centre_ratio_step = 9;       //16
                    else if(i>115)     //130~115行  属于更靠近自己的行段，单调这段的权重（+2），入90度弯明显内切
                        centre_ratio_step = 20;       //18
                    else if(i>100)
                        centre_ratio_step = 21;       //16
                    else if(i>90)      //100~90行   属于较远离自己的行段，单调这段的权重（+1），入90度弯明显的内切就消失了
                        centre_ratio_step = 16;       //13
                    else if(i>80)
                        centre_ratio_step = 15;        //9    
                    else if(i>70)
                        centre_ratio_step = 15;        //9  
                    else if(i>60)
                        centre_ratio_step = 13;        //9  
                    else if(i>50)
                        centre_ratio_step = 10;        //9  
                    else if(i>40)
                        centre_ratio_step = 5;        //9  
                    else
                        centre_ratio_step = 0;        //9  
                    centre_sum += centre[i]*centre_ratio_step;
                    sum_ratio += centre_ratio_step;                        
                }
                if(valid_farthest>105)
                {
                    for(i=valid_farthest;i>105;i--)
                    {
                        if(i>175)
                            centre_ratio_step = 8;
                        else if(i>160) 
                            centre_ratio_step = 10;
                        else if(i>145)
                            centre_ratio_step = 13;
                        else if(i>130)
                            centre_ratio_step = 16;
                        else 
                            centre_ratio_step = 18;
                        centre_sum += centre[valid_farthest+1]*centre_ratio_step;
                        sum_ratio += centre_ratio_step;                         
                    }
                }
                black_centre = (int)(centre_sum/sum_ratio);
            }
        }
    }
    else if(Speed.Mode==4)//4档，6300
    {
        H = 120;
        black_centre = (int)(get_black_line_oth(ov7725_eagle_img_buff[H],H));
        Store_History();
        if(Multiple_line_enable==1)
        {
            for(i=near_hang;i>far_hang;i--)
                get_black_line(ov7725_eagle_img_buff[i],i);
            valid_farthest = find_valid_farthest();
            if(valid_farthest == -1)
            {       
            }
            else
            {
                centre_sum = 0;
                float sum_ratio=0;
                for(i=190;i>valid_farthest;i--)
                {
                    if(i>175)
                        centre_ratio_step = 0;        //8       
                    else if(i>160) 
                        centre_ratio_step = 10;        //10
                    else if(i>145)
                        centre_ratio_step = 14;       //13
                    else if(i>130) 
                        centre_ratio_step = 16;       //16
                    else if(i>115)     //130~115行  属于更靠近自己的行段，单调这段的权重（+2），入90度弯明显内切
                        centre_ratio_step = 19;       //18
                    else if(i>100)
                        centre_ratio_step = 21;       //16
                    else if(i>90)      //100~90行   属于较远离自己的行段，单调这段的权重（+1），入90度弯明显的内切就消失了
                        centre_ratio_step = 24;       //13
                    else if(i>80)
                        centre_ratio_step = 24;        //9    
                    else if(i>70)
                        centre_ratio_step = 24;        //9  
                    else if(i>60)
                        centre_ratio_step = 24;        //9  
                    else if(i>50)
                        centre_ratio_step = 20;        //9  
                    else if(i>40)
                        centre_ratio_step = 15;        //9  
                    else
                        centre_ratio_step = 0;        //9  
                    centre_sum += centre[i]*centre_ratio_step;
                    sum_ratio += centre_ratio_step;                        
                }
                if(valid_farthest>105)
                {
                    for(i=valid_farthest;i>105;i--)
                    {
                        if(i>175)
                            centre_ratio_step = 8;
                        else if(i>160) 
                            centre_ratio_step = 10;
                        else if(i>145)
                            centre_ratio_step = 13;
                        else if(i>130)
                            centre_ratio_step = 16;
                        else 
                            centre_ratio_step = 18;
                        centre_sum += centre[valid_farthest+1]*centre_ratio_step;
                        sum_ratio += centre_ratio_step;                         
                    }
                }
                black_centre = (int)(centre_sum/sum_ratio);
            }
        }
    }
    else if(Speed.Mode==5)//5档，5500
    {
        H = 130;
        black_centre = (int)(get_black_line_oth(ov7725_eagle_img_buff[H],H));
        Store_History();
        if(Multiple_line_enable==1)
        {
            for(i=near_hang;i>far_hang;i--)
                get_black_line(ov7725_eagle_img_buff[i],i);
            valid_farthest = find_valid_farthest();
            if(valid_farthest == -1)
            {       
            }
            else
            {
                centre_sum = 0;
                float sum_ratio=0;
                for(i=190;i>valid_farthest;i--)
                {
                    if(i>175)
                        centre_ratio_step = 0;        //8       
                    else if(i>160) 
                        centre_ratio_step = 20;        //10
                    else if(i>145)
                        centre_ratio_step = 20;       //13
                    else if(i>130) 
                        centre_ratio_step = 20;       //16
                    else if(i>115)     //130~115行  属于更靠近自己的行段，单调这段的权重（+2），入90度弯明显内切
                        centre_ratio_step = 25;       //18
                    else if(i>100)
                        centre_ratio_step = 30;       //16
                    else if(i>90)      //100~90行   属于较远离自己的行段，单调这段的权重（+1），入90度弯明显的内切就消失了
                        centre_ratio_step = 35;       //13
                    else if(i>80)
                        centre_ratio_step = 40;        //9    
                    else if(i>70)
                        centre_ratio_step = 40;        //9  
                    else if(i>60)
                        centre_ratio_step = 40;        //9  
                    else if(i>50)
                        centre_ratio_step = 40;        //9  
                    else if(i>40)
                        centre_ratio_step = 40;        //9  
                    else if(i>30)
                        centre_ratio_step = 35;        //9  
                    else if(i>20)
                        centre_ratio_step = 10;        //9 
                    else if(i>10)
                        centre_ratio_step = 5;        //9
                    else
                        centre_ratio_step = 0;        //9  
                    centre_sum += centre[i]*centre_ratio_step;
                    sum_ratio += centre_ratio_step;                        
                }
                if(valid_farthest>105)
                {
                    for(i=valid_farthest;i>105;i--)
                    {
                        centre_ratio_step = 30;
                        centre_sum += centre[valid_farthest+1]*centre_ratio_step;
                        sum_ratio += centre_ratio_step;                         
                    }
                }
                black_centre = (int)(centre_sum/sum_ratio);
            }
        }
    }
    else//预防拨码坏了：1档，4700
    {
        H = 140;
        black_centre = (int)(get_black_line(ov7725_eagle_img_buff[H],H));
        Store_History();
    }

    
    
    
    //人字识别
    if(Ren.enable==1 && Ren.flag==0)
        Judge_Ren();
    //坡道检测
    if(Slope_Check_enable==1 && Speed.Mode!=0 && Slope_flag==0 && Time_1ms > 5500)
        Slope_Check();
    else if(Slope_flag==1 && Time_1ms > Slope_time + Slope_delaytime)
        Slope_flag = 0;
    //十字识别
    if(Ren.flag==0) 
        Cross_judge();
    //障碍识别
    if(Ren.flag==0 && Cross_flag==0 && Block.flag==0 && Time_1ms > Block.time + 1000)//Block.enable==1 && //有机会进国赛再改
        Block_judge();
    
    
    //SD(赛场上要干掉)
//    if(SD_enable==1)
//    {
//        if(Time_1ms > Stand_Time)
//            SD_Writedata();
//    }
    //LCD刷屏
    if(Speed.Mode==0)//以下为LCD显示
    {
        //加权平均
        centre_sum = 0;
        float sum_ratio=0;
        for(i=near_hang;i>far_hang;i--)
        {
            get_black_line(ov7725_eagle_img_buff[i],i);
            ov7725_eagle_img_buff[i][centre[i]/8] = ov7725_eagle_img_buff[i][centre[i]/8] | (0x80>>(centre[i]%8));
        } 
        valid_farthest = find_valid_farthest();
        if(valid_farthest!=-1)
        {
            for(i=near_hang;i>valid_farthest;i--)
            {
                centre_sum += centre[i]*centre_ratio[i];
                sum_ratio += centre_ratio[i];
            }
            black_centre = (int)(centre_sum/sum_ratio);
        }
//        LCD_Put_Int(0,200,"va_far:",valid_farthest,Red,Green);
//        LCD_Put_Int(0,220,"centre:",black_centre,Red,Green);
//        Draw_single_line('L',black_centre,BLACK);
//        Draw_single_line('H',near_hang,BLACK);
//        if(valid_farthest != -1)
//            Draw_single_line('H',valid_farthest,BLACK);
//        Draw_single_line('H',far_hang,BLACK);
//        Send_Image_to_LCD(ov7725_eagle_img_buff);
    }
}




/*************************************************************************
*  函数名称：get_black_line_oth（和get_black_line的区别是，里面用的变量不是同一套。防止人字障碍对寻线的影响）
*  功能说明：第八届一行处理的ccd算法
*  参数说明：ImageData_in为某一行的初地址，hang为第几行
*  函数返回：中点的值
*  修改时间：2012-2-14    已测试
*************************************************************************/
int get_black_line_oth(unsigned char *ImageData_in,int hang)  //限值
{ 
    int i,ccd_start=5,ccd_end=315;
    unsigned char getleft_flag=0,getright_flag=0; 
    int Left_Count, Right_Count;
    static int _black_R,_black_L,Middle=CENTER,_halfwidth=80;
    static unsigned char ImageData[Lie+2];
    
    static unsigned char first_run=0;
    if(first_run==0)
    {
        first_run++;
        for(int count=0;count<240;count++)
        {
            centre_oth[count] = 160;
            halfwidth_oth[count] = 80;
        }
    }
    else
    {
        Middle = centre_oth[hang];
        _halfwidth = halfwidth_oth[hang];
    }
    //解压
    for(i=0;i<40;i++)
        for(int k=0;k<8;k++)
            ImageData[i*8+k] = (ImageData_in[i]>>(7-k))&0x01;
    
    Right_Count = Middle;
    while(!(ImageData[Right_Count+3]==BLACK 
            && ImageData[Right_Count+2]==BLACK
                && ImageData[Right_Count+1]==BLACK)
          && Right_Count < ccd_end)
    {Right_Count++;}
    if(Right_Count<ccd_end)
    {
        _black_R = Right_Count;
        getright_flag=1;
    }
    else
        getright_flag=0;
    
    //4.找到左面deal left infomation
    Left_Count = Middle;
    while(!(ImageData[Left_Count-3]==BLACK 
            && ImageData[Left_Count-2]==BLACK
                && ImageData[Left_Count-1]==BLACK)
          && Left_Count > ccd_start)	  
    {Left_Count--;}
    if(Left_Count > ccd_start)
    {
        _black_L = Left_Count;
        getleft_flag=1;
    } 
    else
        getleft_flag=0;
    
    //返回算中线  
    if(getleft_flag==0 && getright_flag==0)
    {
        Middle = CENTER;
    }
    else if(getleft_flag!=1 && getright_flag==1)
    {
        Middle = _black_R - _halfwidth;
        _black_L = _black_R - _halfwidth*2;
    }
    else if(getleft_flag==1 && getright_flag!=1)
    {
        Middle = _black_L + _halfwidth;
        _black_R = _black_L + _halfwidth*2; 
    }
    else if(getleft_flag==1 && getright_flag==1) 
    {
        //半宽限幅
        _halfwidth=(int)((_black_R - _black_L)/2.0) ;
        if(_halfwidth < 80)
            _halfwidth = 80;
        else if(_halfwidth > 110)
            _halfwidth = 110; 
        Middle = (int)((_black_R + _black_L)/2.0) ;
    }
    //limit	 Middle
    if(Middle<60)
        Middle=60;
    else if(Middle>250)
        Middle=250;
    //data record 
    centre_oth[hang] = Middle;
    black_L_oth[hang] = _black_L;
    black_R_oth[hang] = _black_R;
    halfwidth_oth[hang] = _halfwidth;
    getLeft_flag_oth[hang] = getleft_flag;
    getRight_flag_oth[hang] = getright_flag;
    return(Middle);
}



/*************************************************************************
*  函数名称：加权平均get_black_line
*  功能说明：某一行第八届ccd算法
*  参数说明：lie为多少列
*  函数返回：Ren_falg，1为是，0为不是
*  修改时间：2012-2-14    已测试
*************************************************************************/
int get_black_line(unsigned char *ImageData_in,int hang)  //限值
{ 
    int i,ccd_start=5,ccd_end=315;
    unsigned char getleft_flag=0,getright_flag=0; 
    int Left_Count, Right_Count;
    static int _black_R,_black_L,Middle=CENTER,_halfwidth=80;
    static unsigned char ImageData[Lie+2];
    
    static unsigned char first_run=0;
    if(first_run==0)
    {
        first_run++;
        for(int count=0;count<240;count++)
        {
            centre[count] = 160;
            halfwidth[count] = 80;
        }
    }
    else
    {
        if(hang==180)
        { 
            Middle = centre[180];
            _halfwidth = halfwidth[180];
        }
        else
        {
            Middle = centre[hang+1];
            _halfwidth = halfwidth[hang+1];
        }
        
    }
    //解压
    for(i=0;i<40;i++)
        for(int k=0;k<8;k++)
            ImageData[i*8+k] = (ImageData_in[i]>>(7-k))&0x01;
    
    Right_Count = Middle;
    while(!(ImageData[Right_Count+3]==BLACK 
            && ImageData[Right_Count+2]==BLACK
                && ImageData[Right_Count+1]==BLACK)
          && Right_Count < ccd_end)
    {Right_Count++;}
    if(Right_Count<ccd_end)
    {
        _black_R = Right_Count;
        getright_flag=1;
    }
    else
        getright_flag=0;
    
    //4.找到左面deal left infomation
    Left_Count = Middle;
    while(!(ImageData[Left_Count-3]==BLACK 
            && ImageData[Left_Count-2]==BLACK
                && ImageData[Left_Count-1]==BLACK)
          && Left_Count > ccd_start)	  
    {Left_Count--;}
    if(Left_Count > ccd_start)
    {
        _black_L = Left_Count;
        getleft_flag=1;
    } 
    else
        getleft_flag=0;
    
    //返回算中线  
    if(getleft_flag==0 && getright_flag==0)
    {
        Middle = CENTER;
    }
    else if(getleft_flag!=1 && getright_flag==1)
    {
        Middle = _black_R - _halfwidth;
        _black_L = _black_R - _halfwidth*2;
    }
    else if(getleft_flag==1 && getright_flag!=1)
    {
        Middle = _black_L + _halfwidth;
        _black_R = _black_L + _halfwidth*2; 
    }
    else if(getleft_flag==1 && getright_flag==1) 
    {
        //半宽限幅
        _halfwidth=(int)((_black_R - _black_L)/2.0) ;
        if(_halfwidth < _halfwidth_min[hang])
            _halfwidth = _halfwidth_min[hang];
        else if(_halfwidth > _halfwidth_max[hang])
            _halfwidth = _halfwidth_max[hang]; 
        Middle = (int)((_black_R + _black_L)/2.0) ;
    }
    //limit	 Middle
    if(Middle<50)
        Middle=50;
    else if(Middle>270)
        Middle=270;
    //data record 
    centre[hang] = Middle;
    black_L[hang] = _black_L;
    black_R[hang] = _black_R;
    halfwidth[hang] = _halfwidth;
    getLeft_flag[hang] = getleft_flag;
    getRight_flag[hang] = getright_flag;
    return(Middle);
}



/*************************************************************************
*  函数名称：find_valid_farthest
*  功能说明：找到
*  参数说明：lie为多少列
*  函数返回：Ren_falg，1为是，0为不是
*  修改时间：2012-2-14    已测试
*************************************************************************/
int find_valid_farthest()
{
    int double_sides_ct=0,addr_2=near_hang;
    int left_side_ct=0,addr_1L=near_hang;
    int right_side_ct=0,addr_1R=near_hang;
    int zero_side_ct=0,addr_0=near_hang;
    int LRflag_fore,LRflag=1,change_cn=0,add;
    
    
    //寻找各个边线
    for(int i=near_hang;i>far_hang;i--)
    {
        if(getLeft_flag[i]==1 && getRight_flag[i]==1)
        {
            LRflag_fore=LRflag;
            LRflag = 1;
            if(double_sides_ct==0)
            {
                double_sides_ct++;
                addr_2=i;
            }
        }
        if(getLeft_flag[i]==1 && getRight_flag[i]==0)
        {
            LRflag_fore=LRflag;
            LRflag = 2;
            if(left_side_ct==0)
            {
                left_side_ct++;
                addr_1L=i;
            }
        }
        if(getLeft_flag[i]==0 && getRight_flag[i]==1)
        {
            LRflag_fore=LRflag;
            LRflag = 3;
            if(right_side_ct==0)
            {
                right_side_ct++;
                addr_1R=i;
            }
        }
        if(getLeft_flag[i]==0 && getRight_flag[i]==0)
        {
            LRflag_fore=LRflag;
            LRflag = 4;
            if(zero_side_ct==0)
            {
                zero_side_ct++;
                addr_0=i;
            }
        }
        if(i!=near_hang && LRflag!=LRflag_fore)
        {
            change_cn++;
            if(change_cn>=2)
            {
                add=i;
                break;
            }
        }
    }
    
    
    //直线。所有行都有双边
    if(change_cn==0 && (!(getLeft_flag[near_hang]==0 && getRight_flag[near_hang]==0)))
        return (far_hang+1);
    //弯道或者十字。一共两种沿
    else if(change_cn==1)
    {
        //先有双边后（单边 || 十字）
        if(getLeft_flag[near_hang]==1 && getRight_flag[near_hang]==1)
        {
            //有突变的左边，防止十字
            if(left_side_ct==1)
            {
                if(black_L[addr_1L] < black_L[near_hang]-20)//防止弯着入十字
                    return (addr_1L+1);
            }
            else
                return (far_hang+1);
            //有突变的右边，防止十字
            if(right_side_ct==1)
            {
                if(black_R[addr_1R] > black_R[near_hang]+20)//防止弯着入十字
                    return (addr_1R+1);
            }
            else
                return (far_hang+1);
        }
        //先有左边后（双边 || 十字）
        else if(getLeft_flag[near_hang]==1 && getRight_flag[near_hang]==0)
        {
            if(double_sides_ct==1)
                return(addr_2+1);
            else if(zero_side_ct==1)
                return(addr_0+1);
        }
        //先有右边后（双边 || 十字）
        else if(getLeft_flag[near_hang]==0 && getRight_flag[near_hang]==1)
        {
            if(double_sides_ct==1)
                return(addr_2+1);
            else if(zero_side_ct==1)
                return(addr_0+1); 
        }
        //先有十字后（双边 || 单边）
        else if(getLeft_flag[near_hang]==0 && getRight_flag[near_hang]==0)
        {
            return(-1);//此时要特殊处理，因为要出十字了
        }
    }
    //弯道。一共三种种沿
    else if(change_cn==2)
    {
        //先有双边后（单边 || 十字）
        if(getLeft_flag[near_hang]==1 && getRight_flag[near_hang]==1)
        {
            if(zero_side_ct==1)
                return(-1);
            else if(left_side_ct==1 && right_side_ct==1)
                return(-1);
            else if(left_side_ct==1 && right_side_ct==0)
            {
                if(black_L[add] < black_L[near_hang]-20)
                    return(-1);
                else
                    return(add+1);
            }
            else if(left_side_ct==0 && right_side_ct==1)
            {
                if(black_R[add] > black_R[near_hang]+20)//防止弯着入十字
                    return(-1);
                else
                    return(add+1);
            }
        }
        //先有单边后（单边 || 十字）
        else if(getLeft_flag[near_hang]==1 && getRight_flag[near_hang]==0)
        {
            if(zero_side_ct==1 || right_side_ct==1)
                return(-1);
            else if(double_sides_ct==1)
                return(addr_2+1);
        }
        else if(getLeft_flag[near_hang]==0 && getRight_flag[near_hang]==1)
        {
            if(zero_side_ct==1 || left_side_ct==1)
                return(-1);
            else if(double_sides_ct==1)
                return(addr_2+1);
        }
    }
    return(-1);
}



/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：SmallS_Cross.c
 * 描述         ：小S与十字的判断
 * 实验平台     ：凌立印象开发板
 * 库版本       ：基于野火库
 * 嵌入系统     ：
 * 作者         ：xuxu
**********************************************************************************/ 



//十字标志位
unsigned char Cross_flag=0;
#define Cross_THPoint 130
//小S
unsigned char smallS_flag=0;




/*************************************************************************
*  函数名称：Store_History
*  功能说明：队列记录历史值
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/
void Store_History()
{
    #define His_data_num 10
    for(int i=His_data_num;i>0;i--)
    {
        His_centre[i] = His_centre[i-1];
        His_black_L[i] = His_black_L[i-1];
        His_black_R[i] = His_black_R[i-1];
        His_halfwidth[i] = His_halfwidth[i-1];
        His_Left_flag[i] = His_Left_flag[i-1];
        His_Right_flag[i] = His_Right_flag[i-1];
    }
    His_centre[0] = centre_oth[H];
    His_black_L[0] = black_L_oth[H];
    His_black_R[0] = black_R_oth[H];
    His_halfwidth[0] = halfwidth_oth[H];
    His_Left_flag[0] = getLeft_flag_oth[H];
    His_Right_flag[0] = getRight_flag_oth[H];
}



/*************************************************************************
*  函数名称：Cross_judge
*  功能说明：判断有无十字
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/
void Cross_judge()
{
    Cross_flag = 0;
    for(int i=H+20;i>H-20;i--)
    {
        if(sum_OneRow(i)==0)
        {
            Cross_flag = 1;
            black_centre = 160;
            break;
        }
    }
}
//计算一行40个数的总和
int sum_OneRow(unsigned int hang)
{
    int sum=0;
    for(int i=0;i<40;i++)
        sum+=ov7725_eagle_img_buff[hang][i];
    return sum;
}
//计算一列240个数的总和
int sum_OneCol(unsigned int lie)
{
    int sum=0;
    for(int i=0;i<240;i++)
        sum+=ov7725_eagle_img_buff[i][lie];
    return sum;
}




/*************************************************************************
*  函数名称：Judge_smallS
*  功能说明：判断小S，主要用于直冲过去，直到国赛还没有用。。。
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    no测试
*************************************************************************/
unsigned char Judge_smallS()
{
    return 0;
}






/*************************************************************************
*  函数名称：Test_startline_by_camera
*  功能说明：用图像检测起跑线
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/
void Judge_startline_by_camera()
{
    //循环变量i
    int i;
    //起跑线左右两条黑西线采集标志
    unsigned char Rightblack,Leftblack;
    //左右向两边扫描记录黑点数
    unsigned int Leftcount,Rightcount;
    //左、右第一个黑点的行、列数
    unsigned int Leftrow_pre,Leftcol_pre,Rightrow_pre,Rightcol_pre;
    //四条划线的列数
    unsigned int Leftline1,Leftline2,Rightline1,Rightline2,Widthdiv;
    //向两边扫描时不断校正的行、列数
    int Leftrow_next,Leftcol_next,Rightrow_next,Rightcol_next;
    //是否跳出扫描的标志位
    unsigned char jumpflag;
    //unsigned int rowave,Midcount;
    
    get_black_line_oth(ov7725_eagle_img_buff[200],200);
    
    Leftcount = 0;  //左边计数清零
    Rightcount = 0; //右边计数清零
    Leftblack = 0;
    Rightblack = 0;
    //起跑线标志位
    StartLine.flag = 0; 
    //赛道宽度的1/6
    Widthdiv = halfwidth_oth[200]/3; 
    //四条划线的列数
    Leftline1 = black_L_oth[200] + Widthdiv;
    Leftline2 = black_L_oth[200] + 2*Widthdiv;
    Rightline1 = black_R_oth[200] - Widthdiv;
    Rightline2 = black_R_oth[200] - 2*Widthdiv;
    //向两边扫描时不断校正的行、列数
    Leftrow_pre = 0;
    Leftcol_pre = 0;
    Rightrow_pre = 0;
    Rightcol_pre = 0;
    //限幅，不符合跳出整个函数
    if((Leftline1<50)||(Leftline1>270)||(Rightline2<50)||(Rightline2>270))
        return; 
    
    
    //寻左边黑线
    for(i = 200;i>=170;i=i-2)
    {
        //以斜率为2划线
        Leftline2=Leftline2+2; 
        Leftline1=Leftline1+2;
        //在 Leftline2 列上遇到黑色
        if(ov7725_eagle_img_buff2Image(i,Leftline2) == 1)
        {
            Leftrow_pre = i;
            Leftcol_pre = Leftline2;
            Leftblack = 1;
            break;
        } //在 Leftline1 列上遇到黑色
        else if(ov7725_eagle_img_buff2Image(i,Leftline1) == 1)
        {
            Leftrow_pre = i;
            Leftcol_pre = Leftline1;
            Leftblack = 1;
            break;
        } //都没遇到黑色，左边没寻到黑线
        else
        {
            Leftblack = 0;
        }
    }   
    
    //寻右边黑线
    for(i = 200;i>=170;i=i-2)
    { 
        //以斜率为2划线
        Rightline1=Rightline1-2;
        Rightline2=Rightline2-2;
        //在 Rightline2 列上遇到黑色
        if(ov7725_eagle_img_buff2Image(i,Rightline2) == 1)
        {
            Rightrow_pre = i;
            Rightcol_pre = Rightline2;
            Rightblack = 1;
            break;
        } //在 Rightline1 列上遇到黑色
        else if(ov7725_eagle_img_buff2Image(i,Rightline1) == 1)
        {
            Rightrow_pre = i;
            Rightcol_pre = Rightline1;
            Rightblack = 1;
            break;
        } //都没遇到黑色,右边没寻到黑线
        else
        {
            Rightblack = 0;
        }
    } 
    
    //左右黑线均找到，且右黑线最左侧比左黑线最右侧大20，即中间有一段白色
    if((Leftblack==1)&& (Rightblack==1) &&((Rightcol_pre-Leftcol_pre)>20))
    {
        //左边(左侧计数)
        Leftrow_next = Leftrow_pre;
        Leftcol_next = Leftcol_pre-2;
        jumpflag = 1;
        while(jumpflag == 1)   //Leftcol_next>50
        {
            //限幅
            if((Leftrow_next<150)||(Leftrow_next>220)||(Leftcol_next<50)||(Leftcol_next>270))
                return;
            //Leftrow_next 正负4行以内都有可能存在黑点
            for(i = Leftrow_next+4;i>=Leftrow_next-4;i--)
            {
                //遇到黑点
                if(ov7725_eagle_img_buff2Image(i,Leftcol_next) == 1)
                {
                    Leftrow_next = i;
                    Leftcol_next = Leftcol_next-2;//向左
                    Leftcount++; //记录黑点数
                    jumpflag = 1;
                    break;
                } //没遇到黑点
                else
                    jumpflag = 0;
            }
            if(jumpflag == 0)
                break;   
        }  
        //以下同理~~
        //左边（右侧计数）
        Leftrow_next = Leftrow_pre;
        Leftcol_next = Leftcol_pre+2;
        jumpflag = 1;
        while(jumpflag == 1)//Leftcol_next < 210
        {
            if((Leftrow_next<150)||(Leftrow_next>220)||(Leftcol_next<50)||(Leftcol_next>270))
                return;
            for(i = Leftrow_next+4;i>=Leftrow_next-4;i-- )
            {
                if(ov7725_eagle_img_buff2Image(i,Leftcol_next) == 1)
                {
                    Leftrow_next = i;
                    Leftcol_next = Leftcol_next+2;
                    Leftcount++;
                    jumpflag = 1;
                    break;
                }
                else
                    jumpflag = 0;
            }
            if(jumpflag == 0)
                break;   
        }
        //右边(右侧计数)
        Rightrow_next = Rightrow_pre;
        Rightcol_next = Rightcol_pre+2;
        jumpflag = 1;
        while(jumpflag == 1)//Rightcol_next<270
        {
            if((Rightrow_next<150)||(Rightrow_next>220)||(Rightcol_next<50)||(Rightcol_next>270))
                return;
            for(i = Rightrow_next+4;i>=Rightrow_next-4;i--)
            {
                if(ov7725_eagle_img_buff2Image(i,Rightcol_next) == 1)
                {
                    Rightrow_next = i;
                    Rightcol_next = Rightcol_next+2;
                    Rightcount++;
                    jumpflag = 1;
                    break;
                }
                else
                    jumpflag = 0;
            }
            if(jumpflag == 0)
                break;   
        }
        //右边（左侧计数）
        Rightrow_next = Rightrow_pre;
        Rightcol_next = Rightcol_pre-2;
        jumpflag = 1;
        while(jumpflag == 1)//Rightcol_next>110
        {
            if((Rightrow_next<150)||(Rightrow_next>220)||(Rightcol_next<50)||(Rightcol_next>270))
                return;
            for(i = Rightrow_next+4;i>=Rightrow_next-4;i--)
            {
                if(ov7725_eagle_img_buff2Image(i,Rightcol_next) == 1)
                {
                    Rightrow_next = i;
                    Rightcol_next = Rightcol_next-2;
                    Rightcount++;
                    jumpflag = 1;
                    break;
                }
                else
                    jumpflag = 0;
            }
            if(jumpflag == 0)
                break;   
        }
    }
    if((Leftcount>=15) && (Rightcount>=15)&&((Rightcol_next-Leftcol_next)>20) )  //&& (Midcount>12)
    {
        StartLine.time_record = Time_1ms;
        StartLine.flag = 1;
    }
    else
        StartLine.flag = 0;
}





/*************************************************************************
*  函数名称：Judge_Ren
*  功能说明：人字识别
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/
void Judge_Ren()
{
#define Renrow1 160
#define Renrow2 180
#define Renrow3 200
    
#define blackcount1_min 5
#define blackcount1_max 15
#define whitecount1_min 5
#define whitecount1_max 12
#define blackcount2_min 4
#define blackcount2_max 9
#define whitecount2_min 3
#define whitecount2_max 8
    
    unsigned int i,j;
    int Renrow_next,Rencol_next;
    int blackcount1,whitecount1,blackcount2,whitecount2,Singlelinecount;
    int centrecolumn;
    static unsigned char Renturnleft,Renturnright;
    unsigned char jumpflag,blackpoint;
    static unsigned char once_check=0;
    
    //一次触发
    if(Ren.Multiple_enable==0)
    {
        if(once_check==1)
            return;
    }
    else
    {
        if(once_check==2)
            return;
    }
    Renrow_next = 5;
    Rencol_next = 5;
    jumpflag = 0;
    blackpoint = 0;
    Singlelinecount = 0;
    blackcount1 = 0;
    blackcount2 = 0;
    whitecount1  = 0;
    whitecount2  = 0;
    Renturnleft = 0;
    Renturnright = 0;
    
    get_black_line_oth(ov7725_eagle_img_buff[Renrow1],Renrow1);
    get_black_line_oth(ov7725_eagle_img_buff[Renrow2],Renrow2);
    get_black_line_oth(ov7725_eagle_img_buff[Renrow3],Renrow3);
    
    
    //左转人字识别
    if(getLeft_flag_oth[Renrow1]==0&&getRight_flag_oth[Renrow1]==1 //Renrow1为单边
       &&getLeft_flag_oth[Renrow2]==1&&getRight_flag_oth[Renrow2]==1 //Renrow2为双边
           &&getLeft_flag_oth[Renrow3]==1&&getRight_flag_oth[Renrow3]==1 //Renrow3为双边
               &&black_R_oth[Renrow2]-black_R_oth[Renrow1]>2     //单边限幅，排除十字
                   &&black_R_oth[Renrow2]-black_R_oth[Renrow1]< 15  //单边限幅，排除弯道   调整阈值
                       &&black_L_oth[Renrow2]-black_L_oth[Renrow3]>2     
                           &&black_L_oth[Renrow2]-black_L_oth[Renrow3]< 15)  
    {
        //单边检测，十字出弯不正可能出问题
        Renrow_next = Renrow1;
        Rencol_next = black_R_oth[Renrow1]; 
        for(i = 0;i<15;i++)   
        {
            for(j = Rencol_next-4;j<=Rencol_next+1;j++)
            {
                //遇到黑点
                if(ov7725_eagle_img_buff2Image(Renrow_next,j) == 1)
                {
                    Renrow_next = Renrow_next-2;//向上
                    Rencol_next = j;
                    Singlelinecount++; //记录黑点数
                    jumpflag = 1;
                    break;
                } //没遇到黑点
                else
                    jumpflag = 0;
            }
            if(jumpflag == 0)
                break; 
        }  
        if(Singlelinecount>13)
        {
            //寻找人字上的第一个黑点
            centrecolumn = (int)(centre_oth[Renrow2]/10.0*11);
            for(i=Renrow1;i>30;i=i-2)
            {
                if(ov7725_eagle_img_buff2Image(i,centrecolumn) == 1)
                {
                    Renrow_next = i;
                    Rencol_next = centrecolumn; 
                    blackpoint = 1;
                    break;
                }
            }
        }
        
        if(blackpoint == 1)
        {
            //第一条黑边计数
            while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 1)
            {
                blackcount1++;
                Renrow_next = Renrow_next - 1;
                Rencol_next = Rencol_next + 1;    
                if(Renrow_next<10||Rencol_next>310)  //保护
                    return;
            } 
            //第一条白边计数
            if((blackcount1>=blackcount1_min) && (blackcount1<=blackcount1_max))
            {
                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 0)
                {
                    
                    whitecount1++; 
                    Renrow_next = Renrow_next - 1;
                    Rencol_next = Rencol_next + 1;    
                    if(Renrow_next<10||Rencol_next>310)  //保护
                        return;
                }
            }
            else
                return;
            //第二条黑边计数
//            if((whitecount1>=whitecount1_min) && (whitecount1<=whitecount1_max) && (whitecount1<=blackcount1+1))
//            {
//                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 1)
//                {
//                    blackcount2++; 
//                    Renrow_next = Renrow_next - 1;
//                    Rencol_next = Rencol_next + 1;  
//                    if(Renrow_next<10||Rencol_next>310)  //保护
//                        return;
//                } 
//            }
//            else
//                return;
            //第二条白边计数
//            if((blackcount2>=blackcount2_min) && (blackcount2<=blackcount2_max) && (blackcount2<=whitecount1+1))
//                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 0)
//                {
//                    whitecount2++; 
//                    Renrow_next = Renrow_next - 1;
//                    Rencol_next = Rencol_next + 1;  
//                    if(Renrow_next<10||Rencol_next>310)  //保护
//                        return;
//                }
//            else
//                return;
            if((whitecount1>=whitecount1_min) && (whitecount1<=whitecount1_max) && (whitecount1<=blackcount1+1))
                Renturnleft = 1;
            else
                return;
        }
    }
    
    
    
    //右转人字识别
    if(getLeft_flag_oth[Renrow1]==1 && getRight_flag_oth[Renrow1]==0 //Renrow1为单边
       &&getLeft_flag_oth[Renrow2]==1 && getRight_flag_oth[Renrow2]==1 //Renrow2为双边
           &&getLeft_flag_oth[Renrow3]==1 && getRight_flag_oth[Renrow3]==1 //Renrow3为双边
               &&black_L_oth[Renrow1]-black_L_oth[Renrow2]>2     //单边限幅，排除十字
                   &&black_L_oth[Renrow1]-black_L_oth[Renrow2]< 15  //单边限幅，排除弯道   调整阈值
                       &&black_R_oth[Renrow3]-black_R_oth[Renrow2]>2     
                           &&black_R_oth[Renrow3]-black_R_oth[Renrow2]< 15) 
    {
        //单边检测，十字出弯不正可能出问题
        Renrow_next = Renrow1;
        Rencol_next = black_L_oth[Renrow1]; 
        for(i = 0;i<15;i++)   
        {
            for(j = Rencol_next+4;j>=Rencol_next-1;j--)  //black_L 和black_R都是白点
            {
                //遇到黑点
                if(ov7725_eagle_img_buff2Image(Renrow_next,j) == 1)
                {
                    Renrow_next = Renrow_next-2;//向上
                    Rencol_next = j;
                    Singlelinecount++; //记录黑点数
                    jumpflag = 1;
                    break;
                } //没遇到黑点
                else
                    jumpflag = 0;
            }
            if(jumpflag == 0)
                break; 
        }  
        if(Singlelinecount>13)
        {
            //寻找人字上的第一个黑点
            centrecolumn = (int)(centre_oth[Renrow1]/10.0*9);
            for(i=Renrow1;i>30;i=i-2)
            { 
                if(ov7725_eagle_img_buff2Image(i,centrecolumn) == 1)
                {
                    Renrow_next = i;
                    Rencol_next = centrecolumn;  
                    blackpoint = 1;
                    break;
                }
            }
        }
        if(blackpoint == 1) 
        {
            //第一条黑边计数
            while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 1)
            {
                blackcount1++;  
                Renrow_next = Renrow_next - 1;
                Rencol_next = Rencol_next - 1;   
                if(Renrow_next<10||Rencol_next<10)  //保护  
                    return;
            } 
            //第一条白边计数
            if((blackcount1>=blackcount1_min) && (blackcount1<=blackcount1_max))
            {
                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 0)
                {
                    
                    whitecount1++; 
                    Renrow_next = Renrow_next - 1;
                    Rencol_next = Rencol_next - 1;    
                    if(Renrow_next<10||Rencol_next<10)  //保护
                        return;
                }
            }
            else
                return;
            //第二条黑边计数
//            if((whitecount1>=whitecount1_min) && (whitecount1<=whitecount1_max) && (whitecount1<=blackcount1+1))
//            {
//                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 1)
//                {
//                    blackcount2++;
//                    Renrow_next = Renrow_next - 1;
//                    Rencol_next = Rencol_next - 1;    
//                    if(Renrow_next<10||Rencol_next<10)  //保护
//                        return;
//                } 
//            }
//            else
//                return;
            
            //第二条白边计数
//            if((blackcount2>=blackcount2_min) && (blackcount2<=blackcount2_max) && (blackcount2<=whitecount1+1))
//            {
//                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 0)
//                {
//                    whitecount2++; 
//                    Renrow_next = Renrow_next - 1;
//                    Rencol_next = Rencol_next - 1;    
//                    if(Renrow_next<10||Rencol_next<10)  //保护
//                        return;
//                } 
//            }
//            else
//                return;
            
            if((whitecount1>=whitecount1_min) && (whitecount1<=whitecount1_max) && (whitecount1<=blackcount1+1))
                Renturnright = 1;
            else
                return;
        } 
    }
    
    
    
    if(Renturnleft==1||Renturnright==1)
    {
        Ren.flag = 1;
        once_check++;
        Ren.record_time = Time_1ms;
        if(Renturnleft == 1)
            Ren.Loaction = 100;
        else if(Renturnright == 1)
            Ren.Loaction = 200;
       // _LED2=0;
    }
    else
        Ren.flag = 0;
}

    
    
    



/*************************************************************************
*  函数名称：Block_judge
*  功能说明：砖头识别
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/
void Block_judge()
{
#define Blockrow1 124
#define Blockrow2 139  
#define Straightrow1 184
#define Straightrow2 199
    //时间测试350us
    
    int centre_delta=0;
    
    int Lside_delta1=0;
    int Lside_delta2=0;
    int Lside_delta3=0;
    
    int Middle_delta1=0;
    int Middle_delta2=0;  
    int Middle_delta3=0;
    
    int Rside_delta1=0;
    int Rside_delta2=0;
    int Rside_delta3=0;
    
    unsigned char Left_Block_Poss=0; 
    
    unsigned char Right_Block=0;
    unsigned char Left_Block=0;
    
    get_black_line_correct(ov7725_eagle_img_buff[Straightrow2],Straightrow2); 
    get_black_line_correct(ov7725_eagle_img_buff[Straightrow1],Straightrow1); 
    get_black_line_correct(ov7725_eagle_img_buff[Blockrow2],Blockrow2); 
    get_black_line_correct(ov7725_eagle_img_buff[Blockrow1],Blockrow1); 

    
    if(getLeft_flag_oth[Straightrow2]==0 || getRight_flag_oth[Straightrow2]==0 
       || getLeft_flag_oth[Straightrow1]==0 || getRight_flag_oth[Straightrow1]==0
           || getLeft_flag_oth[Blockrow2]==0 || getRight_flag_oth[Blockrow2]==0
               || getLeft_flag_oth[Blockrow1]==0 || getRight_flag_oth[Blockrow1]==0)
        return;
    else
    {
        centre_delta=centre_oth[Straightrow2]-centre_oth[Blockrow2];
        if((centre_delta < 10) && (centre_delta > -10)) //我们认为可能是小弯道
            return;
        else if(centre_delta <= -10) //左障碍
            Left_Block_Poss=1;         //else 右障碍
        
        if(Left_Block_Poss == 1)
        {
            Lside_delta1 = black_L_oth[Blockrow1]-black_L_oth[Blockrow2];
            Lside_delta2 = black_L_oth[Straightrow1]-black_L_oth[Straightrow2];
            Lside_delta3 = black_L_oth[Blockrow2]-black_L_oth[Straightrow1];
            
            Middle_delta1 = centre_oth[Blockrow2]-centre_oth[Blockrow1];
            Middle_delta2 = centre_oth[Straightrow1]-centre_oth[Straightrow2];
            Middle_delta3 = centre_oth[Blockrow1]-centre_oth[Straightrow1];
            
            Rside_delta1 = black_R_oth[Blockrow2]-black_R_oth[Blockrow1];
            Rside_delta2 = black_R_oth[Straightrow2]-black_R_oth[Straightrow1];
            Rside_delta3 = black_R_oth[Straightrow1]-black_R_oth[Blockrow2];
            
            if((Lside_delta1 > -13) && (Lside_delta1 < 13))
            {
                if((Lside_delta2 > 0) && (Lside_delta2 < 40))
                { 
                    if(Lside_delta3 > 40)
                    {
                        if((Middle_delta1 > -10) && (Middle_delta1 < 10))
                        {
                            if((Middle_delta2 > -5) && (Middle_delta2 < 5))
                            {
                                if(Middle_delta3 > 14)
                                {
                                    if((Rside_delta1 > 1) && (Rside_delta2 > 1) && (Rside_delta3 > 6))
                                    {
                                        if(((Rside_delta1 - Rside_delta2) < 7) && ((Rside_delta1 - Rside_delta2) > -7)
                                           && ((Rside_delta3 - Rside_delta1) < 16) && ((Rside_delta3 - Rside_delta1) > -7)
                                               && ((Rside_delta3 - Rside_delta2) < 16) && ((Rside_delta3 - Rside_delta2) > -7))
                                            Left_Block=1;   
                                    } 
                                }  
                            }
                        }
                    }
                }
            }
            if(Left_Block == 0)
            {
                Block.flag=0;
                return;
            }
        }
        else
        {
            Rside_delta1 = black_R_oth[Blockrow2]-black_R_oth[Blockrow1]; 
            Rside_delta2 = black_R_oth[Straightrow2]-black_R_oth[Straightrow1];
            Rside_delta3 = black_R_oth[Straightrow1]-black_R_oth[Blockrow2];
            
            Middle_delta1 = centre_oth[Blockrow1]-centre_oth[Blockrow2];
            Middle_delta2 = centre_oth[Straightrow1]-centre_oth[Straightrow2];
            Middle_delta3 = centre_oth[Straightrow1]-centre_oth[Blockrow2];
            
            Lside_delta1 = black_L_oth[Blockrow1]-black_L_oth[Blockrow2];
            Lside_delta2 = black_L_oth[Straightrow1]-black_L_oth[Straightrow2];
            Lside_delta3 = black_L_oth[Blockrow2]-black_L_oth[Straightrow1];
            
            if((Rside_delta1 > -13) && (Rside_delta1 < 13))
            {
                if((Rside_delta2 > 0) && (Rside_delta2 < 40))
                {
                    if(Rside_delta3 > 40)
                    {
                        if((Middle_delta1 > -10) && (Middle_delta1 < 10))
                        {
                            if((Middle_delta2 > -5) && (Middle_delta2 < 5))
                            {
                                if(Middle_delta3 > 14)
                                {
                                    if((Lside_delta1 > 1) && (Lside_delta2 > 1) && (Lside_delta3 > 6))
                                    {
                                        if(((Lside_delta1 - Lside_delta2) < 7) && ((Lside_delta1 - Lside_delta2) > -7)
                                           && ((Lside_delta3 - Lside_delta1) < 16) 
                                               
                                               && ((Lside_delta3 - Lside_delta1) > -7)
                                                   && ((Lside_delta3 - Lside_delta2) < 16) 
                                                       
                                                       && ((Lside_delta3 - Lside_delta2) > -7))
                                            Right_Block=1;   
                                    } 
                                }  
                            }
                        }
                    }
                }
            }
            if(Right_Block == 0)
            {
                Block.flag=0;
                return;
            }
        }
    }
    if((Left_Block==1) || (Right_Block==1))
    {
        Block.flag = 1;
        Block.time = Time_1ms;
        if(Left_Block==1)
            Block.Offset = Block.Offset_Init;
        else if(Right_Block==1)
            Block.Offset = 0 - Block.Offset_Init;
    }
    else
        Block.flag=0;
}


/*************************************************************************
*  函数名称：get_black_line_correct
*  功能说明：为障碍识别用的中心寻线
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/
void get_black_line_correct(unsigned char *ImageData_in,int hang)  //限值
{ 
    int i,ccd_start=5,ccd_end=315;
    unsigned char getleft_flag=0,getright_flag=0; 
    int Left_Count, Right_Count;
    static unsigned int _black_R,_black_L,Middle=CENTER,_halfwidth=50;
    static unsigned char ImageData[Lie+2];
    
    
    Middle = 160;
    _halfwidth = 50;
    
    //解压
    for(i=0;i<40;i++)
        for(int k=0;k<8;k++)
            ImageData[i*8+k] = (ImageData_in[i]>>(7-k))&0x01;
    
    //找到右边
    Right_Count = Middle;
    while(!(ImageData[Right_Count+3]==BLACK 
            && ImageData[Right_Count+2]==BLACK
                && ImageData[Right_Count+1]==BLACK)
          && Right_Count < ccd_end)
    {Right_Count++;}
    if(Right_Count<ccd_end)
    {
        _black_R = Right_Count;
        getright_flag=1;
    }
    else
        getright_flag=0;
    //找到左边
    Left_Count = Middle;
    while(!(ImageData[Left_Count-3]==BLACK 
            && ImageData[Left_Count-2]==BLACK
                && ImageData[Left_Count-1]==BLACK)
          && Left_Count > ccd_start)	  
    {Left_Count--;}
    if(Left_Count > ccd_start)
    {
        _black_L = Left_Count;
        getleft_flag=1;
    } 
    else
        getleft_flag=0;
    
    //返回算中线  
    if(getleft_flag==0 && getright_flag==0)
    {
        Middle = 160;
    }
    else if(getleft_flag!=1 && getright_flag==1)
    {
        Middle = _black_R - _halfwidth;
        _black_L = _black_R - _halfwidth*2;
    }
    else if(getleft_flag==1 && getright_flag!=1)
    {
        Middle = _black_L + _halfwidth;
        _black_R = _black_L + _halfwidth*2; 
    }
    else if(getleft_flag==1 && getright_flag==1) 
    {
        _halfwidth=(int)((_black_R - _black_L)/2.0) ;
        if(_halfwidth < 80)
            _halfwidth=80;
        else if(_halfwidth >110)
            _halfwidth = 110; 
        Middle = (int)((_black_R + _black_L)/2.0) ;
    }
    //限幅 Middle
    if(Middle<60)
        Middle=60;
    else if(Middle>250)
        Middle=250;
    //data record 
    centre_oth[hang] = Middle;
    black_L_oth[hang] = _black_L;
    black_R_oth[hang] = _black_R;
    halfwidth_oth[hang] = _halfwidth;
    getLeft_flag_oth[hang] = getleft_flag;
    getRight_flag_oth[hang] = getright_flag;
}



/*************************************************************************
*  函数名称：Slope_Check
*  功能说明：坡道识别
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*************************************************************************/
int Slope_time=0;
int Slope_delaytime=0;
void Slope_Check()
{
    unsigned char slope_flag_temp=1;
    for(int i=0;i<=5;i++)
    {
        if(fabs(His_centre[i]-CENTER)>=10)
        {
            slope_flag_temp=0;
            break;
        }
        if(His_Left_flag[i]==0)
        {
            slope_flag_temp=0;
            break;
        }
        if(His_Right_flag[i]==0)
        {
            slope_flag_temp=0;
            break;
        }
        if(His_black_L[i]>=70)
        {
            slope_flag_temp=0;
            break;
        }
        if(His_black_R[i]<=250)
        {
            slope_flag_temp=0;
            break;
        }
        if(His_black_R[i]-His_black_L[i]<=200)
        {
            slope_flag_temp=0;
            break;
        }
    }
    Slope_flag = slope_flag_temp;
    if(Slope_flag==1)
        Slope_time = Time_1ms;
}

