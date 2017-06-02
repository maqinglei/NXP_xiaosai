#include"include.h"
/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��SmallS_Cross.c
 * ����         ��СS��ʮ�ֵ��ж�
 * ʵ��ƽ̨     ������ӡ�󿪷���
 * ��汾       ������Ұ���
 * Ƕ��ϵͳ     ��
 * ����         ��xuxu
**********************************************************************************/ 



//ʮ�ֱ�־λ
unsigned char Cross_flag=0;
#define Cross_THPoint 130
//СS
unsigned char smallS_flag=0;




/*************************************************************************
*  �������ƣ�Store_History
*  ����˵�������м�¼��ʷֵ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
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
*  �������ƣ�Cross_judge
*  ����˵�����ж�����ʮ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
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
//����һ��40�������ܺ�
int sum_OneRow(unsigned int hang)
{
    int sum=0;
    for(int i=0;i<40;i++)
        sum+=ov7725_eagle_img_buff[hang][i];
    return sum;
}
//����һ��240�������ܺ�
int sum_OneCol(unsigned int lie)
{
    int sum=0;
    for(int i=0;i<240;i++)
        sum+=ov7725_eagle_img_buff[i][lie];
    return sum;
}




/*************************************************************************
*  �������ƣ�Judge_smallS
*  ����˵�����ж�СS����Ҫ����ֱ���ȥ��ֱ��������û���á�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    no����
*************************************************************************/
unsigned char Judge_smallS()
{
    return 0;
}