//#include "include.h"
//
//
///*************************************************************************
//*  �������ƣ�Send_Image_to_LCD
//*  ����˵��������ʾ������ʾӥ��ͼ��
//*  ����˵����imgΪָ��
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-14    �Ѳ���
//*************************************************************************/
//void Send_Image_to_LCD(unsigned char img[CAMERA_H][CAMERA_DMA_NUM])
//{
//    int i,j,k;
//    LCD_SetPos(0,CAMERA_W-1,0,CAMERA_H-1);
//    for(i=0;i < CAMERA_H - 20;i++)
//    {
//        for(j = 0;j < CAMERA_DMA_NUM; j++)
//            for(k = 0;k < 8; k++)
//                if(img[i][j]&(0x80>>k))              
//                    write_word(Black);	//дͼ������
//                else
//                    write_word(White);		//дͼ������     
//    }
//}
//
///*************************************************************************
//*  �������ƣ�LCD_Draw_Imageline
//*  ����˵������Image��һ�У���ʾ����ʾ����
//*  ����˵����Pixel[]Ϊ����ָ�룬hangΪҪ��ʾ�ڼ���
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-14    �Ѳ���
//*************************************************************************/
//void Send_ImageLine_to_LCD(unsigned char Pixel[],unsigned hang)
//{
//    /*static unsigned char ImageLine[320];
//    unsigned int i;
//    static int centre_line[Process_Hang+2],black_L_line[Process_Hang+2],black_R_line[Process_Hang+2];
//
//    //������
//    Draw_single_line('L',black_L_line[hang],Black);//��ԭ
//    black_L_line[hang]= (int)(black_L[hang]/2.0);
//    if(black_L_line[hang] < 0)
//        black_L_line[hang] = 0;
//    else if(black_L_line[hang]  > 320)
//        black_L_line[hang] = 319;
//    Draw_single_line('L',black_L_line[hang],White);//��ɫ
//
//    //��������
//    Draw_single_line('L',centre_line[hang],Black);//��ԭ
//    centre_line[hang] = (int)(centre[hang]/2.0);
//    if(centre_line[hang] < 0)
//        centre_line[hang] = 0;
//    else if(centre_line[hang] > 320)
//        centre_line[hang] = 319;
//    Draw_single_line('L',centre_line[hang],White);//��ɫ
//
//    //������
//    Draw_single_line('L',black_R_line[hang],Black);//��ԭ
//    black_R_line[hang] = (int)(black_R[hang]/2.0);
//    if(black_R_line[hang] < 0)
//        black_R_line[hang] = 0;
//    else if(black_R_line[hang] > 320)
//        black_R_line[hang] = 319;
//    Draw_single_line('L',black_R_line[hang],White);//��ɫ
//
//    //����ǰ��һ����
//    for(i=0;i<320;i++)
//    {
//      LCD_SetPos(i,i,239 - ImageLine[i],239 - ImageLine[i]);
//      write_word(Black);//��ԭ
//      if(Pixel[i*2] > 239)
//          ImageLine[i] = 239;
//      else
//          ImageLine[i] = Pixel[i*2];
//      LCD_SetPos(i,i,239 - ImageLine[i],239 -ImageLine[i]);
//      write_word(White);//��ɫ
//    }*/
//}
//
//
///*************************************************************************
//*  �������ƣ�LCD_Draw_Imageline
//*  ����˵������demok��λ����������ͼ������
//*  ����˵����hangΪҪ���Ͷ�����
//*  �������أ���
//*  �޸�ʱ�䣺2012-2-14    �Ѳ���
//*************************************************************************/
//void Send_Image_to_Demok(unsigned int hang)
//{
//    /*int i,j;
//    uart_putchar(UART3,0xff);
//    for(i=0;i < hang;i++)
//    {
//        for(j = 0;j < Lie; j++) //demok tools ��ͼģʽ
//        {
//            if(Image[i][j]==255)
//                uart_putchar(UART3,254);
//            else
//                uart_putchar(UART3,Image[i][j]);
//        }
//    }*/
//}
