#include "include.h"

//�µ���־
unsigned char Slope_Check_enable=0;
unsigned char Slope_flag=0;



/*************************************************************************
*  �������ƣ�Test_startline_by_camera
*  ����˵������ͼ����������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*************************************************************************/
void Judge_startline_by_camera()
{
    //ѭ������i
    int i;
    //�������������������߲ɼ���־
    unsigned char Rightblack,Leftblack;
    //����������ɨ���¼�ڵ���
    unsigned int Leftcount,Rightcount;
    //���ҵ�һ���ڵ���С�����
    unsigned int Leftrow_pre,Leftcol_pre,Rightrow_pre,Rightcol_pre;
    //�������ߵ�����
    unsigned int Leftline1,Leftline2,Rightline1,Rightline2,Widthdiv;
    //������ɨ��ʱ����У�����С�����
    int Leftrow_next,Leftcol_next,Rightrow_next,Rightcol_next;
    //�Ƿ�����ɨ��ı�־λ
    unsigned char jumpflag;
    //unsigned int rowave,Midcount;
    
    get_black_line_oth(ov7725_eagle_img_buff[200],200);
    
    Leftcount = 0;  //��߼�������
    Rightcount = 0; //�ұ߼�������
    Leftblack = 0;
    Rightblack = 0;
    //�����߱�־λ
    StartLine.flag = 0; 
    //������ȵ�1/6
    Widthdiv = halfwidth_oth[200]/3; 
    //�������ߵ�����
    Leftline1 = black_L_oth[200] + Widthdiv;
    Leftline2 = black_L_oth[200] + 2*Widthdiv;
    Rightline1 = black_R_oth[200] - Widthdiv;
    Rightline2 = black_R_oth[200] - 2*Widthdiv;
    //������ɨ��ʱ����У�����С�����
    Leftrow_pre = 0;
    Leftcol_pre = 0;
    Rightrow_pre = 0;
    Rightcol_pre = 0;
    //�޷���������������������
    if((Leftline1<50)||(Leftline1>270)||(Rightline2<50)||(Rightline2>270))
        return; 
    
    
    //Ѱ��ߺ���
    for(i = 200;i>=170;i=i-2)
    {
        //��б��Ϊ2����
        Leftline2=Leftline2+2; 
        Leftline1=Leftline1+2;
        //�� Leftline2 ����������ɫ
        if(ov7725_eagle_img_buff2Image(i,Leftline2) == 1)
        {
            Leftrow_pre = i;
            Leftcol_pre = Leftline2;
            Leftblack = 1;
            break;
        } //�� Leftline1 ����������ɫ
        else if(ov7725_eagle_img_buff2Image(i,Leftline1) == 1)
        {
            Leftrow_pre = i;
            Leftcol_pre = Leftline1;
            Leftblack = 1;
            break;
        } //��û������ɫ�����ûѰ������
        else
        {
            Leftblack = 0;
        }
    }   
    
    //Ѱ�ұߺ���
    for(i = 200;i>=170;i=i-2)
    { 
        //��б��Ϊ2����
        Rightline1=Rightline1-2;
        Rightline2=Rightline2-2;
        //�� Rightline2 ����������ɫ
        if(ov7725_eagle_img_buff2Image(i,Rightline2) == 1)
        {
            Rightrow_pre = i;
            Rightcol_pre = Rightline2;
            Rightblack = 1;
            break;
        } //�� Rightline1 ����������ɫ
        else if(ov7725_eagle_img_buff2Image(i,Rightline1) == 1)
        {
            Rightrow_pre = i;
            Rightcol_pre = Rightline1;
            Rightblack = 1;
            break;
        } //��û������ɫ,�ұ�ûѰ������
        else
        {
            Rightblack = 0;
        }
    } 
    
    //���Һ��߾��ҵ������Һ�����������������Ҳ��20�����м���һ�ΰ�ɫ
    if((Leftblack==1)&& (Rightblack==1) &&((Rightcol_pre-Leftcol_pre)>20))
    {
        //���(������)
        Leftrow_next = Leftrow_pre;
        Leftcol_next = Leftcol_pre-2;
        jumpflag = 1;
        while(jumpflag == 1)   //Leftcol_next>50
        {
            //�޷�
            if((Leftrow_next<150)||(Leftrow_next>220)||(Leftcol_next<50)||(Leftcol_next>270))
                return;
            //Leftrow_next ����4�����ڶ��п��ܴ��ںڵ�
            for(i = Leftrow_next+4;i>=Leftrow_next-4;i--)
            {
                //�����ڵ�
                if(ov7725_eagle_img_buff2Image(i,Leftcol_next) == 1)
                {
                    Leftrow_next = i;
                    Leftcol_next = Leftcol_next-2;//����
                    Leftcount++; //��¼�ڵ���
                    jumpflag = 1;
                    break;
                } //û�����ڵ�
                else
                    jumpflag = 0;
            }
            if(jumpflag == 0)
                break;   
        }  
        //����ͬ��~~
        //��ߣ��Ҳ������
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
        //�ұ�(�Ҳ����)
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
        //�ұߣ���������
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
*  �������ƣ�Judge_Ren
*  ����˵��������ʶ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
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
    
    //һ�δ���
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
    
    ov7725_eagle_img_buff
    //��ת����ʶ��
    if(getLeft_flag_oth[Renrow1]==0&&getRight_flag_oth[Renrow1]==1 //Renrow1Ϊ����
       &&getLeft_flag_oth[Renrow2]==1&&getRight_flag_oth[Renrow2]==1 //Renrow2Ϊ˫��
           &&getLeft_flag_oth[Renrow3]==1&&getRight_flag_oth[Renrow3]==1 //Renrow3Ϊ˫��
               &&black_R_oth[Renrow2]-black_R_oth[Renrow1]>2     //�����޷����ų�ʮ��
                   &&black_R_oth[Renrow2]-black_R_oth[Renrow1]< 15  //�����޷����ų����   ������ֵ
                       &&black_L_oth[Renrow2]-black_L_oth[Renrow3]>2     
                           &&black_L_oth[Renrow2]-black_L_oth[Renrow3]< 15)  
    {
        //���߼�⣬ʮ�ֳ��䲻�����ܳ�����
        Renrow_next = Renrow1;
        Rencol_next = black_R_oth[Renrow1]; 
        for(i = 0;i<15;i++)   
        {
            for(j = Rencol_next-4;j<=Rencol_next+1;j++)
            {
                //�����ڵ�
                if(ov7725_eagle_img_buff2Image(Renrow_next,j) == 1)
                {
                    Renrow_next = Renrow_next-2;//����
                    Rencol_next = j;
                    Singlelinecount++; //��¼�ڵ���
                    jumpflag = 1;
                    break;
                } //û�����ڵ�
                else
                    jumpflag = 0;
            }
            if(jumpflag == 0)
                break; 
        }  
        if(Singlelinecount>13)
        {
            //Ѱ�������ϵĵ�һ���ڵ�
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
            //��һ���ڱ߼���
            while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 1)
            {
                blackcount1++;
                Renrow_next = Renrow_next - 1;
                Rencol_next = Rencol_next + 1;    
                if(Renrow_next<10||Rencol_next>310)  //����
                    return;
            } 
            //��һ���ױ߼���
            if((blackcount1>=blackcount1_min) && (blackcount1<=blackcount1_max))
            {
                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 0)
                {
                    
                    whitecount1++; 
                    Renrow_next = Renrow_next - 1;
                    Rencol_next = Rencol_next + 1;    
                    if(Renrow_next<10||Rencol_next>310)  //����
                        return;
                }
            }
            else
                return;
            //�ڶ����ڱ߼���
//            if((whitecount1>=whitecount1_min) && (whitecount1<=whitecount1_max) && (whitecount1<=blackcount1+1))
//            {
//                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 1)
//                {
//                    blackcount2++; 
//                    Renrow_next = Renrow_next - 1;
//                    Rencol_next = Rencol_next + 1;  
//                    if(Renrow_next<10||Rencol_next>310)  //����
//                        return;
//                } 
//            }
//            else
//                return;
            //�ڶ����ױ߼���
//            if((blackcount2>=blackcount2_min) && (blackcount2<=blackcount2_max) && (blackcount2<=whitecount1+1))
//                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 0)
//                {
//                    whitecount2++; 
//                    Renrow_next = Renrow_next - 1;
//                    Rencol_next = Rencol_next + 1;  
//                    if(Renrow_next<10||Rencol_next>310)  //����
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
    
    
    
    //��ת����ʶ��
    if(getLeft_flag_oth[Renrow1]==1 && getRight_flag_oth[Renrow1]==0 //Renrow1Ϊ����
       &&getLeft_flag_oth[Renrow2]==1 && getRight_flag_oth[Renrow2]==1 //Renrow2Ϊ˫��
           &&getLeft_flag_oth[Renrow3]==1 && getRight_flag_oth[Renrow3]==1 //Renrow3Ϊ˫��
               &&black_L_oth[Renrow1]-black_L_oth[Renrow2]>2     //�����޷����ų�ʮ��
                   &&black_L_oth[Renrow1]-black_L_oth[Renrow2]< 15  //�����޷����ų����   ������ֵ
                       &&black_R_oth[Renrow3]-black_R_oth[Renrow2]>2     
                           &&black_R_oth[Renrow3]-black_R_oth[Renrow2]< 15) 
    {
        //���߼�⣬ʮ�ֳ��䲻�����ܳ�����
        Renrow_next = Renrow1;
        Rencol_next = black_L_oth[Renrow1]; 
        for(i = 0;i<15;i++)   
        {
            for(j = Rencol_next+4;j>=Rencol_next-1;j--)  //black_L ��black_R���ǰ׵�
            {
                //�����ڵ�
                if(ov7725_eagle_img_buff2Image(Renrow_next,j) == 1)
                {
                    Renrow_next = Renrow_next-2;//����
                    Rencol_next = j;
                    Singlelinecount++; //��¼�ڵ���
                    jumpflag = 1;
                    break;
                } //û�����ڵ�
                else
                    jumpflag = 0;
            }
            if(jumpflag == 0)
                break; 
        }  
        if(Singlelinecount>13)
        {
            //Ѱ�������ϵĵ�һ���ڵ�
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
            //��һ���ڱ߼���
            while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 1)
            {
                blackcount1++;  
                Renrow_next = Renrow_next - 1;
                Rencol_next = Rencol_next - 1;   
                if(Renrow_next<10||Rencol_next<10)  //����  
                    return;
            } 
            //��һ���ױ߼���
            if((blackcount1>=blackcount1_min) && (blackcount1<=blackcount1_max))
            {
                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 0)
                {
                    
                    whitecount1++; 
                    Renrow_next = Renrow_next - 1;
                    Rencol_next = Rencol_next - 1;    
                    if(Renrow_next<10||Rencol_next<10)  //����
                        return;
                }
            }
            else
                return;
            //�ڶ����ڱ߼���
//            if((whitecount1>=whitecount1_min) && (whitecount1<=whitecount1_max) && (whitecount1<=blackcount1+1))
//            {
//                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 1)
//                {
//                    blackcount2++;
//                    Renrow_next = Renrow_next - 1;
//                    Rencol_next = Rencol_next - 1;    
//                    if(Renrow_next<10||Rencol_next<10)  //����
//                        return;
//                } 
//            }
//            else
//                return;
            
            //�ڶ����ױ߼���
//            if((blackcount2>=blackcount2_min) && (blackcount2<=blackcount2_max) && (blackcount2<=whitecount1+1))
//            {
//                while(ov7725_eagle_img_buff2Image(Renrow_next,Rencol_next) == 0)
//                {
//                    whitecount2++; 
//                    Renrow_next = Renrow_next - 1;
//                    Rencol_next = Rencol_next - 1;    
//                    if(Renrow_next<10||Rencol_next<10)  //����
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
        _LED2=0;
    }
    else
        Ren.flag = 0;
}

    
    
    



