#ifndef  ccdwork_H
#define  ccdwork_H  

extern int16 line_left[3];//�����λ�ô�����飬���3�ε�
extern int16 line_right[3];//�Һ���λ�ô�����飬���3�ε�
extern int zhangai_hei;
extern int zhangai_hei_zuo;
extern int zhangai_hei_you;
extern int zhangai_time;


void ccd_deal(uint8 ch[]);//������ch����ccd��ƽ��ֵ�����ֵ����Сֵ
void ccd_getline();       //��CCD�����Һ���
void Delay(uint32 a);
void ccd2_work();
void ccd3_work();
void zhijiao_hei_work();

#endif