/*************************************************************************
*  �������ƣ�Block_judge
*  ����˵����שͷʶ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*************************************************************************/
void Block_judge()
{
#define Blockrow1 124
#define Blockrow2 139  
#define Straightrow1 184
#define Straightrow2 199
    //ʱ�����350us
    
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
        if((centre_delta < 10) && (centre_delta > -10)) //������Ϊ������С���
            return;
        else if(centre_delta <= -10) //���ϰ�
            Left_Block_Poss=1;         //else ���ϰ�
        
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
*  �������ƣ�get_black_line_correct
*  ����˵����Ϊ�ϰ�ʶ���õ�����Ѱ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*************************************************************************/
void get_black_line_correct(unsigned char *ImageData_in,int hang)  //��ֵ
{ 
    int i,ccd_start=5,ccd_end=315;
    unsigned char getleft_flag=0,getright_flag=0; 
    int Left_Count, Right_Count;
    static unsigned int _black_R,_black_L,Middle=CENTER,_halfwidth=50;
    static unsigned char ImageData[Lie+2];
    
    
    Middle = 160;
    _halfwidth = 50;
    
    //��ѹ
    for(i=0;i<40;i++)
        for(int k=0;k<8;k++)
            ImageData[i*8+k] = (ImageData_in[i]>>(7-k))&0x01;
    
    //�ҵ��ұ�
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
    //�ҵ����
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
    
    //����������  
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
    //�޷� Middle
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
*  �������ƣ�Slope_Check
*  ����˵�����µ�ʶ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
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
